#ifndef __SG__RDP_CONST__HHH
#define __SG__RDP_CONST__HHH
#include <stdlib.h>         
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <float.h> 
#include <string>
#include <map>
#include <set>
#include <vector>
//#include "CP_Common.h"
#include "csgdataset.h"
#define SG_MAX_FLOATVAL 3.4E38
#define SG_MIN_FLOATVAL -3.4E38

#define MIN_FLOAT_VAL 1e-4f
#define MIN_DOUBLE_VAL 1e-6f
typedef struct S_RDP_DEVMEASINFO
{
	short		DeviceType;		//�豸����
	int		    DeviceID;		//�豸ID
	short		Terminal;		//���Ӻ�
	short		MeasType;		//��������

}S_RDP_DEVMEASINFO;
struct CScdMeasPtInfoLess:
	public std::binary_function<S_RDP_DEVMEASINFO, S_RDP_DEVMEASINFO, bool> {
		bool operator()(const S_RDP_DEVMEASINFO& obj1, const S_RDP_DEVMEASINFO& obj2) const
		{
			if(obj1.DeviceID<obj2.DeviceID)
				return true;
			if(obj1.DeviceID==obj2.DeviceID)
			{
				if(obj1.DeviceType<obj2.DeviceType)
					return true;
				if(obj1.DeviceType==obj2.DeviceType)
				{

					if(obj1.MeasType<obj2.MeasType)
						return true;
					if(obj1.MeasType==obj2.MeasType)
					{
						if(obj1.Terminal<obj2.Terminal)
							return true;

					}
				}

			}
			return false;
		}
};
typedef std::set<S_RDP_DEVMEASINFO,CScdMeasPtInfoLess > SET_DEVMEAS;
typedef std::map<S_RDP_DEVMEASINFO,int,CScdMeasPtInfoLess> MAP_DEVMEAS_INT;
typedef std::map<S_RDP_DEVMEASINFO,S_TWOINT,CScdMeasPtInfoLess> MAP_DEVMEAS_TWOINT;
typedef std::map<int,S_RDP_DEVMEASINFO> MAP_INT_DEVMEAS;
typedef char SG_HOMEPATHNAME[256];			//��Ŀ¼λ�ýṹ

#if defined(WIN32)
#define sg_snprintf _snprintf
//#define sg_strcasecmp(a,b) _stricmp((a),(b))
#define sg_strncasecmp(a,b,n) _strnicmp((a),(b),(n))
#define sg_strdup(a)	_strdup((a))
#define sg_strupr(a)	_strupr((a))
#elif defined(__unix)

//#define sg_strcasecmp(a,b) strcasecmp((a),(b))
#define sg_strncasecmp(a,b,n) strncasecmp((a),(b),(n))
#define sg_strdup(a)	strdup((a))
#define sg_snprintf snprintf
//#define _stricmp strcasecmp
//#define _strnicmp strncasecmp
inline char *sg_strupr(char *p)
{
	char *ch=p;
	while(*ch)
	{
		if( *ch>='a' && *ch<='z' ) *ch=toupper(*ch);
		ch++;
	}
	return p;
}
#ifdef __sun
//��sun �ϣ�strcasecmp������
inline int sg_strcasecmp(char *a, char *b)  
{
	while(*a!=0 && *b!=0) {
		if((*a |0x20)>=0x61 && (*a |0x20)<=0x7a) {
			if((*a | 0x20) != (*b | 0x20))break;
		}
		else if(*a != *b) break;
		a++;b++;
	}
	return (*a- *b);
}
//��sun �ϣ�strcasecmp������
inline int sg_strncasecmp(char *a, char *b,int n)  
{
	int i=0;
	while(*a!=0 && *b!=0&&i<n) {
		if((*a |0x20)>=0x61 && (*a |0x20)<=0x7a) {
			if((*a | 0x20) != (*b | 0x20))break;
		}
		else if(*a != *b) break;
		a++;b++;
		i++;
	}
	return (*a- *b);
}

#else
#define sg_strcasecmp(a,b)  strcasecmp((a),(b))
#define sg_strncasecmp(a,b,n)	strncasecmp((a),(b),n)
#endif
#endif

#define RDPRET_ERROR		0
#define RDPRET_SUCCESS     1
#define RDPRET_OPENRDB_ERR 2  //��ʵʱ��ʧ��
#define RDPRET_NOTIN_RDB   3 //����ʵʱ���в�����

#define RDP_HDB_DSNAME		"HDBSrv"
#define SG_RDB_VERNO			2	//��ǰʵʱ��İ汾��


//ʵʱ��������
#define RTBL_PROTOCOLTYPE  "PROTOCOL"  //
#define RTBL_EXSYS_PROTTYPE  "EXSYS_PROT"  //�ⲿϵͳ��Լ��
#define RTBL_ANALOG  "ANA"
#define RTBL_DEVANALOG  "DEV_ANA"
#define RTBL_STATE  "DIG"
#define RTBL_DEVSTATE  "DEV_DIG"
#define RTBL_ACC	"ACC"
#define RTBL_DEVACC	"DEV_ACC"
#define RTBL_HISDEVINFO	"hisdevinfo"
#define RTBL_MANUAL_ANA  "manual_ana"
#define RTBL_MAN_STAT_ANA  "man_stat_ana"
#define RTBL_CALCINFO  "CALC"
#define RTBL_CALCITEM  "CALCITEM"
#define RTBL_RTU	"RTU"
#define RTBL_CALCCOND  "calc_cond"
#define RTBL_FERTCMDBUF  "fertcmd"
#define RTBL_CALCMEASINFO  "calcmeasinfo"
#define RTBL_CALCMEASCOND  "calcmeas_cond"
#define RTBL_CALCMEASITEM  "calcmeas_item"
#define RTBL_EXSYS  "EXTERNSYS"					//���ڶ������ݿ����
#define RTBL_POSITTION  "Position"
#define RTBL_ANALOG_ZF  "ZF_ANA"
#define RTBL_STATE_ZF  "ZF_DIG"
#define RTBL_ACC_ZF  "ZF_ACC"

