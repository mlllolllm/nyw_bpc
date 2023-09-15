//==================================================================================================
//	Summary:
//		DPS ( Data Process Server ) Share Struct
//
//	---------------------------------------------------------------------------------------------
//	Author: Arctos                    Version: 1.00.000                          Date: 2011-09-01
//==================================================================================================

#ifndef __DPS_SHARE_STRUCT__
#define __DPS_SHARE_STRUCT__
#include "rdp_const.h"
enum SHARE_MEMORY_RECORD_STATUS_
{
	SMRS_LIMIT			= 0x00000007 ,		//	越限标记,参见 SMR_LIMIT_* 定义

	SMRS_LOCKED			= 0x00000080 ,		//	锁定
	SMRS_MANSET			= 0x00000100 ,		//	人工设置

	SMRS_DEATH			= 0x00001000 ,		//	死数

	SMRS_FLASH			= 0x00004000 ,		//	闪烁
	SMRS_INVALID		= 0x00008000 ,		//	值无效
};

enum SHARE_MEMORY_RECORD_FLAGS_
{
	SMRS_CANYKYT = 0x00000002,		//	模拟量可遥调，状态量可遥控
	SMRF_EXCEPT			= 0x00000040 ,		//	事故
	SMRF_AUTO_RESUM		 = 0x00000080,		//	自动复归
	SMRF_INVERT			= 0x00000100 ,		//	信号量取反

	SMRS_NO_EVENT		= 0x00000200 ,		//	报警抑制
	//SMRF_ALARMDELAY		= 0x00000400 ,		//	报警延迟
	SMRS_ALARM_SAVEVAL	= 0x00000800,		//	模拟量报警时存储测点值,状态量报警时存储同设备的yc kwh

	SMRF_LIMIT_1		= 0x00001000 ,		//	上下限有效
	SMRF_LIMIT_2		= 0x00002000 ,		//	上上 下下限有效
	SMRF_RANGE			= 0x00004000 ,		//	物理限有效

	SMRS_DEAD_SAVEVAL	= 0x00008000,		//	模拟量过死区存储历史数据
	SMRS_SAVE_REALMAXMIN= 0x00010000,		//	模拟量存储存盘间隔内的实时最大 实时最小
	SMRS_SAVE_MAN_RESET= 0x00020000,		//	需人工复位

	SMRF_INVALID		= 0x00080000 ,		//	值无效
};

//==================================================================================================
//模拟量表	
typedef struct SMT_DPS_ANA
{
	int		ID;		//ID
	char		Name[80];		//名称
	int		Stamp;		//更新时间戳
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	double		Value;		//测点值
	int		Status;		//状态
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	int		Terminal;		//端子号
	int		Measure;		//量测类型
	double		Maximum;		//日最大值
	double		Minimum;		//日最小值
	double		Limit_H;		//上限
	double		Limit_L;		//下限
	double		Limit_HH;		//上上限
	double		Limit_LL;		//下下限
	double		Base;		//计算基值
	double		Rate;		//计算比率
	int		Interval;		//存盘间隔
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	short		MeasClass;		//量测分类
	unsigned char		res0[2];
	int		Delay;		//延迟时间
	unsigned char		DatLevel;		//数据等级
	unsigned char		res1[3];
	int		ProcMode;		//处理模式
#if (SG_RDB_VERNO>=2)
	double		BrkChanVal;		//突变限值
	int		MaxTime;		//最大值发生时
	int		MinTime;		//最大值发生时
	int		DispUnit;		//显示单位
	int		BakVal1;		//备用1
	double	LastSaveVal; //上次存盘值
#endif
}SMT_DPS_ANA;
//数字量表	
typedef struct SMT_DPS_DIG
{
	int		ID;		//ID
	char		Name[80];		//名称
	int		Stamp;		//更新时间戳
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	int		Value;		//测点值
	int		Status;		//状态
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	int		Terminal;		//端子号
	int		Measure;		//量测类型
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	short		MeasClass;		//量测分类
	short		MCU_Close;		//MCU合闸序号
	short		MCU_Open;		//MCU分闸序号
	short		YK_Close;		//遥控合闸序号
	short		YK_Open;		//遥控分闸序号
	unsigned char		res0[2];
	int		Delay;		//延迟时间
#if (SG_RDB_VERNO>=2)
	int		BakVal1;		//备用1
	int		BakVal2;		//备用2
	int		BakVal3;		//备用3
	int		BakVal4;		//备用4
#endif
}SMT_DPS_DIG;

