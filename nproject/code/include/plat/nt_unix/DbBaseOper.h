#ifndef _CLOUD_DBBASEOPER_HHHH_
#define _CLOUD_DBBASEOPER_HHHH_
#include "sgconst.h"
#include "csgdataset.h"
#include "usefulfunc.h"
#include "DbBaseSession.h"
class  CDBOperBaseSession
{
public:

	CDBOperBaseSession()
	{
	};
	~CDBOperBaseSession()
	{
	};

	//dsΪds.ini�ļ������õ�����Դ����
	virtual SG_BOOL ConnectDB(SG_STRING ds,SG_SHORT GeneralSessionNums,SG_SHORT MaxSessionNums,SG_BOOL ReConnectFlag=false)=0;
#ifndef SG_MINIBOX_PLAT
	virtual SG_BOOL ConnectDirectDB(int DBType, CSgString &DsInfo, SG_SHORT GeneralSessionNums, SG_SHORT MaxSessionNums, SG_BOOL ReConnectFlag = false)=0;
#endif
	virtual SG_BOOL DisConnect()=0;
public:

	virtual SG_BOOL ReadRecorder(CSgString &SQLWord,CSgDataSet *pDataSet,void *psvc=0,
		FUNC_DBREAD_RESPONSE *pCallFunc=NULL,void *pCallInfo=NULL)=0;
	virtual SG_BOOL ReadRecorder(CSgString &SQLWord,CSgDataSet *pDataSet,CSgLine* pSgLine, SG_INT relation = 10, 
		SG_CHAR*pszRelation=NULL,SG_CHAR*pszAndOr=" OR ",void *psvc=0,FUNC_DBREAD_RESPONSE *pCallFunc=NULL,void *pCallInfo=NULL)=0;
	virtual SG_BOOL ReadRecorder(CSgGeoDataSet* pGeoDataSet,const char* pTableName,  const char* pFieldsName, 
		const char* pWhereClause = NULL, CSgLine* pSgLine = NULL, SG_INT relation = 10, 
		void* psvchp = NULL,SG_CHAR*pszRelation=NULL,SG_CHAR*pszAndOr=" OR ",
		FUNC_DBREAD_RESPONSE *pCallFunc=NULL,void *pCallInfo=NULL)=0;
	virtual SG_BOOL ReadSysDate(SG_UINT *pDBTime)=0;
	virtual SG_BOOL GetIDVal(CSgString &SequenceName,SG_INT Cnt,CSgObjects &ObjIDS)=0;
	//�ð󶨷�ʽ�����¼,���pRowList==NULL ,��������м�¼���������pRowList��ָ���кŵļ�¼
	virtual SG_BOOL InsertRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL,int Sync2PDB = false)=0;
	//�� Sql���ķ�ʽ�����¼,���pRowList==NULL ,��������м�¼���������pRowList��ָ���кŵļ�¼
	virtual SG_BOOL	InsertRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//�ð󶨷�ʽ�޸ļ�¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼,ʵ��Ӱ��ļ�¼����
	virtual SG_BOOL UpdateRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	//�� Sql���ķ�ʽ�޸ļ�¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼
	virtual SG_BOOL	UpdateRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//ɾ����¼,���pRowList==NULL ,��ɾ�����м�¼������ɾ��pRowList��ָ���кŵļ�¼
	virtual SG_BOOL DeleteRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	virtual SG_BOOL DeleteRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//�ð󶨷�ʽMerge��¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼,ʵ��Ӱ��ļ�¼����
	virtual SG_BOOL MergeRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//ִ��sql���
	virtual SG_BOOL	Exec(CSgString &SQLWord,void* pSvc=0,unsigned char ExecOnce=false,int *pEffectRows=NULL, int Sync2PDB = false)=0;
#ifndef SG_MINIBOX_PLAT
	virtual SG_BOOL	Exec(CSgString &SQLWord,CSgDataSet &ParaDatSet,void* pSvc=0,unsigned char ExecOnce=false,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	virtual SG_BOOL ReadRecorder(CSgString &SQLWord,CSgDataSet &ParaDatSet,CSgDataSet *pDataSet,void *psvc=0,
		FUNC_DBREAD_RESPONSE *pCallFunc=NULL,void *pCallInfo=NULL)=0;
#endif
	virtual void* StartDBTrans()=0;
	virtual SG_BOOL	DBCommit(void* psvchp)=0;
	virtual SG_BOOL DBRollBack(void* psvchp)=0;
	// --- �������ݿ��еı�
	virtual SG_BOOL	CreateTable(CSgDataSet* pDataSet,void*psvc=NULL)=0;
	// --- ɾ�����ݿ��еı�
	virtual SG_BOOL	DropTable(CSgString &TblName)=0;
	//����ִ��SQL�ļ���������
	virtual SG_BOOL CreateExeSQLFileCmd(char *pDBPath,char *pSQLFile,char *pLogFile,CSgString &ExeCmdLine)=0;
	//��ȡ���ݿ����������ݱ���Ϣ
	virtual SG_BOOL ReadDBTables(char *DBName,CSgDataSet *pTableNames)=0;
	//
	virtual SG_BOOL ReadTableInfo(CSgString &TblName,CSgDataSet *pDataSet)=0;
public:
	virtual SG_STRING GetSpatialOwner()=0;
	virtual SG_BOOL CalGeoBuffer(CSgPoint* pPoints, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLine, void* psvchp = NULL)=0;
	virtual SG_BOOL CalGeoBuffer(CSgLine* pLine, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLine, void* psvchp = NULL)=0;
	virtual SG_BOOL Overlay(CSgLine* pLine1,      CSgLine* pLine2,        CSgLine& remain1,        CSgLine& remain2, 
		SG_LONG& common_nums, CSgLine*& pCommonLines, void* psvchp = NULL)=0;
	//�ϴ��ļ���filename���ϴ������ļ���ȫ·���ļ�����saveName���ݿ�洢������
	virtual SG_BOOL StoreFile(CSgString &fileName, const char*  saveName = "", const char*  contentType = "", const char*  dbName = "",void* psvchp = NULL)=0;
	//�ϴ��ļ�
	virtual SG_BOOL StoreFile(char* data,size_t length,CSgString &saveName, const char*  contentType = "", const char*  dbName = "",void* psvchp = NULL)=0;
	//ɾ���ļ�
	virtual SG_BOOL RemoveFile(CSgString& fileName, const char*  dbName = "",void* psvchp = NULL)=0;
	//������ݿ�洢���ļ���Ϣ��fileName�����ݿ�洢���ļ���
	virtual SG_BOOL GetFileInfo(CSgString &fileName,S_NoSqlFileInfo &fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//�����洢�ļ���
	virtual SG_BOOL GetFile(CSgString &fileName,CSgString &saveFilename,S_NoSqlFileInfo&fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//��ѯ�ļ�������һ���ļ�
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgString &saveFilename,S_NoSqlFileInfo&fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//��ѯ�ļ��������ļ����б�
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgStringArray &fileArray, const char*  dbName = "",void* psvchp = NULL)=0;
	//�ж��Ƿ������ͣ�������Ĺ���
	virtual SG_BOOL CanDisableTrigger()
	{
		return false;
	};
	//ʹ��������ͣ
	virtual SG_BOOL SetTriggerDisable(void *pSvc,SG_BOOL DisableFlag)
	{
		return false;
	};
public:
	//��ò���sql���
	virtual SG_STRING 	GetLastSqlWord()=0;
	virtual SG_STRING 	GetErrorInfo()=0;
	//
};

#endif