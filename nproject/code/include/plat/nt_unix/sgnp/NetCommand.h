

#ifndef CNetCommand_H
#define CNetCommand_H

#include "sgnp_base.h"
#include "sgarchive.h"
#include "ace/Thread_Semaphore.h"
#include "NetCmdHelper.h"
#include "sgdataset.h"
//#pragma warning(disable : 4661)

template< class T > void Object_AddRef( T * Refer )
{
	if( Refer != NULL ){ Refer->AddRef( ); }
}

template< class T > void Object_Release( T * & Refer )
{
	if( Refer != NULL ){ Refer->Release( ); Refer = NULL; }
}

template< class T > void Object_Destroy( T * & Object )
{
	if( Object != NULL ){ delete Object; Object = NULL; }
}

///////////////////////////////////////////////////////////////////////////
enum NETCMD_REQUEST_RETVAL
{
	NETCMD_RETVAL_CIRCUITBREAKER		=-99,			//请求过于频繁，发生熔断
	NETCMD_RETVAL_NORMALERR_MIN			=-90,			//常规错误的最小值
	NETCMD_RETVAL_REQERR				=-3,			//没有有效的请求数据
	NETCMD_RETVAL_COMM_ERROR			=-2,			//连接服务错误
	NETCMD_RETVAL_ERROR					=-1,			//返回错误
	NETCMD_RETVAL_SUCCESS				=0,				//返回成功
	NETCMD_RETVAL_WARNING				=1,				//返回警告
};
#define SG_NETCMDHEAD_PROCMOD_COMPRESS	0x01     //压缩标志
#define SG_NETCMDHEAD_PROCMOD_DBLOG		0x02     //数据库日志程序自写标志
#define SG_NETCMDHEAD_PROCMOD_TOUPDB	0x04     //向上级数据库传递
#define SG_NETCMDHEAD_PROCMOD_DBMSG		0x08     //数据库操作发送变更通知
#define SG_NETCMDHEAD_PROCMOD_GAPTRANS	0x10     //发送传过网关，到内部机器
#define SG_NETCMDHEAD_PROCMOD_LOCALNET	0x20     //发送到内部局域网
#define SG_NETCMDHEAD_PROCMOD_USECURSOR	0x40     //使用游标方式

class _DATASET_DLL_EXPORT_ CNetCmdHead
{
public:
	SG_USHORT			CmdType;				//命令号
	SG_USHORT			DBNo;					//操作的数据库No 
	SG_UCHAR			HeadProcMode;			//头处理模式  bit0:压缩标志  bit1:数据库日志程序自写标志 仅sql语句有效
												//bit2:向上级数据库传递 bit3:数据库操作发送变更通知 
	SG_UCHAR			FinishFlag;	//结束包标志
	SG_INT				FrameNo;	//包序号,从0开始
	S_TWOINT			DatInNodePort;		//通过cps转发过来的报文,记录了分配的NodeID,避免报文循环传递
	ACE_INT32			CmdVersion;				//命令版本号
	ACE_UINT32			FrameLen;				//命令长度，对于读取数据的函数中，返回信息中记录数据库中实际记录的个数
												///对于微盒子数据库复合操作请求中,存放电站ID
	ACE_INT32			RetVal;					//返回码 对于实时库请求，若不为缺省值0，则存放固定的节点ID
	ARR_UINT32			WorkSpaces;				//工作空间集合
#if (SG_NET_VERSION>=SG_NET_VERSION_53)
	SG_UINT64			SchemaHandler;	//实时库Schema
	SG_UINT				CursorID;
	SG_INT				Res[4];	//实时库Schema
#endif
	CSgString			RetInfo;				//返回信息,对于实时库请求，存放SchemaHandler
public:
	ACE_UINT32			GetCmdID(){ return CmdType;}
	void				SetCmdID(ACE_UINT32 cmd) { CmdType = cmd;}
	virtual void		from_pmb(ACE_Message_Block*);
	virtual void		to_pmb(ACE_Message_Block*&);
	virtual void		to_pmb(ACE_Message_Block&);
	virtual  SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int			buf_size();
	bool IsError(){ return RetVal<0; }
	SG_BOOL CheckVersion()
	{
		return 	(SG_NET_CHECKVERSION(CmdVersion));

	}
	CNetCmdHead();
	virtual ~CNetCmdHead(){}
};
typedef CNetCmdHead CNetResponse;
/*class _DATASET_DLL_EXPORT_ CNetResponse
{
public:

	CNetResponse()
	{
		m_error=0;
	}
	
	bool IsError(){ return m_error!=0; }

	ACE_INT32		m_error;
	ACE_CString		m_desc;
	
	virtual void		from_pmb(ACE_Message_Block*);
	virtual void		to_pmb(ACE_Message_Block*&);
	virtual void		to_pmb(ACE_Message_Block&);

protected:

	virtual int			buf_size(){ return sizeof(ACE_UINT32)*2+m_desc.length();}
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=SG_NET_VERSION);
};
*/
///////////////////////////////////////////////////////////////////
class CCommandExcutorBase;
class _DATASET_DLL_EXPORT_ CNetCommand : public CNetCmdHead,public RefCount
{
public:
	//
	CNetCommand()
	{
		m_protocalVer	 = 1;
		m_dwCookie		 = 0;		//被视为无效的cookie
		m_reserver		 = 0;
	//	m_cmd			 = 0;
		m_bExcuted		 = false;
		m_pExcutor		 = NULL;
	}
	//