//电度表
typedef struct SMT_DPS_ACC
{
	int		ID;		//ID
	char		Name[80];		//名称
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	int		Status;		//状态
	double		Value;		//电量值
	double		MarkValue;		//表码值
	double		LastMarkValue;		//上次表码值
	int		Stamp;		//电量时间戳
	int		MarkStamp;		//表码时间戳
	int		DayEvtCnt;		//今日倒走事项次数
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	short		Terminal;		//端子号
	unsigned char		res0[2];
	int		Measure;		//量测类型
	double		ConvFact;		//计算倍率
	double		FullCode;		//满码
	int		Interval;		//存盘间隔
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	short		MeasClass;		//量测分类
	unsigned char		res1[2];
	int		ProcMode;		//处理模式
	int		Delay;		//延迟时间
#if (SG_RDB_VERNO>=2)
	int		DispUnit;		//显示单位
	double	InitMarkValue;		//初始表码
	int		BakVal4;		//每日用量最大值
#endif
	unsigned char		res2[4];
}SMT_DPS_ACC;

typedef struct  SMT_DPS_ANA S_YCINFO;
typedef struct  SMT_DPS_DIG S_YXINFO;
typedef struct  SMT_DPS_ACC S_KWHINFO;
//模拟量基础表	
typedef struct S_ANA_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	int		Terminal;		//端子号
	int		Measure;		//量测类型
	double		Limit_H;		//上限
	double		Limit_L;		//下限
	double		Limit_HH;		//上上限
	double		Limit_LL;		//下下限
	double		Base;		//计算基值
	double		Rate;		//计算比率
	int		Interval;		//存盘间隔
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	int		Delay;		//延迟时间
	int		ProcMode;		//处理模式
	double		BrkChanVal;		//突变限值
}S_ANA_BASEINFO;
//数字量基础表	
typedef struct S_DIG_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	int		Terminal;		//端子号
	int		Measure;		//量测类型
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	short		MCU_Close;		//MCU合闸序号
	short		MCU_Open;		//MCU分闸序号
	short		YK_Close;		//遥控合闸序号
	short		YK_Open;		//遥控分闸序号
	int		Delay;		//延迟时间
}S_DIG_BASEINFO;

//电度量基础表	
typedef struct S_ACC_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//终端编号
	int		Serial;		//测量点序号
	int		SFlag;		//静态状态信息
	int		ObjType;		//设备类型
	int		ObjID;		//设备ID
	int		Terminal;		//端子号
	int		Measure;		//量测类型
	double		ConvFact;		//计算倍率
	double		FullCode;		//满码
	int		Interval;		//存盘间隔
	int		WorkSpace;		//工作空间
	int		SrcType;		//计算标志
	int		SubStation;		//站ID
	int		ProcMode;		//处理模式
	int		Delay;		//延迟时间
	int		BakVal4;		//每日最大变化值
	unsigned char		res1[4];
}S_ACC_BASEINFO;



//通道设备类型表	
typedef struct S_CHANDEVTYPEINFO
{
	short		Type;		//通道设备类型
	char		Desc[40];		//通道设备描述
	char		DllName[40];		//通道设备动态库
}S_CHANDEVTYPEINFO;

//计算量表	
typedef struct SMT_DPS_CALC
{ 
int		ObjType;		//设备类型
int		ObjID;		//设备ID
char	RtField[32];		//计算字段
int		WorkSpace;		//工作空间
char		Formula[1024];		//计算公式
int		StartItemNo;		//起始分项号
int		ItemNum;		//分项个数
short		CalcState;		//计算状态
unsigned char		CalcHisFlag;		//计算历史数据
unsigned char		res0[1];
short		DelayHours;		//历史滞后小时
short		FieldNo;		//实时库域号
}SMT_DPS_CALC;
//计算分项表	
typedef struct SMT_DPS_CALCITEM
{ 
int		CalcNo;		//计算号
short		ItemNo;		//计算分项号
short		ItemType;		//元素类型
short		DatType;		//实时库的表No/符号/函数类型
short		FieldNo;		//实时库域号
int		KeyID;		//实时库的键值
char		FieldName[32];		//实时库域
double		ItemVal;		//元素值
}SMT_DPS_CALCITEM;

