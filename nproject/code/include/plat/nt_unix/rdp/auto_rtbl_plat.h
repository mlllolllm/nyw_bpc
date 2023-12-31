#ifndef _HH_AUTO_RTBL_PLAT_HHH_ 
#define _HH_AUTO_RTBL_PLAT_HHH_ 
//该头文件由程序crthfile.exe自动生成
//交流线路段表	
#include "dppclient.h"
#include "rdbmem.h"
typedef struct MODEL_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//编号
char		NAME[128];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//基准电压
SG_INT64		OF_LINE;		//所属线路
float		R;		//电阻
float		X;		//电抗
float		BCH;		//充电电纳
float		R0;		//零序电阻
float		X0;		//零序电抗
float		B0CH;		//零序充电电纳
char		LINE_MODEL[24];		//线路型号
float		LENGTH;		//长（米）
float		MAX_AMP;		//最大电流
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		RATED_AMP;		//额定电流
float		B;		//电纳
float		G;		//电导
unsigned char		res1[4];
}MODEL_ACLINE_SEGMENT;
//储能表	
typedef struct MODEL_BATTERYENERGYSTORAGE
{ 
SG_INT64		ID;		//编号
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
SG_INT64		MenberOfLine;		//所属馈线
SG_INT64		MenberOfSubstation;		//所属变电站
float		SOCState;		//SOC状态
float		SOCLimHigh;		//SOC上限
float		SOCLimLow;		//SOC下限
float		chargeRatio;		//充电率
float		dischargeRatio;		//放电率
char		PSRID[64];		//PSRID
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属变电站
double		RATED_P;		//额定功率
double		RATED_S;		//额定容量
double		MAX_RATE;		//最大倍率
double		MIN_RATE;		//最小倍率
double		MAX_P;		//最大有功
double		MIN_P;		//最小有功
double		MAX_Q;		//最大无功
double		MIN_Q;		//最大无功
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压值
double		IPOWER_I;		//电流值
unsigned char		OF_BASE_VOLTAGE;		//基准电压
unsigned char		res1[7];
double		MPOWER_P;		//量测有功功率
double		MPOWER_Q;		//量测无功功率
}MODEL_BATTERYENERGYSTORAGE;
//间隔表	
typedef struct MODEL_BAY
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_VOLT_LEVEL;		//所属电压等级
SG_INT64		BAY_TYPE;		//类型
}MODEL_BAY;
//开关表	
typedef struct MODEL_BREAKER
{ 
SG_INT64		ID;		//编号
char		NAME[128];		//描述
char		ALIAS[32];		//别名
char		DISP_CODE[16];		//调度号
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//所属厂站
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_BAY;		//所属间隔
SG_INT64		DIGITAL_ID;		//遥信ID
unsigned char		NORMAL_OPEN_FLAG;		//常开标志
unsigned char		res1[3];
float		MAX_KV;		//最大电压
float		RATED_AMP;		//额定电流
float		MAX_AMP;		//最大电流
float		CAPACITY;		//容量
unsigned char		NORMAL_POSITION;		//正常状态
unsigned char		res2[3];
float		RATED_BREAK_AMP_CAPB;		//额定断流容量
float		INTERRUPTING_AMP;		//开断电流
unsigned char		TROLLY_BREAKER_FLAG;		//小车开关标志
unsigned char		DUAL_DIG_FLAG;		//双遥信标志
unsigned char		ZERO_BRANCH_FLAG;		//零支路标志
unsigned char		res3[1];
float		DYNSTABLE_AMP;		//动稳定电流
float		THERMAL_STABLE_AMP;		//热稳定电流
unsigned char		POWER_STATE;		//带电状态
unsigned char		res4[3];
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res5[4];
SG_INT64		PLD_CB_ID;		//旁路开关
unsigned char		TAG_FLAG;		//挂牌标志
unsigned char		res6[7];
}MODEL_BREAKER;
//母线表	
typedef struct MODEL_BUSBAR_SECTION
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		BUSBAR_TYPE;		//类型
int		BAS_CONN_TYPE;		//母线连接类型
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站号
SG_INT64		OF_BAY;		//间隔代码
int		POWER_SUPPLY_FLAG;		//电源点标志
unsigned char		res1[4];
SG_INT64		OF_FEEDER;		//馈线代码
unsigned char		BUS_STATUS;		//母线状态
unsigned char		res2[7];
double		BUSBAR_VOLT_HLIMIT;		//母线电压上限
float		BUSBAR_VOLT_LLIMIT;		//母线电压下限
unsigned char		LOAD_BUSBAR_FLAG;		//负荷母线标志
char		DISP_CODE[22];		//调度号
unsigned char		res3[1];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res4[4];
}MODEL_BUSBAR_SECTION;
//电容器表	
typedef struct MODEL_COMPENSATOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		COMPENSATOR_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
float		RATED_MVAR;		//额定功率
float		MVAR_PER_SECTION;		//每组容量
int		MAX_SECTIONS;		//最大组数
int		NORMAL_SECTIONS;		//投运组数
float		RATED_KV;		//额定电压
float		MAX_KV;		//最大电压
float		RATED_AMP;		//额定电流
float		MAX_AMP;		//最大电流
float		R;		//电阻
float		X;		//电抗
unsigned char		RUN_STATE;		//运行状态
char		DISP_CODE[22];		//调度号
unsigned char		res0[1];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
}MODEL_COMPENSATOR;
//连接点表	
typedef struct MODEL_CONN_NODE
{ 
SG_INT64		ID;		//编号
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_CONTAINER;		//厂站代码
SG_INT64		OF_BASE_VOLTAGE;		//电压等级
char		PSRID[64];		//资源ID
SG_INT64		OF_TOPOLOGICALNODE;		//所属拓扑节点
}MODEL_CONN_NODE;
//电流互感器	
typedef struct MODEL_CT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		CT_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
unsigned char		PHASE;		//相别
char		CT_MODEL[24];		//电流互感器型号
unsigned char		res0[3];
float		RATED_KV;		//额定电压
float		RATED_AMP_RATIO;		//额定电流比
char		DISP_CODE[22];		//调度号
unsigned char		res1[2];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		AccuracyLimit;		//百分比精度
}MODEL_CT;
//刀闸表	
typedef struct MODEL_DISCONNECTOR
{ 
SG_INT64		ID;		//编号
char		NAME[128];		//描述
char		ALIAS[32];		//别名
char		DISP_CODE[16];		//调度号
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//所属厂站
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_BAY;		//所属间隔
SG_INT64		DIGITAL_ID;		//遥信ID
unsigned char		NORMAL_OPEN_FLAG;		//常开标志
unsigned char		MANUAL_SET_FLAG;		//人工设置标志
unsigned char		NORMAL_POSITION;		//正常状态
unsigned char		DUAL_DIG_FLAG;		//双遥信标志
unsigned char		POWER_STATE;		//带电状态
unsigned char		res1[3];
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		TAG_FLAG;		//挂牌标志
unsigned char		res2[3];
}MODEL_DISCONNECTOR;
//配网交流线段表	
typedef struct MODEL_D_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//编号
char		NAME[256];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		LINE_TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
float		LATITUDE;		//纬度
float		LONGITUDE;		//经度
float		R;		//电阻
float		X;		//电抗
float		BCH;		//充电电纳
char		LINE_MODEL[64];		//线路型号
float		LENGTH;		//长（米）
float		MAX_AMP;		//最大电流
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		B;		//电纳
float		G;		//电导
char		PSRID[64];		//PSRID
unsigned char		res1[4];
SG_INT64		OF_BASE_VOLTAGE;		//基准电压
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_I;		//电流
double		IPOWER_PLOSS;		//有功损耗
double		IPOWER_QLOSS;		//无功损耗
double		RATED_A;		//承载电流容量
double		OVRLMTRATE;		//过载率
double		LIMITUPL;		//电流值越上限
}MODEL_D_ACLINE_SEGMENT;
//配网开关表	
typedef struct MODEL_D_BREAKER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//开关类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
int		NORMAL_POSITION;		//正常状态
char		CABINET_NUMBER[64];		//站房内开关的开关柜编号
char		DA_COMM_ADDRESS[64];		//配电自动化通信地址
float		LATITUDE;		//纬度
float		LONGITUDE;		//经度
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		TAG_FLAG;		//挂牌标志
unsigned char		NORMAL_OPEN_FLAG;		//常开标志
unsigned char		res1[2];
float		RATED_CURRENT;		//额定电流值
float		BREAKING_CAP;		//最大开断电流值
char		PHASE[6];		//相位
char		PSRID[64];		//PSRID
unsigned char		res2[2];
SG_INT64		OF_BASE_VOLTAGE;		//基准电压
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压
double		IPOWER_I;		//电流
}MODEL_D_BREAKER;
//配网母线表	
typedef struct MODEL_D_BUSBAR_SECTION
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		BUS_TYPE;		//母线类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
float		LATITUDE;		//纬度
float		LONGITUDE;		//经度
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
char		PSRID[64];		//PSRID
SG_INT64		OF_BASE_VOLTAGE;		//基准电压
int		OF_TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res1[4];
double		IPOWER_VLTANGLE;		//电压相角
double		IPOWER_U;		//电压
}MODEL_D_BUSBAR_SECTION;
//配网馈线表	
typedef struct MODEL_D_CIRCUIT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
int		AREA_FEATURE;		//区域特征
unsigned char		res0[4];
SG_INT64		SOURCE_SUBST;		//源头变电站
SG_INT64		SOURCE_BREAKER;		//出线开关
int		FA_TYPE;		//馈线自动化类型
int		FA_LOCK_FLAG;		//馈线自动化锁
}MODEL_D_CIRCUIT;
//配网电容器表	
typedef struct MODEL_D_COMPENSATOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
char		PSRID[64];		//PSRID
SG_INT64		NODEID;		//并网点编号
double		EACH_CAPACITY;		//每组容量
int		MAX_NUM;		//最大组数
int		OPERATION_NUM;		//投运组数
int		MAX_ACT_NUM;		//时段内最大动作次数
unsigned char		res1[4];
}MODEL_D_COMPENSATOR;
//配网连接点表	
typedef struct MODEL_D_CONN_NODE
{ 
SG_INT64		ID;		//编号
}MODEL_D_CONN_NODE;
//配网直流线段表	
typedef struct MODEL_D_DCLINE_SEGMENT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		LINE_TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
float		LATITUDE;		//纬度
float		LONGITUDE;		//经度
float		R;		//电阻
float		X;		//电抗
float		BCH;		//充电电纳
char		LINE_MODEL[64];		//线路型号
float		LENGTH;		//长（米）
float		MAX_AMP;		//最大电流
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		B;		//电纳
float		G;		//电导
unsigned char		res1[4];
}MODEL_D_DCLINE_SEGMENT;
//配网刀闸表	
typedef struct MODEL_D_DISCONNECTOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//隔刀类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
int		NORMAL_POSITION;		//正常状态
char		CABINET_NUMBER[64];		//站房内开关的开关柜编号
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		TAG_FLAG;		//挂牌标志
unsigned char		NORMAL_OPEN_FLAG;		//常开标志
unsigned char		res1[2];
float		RATED_CURRENT;		//额定电流值
char		PSRID[64];		//PSRID
unsigned char		res2[4];
}MODEL_D_DISCONNECTOR;
//配网地刀表	
typedef struct MODEL_D_GROUND_DISCONNECTOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//接地刀类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
int		NORMAL_POSITION;		//正常状态
char		CABINET_NUMBER[64];		//站房内开关的开关柜编号
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		TAG_FLAG;		//挂牌标志
unsigned char		NORMAL_OPEN_FLAG;		//常开标志
char		PSRID[64];		//PSRID
unsigned char		res1[2];
}MODEL_D_GROUND_DISCONNECTOR;
//配网电压互感器表	
typedef struct MODEL_D_PT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		NorminalRatio;		//变比
char		PHASE[6];		//相位
unsigned char		res1[6];
}MODEL_D_PT;
//配网电抗器表	
typedef struct MODEL_D_REACTOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
}MODEL_D_REACTOR;
//配网站房表	
typedef struct MODEL_D_SUBSTATION
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
SG_INT64		SUBTYPE;		//站房类型
int		CURR_POWER_NO;		//当前电源号
int		MAIN_POWER_NO;		//主电源号
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
float		LATITUDE;		//纬度
float		LONGITUDE;		//经度
SG_INT64		BRANCH_ID;		//上级干支线
char		PSRID[64];		//PSRID
}MODEL_D_SUBSTATION;
//配网端子表	
typedef struct MODEL_D_TERMINAL
{ 
SG_INT64		ID;		//编号
int		SEQ_NUMBER;		//序号
int		TYPE;		//类型
SG_INT64		OF_DEVICE;		//所属设备
SG_INT64		CONN_NODE_ID;		//连接点ID
}MODEL_D_TERMINAL;
//配网变压器表	
typedef struct MODEL_D_TRANSFORMER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//类型
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_FEEDER_SECTION;		//所属干支线
SG_INT64		OF_D_SUBSTATION;		//所属站房
char		MODEL[64];		//型号
float		RATED_CAPACITY;		//额定容量
int		USER_TYPE;		//用户类型
int		VIP_AMOUNT;		//重要用户数
float		LOAD_RATIO;		//负载率
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
char		VECTOR_GROUP[64];		//接线方式
char		PSRID[64];		//PSRID
double		MPOWER_I;		//电流
double		MPOWER_P;		//有功功率
double		MPOWER_Q;		//无功功率
double		MPOWER_U;		//电压
}MODEL_D_TRANSFORMER;
//配网绕组表	
typedef struct MODEL_D_TRANS_WINDING
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[64];		//别名
char		DISP_CODE[64];		//调度编号
SG_INT64		BASE_VOLTAGE;		//基准电压
int		TYPE;		//类型
int		CONN_TYPE;		//接线方式
SG_INT64		OF_D_TRANSFOR;		//所属变压器
float		RATED_CAPACITY;		//额定容量
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		ENDNUMBER;		//序号
unsigned char		res0[3];
double		R;		//电阻
double		X;		//电抗
double		B;		//电纳
double		G;		//电导
char		PSRID[64];		//PSRID
}MODEL_D_TRANS_WINDING;
//电动汽车表	
typedef struct MODEL_ELECTRICVEHICLE
{ 
SG_INT64		ID;		//编号
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
SG_INT64		MenberOfLine;		//所属馈线
SG_INT64		MenberOfSubstation;		//所属变电站
SG_INT64		timeLasting;		//使用时间
SG_INT64		status;		//充电桩状态
SG_INT64		genEff;		//充电效率
float		ratedP;		//额定功率
float		ratedS;		//额定容量
float		maxSOC;		//SOC上限
float		minSOC;		//SOC下限
float		SOC;		//SOC量测
float		mpower_P;		//有功功率
float		mpower_Q;		//无功功率
float		mpower_U;		//电压值
float		mpower_I;		//电流值
char		PSRID[64];		//PSRID
unsigned char		res0[4];
}MODEL_ELECTRICVEHICLE;
//负荷表	
typedef struct MODEL_ENERGY_CONSUMER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		ENERGY_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_FEEDER;		//馈线代码
float		MW_VOLT_CHARACT;		//有功负荷电压特性
float		MVAR_VOLT_CHARACT;		//无功负荷电压特性
float		MW_FREQ_CHARACT;		//有功负荷频率特性
float		MVAR_FREQ_CHARACT;		//无功负荷频率特性
unsigned char		LOAD_STATE;		//负荷状态
unsigned char		res0[3];
float		MW_VALUE;		//有功负荷值
float		MVAR_VALUE;		//无功负荷值
char		DISP_CODE[22];		//调度号
unsigned char		res1[2];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		RATED_ELECTRICITY;		//额定电流
float		LOAD_RATE;		//负载率
int		CustomerCount;		//聚合用户数
float		Pfixed;		//固定有功功率
float		Qfixed;		//固定无功功率值
unsigned char		Grounded;		//是否接地
char		PhaseConnection[12];		//接线方式
unsigned char		res2[3];
float		MPOWER_I;		//电流
float		MPOWER_U;		//电压
float		MPOWER_Q;		//无功功率
float		MPOWER_P;		//有功功率
char		PSRID[64];		//资源ID
SG_INT64		OF_TRANSFORMER;		//所属台区
unsigned char		OF_BASE_VOLTAGE;		//电压等级
unsigned char		res3[7];
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压
double		IPOWER_I;		//电流
}MODEL_ENERGY_CONSUMER;
//柔性负荷表	
typedef struct MODEL_FLEXLOADINFO
{ 
SG_INT64		ID;		//编号
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
SG_INT64		MenberOfLine;		//所属馈线
SG_INT64		MenberOfSubstation;		//所属变电站
float		LdFlxblIncIndx;		//负荷正向柔性系数
float		LdFlxblDecIndx;		//负荷反向柔性系数
float		LdFlxblIncPr;		//负荷正向可调节功率
float		LdFlxblDecPr;		//负荷反向可调节功率
unsigned char		usable;		//柔性负荷状态
unsigned char		res0[1];
short		type;		//柔性负荷类型
float		mpower_P;		//有功功率
float		mpower_Q;		//无功功率
float		mpower_U;		//电压值
float		mpower_I;		//电流值
unsigned char		res1[4];
}MODEL_FLEXLOADINFO;
//线路参数表	
typedef struct MODEL_LINE
{ 
SG_INT64		ID;		//编号
char		DISP_CODE[22];		//调度号
char		NAME[64];		//描述
unsigned char		res0[2];
int		LINE_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		BASE_VOLTAGE;		//基准电压
SG_INT64		FROM_SUBSTATION;		//起始厂站
SG_INT64		TO_SUBSTATION;		//终止厂站
SG_INT64		OF_COMPANY;		//所属公司
SG_INT64		OF_BAY;		//间隔代码
float		MUTUAL_IMPEDANCE;		//互阻抗
unsigned char		res1[4];
SG_INT64		ASSOC_LINE;		//相关线路名
float		AMP_MARG;		//电流裕度
unsigned char		LINE_STATE;		//线路状态
unsigned char		res2[3];
float		CAP_AMP;		//电容电流
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		RATED_ELECTRICITY;		//额定电流
float		LOAD_RATE;		//负载率
unsigned char		res3[4];
}MODEL_LINE;
//变压器表	
typedef struct MODEL_POWER_TRANS
{ 
SG_INT64		ID;		//编号
char		DISP_CODE[22];		//调度号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[2];
int		TRANS_TYPE;		//类型
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
float		HM_LEAKAGE_IMPEDANCE;		//高中短路电压
float		ML_LEAKAGE_IMPEDANCE;		//中低短路电压
float		LH_LEAKAGE_IMPEDANCE;		//低高短路电压:
float		HM_LOAD_LOSS;		//高中短路损耗
float		ML_LOAD_LOSS;		//中低短路损耗
float		LH_LOAD_LOSS;		//低高短路损耗
float		EXCITING_AMP;		//空载电流
float		NOLOAD_LOSS;		//空载损耗
float		GMAG_SAT;		//变压器励磁电导
float		BMAG_SAT;		//变压器励磁电纳
unsigned char		POWERTRANS_STATE;		//变压器状态
unsigned char		VOLT_ADJUST_MODE;		//调压方式
unsigned char		res1[2];
float		LOAD_CAPB_RATIO;		//负载容比
unsigned char		PARAM_CALC_FLAG;		//参数计算标志
unsigned char		res2[3];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
float		RATED_POWER;		//额定功率
float		ACTIVE_BALANCE_RATE;		//有功平衡率
float		REACTIVE_BALANCE_RATE;		//无功平衡率
float		LOAD_RATE;		//负载率
char		VectorGroup[64];		//接线方式
unsigned char		res3[4];
}MODEL_POWER_TRANS;
//电压互感器	
typedef struct MODEL_PT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
float		PT_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_FEEDER;		//馈线代码
char		PHASE[12];		//相别
char		PT_MODEL[24];		//电压互感器型号
float		RATED_KV;		//额定电压
float		RATED_VOLT_RATIO;		//额定电压比
char		DISP_CODE[22];		//调度号
unsigned char		res0[2];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res1[4];
}MODEL_PT;
//光伏表	
typedef struct MODEL_PVARRAY
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//名称
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属变电站
float		RATED_P;		//额定功率
float		MAX_P;		//最大有功
float		MIN_P;		//最小有功
float		MAX_Q;		//最大无功
float		MIN_Q;		//最小无功
unsigned char		USEABLE;		//光伏状态
unsigned char		res0[3];
float		MAX_PF;		//功率因数上限
float		MIN_PF;		//功率因数下限
float		MPOWER_P;		//有功功率
float		MPOWER_Q;		//无功功率
float		MPOWER_U;		//电压值
float		MPOWER_I;		//电流值
char		PSRID[64];		//PSRID
SG_INT64		OF_TRANSFORMER;		//所属台区
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压值
double		IPOWER_I;		//电流值
unsigned char		OF_BASE_VOLTAGE;		//基准电压
unsigned char		res1[7];
}MODEL_PVARRAY;
//电抗器表	
typedef struct MODEL_REACTOR
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
SG_INT64		REACTOR_TYPE;		//类型
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
float		RATED_MVAR;		//额定功率
float		MVAR_PER_SECTION;		//每组容量
int		MAX_SECTIONS;		//最大组数
int		NORMAL_SECTIONS;		//投运组数
float		RATED_KV;		//额定电压
float		MAX_KV;		//最大电压
float		RATED_AMP;		//额定电流
float		MAX_AMP;		//最大电流
float		R;		//电阻
float		X;		//电抗
unsigned char		RUN_STATE;		//运行状态
char		DISP_CODE[22];		//调度号
unsigned char		res1[1];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
}MODEL_REACTOR;
//厂站表	
typedef struct MODEL_SUBSTATION
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
int		SUBSTATION_TYPE;		//类型
SG_INT64		OF_SCA;		//所属子控区域
SG_INT64		BASE_VOLTAGE;		//基准电压
SG_INT64		OF_FEEDER;		//所属馈线
int		DIGTAL_NUM;		//遥信数
int		ANALOG_NUM;		//遥测数
int		DEVICE_NUM;		//设备数
int		EVENT_NUM;		//告警数
int		TAG_NUM;		//挂牌数
unsigned char		res0[4];
SG_INT64		OF_SUBREGION;		//所属子区域
char		PSRID[255];		//psrid
unsigned char		res1[1];
SG_INT64		OF_BASE_VOLTAGE;		//基准电压
}MODEL_SUBSTATION;
//发电机表	
typedef struct MODEL_SYNCHRONOUS_MACHE
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		MACHE_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_FEEDER;		//馈线代码
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_BAY;		//间隔代码
float		MAX_KV;		//最大电压
float		MAX_MVAR;		//最大无功
float		MIN_KV;		//最小电压
float		MIN_MVAR;		//最小无功
float		MAX_MW;		//最大有功
float		MIN_MW;		//最小有功
float		RATED_MVA;		//额定容量
float		R1;		//正序电阻
float		X1;		//正序电抗
float		R0;		//零序电阻
float		X0;		//零序电抗
float		X2;		//负序电抗
float		GEN_FREQCHARACT;		//发电机功频特性
int		GEN_MODEL;		//发电机模型
float		INTERTIA;		//转子惯性时间常数
float		RA;		//定子电阻
float		XO;		//定子漏抗
float		XD;		//直轴同步电抗
float		XDIRECT_TRANS;		//直轴暂态电抗
float		XDIRECT_SUBTRANS;		//直轴次暂态电抗
float		XQ;		//交轴同步电抗
float		XQUAD_TRANS;		//交轴暂态电抗
float		XQUAD_SUBTRANS;		//交轴次暂态电抗
float		DAMP;		//阻尼系数
float		TD0P;		//励磁回路时间常数
float		TD0PP;		//直轴阻尼绕阻回路时间常数
float		TQ0PP;		//交轴阻尼绕阻时间回路常数
float		GEN_UNIT_FACT_FILTR_COEF;		//机组滤波系数
float		GEN_FM_COE;		//频率调节特性
float		CTRL_DBAND;		//控制死区
float		REG_MARG;		//调节余度
float		EMERG_BACKUP_LLIMIT;		//紧急备用下限
float		CAPB_LLIMIT;		//容量下限
float		CTRL_LLIMIT;		//运行控制下限
float		SCHED_GEN;		//机组计划
float		CTRL_HLIMIT;		//运行控制上限
float		CAPB_HLIMIT;		//容量上限
float		EMERG_BACKUP_HLIMIT;		//紧急备用上限
int		HYD_NUM_IWD_CURVES;		//发电机曲线数量
unsigned char		res0[4];
SG_INT64		GEN_RES_ID;		//PLC号
char		HYD_CURVE_NAME[24];		//耗流量曲线名
int		PHB_CNT;		//禁止运行区个数
float		PROHB_REGN_LO_PWR_RATIO;		//禁止运行区下限系数
float		PROHB_REGN_HI_PWR_RATIO;		//禁止运行区上限系数
float		ROC_LIMIT;		//调节速率限制
float		MAINT_COST;		//维护费用
float		PAYB_CONST;		//偿还系数
char		THR_FUEL_NAME[24];		//燃料名称
float		THR_INC_POLLU_COST;		//微增污染费用
int		WATER_TEMP_FACT;		//冷却水温因子
int		GEN_STATE;		//发电机状态
char		DISP_CODE[22];		//调度号
unsigned char		res1[2];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res2[4];
}MODEL_SYNCHRONOUS_MACHE;
//分接头表	
typedef struct MODEL_TAPCHANGER
{ 
SG_INT64		ID;		//编号
char		DESCRIPTION[64];		//描述
char		NAME[64];		//名称
char		HIGH_STEP[64];		//HIGH_STEP
float		NEUTRAL_STEP;		//NEUTRAL_STEP
float		LOW_STEP;		//LOW_STEP
float		STEP_VOLTAGE_INCREMENT;		//STEP_VOLTAGE_INCREMENT
float		NEUTRAL_KV;		//NEUTRAL_KV
float		NORMAL_STEP;		//NORMAL_STEP
unsigned char		res0[4];
SG_INT64		OF_TRANSWINDING;		//所属绕组
}MODEL_TAPCHANGER;
//端子表	
typedef struct MODEL_TERMINAL
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
int		TERMINAL_TYPE;		//类型
SG_INT64		OF_DEVICE;		//所属设备
char		ADDR[12];		//地址
unsigned char		res0[4];
SG_INT64		CONN_NODE_ID;		//连接点ID
char		PHASE[6];		//相位
char		PSRID[64];		//资源ID
unsigned char		res1[2];
}MODEL_TERMINAL;
//变压器绕组表	
typedef struct MODEL_TRANS_WINDING
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		WINDING_TYPE;		//类型
int		CONN_TYPE;		//连接类型
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_POWERTRANS;		//所属变压器
float		RATED_KV;		//额定电压
float		RATED_MVA;		//额定容量
float		R;		//电阻
float		X;		//电抗
float		R0;		//零序电阻
float		X0;		//零序电抗
float		G;		//绕组励磁电导
float		B;		//绕组器励磁电纳
float		MAX_AMP;		//最大电流
unsigned char		ADJUST_FLAG;		//可调标志
unsigned char		GROUND_FLAG;		//接地标志
unsigned char		res1[2];
int		TAP_TYPE;		//抽头类型
int		ACTUAL_TAP_POS;		//实际档位
float		AMP_MARG;		//电流裕度
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		ENDNUMBER;		//序号
unsigned char		res2[3];
}MODEL_TRANS_WINDING;
//电压等级表	
typedef struct MODEL_VOLT_LEVEL
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
SG_INT64		OF_SUBSTATION;		//厂站表_编号
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//基准电压
}MODEL_VOLT_LEVEL;
//风机表	
typedef struct MODEL_WINDGENERATOR
{ 
SG_INT64		ID;		//ID
char		name[64];		//名称
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属变电站
float		RATED_PF;		//额定功率因数
float		MAX_P;		//最大有功
float		MIN_P;		//最小有功
float		MAX_Q;		//最大无功
float		MIN_Q;		//最小无功
unsigned char		USABLE;		//风机状态
unsigned char		res0[3];
float		START_SPEED;		//启动风速
float		RATED_SPEED;		//额定风速
float		MAX_SPEED;		//最大风速
float		mpower_P;		//有功功率
float		mpower_Q;		//无功功率
float		mpower_U;		//电压值
float		mpower_I;		//电流值
char		PSRID[64];		//PSRID
unsigned char		res1[4];
}MODEL_WINDGENERATOR;
//配网馈线表	
typedef struct MODEL_D_FEEDER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
char		DISP_CODE[64];		//调度编号
unsigned char		res0[4];
SG_INT64		AREA_FEATURE;		//区域特征
SG_INT64		OF_STATION;		//源头变电站
SG_INT64		OF_BREAKER;		//出线开关
int		FA_TYPE;		//馈线自动化类型
int		FA_LOCK_FLAG;		//馈线自动化锁
char		PSRID[64];		//资源ID
}MODEL_D_FEEDER;
//配网接头	
typedef struct MODEL_D_JUNCTION
{ 
SG_INT64		ID;		//编号
SG_INT64		OF_DEVICE;		//所属设备
}MODEL_D_JUNCTION;
//配网客户	
typedef struct MODEL_D_CUSTOMER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//馈线代码
SG_INT64		METER_ID;		//表计
}MODEL_D_CUSTOMER;
//表计	
typedef struct MODEL_METER
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_USAGEPOINT;		//所属接入点
}MODEL_METER;
//CT	
typedef struct MODEL_D_CT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		CT_TYPE;		//类型
char		ALIAS[100];		//别名
SG_INT64		OF_BAY;		//间隔代码
SG_INT64		OF_VOLT_LEVEL;		//电压等级
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
short		PHASE;		//相别
char		CT_MODEL[24];		//电流互感器型号
unsigned char		res0[6];
double		RATED_KV;		//额定电压
double		RATED_AMP_RATIO;		//额定电流比
char		DISP_CODE[22];		//调度号
unsigned char		res1[2];
int		POWER_STATE;		//带电状态
int		TOPO_ISLAND;		//拓扑电气岛号
double		ACCURACYLIMIT;		//百分比精度
}MODEL_D_CT;
//用户接入点	
typedef struct MODEL_USAGEPOINT
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		res0[4];
SG_INT64		OF_EQLOAD;		//所属等效负荷
}MODEL_USAGEPOINT;
//模拟量	
typedef struct MODEL_ANALOG
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//名称
SG_INT64		OF_DEVICE;		//所属设备
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属电站
int		PORT;		//端子号
int		MEAS_TYPE;		//量测类型
double		VAL;		//值
int		STATUS;		//状态
int		PROCTIME;		//变化时间
int		UNIT;		//单位
unsigned char		res0[4];
}MODEL_ANALOG;
//仿真历史表	
typedef struct his_simulation
{ 
int		ID;		//自增ID
unsigned char		res0[4];
SG_INT64		TASKID;		//仿真任务ID
SG_INT64		OF_DEVICE;		//所属设备
unsigned char		MEAS_TYPE;		//量测类型
unsigned char		res1[7];
double		TIME;		//一次仿真内的相对时间
float		VAL;		//仿真结果值
unsigned char		res2[4];
}his_simulation;
//网络节点表	
typedef struct net_node
{ 
int		ID;		//网络节点ID
char		NAME[64];		//节点名称
char		ALIAS[64];		//名称描述
unsigned char		TYPE;		//节点类型
unsigned char		res0[3];
}net_node;
//网络边表	
typedef struct net_edge
{ 
int		ID;		//网络边ID
char		NAME[64];		//边名称
int		LEFTNODE;		//左节点ID
int		RIGHTNODE;		//右节点ID
int		DELAY;		//边初始时延
}net_edge;
//网络节点事件表	
typedef struct sim_event
{ 
int		ID;		//事件ID
unsigned char		res0[4];
double		EVENTTIME;		//事件发生时间
int		OBJECTID;		//发生事件的节点或边的ID
unsigned char		TYPE;		//事件类型
unsigned char		res1[3];
int		PARAM;		//事件相关的节点或边的ID
unsigned char		EVENTTYPE;		//0信息事件，1物理事件
unsigned char		res2[3];
SG_INT64		TASKID;		//仿真任务ID
}sim_event;
//信息物理对象对应关系表	
typedef struct net_pow_relate
{ 
char		NODEID[64];		//信息网节点名
char		OF_DEVICE_MEAS[64];		//采集元件ID
char		OF_DEVICE_CTR[64];		//控制元件ID
int		ID;		//ID
}net_pow_relate;
//cloudpss通道表	
typedef struct pss_passage
{ 
SG_INT64		ID;		//通道ID
char		NAME[256];		//通道名称
char		CHANNLE_TYPE[256];		//输出通道名称，也是类型，如Irms�
char		CHANNLE_PIN[256];		//输出通道引脚，也是元件测量参数�
SG_INT64		OF_DEVICE;		//所属设备
}pss_passage;
//mdc_model_map	
typedef struct mdc_model_map
{ 
int		MODEL_ID;		//MODEL_ID
char		MODEL_NAME[32];		//MODEL_NAME
}mdc_model_map;
//base_meas_def	
typedef struct base_meas_def
{ 
unsigned char		ID;		//ID
char		NAME[288];		//NAME
char		MEASTYPE_DESC[360];		//量测类型描述
}base_meas_def;
//遥测实时数据表	
typedef struct rtval_analog
{ 
SG_INT64		ID;		//ID
float		VAL;		//遥测值
int		STATUS;		//STATUS
int		PROCTIME;		//PROCTIME
unsigned char		res0[4];
}rtval_analog;
//控制常量表	
typedef struct control_constant
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		TYPE[256];		//控制类型，如P、Q
char		VALUE[256];		//控制值
char		PINS[64];		//控制引脚
SG_INT64		OF_DEVICE;		//所属元件ID
}control_constant;
//仿真记录表	
typedef struct sim_task
{ 
SG_INT64		ID;		//仿真任务ID
char		NAME[64];		//仿真任务名称
SG_INT64		OF_FEEDER;		//仿真线路ID
int		TIMELENGTH;		//仿真时长
unsigned char		STATE;		//完成状态
unsigned char		res0[3];
}sim_task;
//光伏逆变器表	
typedef struct model_PV_inverter
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//名称
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//所属馈线ID
int		BASE_VOLTAGE;		//所属电压等级
unsigned char		res0[4];
SG_INT64		NODEID;		//并网点编号
double		RATE_CAPACITY;		//额定容量
double		ACTIVE_POWER;		//有功出力
double		REACTIVE_POWER;		//无功出力
int		CONTROL_MODE;		//控制模式
unsigned char		res1[4];
}model_PV_inverter;
//model_AVC_Node	
typedef struct model_AVC_Node
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//名称
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//所属馈线ID
int		BASE_VOLTAGE;		//所属电压等级
unsigned char		res0[4];
double		VOLTAGE;		//电压幅值
int		UP_STATE;		//电压越上限的离散状态变量
int		DOWN_STATE;		//电压越下限的离散状态变量
int		NORMAL_STATE;		//电压不越限的离散状态变量
unsigned char		res1[4];
}model_AVC_Node;
//model_AVC_Line	
typedef struct model_AVC_Line
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//名称
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//所属馈线ID
int		BASE_VOLTAGE;		//所属电压等级
unsigned char		res0[4];
SG_INT64		START_NODEID;		//起始并网点编号
SG_INT64		END_NODEID;		//结尾并网点编号
double		RESISTANCE;		//电阻
double		REACTANCE;		//电抗
}model_AVC_Line;
//馈线信息表	
typedef struct avc_feeder_info
{ 
SG_INT64		FEEDERID;		//馈线ID
double		ENERGY_LOSS;		//能量损耗
double		MAX_VOLTAGE;		//最高电压值
double		MIN_VOLTAGE;		//最低电压值
double		ENERGY_LOSS_BEFORE;		//优化前能量损耗
double		MAX_VOLTAGE_BEFORE;		//优化前最高电压值
double		MIN_VOLTAGE_BEFORE;		//优化前最低电压值
}avc_feeder_info;
//逆变器出力历史优化结果表	
typedef struct avc_Inverter_Histrory
{ 
SG_INT64		INVERTERID;		//逆变器id
double		ACTIVE_POWER;		//有功出力
double		REACTIVE_POWER;		//无功出力
int		CONTROL_MODE;		//控制模式
unsigned char		res0[4];
SG_INT64		TIME;		//优化时间
}avc_Inverter_Histrory;
//电容器出力历史优化结果表	
typedef struct avc_compensator_Histrory
{ 
SG_INT64		COMPENSATORID;		//电容器id
double		EACH_CAPACITY;		//每组容量
int		OPERATION_NUM;		//投运组数
int		MAX_ACT_NUM;		//时段内最大动作次数
SG_INT64		TIME;		//优化时间
}avc_compensator_Histrory;
//负荷预测表	
typedef struct avc_predictive_load
{ 
SG_INT64		LOADID;		//负荷ID
SG_INT64		NODEID;		//并网点编号
double		ACTIVE_POWER;		//有功出力
double		REACTIVE_POWER;		//无功出力
int		TIME;		//0~95或0~23，与Type配合使用
int		TYPE;		//0：分钟级别；1：小时级别
}avc_predictive_load;
//光伏预测表	
typedef struct avc_predictive_PV
{ 
SG_INT64		PVID;		//光伏ID
SG_INT64		NODEID;		//并网点编号
double		ACTIVE_POWER;		//有功出力
int		TIME;		//0~96或0~24，与Type配合使用
int		TYPE;		//0：分钟级别；1：小时级别
}avc_predictive_PV;
//model_d_ac	
typedef struct model_d_ac
{ 
SG_INT64		ID;		//系统设备ID
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
double		TSetmax;		//空调温度设定上限
double		TSetmin;		//空调温度设定下限
double		ETAmin;		//能效系数最小值
double		ETAmax;		//能效系数最大值
double		Racmin;		//热阻最小值
double		Racmax;		//热阻最大值
double		Cacmin;		//热容最小值
double		Cacmax;		//热容最大值
double		TSetAve;		//设置温度期望
double		DeltaTmin;		//设定温度下调极限
double		DeltaTmax;		//设定温度上调极限
double		Rlow;		//随电价上浮斜率
double		Rhigh;		//随电价下浮斜率
double		Pinuse_a;		//Sigmoid形状参数
double		Pinuse_b;		//Sigmoid形状参数
double		Pindr_a;		//Sigmoid形状参数
double		Pindr_b;		//Sigmoid形状参数
double		ACPara1;		//敏感系数1
double		ACPara2;		//敏感系数2
double		ACPara3;		//敏感系数3
double		ACPara4;		//敏感系数4
}model_d_ac;
//model_d_5g	
typedef struct model_d_5g
{ 
SG_INT64		ID;		//系统设备ID
double		GTrafficMax;		//5G天线最大利用率
double		PMode1;		//1档功率
double		PMode2;		//2档功率
double		PMode3;		//3档功率
double		PMode4;		//4档功率
}model_d_5g;
//model_d_evcar	
typedef struct model_d_evcar
{ 
SG_INT64		ID;		//系统设备ID
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
double		CarBattry;		//平均电池容量
double		ChargeSlow;		//慢充功率
double		ChargeHigh;		//快充功率
double		Charge1;		//每日一充用户占比
double		Charge2;		//每日两充用户占比
double		Charge3;		//每日三充用户占比
double		ChomeAV;		//家用充电均值
double		ChomeSD;		//家用充电标准差
double		CCompAV;		//公司充电均值
double		CCompSD;		//公司充电标准差
double		CShopAV;		//商场充电均值
double		CShopSD;		//商场充电标准差
double		ChargeEff;		//充电效率
double		CarQAV;		//初始电荷分布均值
double		CarQSD;		//初始电荷分布标准差
double		CarPara1;		//参与调节占比1
double		CarPara2;		//参与调节占比2
double		CarPara3;		//参与调节占比3
double		CarPara4;		//参与调节占比4
}model_d_evcar;
//热水器表	
typedef struct model_waterheater
{ 
SG_INT64		ID;		//系统设备ID
char		name[64];		//名称
char		mRID[64];		//设备唯一ID
double		DeltaTW;		//温度设定允许偏移
double		Twhmax;		//最大温度限制
double		Twhmin;		//最小温度限制
double		WHcapacity;		//热水器容量
double		WHPower;		//热水器额定功率
double		TankAmax;		//水箱表面积最大值
double		TankAmin;		//水箱表面积最小值
double		TankRmin;		//水箱热阻最小值
double		TankRmax;		//水箱热阻最大值
double		DeltaWaterEv;		//冷水温度与环境温度之差（设定值�
double		Shift_1;		//无感平移时段数
double		Shift_2;		//微感平移时段数
double		Shift_3;		//中性平移时段数
double		Shift_4;		//强感平移时段数
double		Elast_1;		//无感自弹性系数
double		Elast_2;		//微感自弹性系数
double		Elast_3;		//中性自弹性系数
double		Elast_4;		//强感自弹性系数
double		WH_state;		//初始开关状态
}model_waterheater;
//运行表	
typedef struct Rapa_Operation
{ 
SG_INT64		ID;		//ID
SG_INT64		DeviceID;		//设备ID
int		Time;		//时间（15分钟一个点）
unsigned char		res0[4];
double		Temp;		//室外温度
double		Price;		//电价
double		SHStream;		//热水流速
double		Original;		//原始聚合功率
double		Rapa;		//考虑电价后聚合功率
double		Reserve;		//潜力容量
int		Type;		//类型
unsigned char		res1[4];
}Rapa_Operation;
//日电价表	
typedef struct Rapa_PowerPrice
{ 
int		Time;		//时间（15分钟一个点）
unsigned char		res0[4];
double		Price;		//电价
}Rapa_PowerPrice;
//日室外温度表	
typedef struct Rapa_OutTemp
{ 
int		Time;		//时间（15分钟一个点）
unsigned char		res0[4];
double		Temp;		//室外温度
}Rapa_OutTemp;
//日热水流速表	
typedef struct Rapa_WaterFlow
{ 
int		Time;		//时间（15分钟一个点）
unsigned char		res0[4];
double		SHStream;		//热水流速
}Rapa_WaterFlow;
//区域表	
typedef struct MODEL_REGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//名称
char		PSRID[255];		//资源ID
unsigned char		res0[1];
}MODEL_REGION;
//子区域表	
typedef struct MODEL_SUBREGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//名称
SG_INT64		OF_REGION;		//所属区域
char		PSRID[255];		//资源ID
unsigned char		res0[1];
}MODEL_SUBREGION;
//光伏功率倒送异常修复表	
typedef struct DAS_POWER_REVERSE
{ 
int		ID;		//ID
int		TIME;		//时间


SG_INT64		OF_DEVICE;		//所属台区号
float		B_PV_P;		//调节前光伏有功功率
float		B_PV_Q;		//调节前光伏无功功率
float		A_PV_P;		//调节后光伏有功功率
float		A_PV_Q;		//调节后光伏无功功率
float		B_EC_U;		//调节前负荷电压
float		A_EC_U;		//调节后负荷预测电压
float		QF;		//无功功率调节因数
unsigned char		res0[4];
}DAS_POWER_REVERSE;
//光伏预测表	
typedef struct DAS_PV_PREDICTION
{ 
SG_INT64		ID;		//记录号
SG_INT64		DeviceID;		//设备ID
int		MeasType;		//量测类型
float		Value;		//量测值
SG_INT64		Time;		//时间戳
SG_INT64		PredictionID;		//预测ID
}DAS_PV_PREDICTION;
//电动汽车充电管理表	
typedef struct DAS_EV_MAN
{ 
SG_INT64		ID;		//记录号
int		CHARGETIMESTART;		//充电开始时间
int		CHARGETIMEEND;		//充电结束时间
int		DISCHARGETIMESTART;		//放电开始时间
int		DISCHARGETIMEEND;		//放电结束时间
SG_INT64		OF_DEVICE;		//所属充电设备
}DAS_EV_MAN;
//三相不平衡处理表	
typedef struct DAS_UNBALANCE
{ 
SG_INT64		ID;		//记录号
char		PhaseA[1024];		//A相设备总集
char		PhaseB[1024];		//B相设备总集
char		PhaseC[1024];		//C相设备总集
int		StartTime;		//起始时间点
int		EndTime;		//结束时间点
SG_INT64		OF_DEVICE;		//所属台区ID
}DAS_UNBALANCE;
//测试表	
typedef struct MODEL_TEST
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
int		NVALUE;		//整型值
float		FVALUE;		//浮点值
float		MPOWER_P;		//有功测量值
float		MPOWER_Q;		//无功测量值
float		IPOWER_P;		//有功计算值
float		IPOWER_Q;		//无功计算值
}MODEL_TEST;
//高级应用配置表	
typedef struct DAS_CONFIG
{ 
int		ID;		//ID
char		APPCODE[64];		//应用名称
int		APPID;		//应用编号
int		PARAID;		//参数编号
char		NAME[64];		//参数名称
char		DESC[255];		//参数描述
unsigned char		res0[1];
int		TYPE;		//参数类型
char		CHVALUE[255];		//字符串值
unsigned char		res1[1];
int		INTVALUE;		//整型值
float		FLOATVALUE;		//浮点值
}DAS_CONFIG;
//model_thermalgenerator	
typedef struct model_thermalgenerator
{ 
SG_INT64		ID;		//编号
double		MAX_P;		//最大有功
double		MAX_PF;		//功率因数上限
double		MAX_Q;		//最大无功
double		MIN_P;		//最小有功
double		MIN_PF;		//功率因数下限
double		MIN_Q;		//最小无功
double		MPOWER_I;		//电流值
double		MPOWER_P;		//有功功率
double		MPOWER_Q;		//无功功率
double		MPOWER_U;		//电压值
char		NAME[64];		//名称
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属变电站
char		PSRID[64];		//资源ID
double		RATED_P;		//额定功率
unsigned char		USEABLE;		//光伏状态
unsigned char		res0[7];
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压值
double		IPOWER_I;		//电流值
unsigned char		OF_BASE_VOLTAGE;		//基准电压
unsigned char		res1[7];
}model_thermalgenerator;
//MODEL_HYDROPOWER	
typedef struct MODEL_HYDROPOWER
{ 
SG_INT64		ID;		//编号
double		MAX_P;		//最大有功
double		MAX_PF;		//功率因数上限
double		MAX_Q;		//最大无功
double		MIN_P;		//最小有功
double		MIN_PF;		//功率因数下限
double		MIN_Q;		//最小无功
double		MPOWER_I;		//电流值
double		MPOWER_P;		//有功功率
double		MPOWER_Q;		//无功功率
double		MPOWER_U;		//电压值
char		NAME[64];		//名称
SG_INT64		OF_FEEDER;		//所属馈线
SG_INT64		OF_SUBSTATION;		//所属变电站
char		PSRID[64];		//资源ID
double		RATED_P;		//额定功率
unsigned char		USEABLE;		//光伏状态
unsigned char		res0[7];
double		IPOWER_P;		//有功功率
double		IPOWER_Q;		//无功功率
double		IPOWER_U;		//电压值
double		IPOWER_I;		//电流值
unsigned char		OF_BASE_VOLTAGE;		//基准电压
unsigned char		res1[7];
}MODEL_HYDROPOWER;
//model_d_acline_dot	
typedef struct MODEL_D_ACLINE_DOT
{ 
SG_INT64		ID;		//编号
char		NAME[32];		//名称
double		P_VALUE;		//有功功率
double		Q_VALUE;		//无功功率
double		CURRENT;		//电流
double		VOLTAGE;		//电压值
SG_INT64		OF_ACLINE_SEGMENT;		//所属交流导线段
SG_INT64		OF_TERMINAL;		//所属端子
}MODEL_D_ACLINE_DOT;
//MODEL_ENERGY_SOURCE	
typedef struct MODEL_ENERGY_SOURCE
{ 
SG_INT64		ID;		//编号
char		NAME[64];		//描述
char		ALIAS[100];		//别名
unsigned char		OF_BASE_VOLTAGE;		//电压等级
unsigned char		res0[3];
SG_INT64		OF_SUBSTATION;		//厂站代码
SG_INT64		OF_FEEDER;		//馈线代码
int		TOPO_ISLAND;		//拓扑电气岛号
unsigned char		res1[4];
double		MPOWER_P;		//有功
double		MPOWER_Q;		//有功
double		MPOWER_U;		//有功
double		MPOWER_I;		//有功
double		IPOWER_P;		//有功
double		IPOWER_Q;		//无功
double		IPOWER_U;		//电压
double		IPOWER_I;		//电流
unsigned char		ATTRIBUTE;		//节点类型：1平衡节点；2功率节点�
unsigned char		res2[7];
}MODEL_ENERGY_SOURCE;
//BASE_VOLT_DEF	
typedef struct BASE_VOLT_DEF
{ 
SG_INT64		ID;		//ID
char		EN_NAME[32];		//英文名
char		CN_NAME[32];		//中文名
double		STD_VAL;		//基准值
double		H_LMT;		//基准上限
double		L_LMT;		//基准下限
}BASE_VOLT_DEF;
//MODEL_TOPOLOGICAL_ISLAND	
typedef struct MODEL_TOPOLOGICAL_ISLAND
{ 
SG_INT64		ID;		//编号
char		NAME[32];		//名称
int		CONTAINSTOPOLOGICALNODE;		//包含拓扑节点数量
int		FIRSTPSR;		//首设备下标
int		NUMBEROFPSR;		//设备数目
unsigned char		ISCONVERGED;		//是否收敛
unsigned char		res0[3];
double		LOADPOWERP;		//岛内总负荷有功
double		LOADPOWERQ;		//岛内总负荷无功
double		SUMLOSSP;		//岛内总损耗有功
double		SUMLOSSQ;		//岛内总损耗无功
unsigned char		ISLAND;		//是否孤岛
unsigned char		CLOSEDLOOP;		//是否合环
unsigned char		res1[6];
}MODEL_TOPOLOGICAL_ISLAND;
//MODEL_TOPOLOGICAL_NODE	
typedef struct MODEL_TOPOLOGICAL_NODE
{ 
SG_INT64		ID;		//编号
char		NAME[32];		//名称
SG_INT64		OF_TOPOLOGICALISLAND;		//所属拓扑岛
int		CONTAINSCONNECTIVITYNODE;		//包含连接节点数量
int		NUMBEROFPSR;		//设备数量
double		VLTMAG;		//电压幅值
double		VLTANGLE;		//电压相角
}MODEL_TOPOLOGICAL_NODE;
#endif 
