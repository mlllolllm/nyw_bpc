// const.h
//
/*****************************************************************
	系统的常量定义
			Part 10 数据类型定义
			Part 20 域类型定义
			Part 30 常用字符串结构及其长度定义
			Part 40 系统限制定义
			Part 50 系统特定域名定义
			Part 60 系统控制域名定义----元数据部分
			Part 70 系统控制域名定义----GIS的系统级别表
			Part 80 网络通信用相关定义
*****************************************************************/
#if defined(_MSC_VER)
#   pragma warning(disable:4267)
#	ifdef _DEBUG
#		pragma warning(disable:4231)
#		pragma warning(disable:4244)
#		pragma warning(disable:4018)
#	endif
#endif /* _MSC_VER */


#if !defined(SgConst_h)
#define SgConst_h

#if ! defined( ACE_Proper_Export_Flag )
#	include "ace/config.h"
#endif

#if defined(_LIB) || defined(_USE_CPP_)
	#define SG_CORE_API  
	#define SG_CORE_TEMPLATE
#else
	#if defined(CORE_BUILD_DLL)
		#define SG_CORE_API ACE_Proper_Export_Flag
		#define SG_CORE_TEMPLATE 
	#else
		#define SG_CORE_API ACE_Proper_Import_Flag
		#define SG_CORE_TEMPLATE extern
	#endif
#endif

//  2006-04-11,增加预编译控制_USE_CPP_，运行直接包含CPP文件的工程
#if defined(_LIB) || defined(_USE_CPP_)
	#define _DATASET_DLL_EXPORT_  
	#define _TEMPLATE_EXPORT_ 
#else
	#if defined(_DATASET_DLL_)
		#define _DATASET_DLL_EXPORT_ ACE_Proper_Export_Flag
		#define _TEMPLATE_EXPORT_ 
	#else
		#define _DATASET_DLL_EXPORT_ ACE_Proper_Import_Flag
		#define _TEMPLATE_EXPORT_
	#endif
#endif

//#include "sys_tabledef.h"

#define		PI			3.1415926535897932384626433832795
#define     EARTH_RADIUS  6378137.0
// --- 正常运行方式屏蔽字
#define		NORMAL_RUNSTYLE_MASK_VALUE		0x01
// --- 开关设备错误的状态返回值
#define		ERROR_BREAK_STATUS				100

// --- 镜像对象起始类型
#define	ObjMirrorStartID		20000
#define	ObjShadowStartID		40000
#define	ObjShadowLastID			60000

#define DISTANCE_ZERO				6.2e-9	// 1.e-6,如果距离小于DISTANCE_ZERO，则认为该距离为0(单位米)
#define SG_MAX_EDGE_TOLERANCE		0.000001		//复杂边上的点最大容差范围(单位米)
#define SG_PRINT_ZERO               10          // 最小的打印0.1mm
#define SG_SYMBOL_PART_EXTENT       5.0         // 每个符号状态的限定范围   
#define SG_SYMBOL_MAX_STATUS_NUMS   32
#define SG_DEFAULT_Z_VALUE			-19999.0		//缺省的高程值
/******************************************
	Part 10		数据类型定义
	无论应用那种开发语言，遵循以下对数据类型的定义
******************************************/
#define		 SG_SHORT	short
#define		 SG_INT		int
#define		 SG_BOOL	bool
/*
 *  修改原因：ArcSDE与Oracle的接口对4字节整数返回的类型不一致，当前系统中事实上的处理方式是完全一样的
 *  修改方法：继承事实，将SG_LONG与SG_INT的定义也完全一致
 *            8字节整数定义为SG_INT64，当前系统中暂不使用
 */
#define		 SG_LONG	int
#define		 SG_FLOAT	float
#define		 SG_DOUBLE	double

#define		 SG_USHORT	unsigned short
#define		 SG_UINT	unsigned int
#define		 SG_ULONG	unsigned int
#define		 SG_STRING		char*
#define		 SG_PCSTR		const char*
#define		 SG_PSTR		char*
#define		 SG_CHAR		char
#define		 SG_SCHAR		signed char
#define		 SG_UCHAR		unsigned char


