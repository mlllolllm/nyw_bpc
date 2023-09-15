#ifndef TOPANA_H_
#define TOPANA_H_
#include "ACE_Includes.h"
#pragma once

#ifdef TOPANA_DLL
#define TOPANA_DLL_API ACE_Proper_Export_Flag
#else
#define TOPANA_DLL_API ACE_Proper_Import_Flag
#endif

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include "dasbase/dasbase.h"

class CSgRDBTable;

//配置项记录的说明
enum {
	//设备列表标识-各表OID前三位
	tid_energySource = 300,
	tid_busbarSection = 207,
	tid_Terminal = 171,
	tid_CNNode = 172,
	tid_TopologicalNode = 173,
	tid_TopologicalIsland = 174,
	tid_breaker = 209,
	tid_disconnector = 210,
	tid_groundDisconnector = 211,
	tid_aCLineSegment = 252,
	tid_AclineDot = 253,
	tid_energyConsumer = 301,
	tid_windGenerator = 361,
	tid_pVArray = 362,
	tid_ThermalGenerator = 132,
	tid_batteryEnergyStorage = 364,
	tid_HydroPower = 131,
	tid_transformer = 204
};

//节点类型
enum {
	PV = 1,
	PQ = 2,
	Balance = 3
};

struct oneBaseVolt
{
	uint64_t mRID;								//mRID
	float STD_VAL;                              //基准值
};

struct oneTerminal
{
	uint64_t mRID;								//mRID
	uint64_t BelongtoCN;						//所属CN的mRID
	uint64_t BelongtoPSR;						//所属设备的mRID
	int PSR_ListID;                             //所属设备表简易标识(前三位数字)
};

struct oneCN
{
	uint64_t mRID;									//mRID
	std::vector<uint64_t> vContainsterminal;		//包含端子
	uint64_t BelongtoTN;							//所属拓扑节点
	uint64_t BelongtoTI;							//所属拓扑岛——未赋值，为0
	uint64_t Base_Voltage;             	     	    //基准电压
	float MemberofVoltageLevel;                     //所属电压等级
};

struct oneTN
{
	uint64_t mRID;	                            //mRID
	std::string Name;                                //TN节点名称
	int mSub;
	int firstPSR;                               //首设备下表
	int numberOfPSR;			    			//包含设备数量
	uint64_t BelongtoTI;						//所属拓扑岛
	std::vector<uint64_t> vContainsCNlist;		//包含CN列表
	std::vector<uint64_t> vContainsPSRlist;		//包含连接设备列表
	float vltMag;                               //电压幅值
	float vltAlgle;                             //电压相角
};

struct oneTI
{
	uint64_t mRID;							    	//mRID
	std::string Name;                                //TN节点名称
	int mSub;
	int firstPSR;					    		//首设备下表
	int numberOfPSR;					    	//包含设备数量
	bool isLand;
	std::vector<uint64_t> vContainsTNlist;		//包含TN列表
	std::vector<uint64_t> vContainsPSRlist;		//包含设备列表
	float LoadPowerP;                           //岛内总负荷有功
	float LoadPowerQ;                           //岛内总负荷无功
	float SumLossP;                             //岛内总损耗有功
	float SumLossQ;                             //岛内总损耗无功
};

//所有物理设备公共字段部分(用于拓扑分析、建立设备父子共生及非共生关系)
struct oneDev
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	uint64_t Of_Feeder;                         //所属馈线mRID
	int Base_Voltage;             	    	    //基准电压
	uint64_t MemberofTI_mRID;		     		//所属拓扑岛mRID
	int MemberofTI;                             //所属拓扑岛下标
	std::vector<uint64_t> vContainsterminal;	//设备包含端子列表
	int DevListName;                            //设备表的标识(mRID前三位)
};

