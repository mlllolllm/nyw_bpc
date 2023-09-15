
#include "../topana/topana.h"
#include "math.h"
#include <stdio.h>
#include <string>
#include <vector>


class TOPANA_DLL_API CFastDecouplePwrFlw
{

public:
	CFastDecouplePwrFlw();
	~CFastDecouplePwrFlw();
public:

	struct  ID			//设备标识结构定义
	{
		unsigned long    tsub;					//表示在对应类索引段中的下标
		unsigned short   tid;					//表示本索引对象,向的数据对象的类标识
	};
	struct  LLine		//线路参数结构定义
	{
		int Node_No[2];	//线路两端节点名(号):0-左节点;1-右节点
		int Flag;		//线路类型标志:0-普通支路;1、2-变压器支路。其中,1-非标准变比在左侧节点,2-非标准变比在右侧节点。对接地支路，左右节点名（号）相同。
		double RXBK[3];	//0-R;1-X;2-Bc/2 或 K
		ID	id;			//线路ID
	};

	struct  Generator	//发电机参数结构定义
	{
		int Node_No;	//发电机节点名(号)
		int Flag;		//发电机节点类型标志:0-平衡节点;1-PQ节点;2-PV节点
		double PQV[2];	//对平衡节点，0-V,1-Angle;对PQ节点,0-P,1-Q;对PV节点,0-P,1-V。
		ID	id;			//发电机ID
	};

	struct  LLoad		//负荷参数结构定义
	{
		int Node_No;	//负荷节点名(号)
		int Flag;		//负荷节点静特性标志:0-不计静特性;1-计静特性。
		double ABC[6];	//PL=a1*V**V+b1*V+c1,QL=a2*V*V+b2*V+c2。0-a1;1-a2;2-b1;3-b2;4-c1;5-c2。
		ID	id;			//负荷ID
	};

	struct  InitPara
	{
		int Num_Line;			//总线路数
		int Num_Gen;			//总发电机数
		int Num_Load;			//总负荷数
		int Num_Node;			//总节点数
		int Iter_Max;			//迭代次数最大值
		int VolIni_Flag;		//读电压初值标志:1-读;0-不读
		int VolRes_Flag;		//保留电压(作为下次初值)标志:1-保留;0-不保留。
		double Eps;				//节点功率失配量值收敛限值
		double Total_Gen_P;
		double Total_Gen_Q;
		double Total_Load_P;
		double Total_Load_Q;
		bool Converged;
	};

	enum ERR_CODE {
		CODE_OK = 0,
		CODE_INVALID_VOLTMEAS = 1,
		CODE_NO_VOLTMEAS = 2
	};

	enum {
		MAX_TOL = 999999,
		MIN_TOL = 1000,
		LINEMAX = 500,
		GENERATORMAX = 50,
		LOADMAX = 200,
		NODEMAX = 200,
		SWINGMAX = 20,
		PVMAX = 500,
		NODEFACTOR = 10,
		VIRTUAL_DEVICE = 65535
	};

	static const double Deg_to_Rad;
	static const double Rad_to_Deg;
	static const double SinglePai;
	static const double DoublePai;
	InitPara inipara;

	LLine		LLine[LINEMAX];
	Generator	GGen[GENERATORMAX];
	LLoad		LLoad[LOADMAX];

	int Node_Name_NewtoOld[NODEMAX];	//新节点名（号）-->旧节点名（号）
	int Node_Flag[NODEMAX];				//节点类型标志：0-平衡,1-PQ,2-PV
	int Line_NodeName[LINEMAX][2];		//线路的左、右节点新名（号）
	int Line_No_NewtoOld[LINEMAX];		//新线路号-->旧线路号
	int Line_Flag[LINEMAX];				//新线路的类型标志:0,1,2说明同Line结构
	int Gen_NodeName[GENERATORMAX];		//发电机节点的新节点名（号）
	int Gen_No_NewtoOld[GENERATORMAX];	//新发电机顺序号-->旧发电机顺序号
	int Gen_SWNode[SWINGMAX][2];		//平衡节点数据：0-新节点名（号）1-对应的旧发电机顺序号;
	int Gen_PVNode[PVMAX][2];			//发电机PV节点数据：0-新节点名（号）1-对应的旧发电机顺序号;
	int Gen_PQNode[GENERATORMAX][2];	//发电机PQ节点数据：0-新节点名（号）1-对应的旧发电机顺序号;
	int Load_NodeName[LOADMAX];			//负荷节点的新节点名（号）
	int Load_No_NewtoOld[LOADMAX];		//新负荷顺序号-->旧负荷顺序号