//#ifdef _USE_INT64_
#define		 SG_UINT64	unsigned long long
#define		 SG_INT64	long long
//#endif

#define		 SG_COLORREF	long
#define		 SG_PTR         void*

#define		 SG_PBOOL	bool*
#define		 SG_PSHORT	short*

#define		 SG_PINT	int*
#define		 SG_PLONG	int*
#define		 SG_PFLOAT	float*
#define		 SG_PDOUBLE	double*

#define		 SG_PUSHORT	unsigned short*
#define		 SG_PUINT	unsigned int*
#define		 SG_PULONG	unsigned int*
//#define _USE_TOPO_INT64_
#ifdef _USE_TOPO_INT64_
typedef SG_INT64		SG_NODEINT;
#else
typedef SG_LONG		SG_NODEINT;
#endif
//	函数调用的返回错误码
#define		 SG_CODE		SG_UINT
#ifdef _WIN64
typedef SG_INT64		SG_INTPTR;
#else
typedef SG_LONG		SG_INTPTR;
#endif // _WIN64


//颜色RGB值 
#define MYRGB(r,g,b)          ((SG_ULONG)(((SG_UCHAR)(r)|((SG_USHORT)((SG_UCHAR)(g))<<8))|(((SG_ULONG)(SG_UCHAR)(b))<<16)))
#define MYMAX(a,b)				(((a)>(b))?(a):(b))
#define MYMIN(a,b)				(((a)<(b))?(a):(b))

/***********************************************
	Part 20 域类型定义
	不管应用那种类型的数据库，在应用层具有相同的域类型定义
***********************************************/
#define SG_FIELDTYPE_ILLEGAL		-1
#define SG_FIELDTYPE_CHAR			0
#define SG_FIELDTYPE_BINARY			1
#define SG_FIELDTYPE_LONGCHAR		2
#define SG_FIELDTYPE_LONGBINARY		3
#define SG_FIELDTYPE_TEXT			4
#define SG_FIELDTYPE_IMAGE			5
#define SG_FIELDTYPE_TINYINT		6
#define SG_FIELDTYPE_SMALLINT		7
#define SG_FIELDTYPE_INT			8
#define SG_FIELDTYPE_REAL			9
#define SG_FIELDTYPE_FLOAT			10
#define SG_FIELDTYPE_BIT			11
#define SG_FIELDTYPE_DATETIME		12
#define SG_FIELDTYPE_DATETIME4		13
#define SG_FIELDTYPE_MONEY			14
#define SG_FIELDTYPE_MONEY4			15
#define SG_FIELDTYPE_NUMERIC		16
#define SG_FIELDTYPE_DECIMAL		17
#define SG_FIELDTYPE_VARCHAR		18
#define SG_FIELDTYPE_VARBINARY		19
#define SG_FIELDTYPE_LONG			20
#define SG_FIELDTYPE_SENSITIVITY	21
#define SG_FIELDTYPE_BOUNDARY		22
#define SG_FIELDTYPE_VOID			23
#define SG_FIELDTYPE_USHORT			24
#define SG_FIELDTYPE_GEOMETRY		25			//例如SDE中的SHAPE字段
#define SG_FIELDTYPE_RAW			26			//
#define SG_FIELDTYPE_INT64			27

// ---- OCI的个别定义
#ifndef SQLT_INT
	#define	SQLT_INT		3
#endif
/***********************************************
	Part 30 常用字符串结构及其长度定义
	不管应用那种类型的数据库，在应用层具有相同的域类型定义
***********************************************/
//typedef char SG_TABLENAME[32];			//表名存储结构
//typedef char SG_TABLENAMEDES[40];		//表别名存储结构
typedef char SG_FIELDNAME[32];			//域名存储结构
typedef char SG_FIELDNAMEDES[40];		//域别名存储结构
typedef char SG_OBJECTNAMEDES[40];		//对象名称描述存储结构
typedef char SG_OBJCODE[24];			//对象编码存储结构
typedef char SG_MSG[128];		//系统产生输出消息
//typedef unsigned long SG_OBJECTIDSTRUCT;//设备ID
//#define SG_TABLENAME_LEN sizeof(SG_TABLENAME)
//#define SG_TABLENAMEDES_LEN sizeof(SG_TABLENAMEDES)
#define SG_FIELDNAME_LEN sizeof(SG_FIELDNAME)
#define SG_OBJECTNAMEDES_LEN sizeof(SG_OBJECTNAMEDES)
#define SG_OBJCODE_LEN sizeof(SG_OBJCODE)
#define	SG_MSG_LEN	sizeof(SG_MSG)

