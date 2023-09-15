#ifndef __HH_DPPSRV_CLIENT_H__
#define __HH_DPPSRV_CLIENT_H__
#include "ACE_Includes.h"
#include "csgdataset.h"
#include "DBCommand.h"
#include "DPS_Command.h"
#include "GGisCommand.h"
#include "osbase.h"
#include "dpp_veroper.h"
#include "sys_moduledef.h"
#ifdef _USE_DPPCLIENT_SRC_
#   define _GAP_C_PROCSRVDLL_PORT
#else
#ifdef  GAP_DPPSRVDLL_DLL 
#   define _GAP_C_PROCSRVDLL_PORT ACE_Proper_Export_Flag
#else
#   define _GAP_C_PROCSRVDLL_PORT ACE_Proper_Import_Flag
#endif
#endif
//#define _GAP_C_PROCSRVDLL_PORT __attribute__ ((visibility("default")))
#define SGF_SQL_PARA		"PARA"
#define SGF_SQL_DBNO		"DBNO"
//class _GAP_C_PROCSRVDLL_PORT CGAP_SrvClientBase
class _GAP_C_PROCSRVDLL_PORT CGAP_SrvClientBase
{
protected:
	unsigned char       m_ConnectFlag;
	SG_INT		m_DefaultPort;
	SG_BOOL		m_SrvIPFromFileFlag;
	CSgString	m_SrvIP;
	CSgString	m_UseIP;
	SG_UINT		m_ActiveTime;
	void 	*m_SrvConnectorPt;
	void	*m_StreamPt;

	virtual short int SendStopFrame();
private:
	short int ConnectSrvBase(SG_BOOL CheckFlag=true);

public:
	CSgString m_ErrInfo;
	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ExeCmdRequestOnce(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response,int TimeOutSecond=120,int DesFlag=0);
	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ExeCmdRequest(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response,int TimeOutSecond=120,int DesFlag=0);
	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ExeCmdRequestBase(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response,SG_BOOL &RepeatFlag, int ExeCnt, int TimeOutSecond, int DesFlag);

	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ExeCmdRequest_Row(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response,int TimeOutSecond=120, int DesFlag = 0);
	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ExeCmdRequest_RowBase(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response,SG_BOOL &RepeatFlag,int ExeCnt,int TimeOutSecond, int DesFlag);
	virtual int SendExeCmdAfter(void *pDat)
	{
		return true;
	};

public:
	CGAP_SrvClientBase(char *SrvName,int DefaultPort,char *srvip=NULL);
	CGAP_SrvClientBase();
	virtual ~CGAP_SrvClientBase();

	virtual short int ConnectSrv(SG_BOOL CheckFlag=true);
	virtual void DisConnectSrv();
	bool IsConnected() { return m_ConnectFlag>0; }

	char *GetLastErrInfo()
	{
		return m_ErrInfo.GetSafeBuffer();
	};
	SG_INT CheckSrvLinkState(SG_UINT NowTime=0);
	SG_INT TestSrvLinkState();
	SG_INT SetIPString(char *srvip);
	SG_INT GetIPString(CSgString &SrvIP);
	SG_INT GetUseIP(CSgString &UseIP)
	{
		UseIP=m_UseIP.GetSafeBuffer();
		if(m_UseIP.IsEmpty())
			return false;
		return true;
	};
	SG_INT SendExeCmd(SG_INT CmdType,NetCommandSendParaPrepare *pSendPara,NetCommandReceiveExplain *&pReciveDat,void *pDat,SG_BOOL &RepeatFlag,int TimeOutSecond=120);
	SG_INT SendExeCmd(SG_INT CmdType,NetCommandSendParaPrepare *pSendPara,NetCommandReceiveExplain *&pReciveDat,void *pDat,int TimeOutSecond=120);
	SG_INT SendExeCmd(SG_INT CmdType,ACE_Message_Block *pSendMB,ACE_Message_Block *&pRecvMB,int TimeOutSecond=120);

};
class _GAP_C_PROCSRVDLL_PORT CGAP_SrvClient
{
protected:
	CGAP_SrvClientBase *m_pClientBase;
	SG_BOOL				m_ClientNewFlag;
protected:
	void SetClientBase(CGAP_SrvClientBase *pClientBase);