//前置命令表	
typedef struct S_FERT_CMDINFO
{ 
unsigned char		Valid;		//有效标志
unsigned char		CmdType;		//命令类型
unsigned char		SubCmdType;		//命令子类型
unsigned char		Status;		//执行状态
int		ExSysID;		//SCD系统ID
int		SendCmdTime;		//命令下达时间
int		MaxProcTime;		//最长执行时间
char	CmdDat[128];		//命令数据区
}S_FERT_CMDINFO;

//外部系统	
typedef struct S_EXSYSINFO
{ 
char		Code[32];		//外部系统名称
short		ID;		//外部系统ID
unsigned char		res0[2];
int		WorkSpace;		//工作空间
int		SysAddr;		//外部系统地址
short		Type;		//外部系统类型
short		ProtocolID;		//规约号
unsigned char		UseFlag;		//使用标志
unsigned char		res1[3];
int		SavePeriod;		//存盘间隔(秒)
int		KWHSavePeriod;		//KWH存盘间隔(秒)
char		User[64];		//用户名
char		Passwd[64];		//密码
char		SysPara[128];		//系统参数
int		DeadPeriod;		//死数判别时间(秒)
short		HisYCDelayHours;		//历史YC延时小时
unsigned char		res2[2];
int		HisYCCallTime;		//历史YC召唤天绝对分
short		HisKWHDelayHours;		//历史KWH延时小时
unsigned char		res3[2];
int		HisKWHCallTime;		//历史KWH召唤天绝对分
int		CallAllTime;		//召唤全数据时间
int		HisDatBaseYMD;		//抄收基准年月日
short		Warn_LackPercent;		//缺数报警百分比
short		Warn_YXChanNum;		//变位报警个数
int		ProcMode;		//处理模式
unsigned char		RealLinkStatus;		//实时连接状态
unsigned char		HisLinkStatus;		//历史连接状态
unsigned char		res4[2];
int		ErrCnt;		//断线次数
int		ErrYMD;		//最后断线年月日
int		ErrHMS;		//最后断线时分秒
int		ProcTime_HisYC;		//历史遥测召唤最后的时间
int		ProcTime_HisKWH;		//历史电度召唤最后的时间
int		ProcTime_HisKWH_Mark;		//历史电度表码召唤最后的时间
}S_EXSYSINFO;
//终端表	
typedef struct S_RTUINFO
{
	char		Code[32];		//终端名称
	int		ID;		//终端ID
	int		RtuAddr;		//终端地址
	short		Type;		//终端类型
	unsigned char		UseFlag;		//使用标志
	unsigned char		res0[1];
	int		SavePeriod;		//存盘间隔(秒)
	int		KWHSavePeriod;		//KWH存盘间隔(秒)
	char		User[64];		//用户名
	char		Passwd[64];		//密码
	char		RtuPara[128];		//终端参数
	int		DeadPeriod;		//死数判别时间(秒)
	int		ProcMode;		//处理模式
	int		ZFGrpNo;		//转发组号
	int		WorkSpace;		//工作空间
	int		NodeID;		//前置机ID
	int		MainLinkPathID;		//主链路ID
	int		ProcTime;		//最后操作时间
	unsigned char		LinkStatus;		//连接状态
	unsigned char		Status;		//终端状态
	unsigned char		res1[2];
	int		ErrCnt;		//断线次数
	int		ErrYMD;		//最后断线年月日
	int		ErrHMS;		//最后断线时分秒
}S_RTUINFO;//模拟量表	
//计量点信息表	
typedef struct S_METERINFO
{
	int		ID;		//表计ID
	char		Code[32];		//代码
	int		WorkSpace;		//工作空间
	int		ReaderID;		//采集器ID
	int		RtuID;		//终端ID
	int		MeterNo;		//采集号
	short		Phase;		//相位
	unsigned char		res0[2];
	int		BaudRate;		//波特率
	short		PortNo;		//端口号
	short		ProtocolType;		//通讯协议
	char		TXPasswd[16];		//通讯密码
	short		RateNum;		//费率个数
	short		UseClass1;		//用户大类号
	short		UseClass2;		//用户小类号
	short		MarkIntegerNum;		//表码读数整数位个数
	short		MarkDecimalNum;		//表码读数小数位个数
	unsigned char		res1[2];
	int		ReaderID_CJ;		//实际采集器ID
	int		RtuID_CJ;		//实际终端ID
	int		MeterNo_CJ;		//实际采集号
	short		Phase_CJ;		//实际相位
	unsigned char		res2[2];
	int		ProcTime;		//处理时间
	int		PtID_11;		//电流测点ID
	int		PtID_12;		//A相电流测点ID
	int		PtID_13;		//B相电流测点ID
	int		PtID_14;		//C相电流测点ID
	int		PtID_1;		//电压测点ID
	int		PtID_7;		//A相电压测点ID
	int		PtID_8;		//B相电压测点ID
	int		PtID_9;		//C相电压测点ID
	int		PtID_201;		//有功电量测点ID
}S_METERINFO;
//采集器信息表	
typedef struct S_READERINFO
{
	int		ID;		//采集器ID
	char		Code[32];		//代码
	int		WorkSpace;		//工作空间
	short		Phase;		//相位
	unsigned char		res0[2];
	int		RtuID;		//终端ID
	short		Phase_CJ;		//实际相位
	unsigned char		res1[2];
	int		RtuID_CJ;		//实际采集的终端
	int		ProcTime;		//处理时间
}S_READERINFO;
//转发模拟量表	
typedef struct S_ZFINFO_ANA
{
	int		GroupID;		//转发组号
	int		ZFPointNo;		//转发序号
	char	Name[24];		// 名称
	int		PtID;		//测点ID
	int		WorkSpace;		//工作空间
	float		ConvFace;		//转发系数
	int		ProcMode;		//处理模式
	unsigned char		NewFlag;		//新数标志
	unsigned char		res0[3];
	float		Val;		//值
	int		Status;		//质量标志
}S_ZFINFO_ANA;
//转发数字量表	
typedef struct S_ZFINFO_DIG
{
	int		GroupID;		//转发组号
	int		ZFPointNo;		//转发序号
	char	Name[24];		// 名称
	int		PtID;		//测点ID
	int		WorkSpace;		//工作空间
	int		ProcMode;		//处理模式
	unsigned char		NewFlag;		//新数标志
	unsigned char		res0[3];
	int		Val;		//值
	int		Status;		//质量标志
}S_ZFINFO_DIG;
//转发电度量表	
typedef struct S_ZFINFO_ACC
{
	int		GroupID;		//转发组号
	int		ZFPointNo;		//转发序号
	char	Name[24];		// 名称
	int		PtID;		//测点ID
	int		WorkSpace;		//工作空间
	float		ConvFace;		//转发系数
	int		ProcMode;		//处理模式
	unsigned char		NewFlag;		//新数标志
	unsigned char		res0[3];
	int		Status;		//质量标志
	double		Val;		//值
	double		MarkVal;		//表码值
}S_ZFINFO_ACC;
typedef struct S_CHANNELINFO
{
	int		ID;		//ID
	char		Name[40];		//名称
	unsigned char		UseFlag;		//使用标志
	unsigned char		res0[1];
	short		ChanType;		//通道类型
	int		ProcMode;		//处理模式
	char		IPAddr[20];		//地址IP
	int		BaudRate;		//波特率
	short		CheckBit;		//校验方式
	short		DatBit;		//数据位
	short		StopBit;		//停止位
	short		FCtrlBit;		//流控制位
	short		DevType;		//设备类型
	char		DevAddr[40];		//设备地址
	unsigned char		res1[2];
	int		StopLimitTime;		//通道停止时间限
	int		ErrCodeRateLimit;		//误码率限值
	int		ErrTimeLimit;		//误码率超限时间
	int		ChanGroup;		//通道组
	int		WorkSpace;		//工作空间
	int		ChanStatus;		//通道状态
	int		DevStatus;		//设备状态
}S_CHANNELINFO;
//链路表	
typedef struct S_LINKPATHINFO
{
	int		ID;		//ID
	char		Name[40];		//名称
	short		RtuType;		//终端类型
	unsigned char		res0[2];
	int		RtuID;		//终端ID
	int		ChanID;		//通道ID
	int		WorkSpace;		//工作空间
	unsigned char		MainFlag;		//主通道标志
	unsigned char		res1[1];
	short		ProtocolID;		//规约号
	int		RealRtuID;		//实际终端ID
	int		ProcTime;		//最后操作时间
}S_LINKPATHINFO;
//模拟量生数据表	
typedef struct S_YCINFO_RAW
{
	int		ID;		//点ID
	int		WorkSpace;		//工作空间
	float		Val;		//值
	int		Status;		//质量标志
	int		ProcTime;		//处理时间
	unsigned char		NewFlag;		//新数标志
	unsigned char		res0[3];
}S_YCINFO_RAW;
//状态量生数据表	
typedef struct S_YXINFO_RAW
{
	int		ID;		//点ID
	int		WorkSpace;		//工作空间
	short		Val;		//值
	unsigned char		res0[2];
	int		Status;		//质量标志
	int		ProcTime;		//处理时间
	short		Ms;		//毫秒
	unsigned char		NewFlag;		//新数标志
	unsigned char		res1[1];
}S_YXINFO_RAW;
//电度量生数据表	
typedef struct S_KWHINFO_RAW
{
	int		ID;		//点ID
	int		WorkSpace;		//工作空间
	double		Val;		//值
	double		MarkVal;		//表码值
	int		Status;		//质量标志
	int		ProcTime;		//处理时间
	int		MarkProcTime;		//表码处理时间
	unsigned char		NewFlag;		//新数标志
	unsigned char		res0[3];
}S_KWHINFO_RAW;
//坐标位置表	
typedef struct S_POSITIONINFO
{
	char	Code[32];		//位置名称
	int		ID;		//位置ID
	int		WorkSpace;		//工作空间
	double		X;		//X坐标
	double		Y;		//Y坐标
	double		Z;		//Z坐标
	double		Distance;		//位移变化
#if (SG_RDB_VERNO>=2)
	double		Speed;		//速度
	double		Angle;		//角度
	int		ProcTime;		//时标
	unsigned char		res0[4];
#endif
}S_POSITIONINFO;