#define RTBL_MEASTYPE  "meastype"
#define RTBL_STATDESC  "statdesc"

//ʵʱ����������ѭ�������,���ڴ���ʱ Circuit=1
#define RTBL_EVENT_MAXCIRCUITNUM 99999999


//���������Ϣ��λ�Ķ��� ���������Ϣֻ�е������ֽ���Ч��
//���һ���ֽ�Ϊң�ŵ�������λ
//���һ���ֽ�Ϊscd������״̬λ
#define RDP_POINT_STATUS_INVALID		0x00000001  //1:��Ч  0:��Ч
#define RDP_POINT_STATUS_ACTIVE			0x00000002  //1:����  0:����
#define RDP_POINT_STATUS_MANSET			0x00000004  //1:�˹����� 0:ʵʱ
#define RDP_POINT_STATUS_SOE			0x00000008	//1:�쳣ֵ 0:����ֵ
#define RDP_POINT_STATUS_RTU_OVERLIMIT	0x00000010	//1:����Ƿ�Խ��
#define RDP_POINT_STATUS_RTU_OVERLIMIT2	0x00000020  //1:���Խ������
#define RDP_POINT_STATUS_RTU_UPLIMIT	0x00000040  //1:���Խ����,���Խ�ޣ�����Խ���޾���Խ����
#define RDP_POINT_STATUS_RTU_OVERLIMIT3	0x00000080  //1:���Խ������

#define RDP_POINT_STATUS_GISMANSET		0x00000100  //1:ϵͳ�˹����� 0:ʵʱ
#define RDP_POINT_STATUS_NEEDCONFIRM	0x00000200  //1:ң�ű�λ��Ҫȷ�� 0:����
#define RDP_POINT_STATUS_TJFROMRDP		0x00000400  //1:��ͳ��ֵ������RDPϵͳ 0:ͳ��ֵ���ɱ�ϵͳ����
#define RDP_POINT_STATUS_IDPDEAD		0x00000800  //1:idp����  0:idp����
//ͳ��ֵ�����ȵǼ�Ϊ�Զ���������ͳ��ֵ��ߣ�����ͳ��ֵ��֮  ����ͳ��ֵ���
#define RDP_POINT_STATUS_TJFROM_MARK	0x00001000  //1:��ͳ��ֵ�ɱ���ֵͳ������ 0:����ͳ��ֵ
#define RDP_POINT_STATUS_OVERLIMIT		0x00002000  //1:����Ƿ�Խ��
#define RDP_POINT_STATUS_OVERLIMIT2		0x00004000  //1:���Խ������
#define RDP_POINT_STATUS_UPLIMIT		0x00008000  //1:���Խ����,���Խ�ޣ�����Խ���޾���Խ����
#define RDP_POINT_STATUS_OVERLIMIT3		0x00010000  //1:���Խ������
#define RDP_POINT_STATUS_HISDAT_MANSET	0x00020000  //1:�ò�����˹��޸Ļ�ã��Ǵ��Զ���ϵͳ���
#define RDP_POINT_STATUS_HISDAT_CAL		0x00040000  //1:�ò����ʷ�����ɼ������
#define RDP_POINT_STATUS_ABNORMITY		0x00080000  //1:�ò�����ݲ�����������ͳ�ƴ���
#define RDP_POINT_STATUS_STATWARNING	0x00100000  //1:�ò����ʷ����ͳ��ʱ,��Warning����
#define RDP_POINT_STATUS_GMANCANCEL		0x00200000	//1:GIS�����ոս�� 0:����ֵ

//#define RDP_POINT_STATUS_JIANXIU		0x00200000  //1:����
//#define RDP_POINT_STATUS_SG			0x00400000  //1:�¹� 

//#define RDP_POINT_STATUS_YXRAWVAL		0xFC000000	//��6λ��ң�ŵ�ֵ (0~63)

//#define RDP_POINT_STATUS_NEWDAT			0x00400000	//1:���ϵĲ��      0:�ϲ��
//#define RDP_POINT_STATUS_GMANCANCEL		0x02000000	//1:GIS�����ոս�� 0:����ֵ
//#define RDP_POINT_STATUS_SAVE_MARK		0x01000000	//1:��Ҫ�������ֵ 0���ѱ���
/*
enum SHARE_MEMORY_RECORD_LIMIT_CLOUD
{
	CLOUD_SMRL_NORMAL			= 0x00000000 ,		//	����
	CLOUD_SMRL_LIMIT_H		= 0x00000005 ,		//	Խ����	(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_UPLIMIT)/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_L		= 0x00000001 ,		//	Խ����	RDP_POINT_STATUS_OVERLIMIT/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_HH		= 0x00000007 ,		//	Խ������(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_OVERLIMIT2|RDP_POINT_STATUS_UPLIMIT)/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_LL		= 0x00000003 ,		//	Խ������(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_OVERLIMIT2)/RDP_POINT_STATUS_OVERLIMIT
};
*/
typedef union
{
	int Val;
	struct 
	{
#if defined(__sun)||defined(_AIX)
		unsigned char rawval:6;
		unsigned char bit5:2;
		unsigned char bit2;
		unsigned char bit3;
		unsigned char bit4:4; 
		unsigned char scd_status:4; //�Զ���ϵͳ������״̬λ
#else
		unsigned char scd_status:4;//�Զ���ϵͳ������״̬λ
		unsigned char bit4:4;
		unsigned char bit3;
		unsigned char bit2;
		unsigned char bit5:2;
		unsigned char rawval:6;
#endif
	}BitVal;
}S_PTSTATUS;

