//sgnp_def.h
/*******************************************************************************
*******************************************************************************/
#ifndef	SGNPDEF_H
#define	SGNPDEF_H
//#include "sys_moduledef.h"

#define  SG_DEFAULT_SGNP_SRV_PORT		6100			/*name srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGNP_AGENT_PORT		6101
#define  SG_DEFAULT_MQS_PORT			6102			/*��Ϣ����ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_FPS_SRV_PORT		6103			/*rdb srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_MONITOR_AGENT_PORT	6104			/*monitor agentȱʡ�˿ڶ���*/
#define  SG_DEFAULT_GDB_SRV_PORT		6105			/*gdb srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_BKG_SRV_PORT		6106			/*bkg srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_LITTLE_SRV_PORT		6107			/*little srvȱʡ�˿ڶ��� �򵥷���*/
#define  SG_DEFAULT_EP_SRV_PORT			6108			/*ep srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_LOGMSGSRV_PORT		6109			/*��־��Ϣ����ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_DEBUG_CENTER_PORT	6110			/*monitor center UDP�����ܶ˿ڶ���*/
#define  SG_DEFAULT_PUB_SRV_PORT		6111			/*pub srvȱʡ�˿ڶ���*/

#define  SG_DEFAULT_RDP_RECV_PORT		6112			/*����ʵʱ�����������ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_RDP_SEND_PORT		6113			/*����ʵʱ����������ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_HSDASRV_PORT		6114			/*ʵʱ����ʵʱ���ݷ���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_TSDASRV_PORT		6115			/*ʵʱ������ʷ���ݷ���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_RDP_PROCSRV_PORT	6116			/*IDP���̼��ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_EVTSRV_PORT			6117			/*�·���˿�*/
#define  SG_DEFAULT_SGDPP_SRV_PORT		6118			/*���ݿ�ͨ��ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGDPS_SRV_PORT		5700			/*���ݴ���ͨ��ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGCOMM_SRV_PORT		5701			/*ǰ�÷���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGREP_SRV_PORT		6119			/*���Ʒ���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGIDMAP_PORT		6121			/*�豸ID��Ӧ����˿ڶ���*/
#define  SG_DEFAULT_SGCPS_PORT			6120			/*��ƽ̨Ӧ�÷���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_SGCPS_REP_PORT		6122			/*��ƽ̨Ӧ�÷���Ϊ���Ʒ������Ľ���ȱʡ�˿ڶ���*/
#define  SG_DEFAULT_XSCAL_SRV_PORT		6123			/*������� srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_TOPO_SRV_PORT		6124			/*���˷��� srvȱʡ�˿ڶ���*/
#define  SG_DEFAULT_MINIBOXMAN_PORT		5702			/*΢���ӹ������˿�*/
#define  SG_DEFAULT_GAPTERMSEND_PORT	6998			/*��բ���ͷ���˿�*/
#define  SG_DEFAULT_GAPCOMM_PORT		6999			/*��բͨѶ����˿�*/


#define  SG_DEFAULT_TGDB_SRV_PORT_START	6125			/*ʱ̬�ռ�����ȱʡ��ʼ�˿ڶ���*/
#define  SG_DEFAULT_TGDB_SRV_PORT_END	6140			/*ʱ̬�ռ�����ȱʡ��ֹ�˿ڶ���*/

#define SG_DEFAULT_SGUBS_SRV_PORT       6150            /*���಻ƽ���Ż�����˿ڶ���*/

//5801~5899 dps
#define  SG_DEFAULT_SGDPS_SRV_PORT_BAK		5801			/*���ݴ���ͨ��ȱʡ�˿ڶ���*/
//5901~5999 MiniBoxMan
#define  SG_DEFAULT_MINIBOXMAN_PORT_BAK		5901			/*΢���ӹ������˿�*/