//规约类型表	
typedef struct S_PROTOCOLINFO
{ 
short		Type;		//规约类型
char		Desc[40];		//规约描述
char		DllName[40];		//规约动态库
char		HisDllName[40];		//历史规约动态库
}S_PROTOCOLINFO;

//外部系统规约类型表	
typedef struct S_EXSYS_PROTINFO
{ 
short		ID;		//规约类型
char		Desc[40];		//规约描述
char		DllName[40];		//规约动态库
char		HisDllName[40];		//历史规约动态库
unsigned char		IsClock24;		//0点为24点
char		ExSysDllName[40];		//外部系统动态库
char		ProcName_ANA[40];		//模拟量存储过程
char		ProcName_DIG[40];		//状态量存储过程
char		ProcName_ACC[40];		//电度量存储过程
unsigned char		res0[1];
}S_EXSYS_PROTINFO;
//量测类型表	
typedef struct S_MEASTYPEINFO
{ 
short		ID;		//量测类型
short		B_MeasType;		//基础量测类型
char		Code[32];		//代码
char		Desc[40];		//描述
short		ClassID;		//量测类
short		Phase;		//相位
int		ProcMode;		//处理模式
unsigned char		AbNormalVal;		//异常状态
unsigned char		res0[1];
short		DigStatID;		//状态描述ID
}S_MEASTYPEINFO;
//状态描述表	
typedef struct S_STATDESCINFO
{ 
short		DigStatID;		//状态描述ID
unsigned char		DigVal;		//状态值
char		DigDesc[32];		//状态描述
unsigned char		res0[1];
}S_STATDESCINFO;

#endif /* __DPS_SERVICE_ADAPTER__ */