struct oneAcline
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	float R;                                    //电阻R
	float X;                                    //电抗
	float bch;                                  //正序电纳
	float p_value;                              //有功功率
	float q_value;                              //无功功率
	float ploss_value;                          //有功损耗（单位MW）
	float qloss_value;                          //无功损耗（单位Mvar）
	float current;                              //线路电流
	float ratedA;                               //承载电流容量
	float ovrLmtRate;                           //过载率
	bool  limitupI;                             //电流值越上限
	std::vector<uint64_t> vAclineDot;             //线路值
	float nominalVoltage;                        //通常电压
};

struct oneAclineDot
{
	uint64_t mRID;
	float p_value;                              //有功功率
	float q_value;                              //无功功率
	float current;                              //线路电流
	float voltage;                              //电压值
	uint64_t BelongtoTerm;                      //所属线路的端子
	uint64_t BelongtoPSR;						//所属线路的mRID
};

struct oneBusbar
{
	uint64_t mRID;								//mRID
	int mSub;
	std::string Name;                                //设备名称
	float vltAngle;                          	//电压相角
	float voltage;                              //电压
	float MemberOfVoltageLevel;                 //所属电压等级
};

struct oneBreaker
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	int openstate;                              //开关状态(0————闭合、1————开断)
	int breaker_type;                           //出口断路器标识(0——普通开关、2——出口开关、1——联络开关) 
	float p_value;                              //有功功率
	float q_value;                              //无功功率
	float current;                              //线路电流
	float voltage;                              //电压值
};

struct oneDisconnector
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	int openstate;                              //开关状态(0————闭合、1————开断)
};

struct oneGroundDisconnector
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	int openstate;                              //开关状态(0————闭合、1————开断)
};

struct oneBatteryStorage
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	float SOCState;                             //SOC状态
	float SOCLimHigh;                           //SOC上限
	float SOCLimLow;                            //SOC下限
	float rateP;                                //额定功率
	float rateS;                                //额定容量
	float chargeRatio;                          //充电率
	float dischargeRatio;                       //放电率
	float mpower_P;                             //量测有功功率（单位MW）
	float mpower_Q;                             //量测无功功率（单位Mvar）
	float ipower_P;                             //有功功率（单位MW）
	float ipower_Q;                             //无功功率（单位Mvar）
	float voltage;                               //电压
	float current;                               //线路电流
	float MemberOfVoltageLevel;                 //所属电压等级
};

struct oneThermalGenerator
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	float rateP;                                //额定功率
	float mpower_P;                             //量测有功功率（单位MW）
	float mpower_Q;                             //量测无功功率（单位Mvar）
	float ipower_P;                             //有功功率（单位MW）
	float ipower_Q;                             //无功功率（单位Mvar）
	float voltage;                              //电压
	float current;                              //线路电流
	float MemberOfVoltageLevel;                 //所属电压等级
};

struct onePVArray
{
	uint64_t mRID;							     //mRID
	std::string Name;                                 //设备名称
	int mSub;
	float rateP;                                 //额定功率
	float ip_value;                              //有功功率（单位MW）
	float iq_value;                              //无功功率（单位Mvar）
	float mp_value;                              //量测有功功率（单位MW）
	float mq_value;                              //量测无功功率（单位Mvar）
	float voltage;                               //电压
	float current;                               //线路电流
	float MemberOfVoltageLevel;                  //所属电压等级
};

struct oneWindGenerator
{
	uint64_t mRID;							   	 //mRID
	std::string Name;                                 //设备名称
	int mSub;
	float rateP;                                 //额定功率
	float ip_value;                              //有功功率（单位MW）
	float iq_value;                              //无功功率（单位Mvar）
	float mp_value;                              //量测有功功率（单位MW）
	float mq_value;                              //量测无功功率（单位Mvar）
	float voltage;                               //电压
	float current;                               //线路电流
	float MemberOfVoltageLevel;                  //所属电压等级
};

