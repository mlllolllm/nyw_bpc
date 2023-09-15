#ifndef __HH_RDBMEM_MAN_H__
#define __HH_RDBMEM_MAN_H__
#include "dppclient.h"
#include "osbase.h"
#include "rdpbasedef.h"
#include "sgnp_base.h"
#include "sgconst_cloud.h"
#include <map>
#if ! defined( ACE_Proper_Export_Flag )
#   include "ace/config.h"
#endif

#if defined(RDP_REALDB_DLL)
#define _RDP_REALDB_DLL_PORT ACE_Proper_Export_Flag
#else
#define _RDP_REALDB_DLL_PORT ACE_Proper_Import_Flag
#endif


//#define IDP_RDBUSE_NEWIDX
//---------------------------------------------------------------------------
//ͳһ��һ����������
#define		DEF_RDB_MAXSTRLEN    4096
//---------------------------------------------------------------------------

//ʵʱ�������ģʽ
#define SG_RDB_FIELDMODE_PARA  0
#define SG_RDB_FIELDMODE_DATA  1
#define SG_RDB_FIELDMODE_MEM	2


#define SG_RDB_PARATBLNUM 2  //ʵʱ��֧�ִ�SG_RDB_PARATBLNUM�Ų������м���һ��ʵʱ���
#define SG_RDB_RELTBLNUM  5
#define SG_RDB_RMEMFILE_VERSION		1
#define	SG_RDB_RMEM_GETVERSION(VERSION) 	if(VERSION<0) { VERSION=SG_RDB_RMEMFILE_VERSION; if(VERSION<0) return false; }




typedef union USG_RDB_NUMVAR
{
	SG_INT64     IntVal;
	double		DblVal;
}USG_RDB_NUMVAR;

//---------------------------------------------------------------------------
//һ��������������
//---------------------------------------------------------------------------
typedef struct SG_RDB_DATVAR
{
	short			DatType;
	USG_RDB_NUMVAR  NumVal;
	std::string		StrVal;
}SG_RDB_DATVAR;


#define SG_FIELDNAMEDES_LEN sizeof(SG_FIELDNAMEDES)
#define SG_RTBL_PROCMODE_VALTBL				0x00000001		//���ؼ���ʱ,�Ƿ��ܱ���ֵ��
#define SG_RTBL_PROCMODE_LOAD_SUB				0x00000002		//����ʱ,�������ر�־
#define SG_RTBL_PROCMODE_SAVEHIS_BYCHAN		0x00000004		//�Ƿ���ݱ仯�洢��ʷ����
#define SG_RTBL_PROCMODE_INMINIBOX				0x00000008		//�ñ��Ƿ������΢������
#define SG_RTBL_PROCMODE_PERIODCHECK			0x00000010		//�ñ��Ƿ����ڼ��
#define SG_RTBL_PROCMODE_SYNC_NOLACK			0x00000020		//�ñ���ȱͬ������ң�ű���������
#define SG_RTBL_PROCMODE_SYNC_FATHERDB			0x00000040		//�ñ��ֶθı���д�ϼ����ݿ�

typedef struct SRDB_RTBLINFO_PARA
{
	SG_FIELDNAME		TblCode;         //ʵʱ�����
	SG_FIELDNAMEDES		TblDesc;			//ʵʱ�������
	SG_FIELDNAME		KeyField;			//��������,���ڽ�֧�ֵ������ı�
	SG_FIELDNAMEDES		WorkSpaceField;//�������ݿ��й�˾id�ֶ���
	SG_FIELDNAMEDES		DatLevelField;//�������ݿ������ݵȼ��ֶ���
	SG_FIELDNAMEDES		ParaTbl[SG_RDB_PARATBLNUM];		//������1������ ����֧����������union��һ��ʵʱ��
	SG_FIELDNAMEDES		DataTbl;		//���ݱ�����
	SG_FIELDNAMEDES		RelTbl[SG_RDB_RELTBLNUM];		//��ز�����1����,���ò�����ı��,���¼��ظñ�
														//	SG_FIELDNAMEDES		RelTbl2;		//��ز�����2��,���ò�����ı��,���¼��ظñ�
	//SG_FIELDNAME	ParaTblFlagField;	//���Ǵ�һ����ػ��Ƕ�����ص�������,����һ������ֵ
	SG_MSG			ParaAppendSQL;	//���������ʱ�ĸ���SQL���
	SG_INT			TblID;		//ʵʱ���ID
	SG_INT			LoadSrvType;	//���صķ�������
	SG_INT			BatchNo;	//��ȡʱ���������
	SG_INT			ObjType;		//ʵʱ���Ķ�������  ���޶���,��Ϊ-1
	SG_UINT64			MaxKey;	//�������ֵ
	SG_UINT64			MinKey;	//������Сֵ
	SG_INT			BackupTime;			//�������ݱ��ʱ��
	SG_INT			L_BackupTime;			//���ر������ݱ��ʱ��
	SG_INT			SaveHisPeriod;			//�洢��ʷ���ݱ��ʱ��
	SG_INT			ProcMode;				//����ģʽ 
	SG_INT			MaxRcdNum;		//�������ݿ��е�����¼����,���γ����ݿ�ʱ,�����еĲ�ͬ�ֶ�
	SG_INT			LogicCellType;		//�߼����ݵ�Ԫ������
	SG_INT			LogicCellWorkSpaceNum;	//�߼����ݵ�Ԫʹ��WorkSpace��������
	SG_SHORT		KeyFieldNo; //�������ǵڼ����ֶ� ���Ϊ-1 �����ñ�û������
	SG_SHORT		WorkSpaceFieldNo; //WorkSpace���ǵڼ����ֶ� ���Ϊ-1 �����ñ�û��WorkSpqce�ֶ�
	SG_SHORT		DatLevelFieldNo; //���ݵȼ����ǵڼ����ֶ� ���Ϊ-1 �����ñ�û�����ݵȼ��ֶ�
	SG_SHORT		FieldNum; //�ֶθ���
	SG_SHORT		IdxNum;	 //�ñ��ж��ٸ�����
	SG_SHORT		RcdLen;  //��¼����
	SG_UCHAR		LoadPTblNum;	//���ز�����ĸ���
	SG_UCHAR		LoadRelTblNum;	//������ر�ĸ���
	SG_UCHAR		HasUpdateTimeFlag;	//�Ƿ���Ҫ�����޸�ʱ����Ϣ��־
	SG_UCHAR		HasDatLevel;	//�Ƿ������ݵȼ���Ϣ
	int InitDat();
	SG_INT	Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	SG_BOOL Equal(SRDB_RTBLINFO_PARA &p);
}SRDB_RTBLINFO_PARA;
typedef struct SRDB_RTBLINFO_DATA
{
	SG_UCHAR		 WriteFlag;      //д���ݱ�־,��ʱ��Ҫ�����ݿ��д,����ʱ��ı��Ĵ�С
	SG_UCHAR		 LoadFlag;     //�����¼��صı�־
	SG_UINT64			 RealMinKey;	//ʵ�ʵ��������ֵ
	SG_UINT64			 RealMaxKey;	//ʵ�ʵ�������Сֵ
	SG_UINT TblKeyChangeVer;	//�ñ������Ķ��İ汾,�����ؽ�����������
	SG_UINT		TblChangeVer; //�ñ�Ķ��İ汾,�����ؽ���ͨ�������붯̬����
	SG_UINT		RcdChangeTime; //�ñ��¼�Ķ���ʱ��(���Ժ���),���ڷ��ͱ仯����
	SG_INT		RcdNum;
	SG_INT		TblOffset;		 //�ñ��ڱ���Ϣ�е�λ��
	SG_INT		FieldInfoOffset; //�ñ�����ƫ�ƺ�
	SG_INT		IdxInfoOffset; //�ñ��������ƫ�ƺ�	
	SG_INT64	RcdOffset; //�ñ��������ʼ�ֽ�ƫ��
	SG_INT64	UpdateTimeOffset; //�ñ���޸�ʱ���ƫ��
	SG_INT64	WriteProcID; //��ʵʱ������Ľ���ID

	int InitDat(SG_INT64 MaxKey);
	//SG_INT	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
}SRDB_RTBLINFO_DATA;
typedef struct SRDB_SCHEMAINFO
{
	SG_INT64	SchemaHandle;	//ʵʱ���� ȫϵͳΨһ
	SG_INT		SchemaDBNo;		//��rtdb_dbinfo�еĶ���
	SG_INT		ShareMemKey;	//�����ڴ�Keyֵ
	SG_INT		SDBType;		//ʵʱ������ 0�������ڴ�� 1���о�̬�ڴ�� 2������ʵʱ����
	SG_INT		UserCnt;		//��ǰ�����û��������������û�����Ϊ0ʱ�����Ҹ��ڴ��ǿ�ɾ���ģ������ɾ����������ڴ�
	SG_UINT		ProcMode;		//����ģʽ bit0:1�ǳ�פ�ڴ�
	SG_INT		ValidFlag;		//��Ч��־
	SG_UINT		LastUseTime;	//���ʹ��ʱ��
	SG_INT64	ManageProcID;   //����ProcID�Ƿ�Ҳ����
}SRDB_SCHEMAINFO;

