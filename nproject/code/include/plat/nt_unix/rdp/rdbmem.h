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
	//根据参数配置变化需要重新加载
	int ReLoadByCfgChan();
};
/***********************************************
对象属性表域信息结构
***********************************************/
#define SG_RTBL_COL_PROCMODE_SYNCRTDB		0x00000001		//是否是快速同步字段
#define SG_RTBL_COL_PROCMODE_SAVEHISDB		0x00000002		//是否存储历史数据
#define SG_RTBL_COL_PROCMODE_SAVECLEAR		0x00000004		//是否存储完成后就清空字段
#define SG_RTBL_COL_PROCMODE_CHANGESAVE		0x00000008		//该字段是否是变化存储字段
#define SG_RTBL_COL_PROCMODE_SYNCFATHERDB	0x00000010		//字段改变是否回写源端数据库
//根据IDX信息整理自动赋予的
#define SG_RTBL_COL_PROCMODE_IDXFIELD		0x80000000		//该字段是否是索引字段

//对象属性表域信息结构
class _RDP_REALDB_DLL_PORT CRDBFieldInfo
{
public:
	SG_FIELDNAME FieldName;
	SG_FIELDNAME TblCode;
	SG_FIELDNAMEDES FieldDesc;			//实时库表描述
	SG_FIELDNAMEDES DBFieldName[SG_RDB_PARATBLNUM];		//在第一个参数表中的域名,
	SG_FIELDNAMEDES HisDBFieldName;		//存储在历史数据库中的域名,
	SG_UCHAR FieldMode;    //0:参数列 1:数据列 2:内存列
	SG_UCHAR	  DispFlag;  //内存是否在工具中显示
	SG_SHORT FieldNo;  //列在表内的序号
	SG_SHORT FieldType;
	SG_SHORT FieldLen;
	SG_SHORT SqlType;			// for oracle
	SG_USHORT DatOffset;			//字段内容在一条记录中的相对位置
	SG_UINT	ProcMode;
	SG_INT		TblID;
	union
	{
		SG_FIELDNAMEDES cVal;			//缺省值
		SG_INT64		iVal;
		double			dVal;
	}DefaultVal;
public:
	CRDBFieldInfo();
	~CRDBFieldInfo();
	void SetFieldName(SG_CHAR*pFieldName);
	SG_CHAR *GetFieldName();
	//两个域信息是否一致
	SG_BOOL Equal(CRDBFieldInfo &p);
	SG_BOOL GetColVal(void *pColDat, CSgString &xStr);
	SG_BOOL SetIdxFieldFlag(SG_BOOL Flag);
	SG_BOOL GetIdxFieldFlag();
	SG_BOOL Serialize(CSgArchive&ar, int VerNo = -1);
};

//--------------------------------------------------------------------------
//以下是对实时数据库系统中操作条件的定义
//--------------------------------------------------------------------------
#define  SG_RDB_LOGIC_COND_AND              0        //与
#define  SG_RDB_LOGIC_COND_OR               1        //或

#define  SG_RDB_COND_EQU              0        //等于
#define  SG_RDB_COND_LARGE            1        //大于
#define  SG_RDB_COND_SMALL            2        //小于
#define  SG_RDB_COND_LARGEEQU         3        //大于等于
#define  SG_RDB_COND_SMALLEQU         4        //小于等于
#define  SG_RDB_COND_NOTEQU           5        //不等于

