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
//统一的一个数据类型
#define		DEF_RDB_MAXSTRLEN    4096
//---------------------------------------------------------------------------

//实时库中域的模式
#define SG_RDB_FIELDMODE_PARA  0
#define SG_RDB_FIELDMODE_DATA  1
#define SG_RDB_FIELDMODE_MEM	2


#define SG_RDB_PARATBLNUM 2  //实时库支持从SG_RDB_PARATBLNUM张参数表中加载一个实时库表
#define SG_RDB_RELTBLNUM  5
#define SG_RDB_RMEMFILE_VERSION		1
#define	SG_RDB_RMEM_GETVERSION(VERSION) 	if(VERSION<0) { VERSION=SG_RDB_RMEMFILE_VERSION; if(VERSION<0) return false; }




typedef union USG_RDB_NUMVAR
{
	SG_INT64     IntVal;
	double		DblVal;
}USG_RDB_NUMVAR;

//---------------------------------------------------------------------------
//一个完整数据类型
//---------------------------------------------------------------------------
typedef struct SG_RDB_DATVAR
{
	short			DatType;
	USG_RDB_NUMVAR  NumVal;
	std::string		StrVal;
}SG_RDB_DATVAR;


#define SG_FIELDNAMEDES_LEN sizeof(SG_FIELDNAMEDES)
#define SG_RTBL_PROCMODE_VALTBL				0x00000001		//本地加载时,是否能备份值表
#define SG_RTBL_PROCMODE_LOAD_SUB				0x00000002		//加载时,增量加载标志
#define SG_RTBL_PROCMODE_SAVEHIS_BYCHAN		0x00000004		//是否根据变化存储历史数据
#define SG_RTBL_PROCMODE_INMINIBOX				0x00000008		//该表是否存在于微盒子中
#define SG_RTBL_PROCMODE_PERIODCHECK			0x00000010		//该表是否周期检查
#define SG_RTBL_PROCMODE_SYNC_NOLACK			0x00000020		//该表无缺同步，对遥信表这样处理
#define SG_RTBL_PROCMODE_SYNC_FATHERDB			0x00000040		//该表字段改变会回写上级数据库

typedef struct SRDB_RTBLINFO_PARA
{
	SG_FIELDNAME		TblCode;         //实时库表名
	SG_FIELDNAMEDES		TblDesc;			//实时库表描述
	SG_FIELDNAME		KeyField;			//主键名称,现在仅支持单主键的表
	SG_FIELDNAMEDES		WorkSpaceField;//参数数据库中公司id字段名
	SG_FIELDNAMEDES		DatLevelField;//参数数据库中数据等级字段名
	SG_FIELDNAMEDES		ParaTbl[SG_RDB_PARATBLNUM];		//参数表1的名称 现在支持用两个表union成一个实时表
	SG_FIELDNAMEDES		DataTbl;		//数据表名称
	SG_FIELDNAMEDES		RelTbl[SG_RDB_RELTBLNUM];		//相关参数表1名称,即该参数表改变后,重新加载该表
														//	SG_FIELDNAMEDES		RelTbl2;		//相关参数表2称,即该参数表改变后,重新加载该表
	//SG_FIELDNAME	ParaTblFlagField;	//放是从一表加载还是二表加载的域名称,域是一个整形值
	SG_MSG			ParaAppendSQL;	//参数表加载时的附加SQL语句
	SG_INT			TblID;		//实时库表ID
	SG_INT			LoadSrvType;	//加载的服务类型
	SG_INT			BatchNo;	//读取时的批处理号
	SG_INT			ObjType;		//实时库表的对象类型  如无对象,则为-1
	SG_UINT64			MaxKey;	//主键最大值
	SG_UINT64			MinKey;	//主键最小值
	SG_INT			BackupTime;			//备份数据表的时间
	SG_INT			L_BackupTime;			//本地备份数据表的时间
	SG_INT			SaveHisPeriod;			//存储历史数据表的时间
	SG_INT			ProcMode;				//表处理模式 
	SG_INT			MaxRcdNum;		//中央数据库中的最大纪录个数,在形成数据库时,读库中的不同字段
	SG_INT			LogicCellType;		//逻辑数据单元的类型
	SG_INT			LogicCellWorkSpaceNum;	//逻辑数据单元使用WorkSpace的最大个数
	SG_SHORT		KeyFieldNo; //主键域是第几个字段 如果为-1 表明该表没有主键
	SG_SHORT		WorkSpaceFieldNo; //WorkSpace域是第几个字段 如果为-1 表明该表没有WorkSpqce字段
	SG_SHORT		DatLevelFieldNo; //数据等级域是第几个字段 如果为-1 表明该表没有数据等级字段
	SG_SHORT		FieldNum; //字段个数
	SG_SHORT		IdxNum;	 //该表有多少个索引
	SG_SHORT		RcdLen;  //记录长度
	SG_UCHAR		LoadPTblNum;	//加载参数表的个数
	SG_UCHAR		LoadRelTblNum;	//加载相关表的个数
	SG_UCHAR		HasUpdateTimeFlag;	//是否需要附加修改时间信息标志
	SG_UCHAR		HasDatLevel;	//是否有数据等级信息
	int InitDat();
	SG_INT	Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	SG_BOOL Equal(SRDB_RTBLINFO_PARA &p);
}SRDB_RTBLINFO_PARA;
typedef struct SRDB_RTBLINFO_DATA
{
	SG_UCHAR		 WriteFlag;      //写数据标志,此时不要对数据库读写,即此时会改变表的大小
	SG_UCHAR		 LoadFlag;     //表重新加载的标志
	SG_UINT64			 RealMinKey;	//实际的主键最大值
	SG_UINT64			 RealMaxKey;	//实际的主键最小值
	SG_UINT TblKeyChangeVer;	//该表主键改动的版本,用于重建主键索引用
	SG_UINT		TblChangeVer; //该表改动的版本,用于重建普通索引用与动态索引
	SG_UINT		RcdChangeTime; //该表记录改动的时间(绝对毫秒),用于发送变化数据
	SG_INT		RcdNum;
	SG_INT		TblOffset;		 //该表在表信息中的位置
	SG_INT		FieldInfoOffset; //该表的域的偏移号
	SG_INT		IdxInfoOffset; //该表的索引的偏移号	
	SG_INT64	RcdOffset; //该表的数据起始字节偏移
	SG_INT64	UpdateTimeOffset; //该表的修改时间的偏移
	SG_INT64	WriteProcID; //给实时库加锁的进程ID

	int InitDat(SG_INT64 MaxKey);
	//SG_INT	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
}SRDB_RTBLINFO_DATA;
typedef struct SRDB_SCHEMAINFO
{
	SG_INT64	SchemaHandle;	//实时库句柄 全系统唯一
	SG_INT		SchemaDBNo;		//在rtdb_dbinfo中的定义
	SG_INT		ShareMemKey;	//共享内存Key值
	SG_INT		SDBType;		//实时库类型 0：运行内存库 1：研究态内存库 2：算例实时数据
	SG_INT		UserCnt;		//当前进程用户个数，当进程用户个数为0时，并且该内存是可删除的，则可以删除这个共享内存
	SG_UINT		ProcMode;		//处理模式 bit0:1非常驻内存
	SG_INT		ValidFlag;		//有效标志
	SG_UINT		LastUseTime;	//最后使用时间
	SG_INT64	ManageProcID;   //管理ProcID是否也加入
}SRDB_SCHEMAINFO;

//实时库基类
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
	//映射共享内存,并不建立它
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