/***********************************************
	Part 40 系统限制定义
***********************************************/
#define		SG_MAX_FIELD_WIDTH			4000		//数据库中字段的最大长度
												//包含对raw类型字段的长度控制
#define		SG_MAX_FIELD_NUMS			200				//系统DoWithCurTable支持的最大的域数量
#define		SG_MAX_FILEPATH_LEN			512				//文件路径最大长度
#define		SG_MAX_FILENAME_LEN			64				//文件名最大长度
#define		SG_MAX_SQLWORD_LEN			3998			//系统支持的最大的Sql语句长度
#define		SG_MAX_OBJECT_TYPE			1024			//对象类型的最大值
#define		SG_MAX_FONTNAME_LEN			28				//字体名最大长度
#define		SG_MAX_ORACLESPATIAL_BUFFER	1			//从OracleSpatial读取数据的缓冲区长度
#define		SG_MAX_ATTRIBTABLE_BUFFER   1024			//从一般表读取数据的缓冲区长度

#define		SG_MAX_DOMAIN_IS_OBJIDTONAME		1000		//DoMain为对象ID到名称的转换时提供的下拉选项限值
//系统整形数值的比例 --- 如设备的尺寸设置用一个整形数值存储最小值为1,无法满足工程的需要,除以该比例作为地理的大小(长度)
extern _DATASET_DLL_EXPORT_ int SG_INTVALUE_SCALE;
//#define					100
#define		SG_FLAG_SCREEN_SCALE		100		//显示标记大小占屏幕的大小
#define     SG_SEGMENT_MAX              101     //最大的段数
#define		SG_DISP_AS_DEFAULT_SIZE		9000	//显示配置中配置为显示缺省大小


/******************************************
	Part 80 网络通信用相关定义
******************************************/
#define	SG_NET_VERSION_1			1		//版本1数据格式版本号
#define	SG_NET_VERSION_2			2		//版本2数据格式版本号
#define	SG_NET_VERSION_3			3		//版本3数据格式版本号

#define	SG_NET_VERSION_GIS_START	50		//PSP起始版本号
#define	SG_NET_VERSION_51			51	
#define	SG_NET_VERSION_52			52	
#define	SG_NET_VERSION_53			53	

#define	SG_NET_VERSION				SG_NET_VERSION_53		//当前数据格式版本号
//#define SG_NET_CHECKVERSION(VERSION) ((VERSION==SG_NET_VERSION_1)||(VERSION==SG_NET_VERSION_2))        
#define SG_NET_CHECKVERSION(VERSION) (VERSION<=SG_NET_VERSION)

#define SgNetVersion SG_NET_VERSION
//#define SG_NET_CHECKVERSION(VERSION) ((VERSION==SG_NET_VERSION_1)||(VERSION==SG_NET_VERSION_2))        
#define	  SG_NET_GETVERSION(VERSION) 	if(VERSION<0) {  VERSION=SgNetVersion; if(VERSION<0) return false; }
#define	  SG_NET_GETHEADVERSION(VERSION) 	if(VERSION<0) { if(CmdVersion>0) VERSION=CmdVersion; else VERSION=SgNetVersion; if(VERSION<0) return false; }

#define DEFAULT_DBNO			1
#define DEFAULT_SYS_DBNO		1000
#define DEFAULT_FILE_DBNO		1001
#define DEFAULT_HDBNO			1002

#define DEFAULT_DATVER_RUN		0  //缺省的数据运行版

#define SG_DBVERTYPE_NOVER				0 //没有版本
#define SG_DBVERTYPE_ALLDAT				1 //全量版本
#define SG_DBVERTYPE_INCREMENT			2 //按时间递增版本
#define SG_DBVERTYPE_ADTBL				3 //增量AD表版本

