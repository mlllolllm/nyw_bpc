

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

	//����
	void Exec();

	//�����ñ�
	int ReadConfig();

	//�����ñ�ģ�ͱ��
	int Read();

	//д�����
	int Write();

public:
	CTopana *m_pTopana;
	CRDBLoadSetting * m_pLoadSetting;
	CFastDecouplePwrFlw m_pf;

public:
	std::map<uint64_t, int> mapPSR;   //��ֹ�����˵���豸�ظ����ҵ���ֵ

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


	/**********�����ڴ��***********/
public:
	//�洢���������豸
	std::map<uint64_t, oneTerminal> vterminalList;			    	//����terminal�б�,uint64_t��ӦmRID
	std::map<uint64_t, oneCN> vCNList;						    	//����CN�б�,uint64_t��ӦmRID

																	//�洢���е����豸�Ĺ��в���
	std::map<uint64_t, oneDev> vAclineList;				    	    //���н�����·�б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vBusbarList;				        	//����ĸ���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vBreakerList;				        //���ж�·���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vEnergyConsumerList;	                //���и����б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vBatteryStorageList;	                //���д����б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vThermalGeneratorList;	            //����ȼ���ֻ��б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vPVArrayList;	                    //���й���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vWindGeneratorList;	                //���з���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneDev> vHydroPowerList;	                    //����ˮ���б�,uint64_t��ӦmRID

																	//�洢���е����豸��˽�в���
	std::map<uint64_t, oneAcline> vAcline_List;				  	    //���н�����·�б�,uint64_t��ӦmRID
	std::map<uint64_t, oneBusbar> vBusbar_List;					    //����ĸ���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneBreaker> vBreaker_List;				    //���ж�·���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneEnergyConsumer> vEnergyConsumer_List;	    //���и����б�,uint64_t��ӦmRID
	std::map<uint64_t, oneBatteryStorage> vBatteryStorage_List;	    //���д����б�,uint64_t��ӦmRID
	std::map<uint64_t, oneThermalGenerator> vThermalGenerator_List;	//����ȼ���ֻ��б�,uint64_t��ӦmRID
	std::map<uint64_t, onePVArray> vPVArray_List;	                //���й���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneWindGenerator> vWindGenerator_List;	    //���з���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneHydroPower> vHydroPower_List;	            //����ˮ���б�,uint64_t��ӦmRID
	std::map<uint64_t, oneAclineDot> vAclineDot_List;               //������·ֵ


																	//�洢�������˷����������ɵ��ڴ���
	std::map<uint64_t, oneDev> vEnergySourceList;	                //���е�Ч��Դ�б�(�豸���в���),uint64_t��ӦmRID
	std::map<uint64_t, oneEnergySource> vEnergySource_List;	        //���е�Ч��Դ�б�(�豸˽�в���),uint64_t��ӦmRID
	std::map<uint64_t, oneTN> vTNList;						    	//����TN�б�,uint64_t��Ӧ���˽ڵ��
	std::map<uint64_t, oneTI> vTIList;                              //����TI�б�,uint64_t��Ӧ���˽ڵ��


		
																																	/***************���ܺ���******************/
public: 

	void MapDataInput();   //map���ݵ������

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


		std::map<CFastDecouplePwrFlw::ID*, branch_flow>branch_data;	//֧·����

		std::map<CFastDecouplePwrFlw::ID*, gen_flow>gnld_data;				//��Դ����

		std::map<uint64_t, node_flow>node_data;				//�ڵ㳱��

public:
	/*******�������ܺ���*******/
	//�ɶ���mRID��ȡ��Ӧ���Ӽ�¼ֵ
	oneTerminal Get_Terminal_To_TStruct(uint64_t mrid);
	//�����ӽڵ�mRID��ȡ��Ӧ���ӽڵ��¼ֵ
	oneCN Get_CN_To_CNStruct(uint64_t mrid);
	//�����˽ڵ�mRID��ȡ��Ӧ���˽ڵ��¼ֵ
	oneTN Get_TN_To_TNStruct(uint64_t mrid);


	/*******���ӹ�ϵ���ù��ܺ����������ܺ��������ڴ�������ݵĻ����ϣ��������ڴ��������д��������Ч��********/
	//�ɶ���mRID��ȡ��Ӧ���ӽڵ�mRID
	uint64_t Get_Terminal_To_CNmRID(uint64_t mrid);

	//�ɶ���mRID��ȡ��Ӧ�豸mRID
	uint64_t Get_Terminal_To_DevmRID(uint64_t mrid);

	//�ɶ���mRID��ȡ��Ӧ�豸�б�����
	int Get_Terminal_To_DevListID(uint64_t mrid);

	//�����ӽڵ�mrid��ȡ��Ӧ���˽ڵ�mrid
	uint64_t Get_CNmRID_To_TNmRID(uint64_t mrid);

	//�����ӽڵ�mRID��ȡ��Ӧ���ж��Ӽ���(���Ӵ�ŵ�vector�У������ʽΪmRID)
	std::vector<uint64_t> Get_CNmRID_To_Terminal(uint64_t mrid);

	//�����˽ڵ�mRID��ȡ��Ӧ�������ӽڵ㼯��(���Ӵ�ŵ�vector�У������ʽΪmRID)
	std::vector<uint64_t> Get_TNmRID_To_CN(uint64_t mrid);


	//�ɶ���mRID��ȡ��Ӧ�豸��¼ֵ
	//��֧�������豸����mRID�Ķ�ȡ
	oneDev Get_Terminal_To_Devstruct(uint64_t mrid);

	//�����˽ڵ�mRID��ȡ��Ӧ���˵�
	uint64_t Get_TNmRID_To_TImRID(uint64_t mrid);


	//�ɶ���mRID��ȡ��Ӧ���ӽڵ��¼ֵ
	oneCN Get_Terminal_To_CNstruct(uint64_t mrid);

	//���豸mRID��ȡ��Ӧ���ж��Ӽ���(���Ӵ�ŵ�vector�У������ʽΪmRID)
	//��֧�������豸�б�mRID�Ķ�ȡ���ʺ��ڲ�֪�����豸mrid�����ĸ��б�ʱʹ�ã�
	std::vector<uint64_t> Get_DevmRID_To_Terminal(uint64_t mrid);


	/***************�������ܺ���***************/
	//���豸mrid��ȡ�豸�б��ʶ
	//��֧�������豸�б�mRID�Ķ�ȡ���ʺ��ڲ�֪�����豸mrid�����ĸ��б�ʱʹ�ã�
	int Get_Devmrid_To_ListID(uint64_t mrid);

	//���豸mrid�ж�Ϊ�������豸(����ֵΪ�豸������)
	//��֧�������豸�б�mRID�Ķ�ȡ���ʺ��ڲ�֪�����豸mrid�����ĸ��б�ʱʹ�ã�
	int Get_Dev_Terminal_Num(uint64_t mrid);

	//��Ϊ������豸����һ������mrid��ȡ��һ������mrid(����ֻʵ���������豸)
	//��֧�������豸����mRID�Ķ�ȡ���ʺ��ڲ�֪���ö��������ĸ��豸ʱʹ�ã�
	uint64_t Get_oneT_To_nextT(uint64_t mrid);

	/***********��ȡ���豸˽�в��ּ�¼************/
	//��ʽ1(�Ƽ�ʹ��)��ͨ���豸����������豸˽�в��ּ�¼
	//����·����mRID��ȡ��·˽�в��ּ�¼
	oneAcline Get_AclineTM_To_AclineStrust(uint64_t mrid);

	//�ɶ�·������mRID��ȡ��·��˽�в��ּ�¼
	oneBreaker Get_BreakerTM_To_BreakerStrust(uint64_t mrid);

	//�ɵ�Դ����mRID��ȡ��Դ˽�в��ּ�¼
	oneEnergySource Get_EnergySourceTM_To_EnergySourceStrust(uint64_t mrid);

	//�ɸ��ɶ���mRID��ȡ����˽�в��ּ�¼
	oneEnergyConsumer Get_EnergyConsumerTM_To_EnergyConsumerStrust(uint64_t mrid);

	//�ɴ��ܶ���mRID��ȡ����˽�в��ּ�¼
	oneBatteryStorage Get_BatteryStorageTM_To_BatteryStorageStrust(uint64_t mrid);

	//���Ȼ�����mRID��ȡ�Ȼ�˽�в��ּ�¼
	oneThermalGenerator Get_ThermalGeneratorTM_To_ThermalGeneratorStrust(uint64_t mrid);

	//�ɹ������mRID��ȡ���˽�в��ּ�¼
	onePVArray Get_PVArrayTM_To_PVArrayStrust(uint64_t mrid);

	//�ɷ������mRID��ȡ���˽�в��ּ�¼
	oneWindGenerator Get_WindGeneratorTM_To_WindGeneratorStrust(uint64_t mrid);

	//��ˮ�����mRID��ȡˮ��˽�в��ּ�¼
	oneHydroPower Get_HydroPowerTM_To_HydroPowerStrust(uint64_t mrid);

	//��ĸ��mRID��ȡĸ��˽�в��ּ�¼
	oneBusbar Get_BusbarTM_To_BusbarStrust(uint64_t mrid);


	//��ʽ2(���Ƽ�ʹ��)��ͨ���豸mRID������豸˽�в��ּ�¼
	//����·mRID��ȡ��·˽�в��ּ�¼
	oneAcline Get_Acline_To_AclineStrust(uint64_t mrid);

	//�ɶ�·��mRID��ȡ��·��˽�в��ּ�¼
	oneBreaker Get_Breaker_To_BreakerStrust(uint64_t mrid);




	/****************Ӧ�ú���******************************/
	void InitDataInput();//���������ʼ������

	void InitDbResults();//��ʼ�����糱�����

	void PfSaveACLineResults(int sub, float p, float q,float i, float ploss, float qloss);//���浥һ���߶ν��

	void PfSaveACLineResults(int sub, float pij, float qij, float pji, float qji,float ii, float ij, float vi, float vj);//�����������߶ν��
	void PfSaveBusResults(int sub,float vlt, float angl);//����ĸ������

	void PfSavePVArrayResults(int sub,float p, float q, float i, float u);//���������
	
	void PfSaveWindGeneratorResults(int sub,float p, float q, float i, float u);//���������
	
	void PfSaveBatteryEnergyStorageResults(int sub,float p, float q, float i, float u);//���洢�ܽ��
	
	void PfSaveThermalGeneratorResults(int sub,float p, float q, float i, float u);//����ȼ���ֻ����
	
	void PfSaveHydrpwrInfoResults(int sub,float p, float q, float i, float u);//����ˮ����

	void PfSaveEnergyConsumerResults(int sub,float p, float q, float i, float u);//���渺�ɽ��

	void PfSaveBreakerResults(int sub,float p, float q, float i, float u);//���濪�ؽ��

	void PfSaveEnergySourceResults( int sub, float pg, float qg, float i, float voltage);//�����Դ���





	void SetMpowerToIpower();//���ɣ��ֲ�ʽ��Դ�ϵ��й��޹�����ֵ���õ�����ֵ

	void Execute(); //���г�������

	void Calculate_PQ_pflow(std::map<uint64_t, oneTI>::iterator it_vTIList);//���������˵�Ϊ��λ�ĳ���

	void DataInput(std::map<uint64_t, oneTI>::iterator it_vTIList);//���볱����������
																   //���軯map�ṹ
	void initmapPSR();//��ʼ��map�ṹ

	float PerUnitConvert(float x, float vbase, float sbase);//����ֵת��

	float PerUnit2S(float x, float sbase, float ratio);

	float SPerUnitConvert(float x, float sbase, float ratio);//���ʱ���ֵת��


	void DeleteAndInitial();//�����������

	void GetParaSettings(double& Eps, int& Iter_Max);//��ȡ��������

	void PfGetPara(PfPara& para);//��ȡ��������

								 
	void SaveTopIslandResults(std::map<uint64_t, oneTI>::iterator it_vTIList);//���˵����������

    void SetFeederSegmentBreakerPower(std::map<uint64_t, oneTI>::iterator it_vTIList);//�������豸��ȡ���س���ֵ�������߶Σ�

	bool SwapBranchFlow(BranchMap& elm1, BranchMap& elm2);

	void InitRunPFlow();


	uint64_t SearchFeederSegmentFromTerminal(uint64_t pterm1_s, int& iend);


	bool SetBreakerPowerByEnd(std::map<uint64_t, oneBreaker>::iterator it_vBreaker_List, END_DEFINE iend);

	//�رձ�
	void CloseTable(CSgRDBTable &rdbTable);

	void DataOutPut();//���ݿ��������


	private:
		void dpf();//���ú���

		int m_SchemaHandler;//�ڴ����
		bool m_OpenShareMemory_Success;//���������ڴ��Ƿ�ɹ�
};