struct oneHydroPower
{
	uint64_t mRID;								 //mRID
	std::string Name;                                 //设备名称
	int mSub;
	float rateP;                                 //额定功率
	float ip_value;                              //有功功率（单位MW）
	float iq_value;                              //无功功率（单位Mvar）
	float mp_value;                              //量测有功功率（单位MW）
	float mq_value;                              //量测无功功率（单位Mvar）
	float voltage;                               //电压
	float current;                               //线路电流
	float MemberOfVoltageLevel;                  //所属电压等级
};

struct oneEnergyConsumer
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	float ip_value;                              //有功功率（单位MW）
	float iq_value;                              //无功功率（单位Mvar）
	float mp_value;                              //量测有功功率（单位MW）
	float mq_value;                              //量测无功功率（单位Mvar）
	float voltage;                               //电压
	float current;                               //线路电流
	float MemberOfVoltageLevel;                 //所属电压等级
};

struct oneEnergySource
{
	uint64_t mRID;								//mRID
	std::string Name;                                //设备名称
	int mSub;
	float p_value;                              //有功功率（单位MW）
	float q_value;                              //无功功率（单位Mvar）
	int attribute;                           //电源点属性
	float voltage;                              //电压
	float current;                              //电流
	float MemberOfVoltageLevel;                 //所属电压等级
};

struct IterWithDepth
{
public:
	uint64_t iterTerminal_mRID;                              //端子的mRID
	int Depth;                                               //搜索深度
};

//oneTNContainAcline
struct Acline_ConnNode
{
	uint64_t Acline_mRID;

	uint64_t oneofTerm;
	uint64_t oneofCN;
	uint64_t oneofTN;

	uint64_t anotherTerm;
	uint64_t anotherCN;
	uint64_t anotherTN;
};

struct oneTopolShrink
{
	uint64_t NewAcline_mRID;             //收缩后，两母线拓扑节点间保留下的线路mRID,由其中线路mRID较大来代替

	float NewAcline_R;                   //收缩后保留下来线路新的电阻
	float NewAcline_X;					 //收缩后保留下来线路新的电抗

	std::vector<uint64_t> vAcline;            //所包含的交流线路
	std::vector<uint64_t> vShrinkAcline;      //存储需要缩减的交流线路
	std::vector<uint64_t> vShrinkBreaker;
	std::vector<uint64_t> vShrinkDisconnector;

	std::map<uint64_t, bool> vTN_type;        //true——需要收缩的拓扑节点；false——不需要收缩的拓扑节点
										 //vTN_NotContainBus
										 //vTN_ContainBus
	std::vector<uint64_t> vTN_NotShrink;	     //所包含不需要收缩的拓扑节点	   
	std::vector<uint64_t> vTN_NeedShrink;     //所包含需要收缩的拓扑节点

	std::vector<uint64_t> vTerminalMemOfTN;   //无需进行缩减的拓扑节点 上的属于此段线路的端子
	uint64_t Terminal_NewAcline;         //vTerminalMemOfTN中NewAcline_mRID所对应的Terminal
	uint64_t Terminal_another;           //vTerminalMemOfTN中另一个Terminal

										 //vector<uint64_t> vCNMemOfTN;         //所包含母线或者联络线上的拓扑节点 上的属于此段线路的CN
};

//TOPANA应用配置信息（TOPANA在DAS_CONFIG中的配置内容）
typedef struct TOPANA_CONFIG
{	
	
}TOPANA_CONFIG;

class TOPANA_DLL_API CTopana : public CDasBase
{
public:
	CTopana();
	CTopana(int appID, const char* appCode=NULL);
	~CTopana();

	//计算
	void Exec();

	//读配置表
	int ReadConfig();

	//读配置表、模型表等
	int Read();

	//写结果表
	int Write();

	//关闭表
	void CloseTable(CSgRDBTable &rdbTable);

	/**********建立内存库***********/
public:

	std::map<uint64_t, oneBaseVolt> vBaseVoltList;