#define SG_DB_DATVERNO_BASE			DEFAULT_DATVER_RUN //基版本版本号
#define SG_FIELD_DAT_VERNO	"DAT_VERNO"

/******************************************
	Part 90 基本设备类型元设备ID
******************************************/
//
#define META_DEVICE_LOADRANGE			1	//加载参数
#define META_DEVICE_POWERPOINT			2	//电源点	
#define META_DEVICE_COMBIN_TEMPLATE		3	//设备组合模板
#define META_DEVICE_TEMPLATE			4	//设备组	
#define META_DEVICE_CIRCUIT				5	//间隔单元	
#define META_DEVICE_OFFSET_POINT		6	//系统点偏移	
#define META_DEVICE_OFFSET_LINE			7	//系统线偏移	
#define META_DEVICE_STATION_POS			8	//站址	
#define META_DEVICE_BAY					9	//仓位	
#define META_DEVICE_CABLE_LINE			10	//站外电缆	
#define META_DEVICE_CABLE_LINE_LV		11	//低压电缆	
#define META_DEVICE_CABLE_STATION		12	//站内电缆	
#define META_DEVICE_COMPANY				13	//公司
#define META_DEVICE_GRID_LINE			14	//网格线	
#define META_DEVICE_GRID_POINT			15	//网格点	
#define META_DEVICE_YC_BASE				16	//遥测层	
#define META_DEVICE_KWH_BASE			17	//电度层	
#define META_DEVICE_TOPO_POWE			18	//拓扑等效电源	
#define META_DEVICE_TOPO_LINE			19	//拓扑线路	
#define META_DEVICE_OBJ_CANVAS			20	//画布	
#define META_DEVICE_OBJ_NORMALRANGE		22	//行政区划及正常范围	
#define META_DEVICE_WORK_WELL			23	//工井	
#define META_DEVICE_WORK_WELL_COVER		24	//工井盖	
#define META_DEVICE_TEMP_OBJECT			27	//临时对象	
#define META_DEVICE_LABEL_ARROW			28	//标注箭头	
#define META_DEVICE_DISTRICT_CHARACTER	29	//供电区域特征	
#define META_DEVICE_PIPE_TYPEID			30	//管路元对象的类型ID	
#define META_DEVICE_DISTRICT_TYPEID		31	//行政区划元对象类型ID	
#define META_DEVICE_TR_LINE				32	//输电线路
#define META_DEVICE_LINE				33  //配电线路
#define META_DEVICE_LV_LINE			    34  //低压线路
#define META_DEVICE_OBJLABEL			35	//设备标注
#define META_DEVICE_SUBSTATION			36	//变电站
#define META_DEVICE_SWITCHSTATION		37	//开关站
#define META_DEVICE_TRANSSET			38	//变台
#define META_DEVICE_RMU					39	//开闭所
#define META_DEVICE_POLE				40	//杆塔
#define META_DEVICE_LVLINKFUSE			41	//低压熔丝箱
#define META_DEVICE_USERSTATION			44	//用户电站(38与44之间留给可能细化管理的电站)
#define META_DEVICE_LINEPOINT			45	//进出线点
#define META_DEVICE_DYNAMOTOR			47	//发电机

#define META_DEVICE_DISTRIBUTE_SUBSTAION 50 //配电室
#define META_DEVICE_TRUNK_SUBSTATION	51	//箱式变
#define META_DEVICE_BRANCH_BOX			52	//电缆分支箱
#define META_DEVICE_LV_CIRCUIT			53	//低压间隔
#define META_DEVICE_LV_LINEPOINT		54	//低压进出线点
#define META_DEVICE_LV_SUPPLY_POINT		55	//低压接电点
#define META_DEVICE_LV_TRANS_REGION		56	//低压台区
#define META_DEVICE_HYPER_LINE			57	//中压超连接线
#define META_DEVICE_LV_HYPER_LINE		58	//低压超连接线
#define META_DEVICE_LV_POWER_LINE		59	//杆变连接线
#define META_DEVICE_WORLD_TYPE			60	//world对象
#define META_DEVICE_MAIN_TRANS			61  //主变
#define META_DEVICE_DISTR_TRANS			62  //配变
#define META_DEVICE_USER_SUBSTAION		63	//用户站