//�������͵Ĵ���ʽ
//��0λ:������״̬->�쳣״̬ʱ,����״̬
//��1λ:���쳣״̬->����״̬ʱ,��������
//��2λ:ң��ֱ�ӽ���ʵʱ��,����Ҫ����ң��ȷ��
//��3λ:ң������ʱ,������״̬
//��4λ:����Ϊ��������
#define RDP_MT_PROCMODE_CHANLOCK		0x00000001  //1:������״̬->�쳣״̬ʱ,����  0:��������
#define RDP_MT_PROCMODE_CHANEVT			0x00000002  //1:���쳣״̬->����״̬ʱ,��������  0:����������
#define RDP_MT_PROCMODE_TORDB			0x00000004  //1:ң��ֱ�ӽ���ʵʱ��,����Ҫ����ң��ȷ�� 0:����ʵʱ��,��Ҫ����ң��ȷ��
#define RDP_MT_PROCMODE_EVTNEWSTAT		0x00000008  //1:ң������ʱ,������״̬  0:ң������ʱ,����״̬->��״̬
#define RDP_MT_PROCMODE_PROTECT			0x00000010  //1:����Ϊ��������  0:Ϊң������
#define RDP_MT_PROCMODE_CRTSG			0x00000020  //1:��������б����������б��¹�
//#define RDP_MT_PROCMODE_JUDGELIMIT		0x00000040  //1:�ò���жϲ����ֵ
//


#define RDP_RTDB_FIELD_PTID			"ID"
#define RDP_RTDB_FIELD_DEV_PTID			"POINTID"
#define RDP_RTDB_FIELD_OBJTYPE		"OBJTYPE"
#define RDP_RTDB_FIELD_OBJID		"OBJID"
#define RDP_RTDB_FIELD_TERMINAL		"TERMINAL"
#define RDP_RTDB_FIELD_MEASTYPE		"MEASURE"
#define RDP_RTDB_FIELD_VALUE		"VALUE"
#define RDP_RTDB_FIELD_STATUS		"STATUS"
#define RDP_RTDB_FIELD_STAMP		"STAMP"
#define RDP_RTDB_FIELD_DISPUNIT		"DISPUNIT"
#define RDP_RTDB_FIELD_MARKVALUE		"MARKVALUE"
#define RDP_RTDB_FIELD_MARKSTAMP		"MARKSTAMP"
#define RDP_RTDB_FIELD_CONVFACT		"RATE"
#define RDP_RTDB_FIELD_FLAG			"FLAG"
#define RDP_RTDB_FIELD_WORKSPACE	"WORKSPACE"
#define RDP_RTDB_FIELD_SECTION		"SECTION"
#define RDP_RTDB_FIELD_YMD			"YMD"
#define RDP_RTDB_FIELD_HMS			"HMS"
#define RDP_RTDB_FIELD_MS			"MS"
#define RDP_RTDB_FIELD_GENTIME		"GENTIME"
#define RDP_RTDB_FIELD_GENTIME_S	"S_GENTIME"
#define RDP_RTDB_FIELD_NODEID		"NODEID"
#define RDP_RTDB_FIELD_RTUID1		"RTU_ID"
#define RDP_RTDB_FIELD_EXSYSID		"EXSYS_ID"
#define RDP_HISDB_FIELD_VALUE		"VALUE"
#define RDP_RTDB_FIELD_SUBSTATION	"SUBSTATION"


