
#ifndef SGMAIL_H
#define SGMAIL_H

#include "sgnp_base.h"	
#include "sys_maildef.h"
#ifndef ACE_WIN32
#include "ace/Shared_Memory_SV.h"
#endif

#define MAILBOX_MAX_CAPACITY					(1024*1024*256)	/*邮箱最大容量*/
#define MAILCOUNTER_SHM							"2007"
#define MAILCOUNTER_SHM_LOCK					"MailCounter_Lock"
#define MAIL_DIR								"syncdata"
#define MAIL_GARBAGE							"garbage"
#define SG_AGENT_UP_DIR							"sgagent_up"
#define SGNPSRV_UP_DIR							"sgnpsrv_up"
#define SGNPSRV_DOWN_DIR						"sgnpsrv_down"


typedef char SG_MAIL_ADDR[16];

/*
 *	功能：信封信息
 *	描述：信封格式-----收信人|发信人邮件|编号
 */
class CSgArchive;
class SGNP_Export MailCover
{
public:

	ACE_CString			to_;
	ACE_CString			from_;
	ACE_UINT32			no_;	
	ACE_UINT32			no_i_;
	ACE_UINT32			from_ip_;
	ACE_UINT32			flag_;
	ACE_UINT32			reserve_;
	//
	MailCover()
	{
		no_	= no_i_=0;
		from_ip_ =0;
		reserve_ =0;
		flag_=m_national;
	}
	int buf_size() { return to_.length()+from_.length()+sizeof(ACE_UINT32)*7; }
	void serialize(CSgArchive&);
};	

/*
 *	功能：SgMail封装了邮件信息
 *	描述：邮件格式-----邮件的信封|邮件正文
 */
class  SGNP_Export SgMail
{
public:
#ifndef SG_MINIBOX_PLAT
	void release() {
		delete this;
	}
#endif
	void			set_cover(MailCover&);
	MailCover&		get_cover();

	void			set_to(const char*to);
	void			set_to(ACE_CString&to);
	ACE_CString&	get_to();

	void			set_from(const char* from); 
	void			set_from(ACE_CString&to);
	ACE_CString&	get_from();

	void			set_no(ACE_UINT32);
	ACE_UINT32		get_no();
	
	void			set_from_ip(ACE_UINT32);
	ACE_UINT32		get_from_ip();

	void			set_flag(ACE_UINT32);
	ACE_UINT32		get_flag();
	
	void			set_text(ACE_CString&text);
	void			set_text(const char*data);
	ACE_CString&	get_text();

	ACE_UINT32		length();
	
	int buf_size() { return cover_.buf_size()+text_.length()+sizeof(ACE_UINT32); }
	void serialize(CSgArchive&);
	
	//
	void to_pmb(ACE_Message_Block*&);
	void from_pmb(ACE_Message_Block*);
private:

	MailCover		cover_;
	ACE_CString		text_;
};

/*
 *	功能：MailBox存储邮件
 *	描述：在多线程环境中使用，需加锁
 */
class SGNP_Export MailBox
{
public:
	/*
	 *	构造与析构
	 */
	MailBox();
	~MailBox();
	/*	
	 *	功能     :  把邮件放进邮件队列的最后,如果邮箱满，抛弃第一个
	 *  参数     :  
	 *	返回值   :	成功返回0，失败－1
	 */
	int put(SgMail*);	
	/*	
	 *	功能     :	取出邮件队列中第一个邮件
	 *  参数     :	void
	 *	返回值   :	出件的邮件,邮箱空时返回0	
	 */
	SgMail * get();
	/*	
	 *	功能     :	查看第一邮件，不取出
	 *  参数     :	void
	 *	返回值   :	邮箱空时返回0
	 */
	SgMail * peek();
	/*	
	 *	功能     :	获得邮件数量
	 *  参数     :	void
	 *	返回值   :	邮件数量
	 */
	ACE_UINT32	size();
	/*	
	 *	功能     :	获得所有邮件的正文总长度
	 *  参数     :	
	 *	返回值   :	
	 */
	ACE_UINT32  total_length();

	/*	
	 *	功能     :	确定本地邮箱是否已满
	 *  参数     :	void
	 *	返回值   :	已满返回1，否则返回0	
	 */
	int			is_full(){ return length_ > MAILBOX_MAX_CAPACITY; }

private:

	MailBox(const MailBox&);
	MailBox& operator=(const MailBox&);

	list<SgMail*>		mlist;
	ACE_Thread_Mutex	lock_;
	ACE_UINT32			length_;
};
/*
 *	功能：注册信息管理类
 *	描述：根据需要决定是否加锁
 */
class  SGNP_Export Reg_Manager
{

public:

	~Reg_Manager();
	/*	
	 *	功能     :	加锁与解锁
	 *  参数     :	void
	 *	返回值   :	成功返回0，失败－1
	 */
	int			lock() { return lock_.acquire(); }
	int			unlock() { return lock_.release(); }
	/*	
	 *	功能     :	查找注册了name邮箱的所有连接
	 *  参数     :	连接的服务对象链表
	 *	返回值   :	成功返回list<Svc_Handler_Base*>*，失败null
	 */	
	list<Svc_Handler_Base*>*	find(ACE_CString&name);
	/*	
	 *	功能     :	注册连接handler的邮箱name
	 *  参数     :	name邮箱名，handler连接服务对象
	 *	返回值   :	失败－1,如果已有其他连接注册过name则返回0，handler第一个注册name返回1
	 */	
	int			reg(ACE_CString&name,Svc_Handler_Base*handler);
	/*	
	 *	功能     :	注消连接handler的name邮箱
	 *  参数     :	
	 *	返回值   :	失败－1,如果还有其他连接没有注销name则返回0，handler最后一个注消name返回1
	 */	
	int			unreg(ACE_CString&name,Svc_Handler_Base*handler);
	/*	
	 *	功能     :	注销连接handler的所有邮箱
	 *  参数     :	handler连接的服务对象,arNames返回handler所有最后注销的的邮箱名
	 *	返回值   :	成功返回0
	 */	
	int			unreg(Svc_Handler_Base*handler,StringArray * arNames=0);
	/*	
	 *	功能     :	获得管理的所有邮箱名
	 *  参数     :	
	 *	返回值   :	成功返回邮箱个数
	 */	
	int			name_array(StringArray&arName);
	int			name_array(Svc_Handler_Base*handler,StringArray&arName);
	/*	
	 *	功能     :	获得内部锁
	 *  参数     :	
	 *	返回值   :	
	 */	
	ACE_Thread_Mutex& get_lock(){ return lock_;	}
	/*	
	 *	功能     :	获得内部邮箱名对连接链表指针的映射
	 *  参数     :	
	 *	返回值   :	
	 */	
	String2Ptr&		get_map() { return str2ptr_; }
private:
	String2Ptr			str2ptr_;	
	ACE_Thread_Mutex	lock_;
};

class SGNP_Export MailCounterBase
{
public:
	//
	virtual ~MailCounterBase(){};
	virtual int open (){ return 0; }
	virtual void close (void){ }
	//
	virtual ACE_UINT32 get_count(){ return 0;}
	virtual void set_seed(ACE_UINT32 c){};
};
//
class MailCounterSimple:public MailCounterBase
{
public:
	MailCounterSimple():count_(1){}
	int open (){ return 1; }
	ACE_UINT32 get_count(){ return count_++;}
	void set_seed(ACE_UINT32 c){ count_=c+1;};
protected:
	ACE_Atomic_Op<ACE_Thread_Mutex,ACE_UINT32> count_;
};
//
class SGNP_Export MailCounterShareMem:public MailCounterBase
{
public:
	//
	MailCounterShareMem (void);
	virtual ~MailCounterShareMem (void);
	//
	int open ();
	void close (void);
	//
	ACE_UINT32 get_count();
	void set_seed(ACE_UINT32 c);
	//
private:
	
#ifdef ACE_WIN32
	ACE_HANDLE 				shm_;
#else
	ACE_Shared_Memory_SV	shm_;
#endif
	//
	ACE_UINT32 *			pcount_;
	ACE_Process_Mutex		lock_;
};
//
class SGNP_Export Persist_MailBox
{
public:
	//
	Persist_MailBox(ACE_TCHAR*dir,bool useshm=true);
	~Persist_MailBox();
	//
	//virtual int set_mail_counter(MailCounterBase*mcb);
	//邮件存盘
	int		save(/*in*/SgMail*pMail);
	int		save(ACE_Message_Block*mb,ACE_UINT32 fileno=0);
	//加载邮件 fn:基础文件名,如: 1.dat
	int		load(const ACE_TCHAR*fn,/*out*/SgMail*pMail);
	int		load(const ACE_TCHAR*fn,ACE_Message_Block&mb);
	//获得所有未发送邮件,mailnames:基础文件名数组
	int		getmails(vector<ACE_TString>&mailnames);
	//移到垃圾邮件目录,fn:基础文件名,如: 1.dat
	int		garbage(const ACE_TCHAR*fn);
	//删除邮件
	int		remove_mail(const ACE_TCHAR*fn);
	//
	MailCounterBase* MailCounter(){ return mcb_; }
	//
protected:
	//
	ACE_UINT32 get_mail_counter_seed();
	ACE_UINT32 get_mail_filename(ACE_TString&fr,ACE_TString&fd,ACE_UINT32 fileno=0);
	//
	ACE_TString				base_dir_;
	MailCounterBase*		mcb_;
};

class SGNP_Bridge_Handler_Base;
class SGNP_Export Mail_Picker : public ACE_Task<ACE_MT_SYNCH>
{
public:
	//
	Mail_Picker(Persist_MailBox*mb,SGNP_Bridge_Handler_Base*bridge,ACE_Lock*mblock);
	//
	virtual int open();
	virtual int close();
	//收到邮件回复的回调
	virtual void on_respanse(const MailCover&cover);
	//
protected:
	//
	virtual int svc();
	//设置要发送邮件的计数
	virtual void set_send_count(ACE_Message_Block*pmb);
	//
	bool process_mail(const ACE_TCHAR*fn);
	ACE_Message_Block* load_mail(const ACE_TCHAR*fn);

	bool send_mail(ACE_Message_Block*pmb,const ACE_TCHAR*fn);
	//
	Persist_MailBox	*					mbs_;
	SGNP_Bridge_Handler_Base*			bridge_;
	ACE_Lock* mblock_;
	//
	ACE_UINT32 send_counter_;		//邮件发送计数器
	ACE_UINT32 cur_mail_count_;		//当前发送邮件的计数
	//	
	bool stop_;		
};
//
SGNP_Export ACE_Message_Block*  to_reg_msg(ACE_CString&name,ACE_UINT32 type);
SGNP_Export ACE_Message_Block*  to_unreg_msg(ACE_CString&name,ACE_UINT32 type);
SGNP_Export ACE_Message_Block*  to_rereg_msg(MailCover&);

#endif