#define META_DEVICE_LINE_SEGMENT		70	//导线
#define META_DEVICE_CABLE_SEGMENT		71	//电缆段

#define META_DEVICE_METER				80	//表计
#define META_DEVICE_LAYOUT_LINE			85	//地理走向图线对象
#define META_DEVICE_LAYOUT_POINT		86	//地理走向图点对象
#define META_DEVICE_SCHEME_RANGE		87	//规划方案范围
#define META_DEVICE_RDP_ANA				101	//遥测量
#define META_DEVICE_RDP_DIG				102	//状态量
#define META_DEVICE_RDP_ACC				103	//电度量
#define META_DEVICE_RDP_EVENT			104	//事项

#define DEVICE_RDP_ANA				500	//遥测量
#define DEVICE_RDP_DIG				501	//状态量
#define DEVICE_RDP_ACC				502	//电度量
#define DEVICE_RDP_EVENT			503	//事项
#define DEVICE_RDP_CPSEVT			504	//平台事项
#define DEVICE_RDP_POSITION			505	//位置量

#define DEVICE_PHYNODE              1000 //物理节点
#define DEVICE_RDP_RTU				1001 //终端
#define DEVICE_SUBSTATION			1		//电站的设备类型
#define DEVICE_COMPANY				600		//公司的设备类型
#define DEVICE_TEAM					601		//团队的设备类型
#define DEVICE_INVERTER				29		//逆变器
#define DEVICE_COMBINING			30		//汇流箱
#define DEVICE_PVARRAY				31		//光伏板组串
#define DEVICE_CIRCUIT				20		//回路
#define DEVICE_CONTAINER			4		//机柜
#define DEVICE_POWERPOINT           22		//电源点
#define DEVICE_AREA					602		//地区
#define DEVICE_CUSTOMER				800		//用电用户
#define DEVICE_BATTERIES			34		//电池组
#define DEVICE_BATTERY				35		//电池
#define DEVICE_MCU				24   //表计设备

#define SG_RDP_MAX_TERMAINL				1000000

/**************************************************************************************
	Part 100 系统特定对象类型定义，不通过元方数据解析，注意要和数据库配置一致
**************************************************************************************/
#define DEVICE_SYMBOL_ELEMENT		31		//通过符号对象自身，挂接系统符号
//挂架在DEVICE_SYMBOL_ELEMENT上的符号作为系统符号引用
enum SYS_SYMBOL
{
	FLOW_SYMBOL					=0,		//潮流方向符号
	STATICTOP_SYMBOL			=1,		//静态拓扑方向符号
	TOPBARRIER_SYMBOL			=2,		//拓扑障碍点符号
	WORK_WELL_SYMBOL			=3		//工井模板符号
};

//画刷定义
/* Brush Styles */
#define HS_HORIZONTAL       0       /* ----- */
#define	HS_VERTICAL         1       /* ||||| */
#define	HS_FDIAGONAL        2       /* \\\\\ */
#define	HS_BDIAGONAL        3       /* ///// */
#define	HS_CROSS            4       /* +++++ */
#define	HS_DIAGCROSS        5       /* xxxxx */
//
#ifndef WIN32
#define BS_SOLID            0
#define BS_NULL             1
#define BS_PATTERN          3
#define PS_SOLID            0
#define PS_DOT              2 
#define TRANSPARENT         1
#define OPAQUE              2
#endif
#define HS_BASE				6
#define	HS_SOLID			BS_SOLID+HS_BASE	//6
#define	HS_NULL				BS_NULL+HS_BASE		//7
#define	HS_BITMAP			BS_PATTERN+HS_BASE	//9
//
#define stop_dev_status 59	//设备休止状态值