enum SG_RDP_MAILTYPE_DEF
{
	SG_RDP_MAILTYPE_DBPARACHAN			=0, //���ݿ���������仯
		SG_RDP_MAILTYPE_PFILE2DB			=1, //�������ļ�д�����ݿ���
		SG_RDP_MAILTYPE_CALLRDPPARA			=2, //�ٻ��Զ���ϵͳ�����ļ�
		SG_RDP_MAILTYPE_CALLJCDATA			=3, //�ٻ���������
		SG_RDP_MAILTYPE_FORCELOADRDB		=4, //ǿ�����¼���ĳ��������
		SG_RDP_MAILTYPE_RECALLHISDAT		=5, //����ĳһ��ʱ���ң����ʷ����
		SG_RDP_MAILTYPE_SYNCIDCHANGE		=6, //�豸��������Ĳ�������Ϣ
		SG_RDP_MAILTYPE_DBRCDSYNC			=7, //���ݿ�����仯����������
		SG_RDP_MAILTYPE_CALLPTHISDAT		=8, //����ĳ���ĳһ��ʱ�����ʷ����
		SG_RDP_MAILTYPE_RETINFO_TOCLIENT	=9, //���ظ��ͻ��˵���Ϣ
		SG_RDP_MAILTYPE_CALLPTHISDAT_NEW	=10, //����ĳ���ĳһ��ʱ�����ʷ����
		SG_RDP_MAILTYPE_CALLRTUSTAT			=11, //�ͻ��˲쿴�Զ���ϵͳ������״��
		SG_RDP_MAILTYPE_CALLRTUSTAT_RET		=12, //�ͻ��˲쿴�Զ���ϵͳ������״��������Ϣ
		SG_RDP_MAILTYPE_RTDBLOADOK			=13, //ʵʱ����������Ϣ
		SG_RDP_MAILTYPE_BACKEVT2FILE		=14, //��������ļ�
		SG_RDP_MAILTYPE_RESTOREEVTFROMFILE	=15, //���ļ����ر������ʵʱ���
		SG_RDP_MAILTYPE_MCUCHANGE			=16, //��mcu�仯������
		SG_RDP_MAILTYPE_TESTCHECKRDB		=17, //���ʵʱ��
		SG_RDP_MAILTYPE_LOADRDB				=18, //����ʵʱ���
};
enum SG_RDP_MAILPROC_CALLPTHIS_STEP
{
	SG_RDP_MAILPROC_STEP_RECV_OK			=1, //�յ��ʼ�
	SG_RDP_MAILPROC_STEP_CALLHIS_OK			=2, //������ʷ���ݳɹ�
	SG_RDP_MAILPROC_STEP_CALLHIS_ERR		=3, //������ʷ����ʧ��
};
typedef union 
{
	int IntVal;
	struct 
	{
#if defined(__sun)||defined(_AIX)
		unsigned char Res[2];		//����
		unsigned char XBCS;			//г�����������  0:Ϊ��Чֵ  1:Ϊ����  255:�ܻ����� 254:ż��г���� 253:���г����   
		unsigned char StatFlag;		//ͳ������
#else
		unsigned char StatFlag;		//ͳ������
		unsigned char XBCS;			//г����������� 0:Ϊ��Чֵ  1:Ϊ����  255:�ܻ����� 254:ż��г���� 253:���г����
		unsigned char Res[2];		//����
#endif
	}BitVal;
}USG_RDP_STATFLAG;

typedef struct S_RAW_EVENT
{
	SG_INT		YMD;		//������
	SG_INT		HMS;		//ʱ����
	SG_SHORT	Ms;			//����
	SG_SHORT	EvtClass;	//�������
	SG_INT		EvtType;	//��������
	SG_INT		ObjType;	//�豸����
	SG_INT		ObjID;		//�豸����
	SG_DOUBLE	NewVal;		//��ֵ
	SG_INT		NewStatus;	//������������
	SG_DOUBLE	OldVal;		//��ֵ
	SG_INT		OldStatus;	//������������
	SG_INT		EvtObj[5];	//���������Ϣֵ
	SG_INT		WorkSpace;	//�����ռ�
	SG_INT		Substation;	//��վID
	SG_CHAR		Msg[64];		//������Ϣ
	S_RAW_EVENT()
	{
		Init(); 
	};
	void Init()
	{
		memset(this,0,sizeof(S_RAW_EVENT));
		for(int i=0;i<5;i++)
			EvtObj[i]=0;
		WorkSpace=0;
		Substation=0;
	};
	SG_INT Serialize(CSgArchive & ar)
	{
		SG_INT i;
		CSgString sgstr;
		if(ar.IsLoading())
		{
			ar >>YMD;
			ar >>HMS;
			ar >>Ms;
			ar >>EvtClass;
			ar >>EvtType;
			ar >>ObjType;
			ar >>ObjID;
			ar >>NewVal;
			ar >>NewStatus;
			ar >>OldVal;
			ar >>OldStatus;
			ar >>WorkSpace;
			for(i=0;i<5;i++)
				ar >> EvtObj[i];
			ar	>> Substation;
			sgstr.Serialize(ar);
			strncpy(Msg,sgstr.GetSafeBuffer(),sizeof(Msg));
			Msg[sizeof(Msg)-1]='\0';
		}
		else
		{
			ar <<YMD;
			ar <<HMS;
			ar <<Ms;
			ar <<EvtClass;
			ar <<EvtType;
			ar <<ObjType;
			ar <<ObjID;
			ar <<NewVal;
			ar <<NewStatus;
			ar <<OldVal;
			ar <<OldStatus;
			ar <<WorkSpace;
			for(i=0;i<5;i++)
				ar << EvtObj[i];
			ar	<< Substation;
			sgstr=Msg;
			sgstr.Serialize(ar);
		}
		return true;
	};
	void operator = (const S_RAW_EVENT &obj)
	{
		YMD=obj.YMD;
		HMS=obj.HMS;
		Ms = obj.Ms;
		EvtClass=obj.EvtClass;
		EvtType=obj.EvtType;
		ObjType=obj.ObjType;
		ObjID=obj.ObjID;
		NewVal=obj.NewVal;
		NewStatus=obj.NewStatus;
		OldVal=obj.OldVal;
		OldStatus=obj.OldStatus;
		int i;
		for (i = 0; i<5; i++)
			 EvtObj[i] = obj.EvtObj[i];		
		WorkSpace = obj.WorkSpace;
		Substation = obj.Substation;
		sprintf(Msg, "%s", obj.Msg);
	}
}S_RAW_EVENT;
typedef vector<S_RAW_EVENT >	VECT_RAWEVENT;
#define RDP_EVTTYPE_PROCMODE_NOTSAVEDB			0x0001 //������
#define RDP_EVTTYPE_PROCMODE_NOTWARNING			0x0002  //���澯
#define RDP_EVTTYPE_PROCMODE_CONFIRM			0x0004 //�Ƿ�ȷ��
#define RDP_EVTTYPE_PROCMODE_STATE				0x0008 //�Ƿ�ͳ��
#define RDP_EVTTYPE_PROCMODE_FLASH				0x0010 //�Ƿ���˸
#define RDP_EVTTYPE_PROCMODE_VOICE				0x0020 //�Ƿ�������ʾ
#define RDP_EVTTYPE_PROCMODE_NEEDFREE			0x0040 //�Ƿ�����
#define RDP_EVTTYPE_PROCMODE_AUTOCONFIRM		0x0080 //�Զ����ʱ���Զ�ȷ��
#define RDP_EVTTYPE_PROCMODE_EVTBAG				0x0100 //����ۺ�
//#define RDP_EVTTYPE_PROCMODE_EVTBAG_II			0x0200 //�����ۺ�

#define RDP_EVTDAT_PROCSTATUS_NEED_CONFIRM	0x0001   //��ȷ��
#define RDP_EVTDAT_PROCSTATUS_NEED_FREE		0x0002   //����
#define RDP_EVTDAT_PROCSTATUS_NEED_STATE	0x0004   //��ͳ��
#define RDP_EVTDAT_PROCSTATUS_PROC_CONFIRM	0x0100   //��ȷ��
#define RDP_EVTDAT_PROCSTATUS_PROC_FREE		0x0200   //�ѽ��
typedef union USG_EVTDAT_PROCSTATUS
{
	int IntVal;
	struct
	{
#if defined(__sun)||defined(_AIX)
		unsigned char EvtLevel:8;		//����ȼ�
		unsigned char Res:8;			//����
		unsigned char ProcInfo;		//�Ѿ����������
		unsigned char NeedProc;		//��Ҫ�������
#else
		unsigned char NeedProc;		//��Ҫ�������
		unsigned char ProcInfo;		//�Ѿ����������
		unsigned char Res;			//����
		unsigned char EvtLevel;		//����ȼ�
#endif
	}BitVal;
}USG_EVTDAT_PROCSTATUS;
typedef struct S_RDP_EVENT
{
	S_RAW_EVENT RawEvent;
	SG_INT		ProcStatus;	//״̬
	CSgString	EventTxt;
	void Init()
	{
		RawEvent.Init();
		ProcStatus=0;
		EventTxt="";
	};
	SG_INT Serialize(CSgArchive & ar)
	{
		RawEvent.Serialize(ar);
		if(ar.IsLoading())
			EventTxt="";
		EventTxt.Serialize(ar);
		if(ar.IsLoading())
			ar >>ProcStatus;
		else
			ar <<ProcStatus;
		return true;
	};
}S_RDP_EVENT;
typedef struct S_RDP_EVT_NOTIFYMSG
{
	SG_INT		YMD;		//������
	SG_INT		HMS;		//ʱ����
	SG_SHORT	Ms;			//����
	SG_INT		EvtType;	//��������
	SG_INT		ObjType;	//�豸����
	SG_INT		ObjID;		//�豸����
	SG_INT		WorkSpace;	//�����ռ�
	SG_INT		ProcStatus;	//״̬,��������θĶ���Ч��λ���յ�����Ϣ���������Event.ProcStatus|=S_RDP_EVT_NOTIFYMSG.ProcStatus
	SG_INT		ProcNodeID;	//������Ϣ�Ľڵ�ID
	void Init()
	{
		memset(this,0,sizeof(S_RDP_EVT_NOTIFYMSG));
	};
	void Init(S_RDP_EVENT &EvtInfo,SG_INT StatusBitVal,SG_INT NodeID)
	{
		memset(this,0,sizeof(S_RDP_EVT_NOTIFYMSG));
		YMD=EvtInfo.RawEvent.YMD;
		HMS=EvtInfo.RawEvent.HMS;
		Ms=EvtInfo.RawEvent.Ms;
		EvtType=EvtInfo.RawEvent.EvtType;
		ObjType=EvtInfo.RawEvent.ObjType;
		ObjID=EvtInfo.RawEvent.ObjID;
		WorkSpace=EvtInfo.RawEvent.WorkSpace;
		ProcStatus=EvtInfo.ProcStatus&StatusBitVal;
		ProcNodeID=NodeID;
	};
	SG_INT Serialize(CSgArchive & ar)
	{
		if(ar.IsLoading())
		{
			ar >>YMD;
			ar >>HMS;
			ar >>Ms;
			ar >>EvtType;
			ar >>ObjType;
			ar >>ObjID;
			ar >>WorkSpace;
			ar >>ProcStatus;
			ar >>ProcNodeID;
		}
		else
		{
			ar <<YMD;
			ar <<HMS;
			ar <<Ms;
			ar <<EvtType;
			ar <<ObjType;
			ar <<ObjID;
			ar <<WorkSpace;
			ar <<ProcStatus;
			ar <<ProcNodeID;
		}
		return true;
	};
}S_RDP_EVT_NOTIFYMSG;
typedef std::vector<S_RDP_EVT_NOTIFYMSG >	VECT_EVT_NOTIYMSG;
#define SG_RDP_PTSRCTYPE_RTU			0		//��������������ն�
#define SG_RDP_PTSRCTYPE_CALC			1		//������������ڼ���
#define SG_RDP_PTSRCTYPE_EXSYS			2		//��������������ⲿϵͳ
#define SG_RDP_PTSRCTYPE_CALC_DEMAND	3		//��������������ļ���
#define SG_RDP_PTSRCTYPE_CALC_MEASTYPE	4		//�����������ͼ����㣬����ɢ�ʵ�
#define SG_RDP_PTSRCTYPE_STATION_STAT	5		//������������ڵ�վ����ͳ��,�����豸���ͽ�ΪOBJ_TEAM(�Ŷ�) OBJ_COMPANY(��˾)
#define SG_RDP_PTSRCTYPE_MANUAL			6		//��������������ֹ�����
#define SG_RDP_PTSRCTYPE_CALC_ACC		7		//������������ڻ��ֵ���
#define SG_RDP_PTSRCTYPE_CALC_POWER		8		//��������������õ����㹦��
#define SG_RDP_PTSRCTYPE_CALC_STEAMENERGY		9		//�������������������������

#define MEASTYPE_ACC_START 201   //����������͵���Сֵ

//�Զ���ϵͳ״̬
#define SG_RDP_EXSYSSTATUS_OK   0  //ͨ������
#define SG_RDP_EXSYSSTATUS_ERR  1  //ͨ������

//����flag�Ķ���
//yc
#define HISDAT_FLAG_REAL		0 //ң��ʵʱֵ
#define HISDAT_FLAG_PLAN		1 //�ƻ�ֵ
#define HISDAT_FLAG_H_KWH		2 //���̼���ڵ��
#define HISDAT_FLAG_MARK		3 //����ֵ
#define HISDAT_FLAG_REAL_MAX	4 //���̼����ʵʱ���ֵ
#define HISDAT_FLAG_REAL_MIN	5 //���̼����ʵʱ��Сֵ
#define HISDAT_STATDAT_BEGIN    10
//���¾�Ϊͳ����
#define HISDAT_FLAG_MAX			10 //�����ֵ
#define HISDAT_FLAG_MAX_T		11 //�����ֵ����ʱ
#define HISDAT_FLAG_MIN			12 //����Сֵ
#define HISDAT_FLAG_MIN_T		13 //����Сֵ����ʱ
#define HISDAT_FLAG_SUM			14 //�ܼ�ֵ
#define HISDAT_FLAG_AVER		15 //ƽ��ֵ
#define HISDAT_FLAG_FHL			16  //������
#define HISDAT_FLAG_HGL			17  //�ϸ���
#define HISDAT_FLAG_PTNUM		18  //��Ч�����

#define HISDAT_FLAG_MON_MAX		20 //�����ֵ
#define HISDAT_FLAG_MON_MAX_T	21 //�����ֵ����ʱ
#define HISDAT_FLAG_MON_MIN		22 //����Сֵ
#define HISDAT_FLAG_MON_MIN_T	23 //����Сֵ����ʱ
#define HISDAT_FLAG_MON_SUM		24 //���ܼ�ֵ
#define HISDAT_FLAG_MON_AVER	25 //��ƽ��ֵ
#define HISDAT_FLAG_MON_FHL		26  //�¸�����
#define HISDAT_FLAG_MON_HGL		27  //�ºϸ���
#define HISDAT_FLAG_MON_PTNUM	28  //����Ч�����

#define HISDAT_FLAG_YEAR_MAX	30 //�����ֵ
#define HISDAT_FLAG_YEAR_MAX_T	31 //�����ֵ����ʱ
#define HISDAT_FLAG_YEAR_MIN	32 //����Сֵ
#define HISDAT_FLAG_YEAR_MIN_T	33 //����Сֵ����ʱ
#define HISDAT_FLAG_YEAR_SUM	34 //���ܼ�ֵ
#define HISDAT_FLAG_YEAR_AVER	35 //��ƽ��ֵ
#define HISDAT_FLAG_YEAR_FHL	36  //�긺����
#define HISDAT_FLAG_YEAR_HGL	37  //��ϸ���
#define HISDAT_FLAG_YEAR_PTNUM	38  //����Ч�����

#define HISDAT_FLAG_REAL_DAY_MAX		40 //��ʵʱ���ֵ
#define HISDAT_FLAG_REAL_DAY_MIN		41 //��ʵʱ��Сֵ
#define HISDAT_FLAG_SD_MAX				42 //ʱ�����ֵ
#define HISDAT_FLAG_SD_MIN				43 //ʱ����Сֵ

#define HISDAT_FLAG_REAL_MON_MAX		45 //��ʵʱ���ֵ
#define HISDAT_FLAG_REAL_MON_MIN		46 //��ʵʱ��Сֵ

#define HISDAT_FLAG_REAL_YEAR_MAX			47 //��ʵʱ���ֵ
#define HISDAT_FLAG_REAL_YEAR_MIN			48 //��ʵʱ���ֵ

#define HISDAT_FLAG_DAY_OL_TIME			50  //��Խ��ʱ��
#define HISDAT_FLAG_DAY_OL_CNT			51  //��Խ�޴���
#define HISDAT_FLAG_MON_OL_TIME			52  //��Խ��ʱ��
#define HISDAT_FLAG_MON_OL_CNT			53  //��Խ�޴���
#define HISDAT_FLAG_YEAR_OL_TIME		64  //��Խ��ʱ��
#define HISDAT_FLAG_YEAR_OL_CNT			65  //��Խ�޴���
#define HISDAT_FLAG_SD_REAL_MAX				54 //ʱ��ʵʱ���ֵ
#define HISDAT_FLAG_SD_REAL_MIN				55 //ʱ��ʵʱ��Сֵ

#define HISDAT_FLAG_DAY_EVT_S			56  //������ͳ��
#define HISDAT_FLAG_MON_EVT_S			57  //������ͳ��
#define HISDAT_FLAG_YEAR_EVT_S			58  //������ͳ��

#define HISDAT_FLAG_REAL_MAN		60 //�ֳ�ʵʱֵ
#define HISDAT_FLAG_H_KWH_MAN		62 //�ֳ����̼���ڵ��
#define HISDAT_FLAG_MARK_MAN		63 //�ֳ�����ֵ

#define HISDAT_FLAG_DAY_DISTANCE		66 //�վ���
#define HISDAT_FLAG_MON_DISTANCE		67 //�¾���
#define HISDAT_FLAG_YEAR_DISTANCE		68 //�����

//#define HISDAT_FLAG_DAY_RUN_TIME		69 //������ʱ��
//#define HISDAT_FLAG_MON_RUN_TIME		70 //������ʱ��
//#define HISDAT_FLAG_YEAR_RUN_TIME		71 //������ʱ��

#define HISDAT_FLAG_DAY_KWH		100 //�յ��
#define HISDAT_FLAG_MON_KWH		101 //�µ��
#define HISDAT_FLAG_YEAR_KWH	102 //����
#define HISDAT_FLAG_SD_KWH		103 //ʱ�ε��


#define HISDAT_FLAG_KWH_FEE_CUR			110		// ��ǰ����
#define HISDAT_FLAG_MON_KWH_FEE_CUR		111		// ���·��ʵ��
#define HISDAT_FLAG_MON_KWH_FEE_LAST	112		// ���·��ʵ��
#define HISDAT_FLAG_MON_KWH_FEE_LL		113		// �����·��ʵ��

#define HISDAT_FLAG_DAY_KWH_PTNUM		117 //�յ����Ч�����
#define HISDAT_FLAG_MON_KWH_PTNUM		118 //�µ����Ч�����
#define HISDAT_FLAG_YEAR_KWH_PTNUM		119 //������Ч�����

#define HISDAT_FLAG_DAY_DIG_ONTIME		200 //�պ�բʱ��(��)
#define HISDAT_FLAG_DAY_DIG_OFFTIME		201 //�շ�բʱ��(��)
#define HISDAT_FLAG_DAY_DIG_ONCNT		202 //�պ�բ����
#define HISDAT_FLAG_DAY_DIG_OFFCNT		203 //�շ�բ����
#define HISDAT_FLAG_MON_DIG_ONTIME		210 //�º�բʱ��(��)
#define HISDAT_FLAG_MON_DIG_OFFTIME		211 //�·�բʱ��(��)
#define HISDAT_FLAG_MON_DIG_ONCNT		212 //�º�բ����
#define HISDAT_FLAG_MON_DIG_OFFCNT		213 //�·�բ����
#define HISDAT_FLAG_YEAR_DIG_ONTIME		214 //���բʱ��(��)
#define HISDAT_FLAG_YEAR_DIG_OFFTIME	215 //���բʱ��(��)
#define HISDAT_FLAG_YEAR_DIG_ONCNT		216 //���բ����
#define HISDAT_FLAG_YEAR_DIG_OFFCNT		217 //���բ����

#define HISDAT_FLAG_DAY_PROC_STARTCNT	204 //�ڵ��ս�����������
#define HISDAT_FLAG_MON_PROC_STARTCNT	205 //�ڵ��½�����������
#define HISDAT_FLAG_YEAR_PROC_STARTCNT	206 //�ڵ��������������


//
#define HISDAT_FLAGCLASS_REAL			1		//ʵʱ����
#define HISDAT_FLAGCLASS_DAY			2		//��ͳ������
#define HISDAT_FLAGCLASS_MON			3		//��ͳ������
#define HISDAT_FLAGCLASS_YEAR			4		//��ͳ������
//ϵͳ��ϢID����
#define RDP_SYSINFO_ID_CENTERSRVIP 0
#define RDP_SYSINFO_ID_SGDELAYTIME 1
#define RDP_SYSINFO_ID_SGYCDEAD 2
#define RDP_SYSINFO_ID_JUDGEYCDEADTIME 3	//ң��������ʱ��

//rtu�����Ĵ���ʽ
//��0λ:��1->0ʱ,���¹�����
//��1λ:���¹��������ң���쳣�ж�
#define RDP_RTU_PROCMODE_CRTSG			0x00000001  //1:��������1->0ʱ������SG
#define RDP_RTU_PROCMODE_SGUSEYC			0x00000002  //1:SG���ж�����ң����쳣�ж�
#define RDP_RTU_PROCMODE_CRTYCSG			0x00000004  //1:����ң���Ӧ�豸û��ң��ʱ��ң��ͻ������¹ʵ��쳣�ж�
#define RDP_RTU_PROCMODE_HISPERIODFLAG	0x00000008  //1:��ʷ���ݰ������ٲ� (��ÿ�����ٲ�һ�Σ���һ���ٲ�2�������),������ʼʱ���¼��RTU_Ip�ֶ��� 
														//0:�����ٲ�
#define RDP_RTU_PROCMODE_XS_USEMARK		0x00000010  //1:�������ʱʹ�ñ���ֵ 
#define RDP_RTU_PROCMODE_YX2RDB			0x00000020  //1:ң��ֱ�ӽ���ʵʱ�� 
#define RDP_RTU_PROCMODE_PROCRTDAT			0x00000040  //1:����ʵʱ����

//bit0:�Ƿ���ʵʱyc bit1::�Ƿ�����ʷyc bit2���Ƿ���ʵʱ���� bit3���Ƿ���ʵʱ���� 
//bit4���Ƿ�����ʷ���� bit5���Ƿ�����ʷ���� bit6��yx�Ƿ��͸澯��Ϣ bit7:ң���Ƿ�д��ʵʱ��
#define RDP_EXSYS_PROCMODE_PROCRTYC			0x00000001
#define RDP_EXSYS_PROCMODE_PROCHISYC		0x00000002
#define RDP_EXSYS_PROCMODE_PROCRTKWH		0x00000004
#define RDP_EXSYS_PROCMODE_PROCHISMARK		0x00000008
#define RDP_EXSYS_PROCMODE_PROCHISACC		0x00000010
#define RDP_EXSYS_PROCMODE_YXWRNING			0x00000020
#define RDP_EXSYS_PROCMODE_YX2RDB			0x00000040
#define RDP_EXSYS_PROCMODE_CRTYCSG			0x00000080  //1:����ң���Ӧ�豸û��ң��ʱ��ң��ͻ������¹ʵ��쳣�ж�
#define RDP_EXSYS_PROCMODE_CRTSG			0x00000100  //1:��������1->0ʱ������SG
#define RDP_EXSYS_PROCMODE_SGUSEYC			0x00000200  //1:SG���ж�����ң����쳣�ж�

//0:�����ٲ�
//���Ĵ���ģʽ
#define RDP_PT_PROCMODE_FESEND_MARK			0x00000001	//1:ǰ�ó����ͱ���
#define RDP_PT_PROCMODE_FESEND_VAL			0x00000002	//1:ǰ�÷���ʵʱ����,���ڵ���,���Ƿ���Сʱ����
#define RDP_PT_PROCMODE_FESEND_HIS_VAL		0x00000004	//1:ǰ�÷�����ʷ����,���ڵ���,������ʷ����
#define RDP_PT_PROCMODE_FESEND_HIS_MARK		0x00000008	//1:ǰ�ó�������ʷ����
#define RDP_PT_PROCMODE_OVERLIMIT_1			0x00000010	//1:����ң��һ��Խ�ޱ���
#define RDP_PT_PROCMODE_SAVEDB				0x00000020	//1:�����������ݿ�
#define RDP_PT_PROCMODE_SENDALARM			0x00000040	//1:��������alarm
#define RDP_PT_PROCMODE_CALCMEAS			0x00000080	//1:���������������ͷ�ʽ���м���
#define RDP_PT_PROCMODE_CALC_HISCAL			0x00000100	//1:��������SG_RDP_HIS_CALOBJ���е�������м���
#define RDP_PT_PROCMODE_CALC_I				0x00000200	//1:��������SG_RDP_CALC_EXPR���е�������м���
#define RDP_PT_PROCMODE_PROCABNORMITY		0x00000400	//1:�����쳣����,��ʱң���������,��Ϊ�쳣����ֵ����
#define RDP_PT_PROCMODE_ALARM_DELAY			0x00000800	//1:����ʱ,��ʱ����
#define RDP_PT_PROCMODE_NOTALARM			0x00001000	//1:��㲻����
#define RDP_PT_PROCMODE_ALARMSAVEPT			0x00002000	//1:��㱨��ʱ������ǰֵ�������ʷ����,dps2��Ч
#define RDP_PT_PROCMODE_BIGCHANSAVEPT		0x00004000	//1:���ͻ�����  dps2��Ч 
#define RDP_PT_PROCMODE_SAVE_REALMAXMIN		0x00008000	//1:���洢ʵʱ�����С  dps2��Ч
#define RDP_PT_PROCMODE_MANUALMETER			0x00010000	//1:����г���
#define RDP_PT_PROCMODE_OVERLIMIT_2			0x00020000	//1:����ң�����Խ�ޱ���
#define RDP_PT_PROCMODE_ACCNOTPROCLACK		0x00040000	//1:��Ȳ�����̯����
#define RDP_PT_PROCMODE_ACCMON_NOTUSEMARK	0x00080000	//1:�µ�Ȳ��ñ���ͳ��
#define RDP_PT_PROCMODE_EVTBIG				0x00100000	//1:������ۺϴ���
#define RDP_PT_PROCMODE_ACC_LESSZERO			0x00200000	//1:��ȿ���Ϊ��
#define RDP_PT_PROCMODE_FESEND_REAL_ONPERIOD	0x00400000	//1:��������ݰ����̼��ʱ����д洢
#define RDP_PT_PROCMODE_STAT_NOTZERO	0x00800000	//1:ͳ��ʱ���㲻����ͳ��
#define RDP_PT_PROCMODE_ACC_MARK_NOBACK	0x01000000	//1:��ȱ��벻�ᵹ��
#define RDP_PT_PROCMODE_CHANSAVE	0x02000000	//1:������仯�洢
#define RDP_PT_PROCMODE_ACCDAY_NOTUSEMARK	0x04000000	//1:�յ�Ȳ��ñ���ͳ��

/*
//	��������ģʽ����
#define RDP_MT_PROCMODE_FE_MARK			0x00000001  //1:ǰ�ó����ͱ���
#define RDP_MT_PROCMODE_FE_VALUE		0x00000002  //1:ǰ�ó�����Сʱ����
#define RDP_MT_PROCMODE_FE_HIS_VAL		0x00000004  //1:ǰ�ó�������ʷ����
#define RDP_MT_PROCMODE_FE_HIS_MARK		0x00000008  //1:ǰ�ó�������ʷ����
*/
//�����ģʽ
#define SG_EVT_PROCMODE_ALL		0	//�������е�����
#define SG_EVT_PROCMODE_NO		1	//�������κ�����
#define SG_EVT_PROCMODE_WS		2	//��WorkSpace��������


#endif //#ifndef __SG__OS_BASE__HHH