	virtual void OnCommandStart(bool&bContinue){ bContinue = true;};
	virtual bool OnCommand(ACE_SOCK_Stream*){ return false;}
	virtual void OnCommandComplete(bool bResult,bool bLastCommand){ m_bExcuted = true;};
	
	virtual void OnCancel(){};

//	virtual void		from_pmb(ACE_Message_Block*);
//	virtual void		to_pmb(ACE_Message_Block*&);
//	virtual void		to_pmb(ACE_Message_Block&);
	//

	ACE_UINT32			GetProtocalVer(){ return m_protocalVer;}
	void				SetProtocalVer(ACE_UINT32 pver){ m_protocalVer = pver;}

	ACE_UINT32			GetCookie(){ return m_dwCookie;}
	void				SetCookie(ACE_UINT32 cookie){  m_dwCookie = cookie;}

	virtual CNetResponse*	CreateRespanse(){ return new CNetResponse;}
	//
	CCommandExcutorBase* GetExcutor(){ return m_pExcutor; }
	void				 SetExcutor(CCommandExcutorBase*p){ m_pExcutor = p; }
	//
protected:

	virtual ~CNetCommand()
	{
		if(!m_bExcuted) OnCancel();
	}

	virtual int			buf_size(){ return CNetCmdHead::buf_size()+sizeof(ACE_UINT32)*3;}
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);


	bool				m_bExcuted;
	//ACE_UINT32			m_cmd;
	ACE_UINT32			m_protocalVer;			//交互协议版本
	ACE_UINT32			m_dwCookie;				//cookie
	ACE_UINT32			m_reserver;				//保留

	CCommandExcutorBase* m_pExcutor;
};
typedef CMyAutoPtr<CNetCommand> CNetCommand_AutoPtr;

/////////////////////////////////////////////////////////////
template <class T>
class CMessageT:public ACE_Message_Block
{
public:
	
	CMessageT(T*pHook)
	{
		init(sizeof(T*),MB_USER);
		memcpy(wr_ptr(),&pHook,sizeof(T*));
		wr_ptr(sizeof(T*));
		//
		m_pHook = pHook;
	}

	~CMessageT()
	{
		if(m_pHook) m_pHook->Release();
	}
protected:
	T* m_pHook;
};
//
template <class STREAM>
class CStreamManager
{
public:
	CStreamManager(int nStreams):m_sem(nStreams)
	{
		for(int i=0;i<nStreams;i++)
		{
			STREAM * p= new STREAM;
			m_freeStremas.push_back(p);
		}
	}
	~CStreamManager()
	{
		typename list< STREAM * >::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
			delete p;
		}
		//
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
			delete p;
		}
		//
		m_freeStremas.clear();
		m_busyStremas.clear();
		//
		m_streamLock.release();
	}
	//
	int GetCount()
	{
		m_streamLock.acquire();
		int size = m_freeStremas.size()+m_busyStremas.size();
		m_streamLock.release();
		return size;
	}

	STREAM * Acquire()
	{
		m_sem.acquire();

		m_streamLock.acquire();
		STREAM*pStream=m_freeStremas.front();
		m_freeStremas.pop_front();
		m_busyStremas.push_back(pStream);
		m_streamLock.release();
		//
		return pStream;
	}
	void Release(STREAM*pStream)
	{
		m_streamLock.acquire();
		m_busyStremas.remove(pStream);
		m_freeStremas.push_back(pStream);
		m_streamLock.release();

		m_sem.release();
	}
	void CloseFree()
	{
		typename list<STREAM*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
		}
		m_streamLock.release();
	}
	void CloseBusy()
	{
		typename list<STREAM*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
		}
		m_streamLock.release();
	}
	void CloseAll()
	{
		typename list<STREAM*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
		}
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			STREAM * p = (*itr);
			p->close();
		}
		m_streamLock.release();
	}
	//
	bool Connect(STREAM*pStream)
	{	
		if(pStream->Connect(m_address)==-1) return false;
		return pStream->get_handle()!=ACE_INVALID_HANDLE;
	}

	void SetAddress(ACE_INET_Addr& addr)
	{
		if(m_address!=addr)
		{
			m_address = addr;
			this->CloseAll();
		}
	}

	ACE_INET_Addr& GetAddress(){ return m_address;}
	//
