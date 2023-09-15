//------------------------------------------------------------------------------
// ����scd����Ļ�������
//------------------------------------------------------------------------------

#ifndef _RDPBASEDEF_HHH_
#define _RDPBASEDEF_HHH_
#include "sgarchive.h"
#include "sgdataset.h"
//#include "sgmicro.h"
//#include "rdp_const.h"

//#define RDP_FERT_MAX_EXTSYSNUM 128

#define RDP_DELAY_YXEVENT_TIME       20  //��λ�����ӳٱ���ʱ��

#define RDP_HISTABNAME_HEAD_YC			"HISDAT"
#define RDP_HISTABNAME_HEAD_YX			"HISDATDIG"
#define RDP_HISTABNAME_HEAD_KWH			"HISDATACC"
#define RDP_HISTABNAME_HEAD_PLAN		"SG_HISDAT_PLAN"
#define RDP_HISTABNAME_HEAD_EVENT		"HIS_EVENT"
#define RDP_HISTABNAME_HEAD_MANUAL_YC	"SG_HISDAT_MANUAL"

#define RDP_HISTAB_YCID_SECTION		10000		//ÿ����ʷ����YC��ID�ķ�Χ
#define RDP_HISTAB_YXID_SECTION		500000		//ÿ����ʷ����YX��ID�ķ�Χ
#define RDP_HISTAB_KWHID_SECTION		10000	//ÿ����ʷ����KWH��ID�ķ�Χ
#define RDP_HISTAB_MANUALYCID_SECTION	100000		//ÿ����ʷ���г���YC��ID�ķ�Χ

#define SG_RDP_SAVE_FILE_HEAD "SG_RDP_FILE229"
#define SG_RDP_PARA_FILE_HEAD "--SG_PARA_DATAFMT: "

#define RDP_FILETYPE_PROCHISDATE	0 //������ʷ�������ʱ���ļ�
#define RDP_FILETYPE_SENDHISDAT		1 //������ʷ�����ļ�
#define RDP_FILETYPE_SAVEHISDAT		2 //����������Ĵ�����ʷ�����ļ�
#define RDP_FILETYPE_SAVETMPHISDAT	3 //�����������Ļ�����ʷ�����ļ�
#define RDP_FILETYPE_BAK_POINTVAL	4 //����ֵ�����Ϣ
#define RDP_FILETYPE_PROCHISDATE_OLD	5 //�µĴ�����ʷ�������ʱ���ļ�
#define RDP_FILETYPE_CALLHISINFO	6 //�ٻ���ʷ���ݵ���Ϣ�ļ�
#define RDP_FILETYPE_RTUSTATUS		8 //�Զ���ϵͳ״̬��Ϣ�ļ�
#define RDP_FILETYPE_PTPROCTIME		9 //���������ȡʱ���ļ�
#define RDP_FILETYPE_CALLPROCINFO	10 //ͳ�ƴ洢���̵�����Ϣ
#define RDP_FILETYPE_RECVHISDAT		11 //����������Ľ��ܵ�����ʷ�����ļ�
#define RDP_FILETYPE_HISCHANPROCTIME		12  //��ʷ�������ȡʱ���ļ�
#define RDP_FILETYPE_HISOPERMODE		13  //��ʷ���з�ʽ�ļ�
#define RDP_FILETYPE_HIGHLOADINFO		15  //��߸�����Ϣ�ļ�
#define RDP_FILETYPE_LACKHISDATINFO     16  //�Զ���ϵͳ��ʷ�����ļ�ȱʧ����ļ�
#define RDP_FILETYPE_CHANYXERR          17  //�仯ң�Ź�������ļ�
#define RDP_FILETYPE_HISTBLCHANLOG	18 //��ʷ������Ϣ
#define RDP_FILETYPE_SENDHISDAT_NEW		19 //������ʷ�����ļ�
#define RDP_FILETYPE_SENDRTUSOE		20 //�洢soe�ļ�
#define RDP_FILETYPE_MODIFYPTINFO	21 //��ʷ����޸���Ϣ

#define RDP_FILETYPE_SAVEHISDAT_CLOUD	25 //�Ʒ��������ʷ�����ļ�
#define RDP_FILETYPE_SAVEPARADAT_CLOUD	26 //�Ʒ���洢���������Ϣ

