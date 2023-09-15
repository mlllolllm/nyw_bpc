#ifndef _DB_BASE_SESSION_HHHH_
#define _DB_BASE_SESSION_HHHH_

#include "csgdataset.h"
#include "osbase.h"
#if defined( SG_DBOPER_EXPORTS )
#   define _GAP_DBOPERL_EXPORT ACE_Proper_Export_Flag
#else
#   define _GAP_DBOPERL_EXPORT
#endif
typedef SG_INT (FUNC_DBREAD_RESPONSE)(CSgDataSet *pDatSet,void *pCallInfo,SG_BOOL RetVal,SG_BOOL FinishFlag);

//每一个动态库，在该函数中完成对数据库进行的必要的初始化工作
//void *CreateDBObj();
//释放时，完成相应的资源的释放
//int FreeDBObj(void *pObj);
//每一个数据库连接的动态状态
#define SG_MAX_SEND_BUFFER	32768
#define SG_MAX_SEND_BUFFER_SIZE 102400000
typedef struct S_DBSESSION_RUNSTATE
{
	SG_BOOL			LockFlag;
	SG_BOOL			IsConnectFlag;
	SG_BOOL			StartTransFlag;
	SG_LONG			CreateTime; //create timestamp
	SG_LONG			LastUseTime;; //last use timestamp
	CSgString		LastSQL; //最后的sql语句或dataset
	CSgString		LastError;	//最后的错误信息
	S_DBSESSION_RUNSTATE()
	{
		Reset();
	};
	void Reset()
	{
		LockFlag=false;
		IsConnectFlag=false;
		CreateTime=0;
		LastUseTime=0;
		LastSQL="";
		LastError="";
		StartTransFlag=false;
	};
}S_DBSESSION_RUNSTATE;
class _GAP_DBOPERL_EXPORT CDBBaseOperation
{
public:
	virtual void   OutputFileLog(SG_CHAR* szText)=0;
	virtual SG_BOOL CutStringFromTo(SG_CHAR* source,SG_CHAR* from, SG_CHAR* to,SG_CHAR* dest)=0;
	virtual SG_BOOL SetTablePK(char*owner,char*tablename,CSgStringArray&pk)=0;
	virtual SG_BOOL GetTablePK(char*owner,char*tablename,CSgStringArray&pk)=0;
	//设置表是否有几何字段
	virtual void	SetTableShape(char*tablename,SG_INT bHasShapeFalg)=0;
	//获取该表是否具有几何字段
	virtual SG_INT GetTableHasShape(char*tablename)=0;
	virtual SG_INT	GetReadBufferNums() 
	{
		return SG_MAX_ATTRIBTABLE_BUFFER;
	};
	virtual SG_INT	NotifyDBChange(SG_INT DBOper,CSgDataSet &DatSet)=0;
};
typedef struct SG_DBLINKBASEINFO
{
	CSgStringArray			DsInfoArray;
	CSgString				SpatialOwner;	
	SG_BOOL					UseSpatialFlag;
	SG_BOOL					SpatialUseIdx;	//是否使用空间索引
	SG_BOOL					ReConnectFlag;
	SG_BOOL					UseNotifyFlag;
	SG_DOUBLE				SpatialTolerance;
	SG_DBLINKBASEINFO()
	{
		Init();
	};
	void Init()
	{
		UseSpatialFlag=false;
		UseNotifyFlag=false;
		ReConnectFlag=true;
		SpatialOwner="";
		SpatialUseIdx=false;
		SpatialTolerance=0.5;
		DsInfoArray.RemoveAll();
	};
	void operator = (SG_DBLINKBASEINFO &InObj)
	{
		DsInfoArray.RemoveAll();
		for(int i=0;i<InObj.DsInfoArray.GetSize();i++)
			DsInfoArray.Add(InObj.DsInfoArray.Get(i)); 
		ReConnectFlag=InObj.ReConnectFlag;
		UseSpatialFlag=InObj.UseSpatialFlag;
		SpatialOwner=InObj.SpatialOwner;
		SpatialUseIdx=InObj.SpatialUseIdx;
		SpatialTolerance=InObj.SpatialTolerance;
		UseNotifyFlag=InObj.UseNotifyFlag;
	};
}SG_DBLINKBASEINFO;
typedef struct S_NoSqlFileInfo
{
	CSgString		FileName;
	CSgString		FileMD5;
	CSgString		ContentType;
	int				ContentLength;
	SG_Date			UpLoadDate;
	S_NoSqlFileInfo()
	{
		FileName="";
		FileMD5="";
		ContentType="";
		ContentLength = 0;
	}
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1)
	{
		FileName.Serialize(ar);
		FileMD5.Serialize(ar);
		ContentType.Serialize(ar);
		UpLoadDate.Serialize(ar);
		if(ar.IsLoading())
			ar >> ContentLength;
		else
			ar << ContentLength;
		return true;
	};
	virtual int buf_size()
	{
		return FileName.buf_size()+FileMD5.buf_size()+ContentType.buf_size()+sizeof(UpLoadDate)+sizeof(ContentLength);
	};
} S_NoSqlFileInfo;

