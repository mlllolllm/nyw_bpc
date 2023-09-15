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

//ÿһ����̬�⣬�ڸú�������ɶ����ݿ���еı�Ҫ�ĳ�ʼ������
//void *CreateDBObj();
//�ͷ�ʱ�������Ӧ����Դ���ͷ�
//int FreeDBObj(void *pObj);
//ÿһ�����ݿ����ӵĶ�̬״̬
#define SG_MAX_SEND_BUFFER	32768
#define SG_MAX_SEND_BUFFER_SIZE 102400000
typedef struct S_DBSESSION_RUNSTATE
{
	SG_BOOL			LockFlag;
	SG_BOOL			IsConnectFlag;
	SG_BOOL			StartTransFlag;
	SG_LONG			CreateTime; //create timestamp
	SG_LONG			LastUseTime;; //last use timestamp
	CSgString		LastSQL; //����sql����dataset
	CSgString		LastError;	//���Ĵ�����Ϣ
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
	//���ñ��Ƿ��м����ֶ�
	virtual void	SetTableShape(char*tablename,SG_INT bHasShapeFalg)=0;
	//��ȡ�ñ��Ƿ���м����ֶ�
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
	SG_BOOL					SpatialUseIdx;	//�Ƿ�ʹ�ÿռ�����
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
	//�ر����ݿ�����
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
	//�ж��Ƿ������ͣ�������Ĺ���
	virtual SG_BOOL CanDisableTrigger()
	{
		m_SessionRunInfo.LastError.Format("�����ݿⲻ֧����ͣ������������");
		return false;
	};
	//ʹ��������ͣ
	virtual SG_BOOL SetTriggerDisable(SG_BOOL DisableFlag)
	{
		return false;
	};
	virtual SG_BOOL GetIDVal(CSgString &SequenceName,SG_INT Cnt,CSgObjects &ObjIDS)
	{
		m_SessionRunInfo.LastError.Format("�����ݿⲻ֧�ֻ�ȡSequence������");
		return false;
	};
	virtual SG_BOOL ReadTableInfo(CSgString &TblName,CSgDataSet *pDataSet)
	{
		CSgString CmdBuf;
		CmdBuf.Format("select * from %s where 0=12",TblName.GetSafeBuffer());
		return ReadRecorder(CmdBuf,pDataSet);
	};
	//�����¼���Ƿ񻹻����ֶ���Ϣ�����������ݼ�
	virtual SG_BOOL InsertAfterRetFieldVal()
	{
		return false;
	};
public:
	// --- ɾ�����ݿ��еı�
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
	//���ñ��Ƿ��м����ֶ�
	void	SetTableShape(char*tablename, SG_INT bHasShapeFalg)
	{
		if (m_pDBOperation)
			m_pDBOperation->SetTableShape(tablename, bHasShapeFalg);
	};

	//��ȡ�ñ��Ƿ���м����ֶ�
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
	//			��ϵ�����ݿ�������ʵ�ֵĺ���    ��ʼ
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
	//�ð󶨷�ʽ�����¼,���pRowList==NULL ,��������м�¼���������pRowList��ָ���кŵļ�¼
	virtual SG_BOOL InsertRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//�� Sql���ķ�ʽ�����¼,���pRowList==NULL ,��������м�¼���������pRowList��ָ���кŵļ�¼
	virtual SG_BOOL	InsertRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//�ð󶨷�ʽ�޸ļ�¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼
	virtual SG_BOOL UpdateRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//�� Sql���ķ�ʽ�޸ļ�¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼
	virtual SG_BOOL	UpdateRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};

	//ɾ����¼,���pRowList==NULL ,��ɾ�����м�¼������ɾ��pRowList��ָ���кŵļ�¼
	virtual SG_BOOL DeleteRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	virtual SG_BOOL DeleteRecorder_SQL(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};

	//�ð󶨷�ʽ�ϲ���¼,���pRowList==NULL ,���޸����м�¼�������޸�pRowList��ָ���кŵļ�¼
	virtual SG_BOOL MergeRecorder(CSgDataSet *pDataSet, VECT_INT *pRowList = NULL, int *pEffectRows = NULL, int Sync2PDB = false)
	{
		return false;
	};
	//ִ��sql���
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
	//��ȡ���ݿ����������ݱ���Ϣ
	virtual SG_BOOL ReadDBTables(char *DBName, CSgDataSet *pTableNames)
	{
		return false;
	};
	//����ִ��SQL�ļ���������
	virtual	SG_BOOL CreateExeSQLFileCmd(char *pDBPath,char *pSQLFile,char *pLogFile,CSgString &ExeCmdLine)
	{
		return false;
	};

	// --- �������ݿ��еı�
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
	//			��ϵ�����ݿ�������ʵ�ֵĺ���       ����
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//			 �ռ����ݿ�������ʵ�ֵĺ���    ��ʼ
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
public:
	virtual SG_BOOL CalGeoBuffer(CSgPoint* pPoints, SG_SHORT nFeatureType, SG_DOUBLE dWidth, CSgLine& rLi)
	{
		return false;
	};
	//��Զ��PART���߼���
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
	//			�ռ����ݿ�������ʵ�ֵĺ���       ����
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//			 NoSQL���ݿ�������ʵ�ֵĺ���    ��ʼ
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//�ϴ��ļ���filename���ϴ������ļ���ȫ·���ļ�����saveName���ݿ�洢������
	virtual SG_BOOL StoreFile(CSgString &SrvFileName,const char* LocalFileName = "",const char* contentType = "",const char* dbName="")
	{
		return false;
	};
	//�ϴ��ļ�
	virtual SG_BOOL StoreFile(char* data,size_t length,CSgString &SrvFileName, const char*  contentType = "", const char*  dbName="")
	{
		return false;
	};
	//ɾ���ļ�
	virtual SG_BOOL RemoveFile(CSgString& SrvFileName, const char*  dbName="")
	{
		return false;
	};
	//������ݿ�洢���ļ���Ϣ��fileName�����ݿ�洢���ļ���
	virtual SG_BOOL GetFileInfo(CSgString &SrvFileName,S_NoSqlFileInfo &fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//����ļ��������ļ��Ĵ�С���ļ����
	//virtual SG_BOOL GetFile(CSgString fileName, ISF_File_Handler &fileHandler, S_NoSqlFileInfo&fileInfo,CSgString dbName ="");
	//�����洢�ļ���
	virtual SG_BOOL GetFile(CSgString &SrvFileName,CSgString &LocalFileName,S_NoSqlFileInfo&fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//��ѯ�ļ�������һ���ļ�
//	virtual SG_BOOL QueryFile(CSgString queryJson, ISF_File_Handler &fileHandler, S_NoSqlFileInfo&fileInfo, CSgString dbName = "");
	virtual SG_BOOL QueryFile(CSgString &queryJson,CSgString &LocalFileName,S_NoSqlFileInfo&fileInfo, const char*  dbName = "")
	{
		return false;
	};
	//��ѯ�ļ��������ļ����б�
	virtual SG_BOOL QueryFile(CSgString &queryJson, CSgStringArray &fileArray, const char*  dbName = "")
	{
		return false;
	};
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//			NoSQL���ݿ�������ʵ�ֵĺ���       ����
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	private:
};
#endif