//
#define  SG_DEFAULT_QUEUE_MAX		(1024*1024*16)	/*����ȱʡ��󻺴�16M*/
#define	 SG_HEARTBEAT_CLIENT		10				/*�ͻ����������--10 seconds*/
#define  SG_HEARTBEAT_SRV			15				/*������������--15 seconds*/	
//
#define  SG_UDP_BUF_LEN				1024			//1k
/*��Ϣ���Ͷ���*/
enum SG_MT_DEF
{
	SG_MT_STOP = 0xFFFF,
	SG_MT_CHECK = 0xFFFE,		//��ⱨ��
	/*ϵͳ��Ϣ���Ͷ���*/
	SG_SYS_STATUS = 0x01,
	SG_SYS_HEARTBEAT = 0x02,		/*����*/
	//
	SG_SYS_CMD_POST = 0x03,		/*ϵͳ����*/
	SG_SYS_CMD_RECV = 0x04,
	//
	SG_SYS_EVENT_POST = 0x05,		/*ϵͳ����*/
	SG_SYS_EVENT_RECV = 0x06,
	//other
	SG_SYS_LINKTYPE = 0x07,		/*������·����*/
	SG_SYS_TIME = 0x08,		/*���ϵͳʱ��*/
	SG_SYS_TIME_REPLY = 0x09,		/*���ϵͳʱ��ظ�*/
	/*�ʼ���Ϣ���Ͷ���*/
	SG_MAIL_POST = 0x10,		/*����*/
	SG_MAIL_RECV = 0x11,		/*����*/
	SG_MAIL_REG = 0x12,		/*ע������*/
	SG_MAIL_UNREG = 0x13,		/*ע������*/
	SG_MAIL_REREG = 0x14,		/*����ע������*/
	SG_MAIL_COUNT = 0x15,		/*�ʼ�����*/
	SG_MAIL_REGET = 0x16,		/*�������ñ�������*/
	SG_MAIL_REGET_EX = 0x17,		/*Ϊ�˼�����ϵͳ������,�������ñ���������չ*/
	//
	SG_MAIL_POST2 = 0x20,	//�践����Ϣ����ȷ��
	SG_MAIL_COUNT2 = 0x21,
	//
	SG_PROC_START = 0x30,		/*��������*/
	SG_PROC_EXIT = 0x31,		/*�����˳�*/
	//
	SG_CHANGE_SRV = 0x40,		/*�ı�agent�еķ���ָ��*/
	//
	SG_NAME_BIND = 0x50,		/*������*/
	SG_NAME_BIND_REPLY = 0x51,		/*�����ֻظ�*/
	SG_NAME_UNBIND = 0x52,		/*�����*/
	SG_NAME_RESOLVE = 0x53,		/*��������*/
	SG_NAME_RESOLVE_REPLY = 0x54,		/*�������ֻظ�*/
	SG_NAME_REBIND = 0x55,		/*���°�*/
	/*ʵʱ����Ϣ���Ͷ���*/
	SG_MT_ALLDATA = 0x100,		/*ȫ��������*/
	SG_MT_PARTDATA = 0x101,		/*������������*/
	SG_MT_UPDATE = 0x102,		/*���ݸ���*/
	SG_MT_OPEN_STREAM = 0x103,		/*����������*/
	SG_MT_CLOSE_STREAM = 0x104,		/*�ر�������*/
	SG_MT_STREAM = 0x105,		/*���������ݣ��仯���ݣ�������Ϣ,�ɶ�ʱ������*/
	SG_MT_STREAM_INDEX = 0x106,		/*����������*/
	SG_MT_MODIFY_INDEX = 0x107,		/*�޸�������*/
	SG_MT_UPDATE_FLAG = 0x108,		/*�������޸ı��*/
	SG_MT_DESC = 0x109,		/*������ṹ*/

	//SG_DATA_POST					=0x120,		/*Ͷ�����ݰ�*/
	//SG_DATA_RECV					=0x121,		/*�������ݰ�*/
	SG_SYS_HEARTBEAT_EX = 0x200,		/*Ϊ�˼�����ϵͳ������*/
	SG_SYS_LINKTYPE_EX = 0x201,		/*��ԭ�ṹ����������ڵ�ID��Ϣ*/