	double Y_Diag[NODEMAX][2];				//节点导纳阵的对角元:0-实部 1-虚部。
	double Y_UpTri[NODEMAX*NODEFACTOR][2];	//节点导纳阵上三角的非零元:0-实部;1-虚部。
	int Foot_Y_UpTri[NODEMAX*NODEFACTOR];	//上三角按行压缩存储的非零元的列足码。
	int Num_Y_UpTri[NODEMAX];				//上三角各行非零元素的个数
	int No_First_Y_UpTri[NODEMAX];			//上三角各行第一个非零元素在Y_UpTri中的顺序号。
	int Foot_Y_DownTri[NODEMAX*NODEFACTOR];	//下三角按行压缩存储的非零元的列足码。
	int Num_Y_DownTri[NODEMAX];				//下三角各行非零元素的个数
	int No_First_Y_DownTri[NODEMAX];		//下三角各行第一个非零元素在按行压缩存储序列中的顺序号
	int No_Y_DownTri_RowtoCol[NODEMAX*NODEFACTOR];	//下三角某行非零元所对应的按列压缩存储序列中的序号

	double Fact_Diag[NODEMAX][2];				//因子表对角元素:0-有功因子表;1-无功因子表。
	double Fact_UpTri[NODEMAX*NODEFACTOR][2];	//因子表上三角非零元素:0-有功因子表;1-无功因子表。
	int Foot_Fact_UpTri[NODEMAX*NODEFACTOR][2];	//因子表上三角非零元列足码
	int Num_Fact_UpTri[NODEMAX][2];				//因子表上三角各行非零非对角元的个数。

	double Voltage[NODEMAX][2];						//节点电压:0-相位角 1-幅值。
	double Current_Const[SWINGMAX*NODEFACTOR][2];	//常数电流:0-实部 1-虚部。
	int Node_Name_Curr_Const[SWINGMAX*NODEFACTOR];	//常数电流的节点名(号)
	double Power_Const[NODEMAX][2];					//各节点注入功率不变部分:0-实部;1-虚部。

	double S_Line[LINEMAX][4];		//线路功率:0-Pij,1-Qij,2-Pji,3-Qji
	double S_Count[NODEMAX][2];		//节点所有出线功率累加数组:0-实部,1-虚部。
	double S_Node[NODEMAX][4];		//节点功率:0-PG,1-QG,2-PL,3-QL
	double Total_P_Loss;
	double Total_Q_Loss;
	std::vector<double> P_loss_list;
	std::vector<double> Q_loss_list;



	public:

		void Execute();

		//执行潮流计算
		int CalculatePowerFlow(void);

		//序号处理子程序
		void Node_Sequen(int &Num_Node, int Num_Line, int Num_Gen, int Num_Load,
			int &Num_Swing, int &Num_GPV, int &Num_GPQ);

		//形成节点导纳矩阵1(不包括线路充电容纳及非标准变比的影响)子程
		void Y_Bus1(int Num_Node, int Num_Line,/*int Num_Load,*/int Num_Swing);

		//形成节点导纳矩阵因子表
		void Factor_Table(int Num_Node, int Num_Swing, int Num_GPV, int IterFlag);

		//形成节点导纳矩阵2(包括线路充电容纳及非标准变比的影响)子程
		void Y_Bus2(int Num_Node, int Num_Line, int Num_Load, int Num_Swing);

		//初始化子程
		void Initial(int Num_Node, int Num_Line, int Num_Load, int Num_Swing,
			int Num_GPV, int Num_GPQ, int &Num_Cur_Const,
			double DVolt[NODEMAX][2],
			int VolIni_Flag);

		//读取电压初始化值(按内部节点号)子程
		void Voltage_Initial(int Num_Node, int Num_Swing);

		//复数A和B相乘得C（直角坐标形式）
		void Comp_Mul(double C[2], double A[2], double B[2]);

		//求节点功率失配量子程(PV节点的dQi=0)
		void PowerDis_Comp(int Num_Node, int Num_Load, int Num_Swing, int Num_GPV,
			int Num_Cur_Const, double Power_Dis[NODEMAX][2],
			double Pij_Sum[NODEMAX][2], double DVolt[NODEMAX][2],
			int Num_Iteration,
			double &Power_Dis_Max);

		//方程AX=t求解
		void Equ_Calculation(int Num_Node, int Num_Swing,
			double Power_Dis_Correct[NODEMAX], int IterFlag);


		//将角度换算到区间[-PAI，PAI]
		void TreatAngle(double &angle);

		//电压保存(按内部节点号)子程
		void Voltage_Reserve(int Num_Node, int Num_Swing);

		//结果输出子程
		void Result_Output(int Num_Node, int Num_Line, int Num_Gen, int Num_Load,
			int Num_Swing, int Num_Iteration, double Duration);

		//复数A和B相除得C（直角坐标形式）
		void Comp_Div(double C[2], double A[2], double B[2]);
};

