
#ifndef _NET_DEF_H_
#define _NET_DEF_H_
#include "sgConst.h"
#include "VersionDefines.h"
#include "csgdataset.h"
#include "NetCommand.h"
#include "command/GdbCommand.h"

/**********************************************************************
	本文定义与空间引擎器通信相关功能号和相关结构
	Part	1:		指令表
	Part	2:		
**********************************************************************/
//********************指令表开始*******************//


//********************指令表结束*******************//

enum GDBSRV_STATUS
{
	gdbsrv_status_normal		=0,
	gdbsrv_status_exception	=1,
	gdbsrv_status_backup		=2
};
//********************指令表*******************//

struct SG_CORE_API ClientRequestUserInfo
{
	
	ClientRequestUserInfo();
	virtual ~ClientRequestUserInfo();
	
	SG_BOOL		ModiByApp;	// --- 被应用接口修改标记（不参与传递）
	SG_ULONG	Company;	// --- 用户的公司信息
	SG_ULONG	UserID;		// --- 请求的用户

	virtual SG_BOOL Serialize(CSgArchive&ar);
};

// --- 对象属性请求参数
/*enum version_status_goto
{
	vlm_ask_run_ver      =0,
	vlm_same_ver_downto_up,
	vlm_same_ver_upto_down,
	vlm_diff_ver_goto,
	vlm_run_to_edit
};
*/
/************************************************************************/
/*                  空间引擎请求通用命令结构		                    */
/************************************************************************/
struct SG_CORE_API S_SgNetCommandHead:public CNetCmdHead
{
	SG_UINT		VerNo;			//运行版、编辑版、规划版
//	SG_UINT		Reserve;	//预留
	S_SgNetCommandHead()
	{
		VerNo		= 0;
	};
//	SG_BOOL CheckVersion();
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	
};
/************************************************************************/
/*						空间引擎请求参数基类		                    */
/************************************************************************/
struct S_SgNetCommandPara
{
	virtual SG_BOOL GetTaskList(CSgObjects**TaskList)=0;
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1)=0;
};
/************************************************************************/
/*                  空间引擎请求返回参数基类		                    */
/************************************************************************/
struct S_SgNetCommandRtn
{
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1)=0;
};

struct SG_CORE_API Ver_ObjInfoRequestPara
{
	CSgString	TableName;		//表名
	CSgString	FieldName;		//字段名
	CSgString	WhereClause;	//条件
	SG_INT		FeatureType;
	GIS_Schema	SchemeInfo;		//方案信息
	CSgLine		Range;

	Ver_ObjInfoRequestPara()
	{
		TableName="";
		FieldName="";
		WhereClause="";
		FeatureType=0;
	}
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno=-1);
};

struct SG_CORE_API ObjAttribRequestPara:public LoadControlPara,public CNetCmdHead
{
	
	//SG_UCHAR	VersionNo;		// --- 版本号
	CSgString	LocalName;		//本地库名
	CSgObjects	TaskList_base;	//前一任务列表（不要的ID集合）
	CSgObjects	TaskList;		//本次任务列表（不要的ID集合）
	GIS_Schema	SchemeInfo;		//规划方案id
	
	SG_UCHAR	ReqGeometry;	// --- 动态加载几何属性用
	SG_UCHAR    LoadFlag;       //根据TaskList_base和TaskList的处理方式(version_status_goto)  
	SG_UCHAR	LoadType;		//	加载类型，1 加载基本数据、2 扩展数据、3 全数据 ，参加 LoadType 枚举定义	
	SG_UCHAR	Reserve2;	//预留
	
	ObjAttribRequestPara()
	{
		LocalName.Empty();

		TaskList_base.ClearObj();
		TaskList.ClearObj();

	//	VersionNo	= SG_NET_VERSION;
		ReqGeometry = true;
		LoadFlag	= cvsRequestRunVer;
		LoadType	= CLT_LOAD_ALL;
		Reserve2	= 0;
	}
	
	//SG_BOOL CheckVersion();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- 对象属性请求返回参数

struct SG_CORE_API ObjAttribRequestReturnPara:public CNetCmdHead
{
	
	
	SG_UCHAR	HasGeometry;	// --- 返回的信息中是否具有几何属性
	
