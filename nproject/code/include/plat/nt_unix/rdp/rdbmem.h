#ifndef __HH_RDBMEM_H__
#define __HH_RDBMEM_H__
#include "dppclient.h"
#include "osbase.h"
#include "rdpbasedef.h"
#include "sgnp_base.h"
#include "sgconst_cloud.h"
#include "rdbman.h"
#include <map>
#if ! defined( ACE_Proper_Export_Flag )
#include "ace/config.h"
#endif

#if defined(RDP_REALDB_DLL)
#define _RDP_REALDB_DLL_PORT ACE_Proper_Export_Flag
#else
#define _RDP_REALDB_DLL_PORT ACE_Proper_Import_Flag
#endif


class _RDP_REALDB_DLL_PORT CRDBTableInfo
{
	friend class CSgRDBManagerOperBase;
	friend class CSgRDBMemBaseOper;
protected:
	SRDB_RTBLINFO_PARA Para;
	SRDB_RTBLINFO_DATA Data;
public:
	int InitDat();
	int	Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	int GetRcdLen();
	int GetRcdNum();
	int GetFieldNum();
	int GetIndexNum();
	int GetKeyField(CSgString &KeyField);
	int GetKeyFieldPtr();
	int GetWKSFieldPtr();
	int GetWKSField(CSgString &WKSField);
	int GetTblID();
	char *GetTblName();
	char *GetTblDesc();
	char *GetParaTblName(int ParaTblNo);
	char *GetRelationTblName(int RelTblNo);
	char *GetDataTblName();
	SG_UCHAR GetWriteFlag();
	int GetMaxRcdNum();
	int GetObjType();
	int GetProcMode();
	int GetLoadParaTblNum();
	int GetRelationTblNum();
	int GetLogicCellWKSNum();
	int GetLogicCellType();
	int HasCloudSyncFlag();
	int GetDatVerID();
	//���ݲ������ñ仯��Ҫ���¼���
	int ReLoadByCfgChan();
};
/***********************************************
�������Ա�����Ϣ�ṹ
***********************************************/
#define SG_RTBL_COL_PROCMODE_SYNCRTDB		0x00000001		//�Ƿ��ǿ���ͬ���ֶ�
#define SG_RTBL_COL_PROCMODE_SAVEHISDB		0x00000002		//�Ƿ�洢��ʷ����
#define SG_RTBL_COL_PROCMODE_SAVECLEAR		0x00000004		//�Ƿ�洢��ɺ������ֶ�
#define SG_RTBL_COL_PROCMODE_CHANGESAVE		0x00000008		//���ֶ��Ƿ��Ǳ仯�洢�ֶ�
#define SG_RTBL_COL_PROCMODE_SYNCFATHERDB	0x00000010		//�ֶθı��Ƿ��дԴ�����ݿ�
//����IDX��Ϣ�����Զ������
#define SG_RTBL_COL_PROCMODE_IDXFIELD		0x80000000		//���ֶ��Ƿ��������ֶ�

//�������Ա�����Ϣ�ṹ
class _RDP_REALDB_DLL_PORT CRDBFieldInfo
{
public:
	SG_FIELDNAME FieldName;
	SG_FIELDNAME TblCode;
	SG_FIELDNAMEDES FieldDesc;			//ʵʱ�������
	SG_FIELDNAMEDES DBFieldName[SG_RDB_PARATBLNUM];		//�ڵ�һ���������е�����,
	SG_FIELDNAMEDES HisDBFieldName;		//�洢����ʷ���ݿ��е�����,
	SG_UCHAR FieldMode;    //0:������ 1:������ 2:�ڴ���
	SG_UCHAR	  DispFlag;  //�ڴ��Ƿ��ڹ�������ʾ
	SG_SHORT FieldNo;  //���ڱ��ڵ����
	SG_SHORT FieldType;
	SG_SHORT FieldLen;
	SG_SHORT SqlType;			// for oracle
	SG_USHORT DatOffset;			//�ֶ�������һ����¼�е����λ��
	SG_UINT	ProcMode;
	SG_INT		TblID;
	union
	{
		SG_FIELDNAMEDES cVal;			//ȱʡֵ
		SG_INT64		iVal;
		double			dVal;
	}DefaultVal;
public:
	CRDBFieldInfo();
	~CRDBFieldInfo();
	void SetFieldName(SG_CHAR*pFieldName);
	SG_CHAR *GetFieldName();
	//��������Ϣ�Ƿ�һ��
	SG_BOOL Equal(CRDBFieldInfo &p);
	SG_BOOL GetColVal(void *pColDat, CSgString &xStr);
	SG_BOOL SetIdxFieldFlag(SG_BOOL Flag);
	SG_BOOL GetIdxFieldFlag();
	SG_BOOL Serialize(CSgArchive&ar, int VerNo = -1);
};