protected:
	//
	list<STREAM *> m_freeStremas;
	list<STREAM *> m_busyStremas;
	//
	ACE_Thread_Mutex  m_streamLock;
	ACE_INET_Addr	  m_address;
	ACE_Thread_Semaphore m_sem;
};
//
class _DATASET_DLL_EXPORT_ CSockStream : public ACE_SOCK_Stream
{
public:
	int Connect(ACE_INET_Addr&addr);
};
//
class _DATASET_DLL_EXPORT_ CSockStream2 : public ACE_SOCK_Stream
{
public:
	int Connect(ACE_INET_Addr&addr);
};

//
class _DATASET_DLL_EXPORT_ CCommandExcutorBase:public ACE_Task<ACE_MT_SYNCH>
{
public:
	virtual ~CCommandExcutorBase(){};
	//
	virtual bool PostCommand(CNetCommand*)=0;
	virtual bool SendCommand(CNetCommand*)=0;
	virtual bool TrySend(ACE_SOCK_Stream*pStream,CNetCommand*,int to=-1)=0;
	//
	virtual bool Cancel()=0;
	virtual bool Start()=0;
	virtual void Stop(CNetCommand*pCallBack=NULL)=0;
	//
	virtual CCommandExcutorBase* SetNextExcutor(CCommandExcutorBase*p);
	virtual CCommandExcutorBase* GetNextExcutor() { return m_pNextExcutor; }
	//
protected:
	CCommandExcutorBase*  m_pNextExcutor;
};

template<class STREAM>
class CCommandExcutor: public CCommandExcutorBase
{
	typedef CMessageT<CNetCommand> CNetCommandMessage; 
public:
	//
	CCommandExcutor(CStreamManager<STREAM>*pStreamManager,bool bKeepAlive=true);
	CCommandExcutor(int nThreads=1,char*lpszAddress=NULL,bool bKeepAlive=true);
	CCommandExcutor(int nThreads,ACE_INET_Addr&addr,bool bKeepAlive=true);
	//
	~CCommandExcutor();
	//
	virtual bool PostCommand(CNetCommand*);
	virtual bool SendCommand(CNetCommand*);
	virtual bool TrySend(ACE_SOCK_Stream*pStream,CNetCommand*,int to=-1);
	//
	virtual bool Start();
	virtual void Stop(CNetCommand*pCallBack=NULL);
	virtual bool Cancel();
	//
	ACE_INET_Addr GetServerAddress();
	void SetServerAddress(ACE_INET_Addr&addr);
	//
	CStreamManager<STREAM>* GetStreamManager(){ return m_pStreamMan;}
	//
protected:
	//重载TASK类
	virtual int  svc();
	virtual int  close (u_long flags = 0);
	virtual int	 putq(ACE_Message_Block *m, ACE_Time_Value *t=0);
	//
	bool TryConnect(ACE_SOCK_Stream*pStream);
	//
	CStreamManager<STREAM> *m_pStreamMan;		//底层SOCK连接管理器
	//
	int					m_nThreadNums;			//线程数
	bool				m_bStop;				//终止所有任务标记
	bool				m_bKeepAlive;			//是否保持连接
	bool				m_bAutoDelete;			//是否自动删除CStreamManager

	ACE_Atomic_Op< ACE_Thread_Mutex , long > m_nTaskNums;
};

