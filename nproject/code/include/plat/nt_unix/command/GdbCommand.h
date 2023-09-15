#ifndef __GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__

#pragma once

#include "csgdataset.h"

#include "NetCommand.h"
#include "command/NetCommandID.h"
#include "command/NetCmdHelper.h"

//==================================================================================================
// 定义规划信息系统中空间引擎的命令
namespace NetCommand
{
	enum GdbCommandID		//	空间引擎的扩展命令，从 100 开始，到 600 结束
	{


		commitVersion					=	VerCmdMin,			//提交版本
		rollBackVersion					=	VerCmdMin+1,		//回滚版本
		updateManSet					=	VerCmdMin+2,		//人工置数
		updateRunStyle					=	VerCmdMin+4,
		QueryDeleteObjs					=	VerCmdMin+5,		//请求删除的记录
		QueryRunVerObjs					=	VerCmdMin+6,		//请求某一设备类型运行版本下对应的记录
		getGdbVerEnable					=	VerCmdMin+7,		//空间引擎是否启用版本
		Ver_readSdetable				=	VerCmdMin+8,		//请求多个objs的3D信息
		Ver_ObjUpdatePierce				=	VerCmdMin+9,		//穿透版本的修改
		Ver_EMObjSync					=	VerCmdMin+10,		//台帐同步消息
		ForceObjModi					=	VerCmdMin+11,		//强制对象修改，收到此命令，将锁定的记录回滚，
																//用新的记录进行修改。该命令不支持几何字段的修改
		Ver_EMDatSetSync				=	VerCmdMin+12,		//台帐同步消息,传过来的是ObjTransManager
		TSrvSaveSnapCmd					=	VerCmdMin+13,		//时态服务器存当前系统快照
		getTSrvInfo						=	VerCmdMin+14,		//获取时态服务的信息
		Ver_ReadDBVerRecord				=	VerCmdMin+15,		//从数据库获取版本的记录
		Ver_FmGetObjLockFlag			=	VerCmdMin+16,		//台帐获取对象是否锁定信息
		TSrvSaveSnapClientCmd			=	VerCmdMin+17,		//时态服务器存当前系统快照,命令自客户端发出
		TSrvReCreateSnapList			=	VerCmdMin+18,		//根据实际数据新生成时间断面信息

		GIS_LOAD_LAYER					=	VerCmdMin+19,		//	加载整个图层的数据,可根据其他信息决定：
		GIS_LOAD_WORLD					=	VerCmdMin+20,		//	根据 WORLDID 加载数据
		GIS_LOAD_ARRAY					=	VerCmdMin+21,		//	根据 ID 列表加载数据
		GIS_LOAD_CELLS					=	VerCmdMin+22,		//	根据网格数组加载数据

		GIS_LOAD_BY_LINES				=	VerCmdMin +23,		//按照传入的几何多边形选择
		GIS_LOAD_BY_PYBLUR				=	VerCmdMin +24,		//按照拼音模糊查询

		readObjAttrib					=	VerCmdMin +25,		//读取设备属性
		objAdd							=	VerCmdMin +26,		//对象新增命令
		objModi							=	VerCmdMin +27,		//对象修改命令
		objDelete						=	VerCmdMin +28,		//对象删除命令
		objTransOper					=	VerCmdMin +29,		//事务操作命令
		
		GIS_LOAD_BY_APDOBJTYPE			=	VerCmdMin +30,		//根据附属设备的类型加载主设备,主设备中具有BASE_OBJ_TYPE字段
		GIS_SCHEMES_TASKDIFF			=	VerCmdMin +31,		//比较两个方案的任务差异
		GIS_ROLLBACK					=	VerCmdMin +33,		//规划项目(或任务)归档
		GIS_GET_RELDAT					=	VerCmdMin +34,		//获得和项目(或任务)相关的数据信息
		GIS_RELDAT_REPLACE				=	VerCmdMin +35,		//和项目(或任务)相关的数据新旧设备更换处理
		GIS_LOAD_BY_MULTICOND			=	VerCmdMin +36,		//根据几何多边形和where条件联合选择数据