	int GetFilePath(char *pFileName,char *pPath,char *pBaseFileName);
	int ClearPathFile(char *pPathName,char *pFileBaseName);
	int ReadLoadInfoIniFile(char *pTmpPath,char *pBaseFileName,MAP_INT_FILELOADINFO &LoadInfoArray,int &MaxFrameNo);
	int WriteLoadInfoIniFile(char *pTmpPath,char *pBaseFileName,MAP_INT_FILELOADINFO &LoadInfoArray);
	template <class REQUEST_T, class RESPONSE_T,class DATASET_T>
	int ProcCursorBefore(REQUEST_T &Request, RESPONSE_T &Response, int &UseCursorFlag, int &RetStartPos, int &RetMaxNum, DATASET_T *&pInRetDatSet);
	template <class REQUEST_T, class RESPONSE_T, class DATASET_T>
	int ProcCursorAfter(REQUEST_T &Request, RESPONSE_T &Response,int RetVal, int UseCursorFlag, int RetStartPos, int RetMaxNum, DATASET_T *pInRetDatSet);

public:
	CGAP_SrvClient(char *SrvIP,int Port,char *SrvName);
	CGAP_SrvClient(CGAP_SrvClientBase *pClientBase);
	~CGAP_SrvClient();
	virtual void DisConnectSrv();
	virtual short int ConnectSrv(SG_BOOL CheckFlag=true);
	SG_INT TestSrvLinkState();
	char *GetLastErrInfo();
	SG_INT SetIPString(char *srvip);
	SG_INT GetUseIP(CSgString &UseIP);
	CGAP_SrvClientBase *GetClientBase();
	int GetIPString(CSgString &SrvIP);
	int GetCursorDatSet(SG_UINT CursorID,int StartRow,int RetRowNum,CSgDataSet *pDatSet);
	int GetCursorDataSetRowNum(SG_UINT CursorID);
	int CloseCursor(SG_UINT CursorID);

};
class CDBOperBaseSession;
class CDB_SysModelInfo;
class _GAP_C_PROCSRVDLL_PORT CGAP_DBLocalOper
{
	SG_BOOL			m_InitFlag;
	VECT_VOIDPT		m_DBOperList;
	private:
	CDBOperBaseSession	*GetDBOperObj(SG_INT DBNo,SG_INT *pSNo=NULL);
	int RDB_BatchExec_OneStep(SG_INT Oper2PDB, SG_INT StepNo,SG_INT OperType,CSgDataSet *pOperDatSet,
				CDBOperBaseSession *pDBOper,void *pSvc,CSgString &OperInfo);
	template<class C_REQUEST,class C_RESPONSE,class CSGDATASET>
	int RDB_BaseReadRecorder(C_REQUEST &Request,C_RESPONSE &Response,CSGDATASET *pTempDat);
	template<class C_REQUEST,class C_RESPONSE,class CSGDATASET>
	int RDB_CompileBaseReadRecorder(C_REQUEST &Request,C_RESPONSE &Response,CSGDATASET *pTempDat);
	int RDB_BatchExec_OneStep(SG_INT Oper2PDB, SG_INT StepNo, SG_INT DBNo, SG_INT OperType, CSgLobDataSet *pOperDatSet,
		MAP_INT_TWOVOIDPT &DbOperList,CDB_SysModelInfo &DBModelOper, S_TWOINT &DatVerInfo, CSgString &RetInfo);
	int ClearTransOperEngine(MAP_INT_TWOVOIDPT &DbOperList, int OperType);
public:
	CGAP_DBLocalOper();
	~CGAP_DBLocalOper();

	int RDB_ReadRecorder(CDBCmd_ReadRecorder_Req &Request,CDBCmd_ReadRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertRecorder_Req &Request,CDBCmd_InsertRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateRecorder_Req &Request,CDBCmd_UpdateRecorder_Res &Response);
	int RDB_DeleteRecorder(CDBCmd_DeleteRecorder_Req &Request,CDBCmd_DeleteRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeRecorder_Req &Request,CDBCmd_MergeRecorder_Res &Response);

	int RDB_ReadRecorder(CDBCmd_ReadGeoRecorder_Req &Request,CDBCmd_ReadGeoRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertGeoRecorder_Req &Request,CDBCmd_InsertGeoRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateGeoRecorder_Req &Request,CDBCmd_UpdateGeoRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeGeoRecorder_Req &Request,CDBCmd_MergeGeoRecorder_Res &Response);
	int GetSpatialOwner(CSgString &Owner,SG_USHORT DBNo=DEFAULT_DBNO);

	int RDB_ReadLobRecorder(CDBCmd_ReadLobRecorder_Req &Request,CDBCmd_ReadLobRecorder_Res &Response);
	int RDB_InsertLobRecorder(CDBCmd_InsertLobRecorder_Req &Request,CDBCmd_InsertLobRecorder_Res &Response);
	int RDB_UpdateLobRecorder(CDBCmd_UpdateLobRecorder_Req &Request,CDBCmd_UpdateLobRecorder_Res &Response);
	int RDB_MergeLobRecorder(CDBCmd_MergeLobRecorder_Req &Request,CDBCmd_MergeLobRecorder_Res &Response);

	int RDB_ExecSQL(CDBCmd_ExecSQL_Req &Request,CDBCmd_ExecSQL_Res &Response);
	int RDB_ExecSQL(CDBCmd_ExecSQLNotTrigger_Req &Request,CDBCmd_ExecSQLNotTrigger_Res &Response);
	int RDB_BatchExec(CDBCmd_TransOper_Req &Request,CDBCmd_TransOper_Res &Response);
	int RDB_BatchExec(CDBCmd_MultiDBTransOper_Req &Request,CDBCmd_MultiDBTransOper_Res &Response);
	
	int RDB_BatchReadRecorder(CDBCmd_BatchReadRecorder_Req &Request,CDBCmd_BatchReadRecorder_Res &Response);

//	int GetIDVal(SG_UCHAR DBNo,const char *Name,int WorkSpace,int Cnt,int *pSeqVal);
	int RDB_ReadLobField(CDBCmd_ReadLobField_Req &Request,CDBCmd_ReadLobField_Res &Response);
	int RDB_WriteLobField(CDBCmd_WriteLobField_Req &Request,CDBCmd_WriteLobField_Res &Response);
	int RDB_GetSysDate(CDBCmd_GetSysDate_Req &Request,CDBCmd_GetSysDate_Res &Response);
	int RDB_GetIDVal(CDBCmd_GetIDVal_Req &Request,CDBCmd_GetIDVal_Res &Response);
	int RDB_GetIDVal(CDBCmd_GetIDVal_New_Req &Request,CDBCmd_GetIDVal_Res &Response);
	int RDB_GetDBType(SG_INT DBNo=DEFAULT_DBNO);
	int RDB_ReadTableInfo(CDBCmd_ReadTableInfo_Req &Request, CDBCmd_ReadTableInfo_Res &Response);
	int RDB_ReadRecorder(CDBCmd_CompileReadRecorder_Req &Request,CDBCmd_CompileReadRecorder_Res &Response);
	int RDB_ReadRecorder(CDBCmd_CompileReadLobRecorder_Req &Request,CDBCmd_CompileReadLobRecorder_Res &Response);
	int RDB_ExecSQL(CDBCmd_CompileExecSQL_Req &Request,CDBCmd_CompileExecSQL_Res &Response);

