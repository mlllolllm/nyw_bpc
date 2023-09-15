//------------------------------------------------------------------------------
// 定义scd处理的基础数据
//------------------------------------------------------------------------------

#ifndef _RDPBASEDEF_HHH_
#define _RDPBASEDEF_HHH_
#include "sgarchive.h"
#include "sgdataset.h"
//#include "sgmicro.h"
//#include "rdp_const.h"

//#define RDP_FERT_MAX_EXTSYSNUM 128

#define RDP_DELAY_YXEVENT_TIME       20  //变位事项延迟报的时间

#define RDP_HISTABNAME_HEAD_YC			"HISDAT"
#define RDP_HISTABNAME_HEAD_YX			"HISDATDIG"
#define RDP_HISTABNAME_HEAD_KWH			"HISDATACC"
#define RDP_HISTABNAME_HEAD_PLAN		"SG_HISDAT_PLAN"
#define RDP_HISTABNAME_HEAD_EVENT		"HIS_EVENT"
#define RDP_HISTABNAME_HEAD_MANUAL_YC	"SG_HISDAT_MANUAL"

#define RDP_HISTAB_YCID_SECTION		10000		//每张历史表中YC点ID的范围
#define RDP_HISTAB_YXID_SECTION		500000		//每张历史表中YX点ID的范围
#define RDP_HISTAB_KWHID_SECTION		10000	//每张历史表中KWH点ID的范围
#define RDP_HISTAB_MANUALYCID_SECTION	100000		//每张历史表中抄表YC点ID的范围

#define SG_RDP_SAVE_FILE_HEAD "SG_RDP_FILE229"
#define SG_RDP_PARA_FILE_HEAD "--SG_PARA_DATAFMT: "

#define RDP_FILETYPE_PROCHISDATE	0 //处理历史数据最后时间文件
#define RDP_FILETYPE_SENDHISDAT		1 //发送历史数据文件
#define RDP_FILETYPE_SAVEHISDAT		2 //中央服务器的存盘历史数据文件
#define RDP_FILETYPE_SAVETMPHISDAT	3 //二级服务器的缓存历史数据文件
#define RDP_FILETYPE_BAK_POINTVAL	4 //备份值表的信息
#define RDP_FILETYPE_PROCHISDATE_OLD	5 //新的处理历史数据最后时间文件
#define RDP_FILETYPE_CALLHISINFO	6 //召唤历史数据的信息文件
#define RDP_FILETYPE_RTUSTATUS		8 //自动化系统状态信息文件
#define RDP_FILETYPE_PTPROCTIME		9 //测点增量读取时间文件
#define RDP_FILETYPE_CALLPROCINFO	10 //统计存储过程调用信息
#define RDP_FILETYPE_RECVHISDAT		11 //中央服务器的接受到的历史数据文件
#define RDP_FILETYPE_HISCHANPROCTIME		12  //历史测点变更读取时间文件
#define RDP_FILETYPE_HISOPERMODE		13  //历史运行方式文件
#define RDP_FILETYPE_HIGHLOADINFO		15  //最高负荷信息文件
#define RDP_FILETYPE_LACKHISDATINFO     16  //自动化系统历史数据文件缺失情况文件
#define RDP_FILETYPE_CHANYXERR          17  //变化遥信过多情况文件
#define RDP_FILETYPE_HISTBLCHANLOG	18 //历史表变更信息
#define RDP_FILETYPE_SENDHISDAT_NEW		19 //发送历史数据文件
#define RDP_FILETYPE_SENDRTUSOE		20 //存储soe文件
#define RDP_FILETYPE_MODIFYPTINFO	21 //历史测点修改信息

#define RDP_FILETYPE_SAVEHISDAT_CLOUD	25 //云服务存盘历史数据文件
#define RDP_FILETYPE_SAVEPARADAT_CLOUD	26 //云服务存储参数表的信息

#define RDP_FILETYPE_SAVEEVENT_CLOUD		27 //云服务存历史事项文件
#define RDP_FILETYPE_SAVEEVENTLIST_CLOUD	34 //云服务存历史事项文件