//--------------------------------------------------------------------------
//�����Ƕ�ʵʱ���ݿ�ϵͳ�в��������Ķ���
//--------------------------------------------------------------------------
#define  SG_RDB_LOGIC_COND_AND              0        //��
#define  SG_RDB_LOGIC_COND_OR               1        //��

#define  SG_RDB_COND_EQU              0        //����
#define  SG_RDB_COND_LARGE            1        //����
#define  SG_RDB_COND_SMALL            2        //С��
#define  SG_RDB_COND_LARGEEQU         3        //���ڵ���
#define  SG_RDB_COND_SMALLEQU         4        //С�ڵ���
#define  SG_RDB_COND_NOTEQU           5        //������

typedef struct SG_RDB_CONDINFO
{
	unsigned char	LogicOpt;
	unsigned char	RelOpt;
	short			TblNo;
	std::string		Code;
	SG_RDB_DATVAR		Val;			//����ֵ
	CRDBFieldInfo *pColInfo; //ѡ�����ڱ��е�����Ϣ
	SG_RDB_CONDINFO()
	{
		pColInfo = NULL;
		TblNo = 0;
		Val.DatType = SG_FIELDTYPE_INT64;
		Val.NumVal.IntVal = 0;
		Val.StrVal = "";
		LogicOpt = SG_RDB_LOGIC_COND_AND;
		RelOpt = SG_RDB_COND_EQU;
	};
}SG_RDB_CONDINFO;
typedef std::vector<SG_RDB_CONDINFO > VECT_RDBCOND;
#define SG_DEFAULT_RUNNING_SCHEMAHANDLER     1
#define SG_RDB_DYNAMIC_SCHEMAHANDLER_MIN     1000 //��̬Schema�ľ����Сֵ

#define SG_RDB_DBTYPE_RUNNING	1 //����̬ʵʱ��
#define SG_RDB_DBTYPE_STUDY		2 //�о�̬ʵʱ��
#define SG_RDB_DBTYPE_CALCCASE	3 //����ʵʱ��
//

#define SG_RDB_LOADSET_KEY_LOADTYPE "LoadType"
#define SG_RDB_LOADSET_KEY_RTDBVER "RtDBVer"
#define SG_RDB_LOADSET_KEY_SRVTYPE "SrvType"
#define SG_RDB_LOADSET_KEY_SCHEMADBNO "SchemaDBNo"
#define SG_RDB_LOADSET_KEY_SCHEMATYPE "SchemaType"
#define SG_RDB_LOADSET_KEY_PROCMODE "SchemaProcMode"
#define SG_RDB_LOADSET_KEY_REPLACEKEY "ReplaceKey"
#define SG_RDB_LOADSET_KEY_REPLACEKEY_NAME "Name"
#define SG_RDB_LOADSET_KEY_REPLACEKEY_VAL "Value"