	int RDB_ReadRecorder(CDBCmd_ReadVerRecorder_Req &Request, CDBCmd_ReadVerRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertVerRecorder_Req &Request, CDBCmd_InsertVerRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateVerRecorder_Req &Request, CDBCmd_UpdateVerRecorder_Res &Response);
	int RDB_DeleteRecorder(CDBCmd_DeleteVerRecorder_Req &Request, CDBCmd_DeleteVerRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeVerRecorder_Req &Request, CDBCmd_MergeVerRecorder_Res &Response);
	int RDB_CommitDatVer(CDBCmd_CommitDatVer_Req &Request, CDBCmd_CommitDatVer_Res &Response);
	int RDB_RollBackDatVer(CDBCmd_RollBackDatVer_Req &Request, CDBCmd_RollBackDatVer_Res &Response);
	int RDB_CompareDatVer(CDBCmd_CompareDatVer_Req &Request, CDBCmd_CompareDatVer_Res &Response);
	int RDB_CopyDatVer(CDBCmd_CopyDatVer_Req &Request, CDBCmd_CopyDatVer_Res &Response);
	int RDB_BatchExec(CDBCmd_MultiDBTransVerOper_Req &Request, CDBCmd_MultiDBTransVerOper_Res &Response);

	//int GetMaxID(const char *lpszTableName,const char *lpszFieldName,int &maxid);
	int RDB_GeoOverlay(CDBCmd_GeoOverlay_Req &Request,CDBCmd_GeoOverlay_Res &Response);
	int RDB_CalGeoBuffer(CDBCmd_CalGeoBuffer_Req &Request,CDBCmd_CalGeoBuffer_Res &Response);
	int RDB_CalGeoBuffer(CDBCmd_CalLineGeoBuffer_Req &Request,CDBCmd_CalLineGeoBuffer_Res &Response);
	int RDB_ReadTableName(CDBCmd_ReadTableName_Req &Request,CDBCmd_ReadTableName_Res &Response);
	int RDB_CreateTable(CDBCmd_CreateTable_Req &Request,CDBCmd_CreateTable_Res &Response);

	//上传文件，LocalFileName，上传本地文件的全路径文件名，SrvFileName数据库存储的名字
	int RDB_FileUpLoad(CSgString &SrvFileName,CSgString &LocalFileName,CSgString *pContentType=NULL,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);
	//上传文件
	int RDB_FileUpLoad(char *pFileData,size_t FileLen,CSgString &SrvFileName,CSgString *pContentType=NULL,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);

	//下载文件  当QueryType=0:按文件名获取文件内容  QueryType=1:按需求语句获取文件内容
	int RDB_FileDownLoad(SG_UCHAR QueryType,CSgString &SrvFileName,CSgString &LocalFileName,S_NoSqlFileInfo &FileInfo,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);

	int RDB_RemoveFile(CDBCmd_RemoveFile_Req &Request,CDBCmd_RemoveFile_Res &Response);
	int RDB_GetFileInfo(CDBCmd_GetFileInfo_Req &Request,CDBCmd_GetFileInfo_Res &Response);
	int RDB_GetFileNameArray(CDBCmd_GetFileNameArray_Req &Request,CDBCmd_GetFileNameArray_Res &Response);
};

class _GAP_C_PROCSRVDLL_PORT CGAP_DppSrvClient_Real:public CGAP_SrvClient
{
	CGAP_DBLocalOper m_DBLocalOper;
	SG_INT			m_UseLocalDBFlag;
	SG_BOOL			 m_LinkIsGDBSrv;	//连接是图形服务
	SG_INT			m_UseDesFlag;		//加密传输
private:
	SG_BOOL IsUseLocalDB();
	SG_BOOL IsUseDesTrans();
	int RDB_ReadRecorderBase(CDBCmd_ReadRecorder_Req &Request, CDBCmd_ReadRecorder_Res &Response);
	int RDB_ReadRecorderBase(CDBCmd_ReadGeoRecorder_Req &Request, CDBCmd_ReadGeoRecorder_Res &Response);
	int RDB_ReadLobRecorderBase(CDBCmd_ReadLobRecorder_Req &Request, CDBCmd_ReadLobRecorder_Res &Response);
	int RDB_ReadRecorderBase(CDBCmd_CompileReadRecorder_Req &Request, CDBCmd_CompileReadRecorder_Res &Response);
	int RDB_ReadRecorderBase(CDBCmd_CompileReadLobRecorder_Req &Request, CDBCmd_CompileReadLobRecorder_Res &Response);
	int RDB_ReadRecorderBase(CDBCmd_ReadVerRecorder_Req &Request, CDBCmd_ReadVerRecorder_Res &Response);

public:
	CGAP_DppSrvClient_Real(char *SrvIP=NULL,int Port=SG_DEFAULT_SGDPP_SRV_PORT,char *SrvName=SG_DPP_SRV_NAME);
	CGAP_DppSrvClient_Real(CGAP_SrvClientBase *pClientBase);
	~CGAP_DppSrvClient_Real();
	void SetUseDesTrans(SG_BOOL UseDesFlag)
	{
		if(UseDesFlag)
			m_UseDesFlag=1;
		else
			m_UseDesFlag=0;
	};
	void SetUseLocalDB(SG_BOOL UseLocalDB)
	{
		if(UseLocalDB)
			m_UseLocalDBFlag=1;
		else
			m_UseLocalDBFlag=0;
	};
	void SetLinkGDBFlag(SG_BOOL LinkGDBFlag)
	{
		m_LinkIsGDBSrv=LinkGDBFlag;
	};
	int RDB_ReadRecorder(CDBCmd_ReadRecorder_Req &Request,CDBCmd_ReadRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertRecorder_Req &Request,CDBCmd_InsertRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateRecorder_Req &Request,CDBCmd_UpdateRecorder_Res &Response);
	int RDB_DeleteRecorder(CDBCmd_DeleteRecorder_Req &Request,CDBCmd_DeleteRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeRecorder_Req &Request,CDBCmd_MergeRecorder_Res &Response);