#define RDP_FILETYPE_SAVEEVENT_CLOUD		27 //�Ʒ������ʷ�����ļ�
#define RDP_FILETYPE_SAVEEVENTLIST_CLOUD	34 //�Ʒ������ʷ�����ļ�

#define RDP_FILETYPE_RTDBINFO_CLOUD		28 //�Ʒ���ʵʱ���ݿ���Ϣ�ļ�
#define RDP_FILETYPE_RTTBL_CLOUD		29 //�Ʒ���ʵʱ���ݱ��ļ�
#define RDP_FILETYPE_SENDHISDAT_CLOUD	30 //������ʷ�����ļ�
#define RDP_FILETYPE_SENDRAWEVT_CLOUD	31 //�Ʒ����͵��������ļ�
#define RDP_FILETYPE_DEMANDBAKFILE		32 //���������ļ�
#define RDP_FILETYPE_RTTBL_DATVAL		33 //�Ʒ���ʵʱ����ֵ���ļ�
#define RDP_FILETYPE_POWERBAKFILE		34 //���ʱ����ļ�
#define RDP_FILETYPE_SAVE_EVTMSG		35 //�Ʒ���洢������Ϣ�ļ�
#define RDP_FILETYPE_RTTBL_EVTINFO		36 //�Ʒ���ʵʱ�������Ϣ
#define RDP_FILETYPE_DBOPER				37 //���ݿ�����ļ�
#define RDP_FILETYPE_FERTSENDFILE		38 //ǰ�òɼ������ļ�����¼�����ļ���
#define RDP_FILETYPE_MQTT_TOPICNAME		39 //MQTT������������Ϣ
#define RDP_FILETYPE_MQTT_TOPICINFO		40 //MQTT��������Ϣ�ļ�
#define RDP_FILETYPE_MQTT_MSGDAT		41 //MQTT����Ϣ�ļ�
#define RDP_FILETYPE_RAWBAGINFO			42 //�ۺ�������Ϣ
#define RDP_FILETYPE_MINIBOX_RECVCMD	43 //΢�������յ����·�����
#define RDP_FILETYPE_RTDB_CLOUD			44 //�Ʒ���ʵʱ���ݿ��ļ�

#define SG_RDP_SAVE_FILE_VERSION	1
typedef struct S_SG_RDP_FILE_HEAD
{
	char Version[60];
	short int  FileType;
	short int  VerNo;
	short int  ProcMode;	//0:��������  1:��ʷ���ݲ���¼ͳ�Ʊ����Ϣ
	short int  res1;
	S_SG_RDP_FILE_HEAD()
	{
		strcpy(Version,SG_RDP_SAVE_FILE_HEAD);
		VerNo=SG_RDP_SAVE_FILE_VERSION;
		ProcMode=res1=0;
	}
	int serialize(CSgArchive&ar,int Ver=SG_RDP_SAVE_FILE_VERSION)
	{
		if(ar.IsLoading())
		{
			strcpy(Version, "");
			ar.Read(Version,sizeof(Version));
			if(strcmp(Version,SG_RDP_SAVE_FILE_HEAD)!=0)
				return false;
			ar>>FileType;
			ar>>VerNo;
			ar>>ProcMode;
			ar>>res1;
		}
		else
		{
			ar.Write(Version,sizeof(Version));
			ar<<FileType;
			ar<<VerNo;
			ar<<ProcMode;
			ar<<res1;
		}
		return true;
	};	
}S_SG_RDP_FILE_HEAD;
#define SAVEFILE_INSERTDB_MODE_BATCH_INSERT		0	//���Ȳ��������룬���ɹ���ɾ����¼�󣬲���
#define SAVEFILE_INSERTDB_MODE_DEL_INSERT		1	//ɾ����¼�󣬲���
#define SAVEFILE_INSERTDB_MODE_KEYDEL_INSERT	2	//������ɾ����,����������
#define SAVEFILE_INSERTDB_MODE_DELETE			3	//ɾ����¼
#define SAVEFILE_INSERTDB_MODE_EVT_INSERT			4	//�������ģʽ���������룬�����ԭ�м�¼����PROCSTATUS�ֶλ��洢
typedef struct S_SG_SAVEFILE_INSERTDBINFO
{
	int			InsertMode;			//0:���Ȳ��������룬���ɹ���ɾ����¼�󣬲���
									//1:ɾ����¼�󣬲���
									//2:������ɾ����,����������
									//3:ɾ����¼
	int			KeyFieldFlag;			//0: �����ݿ�����
										//1:��KeyFieldName�м�¼Ϊ����
	int			WorkSpace;				//�洢WorkSpace��
	int			SectionID;				//�洢SectionID��
	CSgString	TblHeadName;	//��ʷ����,��ʷ��Ļ�������,�������µı���
	CSgString	SeqenceName;	//����ʱʹ�õ�sequece���ƣ����û���
	CSgString	SeqFieldName;	//����ʱʹ�õ�sequece�ֶ�
	CSgStringArray KeyFieldName; //�����ֶ�����
	S_SG_SAVEFILE_INSERTDBINFO()
	{
		InsertMode=SAVEFILE_INSERTDB_MODE_BATCH_INSERT;
		KeyFieldFlag=0;
		WorkSpace=0;
		SectionID=-1;
		TblHeadName="";
		SeqenceName="";
		SeqFieldName="";
		KeyFieldName.RemoveAll();
	};
	SG_BOOL		Serialize(CSgArchive&ar,int VerNo=SG_RDP_SAVE_FILE_VERSION)
	{
		int keynum,i;
		if(ar.IsLoading())
		{
			if(VerNo==SG_RDP_SAVE_FILE_VERSION)
			{
				ar>>InsertMode;
				ar>>KeyFieldFlag;
				ar>>WorkSpace;
				ar>>SectionID;
				ar>>keynum;
				CSgString sgstr;
				for(i=0;i<keynum;i++)
				{
					sgstr.Serialize(ar);
					KeyFieldName.Add(sgstr.GetSafeBuffer());
				}
			}
		}
		else
		{
			if(VerNo==SG_RDP_SAVE_FILE_VERSION)
			{
				ar<<InsertMode;
				ar<<KeyFieldFlag;
				ar<<WorkSpace;
				ar<<SectionID;
				keynum=KeyFieldName.GetSize();
				ar<<keynum;
				for(i=0;i<keynum;i++)
				{
					CSgString &sgstrpt=KeyFieldName.Get(i);
					sgstrpt.Serialize(ar);
				}
			}
		}
		SeqenceName.Serialize(ar);
		SeqFieldName.Serialize(ar);
		TblHeadName.Serialize(ar);
		return true;
	};
}S_SG_SAVEFILE_INSERTDBINFO;  //�ļ�->���ݿ�������ز�����Ϣ

typedef struct
{
	short int  ExSysID;
	short int  res;
	SG_Date  ProcDate;
	SG_Date  CurProcDate;  ////��������٣��������ٽ�����Ӧ���ٻ�����ʼʱ��
	int		 ReRead_STime; //�ض��ľ��������ʼʱ��
	int		 ReRead_ETime; //�ض��ľ��������ֹʱ��
}S_HIS_PROCDATE;

typedef struct
{
	short int  ExSysID;
	short int  Status;
	int		   ProcTime;
}S_HIS_EXSYSSTATUS;
//������־�е��¼�����
#define RUNLOG_REAL_LINKCHAN       0
#define RUNLOG_HIS_LINKCHAN        1
#define RUNLOG_LACK_HISDAT         2
#define RUNLOG_YX_MORE             3
#define RUNLOG_SHAREMEMORY_FAIL    4
#define RUNLOG_HDBSRV_DB_FAIL      5

typedef struct
{
	short int WorkSpace;
	short int ExSysID;
	short int EventType;
	int NowYmd;
	int NowHms;
	int HisYmd;
	int HisHms;
	int TheoryNum;
	int FactNum;
	short int DatType;
}S_LACKINFO_HISDAT;
typedef struct
{
	short int WorkSpace;
	short int ExSysID;
	short int EventType;
	int NowYmd;
	int NowHms;
	int AllYXNum;
	int ChanYXNum;
}S_CHANYX_NUMINFO;

