

#include "../topana/topana.h"
#include "fd_pf.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

class CRDBLoadSetting;

class TOPANA_DLL_API CDpf : public CDasBase
{

public:
	CDpf();
	CDpf(int appID, const char* appCode=NULL);
	~CDpf();

	bool Init(int schemaHandler, CRDBLoadSetting *pLoadSetting = NULL);

	//计算
	void Exec();

	//读配置表
	int ReadConfig();

	//读配置表、模型表等
	int Read();

	//写结果表
	int Write();

public:
	CTopana *m_pTopana;
	CRDBLoadSetting * m_pLoadSetting;
	CFastDecouplePwrFlw m_pf;

public:
	std::map<uint64_t, int> mapPSR;   //防止两个端点的设备重复被找到传值

private:
	static  const double    MulS;
	static	const double	RatedS;
	static	const double	InitV;
	static	const double	MaxVoltRatio;
	static  const double	MinVoltRatio;
	static  const double	MinMeasDeadBand;
	static  const double	MismatchDeadBand;
	static  const short     MinTopIslandNode;


	enum END_DEFINE { I_END, J_END };


	/**********建立内存库***********/
public:
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
	std::map<uint64_t, oneTI> vTIList;                              //所有TI列表,uint64_t对应拓扑节点号


		
																																	/***************功能函数******************/
public: 

	void MapDataInput();   //map数据导入程序

public:
	struct PfPara
	{
		float ptol;
		float qtol;
		int maxiter;
	};

	struct PowerSt
	{
		double p;
		double q;
		double i;
		double u;
		float s;
		float pf;
	};

	struct branch_flow
	{
		double Pij;
		double Qij;
		double Pji;
		double Qji;
		double Ii;
		double Ixyi[2];
		double Ij;
		double Ixyj[2];
		unsigned int ind;
		unsigned int jnd;
		double  Vi;
		double  thetai;
		double  Vj;
		double  thetaj;
	};
	struct gen_flow
	{
		double fP;
		double fQ;
		double fI;
		double fU;
	};
	struct node_flow
	{
		double V;
		double theta;
		double PG;
		double QG;
		double PL;
		double QL;
	};

	struct BranchMap
	{
		int ind;
		int jnd;
		CFastDecouplePwrFlw::ID* id;
	};



	public:


		std::vector<double> P_loss_list;
		std::vector<double> Q_loss_list;


		std::map<CFastDecouplePwrFlw::ID*, branch_flow>branch_data;	//支路潮流

		std::map<CFastDecouplePwrFlw::ID*, gen_flow>gnld_data;				//电源潮流

		std::map<uint64_t, node_flow>node_data;				//节点潮流

public:
	/*******基本功能函数*******/
	//由端子mRID获取对应端子记录值
	oneTerminal Get_Terminal_To_TStruct(uint64_t mrid);
	//由连接节点mRID获取对应连接节点记录值
	oneCN Get_CN_To_CNStruct(uint64_t mrid);
	//由拓扑节点mRID获取对应拓扑节点记录值
	oneTN Get_TN_To_TNStruct(uint64_t mrid);


	/*******父子关系调用功能函数（本功能函数基于内存库有数据的基础上，必须在内存库有数据写入后才能生效）********/
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

	/***********获取各设备私有部分记录************/
	//方式1(推荐使用)：通过设备端子来获得设备私有部分记录
	//由线路端子mRID获取线路私有部分记录
	oneAcline Get_AclineTM_To_AclineStrust(uint64_t mrid);

	//由断路器端子mRID获取断路器私有部分记录
	oneBreaker Get_BreakerTM_To_BreakerStrust(uint64_t mrid);

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

	//由母线mRID获取母线私有部分记录
	oneBusbar Get_BusbarTM_To_BusbarStrust(uint64_t mrid);


	//方式2(不推荐使用)：通过设备mRID来获得设备私有部分记录
	//由线路mRID获取线路私有部分记录
	oneAcline Get_Acline_To_AclineStrust(uint64_t mrid);

	//由断路器mRID获取断路器私有部分记录
	oneBreaker Get_Breaker_To_BreakerStrust(uint64_t mrid);




	/****************应用函数******************************/
	void InitDataInput();//数据输入初始化程序

	void InitDbResults();//初始化网络潮流结果

	void PfSaveACLineResults(int sub, float p, float q,float i, float ploss, float qloss);//保存单一馈线段结果

	void PfSaveACLineResults(int sub, float pij, float qij, float pji, float qji,float ii, float ij, float vi, float vj);//保存两端馈线段结果
	void PfSaveBusResults(int sub,float vlt, float angl);//保存母线数据

	void PfSavePVArrayResults(int sub,float p, float q, float i, float u);//保存光伏结果
	
	void PfSaveWindGeneratorResults(int sub,float p, float q, float i, float u);//保存风机结果
	
	void PfSaveBatteryEnergyStorageResults(int sub,float p, float q, float i, float u);//保存储能结果
	
	void PfSaveThermalGeneratorResults(int sub,float p, float q, float i, float u);//保存燃气轮机结果
	
	void PfSaveHydrpwrInfoResults(int sub,float p, float q, float i, float u);//保存水电结果

	void PfSaveEnergyConsumerResults(int sub,float p, float q, float i, float u);//保存负荷结果

	void PfSaveBreakerResults(int sub,float p, float q, float i, float u);//保存开关结果

	void PfSaveEnergySourceResults( int sub, float pg, float qg, float i, float voltage);//保存电源结果





	void SetMpowerToIpower();//负荷，分布式电源上的有功无功量测值设置到潮流值

	void Execute(); //运行潮流计算

	void Calculate_PQ_pflow(std::map<uint64_t, oneTI>::iterator it_vTIList);//计算以拓扑岛为单位的潮流

	void DataInput(std::map<uint64_t, oneTI>::iterator it_vTIList);//输入潮流计算数据
																   //初设化map结构
	void initmapPSR();//初始化map结构

	float PerUnitConvert(float x, float vbase, float sbase);//标幺值转换

	float PerUnit2S(float x, float sbase, float ratio);

	float SPerUnitConvert(float x, float sbase, float ratio);//功率标幺值转换


	void DeleteAndInitial();//数据清理程序

	void GetParaSettings(double& Eps, int& Iter_Max);//获取参数配置

	void PfGetPara(PfPara& para);//获取参数配置

								 
	void SaveTopIslandResults(std::map<uint64_t, oneTI>::iterator it_vTIList);//拓扑岛计算结果入库

    void SetFeederSegmentBreakerPower(std::map<uint64_t, oneTI>::iterator it_vTIList);//从相邻设备获取开关潮流值（交流线段）

	bool SwapBranchFlow(BranchMap& elm1, BranchMap& elm2);

	void InitRunPFlow();


	uint64_t SearchFeederSegmentFromTerminal(uint64_t pterm1_s, int& iend);


	bool SetBreakerPowerByEnd(std::map<uint64_t, oneBreaker>::iterator it_vBreaker_List, END_DEFINE iend);

	//关闭表
	void CloseTable(CSgRDBTable &rdbTable);

	void DataOutPut();//数据库输出函数


	private:
		void dpf();//调用函数

		int m_SchemaHandler;//内存库句柄
		bool m_OpenShareMemory_Success;//创建共享内存是否成功
};


