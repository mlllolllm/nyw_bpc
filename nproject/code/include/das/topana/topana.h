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

//�������¼��˵��
enum {
	//�豸�б��ʶ-����OIDǰ��λ
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

//�ڵ�����
enum {
	PV = 1,
	PQ = 2,
	Balance = 3
};

struct oneBaseVolt
{
	uint64_t mRID;								//mRID
	float STD_VAL;                              //��׼ֵ
};

struct oneTerminal
{
	uint64_t mRID;								//mRID
	uint64_t BelongtoCN;						//����CN��mRID
	uint64_t BelongtoPSR;						//�����豸��mRID
	int PSR_ListID;                             //�����豸����ױ�ʶ(ǰ��λ����)
};

struct oneCN
{
	uint64_t mRID;									//mRID
	std::vector<uint64_t> vContainsterminal;		//��������
	uint64_t BelongtoTN;							//�������˽ڵ�
	uint64_t BelongtoTI;							//�������˵�����δ��ֵ��Ϊ0
	uint64_t Base_Voltage;             	     	    //��׼��ѹ
	float MemberofVoltageLevel;                     //������ѹ�ȼ�
};

struct oneTN
{
	uint64_t mRID;	                            //mRID
	std::string Name;                                //TN�ڵ�����
	int mSub;
	int firstPSR;                               //���豸�±�
	int numberOfPSR;			    			//�����豸����
	uint64_t BelongtoTI;						//�������˵�
	std::vector<uint64_t> vContainsCNlist;		//����CN�б�
	std::vector<uint64_t> vContainsPSRlist;		//���������豸�б�
	float vltMag;                               //��ѹ��ֵ
	float vltAlgle;                             //��ѹ���
};

struct oneTI
{
	uint64_t mRID;							    	//mRID
	std::string Name;                                //TN�ڵ�����
	int mSub;
	int firstPSR;					    		//���豸�±�
	int numberOfPSR;					    	//�����豸����
	bool isLand;
	std::vector<uint64_t> vContainsTNlist;		//����TN�б�
	std::vector<uint64_t> vContainsPSRlist;		//�����豸�б�
	float LoadPowerP;                           //�����ܸ����й�
	float LoadPowerQ;                           //�����ܸ����޹�
	float SumLossP;                             //����������й�
	float SumLossQ;                             //����������޹�
};

//���������豸�����ֶβ���(�������˷����������豸���ӹ������ǹ�����ϵ)
struct oneDev
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	uint64_t Of_Feeder;                         //��������mRID
	int Base_Voltage;             	    	    //��׼��ѹ
	uint64_t MemberofTI_mRID;		     		//�������˵�mRID
	int MemberofTI;                             //�������˵��±�
	std::vector<uint64_t> vContainsterminal;	//�豸���������б�
	int DevListName;                            //�豸��ı�ʶ(mRIDǰ��λ)
};

struct oneAcline
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	float R;                                    //����R
	float X;                                    //�翹
	float bch;                                  //�������
	float p_value;                              //�й�����
	float q_value;                              //�޹�����
	float ploss_value;                          //�й���ģ���λMW��
	float qloss_value;                          //�޹���ģ���λMvar��
	float current;                              //��·����
	float ratedA;                               //���ص�������
	float ovrLmtRate;                           //������
	bool  limitupI;                             //����ֵԽ����
	std::vector<uint64_t> vAclineDot;             //��·ֵ
	float nominalVoltage;                        //ͨ����ѹ
};

struct oneAclineDot
{
	uint64_t mRID;
	float p_value;                              //�й�����
	float q_value;                              //�޹�����
	float current;                              //��·����
	float voltage;                              //��ѹֵ
	uint64_t BelongtoTerm;                      //������·�Ķ���
	uint64_t BelongtoPSR;						//������·��mRID
};

struct oneBusbar
{
	uint64_t mRID;								//mRID
	int mSub;
	std::string Name;                                //�豸����
	float vltAngle;                          	//��ѹ���
	float voltage;                              //��ѹ
	float MemberOfVoltageLevel;                 //������ѹ�ȼ�
};