		TSrvRepairADTable				=	VerCmdMin+37,		 //时态服务根据实际数据情况修复A/D表中的数据
		TSrvChangeObjsTime				=	VerCmdMin+38,		 //时态服务调整一个设备的产生时间

		GIS_SCHEMES_DIFFOBJ				=	VerCmdMin+39,		 //申请两个版本的差异数据

		GIS_QueryPSRByPoint				=	VerCmdMin+50,		//根据传入的点坐标查询电网地理图中的电网资源信息
		GIS_QueryPSRByCircle			=	VerCmdMin+51,		//根据传入的圆查询电网地理图中的电网资源信息
		GIS_QueryPSRByRect				=	VerCmdMin+52,		//根据传入的矩形查询电网地理图中的电网资源信息
		GIS_QueryPSRByPolygon			=	VerCmdMin+53,		//根据传入的多边形查询电网地理图中的电网资源信息
		GIS_QueryPSRByFather			=	VerCmdMin+54,		//查找子设备的电网资源信息
		GIS_QueryPSRByCompany			=	VerCmdMin+55,		//根据输入的单位ID 统计该单位管辖区域内的电网资源
		GIS_QueryPSRByPYBlur			=	VerCmdMin+56,		//按照拼音模糊查询电网资源

		GIS_LoadByIDArray				=	VerCmdMin+57,		//根据传入的设备id数组，返回需要的设备信息字段
		GIS_LoadByWhereSQL				=	VerCmdMin+58,		//根据WHERE SQL语句，返回需要的设备信息字段

		GIS_QueryLineLengthByCompany	=	VerCmdMin+59,		//根据输入的单位ID,获取线路的总长度

		GIS_LoadModel_ObjType			=	VerCmdMin+60,		//获取设备模型
		GIS_LoadModel_ObjField			=	VerCmdMin+61,		//获取设备的属性

		GIS_QueryEnCloseRectByIDArray	=	VerCmdMin+62,		//根据传入的设备id数组，返回设备的外接矩形
		GIS_LoadDispByIDArray		=	VerCmdMin+63,		//根据传入的设备id数组，返回需要进行显示的设备信息字段
		GIS_LoadDispByWhereSQL		=	VerCmdMin+64,		//根据WHERE SQL语句，返回需要进行显示的设备信息字段
		GIS_QueryPSRByChild			=	VerCmdMin+65,		//查找父设备的电网资源信息
		GIS_QueryChildPSRByLine		=	VerCmdMin+66,		//查找线路的所有电网资源信息

		GAP_GetSeqValue				=	VerCmdMin+67,		//获取ID的序列值
	};
};

//==================================================================================================
//	规划信息系统动态加载命令的通用信息
struct GIS_Common
{
	SG_UINT		WorldID;		//	如果需要加载设备标注，那么该变量参与过滤设备标注
	SG_UINT		ObjectType;		//	要加载的设备类型，如果该设备根据 WorldID 加载，那么仅加载 WorldID 指定的数据
	SG_UINT		LoadType;		//	加载类型，1 加载基本数据、2 扩展数据、3 全数据 ，参加 LoadType 枚举定义
	SG_UINT		Reserved;		//	保留内容，/****是否加载对应的设备标注****/
	ARR_UINT32	AppendObjTypes;	//	跟随加载的相关设备类型列表

	GIS_Common( )
	{
		WorldID			= 0	;
		ObjectType		= 0	;
		LoadType		= 0 ;

		Reserved		= 0	;
		AppendObjTypes.clear();
	}

	inline void operator = ( const GIS_Common & rhs )
	{
		WorldID			= rhs.WorldID		;
		ObjectType		= rhs.ObjectType	;
		LoadType		= rhs.LoadType		;

		Reserved		= rhs.Reserved		;
		AppendObjTypes	= rhs.AppendObjTypes;
	}

	inline int buf_size()
	{
		return BUF_SIZE( 4 , 0 , 0 )+AppendObjTypes.buf_size();
	}