	SG_UCHAR	NotRunVersion;	//返回数据不是运行版本数据
	
	
	ObjAttribRequestReturnPara(){
		NotRunVersion=0;
	}
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};


struct SG_CORE_API ServerInfoRequestReturnPara:public ObjAttribRequestReturnPara
{
	union{
		SG_LONG ServerNo;
		SG_LONG FeatureLineID;
		SG_LONG FeatureStationID;
		SG_LONG GrpVerNo;
	};
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

// --- 表内容属性请求参数

struct SG_CORE_API TableContentRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
/*	SG_UCHAR	VersionNo;		// --- 版本号
	
	SG_UCHAR	Reserve0;	//预留
	
	SG_UCHAR	Reserve1;	//预留
	
	SG_UCHAR	Reserve2;	//预留
*/	
	CSgString	TableName;		//表名 --- 当表名为空时,WhereClause中为完整的数据库访问Sql语句
	
	CSgString	FieldName;		//字段名
	
	CSgString	WhereClause;	//条件
	
	CSgString	OrderField;		//排序字段
	
	TableContentRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
	}
	
//	SG_BOOL CheckVersion();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- 表内容属性请求返回参数

struct SG_CORE_API TableContentReturnPara:public CNetCmdHead
{
	
//	SG_UCHAR	VersionNo;		// --- 版本号
	SG_UINT		VerNo;			//运行态、编辑态、研究态
	SG_UINT		TaskNo;			//--- 任务号
	
/*	SG_UCHAR	RtnValue;		// --- 返回正确还是错误
	
	SG_UCHAR	Reserve1;	//预留
	
	SG_UCHAR	Reserve2;	//预留
	
	CSgString	RtnInfo;	// --- 返回信息,正确时为空,错误时为错误信息
*/	
	TableContentReturnPara()
	{
		//VersionNo	=	SG_NET_VERSION;
		TaskNo=0;
		VerNo=0;
	}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- 数据库执行(Exec)请求参数

struct SG_CORE_API DbfExecuteRequestPara:public CNetCmdHead
{
	
//	SG_UCHAR	VersionNo;		// --- 版本号
	
	SG_UCHAR	Commit;			// --- 是否提交
	
//	SG_UCHAR	Reserve1;	//预留
	
//	SG_UCHAR	Reserve2;	//预留
	
	CSgString	SqlWord;
	
	DbfExecuteRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
	}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- 数据库执行(Exec)返回参数
typedef TableContentReturnPara ModiCommandReturnPara;

// --- SDE普通表读取请求参数
typedef TableContentRequestPara SdeTableContentRequestPara;
// --- SDE普通表读取请求返回参数
typedef TableContentReturnPara SdeTableContentReturnPara;
// --- 带几何属性SDE表读取请求参数

struct SG_CORE_API SdeSpatialTableRequestPara:public TableContentRequestPara
{
	
	SdeSpatialTableRequestPara(){
		Flag = 0;
	}
	
	SG_INT	Flag;
	
	CSgLine Range;
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- 带几何属性SDE表读取返回参数
typedef TableContentReturnPara SdeSpatialTableReturnPara;


// --- 插入语句请求参数
struct SG_CORE_API InsertCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	InsertCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
		TaskNo=0;
	}
	
	//SG_UCHAR	VersionNo;		// --- 数据格式版本号
	
	SG_UCHAR	Commit;			// --- 是否提交
	
//	SG_UCHAR	Reserve1;	//预留
	
//	SG_UCHAR	Reserve2;	//预留
	GIS_Schema	SchemeInfo;		//规划方案id
	SG_UINT		TaskNo;			//--- 任务号
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}

	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- 修改语句请求参数

struct SG_CORE_API UpdateCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	UpdateCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		GeometryValid = true;
		Commit = true;
		TaskNo=0;
		OperExtAttrib = false;
	}
	
