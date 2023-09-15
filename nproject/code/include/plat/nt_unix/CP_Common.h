//==================================================================================================
//	Summary:
//		Cloud Platform Common Define Header
//
//	Comment:
//		<1>	
//
//	---------------------------------------------------------------------------------------------
//	Author:  yanh,shaoy,zhangyy,liuh,wzk           Version: 1.00.000              Date: 2012-01-06
//==================================================================================================

#ifndef __CP_COMMON_HEADER__
#define __CP_COMMON_HEADER__

#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#  pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

//==================================================================================================
//�Ʒ�����ඨ��
enum CP_SvcClass
{
	CP_DPP_SVC = 1,			//���ݿ����
	CP_HDA_SVC = 2,			//ʵʱ�����
	CP_TSDA_SVC = 3,			//��ʷ�����
	CP_DPS_SVC = 4,			//���ݴ������
	CP_GDB_SVC = 5,			//ͼ�η���
	CP_FILE_SVC = 6,			//�ļ�����
	CP_NP_AGENT = 7,			//����ƽ̨����
	CP_CPS_SVC = 8,		    //��ƽ̨Ӧ�÷���
	CP_NPS = 9,			//����ƽ̨����
	CP_IDMAP_SVC = 12 		//��Դƥ�����
};
//==================================================================================================

//==================================================================================================
//�Ʒ���ڵ���ඨ��
enum CP_NodeClass
{
	CP_NORMAL_NODE = 1,			//�ƴ���ڵ�
	CP_SCD_NODE = 2,			//�Ʋɼ��ڵ�	
	CP_SCDBAK_NODE = 3, 			//�Ʋɼ����ݽڵ�	
	CP_COMM_TERM_NODE = 4, 			//��ͨѶ�ն˽ڵ�	
};
//�Ʒ���ڵ�״̬����
enum CP_NodeStatus
{
	CP_NODESTATUS_ERROR = 0,			//�쳣״̬
	CP_NODESTATUS_NORMAL = 1,			//����״̬
};
//�Ʒ���ڵ㱸��������״̬����
enum CP_BakBlueBoxStatus
{
	CP_BAKBLUEBOX_STATUS_BAK = 0,			//����״̬
											//	CP_BAKBLUEBOX_STATUS_WAIT		=1,			//�ȴ���Ϊ����״̬
	CP_BAKBLUEBOX_STATUS_MAIN = 1,			//����״̬
};

//==================================================================================================
//�Ʒ������ݵ�Ԫά��ģʽ����
enum CP_CellMode
{
	CP_CELLMODE_NONE = 0,			//��ά��
	CP_CELLMODE_MANUAL = 1,			//�ֶ�ά������ʵʱ�����
	CP_CELLMODE_AUTO = 2 			//�Զ�ά��(����ʷ�����
};

//==================================================================================================

//==================================================================================================
//��ƽ̨��ϵ���������
#define TBL_CP_CENTER				"CP_CENTER_PARA"		//��ƽ̨�������Ĳ�����
#define TBL_CP_PHYNODE_PARA			"CP_PHYNODE_PARA"		//��ƽ̨����ڵ������
#define TBL_CP_PHYNODE				"CP_PHYNODE"			//
#define TBL_CP_DISKPOOL_PARA		"CP_DISKPOOL_PARA"		//�洢��Դ�ز�����
#define TBL_CP_LOGICDISK_STAT		"CP_LOGICDISK_STAT"		//��ƽ̨�߼��������й���ͳ�Ʊ�
#define TBL_CP_WORKSPACE			"CP_WORKSPACE"			//��ƽ̨�����ռ��

//#define TBL_CP_SRVCLASS				"CP_SRVCLASS"			//��ƽ̨��������
//#define TBL_CP_SRVCONFIG			"CP_SRVCONFIG"			//��ƽ̨�������ñ�
//#define TBL_CP_LOGICCELL_TYPE		"CP_LOGICCELLTYPE"		//��ƽ̨�߼����ݵ�Ԫ�����
//#define TBL_CP_SRVTYPE_INFO			"CP_SRVTYPE_INFO"		//��ƽ̨����������Ϣ��
#define TBL_CP_LOGICCELL			"CP_LOGICCELL"			//��ƽ̨��Դ���
#define TBL_CP_LONGICNODE			"CP_LOGICNODE_PARA"		//��ƽ̨�߼��ڵ��
#define TBL_CP_REL_CELLNODE			"CP_REL_CELLNODE"		//��ƽ̨�߼��ڵ�ֲ���
#define TBL_CP_WKS_BLUEBOX			"CP_WKS_BLUEBOX"		//�����ռ��������ӹ�����

//��ƽ̨ʵʱ���������
#define RTBL_PHYNODE				"PHYNODE"				//����ڵ��
#define RTBL_LOGICNODE				"LOGICNODE"				//�߼��ڵ��
#define RTBL_DISKPOOL				"DISKPOOL"				//�洢��Դ��
#define RTBL_DISKSTAT				"DISKSTAT"				//�߼�����ͳ�Ʊ�
#define RTBL_SRVCONFIG				"SRVCONFIG"				//�������ñ�
#define RTBL_NETSTAT				"NETSTAT"				//����ͳ�Ʊ�
#define RTBL_WKSBLUEBOX				"WKS_BLUEBOX"			//�����ռ��������ӹ�ϵ��
#define RTBL_PROCINFO				"PROCSTAT"				//���̱�
#define RTBL_REALEVENT				"REALEVT"				//ʵʱ�����
#define RTBL_REALEVENTINFO			"REALEVTINFO"			//ʵʱ������Ϣ��

#define FIELD_PHYNODE				"PHYNODE"				//����ڵ�ID�ֶ�
#define FIELD_SRVCLASS				"SRVCLASS"				//�������
#define FIELD_DISKID				"DISKID"				//�߼�����ID
#define FIELD_TOTAL					"TOTAL"
#define FIELD_FREE					"FREE"
#define FIELD_USED					"USED"
#define FIELD_HOMEPATH				"HOMEPATH"	
#define FIELD_MAXSIZE				"MAXSIZE"
#define FIELD_ALLOC					"ALLOC"
#define FIELD_CELLID				"CELLID"
#define FIELD_CELLMODE				"CELLMODE"
#define FIELD_WORKSPACEFLAG			"WORKSPACEFLAG"
#define FIELD_TIMESECTION			"TIMESECTION"
#define FIELD_IDSECTION			    "IDSECTION"
#define FIELD_STARTYM				"STARTYM"
#define FIELD_ENDYM					"ENDYM"
#define FIELD_STARTPTID				"STARTPTID"
#define FIELD_ENDPTID				"ENDPTID"
#define FIELD_CELLTYPE				"CELLTYPE"
#define FIELD_DISKRESID				"DISKRESID"
#define FIELD_DISKSIZE				"DISKSIZE"


//��ƽ̨����������䶨��
#define CP_EVENT_MAILBOX			"CP_EVENT"
#define CP_EVENT_CLASS				4
#define PHYNODE_OBJTYPE				1000

//�Ʒ������ݵ�Ԫά��ģʽ����
enum CP_EVENT_TYPE
{
	CP_EVENT_PHYNODE = 200,			//����ڵ�����״̬����¼�
	CP_EVENT_PROC = 201,			//������ͣ�¼�
	CP_EVENT_DISKRES = 202,			//��Դ״̬����
	CP_EVENT_MEMORY = 203,			//�ڴ�Խ��
	CP_EVENT_CPU = 204,			//CPUԽ��
	CP_EVENT_DB = 205,			//���ݿ����
	CP_EVENT_PROCWARNING = 210,			//���̱���
	CP_EVENT_PROCKILLED = 211,			//���̱�ɱ
	CP_EVENT_SRVUPDATE = 212,			//��������

};
#define SG_CENTERFLAG_LINKOTHERCENTER		0x0001 //���Զ�ȡ�����������
#define SG_CENTERFLAG_SYNCOTHERCENTER		0x0002 //����ͬ�������������
#define SG_CENTERFLAG_HASSELFDB				0x0004//���Լ������ݿ�
#define SG_CENTERFLAG_MAINTSELFDB			0x0008 //���ݿ�����ά��
#define SG_CENTERFLAG_OPENSELFDAT			0x0010 //���⿪������
#define SG_CENTERFLAG_MINIBOXHISDBNUMBYSET	0x0020 //MINIBOX��ʷ���ݵı��ݸ�����������,Ϊ0ʱ,�򱸷���Ϊ������+1
//������Щ�ֳ����̴�С����,���ܲ�������ʷ����˫����
#define SG_CENTERFLAG_HISDB_SINGLE			0x0040 //��ʷ���ݿ������ĵ�������
#define SG_CENTERFLAG_DB_NOTSYNC			0x0080 //�����ⲻͬ��
#define SG_CENTERFLAG_STAT_ONLYUSESTATION	0x0100 //��˾������ʷ����ֻ���õ�վ��ʷ����
#define SG_CENTERFLAG_STAT_ACCNOTPROCLACK	0x0200 //��վ�ܼӲ������̯
#define SG_CENTERFLAG_SYNCMODE_ONLYUP		0x0400 //����������ͬ��

#include /**/ "ace/post.h"

#endif /* __CSP_COMMON_HEADER__ */