	int RDB_ReadRecorder(CDBCmd_ReadGeoRecorder_Req &Request,CDBCmd_ReadGeoRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertGeoRecorder_Req &Request,CDBCmd_InsertGeoRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateGeoRecorder_Req &Request,CDBCmd_UpdateGeoRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeGeoRecorder_Req &Request,CDBCmd_MergeGeoRecorder_Res &Response);
	int GetSpatialOwner(CSgString &Owner,SG_USHORT DBNo=DEFAULT_DBNO);

	int RDB_ReadLobRecorder(CDBCmd_ReadLobRecorder_Req &Request,CDBCmd_ReadLobRecorder_Res &Response);
	int RDB_InsertLobRecorder(CDBCmd_InsertLobRecorder_Req &Request,CDBCmd_InsertLobRecorder_Res &Response);
	int RDB_UpdateLobRecorder(CDBCmd_UpdateLobRecorder_Req &Request,CDBCmd_UpdateLobRecorder_Res &Response);
	int RDB_MergeLobRecorder(CDBCmd_MergeLobRecorder_Req &Request,CDBCmd_MergeLobRecorder_Res &Response);

	int RDB_ExecSQL(CDBCmd_ExecSQL_Req &Request,CDBCmd_ExecSQL_Res &Response);
	int RDB_ExecSQL(CDBCmd_ExecSQLNotTrigger_Req &Request,CDBCmd_ExecSQLNotTrigger_Res &Response);
	int RDB_BatchExec(CDBCmd_TransOper_Req &Request,CDBCmd_TransOper_Res &Response);
	int RDB_BatchExec(CDBCmd_MultiDBTransOper_Req &Request,CDBCmd_MultiDBTransOper_Res &Response);

	int RDB_BatchReadRecorder(CDBCmd_BatchReadRecorder_Req &Request,CDBCmd_BatchReadRecorder_Res &Response);

	int GetIDVal(SG_UCHAR DBNo,const char *Name,int WorkSpace,int Cnt,int *pSeqVal);
	int RDB_ReadLobField(CDBCmd_ReadLobField_Req &Request,CDBCmd_ReadLobField_Res &Response);
	int RDB_WriteLobField(CDBCmd_WriteLobField_Req &Request,CDBCmd_WriteLobField_Res &Response);
	int RDB_GetSysDate(CDBCmd_GetSysDate_Req &Request,CDBCmd_GetSysDate_Res &Response);
	int RDB_GetIDVal(CDBCmd_GetIDVal_Req &Request,CDBCmd_GetIDVal_Res &Response);
	int RDB_GetIDVal(CDBCmd_GetIDVal_New_Req &Request,CDBCmd_GetIDVal_Res &Response);
	int RDB_GetDBType(SG_INT DBNo=DEFAULT_DBNO);
	int RDB_GetDBType(CDBCmd_GetDBType_Req &Req,CDBCmd_GetDBType_Res &Res);
	int RDB_GetDBLinkStat(CCloud_GetDBLinkStat_Req &Request,CCloud_GetDBLinkStat_Res &Response);
	int RDB_ReadRecorder(CDBCmd_CompileReadRecorder_Req &Request,CDBCmd_CompileReadRecorder_Res &Response);
	int RDB_ReadRecorder(CDBCmd_CompileReadLobRecorder_Req &Request,CDBCmd_CompileReadLobRecorder_Res &Response);
	int RDB_ExecSQL(CDBCmd_CompileExecSQL_Req &Request,CDBCmd_CompileExecSQL_Res &Response);

	int RDB_ReadRecorder(CDBCmd_ReadVerRecorder_Req &Request, CDBCmd_ReadVerRecorder_Res &Response);
	int RDB_InsertRecorder(CDBCmd_InsertVerRecorder_Req &Request, CDBCmd_InsertVerRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBCmd_UpdateVerRecorder_Req &Request, CDBCmd_UpdateVerRecorder_Res &Response);
	int RDB_MergeRecorder(CDBCmd_MergeVerRecorder_Req &Request, CDBCmd_MergeVerRecorder_Res &Response);
	int RDB_DeleteRecorder(CDBCmd_DeleteVerRecorder_Req &Request, CDBCmd_DeleteVerRecorder_Res &Response);
	int RDB_CommitDatVer(CDBCmd_CommitDatVer_Req &Request, CDBCmd_CommitDatVer_Res &Response);
	int RDB_RollBackDatVer(CDBCmd_RollBackDatVer_Req &Request, CDBCmd_RollBackDatVer_Res &Response);
	int RDB_CompareDatVer(CDBCmd_CompareDatVer_Req &Request, CDBCmd_CompareDatVer_Res &Response);
	int RDB_CopyDatVer(CDBCmd_CopyDatVer_Req &Request, CDBCmd_CopyDatVer_Res &Response);
	int RDB_BatchExec(CDBCmd_MultiDBTransVerOper_Req &Request, CDBCmd_MultiDBTransVerOper_Res &Response);

	int RDB_ReadTableInfo(CDBCmd_ReadTableInfo_Req &Request, CDBCmd_ReadTableInfo_Res &Response);
	int GetMaxID(const char* lpszTableName,const char*lpszFieldName,int&maxid);
	int RDB_GeoOverlay(CDBCmd_GeoOverlay_Req &Request,CDBCmd_GeoOverlay_Res &Response);
	int RDB_CalGeoBuffer(CDBCmd_CalGeoBuffer_Req &Request,CDBCmd_CalGeoBuffer_Res &Response);
	int RDB_CalGeoBuffer(CDBCmd_CalLineGeoBuffer_Req &Request,CDBCmd_CalLineGeoBuffer_Res &Response);
	int RDB_ReadTableName(CDBCmd_ReadTableName_Req &Request,CDBCmd_ReadTableName_Res &Response);
	int RDB_CreateTable(CDBCmd_CreateTable_Req &Request,CDBCmd_CreateTable_Res &Response);