//	SG_UCHAR	VersionNo;		// --- 版本号
	
	SG_UCHAR	Commit;			// --- 是否提交
	
	SG_UCHAR	GeometryValid;	// --- 几何属性是否有效
	
	SG_UCHAR	OperExtAttrib;	// --- 是否改写台帐扩展属性
	CSgString	WhereClause;	//
	GIS_Schema	SchemeInfo;		//规划方案id
	SG_UINT		TaskNo;			//--- 任务号

	CSgObjects	TaskList;		//和该任务属于同一大版本下的任务列表（用于判定该图素是否锁定），为 GAP 代码兼容保留
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- 台帐同步请求参数
struct SG_CORE_API EmSyncRequestPara:public ClientRequestUserInfo
{
	EmSyncRequestPara()
	{
		TaskNo=0;
	}
	SG_UINT		TaskNo;			//--- 任务号
	SG_INT		OperType;	//操作类型(1-新增,2-修改,3-删除)
	SG_INT		ObjType;	//台帐改变的对象类型
	SG_INT		ObjID;		//台帐改变的对象ID
	SG_INT		TableID;	//台帐改变的表id
	SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno);
};



// --- 台帐同步数据集请求参数
struct SG_CORE_API EmSyncDatSetRequestPara:public ClientRequestUserInfo
{
	EmSyncDatSetRequestPara()
	{
		TaskNo=0;
	}
	SG_UINT		TaskNo;			//--- 任务号

	CSgDataSetArray_ObjOper	m_pObjs;				//操作对象的信息
	SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno);
};

/*struct SG_CORE_API Ver_PierceRequestPara:public ClientRequestUserInfo
{
	
	CSgGeoDataSet DatSet;
	SG_BOOL Serialize(CSgArchive&ar,SG_INT version=SG_NET_VERSION);
};
*/
// --- 删除语句请求参数

struct SG_CORE_API DeleteCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	DeleteCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
		TaskNo=0;
	}
	
//	SG_UCHAR	VersionNo;		// --- 版本号
	
	SG_UCHAR	Commit;			// --- 是否提交
	
//	SG_UCHAR	Reserve1;	//预留
	
//	SG_UCHAR	Reserve2;	//预留
	
	GIS_Schema	SchemeInfo;		//规划方案id
	SG_UINT		TaskNo;			//--- 任务号
	CSgObjects	TaskList;		//和该任务属于同一大版本下的任务列表（用于判定该图素是否锁定）
	CSgString	TableName;		// --- 表名
	
	CSgObjects  Objs;			// --- ArcGisID
	
	CSgString	WhereClause;	// --- 与ArcGisID互斥
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
//版本提交或回滚的参数
struct SG_CORE_API	CommitVersionPara:public ClientRequestUserInfo,public CNetCmdHead
{
	CommitVersionPara(){
//		VersionNo	=	SG_NET_VERSION;
		Commit = true;
	}
	SG_UCHAR	VersionNo;		// --- 版本号
	SG_UCHAR	Commit;			// --- 是否提交	
	SG_UCHAR	Reserve1;	//预留
	SG_UCHAR	OnlyCheckPoint;	//任务仅仅包含检查点
	GIS_Schema	SchemeInfo;		//规划方案id
	CSgObjects	TaskList;			//编辑任务号
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

//－－－设备调换后的ID同步

struct SG_CORE_API SYNC_ID_CHANGE 
{
	
	SG_SHORT ObjType;
	
	SG_INT ObjID_old;
	
	SG_INT ObjID_new;
	
	void Serialize(CSgArchive&ar);
};
// --- 短事务方式批量处理请求结构
class CSgDataSet;
class CSgGeoDataSet;
class CSgDataSetArray;
class CSgGeoDataSetArray;

struct ObjTransModiStruct
{
	
	ObjTransModiStruct();
	
	~ObjTransModiStruct();
	// --- 增加传输的字段
	
	void AttribFieldChange(SG_SHORT col);
	// --- 所有的字段都传输
	
	void AttribFieldChangeAll();
	//
	
	SG_BOOL GetAttribFieldChangeAll();
	
	CSgObjects *GetChangeFields(){return ChangeField;}
public:
	
	SG_UCHAR	GeoMetryOnly;	//GeoMetryOnly 成立将忽略CSgGeoDataSet中的物理属性(传输中不传递其它物理属性)
	
	SG_UCHAR	HasGeoMetry;	//是否服务器是否处理几何属性,如果不成立服务器处理时不对几何字段进行操作
protected:
	