	virtual SG_BOOL		Serialize(CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		
		SERIALIZE_MEMBER( rStream , WorldID			);
		SERIALIZE_MEMBER( rStream , ObjectType		);
		SERIALIZE_MEMBER( rStream , LoadType		);

		SERIALIZE_MEMBER( rStream , Reserved		);
		SERIALIZE_OBJECT( rStream , AppendObjTypes	);
		return true;
	}
};

enum GIS_Common_LoadType
{
	CLT_LOAD_BASIC	= 0x00000001,						//	加载基础字段
	CLT_LOAD_EXTRA	= 0x00000002,						//	加载扩展字段
	CLT_LOAD_ALL	= CLT_LOAD_BASIC|CLT_LOAD_EXTRA,	//  加载全部字段

	CLT_SYNC_APPENDDEV	= 0x00000004,	//	同步加载相关设备
	CLT_ONLY_TABLE		= 0x00000008,	//	仅加载表结构
	CLT_LOAD_COMBIN		= 0x00000010	//  组合加载
};

//==================================================================================================
//	规划信息系统通用的数据请求信息
struct GIS_Schema				
{
	ACE_UINT32 m_nVersion;		//	大版本号，根据大版本号来确定加载的增量数据
	ACE_UINT32 m_nSchema;		//	方案编号，对于时态服务该值存储对应的日期
	ACE_UINT32 m_nSchemaYMD;	//	客户端察看时，选择查看的时间点
								//如果为0，查看的时间点为方案的起始时间
	ACE_UINT32 m_nHighLoadYMD;	//	如果为时态服务，该值不为零，则为最高负荷日的年月日
	ACE_UINT32 m_nHighLoadHMS;	//	如果为时态服务，则为最高负荷发生的时分秒
	
	ARR_UINT32 m_arrScheme;		//	非默认子方案的列表

	inline GIS_Schema()
	{
		m_nVersion	= 0;
		m_nSchema	= 0;
		m_nSchemaYMD= 0;
		m_nHighLoadYMD=0;
		m_nHighLoadHMS=0;
	}

	inline int buf_size()
	{
		return OBJ_SIZE( m_arrScheme ) + BUF_SIZE( 5 , 0 , 0 );
	}

	inline SG_BOOL Serialize( CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		SERIALIZE_MEMBER( rStream , m_nVersion	);
		SERIALIZE_MEMBER( rStream , m_nSchema	);
		SERIALIZE_MEMBER( rStream , m_nSchemaYMD	);
		
		SERIALIZE_OBJECT( rStream , m_arrScheme	);
		SERIALIZE_MEMBER( rStream , m_nHighLoadYMD	);
		SERIALIZE_MEMBER( rStream , m_nHighLoadHMS	);
		return true;
	}

	inline void Assign( const GIS_Schema & rhs )
	{
		if( & rhs == this ) return ;
		
		m_nVersion	= rhs.m_nVersion	;
		m_nSchema	= rhs.m_nSchema		;
		m_nSchemaYMD	= rhs.m_nSchemaYMD	;
		m_nHighLoadYMD	= rhs.m_nHighLoadYMD	;
		m_nHighLoadHMS	= rhs.m_nHighLoadHMS	;
		m_arrScheme	= rhs.m_arrScheme	;
	}

	inline GIS_Schema( const GIS_Schema & rhs )
	{
		Assign( rhs );
	}

	inline GIS_Schema & operator = ( const GIS_Schema & rhs )
	{
		Assign( rhs );
		return * this;
	}

	bool operator == ( const GIS_Schema & rhs ) const
	{
		return	( m_nVersion	== rhs.m_nVersion	)
			 &&	( m_nSchema		== rhs.m_nSchema	)
			 &&	( m_nSchemaYMD	== rhs.m_nSchemaYMD	)
			 &&	( m_nHighLoadYMD== rhs.m_nHighLoadYMD	)
			 &&	( m_nHighLoadHMS== rhs.m_nHighLoadHMS	)
			 &&	( m_arrScheme	== rhs.m_arrScheme	);
	}