struct oneBreaker
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	int openstate;                              //����״̬(0���������պϡ�1������������)
	int breaker_type;                           //���ڶ�·����ʶ(0������ͨ���ء�2�������ڿ��ء�1�������翪��) 
	float p_value;                              //�й�����
	float q_value;                              //�޹�����
	float current;                              //��·����
	float voltage;                              //��ѹֵ
};

struct oneDisconnector
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	int openstate;                              //����״̬(0���������պϡ�1������������)
};

struct oneGroundDisconnector
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	int openstate;                              //����״̬(0���������պϡ�1������������)
};

struct oneBatteryStorage
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	float SOCState;                             //SOC״̬
	float SOCLimHigh;                           //SOC����
	float SOCLimLow;                            //SOC����
	float rateP;                                //�����
	float rateS;                                //�����
	float chargeRatio;                          //�����
	float dischargeRatio;                       //�ŵ���
	float mpower_P;                             //�����й����ʣ���λMW��
	float mpower_Q;                             //�����޹����ʣ���λMvar��
	float ipower_P;                             //�й����ʣ���λMW��
	float ipower_Q;                             //�޹����ʣ���λMvar��
	float voltage;                               //��ѹ
	float current;                               //��·����
	float MemberOfVoltageLevel;                 //������ѹ�ȼ�
};

struct oneThermalGenerator
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	float rateP;                                //�����
	float mpower_P;                             //�����й����ʣ���λMW��
	float mpower_Q;                             //�����޹����ʣ���λMvar��
	float ipower_P;                             //�й����ʣ���λMW��
	float ipower_Q;                             //�޹����ʣ���λMvar��
	float voltage;                              //��ѹ
	float current;                              //��·����
	float MemberOfVoltageLevel;                 //������ѹ�ȼ�
};

struct onePVArray
{
	uint64_t mRID;							     //mRID
	std::string Name;                                 //�豸����
	int mSub;
	float rateP;                                 //�����
	float ip_value;                              //�й����ʣ���λMW��
	float iq_value;                              //�޹����ʣ���λMvar��
	float mp_value;                              //�����й����ʣ���λMW��
	float mq_value;                              //�����޹����ʣ���λMvar��
	float voltage;                               //��ѹ
	float current;                               //��·����
	float MemberOfVoltageLevel;                  //������ѹ�ȼ�
};

struct oneWindGenerator
{
	uint64_t mRID;							   	 //mRID
	std::string Name;                                 //�豸����
	int mSub;
	float rateP;                                 //�����
	float ip_value;                              //�й����ʣ���λMW��
	float iq_value;                              //�޹����ʣ���λMvar��
	float mp_value;                              //�����й����ʣ���λMW��
	float mq_value;                              //�����޹����ʣ���λMvar��
	float voltage;                               //��ѹ
	float current;                               //��·����
	float MemberOfVoltageLevel;                  //������ѹ�ȼ�
};

struct oneHydroPower
{
	uint64_t mRID;								 //mRID
	std::string Name;                                 //�豸����
	int mSub;
	float rateP;                                 //�����
	float ip_value;                              //�й����ʣ���λMW��
	float iq_value;                              //�޹����ʣ���λMvar��
	float mp_value;                              //�����й����ʣ���λMW��
	float mq_value;                              //�����޹����ʣ���λMvar��
	float voltage;                               //��ѹ
	float current;                               //��·����
	float MemberOfVoltageLevel;                  //������ѹ�ȼ�
};

struct oneEnergyConsumer
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	float ip_value;                              //�й����ʣ���λMW��
	float iq_value;                              //�޹����ʣ���λMvar��
	float mp_value;                              //�����й����ʣ���λMW��
	float mq_value;                              //�����޹����ʣ���λMvar��
	float voltage;                               //��ѹ
	float current;                               //��·����
	float MemberOfVoltageLevel;                 //������ѹ�ȼ�
};

struct oneEnergySource
{
	uint64_t mRID;								//mRID
	std::string Name;                                //�豸����
	int mSub;
	float p_value;                              //�й����ʣ���λMW��
	float q_value;                              //�޹����ʣ���λMvar��
	int attribute;                           //��Դ������
	float voltage;                              //��ѹ
	float current;                              //����
	float MemberOfVoltageLevel;                 //������ѹ�ȼ�
};