	//上传文件，LocalFileName，上传本地文件的全路径文件名，SrvFileName数据库存储的名字
	int RDB_FileUpLoad(CSgString &SrvFileName,CSgString &LocalFileName,CSgString *pContentType=NULL,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);
	//上传文件
	int RDB_FileUpLoad(char *pFileData,size_t FileLen,CSgString &SrvFileName,CSgString *pContentType=NULL,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);

	//下载文件  当QueryType=0:按文件名获取文件内容  QueryType=1:按需求语句获取文件内容
	int RDB_FileDownLoad(SG_UCHAR QueryType,CSgString &SrvFileName,CSgString &LocalFileName,S_NoSqlFileInfo &FileInfo,
		CSgString *pDBName=NULL,SG_USHORT DBNo=DEFAULT_FILE_DBNO,CSgString *pErrInfo=NULL);

	int RDB_RemoveFile(CDBCmd_RemoveFile_Req &Request,CDBCmd_RemoveFile_Res &Response);
	int RDB_GetFileInfo(CDBCmd_GetFileInfo_Req &Request,CDBCmd_GetFileInfo_Res &Response);
	int RDB_GetFileNameArray(CDBCmd_GetFileNameArray_Req &Request,CDBCmd_GetFileNameArray_Res &Response);

};
class _GAP_C_PROCSRVDLL_PORT CGAP_DppSrvClient:public CGAP_DppSrvClient_Real
{
public:
	CGAP_DppSrvClient(char *SrvIP=NULL);
	CGAP_DppSrvClient(CGAP_SrvClientBase *pClientBase);
	static int SetRepeatFlag(SG_BOOL RepeatFlag);
//	static int RDB_CompilePara_Json2DatSet(CSgString &Json, CSgDataSet &ParaDatSet);

};
class _GAP_C_PROCSRVDLL_PORT CGAP_HSDASrvClient_Real:public CGAP_SrvClient
{
public:
	CGAP_HSDASrvClient_Real(char *srvip=NULL,int Port=SG_DEFAULT_HSDASRV_PORT,char *SrvName=SG_RDP_RDB_SRV_NAME);
	CGAP_HSDASrvClient_Real(CGAP_SrvClientBase *pClientBase);
	~CGAP_HSDASrvClient_Real();
private:
	int HSDA_ReadRecorderBase(CHSDA_ReadRecorder_Req &Request, CHSDA_ReadRecorder_Res &Response);
public:
	int HSDA_ReadRecorder(CHSDA_ReadRecorder_Req &Request,CHSDA_ReadRecorder_Res &Response);
	int HSDA_ReadTblRecorder(CHSDA_ReadTblRecorder_Req &Request,CHSDA_ReadTblRecorder_Res &Response);
	int HSDA_ExecSQL(CHSDA_ExecSQL_Req &Request,CHSDA_ExecSQL_Res &Response);

	int HSDA_SubscribeData(CHSDA_SubscribeData_Req &Request,CHSDA_SubscribeData_Res &Response);
	int HSDA_CancelSubscribe(CHSDA_CancelSubscribe_Req &Request,CHSDA_CancelSubscribe_Res &Response);
	int HSDA_GetChangeData(CHSDA_GetChangeData_Req &Request,CHSDA_GetChangeData_Res &Response);

	//更改实时库的字段，对于微盒子和中央，还要改动关系库内容
	int HSDA_UpdateRecorder(CDBCmd_UpdateRecorder_Req &Request,CDBCmd_UpdateRecorder_Res &Response);
	int HSDA_InsertRecorder(CDBCmd_InsertRecorder_Req &Request, CDBCmd_InsertRecorder_Res &Response);
	int HSDA_DeleteRecorder(CDBCmd_DeleteRecorder_Req &Request, CDBCmd_DeleteRecorder_Res &Response);
	int HSDA_RDBMemOper(CHSDA_RDBMemOper_Req &Request, CHSDA_RDBMemOper_Res &Response);
	int HSDA_NewCCRtDB(CHSDA_RDB_NewCCRtDB_Req &Request, CHSDA_RDB_NewCCRtDB_Res &Response);
	int HSDA_DeleteCCRtDB(CHSDA_RDB_DeleteCCRtDB_Req &Request, CHSDA_RDB_DeleteCCRtDB_Res &Response);
	int HSDA_GetNewSchemaHandler(CHSDA_GetNewSchemaHandler_Req &Request, CHSDA_GetNewSchemaHandler_Res &Response);
};

#define SG_CENTERCALC_PROCMODE_FORCEMODIFY  0x00000001   //计算时强制修改已有数据
#define SG_CENTERCALC_PROCMODE_HIGHLEVEL	0x00000002   //计算时写入数据优先级最高,不容许任何统计数据修改

class _GAP_C_PROCSRVDLL_PORT CGAP_HSDASrvClient:public CGAP_HSDASrvClient_Real
{
public:
	CGAP_HSDASrvClient(char *srvip=NULL);
	CGAP_HSDASrvClient(CGAP_SrvClientBase *pClientBase);
};
class RDBStreamParameter;
class _GAP_C_PROCSRVDLL_PORT CGAP_RDBStream :public CGAP_HSDASrvClient,public ACE_Task<ACE_MT_SYNCH>
{
public:
	typedef SG_INT(FUNC_STREAMEVENT_RESPONSE)(SG_UINT64 StreamHandler, CSgDataSet *pDatSet);
private:
	CSG_OS_ThreadVar		m_DatLock;
	FUNC_STREAMEVENT_RESPONSE	*m_pCallBack;
	MAP_INT64_VOIDPT		m_StreamList;
	int m_StopFlag;
	SG_UINT64		m_LocalStreamHandler;

public:

