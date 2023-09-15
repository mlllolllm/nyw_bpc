
#ifndef _INCLUDE_SGNP_INTERFACE_
#define _INCLUDE_SGNP_INTERFACE_

#include "sgnp_export.h"
#include "sgmail.h"
#include "sgnp_name.h"
#include "sgnp_event.h"
#include "sgnp_node.h"

#ifdef ACE_WIN32
#  define  WM_SGNP		(WM_USER+555)
#endif	

#ifdef _USE_CPP_
#  undef SGNP_Export
#  define SGNP_Export
#endif
//success : 0
//fail : -1
class SGNPC;
class SGNP;
class NPC_API SGNPManager
{
protected:
	//
	SGNPManager();
	~SGNPManager();
	//
	std::vector<SGNP*> sgnps_;
public:
	//
	static SGNPManager* instance();
	static void  release();
	//
	SGNP* create(ACE_CString strAddress);
	SGNP* create(ACE_INET_Addr&address);
	SGNP* find(ACE_CString strAddress);
	SGNP* find(ACE_INET_Addr&address);
	void destroy(SGNP*);

	SGNP* agent_sgnp();
	SGNP* default_sgnp();
	//
private:
	static SGNPManager * instance_;
};

struct NPS_Mail_Receiver
{
	virtual int Process( SgMail * Mail ) = 0;
};

class NPC_API NPS_Dispatcher : public ACE_Task< ACE_MT_SYNCH >
{
public:
	int Unregister( NPS_Mail_Receiver * Receiver );
	int Register( NPS_Mail_Receiver * Receiver );

public:
	//	全局可用的，为某一个具体的分派器的指针
	static NPS_Dispatcher * instance( void );
	static void instance( NPS_Dispatcher * );

public:
	//	获取邮件分派器的管理者
	SGNP * Manager( void );

protected:
	NPS_Dispatcher( SGNP * Manager );
	~NPS_Dispatcher( );

protected:
	int stop( bool Wait = true );
	int process( SgMail * );
	int svc( );

protected:
	typedef NPS_Mail_Receiver * Receiver_Ptr;
	typedef std::vector< Receiver_Ptr > ReceiverArray;
	typedef ReceiverArray::iterator Receiver_Itr;
	ACE_Thread_Mutex mutex_lock_ ;
	ReceiverArray receivers_ ;
	
private:
	void operator = ( const NPS_Dispatcher & );
	NPS_Dispatcher( const NPS_Dispatcher & );

private:
	friend class SGNP ;
	SGNP * Manager_ ;
	bool Stop_ ;
};

class NPC_API SGNP
{
	friend class SGNPManager;
	SGNP();
	virtual ~SGNP();
public:
	
	static SGNP* instance();
	static void  release();

	ACE_INET_Addr get_address();
	//
public:
	
