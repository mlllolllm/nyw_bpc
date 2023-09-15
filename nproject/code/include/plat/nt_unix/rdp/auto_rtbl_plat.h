#ifndef _HH_AUTO_RTBL_PLAT_HHH_ 
#define _HH_AUTO_RTBL_PLAT_HHH_ 
//��ͷ�ļ��ɳ���crthfile.exe�Զ�����
//������·�α�	
#include "dppclient.h"
#include "rdbmem.h"
typedef struct MODEL_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//���
char		NAME[128];		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
SG_INT64		OF_LINE;		//������·
float		R;		//����
float		X;		//�翹
float		BCH;		//������
float		R0;		//�������
float		X0;		//����翹
float		B0CH;		//���������
char		LINE_MODEL[24];		//��·�ͺ�
float		LENGTH;		//�����ף�
float		MAX_AMP;		//������
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		RATED_AMP;		//�����
float		B;		//����
float		G;		//�絼
unsigned char		res1[4];
}MODEL_ACLINE_SEGMENT;
//���ܱ�	
typedef struct MODEL_BATTERYENERGYSTORAGE
{ 
SG_INT64		ID;		//���
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
SG_INT64		MenberOfLine;		//��������
SG_INT64		MenberOfSubstation;		//�������վ
float		SOCState;		//SOC״̬
float		SOCLimHigh;		//SOC����
float		SOCLimLow;		//SOC����
float		chargeRatio;		//�����
float		dischargeRatio;		//�ŵ���
char		PSRID[64];		//PSRID
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//�������վ
double		RATED_P;		//�����
double		RATED_S;		//�����
double		MAX_RATE;		//�����
double		MIN_RATE;		//��С����
double		MAX_P;		//����й�
double		MIN_P;		//��С�й�
double		MAX_Q;		//����޹�
double		MIN_Q;		//����޹�
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹֵ
double		IPOWER_I;		//����ֵ
unsigned char		OF_BASE_VOLTAGE;		//��׼��ѹ
unsigned char		res1[7];
double		MPOWER_P;		//�����й�����
double		MPOWER_Q;		//�����޹�����
}MODEL_BATTERYENERGYSTORAGE;
//�����	
typedef struct MODEL_BAY
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_VOLT_LEVEL;		//������ѹ�ȼ�
SG_INT64		BAY_TYPE;		//����
}MODEL_BAY;
//���ر�	
typedef struct MODEL_BREAKER
{ 
SG_INT64		ID;		//���
char		NAME[128];		//����
char		ALIAS[32];		//����
char		DISP_CODE[16];		//���Ⱥ�
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//������վ
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_BAY;		//�������
SG_INT64		DIGITAL_ID;		//ң��ID
unsigned char		NORMAL_OPEN_FLAG;		//������־
unsigned char		res1[3];
float		MAX_KV;		//����ѹ
float		RATED_AMP;		//�����
float		MAX_AMP;		//������
float		CAPACITY;		//����
unsigned char		NORMAL_POSITION;		//����״̬
unsigned char		res2[3];
float		RATED_BREAK_AMP_CAPB;		//���������
float		INTERRUPTING_AMP;		//���ϵ���
unsigned char		TROLLY_BREAKER_FLAG;		//С�����ر�־
unsigned char		DUAL_DIG_FLAG;		//˫ң�ű�־
unsigned char		ZERO_BRANCH_FLAG;		//��֧·��־
unsigned char		res3[1];
float		DYNSTABLE_AMP;		//���ȶ�����
float		THERMAL_STABLE_AMP;		//���ȶ�����
unsigned char		POWER_STATE;		//����״̬
unsigned char		res4[3];
int		TOPO_ISLAND;		//���˵�������
unsigned char		res5[4];
SG_INT64		PLD_CB_ID;		//��·����
unsigned char		TAG_FLAG;		//���Ʊ�־
unsigned char		res6[7];
}MODEL_BREAKER;
//ĸ�߱�	
typedef struct MODEL_BUSBAR_SECTION
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		BUSBAR_TYPE;		//����
int		BAS_CONN_TYPE;		//ĸ����������
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ��
SG_INT64		OF_BAY;		//�������
int		POWER_SUPPLY_FLAG;		//��Դ���־
unsigned char		res1[4];
SG_INT64		OF_FEEDER;		//���ߴ���
unsigned char		BUS_STATUS;		//ĸ��״̬
unsigned char		res2[7];
double		BUSBAR_VOLT_HLIMIT;		//ĸ�ߵ�ѹ����
float		BUSBAR_VOLT_LLIMIT;		//ĸ�ߵ�ѹ����
unsigned char		LOAD_BUSBAR_FLAG;		//����ĸ�߱�־
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res3[1];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		res4[4];
}MODEL_BUSBAR_SECTION;
//��������	
typedef struct MODEL_COMPENSATOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		COMPENSATOR_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
float		RATED_MVAR;		//�����
float		MVAR_PER_SECTION;		//ÿ������
int		MAX_SECTIONS;		//�������
int		NORMAL_SECTIONS;		//Ͷ������
float		RATED_KV;		//���ѹ
float		MAX_KV;		//����ѹ
float		RATED_AMP;		//�����
float		MAX_AMP;		//������
float		R;		//����
float		X;		//�翹
unsigned char		RUN_STATE;		//����״̬
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res0[1];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
}MODEL_COMPENSATOR;
//���ӵ��	
typedef struct MODEL_CONN_NODE
{ 
SG_INT64		ID;		//���
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_CONTAINER;		//��վ����
SG_INT64		OF_BASE_VOLTAGE;		//��ѹ�ȼ�
char		PSRID[64];		//��ԴID
SG_INT64		OF_TOPOLOGICALNODE;		//�������˽ڵ�
}MODEL_CONN_NODE;
//����������	
typedef struct MODEL_CT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		CT_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
unsigned char		PHASE;		//���
char		CT_MODEL[24];		//�����������ͺ�
unsigned char		res0[3];
float		RATED_KV;		//���ѹ
float		RATED_AMP_RATIO;		//�������
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res1[2];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		AccuracyLimit;		//�ٷֱȾ���
}MODEL_CT;
//��բ��	
typedef struct MODEL_DISCONNECTOR
{ 
SG_INT64		ID;		//���
char		NAME[128];		//����
char		ALIAS[32];		//����
char		DISP_CODE[16];		//���Ⱥ�
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//������վ
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_BAY;		//�������
SG_INT64		DIGITAL_ID;		//ң��ID
unsigned char		NORMAL_OPEN_FLAG;		//������־
unsigned char		MANUAL_SET_FLAG;		//�˹����ñ�־
unsigned char		NORMAL_POSITION;		//����״̬
unsigned char		DUAL_DIG_FLAG;		//˫ң�ű�־
unsigned char		POWER_STATE;		//����״̬
unsigned char		res1[3];
int		TOPO_ISLAND;		//���˵�������
unsigned char		TAG_FLAG;		//���Ʊ�־
unsigned char		res2[3];
}MODEL_DISCONNECTOR;
//���������߶α�	
typedef struct MODEL_D_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//���
char		NAME[256];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		LINE_TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
float		LATITUDE;		//γ��
float		LONGITUDE;		//����
float		R;		//����
float		X;		//�翹
float		BCH;		//������
char		LINE_MODEL[64];		//��·�ͺ�
float		LENGTH;		//�����ף�
float		MAX_AMP;		//������
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		B;		//����
float		G;		//�絼
char		PSRID[64];		//PSRID
unsigned char		res1[4];
SG_INT64		OF_BASE_VOLTAGE;		//��׼��ѹ
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_I;		//����
double		IPOWER_PLOSS;		//�й����
double		IPOWER_QLOSS;		//�޹����
double		RATED_A;		//���ص�������
double		OVRLMTRATE;		//������
double		LIMITUPL;		//����ֵԽ����
}MODEL_D_ACLINE_SEGMENT;
//�������ر�	
typedef struct MODEL_D_BREAKER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//��������
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
int		NORMAL_POSITION;		//����״̬
char		CABINET_NUMBER[64];		//վ���ڿ��صĿ��ع���
char		DA_COMM_ADDRESS[64];		//����Զ���ͨ�ŵ�ַ
float		LATITUDE;		//γ��
float		LONGITUDE;		//����
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		TAG_FLAG;		//���Ʊ�־
unsigned char		NORMAL_OPEN_FLAG;		//������־
unsigned char		res1[2];
float		RATED_CURRENT;		//�����ֵ
float		BREAKING_CAP;		//��󿪶ϵ���ֵ
char		PHASE[6];		//��λ
char		PSRID[64];		//PSRID
unsigned char		res2[2];
SG_INT64		OF_BASE_VOLTAGE;		//��׼��ѹ
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹ
double		IPOWER_I;		//����
}MODEL_D_BREAKER;
//����ĸ�߱�	
typedef struct MODEL_D_BUSBAR_SECTION
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		BUS_TYPE;		//ĸ������
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
float		LATITUDE;		//γ��
float		LONGITUDE;		//����
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
char		PSRID[64];		//PSRID
SG_INT64		OF_BASE_VOLTAGE;		//��׼��ѹ
int		OF_TOPO_ISLAND;		//���˵�������
unsigned char		res1[4];
double		IPOWER_VLTANGLE;		//��ѹ���
double		IPOWER_U;		//��ѹ
}MODEL_D_BUSBAR_SECTION;
//�������߱�	
typedef struct MODEL_D_CIRCUIT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
int		AREA_FEATURE;		//��������
unsigned char		res0[4];
SG_INT64		SOURCE_SUBST;		//Դͷ���վ
SG_INT64		SOURCE_BREAKER;		//���߿���
int		FA_TYPE;		//�����Զ�������
int		FA_LOCK_FLAG;		//�����Զ�����
}MODEL_D_CIRCUIT;
//������������	
typedef struct MODEL_D_COMPENSATOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
char		PSRID[64];		//PSRID
SG_INT64		NODEID;		//��������
double		EACH_CAPACITY;		//ÿ������
int		MAX_NUM;		//�������
int		OPERATION_NUM;		//Ͷ������
int		MAX_ACT_NUM;		//ʱ�������������
unsigned char		res1[4];
}MODEL_D_COMPENSATOR;
//�������ӵ��	
typedef struct MODEL_D_CONN_NODE
{ 
SG_INT64		ID;		//���
}MODEL_D_CONN_NODE;
//����ֱ���߶α�	
typedef struct MODEL_D_DCLINE_SEGMENT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		LINE_TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
float		LATITUDE;		//γ��
float		LONGITUDE;		//����
float		R;		//����
float		X;		//�翹
float		BCH;		//������
char		LINE_MODEL[64];		//��·�ͺ�
float		LENGTH;		//�����ף�
float		MAX_AMP;		//������
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		B;		//����
float		G;		//�絼
unsigned char		res1[4];
}MODEL_D_DCLINE_SEGMENT;
//������բ��	
typedef struct MODEL_D_DISCONNECTOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//��������
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
int		NORMAL_POSITION;		//����״̬
char		CABINET_NUMBER[64];		//վ���ڿ��صĿ��ع���
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		TAG_FLAG;		//���Ʊ�־
unsigned char		NORMAL_OPEN_FLAG;		//������־
unsigned char		res1[2];
float		RATED_CURRENT;		//�����ֵ
char		PSRID[64];		//PSRID
unsigned char		res2[4];
}MODEL_D_DISCONNECTOR;
//�����ص���	
typedef struct MODEL_D_GROUND_DISCONNECTOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//�ӵص�����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
int		NORMAL_POSITION;		//����״̬
char		CABINET_NUMBER[64];		//վ���ڿ��صĿ��ع���
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		TAG_FLAG;		//���Ʊ�־
unsigned char		NORMAL_OPEN_FLAG;		//������־
char		PSRID[64];		//PSRID
unsigned char		res1[2];
}MODEL_D_GROUND_DISCONNECTOR;
//������ѹ��������	
typedef struct MODEL_D_PT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		NorminalRatio;		//���
char		PHASE[6];		//��λ
unsigned char		res1[6];
}MODEL_D_PT;
//�����翹����	
typedef struct MODEL_D_REACTOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
}MODEL_D_REACTOR;
//����վ����	
typedef struct MODEL_D_SUBSTATION
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
SG_INT64		SUBTYPE;		//վ������
int		CURR_POWER_NO;		//��ǰ��Դ��
int		MAIN_POWER_NO;		//����Դ��
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
float		LATITUDE;		//γ��
float		LONGITUDE;		//����
SG_INT64		BRANCH_ID;		//�ϼ���֧��
char		PSRID[64];		//PSRID
}MODEL_D_SUBSTATION;
//�������ӱ�	
typedef struct MODEL_D_TERMINAL
{ 
SG_INT64		ID;		//���
int		SEQ_NUMBER;		//���
int		TYPE;		//����
SG_INT64		OF_DEVICE;		//�����豸
SG_INT64		CONN_NODE_ID;		//���ӵ�ID
}MODEL_D_TERMINAL;
//������ѹ����	
typedef struct MODEL_D_TRANSFORMER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_FEEDER_SECTION;		//������֧��
SG_INT64		OF_D_SUBSTATION;		//����վ��
char		MODEL[64];		//�ͺ�
float		RATED_CAPACITY;		//�����
int		USER_TYPE;		//�û�����
int		VIP_AMOUNT;		//��Ҫ�û���
float		LOAD_RATIO;		//������
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
char		VECTOR_GROUP[64];		//���߷�ʽ
char		PSRID[64];		//PSRID
double		MPOWER_I;		//����
double		MPOWER_P;		//�й�����
double		MPOWER_Q;		//�޹�����
double		MPOWER_U;		//��ѹ
}MODEL_D_TRANSFORMER;
//���������	
typedef struct MODEL_D_TRANS_WINDING
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[64];		//����
char		DISP_CODE[64];		//���ȱ��
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
int		TYPE;		//����
int		CONN_TYPE;		//���߷�ʽ
SG_INT64		OF_D_TRANSFOR;		//������ѹ��
float		RATED_CAPACITY;		//�����
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		ENDNUMBER;		//���
unsigned char		res0[3];
double		R;		//����
double		X;		//�翹
double		B;		//����
double		G;		//�絼
char		PSRID[64];		//PSRID
}MODEL_D_TRANS_WINDING;
//�綯������	
typedef struct MODEL_ELECTRICVEHICLE
{ 
SG_INT64		ID;		//���
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
SG_INT64		MenberOfLine;		//��������
SG_INT64		MenberOfSubstation;		//�������վ
SG_INT64		timeLasting;		//ʹ��ʱ��
SG_INT64		status;		//���׮״̬
SG_INT64		genEff;		//���Ч��
float		ratedP;		//�����
float		ratedS;		//�����
float		maxSOC;		//SOC����
float		minSOC;		//SOC����
float		SOC;		//SOC����
float		mpower_P;		//�й�����
float		mpower_Q;		//�޹�����
float		mpower_U;		//��ѹֵ
float		mpower_I;		//����ֵ
char		PSRID[64];		//PSRID
unsigned char		res0[4];
}MODEL_ELECTRICVEHICLE;
//���ɱ�	
typedef struct MODEL_ENERGY_CONSUMER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		ENERGY_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_FEEDER;		//���ߴ���
float		MW_VOLT_CHARACT;		//�й����ɵ�ѹ����
float		MVAR_VOLT_CHARACT;		//�޹����ɵ�ѹ����
float		MW_FREQ_CHARACT;		//�й�����Ƶ������
float		MVAR_FREQ_CHARACT;		//�޹�����Ƶ������
unsigned char		LOAD_STATE;		//����״̬
unsigned char		res0[3];
float		MW_VALUE;		//�й�����ֵ
float		MVAR_VALUE;		//�޹�����ֵ
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res1[2];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		RATED_ELECTRICITY;		//�����
float		LOAD_RATE;		//������
int		CustomerCount;		//�ۺ��û���
float		Pfixed;		//�̶��й�����
float		Qfixed;		//�̶��޹�����ֵ
unsigned char		Grounded;		//�Ƿ�ӵ�
char		PhaseConnection[12];		//���߷�ʽ
unsigned char		res2[3];
float		MPOWER_I;		//����
float		MPOWER_U;		//��ѹ
float		MPOWER_Q;		//�޹�����
float		MPOWER_P;		//�й�����
char		PSRID[64];		//��ԴID
SG_INT64		OF_TRANSFORMER;		//����̨��
unsigned char		OF_BASE_VOLTAGE;		//��ѹ�ȼ�
unsigned char		res3[7];
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹ
double		IPOWER_I;		//����
}MODEL_ENERGY_CONSUMER;
//���Ը��ɱ�	
typedef struct MODEL_FLEXLOADINFO
{ 
SG_INT64		ID;		//���
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
SG_INT64		MenberOfLine;		//��������
SG_INT64		MenberOfSubstation;		//�������վ
float		LdFlxblIncIndx;		//������������ϵ��
float		LdFlxblDecIndx;		//���ɷ�������ϵ��
float		LdFlxblIncPr;		//��������ɵ��ڹ���
float		LdFlxblDecPr;		//���ɷ���ɵ��ڹ���
unsigned char		usable;		//���Ը���״̬
unsigned char		res0[1];
short		type;		//���Ը�������
float		mpower_P;		//�й�����
float		mpower_Q;		//�޹�����
float		mpower_U;		//��ѹֵ
float		mpower_I;		//����ֵ
unsigned char		res1[4];
}MODEL_FLEXLOADINFO;
//��·������	
typedef struct MODEL_LINE
{ 
SG_INT64		ID;		//���
char		DISP_CODE[22];		//���Ⱥ�
char		NAME[64];		//����
unsigned char		res0[2];
int		LINE_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
SG_INT64		FROM_SUBSTATION;		//��ʼ��վ
SG_INT64		TO_SUBSTATION;		//��ֹ��վ
SG_INT64		OF_COMPANY;		//������˾
SG_INT64		OF_BAY;		//�������
float		MUTUAL_IMPEDANCE;		//���迹
unsigned char		res1[4];
SG_INT64		ASSOC_LINE;		//�����·��
float		AMP_MARG;		//����ԣ��
unsigned char		LINE_STATE;		//��·״̬
unsigned char		res2[3];
float		CAP_AMP;		//���ݵ���
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		RATED_ELECTRICITY;		//�����
float		LOAD_RATE;		//������
unsigned char		res3[4];
}MODEL_LINE;
//��ѹ����	
typedef struct MODEL_POWER_TRANS
{ 
SG_INT64		ID;		//���
char		DISP_CODE[22];		//���Ⱥ�
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		res0[2];
int		TRANS_TYPE;		//����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
float		HM_LEAKAGE_IMPEDANCE;		//���ж�·��ѹ
float		ML_LEAKAGE_IMPEDANCE;		//�еͶ�·��ѹ
float		LH_LEAKAGE_IMPEDANCE;		//�͸߶�·��ѹ:
float		HM_LOAD_LOSS;		//���ж�·���
float		ML_LOAD_LOSS;		//�еͶ�·���
float		LH_LOAD_LOSS;		//�͸߶�·���
float		EXCITING_AMP;		//���ص���
float		NOLOAD_LOSS;		//�������
float		GMAG_SAT;		//��ѹ�����ŵ絼
float		BMAG_SAT;		//��ѹ�����ŵ���
unsigned char		POWERTRANS_STATE;		//��ѹ��״̬
unsigned char		VOLT_ADJUST_MODE;		//��ѹ��ʽ
unsigned char		res1[2];
float		LOAD_CAPB_RATIO;		//�����ݱ�
unsigned char		PARAM_CALC_FLAG;		//���������־
unsigned char		res2[3];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
float		RATED_POWER;		//�����
float		ACTIVE_BALANCE_RATE;		//�й�ƽ����
float		REACTIVE_BALANCE_RATE;		//�޹�ƽ����
float		LOAD_RATE;		//������
char		VectorGroup[64];		//���߷�ʽ
unsigned char		res3[4];
}MODEL_POWER_TRANS;
//��ѹ������	
typedef struct MODEL_PT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
float		PT_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_FEEDER;		//���ߴ���
char		PHASE[12];		//���
char		PT_MODEL[24];		//��ѹ�������ͺ�
float		RATED_KV;		//���ѹ
float		RATED_VOLT_RATIO;		//���ѹ��
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res0[2];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		res1[4];
}MODEL_PT;
//�����	
typedef struct MODEL_PVARRAY
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//�������վ
float		RATED_P;		//�����
float		MAX_P;		//����й�
float		MIN_P;		//��С�й�
float		MAX_Q;		//����޹�
float		MIN_Q;		//��С�޹�
unsigned char		USEABLE;		//���״̬
unsigned char		res0[3];
float		MAX_PF;		//������������
float		MIN_PF;		//������������
float		MPOWER_P;		//�й�����
float		MPOWER_Q;		//�޹�����
float		MPOWER_U;		//��ѹֵ
float		MPOWER_I;		//����ֵ
char		PSRID[64];		//PSRID
SG_INT64		OF_TRANSFORMER;		//����̨��
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹֵ
double		IPOWER_I;		//����ֵ
unsigned char		OF_BASE_VOLTAGE;		//��׼��ѹ
unsigned char		res1[7];
}MODEL_PVARRAY;
//�翹����	
typedef struct MODEL_REACTOR
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
SG_INT64		REACTOR_TYPE;		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
float		RATED_MVAR;		//�����
float		MVAR_PER_SECTION;		//ÿ������
int		MAX_SECTIONS;		//�������
int		NORMAL_SECTIONS;		//Ͷ������
float		RATED_KV;		//���ѹ
float		MAX_KV;		//����ѹ
float		RATED_AMP;		//�����
float		MAX_AMP;		//������
float		R;		//����
float		X;		//�翹
unsigned char		RUN_STATE;		//����״̬
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res1[1];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
}MODEL_REACTOR;
//��վ��	
typedef struct MODEL_SUBSTATION
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
int		SUBSTATION_TYPE;		//����
SG_INT64		OF_SCA;		//�����ӿ�����
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
SG_INT64		OF_FEEDER;		//��������
int		DIGTAL_NUM;		//ң����
int		ANALOG_NUM;		//ң����
int		DEVICE_NUM;		//�豸��
int		EVENT_NUM;		//�澯��
int		TAG_NUM;		//������
unsigned char		res0[4];
SG_INT64		OF_SUBREGION;		//����������
char		PSRID[255];		//psrid
unsigned char		res1[1];
SG_INT64		OF_BASE_VOLTAGE;		//��׼��ѹ
}MODEL_SUBSTATION;
//�������	
typedef struct MODEL_SYNCHRONOUS_MACHE
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		MACHE_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_FEEDER;		//���ߴ���
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_BAY;		//�������
float		MAX_KV;		//����ѹ
float		MAX_MVAR;		//����޹�
float		MIN_KV;		//��С��ѹ
float		MIN_MVAR;		//��С�޹�
float		MAX_MW;		//����й�
float		MIN_MW;		//��С�й�
float		RATED_MVA;		//�����
float		R1;		//�������
float		X1;		//����翹
float		R0;		//�������
float		X0;		//����翹
float		X2;		//����翹
float		GEN_FREQCHARACT;		//�������Ƶ����
int		GEN_MODEL;		//�����ģ��
float		INTERTIA;		//ת�ӹ���ʱ�䳣��
float		RA;		//���ӵ���
float		XO;		//����©��
float		XD;		//ֱ��ͬ���翹
float		XDIRECT_TRANS;		//ֱ����̬�翹
float		XDIRECT_SUBTRANS;		//ֱ�����̬�翹
float		XQ;		//����ͬ���翹
float		XQUAD_TRANS;		//������̬�翹
float		XQUAD_SUBTRANS;		//�������̬�翹
float		DAMP;		//����ϵ��
float		TD0P;		//���Ż�·ʱ�䳣��
float		TD0PP;		//ֱ�����������·ʱ�䳣��
float		TQ0PP;		//������������ʱ���·����
float		GEN_UNIT_FACT_FILTR_COEF;		//�����˲�ϵ��
float		GEN_FM_COE;		//Ƶ�ʵ�������
float		CTRL_DBAND;		//��������
float		REG_MARG;		//�������
float		EMERG_BACKUP_LLIMIT;		//������������
float		CAPB_LLIMIT;		//��������
float		CTRL_LLIMIT;		//���п�������
float		SCHED_GEN;		//����ƻ�
float		CTRL_HLIMIT;		//���п�������
float		CAPB_HLIMIT;		//��������
float		EMERG_BACKUP_HLIMIT;		//������������
int		HYD_NUM_IWD_CURVES;		//�������������
unsigned char		res0[4];
SG_INT64		GEN_RES_ID;		//PLC��
char		HYD_CURVE_NAME[24];		//������������
int		PHB_CNT;		//��ֹ����������
float		PROHB_REGN_LO_PWR_RATIO;		//��ֹ����������ϵ��
float		PROHB_REGN_HI_PWR_RATIO;		//��ֹ����������ϵ��
float		ROC_LIMIT;		//������������
float		MAINT_COST;		//ά������
float		PAYB_CONST;		//����ϵ��
char		THR_FUEL_NAME[24];		//ȼ������
float		THR_INC_POLLU_COST;		//΢����Ⱦ����
int		WATER_TEMP_FACT;		//��ȴˮ������
int		GEN_STATE;		//�����״̬
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res1[2];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		res2[4];
}MODEL_SYNCHRONOUS_MACHE;
//�ֽ�ͷ��	
typedef struct MODEL_TAPCHANGER
{ 
SG_INT64		ID;		//���
char		DESCRIPTION[64];		//����
char		NAME[64];		//����
char		HIGH_STEP[64];		//HIGH_STEP
float		NEUTRAL_STEP;		//NEUTRAL_STEP
float		LOW_STEP;		//LOW_STEP
float		STEP_VOLTAGE_INCREMENT;		//STEP_VOLTAGE_INCREMENT
float		NEUTRAL_KV;		//NEUTRAL_KV
float		NORMAL_STEP;		//NORMAL_STEP
unsigned char		res0[4];
SG_INT64		OF_TRANSWINDING;		//��������
}MODEL_TAPCHANGER;
//���ӱ�	
typedef struct MODEL_TERMINAL
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
int		TERMINAL_TYPE;		//����
SG_INT64		OF_DEVICE;		//�����豸
char		ADDR[12];		//��ַ
unsigned char		res0[4];
SG_INT64		CONN_NODE_ID;		//���ӵ�ID
char		PHASE[6];		//��λ
char		PSRID[64];		//��ԴID
unsigned char		res1[2];
}MODEL_TERMINAL;
//��ѹ�������	
typedef struct MODEL_TRANS_WINDING
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		WINDING_TYPE;		//����
int		CONN_TYPE;		//��������
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_POWERTRANS;		//������ѹ��
float		RATED_KV;		//���ѹ
float		RATED_MVA;		//�����
float		R;		//����
float		X;		//�翹
float		R0;		//�������
float		X0;		//����翹
float		G;		//�������ŵ絼
float		B;		//���������ŵ���
float		MAX_AMP;		//������
unsigned char		ADJUST_FLAG;		//�ɵ���־
unsigned char		GROUND_FLAG;		//�ӵر�־
unsigned char		res1[2];
int		TAP_TYPE;		//��ͷ����
int		ACTUAL_TAP_POS;		//ʵ�ʵ�λ
float		AMP_MARG;		//����ԣ��
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
unsigned char		ENDNUMBER;		//���
unsigned char		res2[3];
}MODEL_TRANS_WINDING;
//��ѹ�ȼ���	
typedef struct MODEL_VOLT_LEVEL
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
SG_INT64		OF_SUBSTATION;		//��վ��_���
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//��׼��ѹ
}MODEL_VOLT_LEVEL;
//�����	
typedef struct MODEL_WINDGENERATOR
{ 
SG_INT64		ID;		//ID
char		name[64];		//����
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//�������վ
float		RATED_PF;		//���������
float		MAX_P;		//����й�
float		MIN_P;		//��С�й�
float		MAX_Q;		//����޹�
float		MIN_Q;		//��С�޹�
unsigned char		USABLE;		//���״̬
unsigned char		res0[3];
float		START_SPEED;		//��������
float		RATED_SPEED;		//�����
float		MAX_SPEED;		//������
float		mpower_P;		//�й�����
float		mpower_Q;		//�޹�����
float		mpower_U;		//��ѹֵ
float		mpower_I;		//����ֵ
char		PSRID[64];		//PSRID
unsigned char		res1[4];
}MODEL_WINDGENERATOR;
//�������߱�	
typedef struct MODEL_D_FEEDER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
char		DISP_CODE[64];		//���ȱ��
unsigned char		res0[4];
SG_INT64		AREA_FEATURE;		//��������
SG_INT64		OF_STATION;		//Դͷ���վ
SG_INT64		OF_BREAKER;		//���߿���
int		FA_TYPE;		//�����Զ�������
int		FA_LOCK_FLAG;		//�����Զ�����
char		PSRID[64];		//��ԴID
}MODEL_D_FEEDER;
//������ͷ	
typedef struct MODEL_D_JUNCTION
{ 
SG_INT64		ID;		//���
SG_INT64		OF_DEVICE;		//�����豸
}MODEL_D_JUNCTION;
//�����ͻ�	
typedef struct MODEL_D_CUSTOMER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//���ߴ���
SG_INT64		METER_ID;		//���
}MODEL_D_CUSTOMER;
//���	
typedef struct MODEL_METER
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_USAGEPOINT;		//���������
}MODEL_METER;
//CT	
typedef struct MODEL_D_CT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		CT_TYPE;		//����
char		ALIAS[100];		//����
SG_INT64		OF_BAY;		//�������
SG_INT64		OF_VOLT_LEVEL;		//��ѹ�ȼ�
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
short		PHASE;		//���
char		CT_MODEL[24];		//�����������ͺ�
unsigned char		res0[6];
double		RATED_KV;		//���ѹ
double		RATED_AMP_RATIO;		//�������
char		DISP_CODE[22];		//���Ⱥ�
unsigned char		res1[2];
int		POWER_STATE;		//����״̬
int		TOPO_ISLAND;		//���˵�������
double		ACCURACYLIMIT;		//�ٷֱȾ���
}MODEL_D_CT;
//�û������	
typedef struct MODEL_USAGEPOINT
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		res0[4];
SG_INT64		OF_EQLOAD;		//������Ч����
}MODEL_USAGEPOINT;
//ģ����	
typedef struct MODEL_ANALOG
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
SG_INT64		OF_DEVICE;		//�����豸
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//������վ
int		PORT;		//���Ӻ�
int		MEAS_TYPE;		//��������
double		VAL;		//ֵ
int		STATUS;		//״̬
int		PROCTIME;		//�仯ʱ��
int		UNIT;		//��λ
unsigned char		res0[4];
}MODEL_ANALOG;
//������ʷ��	
typedef struct his_simulation
{ 
int		ID;		//����ID
unsigned char		res0[4];
SG_INT64		TASKID;		//��������ID
SG_INT64		OF_DEVICE;		//�����豸
unsigned char		MEAS_TYPE;		//��������
unsigned char		res1[7];
double		TIME;		//һ�η����ڵ����ʱ��
float		VAL;		//������ֵ
unsigned char		res2[4];
}his_simulation;
//����ڵ��	
typedef struct net_node
{ 
int		ID;		//����ڵ�ID
char		NAME[64];		//�ڵ�����
char		ALIAS[64];		//��������
unsigned char		TYPE;		//�ڵ�����
unsigned char		res0[3];
}net_node;
//����߱�	
typedef struct net_edge
{ 
int		ID;		//�����ID
char		NAME[64];		//������
int		LEFTNODE;		//��ڵ�ID
int		RIGHTNODE;		//�ҽڵ�ID
int		DELAY;		//�߳�ʼʱ��
}net_edge;
//����ڵ��¼���	
typedef struct sim_event
{ 
int		ID;		//�¼�ID
unsigned char		res0[4];
double		EVENTTIME;		//�¼�����ʱ��
int		OBJECTID;		//�����¼��Ľڵ��ߵ�ID
unsigned char		TYPE;		//�¼�����
unsigned char		res1[3];
int		PARAM;		//�¼���صĽڵ��ߵ�ID
unsigned char		EVENTTYPE;		//0��Ϣ�¼���1�����¼�
unsigned char		res2[3];
SG_INT64		TASKID;		//��������ID
}sim_event;
//��Ϣ��������Ӧ��ϵ��	
typedef struct net_pow_relate
{ 
char		NODEID[64];		//��Ϣ���ڵ���
char		OF_DEVICE_MEAS[64];		//�ɼ�Ԫ��ID
char		OF_DEVICE_CTR[64];		//����Ԫ��ID
int		ID;		//ID
}net_pow_relate;
//cloudpssͨ����	
typedef struct pss_passage
{ 
SG_INT64		ID;		//ͨ��ID
char		NAME[256];		//ͨ������
char		CHANNLE_TYPE[256];		//���ͨ�����ƣ�Ҳ�����ͣ���Irms�
char		CHANNLE_PIN[256];		//���ͨ�����ţ�Ҳ��Ԫ�����������
SG_INT64		OF_DEVICE;		//�����豸
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
char		MEASTYPE_DESC[360];		//������������
}base_meas_def;
//ң��ʵʱ���ݱ�	
typedef struct rtval_analog
{ 
SG_INT64		ID;		//ID
float		VAL;		//ң��ֵ
int		STATUS;		//STATUS
int		PROCTIME;		//PROCTIME
unsigned char		res0[4];
}rtval_analog;
//���Ƴ�����	
typedef struct control_constant
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		TYPE[256];		//�������ͣ���P��Q
char		VALUE[256];		//����ֵ
char		PINS[64];		//��������
SG_INT64		OF_DEVICE;		//����Ԫ��ID
}control_constant;
//�����¼��	
typedef struct sim_task
{ 
SG_INT64		ID;		//��������ID
char		NAME[64];		//������������
SG_INT64		OF_FEEDER;		//������·ID
int		TIMELENGTH;		//����ʱ��
unsigned char		STATE;		//���״̬
unsigned char		res0[3];
}sim_task;
//����������	
typedef struct model_PV_inverter
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//����
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//��������ID
int		BASE_VOLTAGE;		//������ѹ�ȼ�
unsigned char		res0[4];
SG_INT64		NODEID;		//��������
double		RATE_CAPACITY;		//�����
double		ACTIVE_POWER;		//�й�����
double		REACTIVE_POWER;		//�޹�����
int		CONTROL_MODE;		//����ģʽ
unsigned char		res1[4];
}model_PV_inverter;
//model_AVC_Node	
typedef struct model_AVC_Node
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//����
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//��������ID
int		BASE_VOLTAGE;		//������ѹ�ȼ�
unsigned char		res0[4];
double		VOLTAGE;		//��ѹ��ֵ
int		UP_STATE;		//��ѹԽ���޵���ɢ״̬����
int		DOWN_STATE;		//��ѹԽ���޵���ɢ״̬����
int		NORMAL_STATE;		//��ѹ��Խ�޵���ɢ״̬����
unsigned char		res1[4];
}model_AVC_Node;
//model_AVC_Line	
typedef struct model_AVC_Line
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//����
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//��������ID
int		BASE_VOLTAGE;		//������ѹ�ȼ�
unsigned char		res0[4];
SG_INT64		START_NODEID;		//��ʼ��������
SG_INT64		END_NODEID;		//��β��������
double		RESISTANCE;		//����
double		REACTANCE;		//�翹
}model_AVC_Line;
//������Ϣ��	
typedef struct avc_feeder_info
{ 
SG_INT64		FEEDERID;		//����ID
double		ENERGY_LOSS;		//�������
double		MAX_VOLTAGE;		//��ߵ�ѹֵ
double		MIN_VOLTAGE;		//��͵�ѹֵ
double		ENERGY_LOSS_BEFORE;		//�Ż�ǰ�������
double		MAX_VOLTAGE_BEFORE;		//�Ż�ǰ��ߵ�ѹֵ
double		MIN_VOLTAGE_BEFORE;		//�Ż�ǰ��͵�ѹֵ
}avc_feeder_info;
//�����������ʷ�Ż������	
typedef struct avc_Inverter_Histrory
{ 
SG_INT64		INVERTERID;		//�����id
double		ACTIVE_POWER;		//�й�����
double		REACTIVE_POWER;		//�޹�����
int		CONTROL_MODE;		//����ģʽ
unsigned char		res0[4];
SG_INT64		TIME;		//�Ż�ʱ��
}avc_Inverter_Histrory;
//������������ʷ�Ż������	
typedef struct avc_compensator_Histrory
{ 
SG_INT64		COMPENSATORID;		//������id
double		EACH_CAPACITY;		//ÿ������
int		OPERATION_NUM;		//Ͷ������
int		MAX_ACT_NUM;		//ʱ�������������
SG_INT64		TIME;		//�Ż�ʱ��
}avc_compensator_Histrory;
//����Ԥ���	
typedef struct avc_predictive_load
{ 
SG_INT64		LOADID;		//����ID
SG_INT64		NODEID;		//��������
double		ACTIVE_POWER;		//�й�����
double		REACTIVE_POWER;		//�޹�����
int		TIME;		//0~95��0~23����Type���ʹ��
int		TYPE;		//0�����Ӽ���1��Сʱ����
}avc_predictive_load;
//���Ԥ���	
typedef struct avc_predictive_PV
{ 
SG_INT64		PVID;		//���ID
SG_INT64		NODEID;		//��������
double		ACTIVE_POWER;		//�й�����
int		TIME;		//0~96��0~24����Type���ʹ��
int		TYPE;		//0�����Ӽ���1��Сʱ����
}avc_predictive_PV;
//model_d_ac	
typedef struct model_d_ac
{ 
SG_INT64		ID;		//ϵͳ�豸ID
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
double		TSetmax;		//�յ��¶��趨����
double		TSetmin;		//�յ��¶��趨����
double		ETAmin;		//��Чϵ����Сֵ
double		ETAmax;		//��Чϵ�����ֵ
double		Racmin;		//������Сֵ
double		Racmax;		//�������ֵ
double		Cacmin;		//������Сֵ
double		Cacmax;		//�������ֵ
double		TSetAve;		//�����¶�����
double		DeltaTmin;		//�趨�¶��µ�����
double		DeltaTmax;		//�趨�¶��ϵ�����
double		Rlow;		//�����ϸ�б��
double		Rhigh;		//�����¸�б��
double		Pinuse_a;		//Sigmoid��״����
double		Pinuse_b;		//Sigmoid��״����
double		Pindr_a;		//Sigmoid��״����
double		Pindr_b;		//Sigmoid��״����
double		ACPara1;		//����ϵ��1
double		ACPara2;		//����ϵ��2
double		ACPara3;		//����ϵ��3
double		ACPara4;		//����ϵ��4
}model_d_ac;
//model_d_5g	
typedef struct model_d_5g
{ 
SG_INT64		ID;		//ϵͳ�豸ID
double		GTrafficMax;		//5G�������������
double		PMode1;		//1������
double		PMode2;		//2������
double		PMode3;		//3������
double		PMode4;		//4������
}model_d_5g;
//model_d_evcar	
typedef struct model_d_evcar
{ 
SG_INT64		ID;		//ϵͳ�豸ID
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
double		CarBattry;		//ƽ���������
double		ChargeSlow;		//���书��
double		ChargeHigh;		//��书��
double		Charge1;		//ÿ��һ���û�ռ��
double		Charge2;		//ÿ�������û�ռ��
double		Charge3;		//ÿ�������û�ռ��
double		ChomeAV;		//���ó���ֵ
double		ChomeSD;		//���ó���׼��
double		CCompAV;		//��˾����ֵ
double		CCompSD;		//��˾����׼��
double		CShopAV;		//�̳�����ֵ
double		CShopSD;		//�̳�����׼��
double		ChargeEff;		//���Ч��
double		CarQAV;		//��ʼ��ɷֲ���ֵ
double		CarQSD;		//��ʼ��ɷֲ���׼��
double		CarPara1;		//�������ռ��1
double		CarPara2;		//�������ռ��2
double		CarPara3;		//�������ռ��3
double		CarPara4;		//�������ռ��4
}model_d_evcar;
//��ˮ����	
typedef struct model_waterheater
{ 
SG_INT64		ID;		//ϵͳ�豸ID
char		name[64];		//����
char		mRID[64];		//�豸ΨһID
double		DeltaTW;		//�¶��趨����ƫ��
double		Twhmax;		//����¶�����
double		Twhmin;		//��С�¶�����
double		WHcapacity;		//��ˮ������
double		WHPower;		//��ˮ�������
double		TankAmax;		//ˮ���������ֵ
double		TankAmin;		//ˮ��������Сֵ
double		TankRmin;		//ˮ��������Сֵ
double		TankRmax;		//ˮ���������ֵ
double		DeltaWaterEv;		//��ˮ�¶��뻷���¶�֮��趨ֵ�
double		Shift_1;		//�޸�ƽ��ʱ����
double		Shift_2;		//΢��ƽ��ʱ����
double		Shift_3;		//����ƽ��ʱ����
double		Shift_4;		//ǿ��ƽ��ʱ����
double		Elast_1;		//�޸��Ե���ϵ��
double		Elast_2;		//΢���Ե���ϵ��
double		Elast_3;		//�����Ե���ϵ��
double		Elast_4;		//ǿ���Ե���ϵ��
double		WH_state;		//��ʼ����״̬
}model_waterheater;
//���б�	
typedef struct Rapa_Operation
{ 
SG_INT64		ID;		//ID
SG_INT64		DeviceID;		//�豸ID
int		Time;		//ʱ�䣨15����һ���㣩
unsigned char		res0[4];
double		Temp;		//�����¶�
double		Price;		//���
double		SHStream;		//��ˮ����
double		Original;		//ԭʼ�ۺϹ���
double		Rapa;		//���ǵ�ۺ�ۺϹ���
double		Reserve;		//Ǳ������
int		Type;		//����
unsigned char		res1[4];
}Rapa_Operation;
//�յ�۱�	
typedef struct Rapa_PowerPrice
{ 
int		Time;		//ʱ�䣨15����һ���㣩
unsigned char		res0[4];
double		Price;		//���
}Rapa_PowerPrice;
//�������¶ȱ�	
typedef struct Rapa_OutTemp
{ 
int		Time;		//ʱ�䣨15����һ���㣩
unsigned char		res0[4];
double		Temp;		//�����¶�
}Rapa_OutTemp;
//����ˮ���ٱ�	
typedef struct Rapa_WaterFlow
{ 
int		Time;		//ʱ�䣨15����һ���㣩
unsigned char		res0[4];
double		SHStream;		//��ˮ����
}Rapa_WaterFlow;
//�����	
typedef struct MODEL_REGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//����
char		PSRID[255];		//��ԴID
unsigned char		res0[1];
}MODEL_REGION;
//�������	
typedef struct MODEL_SUBREGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//����
SG_INT64		OF_REGION;		//��������
char		PSRID[255];		//��ԴID
unsigned char		res0[1];
}MODEL_SUBREGION;
//������ʵ����쳣�޸���	
typedef struct DAS_POWER_REVERSE
{ 
int		ID;		//ID
int		TIME;		//ʱ��


SG_INT64		OF_DEVICE;		//����̨����
float		B_PV_P;		//����ǰ����й�����
float		B_PV_Q;		//����ǰ����޹�����
float		A_PV_P;		//���ں����й�����
float		A_PV_Q;		//���ں����޹�����
float		B_EC_U;		//����ǰ���ɵ�ѹ
float		A_EC_U;		//���ں󸺺�Ԥ���ѹ
float		QF;		//�޹����ʵ�������
unsigned char		res0[4];
}DAS_POWER_REVERSE;
//���Ԥ���	
typedef struct DAS_PV_PREDICTION
{ 
SG_INT64		ID;		//��¼��
SG_INT64		DeviceID;		//�豸ID
int		MeasType;		//��������
float		Value;		//����ֵ
SG_INT64		Time;		//ʱ���
SG_INT64		PredictionID;		//Ԥ��ID
}DAS_PV_PREDICTION;
//�綯�����������	
typedef struct DAS_EV_MAN
{ 
SG_INT64		ID;		//��¼��
int		CHARGETIMESTART;		//��翪ʼʱ��
int		CHARGETIMEEND;		//������ʱ��
int		DISCHARGETIMESTART;		//�ŵ翪ʼʱ��
int		DISCHARGETIMEEND;		//�ŵ����ʱ��
SG_INT64		OF_DEVICE;		//��������豸
}DAS_EV_MAN;
//���಻ƽ�⴦���	
typedef struct DAS_UNBALANCE
{ 
SG_INT64		ID;		//��¼��
char		PhaseA[1024];		//A���豸�ܼ�
char		PhaseB[1024];		//B���豸�ܼ�
char		PhaseC[1024];		//C���豸�ܼ�
int		StartTime;		//��ʼʱ���
int		EndTime;		//����ʱ���
SG_INT64		OF_DEVICE;		//����̨��ID
}DAS_UNBALANCE;
//���Ա�	
typedef struct MODEL_TEST
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
int		NVALUE;		//����ֵ
float		FVALUE;		//����ֵ
float		MPOWER_P;		//�й�����ֵ
float		MPOWER_Q;		//�޹�����ֵ
float		IPOWER_P;		//�й�����ֵ
float		IPOWER_Q;		//�޹�����ֵ
}MODEL_TEST;
//�߼�Ӧ�����ñ�	
typedef struct DAS_CONFIG
{ 
int		ID;		//ID
char		APPCODE[64];		//Ӧ������
int		APPID;		//Ӧ�ñ��
int		PARAID;		//�������
char		NAME[64];		//��������
char		DESC[255];		//��������
unsigned char		res0[1];
int		TYPE;		//��������
char		CHVALUE[255];		//�ַ���ֵ
unsigned char		res1[1];
int		INTVALUE;		//����ֵ
float		FLOATVALUE;		//����ֵ
}DAS_CONFIG;
//model_thermalgenerator	
typedef struct model_thermalgenerator
{ 
SG_INT64		ID;		//���
double		MAX_P;		//����й�
double		MAX_PF;		//������������
double		MAX_Q;		//����޹�
double		MIN_P;		//��С�й�
double		MIN_PF;		//������������
double		MIN_Q;		//��С�޹�
double		MPOWER_I;		//����ֵ
double		MPOWER_P;		//�й�����
double		MPOWER_Q;		//�޹�����
double		MPOWER_U;		//��ѹֵ
char		NAME[64];		//����
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//�������վ
char		PSRID[64];		//��ԴID
double		RATED_P;		//�����
unsigned char		USEABLE;		//���״̬
unsigned char		res0[7];
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹֵ
double		IPOWER_I;		//����ֵ
unsigned char		OF_BASE_VOLTAGE;		//��׼��ѹ
unsigned char		res1[7];
}model_thermalgenerator;
//MODEL_HYDROPOWER	
typedef struct MODEL_HYDROPOWER
{ 
SG_INT64		ID;		//���
double		MAX_P;		//����й�
double		MAX_PF;		//������������
double		MAX_Q;		//����޹�
double		MIN_P;		//��С�й�
double		MIN_PF;		//������������
double		MIN_Q;		//��С�޹�
double		MPOWER_I;		//����ֵ
double		MPOWER_P;		//�й�����
double		MPOWER_Q;		//�޹�����
double		MPOWER_U;		//��ѹֵ
char		NAME[64];		//����
SG_INT64		OF_FEEDER;		//��������
SG_INT64		OF_SUBSTATION;		//�������վ
char		PSRID[64];		//��ԴID
double		RATED_P;		//�����
unsigned char		USEABLE;		//���״̬
unsigned char		res0[7];
double		IPOWER_P;		//�й�����
double		IPOWER_Q;		//�޹�����
double		IPOWER_U;		//��ѹֵ
double		IPOWER_I;		//����ֵ
unsigned char		OF_BASE_VOLTAGE;		//��׼��ѹ
unsigned char		res1[7];
}MODEL_HYDROPOWER;
//model_d_acline_dot	
typedef struct MODEL_D_ACLINE_DOT
{ 
SG_INT64		ID;		//���
char		NAME[32];		//����
double		P_VALUE;		//�й�����
double		Q_VALUE;		//�޹�����
double		CURRENT;		//����
double		VOLTAGE;		//��ѹֵ
SG_INT64		OF_ACLINE_SEGMENT;		//�����������߶�
SG_INT64		OF_TERMINAL;		//��������
}MODEL_D_ACLINE_DOT;
//MODEL_ENERGY_SOURCE	
typedef struct MODEL_ENERGY_SOURCE
{ 
SG_INT64		ID;		//���
char		NAME[64];		//����
char		ALIAS[100];		//����
unsigned char		OF_BASE_VOLTAGE;		//��ѹ�ȼ�
unsigned char		res0[3];
SG_INT64		OF_SUBSTATION;		//��վ����
SG_INT64		OF_FEEDER;		//���ߴ���
int		TOPO_ISLAND;		//���˵�������
unsigned char		res1[4];
double		MPOWER_P;		//�й�
double		MPOWER_Q;		//�й�
double		MPOWER_U;		//�й�
double		MPOWER_I;		//�й�
double		IPOWER_P;		//�й�
double		IPOWER_Q;		//�޹�
double		IPOWER_U;		//��ѹ
double		IPOWER_I;		//����
unsigned char		ATTRIBUTE;		//�ڵ����ͣ�1ƽ��ڵ㣻2���ʽڵ�
unsigned char		res2[7];
}MODEL_ENERGY_SOURCE;
//BASE_VOLT_DEF	
typedef struct BASE_VOLT_DEF
{ 
SG_INT64		ID;		//ID
char		EN_NAME[32];		//Ӣ����
char		CN_NAME[32];		//������
double		STD_VAL;		//��׼ֵ
double		H_LMT;		//��׼����
double		L_LMT;		//��׼����
}BASE_VOLT_DEF;
//MODEL_TOPOLOGICAL_ISLAND	
typedef struct MODEL_TOPOLOGICAL_ISLAND
{ 
SG_INT64		ID;		//���
char		NAME[32];		//����
int		CONTAINSTOPOLOGICALNODE;		//�������˽ڵ�����
int		FIRSTPSR;		//���豸�±�
int		NUMBEROFPSR;		//�豸��Ŀ
unsigned char		ISCONVERGED;		//�Ƿ�����
unsigned char		res0[3];
double		LOADPOWERP;		//�����ܸ����й�
double		LOADPOWERQ;		//�����ܸ����޹�
double		SUMLOSSP;		//����������й�
double		SUMLOSSQ;		//����������޹�
unsigned char		ISLAND;		//�Ƿ�µ�
unsigned char		CLOSEDLOOP;		//�Ƿ�ϻ�
unsigned char		res1[6];
}MODEL_TOPOLOGICAL_ISLAND;
//MODEL_TOPOLOGICAL_NODE	
typedef struct MODEL_TOPOLOGICAL_NODE
{ 
SG_INT64		ID;		//���
char		NAME[32];		//����
SG_INT64		OF_TOPOLOGICALISLAND;		//�������˵�
int		CONTAINSCONNECTIVITYNODE;		//�������ӽڵ�����
int		NUMBEROFPSR;		//�豸����
double		VLTMAG;		//��ѹ��ֵ
double		VLTANGLE;		//��ѹ���
}MODEL_TOPOLOGICAL_NODE;
#endif 