//���ݿ��в��仯�����еĲ�����Ͷ���
#define PTCHANGE_TYPE_YC			1
#define PTCHANGE_TYPE_YX			2
#define PTCHANGE_TYPE_KWH			3
#define PTCHANGE_TYPE_MANUAL_YC		4
#define PTCHANGE_TYPE_MANUAL_VAL	5
#define PTCHANGE_TYPE_SRVSEND_YC	6
#define PTCHANGE_TYPE_SRVSEND_YX	7
#define PTCHANGE_TYPE_SRVSEND_KWH	8
//���ݿ�����Ķ���
#define DBOPER_TYPE_INSERT			0
#define DBOPER_TYPE_UPDATE			1
#define DBOPER_TYPE_DELETE			2
typedef struct 
{
	int WorkSpace;
	int	BufLen;
}S_RECVHISFILE_HEAD;
typedef struct 
{
	int WorkSpace;
	int PtNum;
}S_PT_PROCTIME_HEAD;
typedef struct 
{
	int		PTChangeType;  //��������仯����
	int		ProcTime;		//������㴦��ʱ��
}S_PT_PROCTIME;

//���ݿ��Ĳ������
#define DBTBL_POINTTYPE_YC		0
#define DBTBL_POINTTYPE_YX		1
#define DBTBL_POINTTYPE_KWH	2
#define DBTBL_POINTTYPE_EVENT	3
#define DBTBL_POINTTYPE_MANUAL_YC	5
#define DBTBL_POINTTYPE_END		6

//���ݿ�����������
#ifdef SG_CLOUD_RDP
#define	DBTBL_DATATYPE_SAVE		1	//��ʱ��������
#define	DBTBL_DATATYPE_D_STAT	2  //��ͳ������
#define	DBTBL_DATATYPE_M_STAT	3  //��ͳ������
#define	DBTBL_DATATYPE_Y_STAT	4  //��ͳ������
#define	DBTBL_DATATYPE_PLAN		5		//�ƻ�����
#define	DBTBL_DATATYPE_END		6	
#else
#define	DBTBL_DATATYPE_SAVE		1	//��ʱ��������
#define	DBTBL_DATATYPE_STAT		2  //ͳ������
#define	DBTBL_DATATYPE_PLAN		3		//�ƻ�����
#define	DBTBL_DATATYPE_END		4	
#endif
#define HIS_DATTYPE_YC		0
#define HIS_DATTYPE_YX		1
#define HIS_DATTYPE_KWH		2
#define HIS_DATTYPE_PLAN	3
#define HIS_DATTYPE_EVENT	4

#define HISHEAD_CALLFLAG_RECALL			0  //���ٲ��������ʷ����
#define HISHEAD_CALLFLAG_AUTO			1  //�Զ����ղ�������ʷ���� ��YC OR KWH��
#define HISHEAD_CALLFLAG_AUTO_YCKWH		2  //�Զ����ղ�������ʷ���� ��YC AND KWH��
#define HISHEAD_CALLFLAG_MODI			3  //�޸Ĳ�������ʷ����
#define HISHEAD_CALLFLAG_SELFSAVE		4  //�Լ����̲�������ʷ����
#define HISHEAD_CALLFLAG_HISCAL			5  //��ʷ�����������ʷ����
typedef struct 
{
	SG_UCHAR DatType;
	SG_UCHAR AutoCallFlag; //�Զ����ձ�־
	SG_UCHAR ModifyCallTimeFlag; //�޸��ٲ�ʱ���־
	SG_UCHAR res[1];
	SG_INT   RcdNum;
	SG_INT  s_YMD;
	SG_INT  s_HMS;
	SG_INT  e_YMD;
	SG_INT  e_HMS;
	int buf_size()
	{
		return sizeof(DatType)+sizeof(AutoCallFlag)+sizeof(RcdNum)
			+sizeof(s_YMD)+sizeof(s_HMS)+sizeof(e_YMD)+sizeof(e_HMS);
	};
	void serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>DatType;
			ar>>AutoCallFlag;
			ar>>RcdNum;
			ar>>s_YMD;
			ar>>s_HMS;
			ar>>e_YMD;
			ar>>e_HMS;
		}
		else
		{
			ar<<DatType;
			ar<<AutoCallFlag;
			ar<<RcdNum;
			ar<<s_YMD;
			ar<<s_HMS;
			ar<<e_YMD;
			ar<<e_HMS;
		}
	};
}S_HIS_HEAD;
typedef struct S_COMMTASK_HISHEAD
{
	SG_UCHAR DatType;
	SG_UINT	 TaskID;
	SG_INT	 RtuID;
	SG_INT   s_YMD;
	SG_INT   e_YMD;
	int buf_size()
	{
		return sizeof(DatType)+sizeof(TaskID)+sizeof(RtuID)+sizeof(s_YMD)
			+sizeof(e_YMD);
	};
	void serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>DatType;
			ar>>TaskID;
			ar>>RtuID;
			ar>>s_YMD;
			ar>>e_YMD;
		}
		else
		{
			ar<<DatType;
			ar<<TaskID;
			ar<<RtuID;
			ar<<s_YMD;
			ar<<e_YMD;
		}
	};
}S_COMMTASK_HISHEAD;