class _RDP_REALDB_DLL_PORT CRDBLoadSetting
{
public:
	//
	SG_INT				LoadType; //0: �����ݿ����  1�����ļ�����
	SG_INT				RtDBVerNo;
	SG_INT				SchemaDBNo;
	SG_INT				SchemaType;
	SG_UINT				SchemaProcMode;
	std::string			SrvTypeStr;  //LoadType=0 ��SrvType��Ϣ  1:���ļ�������
	MAP_STRING_STRING	ReplaceKeyList;	//first:Key�ȹؼ��֣���workspace SysID��  second: �滻��Ϣ
public:
	CRDBLoadSetting();
	~CRDBLoadSetting();
	int Compare(CRDBLoadSetting *pLoadSetting);
	void operator = (CRDBLoadSetting &para);
	void operator = (CHSDA_RTDBLoadPara &para);
	//ParaBuf��Json�ļ���ʽ {"LoadType":1,"RtDBVerNo",5,"SrvTypeStr":"1,2",
	//"ReplaceKey":[{"name":"OF_SUBSTATION","value":"100300000000000147,100300000000000148"},{"name":"OF_VOLT_LEVEL","value":"101400000000000114"}]}
	int SetPara(CSgString &ParaBuf);

private:
	int Free();
};
//����ʵʱ��,����̬ʵʱ��
class _RDP_REALDB_DLL_PORT CSgRDBMemCalcCase :public CSgRDBMemBase
{
	friend class CSgRDBMemBase;
	static CSG_OS_ThreadVar		m_DatLock;
	static MAP_INT64_VOIDPT		m_RtDBLoadSetting; //first: SchemaHandler second:CRDBLoadSetting
protected:
	static int FreeAllLoadSetting();
	static int GetRtDBLoadSetting(SG_INT64 m_SchemaHandler, CRDBLoadSetting &LoadSetting);
//	virtual int GetRtDBLoadSetting(CRDBLoadSetting &LoadSetting);
public:
	CSgRDBMemCalcCase(SG_UINT64 SchemaHandler);
	~CSgRDBMemCalcCase();
	//�ͷű�����ӳ�䵽������ʵʱ��
	static int FreeAllShareMemory();
	int CreateShareMemory(CRDBLoadSetting &LoadSetting);
	//ӳ�乲���ڴ�,����������
	virtual int MapShareMemory();
	virtual int FreeShareMemory();
	int WriteRDBToFile(CSgString &FileName);
};
//���ʵʱ��,����פʵʱ��
class _RDP_REALDB_DLL_PORT CSgRDBMemOverall :public CSgRDBMemBase
{
	friend class CSgRDBMemBase;
	static CSG_OS_ThreadVar		m_DatLock;
	static MAP_INT64_VOIDPT		m_RtDBLoadSetting; //first: SchemaHandler second:CRDBLoadSetting
	static SG_UINT				m_WSCfgFileTime;
protected:
	static int GetRtDBLoadSetting(SG_INT64 m_SchemaHandler, CRDBLoadSetting &LoadSetting);
public:
	CSgRDBMemOverall(SG_UINT64 SchemaHandler = SG_DEFAULT_RUNNING_SCHEMAHANDLER);
	~CSgRDBMemOverall();
	//��ȡ�����ļ��г�פ�ڴ��ʵʱ������
	static int ReadSchemaInfoFromFile(SET_INT64 *pSettingChanRDBHandlerList = NULL);
	//��ȡ�����ļ��г�פ�ڴ��ʵʱ������
	static int GetCfgSchemaHandler(SET_INT64 &SchemaHandlerList);
	static int GetCfgSchemaInfo(SG_UINT64 SchemaHandler, CRDBLoadSetting &LoadSetting);
	//�ͷű�����ӳ�䵽������ʵʱ��
	static int FreeAllShareMemory();
	int LoadRealTableForCfgChan();
	//����ʵʱ��
	int CreateShareMemory();
	//����ʵʱ�⵽�ļ���
	int WriteRDBToFile(CSgString &FileName);
	//ӳ�乲���ڴ�,����������
	virtual int MapShareMemory();
	//�ͷŹ����ڴ�
	virtual int FreeShareMemory();
};
#define SG_RDBTBL_SYNCMODE_PARA   0X01
#define SG_RDBTBL_SYNCMODE_DATA   0X02
class _RDP_REALDB_DLL_PORT CSgRDBTable
{
protected:
	friend class CSgRDBSqlOperBase;
	int m_CurTblNo;
	SG_UINT64 m_SchemaHandler;
	SG_UCHAR m_LockFlag;
protected:
	void *GetColValByNo(int RcdNo,int ColNo, CRDBFieldInfo **pFieldInfo=NULL,int *pFieldLen =NULL);
	void *GetFirstRcd_UnLock();
	int ColValCompare(int RcdNo, VECT_RDBCOND &DBCond);
	CRDBFieldInfo *GetFieldInfo();
	SG_BOOL SetColValChangeInfo(int RcdNo,int ColNo, CRDBFieldInfo &FieldInfo);
	int InitOneRcdMemory(char *pRcdDat);
	template< class MATHTYPE >
	SG_BOOL GetAtBase(int RcdNo, short ColNo, MATHTYPE *pVal);
	template< class MATHTYPE >
	SG_BOOL SetAtBase(int RcdNo, short ColNo, MATHTYPE &Val);
	int OpenTable(int RTblNo, unsigned char LockFlag, unsigned char ForceOpenFlag,int MaxWaitMs);
	int OpenTable(int RTblNo, unsigned char LockFlag, unsigned char ForceOpenFlag);
public:
	CSgRDBTable(SG_UINT64 SchemaHandler= SG_DEFAULT_RUNNING_SCHEMAHANDLER);
	~CSgRDBTable();
	void SetSchemaHandler(SG_UINT64 SchemaHandler);
	//��ʵʱ���
	int OpenTable(char *RTblName,unsigned char LockFlag=0,unsigned char ForceOpenFlag=0,int MaxWaitMs=0);
	int OpenTableByTblID(int RTblID, unsigned char LockFlag = 0, unsigned char ForceOpenFlag = 0, int MaxWaitMs = 0);
	int ReOpenTable(unsigned char LockFlag =0,unsigned char ForceOpenFlag =0, int MaxWaitMs = 0);
	virtual int TableCanUse();
	virtual int CloseTable();