	CSgObjects*	ChangeField;	//里面存放的是需要改变的字段的位置序(传输过程中不传递没有改变的信息)
};

class CObjModel;
#define VER_SRVSYNCMAIL_OPERTYPE_EDIT		0		//由编辑引起的同步
#define VER_SRVSYNCMAIL_OPERTYPE_ROLLBACK   1		//由回滚引起的同步
#define VER_SRVSYNCMAIL_OPERTYPE_COMMIT		2		//由提交引起的同步
class SG_CORE_API ObjTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	ObjTransManager();
	virtual ~ObjTransManager();
	
public:
	// --- 清空任务队列
	
	void Reset();


	// --- 增加的对象加入队列
	virtual SG_BOOL ObjAdd(CSgGeoDataSet*pDataSet,SG_LONG row);
	// --- 将pDataSet中的所有成员都加入事务队列
	virtual SG_BOOL ObjsAdd(CSgGeoDataSet*pDataSet);


	// --- 修改的对象加入队列
	virtual SG_BOOL ObjModi(CSgGeoDataSet*pDataSet,SG_LONG	row,ObjTransModiStruct&modiattrib,SG_BOOL bOrigin=false);
	// --- 将pDataSet中的所有成员都加入事务队列
	virtual SG_BOOL ObjsModi(CSgGeoDataSet*pDataSet,SG_BOOL bOrigin=false);


	// --- 删除的对象加入队列
	//RecAllAttrib	为true时将所有的属性记录下来，对于具有可存储高程信息的对象将高程信息记录下来
	//				为false
	virtual SG_BOOL ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row,SG_BOOL RecAllAttrib=false);
	// --- 将pDataSet中的所有成员都加入事务队列
	virtual SG_BOOL ObjsDelete(CSgGeoDataSet*pDataSet);

	/******************获得事务中的对象**************************
	入参：
	   inObjType --设备类型； pTableName--对象的表名
	   inObjID	 --设备ID
	   nEditFlag --参见：枚举值定义，新增：SG_NET_ATTRIB_CREATE	=4,
									修改	：SG_NET_ATTRIB_MODIFY	=5,
									删除：SG_NET_ATTRIB_DELETE	=6,
    出参：
	    outRow --该对象在返回DATASET中的行号
	返回值：
	    该对象所在的DATASET,如果没有，则返回NULL
	**************************************************************/
	virtual CSgGeoDataSet*GetTransObj(SG_SHORT inObjType,SG_INT inObjID,SG_SHORT nEditFlag,SG_INT&outRow);
	//
	virtual CSgGeoDataSet*GetTransObj(char* pTableName,SG_INT inObjID,SG_SHORT nEditFlag,SG_INT&outRow);

	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	//
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	//
	
	CSgObjects* GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgGeoDataSetArray* GetOperDataSetArray(){return m_pObjs;}
	
	
public:
	
//	SG_UCHAR	VersionNo;		// --- 版本号
	
	
	SG_UCHAR	MixFlag;	//0: 为单一编辑态或运行态信息  
							//1:既有编辑态信息也有运行态信息,仅当服务器间同步时会出现
	
	SG_UCHAR	PierceFlag;	//穿透标志

	
	SG_UCHAR	Reserve2;	//预留
	//
	GIS_Schema	SchemeInfo;		//规划方案id
	SG_UINT		TaskNo;			//--- 任务号
	CSgObjects	TaskList;		//和该任务属于同一大版本下的任务列表（用于判定该图素是否锁定）
protected:	
	
	CSgObjects			m_ObjsOperAttrib;		//对象(记录)操作属性
	
	CSgGeoDataSetArray*	m_pObjs;				//操作对象的信息
};

// --- 短事务方式批量处理响应结构

class SG_CORE_API ObjTransReturnStruct:public ModiCommandReturnPara
{
public:
	
	ObjTransReturnStruct();
	~ObjTransReturnStruct();

	// --- 处理对象的数量
	
	void SetSize(SG_INT Nums);
	// --- 增加的对象加入队列
	
	void ObjAdd(CSgGeoDataSet*pDataSet,int row=-1);
	// --- 修改的对象加入队列
	