typedef struct S_HIS_DAT
{
	SG_INT  PointID;
	SG_INT  YMD;
	SG_INT  HMS;
	SG_USHORT Flag;
	SG_INT  Status;
	SG_DOUBLE  Value;
	int buf_size()
	{
		return sizeof(PointID)+sizeof(YMD)+sizeof(HMS)
		+sizeof(Flag)+sizeof(Status)+sizeof(Value);
	};
	void serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>PointID;
			ar>>YMD;
			ar>>HMS;
			ar>>Flag;
			ar>>Status;
			ar>>Value;
		}
		else
		{
			ar<<PointID;
			ar<<YMD;
			ar<<HMS;
			ar<<Flag;
			ar<<Status;
			ar<<Value;
		}
	}
}S_HIS_DAT;

#define IDP_MAILTYPE_DELTMPHISDB		1  //ɾ��������ʷ�����ʼ�
#define IDP_MAILTYPE_SGEVENT			2  //����SG����ʱ��
typedef struct 
{
	int	MailType;
	int MailType2;   //MailType=MailType2,Ϊ�˰�ȫ
	int VerNo;
	void serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>MailType;
			ar>>MailType2;
			ar>>VerNo;
		}
		else
		{
			ar<<MailType;
			ar<<MailType2;
			ar<<VerNo;
		}
	};
	int buf_size()
	{
		return sizeof(MailType)+sizeof(MailType2)+sizeof(VerNo);
	};
}S_IDPCOMMON_MAILHEAD;
typedef struct 
{
	int YMD;
	int PointID;
	int Flag;		//0:����ֵ  1:ͳ��ֵ
	void serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>YMD;
			ar>>PointID;
			ar>>Flag;
		}
		else
		{
			ar<<YMD;
			ar<<PointID;
			ar<<Flag;
		}
	};
	int buf_size()
	{
		return sizeof(YMD)+sizeof(PointID)+sizeof(Flag);
	}
	
}S_FERT_HISDATINFO;

typedef struct S_BAK_POINTVAL
{
	SG_INT  PointID;
	SG_INT  Status;
	SG_INT  LastUpdate_Time;
	SG_INT  LastUpdate_Ms;
	SG_DOUBLE  Value;	
	SG_DOUBLE  SaveValue;	
	SG_DOUBLE  MarkValue;	
}S_BAK_POINTVAL;
enum SG_RDP_SG_EVENTTYPE_DEF
{
	SG_RDP_SG_EVENTTYPE_LINE_GLEAM		=1,		//��·˲ʱ��բ
	SG_RDP_SG_EVENTTYPE_LINE			=2,		//��·������բ
	SG_RDP_SG_EVENTTYPE_LINE_LNKGROUND	=3,		//��·�ӵػ�г��
	SG_RDP_SG_EVENTTYPE_TRANS			=4,		//��ѹ������
	SG_RDP_SG_EVENTTYPE_BUS				=5,		//ĸ�߹���
	SG_RDP_SG_EVENTTYPE_CAP				=6,		//����������
	SG_RDP_SG_EVENTTYPE_DSCADA_YX		=100,	//���������,���ر�λ
	SG_RDP_SG_EVENTTYPE_DSCADA_YC		=101	//���������,YCͻ��
	
};
//==================================================================================================