//电压等级定义与Domain配置一致
enum STANDARD_VOLTAGE
{
	STANDARD_220V_VOLTAGE			=	7,	//0.4千伏/380伏的内值
	STANDARD_380V_VOLTAGE			=	8,	//0.4千伏/380伏的内值
	STANDARD_2_5KV_VOLTAGE			=	15, //2.5kV
	STANDARD_3KV_VOLTAGE			=	20,	//3千伏的内值
	STANDARD_6KV_VOLTAGE			=	21,	//6千伏的内值
	STANDARD_10KV_VOLTAGE			=	22,  //10kV电压等级的内值
	STANDARD_15_75KV_VOLTAGE		=	23,	//15.75kV电压等级的内值
	STANDARD_20KV_VOLTAGE			=	24,	//20kV电压等级的内值
	STANDARD_35KV_VOLTAGE			=	25,  //35kV电压等级的内值
	STANDARD_50KV_VOLTAGE			=	5,  //50kV电压等级的内值
	STANDARD_66KV_VOLTAGE			=	30,  //66kV电压等级的内值
	STANDARD_110KV_VOLTAGE			=	32,  //110kV电压等级的内值
	STANDARD_220KV_VOLTAGE			=	33,  //220kV电压等级的内值
	STANDARD_330KV_VOLTAGE			=	34,  //330kV电压等级的内值
	STANDARD_500KV_VOLTAGE			=	35,  //500kV电压等级的内值
	STANDARD_750KV_VOLTAGE			=	36,  //750kV电压等级的内值
	STANDARD_1000KV_VOLTAGE			=	37  //1000kV电压等级的内值
};

enum
{
	STANDARD_110V_DC_VOLT			=	56,	//直流110V5
	STANDARD_220V_DC_VOLT			=	60,	//直流220V
	STANDARD_120kV_DC_VOLT			=	80,	//直流120kV
	STANDARD_125kV_DC_VOLT			=	81,	//直流125kV
	STANDARD_500kV_DC_VOLT			=	83,	//直流500kV
	STANDARD_800kV_DC_VOLT			=	85,	//直流800kV
	STANDARD_1000kV_DC_VOLT			=	86	//直流1000kV	
};

enum
{
	STANDARD_220V_VOLT_VAL			=	220,		//220伏的计算值
	STANDARD_380V_VOLT_VAL			=	400,		//0.4千伏/380伏的计算值
	STANDARD_2_5KV_VOLT_VAL			=	2500,		//2.5千伏的计算值
	STANDARD_3KV_VOLT_VAL			=	3000,		//3千伏的计算值
	STANDARD_6KV_VOLT_VAL			=	6000,		//6千伏的计算值
	STANDARD_10KV_VOLT_VAL			=	10000,		//10kV电压等级的计算值
	STANDARD_15_75KV_VOLT_VAL		=	15750,		//15.75kV电压等级的计算值
	STANDARD_20KV_VOLT_VAL			=	20000,		//20kV电压等级的计算值
	STANDARD_35KV_VOLT_VAL			=	35000,		//35kV电压等级的计算值
	STANDARD_50KV_VOLT_VAL			=	50000,		//50kV电压等级的计算值
	STANDARD_66KV_VOLT_VAL			=	66000,		//50kV电压等级的计算值
	STANDARD_110KV_VOLT_VAL			=	110000,		//110kV电压等级的计算值
	STANDARD_220KV_VOLT_VAL			=	220000,		//220kV电压等级的计算值
	STANDARD_330KV_VOLT_VAL			=	330000,		//330kV电压等级的计算值
	STANDARD_500KV_VOLT_VAL			=	500000,		//500kV电压等级的计算值		
	STANDARD_750KV_VOLT_VAL			=	750000,		//500kV电压等级的计算值	
	STANDARD_1000KV_VOLT_VAL		=	1000000		//500kV电压等级的计算值	
};

enum
{
	STANDARD_110V_DC_VOLT_VAL			=	110,	//直流110V5
	STANDARD_220V_DC_VOLT_VAL			=	220,	//直流220V
	STANDARD_120kV_DC_VOLT_VAL			=	120000,	//直流120kV
	STANDARD_125kV_DC_VOLT_VAL			=	125000,	//直流125kV
	STANDARD_500kV_DC_VOLT_VAL			=	500000,	//直流500kV
	STANDARD_800kV_DC_VOLT_VAL			=	800000,	//直流800kV
	STANDARD_1000kV_DC_VOLT_VAL			=	1000000	//直流1000kV	
};
#endif