//ʵʱ�����
class CSgRDBMemBaseOper;
class CRDBLoadSetting;
class CRDBTableInfo;
class CRDBFieldInfo;
class _RDP_REALDB_DLL_PORT CSgRDBMemBase
{
	friend class CSgRDBMemBaseOper;
	CSgRDBMemBaseOper *m_MemBaseOper;
protected:
	SG_UINT64				m_SchemaHandler;
protected:
	virtual int GetRtDBLoadSetting(CRDBLoadSetting &LoadSetting);
	int CreateShareMemory(CRDBLoadSetting &LoadSetting);
	int WriteRDBToFile(CSgString &FileName);
public:
	CSgRDBMemBase(SG_UINT64 SchemaHandler);
	~CSgRDBMemBase();
	int LoadOneTable(CGAP_DppSrvClient &DBEngine, char *pRTblName);
	//ӳ�乲���ڴ�,����������
	virtual int MapShareMemory();
	int GetRTblNum();
	int GetRTblNo(char *pTblName);
	int GetRTblInfo(int RTblNo, CRDBTableInfo *pTblInfo);
	int GetRTblInfo(char *pRTblName, CRDBTableInfo *pTblInfo);
	int BackupRTbl(CGAP_DppSrvClient &DBEngine, CGAP_TSDASrvClient_Real &TSDAClient, VECT_LOGICCELL *pLogicCellList = NULL);
	int GetLogicCellNums();
	int GetLogicCellUpdateTime(S_LOGICCELLINFO &LogicCell, SG_UINT &UpdateTime);
	int SetLogicCellUpdateTime(S_LOGICCELLINFO &LogicCell, SG_UINT &UpdateTime);
	int GetLogicCellInfo(int RcdNo, S_LOGICCELLINFO &LogicCell,SG_UINT *pUpdateTime=NULL);
	int SaveRTblHisDatByChanField(CGAP_TSDASrvClient_Real &TSDAClient, VECT_LOGICCELL *pLogicCellList);
	SG_UCHAR GetLoadFromDBFlag();
	int LoadRealTable();
	int LoadTableChange(CGAP_DppSrvClient &DBEngine,char *pRTblName, VECT_TWOINT64 *pChanItemList, char *pTblName);
	CRDBFieldInfo *GetTblFieldInfo(CRDBTableInfo &TblInfo, SG_INT FieldPtr);
	int CheckRealTable();
	int CheckOneTable(CGAP_DppSrvClient &DBEngine, char *pRTblName);
	int GetUniqueKeyList(SG_INT TblNo, VECT_INT &KeyPtrList);
	int UnLockTable(char *pRTblName);
	int UnLockTable(int RTblNo);
};

class _RDP_REALDB_DLL_PORT CSgRDBManagerOper
{
public:
	static int CheckRDBSchema();
	static int SetManageProcFlag();
	static int SetRDBUpdateTime(SG_UINT64 SchemaHandler);
	static int GetSchemaHandler(SET_INT64 &SchemaHandlerList);
	static int GetSchemaBaseInfo(SG_UINT64 SchemaHandler, SRDB_SCHEMAINFO &ScheamInfo);
	static void SetFieldValByType(short int srctype, char *srcpt, int dftype, int dflen, char *colpt);
	static int GetDistinctDatSet(CSgDataSet &SrcDatSet, CSgDataSet *pDesDatSet, int RetRcdNum);

};

#endif