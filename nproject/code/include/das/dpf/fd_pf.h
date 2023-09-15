
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

	struct  ID			//�豸��ʶ�ṹ����
	{
		unsigned long    tsub;					//��ʾ�ڶ�Ӧ���������е��±�
		unsigned short   tid;					//��ʾ����������,������ݶ�������ʶ
	};
	struct  LLine		//��·�����ṹ����
	{
		int Node_No[2];	//��·���˽ڵ���(��):0-��ڵ�;1-�ҽڵ�
		int Flag;		//��·���ͱ�־:0-��֧ͨ·;1��2-��ѹ��֧·������,1-�Ǳ�׼��������ڵ�,2-�Ǳ�׼������Ҳ�ڵ㡣�Խӵ�֧·�����ҽڵ������ţ���ͬ��
		double RXBK[3];	//0-R;1-X;2-Bc/2 �� K
		ID	id;			//��·ID
	};

	struct  Generator	//����������ṹ����
	{
		int Node_No;	//������ڵ���(��)
		int Flag;		//������ڵ����ͱ�־:0-ƽ��ڵ�;1-PQ�ڵ�;2-PV�ڵ�
		double PQV[2];	//��ƽ��ڵ㣬0-V,1-Angle;��PQ�ڵ�,0-P,1-Q;��PV�ڵ�,0-P,1-V��
		ID	id;			//�����ID
	};

	struct  LLoad		//���ɲ����ṹ����
	{
		int Node_No;	//���ɽڵ���(��)
		int Flag;		//���ɽڵ㾲���Ա�־:0-���ƾ�����;1-�ƾ����ԡ�
		double ABC[6];	//PL=a1*V**V+b1*V+c1,QL=a2*V*V+b2*V+c2��0-a1;1-a2;2-b1;3-b2;4-c1;5-c2��
		ID	id;			//����ID
	};

	struct  InitPara
	{
		int Num_Line;			//����·��
		int Num_Gen;			//�ܷ������
		int Num_Load;			//�ܸ�����
		int Num_Node;			//�ܽڵ���
		int Iter_Max;			//�����������ֵ
		int VolIni_Flag;		//����ѹ��ֵ��־:1-��;0-����
		int VolRes_Flag;		//������ѹ(��Ϊ�´γ�ֵ)��־:1-����;0-��������
		double Eps;				//�ڵ㹦��ʧ����ֵ������ֵ
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

	int Node_Name_NewtoOld[NODEMAX];	//�½ڵ������ţ�-->�ɽڵ������ţ�
	int Node_Flag[NODEMAX];				//�ڵ����ͱ�־��0-ƽ��,1-PQ,2-PV
	int Line_NodeName[LINEMAX][2];		//��·�����ҽڵ��������ţ�
	int Line_No_NewtoOld[LINEMAX];		//����·��-->����·��
	int Line_Flag[LINEMAX];				//����·�����ͱ�־:0,1,2˵��ͬLine�ṹ
	int Gen_NodeName[GENERATORMAX];		//������ڵ���½ڵ������ţ�
	int Gen_No_NewtoOld[GENERATORMAX];	//�·����˳���-->�ɷ����˳���
	int Gen_SWNode[SWINGMAX][2];		//ƽ��ڵ����ݣ�0-�½ڵ������ţ�1-��Ӧ�ľɷ����˳���;
	int Gen_PVNode[PVMAX][2];			//�����PV�ڵ����ݣ�0-�½ڵ������ţ�1-��Ӧ�ľɷ����˳���;
	int Gen_PQNode[GENERATORMAX][2];	//�����PQ�ڵ����ݣ�0-�½ڵ������ţ�1-��Ӧ�ľɷ����˳���;
	int Load_NodeName[LOADMAX];			//���ɽڵ���½ڵ������ţ�
	int Load_No_NewtoOld[LOADMAX];		//�¸���˳���-->�ɸ���˳���

	double Y_Diag[NODEMAX][2];				//�ڵ㵼����ĶԽ�Ԫ:0-ʵ�� 1-�鲿��
	double Y_UpTri[NODEMAX*NODEFACTOR][2];	//�ڵ㵼���������ǵķ���Ԫ:0-ʵ��;1-�鲿��
	int Foot_Y_UpTri[NODEMAX*NODEFACTOR];	//�����ǰ���ѹ���洢�ķ���Ԫ�������롣
	int Num_Y_UpTri[NODEMAX];				//�����Ǹ��з���Ԫ�صĸ���
	int No_First_Y_UpTri[NODEMAX];			//�����Ǹ��е�һ������Ԫ����Y_UpTri�е�˳��š�
	int Foot_Y_DownTri[NODEMAX*NODEFACTOR];	//�����ǰ���ѹ���洢�ķ���Ԫ�������롣
	int Num_Y_DownTri[NODEMAX];				//�����Ǹ��з���Ԫ�صĸ���
	int No_First_Y_DownTri[NODEMAX];		//�����Ǹ��е�һ������Ԫ���ڰ���ѹ���洢�����е�˳���
	int No_Y_DownTri_RowtoCol[NODEMAX*NODEFACTOR];	//������ĳ�з���Ԫ����Ӧ�İ���ѹ���洢�����е����

	double Fact_Diag[NODEMAX][2];				//���ӱ�Խ�Ԫ��:0-�й����ӱ�;1-�޹����ӱ�
	double Fact_UpTri[NODEMAX*NODEFACTOR][2];	//���ӱ������Ƿ���Ԫ��:0-�й����ӱ�;1-�޹����ӱ�
	int Foot_Fact_UpTri[NODEMAX*NODEFACTOR][2];	//���ӱ������Ƿ���Ԫ������
	int Num_Fact_UpTri[NODEMAX][2];				//���ӱ������Ǹ��з���ǶԽ�Ԫ�ĸ�����

	double Voltage[NODEMAX][2];						//�ڵ��ѹ:0-��λ�� 1-��ֵ��
	double Current_Const[SWINGMAX*NODEFACTOR][2];	//��������:0-ʵ�� 1-�鲿��
	int Node_Name_Curr_Const[SWINGMAX*NODEFACTOR];	//���������Ľڵ���(��)
	double Power_Const[NODEMAX][2];					//���ڵ�ע�빦�ʲ��䲿��:0-ʵ��;1-�鲿��

	double S_Line[LINEMAX][4];		//��·����:0-Pij,1-Qij,2-Pji,3-Qji
	double S_Count[NODEMAX][2];		//�ڵ����г��߹����ۼ�����:0-ʵ��,1-�鲿��
	double S_Node[NODEMAX][4];		//�ڵ㹦��:0-PG,1-QG,2-PL,3-QL
	double Total_P_Loss;
	double Total_Q_Loss;
	std::vector<double> P_loss_list;
	std::vector<double> Q_loss_list;



	public:

		void Execute();

		//ִ�г�������
		int CalculatePowerFlow(void);

		//��Ŵ����ӳ���
		void Node_Sequen(int &Num_Node, int Num_Line, int Num_Gen, int Num_Load,
			int &Num_Swing, int &Num_GPV, int &Num_GPQ);

		//�γɽڵ㵼�ɾ���1(��������·������ɼ��Ǳ�׼��ȵ�Ӱ��)�ӳ�
		void Y_Bus1(int Num_Node, int Num_Line,/*int Num_Load,*/int Num_Swing);

		//�γɽڵ㵼�ɾ������ӱ�
		void Factor_Table(int Num_Node, int Num_Swing, int Num_GPV, int IterFlag);

		//�γɽڵ㵼�ɾ���2(������·������ɼ��Ǳ�׼��ȵ�Ӱ��)�ӳ�
		void Y_Bus2(int Num_Node, int Num_Line, int Num_Load, int Num_Swing);

		//��ʼ���ӳ�
		void Initial(int Num_Node, int Num_Line, int Num_Load, int Num_Swing,
			int Num_GPV, int Num_GPQ, int &Num_Cur_Const,
			double DVolt[NODEMAX][2],
			int VolIni_Flag);

		//��ȡ��ѹ��ʼ��ֵ(���ڲ��ڵ��)�ӳ�
		void Voltage_Initial(int Num_Node, int Num_Swing);

		//����A��B��˵�C��ֱ��������ʽ��
		void Comp_Mul(double C[2], double A[2], double B[2]);

		//��ڵ㹦��ʧ�����ӳ�(PV�ڵ��dQi=0)
		void PowerDis_Comp(int Num_Node, int Num_Load, int Num_Swing, int Num_GPV,
			int Num_Cur_Const, double Power_Dis[NODEMAX][2],
			double Pij_Sum[NODEMAX][2], double DVolt[NODEMAX][2],
			int Num_Iteration,
			double &Power_Dis_Max);

		//����AX=t���
		void Equ_Calculation(int Num_Node, int Num_Swing,
			double Power_Dis_Correct[NODEMAX], int IterFlag);


		//���ǶȻ��㵽����[-PAI��PAI]
		void TreatAngle(double &angle);

		//��ѹ����(���ڲ��ڵ��)�ӳ�
		void Voltage_Reserve(int Num_Node, int Num_Swing);

		//�������ӳ�
		void Result_Output(int Num_Node, int Num_Line, int Num_Gen, int Num_Load,
			int Num_Swing, int Num_Iteration, double Duration);

		//����A��B�����C��ֱ��������ʽ��
		void Comp_Div(double C[2], double A[2], double B[2]);
};