	std::map<uint64_t, oneDev> vDisconnectorList;
	std::map<uint64_t, oneDisconnector> vDisconnector_List;
	std::map<uint64_t, oneDev> vGroundDisconnectorList;
	std::map<uint64_t, oneGroundDisconnector> vGroundDisconnector_List;
	std::map<uint64_t, oneDev> vTransformerList;	                //所有变压器列表,uint64_t对应mRID

																	//存储所有连接设备
	std::map<uint64_t, oneTerminal> vterminalList;			    	//所有terminal列表,uint64_t对应mRID
	std::map<uint64_t, oneCN> vCNList;						    	//所有CN列表,uint64_t对应mRID

																	//存储所有电气设备的共有部分
	std::map<uint64_t, oneDev> vAclineList;				    	    //所有交流线路列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vBusbarList;				        	//所有母线列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vBreakerList;				        //所有断路器列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vEnergyConsumerList;	                //所有负荷列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vBatteryStorageList;	                //所有储能列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vThermalGeneratorList;	            //所有燃气轮机列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vPVArrayList;	                    //所有光伏列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vWindGeneratorList;	                //所有风机列表,uint64_t对应mRID
	std::map<uint64_t, oneDev> vHydroPowerList;	                    //所有水电列表,uint64_t对应mRID

																	//存储所有电气设备的私有部分
	std::map<uint64_t, oneAcline> vAcline_List;				  	    //所有交流线路列表,uint64_t对应mRID
	std::map<uint64_t, oneBusbar> vBusbar_List;					    //所有母线列表,uint64_t对应mRID
	std::map<uint64_t, oneBreaker> vBreaker_List;				    //所有断路器列表,uint64_t对应mRID
	std::map<uint64_t, oneEnergyConsumer> vEnergyConsumer_List;	    //所有负荷列表,uint64_t对应mRID
	std::map<uint64_t, oneBatteryStorage> vBatteryStorage_List;	    //所有储能列表,uint64_t对应mRID
	std::map<uint64_t, oneThermalGenerator> vThermalGenerator_List;	//所有燃气轮机列表,uint64_t对应mRID
	std::map<uint64_t, onePVArray> vPVArray_List;	                //所有光伏列表,uint64_t对应mRID
	std::map<uint64_t, oneWindGenerator> vWindGenerator_List;	    //所有风机列表,uint64_t对应mRID
	std::map<uint64_t, oneHydroPower> vHydroPower_List;	            //所有水电列表,uint64_t对应mRID
	std::map<uint64_t, oneAclineDot> vAclineDot_List;               //所有线路值

																	//存储运行拓扑分析后所生成的内存库表
	std::map<uint64_t, oneDev> vEnergySourceList;	                //所有等效电源列表(设备共有部分),uint64_t对应mRID
	std::map<uint64_t, oneEnergySource> vEnergySource_List;	        //所有等效电源列表(设备私有部分),uint64_t对应mRID
	std::map<uint64_t, oneTN> vTNList;						    	//所有TN列表,uint64_t对应拓扑节点号
	std::map<uint64_t, oneTI> vTIList;						    	//所有TI列表,uint64_t对应拓扑节点号

																	//拓扑收缩后所生成的内存库表
	std::map<uint64_t, oneDev> vAclineShrinkList;
	std::map<uint64_t, oneAcline> vAclineShrink_List;
	std::map<uint64_t, oneDev> vBreakerShrinkList;
	std::map<uint64_t, oneBreaker> vBreakerShrink_List;
	std::map<uint64_t, oneDev> vDisconnectorShrinkList;
	std::map<uint64_t, oneDisconnector> vDisconnectorShrink_List;
	std::map<uint64_t, oneAclineDot> vAclineDotShrink_List;
	std::map<uint64_t, oneTerminal> vTerminalShrinkList;
	std::map<uint64_t, oneCN> vCNShrinkList;
	std::map<uint64_t, oneTN> vTNShrinkList;
	std::map<uint64_t, oneTI> vTIShrinkList;


