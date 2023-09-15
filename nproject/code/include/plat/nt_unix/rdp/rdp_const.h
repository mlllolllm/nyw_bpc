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
	short		DeviceType;		//设备类型
	int		    DeviceID;		//设备ID
	short		Terminal;		//端子号
	short		MeasType;		//量测类型

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
typedef char SG_HOMEPATHNAME[256];			//根目录位置结构

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
//在sun 上，strcasecmp有问题
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
//在sun 上，strcasecmp有问题
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
#define RDPRET_OPENRDB_ERR 2  //打开实时库失败
#define RDPRET_NOTIN_RDB   3 //点在实时库中不存在

#define RDP_HDB_DSNAME		"HDBSrv"
#define SG_RDB_VERNO			2	//当前实时库的版本号


//实时库表的名称
#define RTBL_PROTOCOLTYPE  "PROTOCOL"  //
#define RTBL_EXSYS_PROTTYPE  "EXSYS_PROT"  //外部系统规约库
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
#define RTBL_EXSYS  "EXTERNSYS"					//仅在二级数据库加载
#define RTBL_POSITTION  "Position"
#define RTBL_ANALOG_ZF  "ZF_ANA"
#define RTBL_STATE_ZF  "ZF_DIG"
#define RTBL_ACC_ZF  "ZF_ACC"

#define RTBL_MEASTYPE  "meastype"
#define RTBL_STATDESC  "statdesc"

//实时库中事项表的循环最大数,大于次数时 Circuit=1
#define RTBL_EVENT_MAXCIRCUITNUM 99999999


//点的质量信息各位的定义 点的质量信息只有低三个字节有效，
//最高一个字节为遥信的生数据位
//最低一个字节为scd传来的状态位
#define RDP_POINT_STATUS_INVALID		0x00000001  //1:无效  0:有效
#define RDP_POINT_STATUS_ACTIVE			0x00000002  //1:死数  0:正常
#define RDP_POINT_STATUS_MANSET			0x00000004  //1:人工置数 0:实时
#define RDP_POINT_STATUS_SOE			0x00000008	//1:异常值 0:正常值
#define RDP_POINT_STATUS_RTU_OVERLIMIT	0x00000010	//1:测点是否越限
#define RDP_POINT_STATUS_RTU_OVERLIMIT2	0x00000020  //1:测点越二级限
#define RDP_POINT_STATUS_RTU_UPLIMIT	0x00000040  //1:测点越上限,如果越限，不是越上限就是越下限
#define RDP_POINT_STATUS_RTU_OVERLIMIT3	0x00000080  //1:测点越三级限

#define RDP_POINT_STATUS_GISMANSET		0x00000100  //1:系统人工置数 0:实时
#define RDP_POINT_STATUS_NEEDCONFIRM	0x00000200  //1:遥信变位需要确认 0:正常
#define RDP_POINT_STATUS_TJFROMRDP		0x00000400  //1:该统计值来自于RDP系统 0:统计值是由本系统产生
#define RDP_POINT_STATUS_IDPDEAD		0x00000800  //1:idp死数  0:idp正常
//统计值得优先登记为自动化送来的统计值最高，表码统计值次之  正常统计值最低
#define RDP_POINT_STATUS_TJFROM_MARK	0x00001000  //1:该统计值由表码值统计生成 0:正常统计值
#define RDP_POINT_STATUS_OVERLIMIT		0x00002000  //1:测点是否越限
#define RDP_POINT_STATUS_OVERLIMIT2		0x00004000  //1:测点越二级限
#define RDP_POINT_STATUS_UPLIMIT		0x00008000  //1:测点越上限,如果越限，不是越上限就是越下限
#define RDP_POINT_STATUS_OVERLIMIT3		0x00010000  //1:测点越三级限
#define RDP_POINT_STATUS_HISDAT_MANSET	0x00020000  //1:该测点由人工修改获得，非从自动化系统获得
#define RDP_POINT_STATUS_HISDAT_CAL		0x00040000  //1:该测点历史数据由计算产生
#define RDP_POINT_STATUS_ABNORMITY		0x00080000  //1:该测点数据不合理，不参与统计处理
#define RDP_POINT_STATUS_STATWARNING	0x00100000  //1:该测点历史数据统计时,有Warning出现
#define RDP_POINT_STATUS_GMANCANCEL		0x00200000	//1:GIS置数刚刚解除 0:正常值

