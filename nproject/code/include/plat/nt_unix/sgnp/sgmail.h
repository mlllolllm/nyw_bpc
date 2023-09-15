
#ifndef SGMAIL_H
#define SGMAIL_H

#include "sgnp_base.h"	
#include "sys_maildef.h"
#ifndef ACE_WIN32
#include "ace/Shared_Memory_SV.h"
#endif

#define MAILBOX_MAX_CAPACITY					(1024*1024*256)	/*�����������*/
#define MAILCOUNTER_SHM							"2007"
#define MAILCOUNTER_SHM_LOCK					"MailCounter_Lock"
#define MAIL_DIR								"syncdata"
#define MAIL_GARBAGE							"garbage"
#define SG_AGENT_UP_DIR							"sgagent_up"
#define SGNPSRV_UP_DIR							"sgnpsrv_up"
#define SGNPSRV_DOWN_DIR						"sgnpsrv_down"


typedef char SG_MAIL_ADDR[16];

/*
 *	���ܣ��ŷ���Ϣ
 *	�������ŷ��ʽ-----������|�������ʼ�|���
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
 *	���ܣ�SgMail��װ���ʼ���Ϣ
 *	�������ʼ���ʽ-----�ʼ����ŷ�|�ʼ�����
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
 *	���ܣ�MailBox�洢�ʼ�
 *	�������ڶ��̻߳�����ʹ�ã������
 */
class SGNP_Export MailBox
{
public:
	/*
	 *	����������
	 */
	MailBox();
	~MailBox();
	/*	
	 *	����     :  ���ʼ��Ž��ʼ����е����,�����������������һ��
	 *  ����     :  
	 *	����ֵ   :	�ɹ�����0��ʧ�ܣ�1
	 */
	int put(SgMail*);	
	/*	
	 *	����     :	ȡ���ʼ������е�һ���ʼ�
	 *  ����     :	void
	 *	����ֵ   :	�������ʼ�,�����ʱ����0	
	 */
	SgMail * get();
	/*	
	 *	����     :	�鿴��һ�ʼ�����ȡ��
	 *  ����     :	void
	 *	����ֵ   :	�����ʱ����0
	 */
	SgMail * peek();
	/*	
	 *	����     :	����ʼ�����
	 *  ����     :	void
	 *	����ֵ   :	�ʼ�����
	 */
	ACE_UINT32	size();
	/*	
	 *	����     :	��������ʼ��������ܳ���
	 *  ����     :	
	 *	����ֵ   :	
	 */
	ACE_UINT32  total_length();

	/*	
	 *	����     :	ȷ�����������Ƿ�����
	 *  ����     :	void
	 *	����ֵ   :	��������1�����򷵻�0	
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
 *	���ܣ�ע����Ϣ������
 *	������������Ҫ�����Ƿ����
 */
class  SGNP_Export Reg_Manager
{

public:

	~Reg_Manager();
	/*	
	 *	����     :	���������
	 *  ����     :	void
	 *	����ֵ   :	�ɹ�����0��ʧ�ܣ�1
	 */
	int			lock() { return lock_.acquire(); }
	int			unlock() { return lock_.release(); }
	/*	
	 *	����     :	����ע����name�������������
	 *  ����     :	���ӵķ����������
	 *	����ֵ   :	�ɹ�����list<Svc_Handler_Base*>*��ʧ��null
	 */	
	list<Svc_Handler_Base*>*	find(ACE_CString&name);
	/*	
	 *	����     :	ע������handler������name
	 *  ����     :	name��������handler���ӷ������
	 *	����ֵ   :	ʧ�ܣ�1,���������������ע���name�򷵻�0��handler��һ��ע��name����1
	 */	
	int			reg(ACE_CString&name,Svc_Handler_Base*handler);
	/*	
	 *	����     :	ע������handler��name����
	 *  ����     :	
	 *	����ֵ   :	ʧ�ܣ�1,���������������û��ע��name�򷵻�0��handler���һ��ע��name����1
	 */	
	int			unreg(ACE_CString&name,Svc_Handler_Base*handler);
	/*	
	 *	����     :	ע������handler����������
	 *  ����     :	handler���ӵķ������,arNames����handler�������ע���ĵ�������
	 *	����ֵ   :	�ɹ�����0
	 */	
	int			unreg(Svc_Handler_Base*handler,StringArray * arNames=0);
	/*	
	 *	����     :	��ù��������������
	 *  ����     :	
	 *	����ֵ   :	�ɹ������������
	 */	
	int			name_array(StringArray&arName);
	int			name_array(Svc_Handler_Base*handler,StringArray&arName);
	/*	
	 *	����     :	����ڲ���
	 *  ����     :	
	 *	����ֵ   :	
	 */	
	ACE_Thread_Mutex& get_lock(){ return lock_;	}
	/*	
	 *	����     :	����ڲ�����������������ָ���ӳ��
	 *  ����     :	
	 *	����ֵ   :	
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
	//�ʼ�����
	int		save(/*in*/SgMail*pMail);
	int		save(ACE_Message_Block*mb,ACE_UINT32 fileno=0);
	//�����ʼ� fn:�����ļ���,��: 1.dat
	int		load(const ACE_TCHAR*fn,/*out*/SgMail*pMail);
	int		load(const ACE_TCHAR*fn,ACE_Message_Block&mb);
	//�������δ�����ʼ�,mailnames:�����ļ�������
	int		getmails(vector<ACE_TString>&mailnames);
	//�Ƶ������ʼ�Ŀ¼,fn:�����ļ���,��: 1.dat
	int		garbage(const ACE_TCHAR*fn);
	//ɾ���ʼ�
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
	//�յ��ʼ��ظ��Ļص�
	virtual void on_respanse(const MailCover&cover);
	//
protected:
	//
	virtual int svc();
	//����Ҫ�����ʼ��ļ���
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
	ACE_UINT32 send_counter_;		//�ʼ����ͼ�����
	ACE_UINT32 cur_mail_count_;		//��ǰ�����ʼ��ļ���
	//	
	bool stop_;		
};
//
SGNP_Export ACE_Message_Block*  to_reg_msg(ACE_CString&name,ACE_UINT32 type);
SGNP_Export ACE_Message_Block*  to_unreg_msg(ACE_CString&name,ACE_UINT32 type);
SGNP_Export ACE_Message_Block*  to_rereg_msg(MailCover&);

#endif