struct IterWithDepth
{
public:
	uint64_t iterTerminal_mRID;                              //���ӵ�mRID
	int Depth;                                               //�������
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
	uint64_t NewAcline_mRID;             //��������ĸ�����˽ڵ�䱣���µ���·mRID,��������·mRID�ϴ�������

	float NewAcline_R;                   //��������������·�µĵ���
	float NewAcline_X;					 //��������������·�µĵ翹

	std::vector<uint64_t> vAcline;            //�������Ľ�����·
	std::vector<uint64_t> vShrinkAcline;      //�洢��Ҫ�����Ľ�����·
	std::vector<uint64_t> vShrinkBreaker;
	std::vector<uint64_t> vShrinkDisconnector;

	std::map<uint64_t, bool> vTN_type;        //true������Ҫ���������˽ڵ㣻false��������Ҫ���������˽ڵ�
										 //vTN_NotContainBus
										 //vTN_ContainBus
	std::vector<uint64_t> vTN_NotShrink;	     //����������Ҫ���������˽ڵ�	   
	std::vector<uint64_t> vTN_NeedShrink;     //��������Ҫ���������˽ڵ�

	std::vector<uint64_t> vTerminalMemOfTN;   //����������������˽ڵ� �ϵ����ڴ˶���·�Ķ���
	uint64_t Terminal_NewAcline;         //vTerminalMemOfTN��NewAcline_mRID����Ӧ��Terminal
	uint64_t Terminal_another;           //vTerminalMemOfTN����һ��Terminal

										 //vector<uint64_t> vCNMemOfTN;         //������ĸ�߻����������ϵ����˽ڵ� �ϵ����ڴ˶���·��CN
};

//TOPANAӦ��������Ϣ��TOPANA��DAS_CONFIG�е��������ݣ�
typedef struct TOPANA_CONFIG
{	
	
}TOPANA_CONFIG;

class TOPANA_DLL_API CTopana : public CDasBase
{
public:
	CTopana();
	CTopana(int appID, const char* appCode=NULL);
	~CTopana();

	//����
	void Exec();

	//�����ñ�
	int ReadConfig();

	//�����ñ�ģ�ͱ��
	int Read();

	//д�����
	int Write();

	//�رձ�
	void CloseTable(CSgRDBTable &rdbTable);

	/**********�����ڴ��***********/
public:

	std::map<uint64_t, oneBaseVolt> vBaseVoltList;

	std::map<uint64_t, oneDev> vDisconnectorList;
	std::map<uint64_t, oneDisconnector> vDisconnector_List;
	std::map<uint64_t, oneDev> vGroundDisconnectorList;
	std::map<uint64_t, oneGroundDisconnector> vGroundDisconnector_List;
	std::map<uint64_t, oneDev> vTransformerList;	                //���б�ѹ���б�,uint64_t��ӦmRID

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
	std::map<uint64_t, oneTI> vTIList;						    	//����TI�б�,uint64_t��Ӧ���˽ڵ��

																	//���������������ɵ��ڴ���
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


	/********�м����*********/
public:
	std::vector<uint64_t> vESTermList;    //�������������Դʱ�����ɵĶ���mRID(д�����ݿ�ʱʹ��)
	std::vector<uint64_t> vTIPSRList;	  //�豸�б����豸mRID���룬ͨ��TI��firstPSR��numberOfPSR��������ȷ���������豸
	std::vector<uint64_t> vTNPSRList;	  //�豸�б����豸mRID���룬ͨ��TN��firstPSR��numberOfPSR��������ȷ���������豸

										  //Ĭ������Ϊ0;���ڷ�����������Ҫ������������������Ϊ1
	int topana_model = 0;

	/********������������********/
	//����ÿ��TN�����ӵ����н�����·��Ϣ
	std::map<uint64_t, std::vector<Acline_ConnNode>> vTNContainAcline_List;
	//����ÿ��������·���˵�TN�ڵ�
	std::map<uint64_t, Acline_ConnNode> vAclineMemOfTN;