class _DATASET_DLL_EXPORT_ CStopCommandExcutor:public ACE_Task<ACE_NULL_SYNCH>
{
public:
	CStopCommandExcutor(CCommandExcutorBase*pExcutor,CNetCommand*pCommmand)
	{
		m_pExcutor = pExcutor;
		m_pCommand = pCommmand;
	}
	~CStopCommandExcutor()
	{
		if(m_pCommand) m_pCommand->Release();
	}
	virtual int  svc()
	{
		if(m_pExcutor) m_pExcutor->Stop();
		return 0;
	}
	virtual int  close (u_long flags = 0)
	{
		if(m_pCommand) m_pCommand->OnCommandComplete(true,true);
		delete this;
		return 0;
	}
protected:
	CCommandExcutorBase * m_pExcutor;
	CNetCommand			* m_pCommand;
};


template<class STREAM>
CCommandExcutor<STREAM>::CCommandExcutor(CStreamManager<STREAM>*pStreamManager,bool bKeepAlive)
{
	m_bStop =false;
	m_bKeepAlive = bKeepAlive;
	//
	if(NULL==pStreamManager) 
	{
		pStreamManager= new CStreamManager<STREAM>(1);
		m_bAutoDelete = true;
	}
	else m_bAutoDelete = false;
	//
	m_pStreamMan =pStreamManager;
	m_nThreadNums = m_pStreamMan->GetCount();
	//
	m_pNextExcutor =NULL;
}

template<class STREAM>
CCommandExcutor<STREAM>::CCommandExcutor(int nThreads,char*lpszAddress,bool bKeepAlive)
{
	m_bStop =false;
	m_bKeepAlive = bKeepAlive;

	if(nThreads<=0) nThreads = 1;
	if(nThreads>20) nThreads = 20;
	m_nThreadNums = nThreads;
	m_pStreamMan = new CStreamManager<STREAM>(nThreads);
	m_bAutoDelete = true;

	m_pNextExcutor =NULL;

	if(lpszAddress)
	{
		ACE_INET_Addr addr;
		addr.set(lpszAddress);
		m_pStreamMan->SetAddress(addr);
	}
}

template<class STREAM>
CCommandExcutor<STREAM>::CCommandExcutor(int nThreads,ACE_INET_Addr&addr,bool bKeepAlive)
{
	m_bStop =false;
	m_bKeepAlive = bKeepAlive;

	if(nThreads<=0) nThreads = 1;
	if(nThreads>20) nThreads = 20;
	m_nThreadNums = nThreads;
	m_pStreamMan = new CStreamManager<STREAM>(nThreads);
	m_bAutoDelete = true;
	//
	m_pNextExcutor =NULL;

	m_pStreamMan->SetAddress(addr);
}

template<class STREAM>
CCommandExcutor<STREAM>:: ~CCommandExcutor()
{
	this->Stop();
	if(m_pStreamMan && m_bAutoDelete)
	{
		delete m_pStreamMan;
		m_pStreamMan=NULL;
	}
}

template<class STREAM>
bool CCommandExcutor<STREAM>::Start()
{
	m_bStop = false;
	//
	if(thr_count()==0)
	{
		activate(THR_NEW_LWP,m_nThreadNums);
		msg_queue()->high_water_mark(SG_DEFAULT_QUEUE_MAX);
		msg_queue()->low_water_mark(SG_DEFAULT_QUEUE_MAX);
		m_nTaskNums=0;
	}
	return true;
}


template<class STREAM>
void CCommandExcutor<STREAM>::Stop(CNetCommand*pCallBack)
{
	if(pCallBack)
	{
		CStopCommandExcutor * p = new CStopCommandExcutor(this,pCallBack);
		p->activate(THR_DETACHED);
	}
	else
	{
		if(false==m_bStop)
		{
			m_bStop = true;
			//释放所有任务
			//msg_queue()->flush();
			this->Cancel();
			msg_queue()->deactivate();
			//关闭所有SOCKET，并等待所有线程退出
			if(m_bAutoDelete) m_pStreamMan->CloseAll();
			this->wait();
		}
	}
}
//
template<class STREAM>
int CCommandExcutor<STREAM>::close (u_long flags)
{
	ACE_DEBUG((LM_DEBUG,"线程[%t]结束!\n",ACE_OS::thr_self()));
	return 0;
}
//
template<class STREAM>
int	 CCommandExcutor<STREAM>::putq(ACE_Message_Block *m, ACE_Time_Value *t)
{
	m_nTaskNums++;
	int n = ACE_Task<ACE_MT_SYNCH>::putq(m,t);
	if(n==-1) m_nTaskNums--;
	return n;
}

template<class STREAM>
bool CCommandExcutor<STREAM>::Cancel()
{
	if(msg_queue()->message_count()==0) return true;
	//
	int n=msg_queue()->flush();
	m_nTaskNums-=n;
	//
	ACE_DEBUG((LM_DEBUG,"***************取消了[%d]个下载任务.....\n",n));
	return true;
}