	//��ȡ��Ļ�����Ϣ
	int GetRcdLen();
	int GetRcdNum();
	int GetFieldNum();
	int GetFieldPtr(char *pFieldName);
	int GetKeyField(CSgString &KeyField);
	int GetKeyFieldPtr();
	char *GetTableName();
	CRDBFieldInfo *GetFieldInfo(int FieldNo);
	CRDBFieldInfo *GetFieldInfo(char *pFieldName);
	int GetTblInfo(CRDBTableInfo *pTblInfo);
	//������صĺ���
	int RegisterIndex(char *pFieldNames);
	int UnRegisterIndex(char *pFieldNames);
	int IsIndexField(SG_INT FieldPtr);
	int GetUniqueKeyList(VECT_INT &KeyPtrList);
	SG_UINT	GetKeyIndexCreateTime();

	//�޸ı������
	//SyncMode bit0:ͬ�������ֶ�  bit1:ͬ�������ֶ�
	int InsertRecorder(CSgDataSet &DatSet,int SyncMode);
	//SyncMode bit0:ͬ�������ֶ�  bit1:ͬ�������ֶ�
	int UpdateRecorder(CSgDataSet &DatSet,int SyncMode);
	//SyncMode bit0:ͬ�������ֶ�  bit1:ͬ�������ֶ�
	int DelRcdByKey(VECT_INT64 &KeyIDList,int SyncMode);
	int AddRcd(int RcdNum, int RcdLen, void *pRcdDat);
	int DelRcdByNo(int RcdNo);
	int DelAllRcd();
	//SyncMode bit0:ͬ�������ֶ�  bit1:ͬ�������ֶ�
	int SyncRecorder2ParaDB(int SyncMode,VECT_INT *pRcdNoList=NULL);

	void *GetFirstRcd();//ֻ��д�򿪵�,�ſ������������
	//��ȡ��ļ�¼��Ϣ
	void *GetRcdByKey(SG_INT64 KeyID, int *pRcdNo = NULL);
	void *GetRcdByNo(int RcdNo);
	int GetRcdByNo(int RcdNo, char *pRcdDat, int RcdLen = 0);
	int PutRcdByNo(int RcdNo, char *pRcdDat, SG_BOOL IdxChanFlag = false, SG_BOOL UpdateTimeFlag = false, int RcdLen = 0);
	int GetRcdNoByFieldVal(VECT_RDBCOND &DBCondList, VECT_INT &RcdNoList, VECT_INT *pFindInRcdList = NULL);
	int GetRcdNoByFieldVal(VECT_STRINT64 &FieldValList, VECT_INT &RcdNoList, VECT_INT *pFindInRcdList = NULL);
	int GetRcdNoByFieldVal(char *pFieldName,SG_INT64 Val,VECT_INT &RcdNoList, VECT_INT *pFindInRcdList = NULL);
	int GetRcdDataSet(CSgDataSet &RetDatSet,VECT_INT *pRcdNoList = NULL);
	int GetRcdDataSet(char *pFieldNames,CSgDataSet &RetDatSet, VECT_INT *pRcdNoList = NULL);