	CGAP_RDBStream();
	virtual ~CGAP_RDBStream();
	int  Open();
	//关闭流管理器 ( 关闭网络连接，退出线程，释放订阅的流信息)
	void Close();
	//测试流管理器是否打开
	int IsOpen();
	//订阅流信息
	SG_UINT64  Subscibe(SG_UINT64 SchemaHander,char *pTblName, CSgString &KeyField, CSgString &SubFields, SET_INT64 &KIDList, int Interval = 5);
	int CloseStream(SG_UINT64 StreamHandler);	//关闭指定的流
	// 变化流数据的通知
	int BindStreamEventFunc(FUNC_STREAMEVENT_RESPONSE *pFunc);

private:

	virtual int svc();								//内部服务线程
	int OpenStream(RDBStreamParameter* pStream);	//打开指定的流
	int SendGetChangeDataRequest(int GetType, S_THREEINT64 &StreamInfo);
	int PacketSubscribeReq(RDBStreamParameter *pStream, CHSDA_SubscribeData_Req &Req);
	int CloseStream(VECT_THREEINT64 &DelStreamList);
};

class _GAP_C_PROCSRVDLL_PORT CGAP_TSDASrvClient_Real:public CGAP_SrvClient
{
private:
	template <class REQUEST_INFO,class RESPONSE_INFO>
	SG_INT ReadCmdRequest(SG_INT CmdType,REQUEST_INFO &Request,RESPONSE_INFO &Response);
	int PackAccValue(SG_INT StartYMD,SG_INT StartHMS,SG_INT Interval,CSgDataSet *pProcDatSet);
	template <class REQUEST_INFO>
	int PrepareAccReqVal(REQUEST_INFO &Req,SG_INT DevFlag,CSgDataSet &StatDatSet,int &HasStatFlag,CSgString &KeyFields);
	int TSDA_QueryDataByPtBase(CTSDA_QueryDataByPt_Req &Request, CTSDA_QueryDataByPt_Res &Response);
	int TSDA_QueryDataByPtBase(CTSDA_QueryDataByPt_New_Req &Request, CTSDA_QueryDataByPt_New_Res &Response);
	int TSDA_QueryDataByPtBase(CTSDA_QueryDataByPt_Append_Req &Request, CTSDA_QueryDataByPt_Append_Res &Response);

public:
	CGAP_TSDASrvClient_Real(char *srvip=NULL,int Port=SG_DEFAULT_TSDASRV_PORT,char *SrvName=SG_RDP_HDB_SRV_NAME);
	CGAP_TSDASrvClient_Real(CGAP_SrvClientBase *pClientBase);
	~CGAP_TSDASrvClient_Real();
	int TSDA_QueryDataByPt(CTSDA_QueryDataByPt_Req &Request,CTSDA_QueryDataByPt_Res &Response);
	int TSDA_QueryDataByPt(CTSDA_QueryDataByPt_New_Req &Request,CTSDA_QueryDataByPt_New_Res &Response);
	int TSDA_QueryStatByPt(CTSDA_QueryStatByPt_Req &Request,CTSDA_QueryStatByPt_Res &Response);
	int TSDA_QueryValuesByPt(CTSDA_QueryValuesByPt_Req &Request,CTSDA_QueryValuesByPt_Res &Response);
	int TSDA_SaveDataByPt(CTSDA_SaveDataByPt_Req &Request,CTSDA_SaveDataByPt_Res &Response);
	int TSDA_DelDataByPt(CTSDA_DelDataByPt_Req &Request,CTSDA_DelDataByPt_Res &Response);

	int TSDA_QueryDataByPt(CTSDA_QueryDataByPt_Append_Req &Request,CTSDA_QueryDataByPt_Append_Res &Response);
	int TSDA_QueryDataByPt_Pure(CTSDA_QueryDataByPt_New_Req &Request,CTSDA_QueryDataByPt_New_Res &Response);
	int TSDA_GetDBLinkStat(CCloud_GetDBLinkStat_Req &Request,CCloud_GetDBLinkStat_Res &Response);
};
class _GAP_C_PROCSRVDLL_PORT CGAP_TSDASrvClient:public CGAP_TSDASrvClient_Real
{
public:
	CGAP_TSDASrvClient(char *srvip=NULL);
	CGAP_TSDASrvClient(CGAP_SrvClientBase *pClientBase);
};


class _GAP_C_PROCSRVDLL_PORT CGAP_ReplicationSrvClient:public CGAP_SrvClientBase
{
public:
	CGAP_ReplicationSrvClient(char *SrvIP);
	~CGAP_ReplicationSrvClient();
	int REP_GetLogicCellVer(CREP_GetLogicCellVer_Req &Request,CREP_GetLogicCellVer_Res &Response);
	int REP_GetLogicCellDat(CREP_GetLogicCellDat_Req &Request,CREP_GetLogicCellDat_Res &Response);
};