//==================================================================================================
#define		EVENT_SOURCE_DPS 0x02	//	DPS
#define		EVENT_SOURCE_OPER 0x03	//	DPS
#define		EVENTCLASS_SOURCE_CPLAT 0x04	//	ƽ̨

#define     EVENT_SET_VALUE   33  //�˹��趨
#define     EVENT_LOCK_VALUE  34  //�˹�����

//==================================================================================================
#define     EVENT_CHANGE_DASI			10  //״̬���¼�����λ��
#define     EVENT_OVERLIMIT_DASF		11  //
#define     EVENT_ANA_BIGCHANGE			12  //ң��ͻ��
#define     EVENT_DIG_NEEDCONFIRM		13  //ң��ȷ��
#define     EVENT_CHANGE_DASI_STAT		14  //����״̬�仯
#define     EVENT_OVERLIMIT_DASF_EXSYS	15  //ң��Խ��,ǰ���͹�����
#define     EVENT_ACC_MARK_FLY			16  //�������
#define     EVENT_ACC_MARK_BACK			17  //���뵹��
#define     EVENT_SOE_DASI_RTU			18  //ǰ���͹�����SOE����
#define     EVENT_RTU_ERREVT			19  //�ն˹�����Ϣ
#define     EVENT_MINIBOX_CONFLICT		213  //΢���ӳ�ͻ,ͬһ��վ��������ͬ�ڵ�ID��΢�����ڴ���
#define     EVENT_CENTERNET				205  //��������״̬
#define     EVENT_ACC_MARK_RESUM		41  //����ָ�

/*
enum SG_RDP_EVENT_CLASS_DEF
{
	RDP_EVENT_CLASS_STATE		=0,  //״̬������
	RDP_EVENT_CLASS_ANALOG		=1,	 //ģ��������
	RDP_EVENT_CLASS_SYS			=2	 //ϵͳ����
};
enum SG_RDP_EVENT_TYPE_DEF
{
	RDP_EVENT_TYPE_YXC_NOMAL		=0, //ң��������λ
	RDP_EVENT_TYPE_YXC_SG			=1, //ң���¹ʱ�λ
	RDP_EVENT_TYPE_YXC_GISMANSET	=2, //�ɱ�ϵͳ����ң�ű�λ
	RDP_EVENT_TYPE_YXC_MANSET		=3, //ң��������λ
	RDP_EVENT_TYPE_YXC_VERIFY		=4, //����ң�ű�λ,����Աȷ�ϱ�λ����
	RDP_EVENT_TYPE_YXC_SOE			=5, //ң��SOE��λ
	
	RDP_EVENT_TYPE_YXC_PROT			=8, //�����ź���Ϣ
	
	RDP_EVENT_TYPE_YC_UP_LIMIT		=100, //ң��Խ����
	RDP_EVENT_TYPE_YC_UP_NORMAL		=101, //ң��Խ���޻ָ�
	RDP_EVENT_TYPE_YC_DOWN_LIMIT	=102, //ң��Խ����
	RDP_EVENT_TYPE_YC_DOWN_NORMAL	=103, //ң��Խ���޻ָ�
	
	RDP_EVENT_TYPE_SYS_PARAC		=200,	 //RDP�����仯����,�յ�RDP���͵Ĳ����ļ�
	RDP_EVENT_TYPE_SYS_YXMANSET		=201,	 //ң������
	RDP_EVENT_TYPE_SYS_GISYXMANSET	=202,	 //GISң������
	RDP_EVENT_TYPE_SYS_YCMANSET	=203	 //ң������
};
*/
typedef struct  {
	SG_INT		ID;
	SG_SHORT	Flag;
	SG_INT		YMD;
	SG_INT		HMS;
	SG_SHORT	Ms;
	SG_SHORT	EventClass;
	SG_SHORT	EventType;
	SG_SHORT	CompanyID;
	SG_SHORT	DevType;//�豸����
	SG_INT		DevID;
	SG_INT		PointID;
	SG_SHORT	OldVal;
	SG_DOUBLE	Val;
	SG_CHAR		Append[255];
	int buf_size()
	{ 
		return sizeof(ID)+sizeof(Flag)+sizeof(YMD)+sizeof(HMS)+sizeof(Ms)
			+sizeof(EventClass)+sizeof(EventType)+
			+sizeof(CompanyID)+sizeof(DevType)+sizeof(DevID)+
			sizeof(PointID)+sizeof(OldVal)+sizeof(Val)+sizeof(Append);
	};
	void serialize(CSgArchive &ar)
	{ 
		if(ar.IsLoading())
		{
			ar>>ID;
			ar>>Flag;
			ar>>YMD;
			ar>>HMS;
			ar>>Ms;
			ar>>EventClass;
			ar>>EventType;
			
			ar>>CompanyID;
			ar>>DevType;
			ar>>DevID;
			ar>>PointID;
			ar>>OldVal;
			ar>>Val;
			ar.Read(Append,sizeof(Append));
		}
		else
		{
			ar<<ID;
			ar<<Flag;
			ar<<YMD;
			ar<<HMS;
			ar<<Ms;
			ar<<EventClass;
			ar<<EventType;
			
			ar<<CompanyID;
			ar<<DevType;
			ar<<DevID;
			ar<<PointID;
			ar<<OldVal;
			ar<<Val;
			ar.Write(Append,sizeof(Append));
		}
	};
}S_HIS_EVENT;