	inline void FromString(const char* lpszVerName)
	{
		if(lpszVerName)
		{
			int len = strlen(lpszVerName);
			for(int i=0;i<len;i++) m_arrScheme.push_back(lpszVerName[i]);
		}
	}

	inline void ToString(ACE_CString&strVerName)
	{
		int len = m_arrScheme.size();
		strVerName.resize( len+1 );
		strVerName[len]=NULL;
		for(int i=0;i<len;i++)  strVerName[i] = m_arrScheme[i];
	}

};
typedef struct S_WorkSchemaInfo
{
	GIS_Schema	SchemaInfo;
	int			ProcTaskNo;
}S_WorkSchemaInfo;

//==================================================================================================
//	
struct GIS_Attrib
{
	//	直接调用基类的序列化函数
	inline SG_BOOL Serialize( CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		// 如果是反序列化数据，并且指针不存在
		if( rStream.IsLoading() && lpGeoDataSet == NULL )
		{
			//	申请一个数据集对象
			lpGeoDataSet = new CSgGeoDataSet;
		}

		if( lpGeoDataSet == NULL )
		{
			// 如果对象不存在，序列化空记录集
			CSgGeoDataSet().Serialize( rStream );
		}
		else
		{
			// 直接序列化记录集
			lpGeoDataSet->Serialize( rStream );
		}
		return true;
	}

	// 返回极大值，避免该函数调用
	inline int buf_size()
	{
		return INT_MAX ;
	}

	inline void Release()
	{
		if( lpGeoDataSet )
		{ 
			delete lpGeoDataSet; 
			lpGeoDataSet = NULL; 
		}
	}

	GIS_Attrib() : lpGeoDataSet( NULL ) { }
	~GIS_Attrib() { Release(); }

	CSgGeoDataSet * lpGeoDataSet;
};