	std::map<uint64_t, oneTopolShrink> vTopolShrinkList;

	//�洢�������˽ڵ�mRID��������
	//0��������ĸ�ߵ����˽ڵ㡢1����������ĸ������������·���ӵ����˽ڵ㡢2����������ĸ�������������ϵ����˽ڵ�
	std::map<uint64_t, int> vTN_Type;

	std::map<uint64_t, int> vTN_Conn_LineNum;

	/*********Ӧ�ú���*********/
public:
	//��ģ�����ݴ�redis���ݿ��ж����ڴ��
	//���Ӧ�ú����ﲻ��ʹ�ù��ܺ���
	bool read_model();	

	//���ӵ�Ч��Դ(��10kVվ��ĸ�ߴ�)
	void AddEquivalentSource();

	//�γ����˽ڵ�
	void FormTopologicalNodes();

	//�γ����˵�
	void FormTopologicalIsland();

	//���˽��д�����ݿ�
	void WriteTopoAnaResults();

	//�������ݿ������˷������
	void CleanTopoAnaResults();

	//����������
	void CleanbadData();


	/*********��������Ӧ�ú���*********/
public:

	//��������������
	void TopolShrink();


	/*****����������������******/
	//�ҵ�ÿ��TN�����ӵ����н�����·��Ϣ
	void Get_TN_Conn_Acline();

	//��ȡÿ��������·���˵�TN�ڵ�
	void Get_AclineMemOfTN();

	//���������˽ڵ����
	void SortTN();
	//�ж����˽ڵ�����
	int JudgeBusType(uint64_t mrid);

	/***************���ܺ����������ܺ��������ڴ�������ݵĻ����ϣ��������ڴ��������д��������Ч��******************/
public:
	/*******�������ܺ���*******/
	//�ɶ���mRID��ȡ��Ӧ���Ӽ�¼ֵ
	oneTerminal Get_Terminal_To_TStruct(uint64_t mrid);
	//�����ӽڵ�mRID��ȡ��Ӧ���ӽڵ��¼ֵ
	oneCN Get_CN_To_CNStruct(uint64_t mrid);
	//�����˽ڵ�mRID��ȡ��Ӧ���˽ڵ��¼ֵ
	oneTN Get_TN_To_TNStruct(uint64_t mrid);

	/*******���ӹ�ϵ���ù��ܺ���********/
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

	//�ɻ�׼��ѹID��ȡ��׼��ѹֵ
	float Get_voltvalue(uint64_t mrid);

	/***********��ȡ���豸˽�в��ּ�¼************/
	//��ʽ1(�Ƽ�ʹ��)��ͨ���豸����������豸˽�в��ּ�¼
	//����·����mRID��ȡ��·˽�в��ּ�¼
	oneAcline Get_AclineTM_To_AclineStrust(uint64_t mrid);

	//�ɶ�·������mRID��ȡ��·��˽�в��ּ�¼
	oneBreaker Get_BreakerTM_To_BreakerStrust(uint64_t mrid);

	//��բ������mRID��ȡբ��˽�в��ּ�¼
	oneDisconnector Get_DisconnectorTM_To_DisconnectorStrust(uint64_t mrid);

	//�ɸ��ɿ��ض���mRID��ȡ���ɿ���˽�в��ּ�¼
	oneGroundDisconnector Get_GDisconnectorTM_To_GDisconnectorStrust(uint64_t mrid);

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


	//��ʽ2(���Ƽ�ʹ��)��ͨ���豸mRID������豸˽�в��ּ�¼
	//����·mRID��ȡ��·˽�в��ּ�¼
	oneAcline Get_Acline_To_AclineStrust(uint64_t mrid);

	//�ɶ�·��mRID��ȡ��·��˽�в��ּ�¼
	oneBreaker Get_Breaker_To_BreakerStrust(uint64_t mrid);

	/******�������ݿ���������******/
public:	

private:
	/********���˷���Ӧ�ó���******/
	void Topol();

	CSgRDBTable * m_pTabe;//�ڴ��

	TOPANA_CONFIG m_Config;
};

#endif