#define RDP_FILETYPE_RTDBINFO_CLOUD		28 //云服务实时数据库信息文件
#define RDP_FILETYPE_RTTBL_CLOUD		29 //云服务实时数据表文件
#define RDP_FILETYPE_SENDHISDAT_CLOUD	30 //发送历史数据文件
#define RDP_FILETYPE_SENDRAWEVT_CLOUD	31 //云服务发送的生数据文件
#define RDP_FILETYPE_DEMANDBAKFILE		32 //需量备份文件
#define RDP_FILETYPE_RTTBL_DATVAL		33 //云服务实时数据值表文件
#define RDP_FILETYPE_POWERBAKFILE		34 //功率备份文件
#define RDP_FILETYPE_SAVE_EVTMSG		35 //云服务存储事项消息文件
#define RDP_FILETYPE_RTTBL_EVTINFO		36 //云服务实时事项表信息
#define RDP_FILETYPE_DBOPER				37 //数据库操作文件
#define RDP_FILETYPE_FERTSENDFILE		38 //前置采集来的文件（如录波等文件）
#define RDP_FILETYPE_MQTT_TOPICNAME		39 //MQTT的主题名称信息
#define RDP_FILETYPE_MQTT_TOPICINFO		40 //MQTT的主题信息文件
#define RDP_FILETYPE_MQTT_MSGDAT		41 //MQTT的消息文件
#define RDP_FILETYPE_RAWBAGINFO			42 //聚合事项信息
#define RDP_FILETYPE_MINIBOX_RECVCMD	43 //微盒子上收到的下发命令
#define RDP_FILETYPE_RTDB_CLOUD			44 //云服务实时数据库文件

#define SG_RDP_SAVE_FILE_VERSION	1
typedef struct S_SG_RDP_FILE_HEAD
{
	char Version[60];
	short int  FileType;
	short int  VerNo;
	short int  ProcMode;	//0:正常处理  1:历史数据不记录统计变更信息
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
#define SAVEFILE_INSERTDB_MODE_BATCH_INSERT		0	//首先采用批插入，不成功后删除记录后，插入
#define SAVEFILE_INSERTDB_MODE_DEL_INSERT		1	//删除记录后，插入
#define SAVEFILE_INSERTDB_MODE_KEYDEL_INSERT	2	//按主键删除后,进行批插入
#define SAVEFILE_INSERTDB_MODE_DELETE			3	//删除记录
#define SAVEFILE_INSERTDB_MODE_EVT_INSERT			4	//事项插入模式，单条插入，如果有原有纪录，则将PROCSTATUS字段或后存储
typedef struct S_SG_SAVEFILE_INSERTDBINFO
{
	int			InsertMode;			//0:首先采用批插入，不成功后删除记录后，插入
									//1:删除记录后，插入
									//2:按主键删除后,进行批插入
									//3:删除记录
	int			KeyFieldFlag;			//0: 按数据库主键
										//1:按KeyFieldName中记录为主键
	int			WorkSpace;				//存储WorkSpace号
	int			SectionID;				//存储SectionID号
	CSgString	TblHeadName;	//历史数据,历史表的基本名称,不带年月的表名
	CSgString	SeqenceName;	//插入时使用的sequece名称，带用户名
	CSgString	SeqFieldName;	//插入时使用的sequece字段
	CSgStringArray KeyFieldName; //主键字段名称
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
}S_SG_SAVEFILE_INSERTDBINFO;  //文件->数据库插入的相关操作信息

typedef struct
{
	short int  ExSysID;
	short int  res;
	SG_Date  ProcDate;
	SG_Date  CurProcDate;  ////如果有重召，这是重召结束后应该召唤的起始时间
	int		 ReRead_STime; //重读的绝对秒的起始时间
	int		 ReRead_ETime; //重读的绝对秒的终止时间
}S_HIS_PROCDATE;

typedef struct
{
	short int  ExSysID;
	short int  Status;
	int		   ProcTime;
}S_HIS_EXSYSSTATUS;
//运行日志中的事件类型
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

//数据库中测点变化增量中的测点类型定义
#define PTCHANGE_TYPE_YC			1
#define PTCHANGE_TYPE_YX			2
#define PTCHANGE_TYPE_KWH			3
#define PTCHANGE_TYPE_MANUAL_YC		4
#define PTCHANGE_TYPE_MANUAL_VAL	5
#define PTCHANGE_TYPE_SRVSEND_YC	6
#define PTCHANGE_TYPE_SRVSEND_YX	7
#define PTCHANGE_TYPE_SRVSEND_KWH	8
//数据库操作的定义
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
	int		PTChangeType;  //测点增量变化类型
	int		ProcTime;		//增量测点处理时间
}S_PT_PROCTIME;

//数据库表的测点类型
#define DBTBL_POINTTYPE_YC		0
#define DBTBL_POINTTYPE_YX		1
#define DBTBL_POINTTYPE_KWH	2
#define DBTBL_POINTTYPE_EVENT	3
#define DBTBL_POINTTYPE_MANUAL_YC	5
#define DBTBL_POINTTYPE_END		6