struct GIS_LOAD_BASIC_REQ : public CNetCommand
{
	GIS_Common	Common;
	GIS_Schema	Schema;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BASIC_RES : public CNetResponse
{
	GIS_Common	Common;

	GIS_Attrib			dsAttrib;
	GIS_Attrib			dsTblInfo;	//对于仅仅加载基本字段的类，该结构中放设备动态字段的信息
	CSgGeoDataSetArray	dsAppends;	//附加记录集，跟随主设备加载的相关附属设备

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	加载整个图层的数据 , 因为基础信息已经齐备，所以直接空继承，
struct GIS_LOAD_LAYER_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_LAYER_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	根据 WORLDID 加载数据 , 因为基础信息已经齐备，所以直接空继承，
struct GIS_LOAD_WORLD_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_WORLD_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	根据 ID 列表加载数据
struct GIS_LOAD_ARRAY_REQ : public GIS_LOAD_BASIC_REQ
{
	ARR_UINT32	arrObjects;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_ARRAY_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	根据网格数组加载数据
struct GIS_LOAD_CELLS_REQ : public GIS_LOAD_BASIC_REQ
{
	ARR_UINT32	arrCells;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_CELLS_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//	按照附属设备类型加载主设备
struct GIS_LOAD_BY_APDOBJTYPE_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BY_APDOBJTYPE_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//按区域选择对象
struct GIS_LOAD_BYLINES_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;		//规划方案id
	ARR_UINT32	ObjTypes;		//待查询的设备类型
	SG_CHAR		RtnGeometry; 	//是否返回几何属性
	CSgString	ObjAttrib;		//待查询的字段名称
	CSgLine		Range;			//选择的几何范围
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYLINES_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;	//返回记录集
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//按区域+条件选择对象
struct GIS_LOAD_MULTICOND_REQ : public GIS_LOAD_BYLINES_REQ
{
	CSgString	WhereClause;	//条件
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_LOAD_BYLINES_RES GIS_LOAD_MULTICOND_RES ;


struct GIS_LOAD_PYBLUR_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;		//规划方案id
	ARR_UINT32	ObjTypes;		//待模糊查询的设备类型
	SG_CHAR		RtnGeometry; 	//是否返回几何属性
	CSgString	ObjAttrib;		//待模糊查询的字段名称
	CSgString	KeyWord;		//模糊查询关键字
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_PYBLUR_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;	//返回记录集
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


struct GIS_SCHEMES_TASKDIFF_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo1;		//规划方案1
	GIS_Schema	SchemeInfo2;		//规划方案2
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_SCHEMES_TASKDIFF_RES : public CNetResponse
{
	ARR_UINT32	TaskList_Scheme1;		//在规划方案1中，不在规划方案2的任务
	ARR_UINT32	TaskList_Scheme2;		//在规划方案2中，不在规划方案1的任务
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


//请求差异信息
struct GIS_SCHEMES_DIFFOBJ_REQ : public CNetCommand
{
	ARR_UINT32	ObjTypes;			//需要的设备类型,如果个数为0，则所有对象全部搜索
	GIS_Schema	SchemeInfo1;		//规划方案1
	GIS_Schema	SchemeInfo2;		//规划方案2
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//请求差异信息返回
struct GIS_SCHEMES_DIFFOBJ_RES : public CNetResponse
{
	CSgDataSetArray_ObjOper		DiffObjs;		//差异对象列表
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


struct GIS_LOADFDU_REQ  : public  CNetCommand
{
public:
	GIS_Schema		SchemeInfo;
	SG_SHORT		FDM_ID;			//FDM的ID号
	SG_UCHAR		HasScatterFDU;
	ACE_UINT32		WorldID;		//客户端申请的WorldID号
	SG_OBJECTS		Base_FDUArray;	//基表的FDU数组(BASE_OBJ_TYPE,BASE_OBJ_ID)
	SG_OBJECTS		Ver_FDUArray;	//当前大版本下A表FUD数组(BASE_OBJ_TYPE,BASE_OBJ_ID)

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_LOAD_PYBLUR_RES GIS_LOADFDU_RES;

#define GIS_ROLLBACK_TYPE_TASK	1	//任务归档
#define GIS_ROLLBACK_TYPE_PRJ	2	//项目归档
struct GIS_ROLLBACK_REQ : public CNetCommand
{
public:
	GIS_Schema		SchemeInfo;		//规划应用环境
	SG_SHORT		RollBackType;	//1:任务归档   2:项目归档
	SG_INT			RollBackID;		//需要回滚的任务或项目的ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_ROLLBACK_RES : public CNetResponse
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

#define GIS_RELDAT_OPERMODE_DEL			1	//删除相关的数据
#define GIS_RELDAT_OPERMODE_REPLACE		2	//将相关数据中的 源对象改为目的对象

typedef  GIS_ROLLBACK_REQ	GIS_GET_RELDAT_REQ;

struct GIS_GET_RELDAT_RES : public CNetResponse
{
	CSgDataSet	RelDat;		//含有字段为TABLE_NAME	OPERMODE OBJTYPE OBJID
public:
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_RELDAT_REPLACE_REQ : public CNetCommand
{
public:
	GIS_Schema		SchemeInfo;		//规划应用环境
	SG_SHORT		RollBackType;	//1:任务归档   2:项目归档
	SG_INT			RollBackID;		//需要回滚的任务或项目的ID
	CSgDataSet		RelDat;		//含有字段为TABLE_NAME	OPERMODE SRC_OBJTYPE SRC_OBJID DES_OBJTYPE DES_OBJID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_RELDAT_REPLACE_RES : public CNetResponse
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct TSRV_CHG_OBJSTIME_REQ
{
public:
	SG_INT			SrcYMD;			//需要调整设备的原始时间
	SG_INT			DesYMD;			//需要调整设备的原始时间
	SG_SHORT		ObjType;		//设备类型,如果为-1,则为所有的设备类型
	SG_INT			ObjKID;			//设备kid,如果为-1,则为该类型的所有设备
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//获取SequenceID值
struct GAP_GETSEQVALUE_REQ : public CNetCommand
{
	CSgString		SeqName;
	SG_INT			WorkSpace;
	SG_UINT			Cnt;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GAP_GETSEQVALUE_RES : public CNetResponse
{
	CSgObjects			ObjIDS;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	根据定义要求决定是否将函数实现内联
#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/GdbCommand.inl"
#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