class  CDBBaseSession
{
protected:
	CDBBaseOperation		*m_pDBOperation;
	SG_DBLINKBASEINFO		m_DBLinkBaseInfo;
	SG_INT					m_DBType;
	S_DBSESSION_RUNSTATE	m_SessionRunInfo;
public:

	CDBBaseSession()
	{
		m_pDBOperation=NULL;
		m_DBLinkBaseInfo.Init();
	};
	~CDBBaseSession()
	{
	};
public:
	SG_BOOL InitLinkInfo(CDBBaseOperation *pDBOperation,SG_DBLINKBASEINFO &LinkBaseInfo)
	{
		m_pDBOperation=pDBOperation;
		m_DBLinkBaseInfo=LinkBaseInfo;
		return true;
	};
	S_DBSESSION_RUNSTATE &GetSessionRunState()
	{
		m_SessionRunInfo.LastError="";
		return m_SessionRunInfo;
	};
	void   *StartDBTrans()
	{
		m_SessionRunInfo.StartTransFlag=true;
		return StartTrans();
	};
	SG_BOOL	DBCommit()
	{
		m_SessionRunInfo.StartTransFlag=false;
		return Commit();
	};
	SG_BOOL DBRollBack()
	{
		m_SessionRunInfo.StartTransFlag=false;
		return RollBack();
	};
	virtual SG_BOOL ConnectDB()=0;
	//关闭数据库连接
	virtual SG_BOOL DisConnect()=0;
	virtual SG_BOOL ReadSysDate(SG_UINT *pDBTime)
	{
		if(pDBTime==NULL)
			return false;
		CSG_OS_Time ostime;
		ostime.GetNow(pDBTime);
		return true;
	};
	virtual  SG_BOOL CanUseSpatial()
	{
		return false;
	};
	//判断是否具有暂停触发器的功能
	virtual SG_BOOL CanDisableTrigger()
	{
		m_SessionRunInfo.LastError.Format("该数据库不支持暂停触发器操作！");
		return false;
	};
	//使触发器暂停
	virtual SG_BOOL SetTriggerDisable(SG_BOOL DisableFlag)
	{
		return false;
	};
	virtual SG_BOOL GetIDVal(CSgString &SequenceName,SG_INT Cnt,CSgObjects &ObjIDS)
	{
		m_SessionRunInfo.LastError.Format("该数据库不支持获取Sequence操作！");
		return false;
	};
	virtual SG_BOOL ReadTableInfo(CSgString &TblName,CSgDataSet *pDataSet)
	{
		CSgString CmdBuf;
		CmdBuf.Format("select * from %s where 0=12",TblName.GetSafeBuffer());
		return ReadRecorder(CmdBuf,pDataSet);
	};
	//插入记录后，是否还会有字段信息返回填入数据集
	virtual SG_BOOL InsertAfterRetFieldVal()
	{
		return false;
	};
public:
	// --- 删除数据库中的表
	virtual SG_BOOL	DropTable(CSgString &TblName)
	{
		CSgString CmdBuf;
		CmdBuf.Format("drop table %s", TblName.GetSafeBuffer());
		return Exec(CmdBuf);
	};
	virtual char *GetLastError()
	{
		return m_SessionRunInfo.LastError.GetSafeBuffer();
	};
public:
	void OutputFileLog(SG_CHAR* szText)
	{
		if (m_pDBOperation)
			m_pDBOperation->OutputFileLog(szText);
	};
	SG_BOOL CutStringFromTo(SG_CHAR* source, SG_CHAR* from, SG_CHAR* to, SG_CHAR* dest)
	{
		if (m_pDBOperation)
			return m_pDBOperation->CutStringFromTo(source, from, to, dest);
		return false;
	};
	SG_BOOL SetTablePK(char*owner, char*tablename, CSgStringArray&pk)
	{
		if (m_pDBOperation)
			return m_pDBOperation->SetTablePK(owner, tablename, pk);
		return false;
	};
	SG_BOOL GetTablePK(char*owner, char*tablename, CSgStringArray&pk)
	{
		if (m_pDBOperation)
			return m_pDBOperation->GetTablePK(owner, tablename, pk);
		return false;
	};
	//设置表是否有几何字段
	void	SetTableShape(char*tablename, SG_INT bHasShapeFalg)
	{
		if (m_pDBOperation)
			m_pDBOperation->SetTableShape(tablename, bHasShapeFalg);
	};