//数据库表的数据类型
#ifdef SG_CLOUD_RDP
#define	DBTBL_DATATYPE_SAVE		1	//定时存盘数据
#define	DBTBL_DATATYPE_D_STAT	2  //日统计数据
#define	DBTBL_DATATYPE_M_STAT	3  //月统计数据
#define	DBTBL_DATATYPE_Y_STAT	4  //年统计数据
#define	DBTBL_DATATYPE_PLAN		5		//计划数据
#define	DBTBL_DATATYPE_END		6	
#else
#define	DBTBL_DATATYPE_SAVE		1	//定时存盘数据
#define	DBTBL_DATATYPE_STAT		2  //统计数据
#define	DBTBL_DATATYPE_PLAN		3		//计划数据
#define	DBTBL_DATATYPE_END		4	
#endif
#define HIS_DATTYPE_YC		0
#define HIS_DATTYPE_YX		1
#define HIS_DATTYPE_KWH		2
#define HIS_DATTYPE_PLAN	3
#define HIS_DATTYPE_EVENT	4

#define HISHEAD_CALLFLAG_RECALL			0  //补召测产生的历史数据
#define HISHEAD_CALLFLAG_AUTO			1  //自动召收产生的历史数据 （YC OR KWH）
#define HISHEAD_CALLFLAG_AUTO_YCKWH		2  //自动召收产生的历史数据 （YC AND KWH）
#define HISHEAD_CALLFLAG_MODI			3  //修改产生的历史数据
#define HISHEAD_CALLFLAG_SELFSAVE		4  //自己存盘产生的历史数据
#define HISHEAD_CALLFLAG_HISCAL			5  //历史计算产生的历史数据
typedef struct 
{
	SG_UCHAR DatType;
	SG_UCHAR AutoCallFlag; //自动召收标志
	SG_UCHAR ModifyCallTimeFlag; //修改召测时间标志
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

#define IDP_MAILTYPE_DELTMPHISDB		1  //删除二级历史缓存邮件
#define IDP_MAILTYPE_SGEVENT			2  //发送SG处理时间
typedef struct 
{
	int	MailType;
	int MailType2;   //MailType=MailType2,为了安全
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
	int Flag;		//0:存盘值  1:统计值
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
	SG_RDP_SG_EVENTTYPE_LINE_GLEAM		=1,		//线路瞬时跳闸
	SG_RDP_SG_EVENTTYPE_LINE			=2,		//线路永久跳闸
	SG_RDP_SG_EVENTTYPE_LINE_LNKGROUND	=3,		//线路接地或谐振
	SG_RDP_SG_EVENTTYPE_TRANS			=4,		//变压器故障
	SG_RDP_SG_EVENTTYPE_BUS				=5,		//母线故障
	SG_RDP_SG_EVENTTYPE_CAP				=6,		//电容器故障
	SG_RDP_SG_EVENTTYPE_DSCADA_YX		=100,	//配电网故障,开关变位
	SG_RDP_SG_EVENTTYPE_DSCADA_YC		=101	//配电网故障,YC突变
	
};
//==================================================================================================

//==================================================================================================
#define		EVENT_SOURCE_DPS 0x02	//	DPS
#define		EVENT_SOURCE_OPER 0x03	//	DPS
#define		EVENTCLASS_SOURCE_CPLAT 0x04	//	平台

#define     EVENT_SET_VALUE   33  //人工设定
#define     EVENT_LOCK_VALUE  34  //人工锁定

//==================================================================================================
#define     EVENT_CHANGE_DASI			10  //状态量事件（变位）
#define     EVENT_OVERLIMIT_DASF		11  //
#define     EVENT_ANA_BIGCHANGE			12  //遥测突变
#define     EVENT_DIG_NEEDCONFIRM		13  //遥信确认
#define     EVENT_CHANGE_DASI_STAT		14  //开关状态变化
#define     EVENT_OVERLIMIT_DASF_EXSYS	15  //遥测越限,前置送过来的
#define     EVENT_ACC_MARK_FLY			16  //表码飞走
#define     EVENT_ACC_MARK_BACK			17  //表码倒走
#define     EVENT_SOE_DASI_RTU			18  //前置送过来的SOE事项
#define     EVENT_RTU_ERREVT			19  //终端故障信息
#define     EVENT_MINIBOX_CONFLICT		213  //微盒子冲突,同一个站点两个不同节点ID的微盒子在传送
#define     EVENT_CENTERNET				205  //中央网络状态
#define     EVENT_ACC_MARK_RESUM		41  //表码恢复

/*
enum SG_RDP_EVENT_CLASS_DEF
{
	RDP_EVENT_CLASS_STATE		=0,  //状态量事项
	RDP_EVENT_CLASS_ANALOG		=1,	 //模拟量事项
	RDP_EVENT_CLASS_SYS			=2	 //系统事项
};
enum SG_RDP_EVENT_TYPE_DEF
{
	RDP_EVENT_TYPE_YXC_NOMAL		=0, //遥信正常变位
	RDP_EVENT_TYPE_YXC_SG			=1, //遥信事故变位
	RDP_EVENT_TYPE_YXC_GISMANSET	=2, //由本系统置数遥信变位
	RDP_EVENT_TYPE_YXC_MANSET		=3, //遥信置数变位
	RDP_EVENT_TYPE_YXC_VERIFY		=4, //根据遥信变位,调度员确认变位事项
	RDP_EVENT_TYPE_YXC_SOE			=5, //遥信SOE变位
	
	RDP_EVENT_TYPE_YXC_PROT			=8, //保护信号信息
	
	RDP_EVENT_TYPE_YC_UP_LIMIT		=100, //遥测越上限
	RDP_EVENT_TYPE_YC_UP_NORMAL		=101, //遥测越上限恢复
	RDP_EVENT_TYPE_YC_DOWN_LIMIT	=102, //遥测越下限
	RDP_EVENT_TYPE_YC_DOWN_NORMAL	=103, //遥测越下限恢复
	
	RDP_EVENT_TYPE_SYS_PARAC		=200,	 //RDP参数变化事项,收到RDP发送的参数文件
	RDP_EVENT_TYPE_SYS_YXMANSET		=201,	 //遥信置数
	RDP_EVENT_TYPE_SYS_GISYXMANSET	=202,	 //GIS遥信置数
	RDP_EVENT_TYPE_SYS_YCMANSET	=203	 //遥测置数
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
	SG_SHORT	DevType;//设备类型
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
	COMMRTU_TASKTYPE_SETMETERINFO=1,	//设置测量点信息
	COMMRTU_TASKTYPE_CALLHISDAT_BYPTID=2,	//根据测点ID召唤历史数据 Obj1:SubStationID Obj2:存放测点类型ObjType 500:yc 502:kwh 
	COMMRTU_TASKTYPE_CALLHISDAT_BYMETERNO=3,	//根据测量点 量测类型召唤历史数据 Obj1:SubStationID Obj2:量测类型  Obj3:MeterNo Obj4:存盘间隔
	COMMRTU_TASKTYPE_GETMETERINFO=4,	//召唤表计信息
	COMMRTU_TASKTYPE_YK=5,				//ObjID=PointID Obj0:SubStationID  Obj1:PointNo Obj2:OperType Obj3:操作值 Obj4:YKNo
	COMMRTU_TASKTYPE_YT=6,				//ObjID=PointID Obj0:SubStationID Obj1:PointNo  Obj2:OperType Obj3:操作值 Obj4:YKNo 
	COMMRTU_TASKTYPE_REQ_PHOTO=7,		//请求拍照 Obj1:SubStationID ObjID2 终端通道号 Obj3:终端预设位置号  
	COMMRTU_TASKTYPE_MINIBOX_SENDREAL=8, //微盒子发送实时数据，Obj1:SubStationID,Obj2:启动标志 1:启动 0:停止 Obj3:发送频率 缺省5秒 Obj4:发送持续时间,缺省发送300秒  
	COMMRTU_TASKTYPE_MINIBOX_UPDATEDB=9, //微盒子升级数据库，Obj1:SubStationID
	COMMRTU_TASKTYPE_ASKGPSPOS=10,		//请求GPS位置信息
	COMMRTU_TASKTYPE_MCUADDRCHANGE=11,		//MCU的485地址码改变，需要发送到Rtu中 ，Obj1:SubStationID Obj2:SlaveRtuID Obj3:OperType 1新增 2删除 3修改
	COMMRTU_TASKTYPE_CALLFILE=12,	//召唤文件 Obj1:SubStationID Obj2:终端ID  Obj3:文件类型  1:录波文件 2:参数文件
	COMMRTU_TASKTYPE_FRCD_CMD = 13,	//充电插座下发命令 ObjID=PointID Obj1:SubStationID  Obj2:OperType 1 yk Obj3:操作值1 Obj4:操作值2 Obj5:操作值3
	COMMRTU_TASKTYPE_SETPT = 14,	//微盒子下发设置数据 ObjID=PointID Obj1:SubStationID  Obj2:ObjType 500 501 502  Obj3:OperType Obj4:操作值(float)存储 
}COMMRTU_DEF_TASKTYPE;
//前置任务信息
typedef struct S_COMMRTU_TASKINFO
{
	int TaskID;		//任务号
	int TaskType;	//任务类型
	int	ObjID;		//任务的对象ID
	int	StartYMD;	//读取起始年月日
	int	StartHMS;	//读取起始时分秒
	int EndYMD;		//读取终止年月日
	int EndHMS;		//读取终止时分秒
	int Obj[5];		//任务对象  根据任务类型,放置不同的信息 发往采集服务的命令 Obj[0]放置SubStationID
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