class _GAP_C_PROCSRVDLL_PORT CGAP_MsgSrvClient:public CGAP_SrvClient
{
public:
	CGAP_MsgSrvClient(char *SrvIP=NULL);
	CGAP_MsgSrvClient(CGAP_SrvClientBase *pClientBase);
	~CGAP_MsgSrvClient();
	int PostChangeMessage(const char*to,const char*from,int operatorType,CSgDataSet&data,int flag=m_national);
	int PostMessage(const char*to,const char*from,CSgDataSet&msgData,int flag=m_national);
	int PostMessage(const char* to,const char*from,const char*data,int len,int flag=m_national);
};
#define PCM_FILESEND_BYTE_MAXNUM		10485760
class _GAP_C_PROCSRVDLL_PORT CGAP_PCMSrvClient:public CGAP_SrvClient
{
public:
	CGAP_PCMSrvClient(char *srvip=NULL,int Port=SG_DEFAULT_RDP_PROCSRV_PORT);
	CGAP_PCMSrvClient(CGAP_SrvClientBase *pClientBase);
	~CGAP_PCMSrvClient();
	int PCM_StartProc(CPCM_StartProc_Req &Request,CPCM_StartProc_Res &Response);
	int PCM_EndProc(CPCM_EndProc_Req &Request,CPCM_EndProc_Res &Response);
	int PCM_EndProc(CPCM_EndProc_Req &Request,CPCM_EndProc_Res &Response,SG_INT TimeOutSecond);
	int PCM_AskProcStatus(CPCM_AskStatus_Req &Request,CPCM_AskStatus_Res &Response);
	int PCM_SysEnvPath(CPCM_SysEnvPath_Req &Request,CPCM_SysEnvPath_Res &Response);
	int PCM_PathFileInfo(CPCM_PathFileInfo_Req &Request,CPCM_PathFileInfo_Res &Response);
	int PCM_FileOper(CPCM_FileOper_Req &Request,CPCM_FileOper_Res &Response);
	//ProcMode: bit0:网关传输
	int PCM_FileDownLoad(CSgString &SrvFileName, CSgString &LocalFileName, int ProcMode, CSgString &ErrInfo, SG_INT NodeID = 0, SG_INT MaxPacketSize = 0);
	int PCM_FileUpLoad(CSgString &SrvFileName, CSgString &LocalFileName, int ProcMode, CSgString &ErrInfo, SG_INT NodeID, SG_INT MaxPacketSize = 0);
	int PCM_RestartSrv(CPCM_RestartSrv_Req &Request,CPCM_RestartSrv_Res &Response);
	int PCM_ExeShecllCmd(CPCM_ShellCmd_Req &Request,CPCM_ShellCmd_Res &Response,SG_INT TimeOutSecond=120);
	int PCM_GetFileInfo(CPCM_GetFileInfo_Req &Request,CPCM_GetFileInfo_Res &Response);
	int PCM_StartCalcProc(CPCM_StartCalcProc_Req &Request, CPCM_StartCalcProc_Res &Response);
	int PCM_AskCalcProcState(CPCM_AskCalcProcState_Req &Request, CPCM_AskCalcProcState_Res &Response);
};
class _GAP_C_PROCSRVDLL_PORT CGAP_CPSSrvClient:public CGAP_DppSrvClient,public CGAP_HSDASrvClient,public CGAP_TSDASrvClient,
	public CGAP_MsgSrvClient,public CGAP_PCMSrvClient
{
	CGAP_SrvClientBase *m_pClientBase;
	SG_BOOL				m_ClientNewFlag;
public:
	CGAP_CPSSrvClient(char *srvip=NULL);
	CGAP_CPSSrvClient(CGAP_SrvClientBase *pClientBase);
	~CGAP_CPSSrvClient();
	void DisConnectSrv();
	int CPS_GetCenterID(CCPS_GetCenterID_Req &Request,CCPS_GetCenterID_Res &Response);
	int CPS_GetCenterID();
	int GetCPSSrvIP(CSgString &SrvIP);
	int CPS_GetClientNum();
};


template <class T>
class CSrvClientArrayT
{
public:
	CSrvClientArrayT(int nStreams,char*lpszSrv=NULL):m_sem(nStreams)
	{
//		m_UseGdbFlag=false;
		m_streamLock.acquire();
		for(int i=0;i<nStreams;i++)
		{
			T * p= new T(lpszSrv);
			m_freeStremas.push_back(p);
		}
		m_streamLock.release();
	}
	~CSrvClientArrayT()
	{
//		typename std::set<T*>::iterator itr;
		typename std::list<T*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
			delete p;
		}
		//
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
			delete p;
		}
		//
		m_freeStremas.clear();
		m_busyStremas.clear();
		//
		m_streamLock.release();
	}
	//
	int GetCount()
	{
		m_streamLock.acquire();
		int size = m_freeStremas.size()+m_busyStremas.size();
		m_streamLock.release();
		return size;
	}
	int GetFreeCount()
	{
		m_streamLock.acquire();
		int size = m_freeStremas.size();
		m_streamLock.release();
		return size;
	}

	T * Acquire()
	{
	
		m_sem.acquire();
		m_streamLock.acquire();
		T*pStream=m_freeStremas.front();
		m_freeStremas.pop_front();
		m_busyStremas.push_back(pStream);
		m_streamLock.release();
		return pStream;
	}
	void Release(T*pStream)
	{

		typename std::list<T*>::iterator itr;
		m_streamLock.acquire();
		for (itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			T * p = (*itr);
			if(pStream!=p)
				continue;
			m_busyStremas.remove(pStream);
			m_freeStremas.push_back(pStream);
			break;
		}		
		m_streamLock.release();
		m_sem.release();
	}
	void CloseFree()
	{
		typename std::list<T*>::iterator itr;
//		typename std::set<T*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
		}
		m_streamLock.release();
	}
	void CloseBusy()
	{
		typename std::list<T*>::iterator itr;
//		typename std::set<T*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
		}
		m_streamLock.release();
	}
	void CloseAll()
	{
		typename std::list<T*>::iterator itr;
//		typename std::set<T*>::iterator itr;
		m_streamLock.acquire();
		for(itr =m_freeStremas.begin();itr!=m_freeStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
		}
		for(itr =m_busyStremas.begin();itr!=m_busyStremas.end();itr++)
		{
			T * p = (*itr);
			p->DisConnectSrv();
		}
		m_streamLock.release();
	}
//	void SetUseGDBFlag(SG_BOOL UseGdbFlag);
	//