	SG_NODE_STATS = 0x300,		/*�ڵ�����ͳ������*/
	SG_PROC_STATS = 0x301,		/*��������ͳ������*/
	SG_NODE_EVENT = 0x302,		/*�ڵ�����*/
};

//������Ϣ������
enum DEBUG_LEVEL
{
	DEBUG_INVALID = -1,					//��Ч���Լ���

	DEBUG_NONE = 0,					//�����������Ϣ
	DEBUG_STARTUP = 0100,					//LM_STARTUP,����������Ϣ
	DEBUG_SHUTDOWN = 01,					//LM_SHUTDOWN,���������˳���Ϣ
	DEBUG_LM_TRACE = 02,					//LM_TRACE,�������ø���
	DEBUG_NORMAL = 04,					//LM_DEBUG,	���õ��Լ���
	DEBUG_WARNING = 040,					//LM_WARNING,/����
	DEBUG_ERROR = 0200,					//LM_ERROR,����
};

/*��������*/
enum  MONITOR_CMD
{
	CMD_INVALID = 0,			//do nothing

	/*���̿���*/
	CMD_RESET0 = 1,			//reset�������Լ����������)
	CMD_RESET1 = 2,			//kill+startup
	CMD_RESET2 = 3,			//quit+startup
	CMD_STARTUP = 4,			//��������
	CMD_KILL = 5,			//ɱ�����̣�������
	CMD_QUIT = 6,			//ʹ���������˳�
	CMD_PROCESS = 7,			//������Ϣ
	CMD_PROCESS_GUARD = 8,			//�ػ�����

	/*ϵͳ���*/
	CMD_REBOOT = 20,			//reboot����
	CMD_SHUTDOWN = 21,			//�ػ�
	CMD_SCHEDULE_REBOOT = 22,			//��ʱreboot����
	CMD_SCHEDULE_SHUTDOWN = 23,			//��ʱ�ػ�
	CMD_SCREEN = 24,			//����
	CMD_SCREEN_TIMER = 25,			//���ڿ���
	CMD_HOST_INFO = 26,			//���������Ϣ
	CMD_GET_TIME = 27,			//�������ʱ��
	CMD_SET_TIME = 28,			//��������ʱ��

	/*�������*/
	CMD_LOAD_SVC = 40,			//���ط���ģ��
	CMD_REMOVE_SVC = 41,			//ж�ط���ģ��
	CMD_REPLACE_SVC = 42,			//�滻����ģ��
	CMD_RECONFIGURE = 43,			//�������÷��������ļ�
	CMD_REPLACE_MONITOR = 44,			//�滻��ش���ģ��
	/*�������*/
	CMD_DEBUG_LEVEL = 50,			//���õ��Լ���
	CMD_DEBUG_OPT_UDP = 51,			//�������ѡ��--UDP��ʽ
	CMD_DEBUG_OPT_FILE = 52,			//�������ѡ��--FILE��ʽ
	CMD_DEBUG_OPT_IO = 53,			//�������ѡ��--IO��ʽ
	CMD_DEBUG_OPT_SPY = 54,			//�������ѡ��--DebugSpy��ʽ
	CMD_DEBUG_OPT_NONE = 55,			//�������ѡ��--ֹͣ�κ����
	/*�ļ����*/
	CMD_UPLOAD_FILE = 60,			//�ϴ��ļ����ڵ㣭>���ģ�
	CMD_DOWNLAOD_FILE = 61,			//�´��ļ������ģ�>�ڵ�)
	CMD_REMOVE_FILE = 62,			//ɾ���ļ�
	CMD_RENAME_FILE = 63,			//�������ļ�
	CMD_LCF_FILE = 64,			//���LCF�ļ���Ϣ
	//
	CMD_ONLINE_HOSTS = 100,			//���߽ڵ�
	CMD_TOPMOST_SRV = 101,			//������ϼ�SRV��ַ
	CMD_AGENT_INFO = 102,			//
	//
	CMD_BACK_MAIN_SWITCH = 200,			//�����л�
	//
	CMD_MAXID = 500

};
enum MONITOR_EVENT
{
	EVENT_BASEID = CMD_MAXID,
	//sgnp server ����
	EVENT_LINK = EVENT_BASEID + 1,			//�ɹ�����sgnpsrv
	EVENT_UNLINK = EVENT_BASEID + 2,			//��agent���¼�sgnpsrv���ӶϿ�
	//sgnp server��agent����
	EVENT_BRIDGE_BUILD = EVENT_BASEID + 3,			//build bridge
	EVENT_BRIDGE_BREAK = EVENT_BASEID + 4,			//bridge break
	EVENT_BRIDGE_HEARTBEAT = EVENT_BASEID + 5,			//bridge heartbeat
	EVENT_BRIDGE_PUTQ = EVENT_BASEID + 6,			//put message to bridge's message fail
	EVENT_MAIL_RESET = EVENT_BASEID + 7,			//�ʼ���������
	EVENT_MAIL_LOST = EVENT_BASEID + 8,			//�ʼ���ʧ
	//agent����
	EVENT_PROG_START = EVENT_BASEID + 10,			//������������
	EVENT_PROG_QUIT = EVENT_BASEID + 11,			//�����˳�����
	EVENT_SGNP_SRV_CHANGE = EVENT_BASEID + 12,			//agent���ӵ�SGNPSRV��ַ�ı�����
	EVENT_SGNP_SRV_CHANGE_OK = EVENT_BASEID + 13,			//SGNPSRV��ַ�ı�������ɹ�����
	EVENT_CHUNNEL_STATUS = EVENT_BASEID + 15,			//ͨ��״̬
	//���ʼ��������������¼�,����ƽ̨������������Ĭ�ϴ�������ǰ�FIFOɾ���ʼ���ֱ���������,
	//��Ӧ�ò��붪ʧ�κ�һ���ʼ�������Ҫ���������
	EVENT_MAILBOX_FULL = EVENT_BASEID + 30,
	//gdbsrv����
	//rdbsrv����
};

/*��·���Ͷ���*/
enum LINK_TYPE
{
	LINK_DATA = 0,	//������·
	LINK_BRIDGE = 1,	//�Ž���·
//	LINK_MONITOR	=2,	//�����·
};
// --- �ʼ���ʶ
enum MAIL_FLAG
{
	f_none = 0,
	f_local = 1,
	f_national = 2,
	f_international = 4,
	//
	f_notbakup = 8,
	//
	m_local = f_local,
	m_national = f_local | f_national,
	m_international = f_local | f_national | f_international
};
enum SYS_NOTIFY
{
	NOTIFY_NONE = -1,	//nothing
	//
	SYS_MSG = 10,	//֪ͨ��Ϣ
	SYS_LOCK = 11,
	SYS_UNLOCK = 12,
	SYS_START_EP = 31,	//��ʼ�쳣������
	SYS_END_EP = 32,	//�����쳣������
	SYS_GDB_START = 50,	//�ռ���������
	SYS_GDB_INIT = 51,	//ͼ���������¼���
};
//
/*����Ŷ���*/
#define E_MAIL_LINK_SRV			(-100)		/*mail agent can't link to mail server*/
#define E_MAIL_LINK_AGENT		(-101)		/*mail client can't link to local mail agent*/
#define E_MAIL_FIND_SRV			(-102)		/*can't find mail server addr*/

#define E_RDB_FIND_SRV			(-200)		/*can't find rdb server addr*/

#define E_NAMING_CONTEXT		(-300)		/*ACE_Naming_Context object does not exists*/
#define E_OPEN_NAME_SRV			(-301)		/*open name srv failed*/
#define E_BIND_NAME				(-302)		/*bind name failed*/
#define E_RESOLVE_NAME			(-303)		/*resolve name failed*/

#endif
