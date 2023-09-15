
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
	//	ȫ�ֿ��õģ�Ϊĳһ������ķ�������ָ��
	static NPS_Dispatcher * instance( void );
	static void instance( NPS_Dispatcher * );

public:
	//	��ȡ�ʼ��������Ĺ�����
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
		���ܣ���ʼ������ƽ̨�⣬������������ƽ̨�⺯��֮ǰ�������ȵ��ô˺���
		������flag----0,������ACE::init(),��֮����                            
	*/
	int init();
	/*  
		���ܣ�ж������ƽ̨��
	*/
	int fini();	
	/* 
		���ܣ�ע�����估�����ʼ�ʱ����֪ͨ�Ĵ��ں���Ϣ��
		�����ע�����֪ͨ�Ĵ��ں���Ϣ��Ӧ�ÿ����Լ���ѯȡ�ʼ���
		������
		name(in)�D�Dע���������������ƽ̨������������������ڵ㷢�͵��ռ���Ϊ�����������ʼ��ŵ��������У�
		hwnd(in)�D�D���������ʼ�֪ͨ�Ĵ��ھ����
		msgid(in)�D�D���ʼ�֪ͨ��Ϣ�Ķ���ֵ
		flag(in)����������                                                              
	*/
#ifdef ACE_WIN32
	int reg_mailbox(const char*name,HWND hwnd=NULL,int msgid=0,int flag=m_national);
#else
	int reg_mailbox(const char*name,pid_t pid,ACE_UINT32 singal,int flag=m_national);
#endif
	/*
	 *	���ܣ�ע������
	 *  ����ֵ���ɹ�:0��ʧ��:-1 
	 */
	int unreg_mailbox(const char*name);
	/*
	 *	���ܣ���ѯ�����Ƿ����
	 *  ����ֵ:����Ϊ1,������Ϊ0
	 */
	int isreg_mailbox(const char*name);
	/*
	 *	���ܣ���������ƽ̨�����
	 */
	SGNP_EventSlot* set_event_slot(SGNP_EventSlot*);
	/* 
		���ܣ��첽���ʼ���Ӧ�ó�����ʼ��ŵ�������󼴷���
		������
		to(in)�D�D�ռ�����������
		from(in)�D�D��������������
		len(in)�D�D���͵��ʼ��ĳ��ȣ�
		pData(in)�D�D���͵��ʼ������ģ�
		flag(in)�D�D�ʼ����
		����ֵ���ɹ�:0��ʧ��:-1                
	*/
	int send_mail(const char*to,const char*from,int len,const char*pData,int flag,bool bforce);
	int send_mail(SgMail&mail,bool bFore);
	/*
	 *	�����һδȡ�ʼ��ĳ���
	 *	����ֵ���ɹ�---�ʼ����ȣ�ʧ��:-1��������û���ʼ�   
	 */
	int get_mail_len();
	/* 
		���ܣ�Ӧ�ó������ʼ�����ѭ�����ô˺�����ֱ������-1(�ռ�����û���ʼ�)Ϊֹ
		Ӧ�ø�������ڴ�
		������
		to(out)�D�D�ʼ����ռ��ˣ�
		from(out)�D�D�ʼ��ķ����ˣ�
		pData(out)�D�D�ʼ�����
		flag(out)--�ʼ����                                   
	*/
	int  recv_mail(char*to,char*from,char*pData,int&flag);
	int  recv_mail(ACE_CString&to,ACE_CString&from,ACE_CString&data,int&flag);
#ifndef SG_MINIBOX_PLAT
	SgMail*  recv_mail();
#endif
	/* 
		���ܣ���ú�������ʧ�ܵ���Ϣ ��������
		����ֵ��������Ϣ�����ָ��            
	*/
	const char*  last_error();
	/*
	*	��������ƽ̨״̬�Ƿ�����,0----�쳣��1��������
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
	//������SERVER��ַ���������߽ڵ���Ϣ
	int get_linknodes(SG_Addr&des,SG_LINKNODES&lns1,SG_LINKNODES&lns2,SG_LINKNODES&lns3);
	//������AGENT�ĵ�ַ��agemt��Ϣ
	int get_agent_info(SG_Addr&des,vector<SG_AGENT_INFO>arAgentInfo);
	int get_topmost_srv_addr(SG_Addr&des,SG_Addr&topmost_addr);
	
	//�ı�AGENT���ӵ�SGNPSRV
	int change_sgnp_srv(ACE_INET_Addr&addr,int to=30);
	//
	int resolve_all(const char*name,SG_LINKNODES&nodes);
	int resolve_name_direct(ACE_INET_Addr&addr,const char*name,ACE_CString&value);
	//�������-1,Ӧ�ô�Ӧ���ͷŵ���pmb->release()
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
	MRF_REGISTER		= 1 ,	//	ע���ʼ�������
	MRF_UNREGISTER		= 2 ,	//	��ע���ʼ�������
	MRF_TRYREGISTER		= 3 ,	//	����ע���ʼ���������ģ�⣬��������ע��)
};

//==================================================================================================
//	Summary:	
//		��ǰ���ʼ��ַ���ע���ʼ����սӿ�
//==================================================================================================
NPC_API int Mail_Recevier( NPS_Mail_Receiver * Receiver , int Flags , NPS_Dispatcher * Dispatcher = NULL );

//==================================================================================================
//	Summary:	
//		�������ݵ� SG_MB_SYS_EVENT ����
//==================================================================================================
NPC_API int Send_Sys_Event( SGNP * npc , const char * From , const char * Data , int Type = LM_ERROR );

//==================================================================================================
//	Summary:	
//		�����������Ƶİ󶨵�ַ
//==================================================================================================
NPC_API int NPS_Resolve_Name( ACE_CString & Value , const char * Name , SGNP * npc = NULL );
NPC_API const char * NPS_Resolve_Name( const char * Name , SGNP * npc = NULL );

//==================================================================================================
//	Summary:	
//		�����������Ƶİ󶨵�ַ
//==================================================================================================
NPC_API SGNP * NPS_Dispatch_Manager( void );

#endif