enum SG_EVTMAILTYPE
{
	EVTMAILTYPE_YXCONFIRM=1,
	EVTMAILTYPE_YXCHANGE=2, 
	EVTMAILTYPE_YC_OVER_LIMIT=3 
	
};

typedef struct 
{

	int EvtMailType;
	union
	{
		S_HIS_EVENT	Base_Event;
	};
	int buf_size()
	{
		int len=0;
	   switch(EvtMailType)
	   {
	   case EVTMAILTYPE_YXCONFIRM:
	   case EVTMAILTYPE_YXCHANGE:
	   case EVTMAILTYPE_YC_OVER_LIMIT:
		   len=sizeof(EvtMailType)+Base_Event.buf_size();
		   break;
	   default:
		   break;
	   }
		return len;
	};
	int serialize(CSgArchive &ar)
	{
		if(ar.IsLoading())
		{
			ar>>EvtMailType;
			switch(EvtMailType)
			{
			case EVTMAILTYPE_YXCONFIRM:
			case EVTMAILTYPE_YXCHANGE:
			case EVTMAILTYPE_YC_OVER_LIMIT:
				Base_Event.serialize(ar);
				break;
			default:
				return false;
				break;
			}
		}
		else
		{
			switch(EvtMailType)
			{
			case EVTMAILTYPE_YXCONFIRM:
			case EVTMAILTYPE_YXCHANGE:
			case EVTMAILTYPE_YC_OVER_LIMIT:
				ar<<EvtMailType;
				Base_Event.serialize(ar);
				break;
			default:
				return false;
				break;
			}

		}
		return true;
	}
		
}SSG_MAIL_EVENT;
typedef enum	COMMRTU_DEF_TASKTYPE
{
	COMMRTU_TASKTYPE_SETMETERINFO=1,	//���ò�������Ϣ
	COMMRTU_TASKTYPE_CALLHISDAT_BYPTID=2,	//���ݲ��ID�ٻ���ʷ���� Obj1:SubStationID Obj2:��Ų������ObjType 500:yc 502:kwh 
	COMMRTU_TASKTYPE_CALLHISDAT_BYMETERNO=3,	//���ݲ����� ���������ٻ���ʷ���� Obj1:SubStationID Obj2:��������  Obj3:MeterNo Obj4:���̼��
	COMMRTU_TASKTYPE_GETMETERINFO=4,	//�ٻ������Ϣ
	COMMRTU_TASKTYPE_YK=5,				//ObjID=PointID Obj0:SubStationID  Obj1:PointNo Obj2:OperType Obj3:����ֵ Obj4:YKNo
	COMMRTU_TASKTYPE_YT=6,				//ObjID=PointID Obj0:SubStationID Obj1:PointNo  Obj2:OperType Obj3:����ֵ Obj4:YKNo 
	COMMRTU_TASKTYPE_REQ_PHOTO=7,		//�������� Obj1:SubStationID ObjID2 �ն�ͨ���� Obj3:�ն�Ԥ��λ�ú�  
	COMMRTU_TASKTYPE_MINIBOX_SENDREAL=8, //΢���ӷ���ʵʱ���ݣ�Obj1:SubStationID,Obj2:������־ 1:���� 0:ֹͣ Obj3:����Ƶ�� ȱʡ5�� Obj4:���ͳ���ʱ��,ȱʡ����300��  
	COMMRTU_TASKTYPE_MINIBOX_UPDATEDB=9, //΢�����������ݿ⣬Obj1:SubStationID
	COMMRTU_TASKTYPE_ASKGPSPOS=10,		//����GPSλ����Ϣ
	COMMRTU_TASKTYPE_MCUADDRCHANGE=11,		//MCU��485��ַ��ı䣬��Ҫ���͵�Rtu�� ��Obj1:SubStationID Obj2:SlaveRtuID Obj3:OperType 1���� 2ɾ�� 3�޸�
	COMMRTU_TASKTYPE_CALLFILE=12,	//�ٻ��ļ� Obj1:SubStationID Obj2:�ն�ID  Obj3:�ļ�����  1:¼���ļ� 2:�����ļ�
	COMMRTU_TASKTYPE_FRCD_CMD = 13,	//�������·����� ObjID=PointID Obj1:SubStationID  Obj2:OperType 1 yk Obj3:����ֵ1 Obj4:����ֵ2 Obj5:����ֵ3
	COMMRTU_TASKTYPE_SETPT = 14,	//΢�����·��������� ObjID=PointID Obj1:SubStationID  Obj2:ObjType 500 501 502  Obj3:OperType Obj4:����ֵ(float)�洢 
}COMMRTU_DEF_TASKTYPE;
//ǰ��������Ϣ
typedef struct S_COMMRTU_TASKINFO
{
	int TaskID;		//�����
	int TaskType;	//��������
	int	ObjID;		//����Ķ���ID
	int	StartYMD;	//��ȡ��ʼ������
	int	StartHMS;	//��ȡ��ʼʱ����
	int EndYMD;		//��ȡ��ֹ������
	int EndHMS;		//��ȡ��ֹʱ����
	int Obj[5];		//�������  ������������,���ò�ͬ����Ϣ �����ɼ���������� Obj[0]����SubStationID
	S_COMMRTU_TASKINFO()
	{
		TaskID=0;
		TaskType=0;
		ObjID=0;
		StartYMD=EndYMD=0;
		StartHMS=EndHMS=0;
		for(int i=0;i<5;i++)
			Obj[i]=0;		
	};
	void operator = (const S_COMMRTU_TASKINFO &obj)
	{
		TaskID=obj.TaskID;
		TaskType=obj.TaskType;
		ObjID=obj.ObjID;
		StartYMD=obj.StartYMD;
		StartHMS=obj.StartHMS;
		EndYMD=obj.EndYMD;
		EndHMS=obj.EndHMS;
		for(int i=0;i<5;i++)
			Obj[i]=obj.Obj[i];		
	};
	SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1)
	{
		int i;
		if(ar.IsLoading())
		{
			ar>>TaskID;
			ar>>TaskType;
			ar>>ObjID;
			ar>>StartYMD;
			ar>>StartHMS;
			ar>>EndYMD;
			ar>>EndHMS;
			for(i=0;i<5;i++)
				ar >> Obj[i];
		}
		else
		{
			ar<<TaskID;
			ar<<TaskType;
			ar<<ObjID;
			ar<<StartYMD;
			ar<<StartHMS;
			ar<<EndYMD;
			ar<<EndHMS;
			for(i=0;i<5;i++)
				ar << Obj[i];
		}
		return true;
	};
	int buf_size()
	{
		return sizeof(TaskID)+sizeof(TaskType)+sizeof(ObjID)+sizeof(StartYMD)+sizeof(StartHMS)
			+sizeof(EndYMD)+sizeof(EndHMS)+5*sizeof( Obj[0]);
	};
}S_COMMRTU_TASKINFO;

#endif