template<class STREAM>
int CCommandExcutor<STREAM>::svc()
{
	for (;;) 
	{	
		ACE_Message_Block * mblk=NULL;
		if (getq (mblk) == -1) break;
		//
		CNetCommand *pTaskHook = 0;
		memcpy(&pTaskHook,mblk->rd_ptr(),sizeof(CNetCommand*));
		//
		if(m_bStop)
		{
			mblk->release();
			break;
		}
		//
		bool bContinue = true;
		bool bResult = false;

		pTaskHook->SetExcutor( this );
		pTaskHook->OnCommandStart(bContinue);
		if(bContinue)
		{
			STREAM*pStream = m_pStreamMan->Acquire();
			TryConnect(pStream);
			//
			if(m_bStop)
			{
				mblk->release();
				break;
			}
			//
			bResult=pTaskHook->OnCommand(pStream);
			//
			if(m_nTaskNums.value()<=m_nThreadNums)
			{
				if(!m_bKeepAlive) pStream->close();
			}

			m_pStreamMan->Release(pStream);
		}
		//完成了一个TASK
		if(m_bStop)
		{
			mblk->release();
			break;
		}
		//
		m_nTaskNums--;
		//ACE_DEBUG((LM_DEBUG,"-----m_nTaskNums=%d-\n",m_nTaskNums.value()));
		bool bLastCommand = false;
		if(m_nTaskNums.value()==0)
		{
			if(!m_bKeepAlive) m_pStreamMan->CloseFree();
			bLastCommand = true;
		}
		pTaskHook->OnCommandComplete(bResult,bLastCommand);
		mblk->release();
	}
	return 0;
}

template<class STREAM>
bool CCommandExcutor<STREAM>::TryConnect(ACE_SOCK_Stream*p)
{	
	if(p->get_handle()!=ACE_INVALID_HANDLE) return true;
	//
	STREAM * pStream = (STREAM *)p;
	//
	int count=0;
	while(false==m_pStreamMan->Connect(pStream))
	{
		if(m_bStop) break;
		//
		if(++count==5) break;
		ACE_Time_Value tv(0,20*1000);	//20ms
		ACE_OS::sleep(tv);	
		//
		if(m_bStop) break;
	}
	return pStream->get_handle()!=ACE_INVALID_HANDLE;
}

template<class STREAM>
bool CCommandExcutor<STREAM>::TrySend(ACE_SOCK_Stream*pStream,CNetCommand*pCommand,int to)
{
	if(NULL==pStream || NULL==pCommand) return false;
	//
	ACE_Message_Block cmdMsg;
	pCommand->to_pmb(cmdMsg);
	//
	if(write_mb(*pStream,&cmdMsg,to)!=-1) return true;
	//
	pStream->close();

	if(false==TryConnect(pStream)) return false;	
	if(write_mb(*pStream,&cmdMsg,to)==-1) return false;

	return true;
}

template<class STREAM>
bool CCommandExcutor<STREAM>::PostCommand(CNetCommand*pCommandHook)
{
	if(!pCommandHook) return false;
	//
	//如果线程池未启动，则以同步方式执行
	if(thr_count()==0) return this->SendCommand(pCommandHook);

	pCommandHook->SetExcutor(this);
	ACE_Message_Block * pmb = new CNetCommandMessage(pCommandHook);
	if(putq(pmb)==-1)
	{
		pmb->release();
		return false;
	}
	return true;
}
//
template<class STREAM>
bool CCommandExcutor<STREAM>::SendCommand(CNetCommand*pCommandHook)
{
	if(!pCommandHook) return false;
	//
	pCommandHook->SetExcutor(this);
	//
	STREAM * p=m_pStreamMan->Acquire();
	this->TryConnect(p);
	//
	bool ret=pCommandHook->OnCommand(p);
	
	if(!m_bKeepAlive) p->close();
	m_pStreamMan->Release(p);

	pCommandHook->OnCommandComplete(ret,true);
	pCommandHook->Release();
	//
	return ret;
}

template<class STREAM>
void CCommandExcutor<STREAM>::SetServerAddress(ACE_INET_Addr&addr)
{
	m_pStreamMan->SetAddress(addr);
}

template<class STREAM>
ACE_INET_Addr CCommandExcutor<STREAM>::GetServerAddress()
{
	return m_pStreamMan->GetAddress();
}

#endif