	//获取该表是否具有几何字段
	SG_INT GetTableHasShape(char*tablename)
	{
		if (m_pDBOperation)
			return m_pDBOperation->GetTableHasShape(tablename);
		return 0;
	};
	CSgStringArray* GetDsStringArray()
	{
		return &m_DBLinkBaseInfo.DsInfoArray;
	}

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//			关系型数据库所必须实现的函数    开始
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
public:
	virtual SG_BOOL ReadRecorder(CSgString &SQLWord, CSgDataSet *pDataSet, FUNC_DBREAD_RESPONSE *pCallFunc = NULL, void *pCallInfo = NULL)
	{
		return false;
	};
#ifndef SG_MINIBOX_PLAT
	virtual SG_BOOL ReadRecorder(CSgString &SQLWord,CSgDataSet &ParaDataSet,CSgDataSet *pDataSet,FUNC_DBREAD_RESPONSE *pCallFunc = NULL,void *pCallInfo = NULL)
	{
		return false;
	};
#endif
	virtual SG_BOOL ReadRecorder(CSgGeoDataSet* pGeoDataSet, const char* pTableName, const char* pFieldsName,
		const char* pWhereClause = NULL, CSgLine* pSgLine = NULL, SG_INT relation = 10, SG_CHAR*pszRelation = NULL,
		SG_CHAR*pszAndOr = " OR ", FUNC_DBREAD_RESPONSE *pCallFunc = NULL, void *pCallInfo = NULL)
	{
		return false;
	};
	//用绑定方式插入记录,如果pRowList==NULL ,则插入所有记录，否则插入pRowList中指定行号的记录
	virtual SG_BOOL InsertRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//用 Sql语句的方式插入记录,如果pRowList==NULL ,则插入所有记录，否则插入pRowList中指定行号的记录
	virtual SG_BOOL	InsertRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//用绑定方式修改记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录
	virtual SG_BOOL UpdateRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//用 Sql语句的方式修改记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录
	virtual SG_BOOL	UpdateRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};

	//删除记录,如果pRowList==NULL ,则删除所有记录，否则删除pRowList中指定行号的记录
	virtual SG_BOOL DeleteRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	virtual SG_BOOL DeleteRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};

	//用绑定方式合并记录,如果pRowList==NULL ,则修改所有记录，否则修改pRowList中指定行号的记录
	virtual SG_BOOL MergeRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//执行sql语句
	virtual SG_BOOL	Exec(CSgString &SQLWord, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
#ifndef SG_MINIBOX_PLAT
	virtual SG_BOOL	Exec(CSgString &SQLWord,CSgDataSet &ParaDatSet,int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
#endif
	//获取数据库中所有数据表信息
	virtual SG_BOOL ReadDBTables(char *DBName, CSgDataSet *pTableNames)
	{
		return false;
	};
	//生成执行SQL文件的命令行
	virtual	SG_BOOL CreateExeSQLFileCmd(char *pDBPath,char *pSQLFile,char *pLogFile,CSgString &ExeCmdLine)
	{
		return false;
	};

	// --- 创建数据库中的表
	virtual SG_BOOL	CreateTable(CSgDataSet* pDataSet)
	{
		return false;
	};
protected:
	virtual void* StartTrans()
	{
		return NULL;
	};
	virtual SG_BOOL	Commit()
	{
		return false;
	};
	virtual SG_BOOL RollBack()
	{
		return false;
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//			关系型数据库所必须实现的函数       结束
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//			 空间数据库所必须实现的函数    开始
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
public:
	virtual SG_BOOL CalGeoBuffer(CSgPoint* pPoints, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLi)
	{
		return false;
	};
	//针对多个PART的线计算
	virtual SG_BOOL CalGeoBuffer(CSgLine* pLine,SG_SHORT nFeatureType,SG_DOUBLE dWidth, CSgLine& rLine)
	{
		return false;
	}
	virtual SG_BOOL Overlay(CSgLine* pLine1,CSgLine* pLine2,CSgLine& remain1,CSgLine& remain2, 
		SG_LONG& common_nums, CSgLine*& pCommonLines)
	{
		return false;
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//			空间数据库所必须实现的函数       结束
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//			 NoSQL数据库所必须实现的函数    开始
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//上传文件，filename，上传本地文件的全路径文件名，saveName数据库存储的名字
	virtual SG_BOOL StoreFile(CSgString &SrvFileName,const char* LocalFileName = "",const char* contentType = "",const char* dbName="")
	{
		return false;
	};
	//上传文件
	virtual SG_BOOL StoreFile(char* data,size_t length,CSgString &SrvFileName, const char*  contentType = "", const char*  dbName="")
	{
		return false;
	};
	//删除文件
	virtual SG_BOOL RemoveFile(CSgString& SrvFileName, const char*  dbName="")
	{
		return false;
	};
	//获得数据库存储的文件信息，fileName：数据库存储的文件名
	virtual SG_BOOL GetFileInfo(CSgString &SrvFileName,S_NoSqlFileInfo &fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//获得文件，返回文件的大小及文件句柄
	//virtual SG_BOOL GetFile(CSgString fileName, ISF_File_Handler &fileHandler, S_NoSqlFileInfo&fileInfo,CSgString dbName ="");
	//给定存储文件名
	virtual SG_BOOL GetFile(CSgString &SrvFileName,CSgString &LocalFileName,S_NoSqlFileInfo&fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//查询文件，返回一个文件
//	virtual SG_BOOL QueryFile(CSgString queryJson, ISF_File_Handler &fileHandler, S_NoSqlFileInfo&fileInfo, CSgString dbName = "");
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgString &LocalFileName,S_NoSqlFileInfo&fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//查询文件，返回文件名列表
	virtual SG_BOOL QueryFile(CSgString &queryJson, CSgStringArray &fileArray, const char*  dbName = "")
	{
		return false;
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//			NoSQL数据库所必须实现的函数       结束
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	private:
};
#endif