	SG_BOOL GetRcdUpdateTimeByNo(SG_INT RcdNo, SG_UINT &UpdateTime);
	//���ø���ʱ���ֵ
	int SetUpdateTimeByNo(SG_INT RcdNo, SG_UINT UpdateTime = 0);
	//��������������Ϣ
	int SetIdxChange();
	//��ȡ������ֵ
	int	GetRcdNoByKey(SG_INT64 KeyID);
	SG_UINT64 GetPrimaryKeyValue(int RcdNo);
	SG_INT64	GetWorkSpaceByKey(SG_INT64 KeyID);
	SG_INT64	GetWorkSpaceByNo(int RcdNo);

	SG_BOOL GetAt(int RcdNo,short FieldNo,CSgString &Val);
	SG_BOOL GetAt(int RcdNo, short FieldNo, SG_Date &Val);
	SG_BOOL GetAt(int RcdNo, short FieldNo, SG_INT64 *pVal);
	SG_BOOL GetAt(int RcdNo,short FieldNo, SG_INT *pVal);
	SG_BOOL GetAt(int RcdNo,short FieldNo,SG_SHORT *pVal);
	SG_BOOL GetAt(int RcdNo,short FieldNo, SG_UCHAR *pVal);
	SG_BOOL GetAt(int RcdNo,short FieldNo,float *pVal);
	SG_BOOL GetAt(int RcdNo,short FieldNo,double *pVal);

	SG_BOOL SetAt(int RcdNo,short FieldNo,CSgString &Val);
	SG_BOOL SetAt(int RcdNo, short FieldNo, SG_Date &Val);
	SG_BOOL SetAt(int RcdNo,short FieldNo, SG_INT *pVal);
	SG_BOOL SetAt(int RcdNo, short FieldNo, SG_INT64 *pVal);
	SG_BOOL SetAt(int RcdNo,short FieldNo, SG_SHORT *pVal);
	SG_BOOL SetAt(int RcdNo,short FieldNo, SG_UCHAR *pVal);
	SG_BOOL SetAt(int RcdNo,short FieldNo,float *pVal);
	SG_BOOL SetAt(int RcdNo,short FieldNo,double *pVal);

	SG_BOOL GetAt(int RcdNo, char *pFieldName, CSgString &Val);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, SG_Date &Val);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, SG_INT64 *pVal);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, SG_INT *pVal);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, SG_SHORT *pVal);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, SG_UCHAR *pVal);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, float *pVal);
	SG_BOOL GetAt(int RcdNo, char *pFieldName, double *pVal);

	SG_BOOL SetAt(int RcdNo, char *pFieldName, CSgString &Val);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, SG_Date &Val);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, SG_INT *pVal);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, SG_INT64 *pVal);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, SG_SHORT *pVal);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, SG_UCHAR *pVal);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, float *pVal);
	SG_BOOL SetAt(int RcdNo, char *pFieldName, double *pVal);

};
#define  SG_OBJMODEL_RELATION_PARENT		0X01  //���ӹ�ϵ
#define  SG_OBJMODEL_RELATION_CONNECT		0X02  //���ӹ�ϵ
#define  SG_OBJMODEL_RELATION_TRIGGER		0X04  //������ϵ
//��ȡ�����ģ�͹�ϵ
class _RDP_REALDB_DLL_PORT CSgObjModel
{
public:
	CSgObjModel();
	~CSgObjModel();
	int	GetLinkObjTypes(int  ObjType, SET_INT &LinkObjTypeList);
	int	GetParentObjTypes(int  ObjType, int Relation, SET_INT &ParentObjTypeList);
	int	GetChildObjTypes(int  ObjType, int Relation, SET_INT &ChildObjTypeList);
	int	GetObjTypeRelation(int  PObjType, int CObjType, int &Relation, CSgString &PTypeField, CSgString &PIDField);

};