	void ObjModi(CSgGeoDataSet*pDataSet,int row=-1);
	// --- 删除的对象加入队列
	
	void ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row);
	//
	
	CSgObjects *GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgGeoDataSetArray* GetOperDataSetArray(){return m_pObjs;}

	
	SG_BOOL Serialize(CSgArchive&ar);

	void Reset();

protected:
	
	CSgObjects			m_ObjsOperAttrib;		//对象(记录)操作属性
	
	CSgGeoDataSetArray*	m_pObjs;				//操作对象的信息
};

class ACE_Thread_Mutex;

class SG_CORE_API ObjNetSendStruct:public ObjTransManager
{
public:
	
	ObjNetSendStruct();
	
	~ObjNetSendStruct();
	
	void Reset();
	
	void ObjAdd(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	void ObjModi(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	void ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	CSgObjects *GetObjsMailFlag(){return &m_ObjsMailFlag;}
	//
	
	SG_BOOL Split(CSgPtrArray&ObjsArray);
	//
protected:
	
	void Lock();
	
	void UnLock();
	
	CSgObjects			m_ObjsMailFlag;
	CSgObjects			m_ObjsPierceFlag;
	CSgObjects			m_ObjsVerNo;	
	
	ACE_Thread_Mutex*	m_Lock;
};


class SG_CORE_API DbfTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	DbfTransManager();
	
	~DbfTransManager();
public:
	// --- 清空任务队列
	
	void Reset();
	// --- 增加的对象加入队列
	
	SG_BOOL ObjAdd(CSgDataSet*pDataSet,SG_LONG row);
	// --- 修改的对象加入队列
	
	SG_BOOL ObjModi(CSgDataSet*pDataSet,SG_LONG row,ObjTransModiStruct&modiattrib);
	// --- 删除的对象加入队列
	
	SG_BOOL ObjDelete(CSgDataSet*pDataSet,SG_LONG row);
	//
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	//
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	//
	
	CSgObjects* GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgDataSetArray* GetOperDataSetArray(){return m_pObjs;}

public:
	
/*	SG_UCHAR	VersionNo;		// --- 版本号
	
	SG_UCHAR	Reserve0;	//预留
	
	SG_UCHAR	Reserve1;	//预留
	
	SG_UCHAR	Reserve2;	//预留
*/
	//
protected:	
	
	CSgObjects			m_ObjsOperAttrib;		//对象(记录)操作属性
	
	CSgDataSetArray*	m_pObjs;				//操作对象的信息
};
//

class SG_CORE_API DbfNetSendStruct:public DbfTransManager
{
public:
	
	void Reset();
	
	void ObjAdd(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	void ObjModi(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	void ObjDelete(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	CSgObjects *GetObjsMailFlag(){return &m_ObjsMailFlag;}
protected:
	
	CSgObjects			m_ObjsMailFlag;
};


class SG_CORE_API CommTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	CommTransManager();
	
	~CommTransManager();
	
	void ReSet();
	//收集事务数据 dataType:0-SDE表数据;1-ORACLE表中的数据
	
	void AddSqlClause(CSgString sqlClause);	
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	
	char*	GetErrorInfo(){return m_ErrorInfo.GetSafeBuffer();}
	
	SG_BOOL AddSdeDataSet(CSgGeoDataSet *pDataSet, SG_LONG row=-1){return AddDataSet(pDataSet,0,row);}
	
	SG_BOOL ModiSdeDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return ModiDataSet(pDataSet,0,row);}
	
	SG_BOOL DelSdeDataSet(CSgGeoDataSet *pDataSet,SG_LONG  row=-1){return DelDataSet(pDataSet,0,row);}
	//
	
	SG_BOOL AddDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return AddDataSet(pDataSet,1,row);}
	
	SG_BOOL ModiDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return ModiDataSet(pDataSet,1,row);}
	
