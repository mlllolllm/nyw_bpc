#ifndef __GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__

#pragma once
#include "csgdataset.h"

#include "NetCommand.h"
#include "command/NetCommandID.h"
#include "command/NetCmdHelper.h"
#include "command/GdbCommand.h"
//目前这些命令的处理仅考虑基版本
struct	GIS_QUERYPSR_BASEINFO
{
	GIS_Schema		SchemeInfo;		//规划方案id
	ARR_UINT32		ObjTypes;		//待查询的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_CHAR			WholeContain;	//是否全包含
	SG_CHAR			SearchAll;		//是否全部进行搜索
	SG_FLOAT		Tolerance;		//选择容差
	SG_DOUBLE		WorldScale;		//如果不是全部搜索，则根据显示比例尺找出搜索那套网格索引
	SG_INT			MaxSelObjNum;	//最多选择的设备类型个数
	GIS_QUERYPSR_BASEINFO()
	{
		WholeContain=0;
		SearchAll=1;
		WorldScale=1.0;
		Tolerance=0.0;
		MaxSelObjNum=5000;
	};
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//获取设备类型列表
struct GIS_LOADMODEL_OBJTYPE_REQ: public CNetCommand
{
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_LOADMODEL_OBJTYPE_RES: public CNetResponse
{
	CSgDataSet		ObjTypes;							// 包含三个字段 OBJTYPE,NAME,DESC
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//获取设备类型的字段信息
struct GIS_LOADMODEL_OBJFIELD_REQ: public CNetCommand	// 包含四个字段 NAME,DESC,FIELDTYPE,FIELDLEN
{
	SG_INT		ObjType;	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADMODEL_OBJFIELD_RES: public CNetResponse
{
	CSgDataSet		ObjFields;	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//选择操作返回
struct GIS_QUERYPSR_RES : public CNetResponse
{
	SG_OBJECTS		SelObject;						//返回选择的记录集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//按点选择对象
struct GIS_QUERYPSR_BYPOINT_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO				ReqBaseInfo;	//选择资源的基本信息
	SgPoint								CenterPoint;	//输入的中心点
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYPOINT_RES;
//按矩形选择对象
struct GIS_QUERYPSR_BYRECT_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO				ReqBaseInfo;	//选择资源的基本信息
	SgRect								SelRect;		//输入的矩形
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYRECT_RES;
//按圆选择对象
struct GIS_QUERYPSR_BYCIRCLE_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO	    ReqBaseInfo;			//选择资源的基本信息
	SgPoint						 CenterPoint;			//圆心
	SG_DOUBLE					 Circle_R;				//圆的半径
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYCIRCLE_RES;

//按区域选择对象
struct GIS_QUERYPSR_BYPOLYGON_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO	    ReqBaseInfo;		//选择资源的基本信息
	CSgLine						 Range;				//选择的几何范围
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYPOLYGON_RES;
//根据父设备返回其子设备的信息
struct GIS_QUERYPSR_BYFATHER_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//规划方案id
	ARR_UINT32		ObjTypes;						//待查询的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_OBJECT		FatherObj;						//父设备对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYFATHER_RES;
//根据线路设备返回其子设备的信息
typedef GIS_QUERYPSR_BYFATHER_REQ GIS_QUERYPSR_BYLINE_REQ;
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYLINE_RES;

//根据单位返回其子设备的信息
struct GIS_QUERYPSR_BYDEPARTMENT_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//规划方案id
	ARR_UINT32		ObjTypes;						//待查询的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_INT				Department;					//公司号
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYDEPARTMENT_RES;

//按照拼音进行模糊搜索
struct GIS_QUERYPSR_BYPYBLUR_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//规划方案id
	ARR_UINT32		ObjTypes;						//待查询的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	CSgString	ObjAttrib;							//待模糊查询的字段名称
	CSgString	KeyWord;							//模糊查询关键字
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//按照拼音进行模糊搜索返回
struct GIS_QUERYPSR_BYPYBLUR_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;						//返回选择的记录集  包含字段OBJTYPE,OBJID,ObjAttrib(待模糊查询的字段名称)
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};


//按设备ID组，返回需要的字段信息
struct GIS_LOAD_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//规划方案id
	SG_SHORT		ObjType;						//设备类型
	ARR_UINT32	ObjIDs;								//需要查询的设备ID
	SG_UCHAR			RtnGeometry; 				//是否返回几何属性
	SG_UCHAR		HasTransDat;					//是否需要翻译数据Datset
	CSgString		ObjAttribs;						//待查询的字段名称
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYIDARRAY_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;					//返回记录集 如果有仅仅的翻译字段数据集，则返回两个datset,这两个数据集记录个数完全相同
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//按设备ID组，返回需要显示的字段信息
struct GIS_LOADDISP_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//规划方案id
	SG_SHORT		ObjType;						//设备类型
	ARR_UINT32		ObjIDs;							//需要查询的设备ID
	CSgString		ObjAttribs;						//待查询的字段名称,返回的记录集字段排序和它有可能不符
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADDISP_BYIDARRAY_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;					//返回记录集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//按sql条件，返回需要的字段信息
struct GIS_LOAD_BYSQL_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//规划方案id
	SG_SHORT		ObjType;						//设备类型
	SG_UCHAR		HasTransDat;					//是否需要翻译数据Datset
	SG_UCHAR		RtnGeometry; 					//是否返回几何属性
	CSgString		ObjAttribs;						//待查询的字段名称
	CSgString		WhereClause;					//条件子句
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYSQL_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;				//返回记录集，如果有仅仅的翻译字段数据集，则返回两个datset,这两个数据集记录个数完全相同
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//按sql条件，返回需要显示的字段信息
struct GIS_LOADDISP_BYSQL_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//规划方案id
	SG_SHORT		ObjType;						//设备类型
	CSgString		ObjAttribs;						//待查询的字段名称
	CSgString		WhereClause;					//条件子句
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADDISP_BYSQL_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;				//返回记录集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//根据单位返回其线路的长度信息
struct GIS_LINELENGTH_BYDEPARTMENT_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		ObjTypes;					//待查询的设备类型，如果ObjTyps.size<=0 则返回所有线路
	SG_INT				Department;				//公司号
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//选择操作返回
struct GIS_LINELENGTH_BYDEPARTMENT_RES : public CNetResponse
{
	SG_DOUBLE			TotalLength;	//总长度
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//按设备，返回这些设备的外接矩形
struct GIS_QUERYRECT_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;						//规划方案id
	SG_OBJECTS	Objects;						//设备类型
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_QUERYRECT_BYIDARRAY_RES : public CNetResponse
{
	SgRect				EncloseRect;		//外接矩形
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//根据子设备返回其父设备的信息
struct GIS_QUERYPSR_BYCHILD_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//规划方案id
	ARR_UINT32		ObjTypes;						//待查询的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_OBJECTS		ChildObj;						//子设备对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//根据子设备返回其父设备的信息
struct GIS_QUERYPSR_BYCHILD_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//包含三个字段 OBJ_TYPE ID PTYPE PID 
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

#define GIS_TOPO_SPCOSTTYPE_NULL		0	//无条件
#define GIS_TOPO_SPCOSTTYPE_LINGTH		1	//管道长度
#define GIS_TOPO_SPCOSTTYPE_CABLENUM	2	//经过管道最少
//管网最短路径分析
struct GIS_TOPO_SHORTPATH_CABLE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		ObjTypes;					//待返回的管网设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_UCHAR			CalMode;				//计算模式  1:道路最短  2:经过管道最少
	SG_UCHAR			JudgePipeUse;			//考虑管孔的可用性
	SG_SHORT			UsePipeNum;				//本次需要的管孔个数   缺省为1
	SG_OBJECT			StartObj;				//起始管道设备
	SG_OBJECT			EndObj;					//终止管道设备
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//管网最短路径分析返回
struct GIS_TOPO_SHORTPATH_CABLE_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//包含三个字段 OBJTYPE OBJID PIPEID 
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//道路最短路径分析
struct GIS_TOPO_SHORTPATH_ROAD_REQ : public CNetCommand
{
	ARR_UINT32		ObjTypes;					 //待返回的管网设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SgPoint				StartPos;				//起始位置
	SgPoint				EndPos;					//终止位置
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//道路最短路径分析返回
struct GIS_TOPO_SHORTPATH_ROAD_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//经过的道路 包含两个字段 ID,NAME
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//连通性分析
struct GIS_TOPO_CONNECTIVITY_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	SG_UCHAR			ConsiderKGStatus;		//是否考虑开断性设备的状态
	SG_UCHAR			SearchInStation;		//仅在站内搜索   0：站内站外都搜  1：仅在站内搜   2：仅在站外搜
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT			Obj1;					//对象1
	SG_OBJECT			Obj2;					//对象2
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//连通性分析
struct GIS_TOPO_CONNECTIVITY_RES : public CNetResponse
{
	SG_SHORT			ConnectFlag;	//是否连通
	SG_OBJECTS		SelObject;	//返回经过的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//供电范围分析
struct GIS_TOPO_SUPPLYRANGE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	ARR_UINT32		StopObjTypes;		  		//搜索停止的设备类型，如果ObjTyps.size<=0 则不按此判断进行搜索停止
	SG_UCHAR			ConsiderKGStatus;		//是否考虑开断性设备的状态
	SG_UCHAR			SearchInStation;		//仅在站内搜索   0：站内站外都搜  1：仅在站内搜   2：仅在站外搜
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//供电范围分析返回
struct GIS_TOPO_SUPPLYRANGE_RES : public CNetResponse
{
	SG_OBJECTS		SelObject;	//返回经过的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//供电半径分析
struct GIS_TOPO_SUPPLYRADIUS_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	SG_UCHAR			ConsiderKGStatus;		//是否考虑开断性设备的状态
	SG_UCHAR			RuleType;				//搜索规则   1：主干线  2：全长
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//供电半径返回
struct GIS_TOPO_SUPPLYRADIUS_RES : public CNetResponse
{
	SG_DOUBLE			PowerSupplyRadius;		//供电半径
	SG_OBJECTS		SelObject;					//返回经过的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//电源点分析
struct GIS_TOPO_POWERSOURCE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	ARR_UINT32		StopObjTypes;		  		//搜索停止的设备类型，如果ObjTyps.size<=0 则不按此判断进行搜索停止
	SG_UCHAR			ConsiderKGStatus;		//是否考虑开断性设备的状态
	SG_UCHAR			SearchInStation;		//仅在站内搜索   0：站内站外都搜  1：仅在站内搜   2：仅在站外搜
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//电源点分析返回
struct GIS_TOPO_POWERSOURCE_RES : public CNetResponse
{
	SG_OBJECT			PowerSourceObj;			//电源设备
	SG_OBJECTS		SelObject;					//返回经过的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//停电范围分析
struct GIS_TOPO_OUTAGERANGE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		StopObjTypes;		  		//搜索停止的设备类型，如果ObjTyps.size<=0 则不按此判断进行搜索停止
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//停电范围返回
struct GIS_TOPO_OUTAGERANGE_RES : public CNetResponse
{
	SG_OBJECTS		OnPowerObject;					//返回开关动作后有电的设备集
	SG_OBJECTS		OffPowerObject;					//返回开关动作后停电的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//电缆线路走廊分析
struct GIS_CABLELINECORRIDOR_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//规划方案id
	SG_OBJECT			CableObj;					//需要分析的电缆对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//电缆线路走廊分析返回
struct GIS_CABLELINECORRIDOR_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;						//经过的道路 包含两个字段 OBJTYPE,OBJID,PIPEID
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//---------------------------------------------------------------------------------------------------
//道路最短路径分析
struct GIS_TOPO_SHORTPATH_ROAD_NEW_REQ : public CNetCommand
{
	SgPoint				StartPos;				//起始位置
	SgPoint				EndPos;					//终止位置
	CSgPoint			AvoidPos;				//避让点
	CSgPoint			PathPos;				//必经点
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
#define GIS_TOPO_ROAD_PASSPOS_NOT		0	//非必经点
#define GIS_TOPO_ROAD_PASSPOS_START		1	//必经点是路径中这个路段的起始点
#define GIS_TOPO_ROAD_PASSPOS_END		2	//必经点是路径中这个路段的终止点
//道路最短路径分析返回
struct GIS_TOPO_SHORTPATH_ROAD_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//经过的道路 包含两个字段 OBJ_TYPE,ID,PTYPE,PID,NAME,FLAG,PASSPOS_FLAG,PASSPOS_X,PASSPOS_Y
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
#define		GIS_TOPO_CONNECT_ANALYSETYPE_ONESIDE	1		//单向连通性分析
#define		GIS_TOPO_CONNECT_ANALYSETYPE_BOTHSIDE	2		//多向连通性分析
#define		GIS_TOPO_CONNECT_ANALYSETYPE_PATH		3		//路径连通性分析
#define		GIS_TOPO_CONNECT_ANALYSETYPE_TWOPOS		4		//两点连通性分析
#define		GIS_TOPO_CONNECT_ANALYSETYPE_DIRECTLINK	5		//直连分析
//连通性分析
struct GIS_TOPO_CONNECTIVITY_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//规划方案id
	SG_UCHAR		AnalyseType;			//分析类型
	ARR_UINT32		RtnObjTypes;		  	//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_UCHAR		OverVoltLevel;			//跨电压等级
	SG_UCHAR		ConsiderKGStatus;		//是否考虑开断性设备的状态
	CSgDataSet		UserKGStatus;			//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	ARR_UINT32		StopObjTypes;			//停止的设备类型
	SG_OBJECTS		StopObjs;				//边界设备集，即搜到以下设备就停止
	SG_OBJECT		Obj1;					//对象1
	SG_OBJECT		Obj2;					//对象2
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//连通性分析
struct GIS_TOPO_CONNECTIVITY_NEW_RES : public CNetResponse
{
	SG_SHORT		ConnectFlag;	//是否连通
	CSgDataSet		RtnDatSet;		//返回设备集  字段：OBJ_TYPE ID ISTLINK  ISTERM
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//连通性分析
struct GIS_TOPO_MULTICONNECTIVITY_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//规划方案id
	SG_UCHAR		AnalyseType;			//分析类型
	ARR_UINT32		RtnObjTypes;		  	//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	SG_UCHAR		OverVoltLevel;			//跨电压等级
	SG_UCHAR		ConsiderKGStatus;		//是否考虑开断性设备的状态
	CSgDataSet		UserKGStatus;			//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	ARR_UINT32		StopObjTypes;			//停止的设备类型
	SG_OBJECTS		StopObjs;				//边界设备集，即搜到以下设备就停止
	SG_OBJECTS		Objs;					//分析对象，需大于1个设备对象	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_TOPO_CONNECTIVITY_NEW_RES GIS_TOPO_MULTICONNECTIVITY_RES;
//供电范围分析
struct GIS_TOPO_SUPPLYRANGE_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	ARR_UINT32		StopObjTypes;		  		//搜索停止的设备类型，如果ObjTyps.size<=0 则不按此判断进行搜索停止
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT		StartObj;				//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//供电范围分析返回
struct GIS_TOPO_SUPPLYRANGE_NEW_RES : public CNetResponse
{
	SG_OBJECTS		RtnObjects;	//返回经过的设备集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//供电半径分析
struct GIS_TOPO_SUPPLYRADIUS_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//规划方案id
	SG_UCHAR		OverKGStation;			//是否跨越开关站
	CSgDataSet		UserKGStatus;			//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECTS		PowerObjs;				//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//供电半径返回
struct GIS_TOPO_SUPPLYRADIUS_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;			//返回供电半径的信息  字段：OBJ_TYPE ID TERM_OBJTYPE TERM_OBJID LINE_OBJTYPE,LINE_OBJID RADIUS
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//电源点分析
struct GIS_TOPO_POWERSOURCE_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  		//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	ARR_UINT32		VoltLevels;					//搜索的电压等级范围
	ARR_UINT32		StopObjTypes;		  		//搜索停止的设备类型，如果ObjTyps.size<=0 则不按此判断进行搜索停止
	CSgDataSet		UserKGStatus;				//模拟的开关状态信息 有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECTS		TermObjs;					//开始分析的对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//电源点分析返回
struct GIS_TOPO_POWERSOURCE_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;				//返回设备集 有字段: TERM_OBJTYPE,TERM_OBJID,POWER_OBJTYPE,POWER_OBJID,PATH_OBJTYPE,PATH_OBJID
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//供电路径分析
struct GIS_TOPO_SUPPLYPATH_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;					//规划方案id
	ARR_UINT32		RtnObjTypes;		  	//待返回的设备类型，如果ObjTyps.size<=0 则返回所有的对象
	CSgDataSet	    UserKGStatus;			//模拟的开关状态信息有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECT		PowerObj;				//电源对象
	SG_OBJECT		TermObj;				//终端对象
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//供电路径分析
struct GIS_TOPO_SUPPLYPATH_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//返回设备集 字段：OBJ_TYPE ID ISTLINK  ISTERM
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//大用户供电关系分析
struct GIS_TOPO_GDD_POWERSOURCE_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;					//规划方案id
	CSgDataSet	    UserKGStatus;			//模拟的开关状态信息有三个字段OBJTYPE,OBJID,FLAG
	SG_OBJECTS		GDDObjs;				//供电点对象集
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//大用户供电关系分析
struct GIS_TOPO_GDD_POWERSOURCE_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//返回设备集 字段：供电点设备类型(OBJ_TYPE)  供电点ID(ID) 
	                                //是否有电缆线路(HAS_CABLELINE) 是否有架空线路(HAS_OVERHEADLINE) 是否直供线(IS_SPECIAL)
	                                //站设备类型(STATION_OBJTYPE) 站ID(STATION_OBJID) 线路设备类型(LINE_OBJTYPE) 线路ID(LINE_OBJID)
	                                //开关类型(BREAK_OBJTYPE) 开关ID(BREAK_OBJID)   变压器类型(TRANS_OBJTYPE) 变压器ID(TRANS_OBJID)
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//获得对象的控制属性
struct GIS_TOPO_GETCTRLATTRIB_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//规划方案id
	SG_INT			ObjType;					//对象类型
	CSgString		Where;						//过滤条件
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//获得对象的控制属性
struct GIS_TOPO_GETCTRLATTRIB_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//返回设备集 字段：设备ID(ID) 控制属性(FLAG) 所属电源(SYSNO) 线路(LINENO)
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//转供路径分析对比
struct GIS_TOPO_TRANSPATH_REQ : public CNetCommand
{	
	CSgDataSet	    ObjDevStatus;	//转供路径设备有三个字段OBJTYPE,OBJID,FLAG,其中第零条记录为电源，最后一条为受点设备，电源电压等级不小于受电设备电压等级
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_TOPO_TRANSPATH_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//返回设备集 字段：设备类型(OBJTYPE)、设备ID(OBJID) 路径号(PATHNO)-从零开始
	SG_SHORT		LineNo;			//最优路径序号
	CSgLine			PathLine;		//最优路径几何位置
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//业扩报装 搜索电源点
struct GIS_TOPO_SEARCHPOWER_YKBZ_REQ : public CNetCommand
{	
	GIS_Schema		SchemeInfo;		//规划方案id
	SgPoint						 CenterPoint;			//报装点坐标
	SG_DOUBLE					 Circle_R;				//搜索半径
	SG_INT						VoltLevel;				//电压等级
	ARR_UINT32		GDDObjTypes;		//供电点类型
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_TOPO_SEARCHPOWER_YKBZ_RES : public CNetResponse
{
	CSgDataSetArray		PathObjDatSetArray;		//返回设备集,每个DataSet是一个方案的设备路径  字段：设备类型(OBJTYPE)、设备ID(OBJID)  路径号(PATHNO)-从零开始  第一个设备是供电点  最后一个设备是电源点
	CSgGeoDataSet       PathCoordinate;			//字段:方案序号(NO,从0开始)  几何字段,每条记录对应一个方案,记录序号和PathObjDatSetArray的DataSet序号匹配
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};


//==================================================================================================
struct GIS_STAT_ANALYSE_REQ : public CNetCommand
{
	CSgString	Field;			//	统计的字段，为空则统计几何坐标
	CSgString	Where;			//	统计条件，为空则不过滤
	ACE_UINT32	ObjType;		//	设备类型，容器类设备则统计线类型的子设备

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_STAT_ANALYSE_RES : public CNetResponse
{
	double	Result;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_SYMBOL_REQ : public CNetCommand
{
	ACE_UINT32 DisplaySchema , ObjType ;		//	显示方案与设备类型

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_SYMBOL_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;		//	

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_LABEL_REQ : public CNetCommand
{
	CSgRect	Extent;				//	视野范围
	ARR_UINT32	ObjTypes;		//	设备类型
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_LABEL_RES : public CNetResponse
{
	CSgGeoDataSet RtnDatSet;	//	标注 ID , NAME , Geometry;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//==================================================================================================
//	根据定义要求决定是否将函数实现内联
#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/GGisCommand.inl"
#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__