class _RDP_REALDB_DLL_PORT CSgRDBTblLock
{
	CSgRDBTable *m_pRTbl;
public:
	CSgRDBTblLock(CSgRDBTable *pRTbl);
	~CSgRDBTblLock();
	int OpenTable(char *pRTblName, unsigned char WriteLockFlag = 0, unsigned char ForceOpenFlag = 0,int WaitMs=0);
};
class _RDP_REALDB_DLL_PORT CSgRDBObject:public CSgRDBTable
{
	static CSG_OS_ThreadVar	m_DatLock;
	static SET_INT		m_CrtIdxObjTypeList;
	static SET_TWOINT	m_CrtIdxChildObjTypeList;
	int m_ObjType;
private:
	int CreateDyncIndexByObjType();
	int CreateDyncIndexByObjTypeRelation(CSgRDBObject &ChildObject,S_TWOINT &ObjRelation,CSgString &PTypeField,CSgString &PIDField);
	int GetObjConnectNode(CSgRDBObject &RTbl_Termal,SG_INT64 KeyID, int TermType, VECT_INT64 &ConNodeList);
	int GetObjMeasPtNo(CSgRDBObject &RTbl_MeasPt,int ObjType, SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType);
	int GetObjMeasPtVal(int ObjType, SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType, double &Val);
	int GetChildObjRcdNoBase(SG_INT64 KeyID, int ChildObjType, CSgRDBObject &ChildRDBObject, VECT_INT &ChildRcdNoList);
	int GetParentObjRcdNoBase(SG_INT64 KeyID, int ParentObjType, CSgRDBObject &ParentRDBObject,  SG_INT &ParentRcdNo, SG_INT64 &ParentKID);
public:
	CSgRDBObject(SG_UINT64 SchemaHandler = SG_DEFAULT_RUNNING_SCHEMAHANDLER);
	CSgRDBObject(int ObjType,SG_UINT64 SchemaHandler = SG_DEFAULT_RUNNING_SCHEMAHANDLER);
	~CSgRDBObject();
	virtual int TableCanUse();
	virtual int CloseTable();
	int OpenTableByObjType(int ObjType,unsigned char LockFlag = 0, unsigned char ForceOpenFlag = 0, int MaxWaitMs = 0);
	int GetObjTerminal(SG_INT64 KeyID, VECT_INT64 &TerminalList);
	int GetObjConnectNode(SG_INT64 KeyID, int TermType, VECT_INT64 &ConNodeList);
	int GetObjConnectObj(SG_INT64 KeyID, SG_INT TermType, VECT_INT64 &ObjList);
	int GetObjAnaRunVal(SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType,double *pVal);
	int GetObjDigRunVal(SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType, SG_INT *pVal);
	int GetObjMeasPtID(int ObjType, SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType, SG_INT64 &PtID);
	double GetObjAccRunVal(SG_INT64 KeyID, SG_INT TermType, SG_INT MeasType);
	int GetChildObjRcdNo(SG_INT64 KeyID, int ChildObjType, VECT_INT &ChildRcdNoList,VECT_INT64 *pChildKIDList=NULL);
	int GetParentObjRcdNo(SG_INT64 KeyID, int ParentObjType, SG_INT &ParentRcdNo, SG_INT64 *pParentKID=NULL);
	int GetChildObjInfo(SG_INT64 KeyID, int ChildObjType, char *pRetFields, CSgDataSet &DatSet);
	int GetParentObjInfo(SG_INT64 KeyID, int ParentObjType, char *pRetFields, CSgDataSet &DatSet);
	char *GetParentObjInfo(SG_INT64 KeyID, int ParentObjType,int *pRcdLen=NULL);

};
class CSgRDBSqlOperBase;
class _RDP_REALDB_DLL_PORT CSgRDBSqlOper
{
	CSgRDBSqlOperBase *m_pOper;
public:
	CSgRDBSqlOper(SG_UINT64 SchemaHander);
	~CSgRDBSqlOper();
	void SetUser(char *User,char *PassWd);
	//ִ��sql��䣬pRetDatSetΪ���ص���Ϣֵ MaxMemSize:����ڴ��С��Ϊ0: ��ʾ�����ƣ�MaxRcdNum���ѡ����ļ�¼���� 0:��ʾȫ��ѡ��
	//pRealRcdNum:���ط��������ļ�¼����,���ܱ�MaxRcdNum�� ��ʵ��ѡ���ĸ���<=MaxRcdNum
	int ExecSqlCmd(char *pSQLBuf, CSgDataSet *pRetDatSet, int MaxMemSize = 0, int MaxRcdNum = 0,
		int *pRealRcdNum = NULL, char *pTblName = NULL, int *pCanExecFlag = NULL);
};
#endif