typedef struct SG_RDB_CONDINFO
{
	unsigned char	LogicOpt;
	unsigned char	RelOpt;
	short			TblNo;
	std::string		Code;
	SG_RDB_DATVAR		Val;			//条件值
	CRDBFieldInfo *pColInfo; //选择列在表中的域信息
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
#define SG_RDB_DYNAMIC_SCHEMAHANDLER_MIN     1000 //动态Schema的句柄最小值

#define SG_RDB_DBTYPE_RUNNING	1 //运行态实时库
#define SG_RDB_DBTYPE_STUDY		2 //研究态实时库
#define SG_RDB_DBTYPE_CALCCASE	3 //算例实时库
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
	SG_INT				LoadType; //0: 从数据库加载  1：从文件加载
	SG_INT				RtDBVerNo;
	SG_INT				SchemaDBNo;
	SG_INT				SchemaType;
	SG_UINT				SchemaProcMode;
	std::string			SrvTypeStr;  //LoadType=0 是SrvType信息  1:是文件的名称
	MAP_STRING_STRING	ReplaceKeyList;	//first:Key等关键字，如workspace SysID等  second: 替换信息
public:
	CRDBLoadSetting();
	~CRDBLoadSetting();
	int Compare(CRDBLoadSetting *pLoadSetting);
	void operator = (CRDBLoadSetting &para);
	void operator = (CHSDA_RTDBLoadPara &para);
	//ParaBuf是Json文件格式 {"LoadType":1,"RtDBVerNo",5,"SrvTypeStr":"1,2",
	//"ReplaceKey":[{"name":"OF_SUBSTATION","value":"100300000000000147,100300000000000148"},{"name":"OF_VOLT_LEVEL","value":"101400000000000114"}]}
	int SetPara(CSgString &ParaBuf);

private:
	int Free();
};
//算例实时库,即动态实时库
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
	//释放本进程映射到的所有实时库
	static int FreeAllShareMemory();
	int CreateShareMemory(CRDBLoadSetting &LoadSetting);
	//映射共享内存,并不建立它
	virtual int MapShareMemory();
	virtual int FreeShareMemory();
	int WriteRDBToFile(CSgString &FileName);
};
//汇聚实时库,即常驻实时库
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
	//读取配置文件中常驻内存的实时库配置
	static int ReadSchemaInfoFromFile(SET_INT64 *pSettingChanRDBHandlerList = NULL);
	//获取配置文件中常驻内存的实时库配置
	static int GetCfgSchemaHandler(SET_INT64 &SchemaHandlerList);
	static int GetCfgSchemaInfo(SG_UINT64 SchemaHandler, CRDBLoadSetting &LoadSetting);
	//释放本进程映射到的所有实时库
	static int FreeAllShareMemory();
	int LoadRealTableForCfgChan();
	//创建实时库
	int CreateShareMemory();
	//备份实时库到文件中
	int WriteRDBToFile(CSgString &FileName);
	//映射共享内存,并不建立它
	virtual int MapShareMemory();
	//释放共享内存
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
	//打开实时库表
	int OpenTable(char *RTblName,unsigned char LockFlag=0,unsigned char ForceOpenFlag=0,int MaxWaitMs=0);
	int OpenTableByTblID(int RTblID, unsigned char LockFlag = 0, unsigned char ForceOpenFlag = 0, int MaxWaitMs = 0);
	int ReOpenTable(unsigned char LockFlag =0,unsigned char ForceOpenFlag =0, int MaxWaitMs = 0);
	virtual int TableCanUse();
	virtual int CloseTable();

	//获取表的基本信息
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
	//索引相关的函数
	int RegisterIndex(char *pFieldNames);
	int UnRegisterIndex(char *pFieldNames);
	int IsIndexField(SG_INT FieldPtr);
	int GetUniqueKeyList(VECT_INT &KeyPtrList);
	SG_UINT	GetKeyIndexCreateTime();

	//修改表的内容
	//SyncMode bit0:同步参数字段  bit1:同步数据字段
	int InsertRecorder(CSgDataSet &DatSet,int SyncMode);
	//SyncMode bit0:同步参数字段  bit1:同步数据字段
	int UpdateRecorder(CSgDataSet &DatSet,int SyncMode);
	//SyncMode bit0:同步参数字段  bit1:同步数据字段
	int DelRcdByKey(VECT_INT64 &KeyIDList,int SyncMode);
	int AddRcd(int RcdNum, int RcdLen, void *pRcdDat);
	int DelRcdByNo(int RcdNo);
	int DelAllRcd();
	//SyncMode bit0:同步参数字段  bit1:同步数据字段
	int SyncRecorder2ParaDB(int SyncMode,VECT_INT *pRcdNoList=NULL);

	void *GetFirstRcd();//只有写打开的,才可以用这个函数
	//获取表的记录信息
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
	//设置更新时间的值
	int SetUpdateTimeByNo(SG_INT RcdNo, SG_UINT UpdateTime = 0);
	//设置索引更改信息
	int SetIdxChange();
	//获取主键的值
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
#define  SG_OBJMODEL_RELATION_PARENT		0X01  //父子关系
#define  SG_OBJMODEL_RELATION_CONNECT		0X02  //连接关系
#define  SG_OBJMODEL_RELATION_TRIGGER		0X04  //触发关系
//获取对象的模型关系
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
	//执行sql语句，pRetDatSet为返回的信息值 MaxMemSize:最大内存大小，为0: 表示不控制，MaxRcdNum最多选择出的纪录个数 0:表示全部选出
	//pRealRcdNum:返回符合条件的记录个数,可能比MaxRcdNum多 但实际选出的个数<=MaxRcdNum
	int ExecSqlCmd(char *pSQLBuf, CSgDataSet *pRetDatSet, int MaxMemSize = 0, int MaxRcdNum = 0,
		int *pRealRcdNum = NULL, char *pTblName = NULL, int *pCanExecFlag = NULL);
};
#endif