protected:
	//
	std::list<T *> m_freeStremas;
	std::list<T *> m_busyStremas;

	//
	ACE_Thread_Mutex  m_streamLock;
	ACE_Thread_Semaphore m_sem;
};
template <class T>
class CDBSrvClientArrayT:public CSrvClientArrayT<T>
{
public:
	CDBSrvClientArrayT(int nStreams,char*lpszSrv=NULL,SG_BOOL LinkGdbFlag=false,SG_BOOL LocalDBFlag=false)
		:CSrvClientArrayT<T>(nStreams,lpszSrv)
	{
		typename std::list<T *>::iterator itr;
//		typename std::set<T *>::iterator itr;
		CSrvClientArrayT<T>::m_streamLock.acquire();
		for(itr=CSrvClientArrayT<T>::m_freeStremas.begin();itr!=CSrvClientArrayT<T>::m_freeStremas.end();itr++)
		{ 
			T *p=(*itr);
			if(p==NULL)
				continue;
			p->SetLinkGDBFlag(LinkGdbFlag);
			//p->SetUseLocalDB(LocalDBFlag);
		}
		CSrvClientArrayT<T>::m_streamLock.release();
	}
};
typedef CSrvClientArrayT <CGAP_SrvClientBase >   CGapBaseClientArray;
typedef CDBSrvClientArrayT <CGAP_DppSrvClient >   CGapDppClientArray;
typedef CDBSrvClientArrayT <CGAP_DppSrvClient_Real >   CGapDppClientArray_Real;
typedef CSrvClientArrayT <CGAP_HSDASrvClient >   CGapHSDAClientArray;
typedef CSrvClientArrayT <CGAP_HSDASrvClient_Real >   CGapHSDAClientArray_Real;
typedef CSrvClientArrayT <CGAP_TSDASrvClient >   CGapTSDAClientArray;
typedef CSrvClientArrayT <CGAP_TSDASrvClient_Real >   CGapTSDAClientArray_Real;
typedef CSrvClientArrayT <CGAP_ReplicationSrvClient > CGapRepClientArray;
typedef CSrvClientArrayT <CGAP_MsgSrvClient > CGapMsgClientArray;
typedef CSrvClientArrayT <CGAP_PCMSrvClient > CGapPCMSrvClientArray;
typedef CSrvClientArrayT <CGAP_CPSSrvClient > CGapCPSClientArray;

/*
template< typename T >
class  CSrvClientDoorT
{
	T							*m_pClient;
	CSrvClientArrayT<T >		*m_pClientArray;
public:
	 CSrvClientDoorT(CSrvClientArrayT<T > *pClientArray)
	{
		m_pClientArray=pClientArray;
		m_pClient=NULL;
	};
	 ~CSrvClientDoorT()
	{
		if(m_pClientArray==NULL)
			return;
		if(m_pClient)
			m_pClientArray->FreeOneSrvClient(m_pClient);
		m_pClient=NULL;
	};
	inline T *GetOneSrvClient(SG_UCHAR WaitFlag=true)
	{
		if(m_pClientArray==NULL)
			return NULL;
		if(m_pClient)
			m_pClientArray->FreeOneSrvClient(m_pClient);
		m_pClient=NULL;
		ACE_Time_Value tv(0,100*1000);	//20ms
		while(true)
		{
			m_pClient=m_pClientArray->GetOneSrvClient();
			if(m_pClient||WaitFlag==false)
				break;
			ACE_OS::sleep(tv);	

		}
		return m_pClient;
	};

};
*/
template< typename T >
class  CSrvClientDoorT
{
	T							*m_pClient;
	CSrvClientArrayT<T >		*m_pClientArray;
public:
	CSrvClientDoorT(CSrvClientArrayT<T > *pClientArray)
	{
		m_pClientArray=pClientArray;
		m_pClient=NULL;
	};
	~CSrvClientDoorT()
	{
		if(m_pClientArray==NULL)
			return;
		if(m_pClient)
			m_pClientArray->Release(m_pClient);
		m_pClient=NULL;
	};
	inline T *GetOneSrvClient(SG_UCHAR WaitFlag=true)
	{
		if(m_pClientArray==NULL)
			return NULL;
		if(m_pClient)
			m_pClientArray->Release(m_pClient);
		m_pClient=m_pClientArray->Acquire();
		return m_pClient;
	};

	inline T * operator->( )
	{ 
		if(NULL==m_pClient) m_pClient=this->GetOneSrvClient(true);
		return m_pClient;
	}
};

//==================================================================================================

typedef CSrvClientDoorT<CGAP_SrvClientBase > CGapBaseClientDoor;
typedef CSrvClientDoorT<CGAP_DppSrvClient > CGapDppClientDoor;
typedef CSrvClientDoorT<CGAP_HSDASrvClient > CGapHSDAClientDoor;
typedef CSrvClientDoorT<CGAP_TSDASrvClient > CGapTSDAClientDoor;
//typedef CSrvClientDoorT<CGAP_GDESrvClient > CGapGDEClientDoor;
typedef CSrvClientDoorT<CGAP_DppSrvClient_Real > CGapDppClientDoor_Real;
typedef CSrvClientDoorT<CGAP_HSDASrvClient_Real > CGapHSDAClientDoor_Real;
typedef CSrvClientDoorT<CGAP_TSDASrvClient_Real > CGapTSDAClientDoor_Real;
typedef CSrvClientDoorT<CGAP_ReplicationSrvClient > CGapRepClientDoor;
typedef CSrvClientDoorT<CGAP_MsgSrvClient > CGapMsgClientDoor;
typedef CSrvClientDoorT<CGAP_PCMSrvClient > CGapPCMSrvClientDoor;
typedef CSrvClientDoorT<CGAP_CPSSrvClient > CGapCPSClientDoor;


_GAP_C_PROCSRVDLL_PORT short int GAP_Srv_Init();

_GAP_C_PROCSRVDLL_PORT void GAP_Srv_End();
_GAP_C_PROCSRVDLL_PORT void GAP_SetUseLocalDB(SG_BOOL UseLocalDB);
_GAP_C_PROCSRVDLL_PORT int GAP_ReadPara_Json2DatSet(CSgString &JsonStr, CSgDataSet &DatSet);
#endif