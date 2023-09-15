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

	//ds为ds.ini文件中配置的数据源名称
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
	//用绑定方式插入记录,如果pRowList==NULL ,则插入所有记录，否则插入pRowList中指定行号的记录
	virtual SG_BOOL InsertRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL,int Sync2PDB = false)=0;
	//用 Sql语句的方式插入记录,如果pRowList==NULL ,则插入所有记录，否则插入pRowList中指定行号的记录
	virtual SG_BOOL	InsertRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//用绑定方式修改记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录,实际影响的记录个数
	virtual SG_BOOL UpdateRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	//用 Sql语句的方式修改记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录
	virtual SG_BOOL	UpdateRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//删除记录,如果pRowList==NULL ,则删除所有记录，否则删除pRowList中指定行号的记录
	virtual SG_BOOL DeleteRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	virtual SG_BOOL DeleteRecorder_SQL(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//用绑定方式Merge记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录,实际影响的记录个数
	virtual SG_BOOL MergeRecorder(CSgDataSet *pDataSet,VECT_INT *pRowList=NULL,void *psvc=0,int *pEffectRows=NULL, int Sync2PDB = false)=0;

	//执行sql语句
	virtual SG_BOOL	Exec(CSgString &SQLWord,void* pSvc=0,unsigned char ExecOnce=false,int *pEffectRows=NULL, int Sync2PDB = false)=0;
#ifndef SG_MINIBOX_PLAT
	virtual SG_BOOL	Exec(CSgString &SQLWord,CSgDataSet &ParaDatSet,void* pSvc=0,unsigned char ExecOnce=false,int *pEffectRows=NULL, int Sync2PDB = false)=0;
	virtual SG_BOOL ReadRecorder(CSgString &SQLWord,CSgDataSet &ParaDatSet,CSgDataSet *pDataSet,void *psvc=0,
		FUNC_DBREAD_RESPONSE *pCallFunc=NULL,void *pCallInfo=NULL)=0;
#endif
	virtual void* StartDBTrans()=0;
	virtual SG_BOOL	DBCommit(void* psvchp)=0;
	virtual SG_BOOL DBRollBack(void* psvchp)=0;
	// --- 创建数据库中的表
	virtual SG_BOOL	CreateTable(CSgDataSet* pDataSet,void*psvc=NULL)=0;
	// --- 删除数据库中的表
	virtual SG_BOOL	DropTable(CSgString &TblName)=0;
	//生成执行SQL文件的命令行
	virtual SG_BOOL CreateExeSQLFileCmd(char *pDBPath,char *pSQLFile,char *pLogFile,CSgString &ExeCmdLine)=0;
	//获取数据库中所有数据表信息
	virtual SG_BOOL ReadDBTables(char *DBName,CSgDataSet *pTableNames)=0;
	//
	virtual SG_BOOL ReadTableInfo(CSgString &TblName,CSgDataSet *pDataSet)=0;
public:
	virtual SG_STRING GetSpatialOwner()=0;
	virtual SG_BOOL CalGeoBuffer(CSgPoint* pPoints, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLine, void* psvchp = NULL)=0;
	virtual SG_BOOL CalGeoBuffer(CSgLine* pLine, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLine, void* psvchp = NULL)=0;
	virtual SG_BOOL Overlay(CSgLine* pLine1,      CSgLine* pLine2,        CSgLine& remain1,        CSgLine& remain2, 
		SG_LONG& common_nums, CSgLine*& pCommonLines, void* psvchp = NULL)=0;
	//上传文件，filename，上传本地文件的全路径文件名，saveName数据库存储的名字
	virtual SG_BOOL StoreFile(CSgString &fileName, const char*  saveName = "", const char*  contentType = "", const char*  dbName = "",void* psvchp = NULL)=0;
	//上传文件
	virtual SG_BOOL StoreFile(char* data,size_t length,CSgString &saveName, const char*  contentType = "", const char*  dbName = "",void* psvchp = NULL)=0;
	//删除文件
	virtual SG_BOOL RemoveFile(CSgString& fileName, const char*  dbName = "",void* psvchp = NULL)=0;
	//获得数据库存储的文件信息，fileName：数据库存储的文件名
	virtual SG_BOOL GetFileInfo(CSgString &fileName,S_NoSqlFileInfo &fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//给定存储文件名
	virtual SG_BOOL GetFile(CSgString &fileName,CSgString &saveFilename,S_NoSqlFileInfo&fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//查询文件，返回一个文件
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgString &saveFilename,S_NoSqlFileInfo&fileInfo, const char*  dbName = "",void* psvchp = NULL)=0;
	//查询文件，返回文件名列表
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgStringArray &fileArray, const char*  dbName = "",void* psvchp = NULL)=0;
	//判断是否具有暂停触发器的功能
	virtual SG_BOOL CanDisableTrigger()
	{
		return false;
	};
	//使触发器暂停
	virtual SG_BOOL SetTriggerDisable(void *pSvc,SG_BOOL DisableFlag)
	{
		return false;
	};
public:
	//获得插入sql语句
	virtual SG_STRING 	GetLastSqlWord()=0;
	virtual SG_STRING 	GetErrorInfo()=0;
	//
};

#endif