//#define RDP_POINT_STATUS_JIANXIU		0x00200000  //1:检修
//#define RDP_POINT_STATUS_SG			0x00400000  //1:事故 

//#define RDP_POINT_STATUS_YXRAWVAL		0xFC000000	//高6位是遥信的值 (0~63)

//#define RDP_POINT_STATUS_NEWDAT			0x00400000	//1:新上的测点      0:老测点
//#define RDP_POINT_STATUS_GMANCANCEL		0x02000000	//1:GIS置数刚刚解除 0:正常值
//#define RDP_POINT_STATUS_SAVE_MARK		0x01000000	//1:需要保存表码值 0：已保存
/*
enum SHARE_MEMORY_RECORD_LIMIT_CLOUD
{
	CLOUD_SMRL_NORMAL			= 0x00000000 ,		//	正常
	CLOUD_SMRL_LIMIT_H		= 0x00000005 ,		//	越上限	(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_UPLIMIT)/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_L		= 0x00000001 ,		//	越下限	RDP_POINT_STATUS_OVERLIMIT/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_HH		= 0x00000007 ,		//	越上上限(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_OVERLIMIT2|RDP_POINT_STATUS_UPLIMIT)/RDP_POINT_STATUS_OVERLIMIT
	CLOUD_SMRL_LIMIT_LL		= 0x00000003 ,		//	越下下限(RDP_POINT_STATUS_OVERLIMIT|RDP_POINT_STATUS_OVERLIMIT2)/RDP_POINT_STATUS_OVERLIMIT
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
		unsigned char scd_status:4; //自动化系统传来的状态位
#else
		unsigned char scd_status:4;//自动化系统传来的状态位
		unsigned char bit4:4;
		unsigned char bit3;
		unsigned char bit2;
		unsigned char bit5:2;
		unsigned char rawval:6;
#endif
	}BitVal;
}S_PTSTATUS;

//量测类型的处理方式
//第0位:从正常状态->异常状态时,闭锁状态
//第1位:从异常状态->正常状态时,不报事项
//第2位:遥信直接进入实时库,不需要进行遥信确认
//第3位:遥信事项时,仅报新状态
//第4位:事项为保护事项
#define RDP_MT_PROCMODE_CHANLOCK		0x00000001  //1:从正常状态->异常状态时,闭锁  0:正常处理
#define RDP_MT_PROCMODE_CHANEVT			0x00000002  //1:从异常状态->正常状态时,不报事项  0:正常报事项
#define RDP_MT_PROCMODE_TORDB			0x00000004  //1:遥信直接进入实时库,不需要进行遥信确认 0:进入实时库,需要进行遥信确认
#define RDP_MT_PROCMODE_EVTNEWSTAT		0x00000008  //1:遥信事项时,仅报新状态  0:遥信事项时,报旧状态->新状态
#define RDP_MT_PROCMODE_PROTECT			0x00000010  //1:事项为保护事项  0:为遥信事项
#define RDP_MT_PROCMODE_CRTSG			0x00000020  //1:该类参与判别量测类型判别事故
//#define RDP_MT_PROCMODE_JUDGELIMIT		0x00000040  //1:该测点判断测点限值
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
	SG_RDP_MAILTYPE_DBPARACHAN			=0, //数据库参数表发生变化
		SG_RDP_MAILTYPE_PFILE2DB			=1, //将参数文件写入数据库中
		SG_RDP_MAILTYPE_CALLRDPPARA			=2, //召唤自动化系统参数文件
		SG_RDP_MAILTYPE_CALLJCDATA			=3, //召唤集抄数据
		SG_RDP_MAILTYPE_FORCELOADRDB		=4, //强制重新加载某个参数表
		SG_RDP_MAILTYPE_RECALLHISDAT		=5, //重召某一段时间的遥测历史数据
		SG_RDP_MAILTYPE_SYNCIDCHANGE		=6, //设备调换后更改测点参数信息
		SG_RDP_MAILTYPE_DBRCDSYNC			=7, //数据库参数变化，增量加载
		SG_RDP_MAILTYPE_CALLPTHISDAT		=8, //重召某测点某一段时间的历史数据
		SG_RDP_MAILTYPE_RETINFO_TOCLIENT	=9, //返回给客户端的信息
		SG_RDP_MAILTYPE_CALLPTHISDAT_NEW	=10, //重召某测点某一段时间的历史数据
		SG_RDP_MAILTYPE_CALLRTUSTAT			=11, //客户端察看自动化系统的连接状况
		SG_RDP_MAILTYPE_CALLRTUSTAT_RET		=12, //客户端察看自动化系统的连接状况返回信息
		SG_RDP_MAILTYPE_RTDBLOADOK			=13, //实时库加载完成信息
		SG_RDP_MAILTYPE_BACKEVT2FILE		=14, //备份事项到文件
		SG_RDP_MAILTYPE_RESTOREEVTFROMFILE	=15, //从文件加载备份事项到实时库表
		SG_RDP_MAILTYPE_MCUCHANGE			=16, //对mcu变化的设置
		SG_RDP_MAILTYPE_TESTCHECKRDB		=17, //检查实时库
		SG_RDP_MAILTYPE_LOADRDB				=18, //加载实时库表
};
enum SG_RDP_MAILPROC_CALLPTHIS_STEP
{
	SG_RDP_MAILPROC_STEP_RECV_OK			=1, //收到邮件
	SG_RDP_MAILPROC_STEP_CALLHIS_OK			=2, //抄收历史数据成功
	SG_RDP_MAILPROC_STEP_CALLHIS_ERR		=3, //抄收历史数据失败
};
typedef union 
{
	int IntVal;
	struct 
	{
#if defined(__sun)||defined(_AIX)
		unsigned char Res[2];		//保留
		unsigned char XBCS;			//谐波分量或费率  0:为有效值  1:为基波  255:总畸变率 254:偶次谐波总 253:奇次谐波总   
		unsigned char StatFlag;		//统计类型
#else
		unsigned char StatFlag;		//统计类型
		unsigned char XBCS;			//谐波分量或费率 0:为有效值  1:为基波  255:总畸变率 254:偶次谐波总 253:奇次谐波总
		unsigned char Res[2];		//保留
#endif
	}BitVal;
}USG_RDP_STATFLAG;

typedef struct S_RAW_EVENT
{
	SG_INT		YMD;		//年月日
	SG_INT		HMS;		//时分秒
	SG_SHORT	Ms;			//毫秒
	SG_SHORT	EvtClass;	//事项分类
	SG_INT		EvtType;	//事项类型
	SG_INT		ObjType;	//设备类型
	SG_INT		ObjID;		//设备类型
	SG_DOUBLE	NewVal;		//新值
	SG_INT		NewStatus;	//新数据质量码
	SG_DOUBLE	OldVal;		//旧值
	SG_INT		OldStatus;	//旧数据质量码
	SG_INT		EvtObj[5];	//事项对象信息值
	SG_INT		WorkSpace;	//工作空间
	SG_INT		Substation;	//电站ID
	SG_CHAR		Msg[64];		//事项信息
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
#define RDP_EVTTYPE_PROCMODE_NOTSAVEDB			0x0001 //不存盘
#define RDP_EVTTYPE_PROCMODE_NOTWARNING			0x0002  //不告警
#define RDP_EVTTYPE_PROCMODE_CONFIRM			0x0004 //是否确认
#define RDP_EVTTYPE_PROCMODE_STATE				0x0008 //是否统计
#define RDP_EVTTYPE_PROCMODE_FLASH				0x0010 //是否闪烁
#define RDP_EVTTYPE_PROCMODE_VOICE				0x0020 //是否语音提示
#define RDP_EVTTYPE_PROCMODE_NEEDFREE			0x0040 //是否需解除
#define RDP_EVTTYPE_PROCMODE_AUTOCONFIRM		0x0080 //自动解除时就自动确认
#define RDP_EVTTYPE_PROCMODE_EVTBAG				0x0100 //事项聚合
//#define RDP_EVTTYPE_PROCMODE_EVTBAG_II			0x0200 //二级聚合

#define RDP_EVTDAT_PROCSTATUS_NEED_CONFIRM	0x0001   //需确认
#define RDP_EVTDAT_PROCSTATUS_NEED_FREE		0x0002   //需解除
#define RDP_EVTDAT_PROCSTATUS_NEED_STATE	0x0004   //需统计
#define RDP_EVTDAT_PROCSTATUS_PROC_CONFIRM	0x0100   //已确认
#define RDP_EVTDAT_PROCSTATUS_PROC_FREE		0x0200   //已解除
typedef union USG_EVTDAT_PROCSTATUS
{
	int IntVal;
	struct
	{
#if defined(__sun)||defined(_AIX)
		unsigned char EvtLevel:8;		//事项等级
		unsigned char Res:8;			//保留
		unsigned char ProcInfo;		//已经处理的内容
		unsigned char NeedProc;		//需要处理的项
#else
		unsigned char NeedProc;		//需要处理的项
		unsigned char ProcInfo;		//已经处理的内容
		unsigned char Res;			//保留
		unsigned char EvtLevel;		//事项等级
#endif
	}BitVal;
}USG_EVTDAT_PROCSTATUS;
typedef struct S_RDP_EVENT
{
	S_RAW_EVENT RawEvent;
	SG_INT		ProcStatus;	//状态
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
	SG_INT		YMD;		//年月日
	SG_INT		HMS;		//时分秒
	SG_SHORT	Ms;			//毫秒
	SG_INT		EvtType;	//事项类型
	SG_INT		ObjType;	//设备类型
	SG_INT		ObjID;		//设备类型
	SG_INT		WorkSpace;	//工作空间
	SG_INT		ProcStatus;	//状态,仅传送这次改动有效的位，收到该信息后，用事项的Event.ProcStatus|=S_RDP_EVT_NOTIFYMSG.ProcStatus
	SG_INT		ProcNodeID;	//发出消息的节点ID
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
#define SG_RDP_PTSRCTYPE_RTU			0		//测点数据来自于终端
#define SG_RDP_PTSRCTYPE_CALC			1		//测点数据来自于计算
#define SG_RDP_PTSRCTYPE_EXSYS			2		//测点数据来自于外部系统
#define SG_RDP_PTSRCTYPE_CALC_DEMAND	3		//测点数据来需量的计算
#define SG_RDP_PTSRCTYPE_CALC_MEASTYPE	4		//根据量测类型计算测点，如离散率等
#define SG_RDP_PTSRCTYPE_STATION_STAT	5		//测点数据来自于电站数据统计,测点的设备类型仅为OBJ_TEAM(团队) OBJ_COMPANY(公司)
#define SG_RDP_PTSRCTYPE_MANUAL			6		//测点数据来自于手工抄表
#define SG_RDP_PTSRCTYPE_CALC_ACC		7		//测点数据来自于积分电量
#define SG_RDP_PTSRCTYPE_CALC_POWER		8		//测点数据来自于用电量算功率
#define SG_RDP_PTSRCTYPE_CALC_STEAMENERGY		9		//测点数据来自于蒸汽能量计算

#define MEASTYPE_ACC_START 201   //电度量测类型的最小值

//自动化系统状态
#define SG_RDP_EXSYSSTATUS_OK   0  //通道正常
#define SG_RDP_EXSYSSTATUS_ERR  1  //通道故障

//存盘flag的定义
//yc
#define HISDAT_FLAG_REAL		0 //遥测实时值
#define HISDAT_FLAG_PLAN		1 //计划值
#define HISDAT_FLAG_H_KWH		2 //存盘间隔内电度
#define HISDAT_FLAG_MARK		3 //表码值
#define HISDAT_FLAG_REAL_MAX	4 //存盘间隔内实时最大值
#define HISDAT_FLAG_REAL_MIN	5 //存盘间隔内实时最小值
#define HISDAT_STATDAT_BEGIN    10
//以下均为统计量
#define HISDAT_FLAG_MAX			10 //日最大值
#define HISDAT_FLAG_MAX_T		11 //日最大值发生时
#define HISDAT_FLAG_MIN			12 //日最小值
#define HISDAT_FLAG_MIN_T		13 //日最小值发生时
#define HISDAT_FLAG_SUM			14 //总加值
#define HISDAT_FLAG_AVER		15 //平均值
#define HISDAT_FLAG_FHL			16  //负荷率
#define HISDAT_FLAG_HGL			17  //合格率
#define HISDAT_FLAG_PTNUM		18  //有效点个数

#define HISDAT_FLAG_MON_MAX		20 //月最大值
#define HISDAT_FLAG_MON_MAX_T	21 //月最大值发生时
#define HISDAT_FLAG_MON_MIN		22 //月最小值
#define HISDAT_FLAG_MON_MIN_T	23 //月最小值发生时
#define HISDAT_FLAG_MON_SUM		24 //月总加值
#define HISDAT_FLAG_MON_AVER	25 //月平均值
#define HISDAT_FLAG_MON_FHL		26  //月负荷率
#define HISDAT_FLAG_MON_HGL		27  //月合格率
#define HISDAT_FLAG_MON_PTNUM	28  //月有效点个数

#define HISDAT_FLAG_YEAR_MAX	30 //年最大值
#define HISDAT_FLAG_YEAR_MAX_T	31 //年最大值发生时
#define HISDAT_FLAG_YEAR_MIN	32 //年最小值
#define HISDAT_FLAG_YEAR_MIN_T	33 //年最小值发生时
#define HISDAT_FLAG_YEAR_SUM	34 //年总加值
#define HISDAT_FLAG_YEAR_AVER	35 //年平均值
#define HISDAT_FLAG_YEAR_FHL	36  //年负荷率
#define HISDAT_FLAG_YEAR_HGL	37  //年合格率
#define HISDAT_FLAG_YEAR_PTNUM	38  //年有效点个数

#define HISDAT_FLAG_REAL_DAY_MAX		40 //日实时最大值
#define HISDAT_FLAG_REAL_DAY_MIN		41 //日实时最小值
#define HISDAT_FLAG_SD_MAX				42 //时段最大值
#define HISDAT_FLAG_SD_MIN				43 //时段最小值

#define HISDAT_FLAG_REAL_MON_MAX		45 //月实时最大值
#define HISDAT_FLAG_REAL_MON_MIN		46 //月实时最小值

#define HISDAT_FLAG_REAL_YEAR_MAX			47 //年实时最大值
#define HISDAT_FLAG_REAL_YEAR_MIN			48 //年实时最大值

#define HISDAT_FLAG_DAY_OL_TIME			50  //日越限时间
#define HISDAT_FLAG_DAY_OL_CNT			51  //日越限次数
#define HISDAT_FLAG_MON_OL_TIME			52  //月越限时间
#define HISDAT_FLAG_MON_OL_CNT			53  //月越限次数
#define HISDAT_FLAG_YEAR_OL_TIME		64  //年越限时间
#define HISDAT_FLAG_YEAR_OL_CNT			65  //年越限次数
#define HISDAT_FLAG_SD_REAL_MAX				54 //时段实时最大值
#define HISDAT_FLAG_SD_REAL_MIN				55 //时段实时最小值

#define HISDAT_FLAG_DAY_EVT_S			56  //日事项统计
#define HISDAT_FLAG_MON_EVT_S			57  //月事项统计
#define HISDAT_FLAG_YEAR_EVT_S			58  //年事项统计

#define HISDAT_FLAG_REAL_MAN		60 //手抄实时值
#define HISDAT_FLAG_H_KWH_MAN		62 //手抄存盘间隔内电度
#define HISDAT_FLAG_MARK_MAN		63 //手抄表码值

#define HISDAT_FLAG_DAY_DISTANCE		66 //日距离
#define HISDAT_FLAG_MON_DISTANCE		67 //月距离
#define HISDAT_FLAG_YEAR_DISTANCE		68 //年距离

//#define HISDAT_FLAG_DAY_RUN_TIME		69 //日运行时间
//#define HISDAT_FLAG_MON_RUN_TIME		70 //月运行时间
//#define HISDAT_FLAG_YEAR_RUN_TIME		71 //年运行时间

#define HISDAT_FLAG_DAY_KWH		100 //日电度
#define HISDAT_FLAG_MON_KWH		101 //月电度
#define HISDAT_FLAG_YEAR_KWH	102 //年电度
#define HISDAT_FLAG_SD_KWH		103 //时段电度


#define HISDAT_FLAG_KWH_FEE_CUR			110		// 当前费率
#define HISDAT_FLAG_MON_KWH_FEE_CUR		111		// 当月费率电度
#define HISDAT_FLAG_MON_KWH_FEE_LAST	112		// 上月费率电度
#define HISDAT_FLAG_MON_KWH_FEE_LL		113		// 上上月费率电度

#define HISDAT_FLAG_DAY_KWH_PTNUM		117 //日电度有效点个数
#define HISDAT_FLAG_MON_KWH_PTNUM		118 //月电度有效点个数
#define HISDAT_FLAG_YEAR_KWH_PTNUM		119 //年电度有效点个数

#define HISDAT_FLAG_DAY_DIG_ONTIME		200 //日合闸时间(秒)
#define HISDAT_FLAG_DAY_DIG_OFFTIME		201 //日分闸时间(秒)
#define HISDAT_FLAG_DAY_DIG_ONCNT		202 //日合闸次数
#define HISDAT_FLAG_DAY_DIG_OFFCNT		203 //日分闸次数
#define HISDAT_FLAG_MON_DIG_ONTIME		210 //月合闸时间(秒)
#define HISDAT_FLAG_MON_DIG_OFFTIME		211 //月分闸时间(秒)
#define HISDAT_FLAG_MON_DIG_ONCNT		212 //月合闸次数
#define HISDAT_FLAG_MON_DIG_OFFCNT		213 //月分闸次数
#define HISDAT_FLAG_YEAR_DIG_ONTIME		214 //年合闸时间(秒)
#define HISDAT_FLAG_YEAR_DIG_OFFTIME	215 //年分闸时间(秒)
#define HISDAT_FLAG_YEAR_DIG_ONCNT		216 //年合闸次数
#define HISDAT_FLAG_YEAR_DIG_OFFCNT		217 //年分闸次数

#define HISDAT_FLAG_DAY_PROC_STARTCNT	204 //节点日进程启动次数
#define HISDAT_FLAG_MON_PROC_STARTCNT	205 //节点月进程启动次数
#define HISDAT_FLAG_YEAR_PROC_STARTCNT	206 //节点年进程启动次数


//
#define HISDAT_FLAGCLASS_REAL			1		//实时数据
#define HISDAT_FLAGCLASS_DAY			2		//日统计数据
#define HISDAT_FLAGCLASS_MON			3		//月统计数据
#define HISDAT_FLAGCLASS_YEAR			4		//年统计数据
//系统信息ID定义
#define RDP_SYSINFO_ID_CENTERSRVIP 0
#define RDP_SYSINFO_ID_SGDELAYTIME 1
#define RDP_SYSINFO_ID_SGYCDEAD 2
#define RDP_SYSINFO_ID_JUDGEYCDEADTIME 3	//遥测判死数时间

//rtu参数的处理方式
//第0位:从1->0时,报事故事项
//第1位:报事故事项，加入遥测异常判断
#define RDP_RTU_PROCMODE_CRTSG			0x00000001  //1:当开关由1->0时，产生SG
#define RDP_RTU_PROCMODE_SGUSEYC			0x00000002  //1:SG的判定加入遥测的异常判断
#define RDP_RTU_PROCMODE_CRTYCSG			0x00000004  //1:当该遥测对应设备没有遥信时，遥测突变产生事故的异常判断
#define RDP_RTU_PROCMODE_HISPERIODFLAG	0x00000008  //1:历史数据按周期召测 (如每两天召测一次，但一次召测2天的数据),抄收起始时间记录在RTU_Ip字段中 
														//0:正常召测
#define RDP_RTU_PROCMODE_XS_USEMARK		0x00000010  //1:线损计算时使用表码值 
#define RDP_RTU_PROCMODE_YX2RDB			0x00000020  //1:遥信直接进入实时库 
#define RDP_RTU_PROCMODE_PROCRTDAT			0x00000040  //1:处理实时数据

//bit0:是否处理实时yc bit1::是否处理历史yc bit2：是否有实时表码 bit3：是否有实时电量 
//bit4：是否有历史表码 bit5：是否有历史电量 bit6：yx是否发送告警信息 bit7:遥信是否写入实时库
#define RDP_EXSYS_PROCMODE_PROCRTYC			0x00000001
#define RDP_EXSYS_PROCMODE_PROCHISYC		0x00000002
#define RDP_EXSYS_PROCMODE_PROCRTKWH		0x00000004
#define RDP_EXSYS_PROCMODE_PROCHISMARK		0x00000008
#define RDP_EXSYS_PROCMODE_PROCHISACC		0x00000010
#define RDP_EXSYS_PROCMODE_YXWRNING			0x00000020
#define RDP_EXSYS_PROCMODE_YX2RDB			0x00000040
#define RDP_EXSYS_PROCMODE_CRTYCSG			0x00000080  //1:当该遥测对应设备没有遥信时，遥测突变产生事故的异常判断
#define RDP_EXSYS_PROCMODE_CRTSG			0x00000100  //1:当开关由1->0时，产生SG
#define RDP_EXSYS_PROCMODE_SGUSEYC			0x00000200  //1:SG的判定加入遥测的异常判断

//0:正常召测
//测点的处理模式
#define RDP_PT_PROCMODE_FESEND_MARK			0x00000001	//1:前置程序发送标码
#define RDP_PT_PROCMODE_FESEND_VAL			0x00000002	//1:前置发送实时数据,对于电量,则是发送小时电量
#define RDP_PT_PROCMODE_FESEND_HIS_VAL		0x00000004	//1:前置发送历史数据,对于电量,则是历史电量
#define RDP_PT_PROCMODE_FESEND_HIS_MARK		0x00000008	//1:前置程序发送历史表码
#define RDP_PT_PROCMODE_OVERLIMIT_1			0x00000010	//1:处理遥测一级越限报警
#define RDP_PT_PROCMODE_SAVEDB				0x00000020	//1:报警存入数据库
#define RDP_PT_PROCMODE_SENDALARM			0x00000040	//1:报警发送alarm
#define RDP_PT_PROCMODE_CALCMEAS			0x00000080	//1:计算量按量测类型方式进行计算
#define RDP_PT_PROCMODE_CALC_HISCAL			0x00000100	//1:计算量按SG_RDP_HIS_CALOBJ表中的置入进行计算
#define RDP_PT_PROCMODE_CALC_I				0x00000200	//1:计算量按SG_RDP_CALC_EXPR表中的置入进行计算
#define RDP_PT_PROCMODE_PROCABNORMITY		0x00000400	//1:处理异常数据,此时遥测的上下限,作为异常数据值得限
#define RDP_PT_PROCMODE_ALARM_DELAY			0x00000800	//1:报警时,延时报警
#define RDP_PT_PROCMODE_NOTALARM			0x00001000	//1:测点不报警
#define RDP_PT_PROCMODE_ALARMSAVEPT			0x00002000	//1:测点报警时，将当前值存入存历史数据,dps2有效
#define RDP_PT_PROCMODE_BIGCHANSAVEPT		0x00004000	//1:测点突变存盘  dps2有效 
#define RDP_PT_PROCMODE_SAVE_REALMAXMIN		0x00008000	//1:测点存储实时最大最小  dps2有效
#define RDP_PT_PROCMODE_MANUALMETER			0x00010000	//1:测点有抄表
#define RDP_PT_PROCMODE_OVERLIMIT_2			0x00020000	//1:处理遥测二级越限报警
#define RDP_PT_PROCMODE_ACCNOTPROCLACK		0x00040000	//1:电度不做均摊处理
#define RDP_PT_PROCMODE_ACCMON_NOTUSEMARK	0x00080000	//1:月电度不用表码统计
#define RDP_PT_PROCMODE_EVTBIG				0x00100000	//1:做事项聚合处理
#define RDP_PT_PROCMODE_ACC_LESSZERO			0x00200000	//1:电度可以为负
#define RDP_PT_PROCMODE_FESEND_REAL_ONPERIOD	0x00400000	//1:处理的数据按存盘间隔时间进行存储
#define RDP_PT_PROCMODE_STAT_NOTZERO	0x00800000	//1:统计时对零不进行统计
#define RDP_PT_PROCMODE_ACC_MARK_NOBACK	0x01000000	//1:电度表码不会倒走
#define RDP_PT_PROCMODE_CHANSAVE	0x02000000	//1:测点做变化存储
#define RDP_PT_PROCMODE_ACCDAY_NOTUSEMARK	0x04000000	//1:日电度不用表码统计

/*
//	电量处理模式定义
#define RDP_MT_PROCMODE_FE_MARK			0x00000001  //1:前置程序发送表码
#define RDP_MT_PROCMODE_FE_VALUE		0x00000002  //1:前置程序发送小时电量
#define RDP_MT_PROCMODE_FE_HIS_VAL		0x00000004  //1:前置程序发送历史电量
#define RDP_MT_PROCMODE_FE_HIS_MARK		0x00000008  //1:前置程序发送历史表码
*/
//事项处理模式
#define SG_EVT_PROCMODE_ALL		0	//处理所有的事项
#define SG_EVT_PROCMODE_NO		1	//不处理任何事项
#define SG_EVT_PROCMODE_WS		2	//按WorkSpace处理事项


#endif //#ifndef __SG__OS_BASE__HHH