	/*	
		功能：初始化网络平台库，调用其他网络平台库函数之前必须首先调用此函数
		参数：flag----0,不调用ACE::init(),反之调用                            
	*/
	int init();
	/*  
		功能：卸载网络平台库
	*/
	int fini();	
	/* 
		功能：注册邮箱及有新邮件时可以通知的窗口和消息。
		如果不注册接收通知的窗口和消息，应用可以自己轮询取邮件。
		参数：
		name(in)――注册的邮箱名，网络平台会把网络上所有其他节点发送的收件人为此邮箱名的邮件放到此邮箱中；
		hwnd(in)――接收新来邮件通知的窗口句柄；
		msgid(in)――新邮件通知消息的定义值
		flag(in)－－邮箱标记                                                              
	*/
#ifdef ACE_WIN32
	int reg_mailbox(const char*name,HWND hwnd=NULL,int msgid=0,int flag=m_national);
#else
	int reg_mailbox(const char*name,pid_t pid,ACE_UINT32 singal,int flag=m_national);
#endif
	/*
	 *	功能：注销邮箱
	 *  返回值：成功:0，失败:-1 
	 */
	int unreg_mailbox(const char*name);
	/*
	 *	功能：查询邮箱是否存在
	 *  返回值:存在为1,不存在为0
	 */
	int isreg_mailbox(const char*name);
	/*
	 *	功能：设置网络平台事项槽
	 */
	SGNP_EventSlot* set_event_slot(SGNP_EventSlot*);
	/* 
		功能：异步发邮件，应用程序把邮件放到发件箱后即返回
		参数：
		to(in)――收件人邮箱名，
		from(in)――发件人邮箱名，
		len(in)――发送的邮件的长度，
		pData(in)――发送的邮件的正文，
		flag(in)――邮件标记
		返回值：成功:0，失败:-1                
	*/
	int send_mail(const char*to,const char*from,int len,const char*pData,int flag,bool bforce);
	int send_mail(SgMail&mail,bool bFore);
	/*
	 *	获得下一未取邮件的长度
	 *	返回值：成功---邮件长度，失败:-1，邮箱中没有邮件   
	 */
	int get_mail_len();
	/* 
		功能：应用程序收邮件，可循环调用此函数，直至返回-1(收件箱中没有邮件)为止
		应用负责分配内存
		参数：
		to(out)――邮件的收件人，
		from(out)――邮件的发件人，
		pData(out)――邮件正文
		flag(out)--邮件标记                                   
	*/
	int  recv_mail(char*to,char*from,char*pData,int&flag);
	int  recv_mail(ACE_CString&to,ACE_CString&from,ACE_CString&data,int&flag);
#ifndef SG_MINIBOX_PLAT
	SgMail*  recv_mail();
#endif
	/* 
		功能：获得函数调用失败的信息 参数：无
		返回值：错误信息缓冲的指针            
	*/
	const char*  last_error();
	/*
	*	测试网络平台状态是否正常,0----异常，1－－正常
	*/
	int is_net_ok();
	/*
	 *	
	 */
	int bind_name(const char* name,const char* value);
	int bind_mutex_name(const char* name,const char* value);
	int unbind_name(const char* name);
	int unbind_mutex_name(const char* name,const char*value);
	int resolve_name(const char*name,ACE_CString&value);
	int rebind_all();
	//
	int send_cmd(SG_Addr&des,MONITOR_CMD cmd,ACE_CString&data);
	int send_cmd(SG_Addr&des,MONITOR_CMD cmd,const char*data=0,int len=0);
	//
	//参数：SERVER地址，所有在线节点信息
	int get_linknodes(SG_Addr&des,SG_LINKNODES&lns1,SG_LINKNODES&lns2,SG_LINKNODES&lns3);
	//参数：AGENT的地址，agemt信息
	int get_agent_info(SG_Addr&des,vector<SG_AGENT_INFO>arAgentInfo);
	int get_topmost_srv_addr(SG_Addr&des,SG_Addr&topmost_addr);
	
	//改变AGENT连接的SGNPSRV
	int change_sgnp_srv(ACE_INET_Addr&addr,int to=30);
	//
	int resolve_all(const char*name,SG_LINKNODES&nodes);
	int resolve_name_direct(ACE_INET_Addr&addr,const char*name,ACE_CString&value);
	//如果返回-1,应用处应该释放调用pmb->release()
	int post_proc_info_to_server(ACE_Message_Block*pmb);

public:
	//
	NPS_Dispatcher * dispatcher( ) const;
	int create_dispatcher( );

protected:
	//
	friend class NPS_Dispatcher ;
	SgMail * receive( ); 

	int check_error( );
	
protected:
	NPS_Dispatcher * dispatcher_ ;
	ACE_CString * err_text_;
	SGNPC		* sgnpc_;
	//
	static SGNP * instance_;
};

//==================================================================================================
enum NPC_MAIL_RECEIVER_FLAGS_
{
	MRF_REGISTER		= 1 ,	//	注册邮件接收器
	MRF_UNREGISTER		= 2 ,	//	反注册邮件接收器
	MRF_TRYREGISTER		= 3 ,	//	尝试注册邮件接收器（模拟，并不真正注册)
};

//==================================================================================================
//	Summary:	
//		向当前的邮件分发器注册邮件接收接口
//==================================================================================================
NPC_API int Mail_Recevier( NPS_Mail_Receiver * Receiver , int Flags , NPS_Dispatcher * Dispatcher = NULL );

//==================================================================================================
//	Summary:	
//		发送数据到 SG_MB_SYS_EVENT 邮箱
//==================================================================================================
NPC_API int Send_Sys_Event( SGNP * npc , const char * From , const char * Data , int Type = LM_ERROR );

//==================================================================================================
//	Summary:	
//		检索给定名称的绑定地址
//==================================================================================================
NPC_API int NPS_Resolve_Name( ACE_CString & Value , const char * Name , SGNP * npc = NULL );
NPC_API const char * NPS_Resolve_Name( const char * Name , SGNP * npc = NULL );

//==================================================================================================
//	Summary:	
//		检索给定名称的绑定地址
//==================================================================================================
NPC_API SGNP * NPS_Dispatch_Manager( void );

#endif