	SG_BOOL DelDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG  row=-1){return DelDataSet(pDataSet,1,row);}
	
	
	CSgGeoDataSetArray *GetAddSdeDataSet(){return m_pAddSdeDataSet;}
	
	CSgGeoDataSetArray *GetModiSdeDataSet(){return m_pModiSdeDataSet;}
	
	CSgGeoDataSetArray *GetDelSdeDataSet(){return m_pDelSdeDataSet;}
	
	CSgGeoDataSetArray *GetAddDbfDataSet(){return m_pAddDbfDataSet;}
	
	CSgGeoDataSetArray *GetModiDbfDataSet(){return m_pModiDbfDataSet;}
	
	CSgGeoDataSetArray *GetDelDbfDataSet(){return m_pDelDbfDataSet;}
	
	CSgStringArray	&GetSqlClauses(){return m_sqlArray;}
protected:	
	
	SG_BOOL AddDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0, SG_LONG row=-1);
	
	SG_BOOL ModiDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0,SG_LONG row=-1);
	
	SG_BOOL DelDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0,SG_LONG  row=-1);
	
	CSgString m_ErrorInfo;
private:
	
	CSgGeoDataSetArray *m_pAddSdeDataSet;
	
	CSgGeoDataSetArray *m_pModiSdeDataSet;
	
	CSgGeoDataSetArray *m_pDelSdeDataSet;
	
	CSgGeoDataSetArray *m_pAddDbfDataSet;
	
	CSgGeoDataSetArray *m_pModiDbfDataSet;
	
	CSgGeoDataSetArray *m_pDelDbfDataSet;
	
	CSgStringArray  m_sqlArray;
	
	SG_SHORT sqlNum;
};


class SG_CORE_API CommTransRtnInfo:public CommTransManager
{
public:
	
	CommTransRtnInfo();
	
	~CommTransRtnInfo();
	
/*	SG_UCHAR	RtnValue;		// --- 返回正确还是错误
	
	SG_UCHAR	Reserve1;	//预留
	
	SG_UCHAR	Reserve2;	//预留
	
	CSgString	RtnInfo;	// --- 返回信息,正确时为空,错误时为错误信息
*/	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);

};

//请求不同版本的数据
struct SG_CORE_API ObjAttribResponsePara:public ClientRequestUserInfo,public CNetCmdHead
{
	SG_UCHAR   run_;	//	是否为运行版数据，需要注意的是：如果请求参数中置了 IsWorldLoad 那么此处的标志意味着是否将运行版的数据和编辑版的增量数据进行了合并
	CSgGeoDataSet* pAdd,*pModi;
	CSgObjects* pDel;
	ObjAttribResponsePara(SG_UCHAR is_run=1);
	void SetStatus(SG_UCHAR is_run){run_=is_run;}
	~ObjAttribResponsePara();
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

//请求删除的记录
class SG_CORE_API RequestRefRecords:public ClientRequestUserInfo,public CNetCmdHead
{
public:
    RequestRefRecords();
    ~RequestRefRecords();
    virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
    void Reset();
public:
    CSgObjects  types;      //size=0--请求所有
    CSgObjects	TaskList;
    CSgGeoDataSetArray*	m_pGeoDs;
};
//请求原数据（修改记录的原数据）
class SG_CORE_API RequestOriRecords:public ClientRequestUserInfo,public CNetCmdHead
{
public:
    RequestOriRecords();
    ~RequestOriRecords();
    virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
    void Reset();
public:
    SG_INT   ObjType;      //type--请求数据的设备类型
    CSgObjects	objs;	//--要请求设备的ID集合
    CSgGeoDataSet*	m_pDataSet;
};
//时态服务信息
class SG_CORE_API S_TSrvInfo
{
public:
    virtual SG_BOOL Serialize(CSgArchive&ar,int versionno);
public:
    SG_INT   TSrvNo;      //时态服务器号
	SG_INT	 StartYMD;    //时态服务的起始年月日
	SG_INT	 EndYMD;    //时态服务的终止年月日
    CSgObjects	TaskList;	//时态服务器检查点的列表
	
};

//时态服务信息
class SG_CORE_API S_TSrvInfoList
{
public:
    S_TSrvInfoList();
    ~S_TSrvInfoList();
    virtual SG_BOOL Serialize(CSgArchive&ar,int versionno);
	void Clear();
	int  AddTSrvInfo(S_TSrvInfo &tsrvinfo);
public:
    SG_OBJECTS	TSrvList;	//时态服务器列表
	
};
#endif