	/********中间变量*********/
public:
	std::vector<uint64_t> vESTermList;    //储存生成虚拟电源时所生成的端子mRID(写回数据库时使用)
	std::vector<uint64_t> vTIPSRList;	  //设备列表：将设备mRID存入，通过TI的firstPSR和numberOfPSR两个属性确定包含的设备
	std::vector<uint64_t> vTNPSRList;	  //设备列表：将设备mRID存入，通过TN的firstPSR和numberOfPSR两个属性确定包含的设备

										  //默认拓扑为0;若在分析过程中需要进行拓扑收缩，则置为1
	int topana_model = 0;

	/********拓扑搜索变量********/
	//建立每个TN所连接的所有交流线路信息
	std::map<uint64_t, std::vector<Acline_ConnNode>> vTNContainAcline_List;
	//建立每个交流线路两端的TN节点
	std::map<uint64_t, Acline_ConnNode> vAclineMemOfTN;

	std::map<uint64_t, oneTopolShrink> vTopolShrinkList;

	//存储所有拓扑节点mRID及其类型
	//0——包含母线的拓扑节点、1——不包含母线且与两条线路连接的拓扑节点、2——不包含母线且在联络线上的拓扑节点
	std::map<uint64_t, int> vTN_Type;

	std::map<uint64_t, int> vTN_Conn_LineNum;

	/*********应用函数*********/
public:
	//将模型数据从redis数据库中读入内存库
	//这个应用函数里不能使用功能函数
	bool read_model();	

	//增加等效电源(在10kV站内母线处)
	void AddEquivalentSource();

	//形成拓扑节点
	void FormTopologicalNodes();

	//形成拓扑岛
	void FormTopologicalIsland();

	//拓扑结果写回数据库
	void WriteTopoAnaResults();

	//清理数据库中拓扑分析结果
	void CleanTopoAnaResults();

	//清理不良数据
	void CleanbadData();


	/*********拓扑收缩应用函数*********/
public:

	//拓扑收缩主程序
	void TopolShrink();


	/*****拓扑收缩辅助函数******/
	//找到每个TN所连接的所有交流线路信息
	void Get_TN_Conn_Acline();

	//获取每个交流线路两端的TN节点
	void Get_AclineMemOfTN();

	//给所有拓扑节点分类
	void SortTN();
	//判断拓扑节点类型
	int JudgeBusType(uint64_t mrid);

	/***************功能函数（本功能函数基于内存库有数据的基础上，必须在内存库有数据写入后才能生效）******************/
public:
	/*******基本功能函数*******/
	//由端子mRID获取对应端子记录值
	oneTerminal Get_Terminal_To_TStruct(uint64_t mrid);
	//由连接节点mRID获取对应连接节点记录值
	oneCN Get_CN_To_CNStruct(uint64_t mrid);
	//由拓扑节点mRID获取对应拓扑节点记录值
	oneTN Get_TN_To_TNStruct(uint64_t mrid);

	/*******父子关系调用功能函数********/
	//由端子mRID获取对应连接节点mRID
	uint64_t Get_Terminal_To_CNmRID(uint64_t mrid);

	//由端子mRID获取对应设备mRID
	uint64_t Get_Terminal_To_DevmRID(uint64_t mrid);

	//由端子mRID获取对应设备列表名称
	int Get_Terminal_To_DevListID(uint64_t mrid);

	//由连接节点mrid获取对应拓扑节点mrid
	uint64_t Get_CNmRID_To_TNmRID(uint64_t mrid);

	//由连接节点mRID获取对应所有端子集合(端子存放到vector中，存放形式为mRID)
	std::vector<uint64_t> Get_CNmRID_To_Terminal(uint64_t mrid);

	//由拓扑节点mRID获取对应所有连接节点集合(端子存放到vector中，存放形式为mRID)
	std::vector<uint64_t> Get_TNmRID_To_CN(uint64_t mrid);

	//由端子mRID获取对应设备记录值
	//可支持任意设备端子mRID的读取
	oneDev Get_Terminal_To_Devstruct(uint64_t mrid);

	//由拓扑节点mRID获取对应拓扑岛
	uint64_t Get_TNmRID_To_TImRID(uint64_t mrid);

	//由端子mRID获取对应连接节点记录值
	oneCN Get_Terminal_To_CNstruct(uint64_t mrid);

	//由设备mRID获取对应所有端子集合(端子存放到vector中，存放形式为mRID)
	//可支持任意设备列表mRID的读取（适合在不知道该设备mrid属于哪个列表时使用）
	std::vector<uint64_t> Get_DevmRID_To_Terminal(uint64_t mrid);

	/***************其它功能函数***************/
	//由设备mrid获取设备列表标识
	//可支持任意设备列表mRID的读取（适合在不知道该设备mrid属于哪个列表时使用）
	int Get_Devmrid_To_ListID(uint64_t mrid);

	//由设备mrid判断为几端子设备(返回值为设备端子数)
	//可支持任意设备列表mRID的读取（适合在不知道该设备mrid属于哪个列表时使用）
	int Get_Dev_Terminal_Num(uint64_t mrid);

	//若为多端子设备，由一个端子mrid获取另一个端子mrid(这里只实现两端子设备)
	//可支持任意设备端子mRID的读取（适合在不知道该端子属于哪个设备时使用）
	uint64_t Get_oneT_To_nextT(uint64_t mrid);

	//由基准电压ID获取基准电压值
	float Get_voltvalue(uint64_t mrid);

	/***********获取各设备私有部分记录************/
	//方式1(推荐使用)：通过设备端子来获得设备私有部分记录
	//由线路端子mRID获取线路私有部分记录
	oneAcline Get_AclineTM_To_AclineStrust(uint64_t mrid);

	//由断路器端子mRID获取断路器私有部分记录
	oneBreaker Get_BreakerTM_To_BreakerStrust(uint64_t mrid);

	//由闸刀端子mRID获取闸刀私有部分记录
	oneDisconnector Get_DisconnectorTM_To_DisconnectorStrust(uint64_t mrid);

	//由负荷开关端子mRID获取负荷开关私有部分记录
	oneGroundDisconnector Get_GDisconnectorTM_To_GDisconnectorStrust(uint64_t mrid);

	//由电源端子mRID获取电源私有部分记录
	oneEnergySource Get_EnergySourceTM_To_EnergySourceStrust(uint64_t mrid);

	//由负荷端子mRID获取负荷私有部分记录
	oneEnergyConsumer Get_EnergyConsumerTM_To_EnergyConsumerStrust(uint64_t mrid);

	//由储能端子mRID获取储能私有部分记录
	oneBatteryStorage Get_BatteryStorageTM_To_BatteryStorageStrust(uint64_t mrid);

	//由热机端子mRID获取热机私有部分记录
	oneThermalGenerator Get_ThermalGeneratorTM_To_ThermalGeneratorStrust(uint64_t mrid);

	//由光伏端子mRID获取光伏私有部分记录
	onePVArray Get_PVArrayTM_To_PVArrayStrust(uint64_t mrid);

	//由风机端子mRID获取风机私有部分记录
	oneWindGenerator Get_WindGeneratorTM_To_WindGeneratorStrust(uint64_t mrid);

	//由水电端子mRID获取水电私有部分记录
	oneHydroPower Get_HydroPowerTM_To_HydroPowerStrust(uint64_t mrid);


	//方式2(不推荐使用)：通过设备mRID来获得设备私有部分记录
	//由线路mRID获取线路私有部分记录
	oneAcline Get_Acline_To_AclineStrust(uint64_t mrid);

	//由断路器mRID获取断路器私有部分记录
	oneBreaker Get_Breaker_To_BreakerStrust(uint64_t mrid);

	/******测试数据库操作库程序******/
public:	

private:
	/********拓扑分析应用程序******/
	void Topol();

	CSgRDBTable * m_pTabe;//内存表

	TOPANA_CONFIG m_Config;
};

#endif


