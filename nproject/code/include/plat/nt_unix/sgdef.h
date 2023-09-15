// sgdef.h
//
/*****************************************************************
	系统的结构定义，同时包含对系统常量头文件的调用

	part 0	对象的记录表征结构
			单一对象记录结构
			对象集合的记录表征结构
			对象集合的记录表征结构
			对象的拓扑端子记录结构
			对象的拓扑端子键值结构
			对象的缺省尺寸结构
			对象的符号属性结构 --- 见文件 CSgSymbol.h SG_OBJ_SYMBOL

 
	Part 10 对象图层属性：
		Part 10 对象层的缺省显示属性 对象的几何属性的显示属性结构
		Part 12 系统特定字段在当前层中的字段偏移量结构
		Part 14 "对象类型"具有的内控属性配置信息内存存储结构
		Part 15 获取对象行号（通过基础对象type和基础对象id）用结构
	Part 20 对象实例的属性结构
	Part 30 对象属性表域信息结构
	Part 40 对象拓扑障碍点属性结构
	Part 50	平面几何属性相关结构

	Part 60	系统枚举类型定义
			对象间的行为特征定义
			表应用类型定义
			基础特征类型定义
			空间数据源类型
			属性数据源类型
			对象实例类型
			对象模型变换方式
			对象分类
			宇宙类型
			网络类型
			World居中显示性质
			电系性质
			电气性质
			设施设备分类
			做图规则
			线符号特性
			点选（点对象）的方法
			点选（线区域对象）的方法
			"对象类型"具有的内控属性类型
			拓扑计算方式
			域属性－输入方式
			网络传输用定义
			服务侧控制加载用

	Part 80	系统指针管理类
	Part 90	与SCADA接口结构定义

	Part 100 视图的应用结构定义

	Part 110 视图相关枚举类型定义
			世界处于的状态
			系统显示策略

	Part 120 对象编辑控制结构

	part 130 系统特定表结构

	part 140 系统运行时间检测

	part 150 内存占用检测
*****************************************************************/

#if !defined(SG_Def_h)
#define SG_Def_h

#include "sgconst.h"
#include <memory.h>
#include <string>
#include <math.h>
//#include "sggeodef_template.h"
#include "sgdataset.h"
//#ifndef WIN32
//#define SG_CORE_API 
//#endif
/************************************************
	part -1	对象的行为记录表征结构
 SG GIS 对象间的行为特征定义
	通过元数据的SYS_OBJECT_RELATION表的BEHAVIOUR属性记录
	关系的行为特征: 隐式容器/显式容器/组合/级联删除/触发关系/可连接关系/显示互斥关系
************************************************/
#define	SG_BEHAVIOUR_CONTAIN	0x07	//对象包含关系屏蔽值
enum SG_Obj_BehaviourType
{
	/*
		隐式包含 如设备组与设备 设备组与设备组 设备组与支线 支线与设备 台区与设备
		关系数据存放在元数据表SYS_OBJECT_RELATION中
		其记录形式为简单的数据库关系,可能会存在一个比较复杂的对应关系
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_HIDE		= 0x01,
	/*
		显式包含 如站房对象与其中安装的设备
		其记录方式存放在对象的属性表中
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_VISIBLE	= 0x02,
	/*
		组合式包含 如主变与绕组 杆塔与架空线/通信线等对象
		关系数据存放在元数据表SYS_OBJECT_RELATION中
		其记录形式为简单的数据库关系
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_COMBIN	= 0x04,
	/*
		级连删除
	*/
	SG_OBJ_BEHAVIOUR_CASCADEDELETE = 0x08,
	/*
		触发关系 --- 该关系GIS内部用
	*/
	SG_OBJ_BEHAVIOUR_TRIGGER = 0x10,
	/*
		可连接关系 --- 该关系GIS内部用
	*/
	SG_OBJ_BEHAVIOUR_CONNECT = 0x20,
	/*
		显示互斥关系 --- 该关系GIS内部用
	*/
	SG_OBJ_BEHAVIOUR_DISPMUTEX = 0x40,
	/*
		依附关系 --- 该关系GIS内部用
	*/
	SG_OBJ_BEHAVIOUR_ADHERE  = 0x80,
	/*
		直属包含
		对象模型调整具有一子多父后，为区别父与子的关系，增加该标记位
		概念上不具有直属包含的父子关系可称谓：叔侄关系
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_FATHER = 0x100,
	/*
	 删除限制关系、如果存在子设备、父设备不能被删除
	 */
	SG_OBJ_BEHAVIOUR_DELETE_RESTRICT=0x200,
	/*
	 跨“逻辑库”引用关系，如：规划电站与生产电站之间
	 */
	 SG_OBJ_BEHAVIOUR_REFRENCE=0x400
};

//对象之间的关系记录结构

struct SG_CORE_API OBJECT_RELATION
{
	
	SG_LONG			Objtype;	//对象类型
	
	SG_ULONG		Behaviour;	//对象行为
	
	SG_UCHAR		nRelation;	//关系的维数
private:
	
	SG_FIELDNAME	fieldName;	//关联字段名 --- 当表征为一个子设备对象时有效，表征与父对象ID关联所用的字段名
	
	SG_FIELDNAME    fieldName0;
public:
	
	OBJECT_RELATION();
	//是否为可视容器关系
	
	SG_BOOL IsVisibleContain();
	//是否为容器关系
	
	SG_BOOL IsContain();
	//类似 杆上附属物的 关系 --- 特定应用
	
	SG_BOOL IsOnPoleRelation();
	//是否为可连接关系
	
	SG_BOOL IsConnectRelation();
	//是否组合式包含
	
	SG_BOOL IsCombin();
	//是否显示互斥
	
	SG_BOOL IsDispMetex();
	//是否由依附关系
	
	SG_BOOL IsAdhereRelation();
	//设置关系字段名
	
	void SetRelaFieldName(SG_CHAR *p);
	
	void SetRelaFieldName_class(SG_CHAR *p);
	//取关系字段名
	
	SG_CHAR *GetRelaFieldName();
	
	SG_CHAR *GetRelaFieldName_class();
	//是否具有关系字段
	
	SG_BOOL HasRelaFieldName();
	//清空关系字段表
	
	void ClearRelaFieldName();
	
	void ClearRelaFieldName_class();
};
//多个关系记录结构

struct SG_CORE_API OBJECT_RELATIONS
{
	
	SG_LONG			RelationNums;	//关系数量
	
	OBJECT_RELATION *pRelation;		//关系内容
	
	OBJECT_RELATIONS();
	
	~OBJECT_RELATIONS(){Clear();}
	//增加管理
	
	void Add(OBJECT_RELATION *pRelation);
	//增加关系
	
	void Add(SG_LONG Objtype,SG_LONG Behaviour,SG_UCHAR nRelation,SG_CHAR *f=0,SG_CHAR*pclass=0);
	//第ptr个关系是否是"杆上附属物"性质的关系 --- 容器到子对象
	
	SG_BOOL IsOnPoleRelation(SG_INT ptr);
	//获得对ObjType的关系
	
	OBJECT_RELATION*GetRelation(SG_INT ObjType);
	//清空队列
	
	void	Clear();
};



struct SG_CORE_API ObjTypeAndSubTypeStruct
{
	
	SG_SHORT ObjType;
	
	SG_SHORT SubType;
};

// --- 对象带属性结构

struct SG_CORE_API SG_REAL_OBJECT:public SG_OBJECT
{
	
	SG_LONG Value;
};

//对象的拓扑端子记录结构

struct SG_CORE_API SG_TOPNODE{
	
	SG_LONG MemNums;
	
	SG_LONG NodeNums;
	
	SG_NODEINT *pNode;
	
	SG_TOPNODE(){MemNums=0;NodeNums=0;pNode=0;}
	
	~SG_TOPNODE(){if(pNode)free(pNode);pNode=0;}
	
	inline SG_BOOL IsNull() const
	{
		if(NodeNums<1)return true;
		if(!pNode)return true;
		return false;
	}
	
	inline void Add(SG_NODEINT node)
	{
		if(node<1)return;
		if(IsNodeIn(node))return;
		SetSize(NodeNums+1);
		pNode[NodeNums] = node;
		NodeNums++;
	}
	
	inline SG_BOOL IsNodeIn(SG_NODEINT node)
	{
		SG_INT i;	
		for(i=0;i<NodeNums;i++)
			if(pNode[i]==node)break;
		return i<NodeNums;
	}
	
	inline void SetSize(SG_INT nums){
		if(nums<=MemNums)return;
		if(pNode==NULL)
			pNode = (SG_NODEINT*)malloc(sizeof(SG_NODEINT)*nums);
		else
			pNode = (SG_NODEINT*)realloc(pNode,sizeof(SG_NODEINT)*nums);
		MemNums=nums;
	}
	
	inline void operator = (const SG_TOPNODE&p)
	{
		SetSize(p.NodeNums);
		NodeNums = p.NodeNums;
		if(!p.IsNull()&&!IsNull())
			memcpy(pNode,p.pNode,sizeof(SG_NODEINT)*NodeNums);
	}
	
	SG_LONG GetAllMemLen(){
		SG_LONG len = sizeof(SG_TOPNODE);
		if(pNode)
			len += sizeof(SG_NODEINT)*MemNums;
		return len;
	}
};

//对象的拓扑端子键值结构
//注意：该结构中位的位置不能随便更改，否则影响系统功能
//#define SG_MASK_BREAKOPEN_VALUE		0x00000100		//用于屏蔽 IsBreakOpen 的值
//#define SG_MASK_POWERPOINT_VALUE	0x00000200		//
//#define SG_MASK_LINESTART_VALUE		0x00000400		//
//#define SG_MASK_LINEEND_VALUE		0x00000800		//
//#define SG_MASK_VOLTLEVEL_VALUE		0x000f0000		//用于屏蔽 VoltLevel 的值
//#define SG_MASK_POWERON_VALUE		0x00100000		//用于屏蔽 带电状态 的值
//#define SG_MASK_DIS_TRANS_VALUE		0x00200000		//用于屏蔽 配电变 的值

struct SG_CORE_API TopNodeKeyValue{
	union{
		SG_ULONG Value;
		struct{
#if defined(__sun)||defined(_AIX)
			SG_UCHAR res1;
			SG_UCHAR IsDisTrans:1;	//临时变量，是否配电变
			SG_UCHAR PowerOn:1;	//当前计算状态下带电
			SG_UCHAR Volt:6;	//特征电压等级
			SG_UCHAR res:3;
			SG_UCHAR IsKGStationBus:1;	//标示节点为开关站内的母线
			SG_UCHAR IsLineEnd:1;		//标识节点为线路终止点
			SG_UCHAR IsLineStart:1;		//标识节点为线路起点
			SG_UCHAR IsPowerPoint:1;	//标识节点为电源点
			SG_UCHAR IsBreakOpen:1;

			SG_UCHAR rev3:1;
			SG_UCHAR rev2:1;
			SG_UCHAR rev1:1;
			SG_UCHAR hasLargeResistor:1;
			SG_UCHAR hasUser:1;
			SG_UCHAR hasBus:1;
			SG_UCHAR hasTrans:1;
			SG_UCHAR hasBreaker:1;
#else
			SG_UCHAR hasBreaker:1;
			SG_UCHAR hasTrans:1;
			SG_UCHAR hasBus:1;
			SG_UCHAR hasUser:1;
			SG_UCHAR hasLargeResistor:1;
			SG_UCHAR rev1:1;
			SG_UCHAR rev2:1;
			SG_UCHAR rev3:1;
			// --- 2005-05-15增加拓扑节点开断标记
			SG_UCHAR IsBreakOpen:1;
			SG_UCHAR IsPowerPoint:1;	//标识节点为电源点
			SG_UCHAR IsLineStart:1;		//标识节点为线路起点
			SG_UCHAR IsLineEnd:1;		//标识节点为线路终止点
			SG_UCHAR IsKGStationBus:1;	//标示节点为开关站内的母线
			SG_UCHAR res:3;
			//
			SG_UCHAR Volt:6;		//特征电压等级
			SG_UCHAR PowerOn:1;		//当前计算状态下带电
			SG_UCHAR IsDisTrans:1;	//临时变量，是否配电变
			SG_UCHAR res1;
#endif
		}BitVal;
	};
	TopNodeKeyValue();
	void Clear();
	/*
	 *	键值相或
	 */
	void operator += (TopNodeKeyValue&AddV);
	/*
	 *	是否具有关键设备(开关类、变压器类、母线类)
	 *  算法：取前四个位【Value&0x0f】，不包括无穷大阻抗设备
	 */
	SG_BOOL HasKeyEquip();
	/*
	 *	获得带电计算前，需要的键值屏蔽值
	 *  算法：SG_MASK_BREAKOPEN_VALUE|SG_MASK_POWERPOINT_VALUE|SG_MASK_LINESTART_VALUE|
	 *		SG_MASK_VOLTLEVEL_VALUE|SG_MASK_POWERON_VALUE|SG_MASK_DIS_TRANS_VALUE
	 */
	SG_ULONG ElecCalMaskValue();
};

//对象的缺省尺寸结构

struct SG_CORE_API SG_OBJ_DEFAULT_SIZE
{
	
	SG_ULONG Universe;
	
	SG_INT InContainer;
	
	SG_INT ContainerType;
	
	SG_FLOAT DefWidth;
	
	SG_FLOAT DefHeight;
	
	SG_OBJ_DEFAULT_SIZE()
	{
		memset(this,0,sizeof(SG_OBJ_DEFAULT_SIZE));
	}
	
	SG_OBJ_DEFAULT_SIZE &operator = (const SG_OBJ_DEFAULT_SIZE& equipsize)
	{
		if(this==&equipsize)
			return *this;
		Universe=equipsize.Universe;
		InContainer=equipsize.InContainer;
		ContainerType=equipsize.ContainerType;
		DefWidth=equipsize.DefWidth;
		DefHeight=equipsize.DefHeight;
		return *this;
	}
};


/***********************************************
	Part 10 对象层的缺省显示属性 对象的几何属性的显示属性结构
***********************************************/
//基础Feature为点的显示属性结构

struct SG_CORE_API SG_POINT_ATTRIB
{
	
	SG_USHORT	sym;		
	
	SG_USHORT	size;		//0-65535
	
	SG_SHORT	angle;		//0-511,圆周360表示法
};

//基础Feature为线的显示属性结构
///* Pen Styles */
//#define PS_SOLID            0
//#define PS_DASH             1       /* -------  */
//#define PS_DOT              2       /* .......  */
//#define PS_DASHDOT          3       /* _._._._  */
//#define PS_DASHDOTDOT       4       /* _.._.._  */
//#define PS_NULL             5

struct SG_CORE_API LINE_COLOR_STYLE
{
	
	SG_ULONG style:4;		/*0-8*/
	
	SG_ULONG color:(32-4);
	
	void SetValue(SG_ULONG StorageValue)
	{
		memcpy(this,&StorageValue,sizeof(SG_ULONG));
	}
	
	SG_ULONG GetValue()
	{
		SG_ULONG StorageValue;
		memcpy(&StorageValue,this,sizeof(SG_ULONG));
		return StorageValue;
	}
};
//线型对象层的线型属性

struct SG_CORE_API SG_LINE_ATTRIB:LINE_COLOR_STYLE
{
	
	SG_USHORT width;		/*线宽*/
	
	SG_USHORT sym;			//线符号
};
//基础Feature为区域的显示属性结构
/* Brush Styles */
// CBrushStyleCmb window
//	HS_HORIZONTAL       0       /* ----- */
//	HS_VERTICAL         1       /* ||||| */
//	HS_FDIAGONAL        2       /* \\\\\ */
//	HS_BDIAGONAL        3       /* ///// */
//	HS_CROSS            4       /* +++++ */
//	HS_DIAGCROSS        5       /* xxxxx */
//	HS_SOLID			BS_SOLID+6		(6)
//	HS_NULL				BS_NULL+6		(7)
//	HS_BITMAP			BS_PATTERN+6	(9)

struct SG_CORE_API SG_REGION_ATTRIB:SG_LINE_ATTRIB
{
	
	SG_ULONG brStyle:4;			//brStyle==HS_BITMAP时，brColor中存储的是“位图符号”的内存索引
	
	SG_ULONG brColor:(32-4);
	
	void SetRegionValue(SG_ULONG value)
	{
		brStyle=value&0x0f;
		brColor=value>>4;
	}
	
	SG_ULONG GetRegionValue()
	{
		SG_ULONG value;
		value = brColor*0x10;
		value += brStyle;
		return value;
	}
};
//基础Feature为文字的显示属性结构
//struct SG_CORE_API SG_TEXT_ATTRIB
//{
//	SG_CHAR		fontname[SG_MAX_FONTNAME_LEN];
//	SG_USHORT	size;
//	SG_USHORT	angle;
//	SG_ULONG	color;
//	SG_ULONG	bkmode:2;
//	SG_ULONG	bkcolor:30;
//	SG_BOOL IsValid(){
//		return size>0 && fontname[0]!='\0' && bkmode>0 && bkmode<3;
//	}
//};


class CSgString;


//对象显示属性结构——联合结构

struct SG_CORE_API ObjectDisplayAttribStruct
{
	
	SG_LINE_ATTRIB LineAttrib;
	
	SG_REGION_ATTRIB RegionAttrib;
	
	SG_POINT_ATTRIB PointAttrib;
	
	SG_TEXT_ATTRIB TextAttrib;
	
	ObjectDisplayAttribStruct(){memset(this,0,sizeof(ObjectDisplayAttribStruct));}
};


/***********************************************
	Part 12 系统特定字段在当前层中的字段偏移量结构
***********************************************/




typedef ObjType_IA_Cfg_Struct Sg_ObjType_InsideAttrib_Struct;

/***********************************************
		Part 15 获取对象行号（通过基础对象type和基础对象id）用结构
***********************************************/

struct SG_CORE_API GetBaseObjRowStruct_Attrib
{
	
	SG_LONG BaseObjID;
	
	SG_LONG StartRow;
	
	SG_SHORT BaseObjType;
	
	SG_BOOL SafeCheck;
	
	GetBaseObjRowStruct_Attrib(){
		BaseObjID				=-1;
		StartRow				=-1;
		BaseObjType				=-1;
		SafeCheck				=true;
	}
};


struct SG_CORE_API GetBaseObjRowStruct_Layer:public GetBaseObjRowStruct_Attrib
{
	
	SG_SHORT GisIDFieldPos;
	
	SG_SHORT BaseObjTypeFieldPos;
	
	SG_SHORT BaseObjIDFieldPos;
	
	GetBaseObjRowStruct_Layer(){
		GisIDFieldPos			=-1;
		BaseObjTypeFieldPos		=-1;
		BaseObjIDFieldPos		=-1;
	}
};

/***********************************************
	Part 20 实时对象定义结构
	 --- 遥测类型定义
	 --- 电度类型定义
	 --- 遥信类型定义
***********************************************/

enum SCADA_COLLECTION_TYPE_DEF{
	// --- 遥测定义开始
	SG_YC_VOLTAGE				=1,	//电压
	SG_YC_VOLTAGE_AB			=2,	//AB线电压
	SG_YC_VOLTAGE_BC			=3,	//BC线电压
	SG_YC_VOLTAGE_CA			=4,	//CA线电压
	//
	SG_YC_VOLTAGE_A				=7,	//A相电压
	SG_YC_VOLTAGE_B				=8,	//B相电压
	SG_YC_VOLTAGE_C				=9,	//C相电压
	SG_YC_VOLTAGE_0				=10,//0序电压
	//
	SG_YC_I						=11,//电流
	SG_YC_I_A					=12,//A相电流
	SG_YC_I_B					=13,//B相电流
	SG_YC_I_C					=14,//C相电流
	SG_YC_I_0					=15,//0序电流
	//
	SG_YC_COS					=16,//功率因数
	SG_YC_COS_A					=17,//A相功率因数
	SG_YC_COS_B					=18,//B相功率因数
	SG_YC_COS_C					=19,//C相功率因数
	//
	SG_YC_P						=21,//有功功率
	SG_YC_P_A					=22,//A相有功功率
	SG_YC_P_B					=23,//B相有功功率
	SG_YC_P_C					=24,//C相有功功率
	SG_YC_P_0					=25,//0序有功功率
	//
	SG_YC_Q						=26,//无功功率
	SG_YC_Q_A					=27,//A相无功功率
	SG_YC_Q_B					=28,//B相无功功率
	SG_YC_Q_C					=29,//C相无功功率
	SG_YC_Q_0					=30,//0序无功功率
	//
	SG_YC_PHASE_ANGLE			=31,//相角
	SG_YC_TEMPERATURE			=32,//温度

	SG_YC_3PHASE_UNBLANCE       =37,//三相不平衡率

	//  ---- 遥信定义开始
	SG_YX_OBJ_STATUS			=81,//设备分段状态
	SG_YX_COMM_STATUS			=82,//设备通信状态
	SG_YX_OBJ_RUN_SATTUS			=83,//设备运行状态
	SG_YX_PROTECT				=85,	//保护信号

	//  ---- 遥信-信号量定义开始
	//遥信信号量量测类型从 100  到  200
	SG_YX_SIGNAL_BENGIN			=100,//信号量量测类型定义开始
	//如果有必要，请在这个之间进行增加对于特殊遥信信号的定义
	//SG_YX_SIGNAL_MYTYOE		=10?,
	SG_YX_SIGNAL_END			=200,//信号量量测类型定义结束
	
	
	//  ---- 电度定义开始
	SG_YC_KWH_P					=201,//有功电度
	SG_YC_KWH_Q					=202,//无功电度
	SG_YC_KWH_P_FORWARD			=203,//正向有功电度
	SG_YC_KWH_P_BACKWARD		=204,//反向有功电度
	SG_YC_KWH_Q_FORWARD			=205,//正向无功电度
	SG_YC_KWH_Q_BACKWARD		=206//反向无功电度
};



/***********************************************
	Part 20 对象实例的属性结构
***********************************************/

//单一遥测结构 --- 遥测对象实时属性

struct OneYaoCeInfo
{
	
	YaoCeAttribStruct Attrib;	//遥测的属性
	
	SG_SHORT Type;				//遥测的类型
	
	SG_FLOAT value;				//遥测值
	
	SG_FLOAT ConvFact;			//转换系数
};

//遥测结构 --- 遥测对象实时属性

struct YaoCeInfo
{
	//遥测的数量
	
	SG_INT Nums;
	//遥测的内容
	
	OneYaoCeInfo *pYaoCe;
	//构造
	
	YaoCeInfo(){
		Nums=0;pYaoCe=NULL;
	}
	//析构
	
	~YaoCeInfo(){
		Nums=0;if(pYaoCe)free(pYaoCe);pYaoCe=NULL;
	}
	//增加遥测
	
	void Add(OneYaoCeInfo*p)
	{
		if(Nums==0 || pYaoCe==NULL)
		{
			Nums = 0;
			pYaoCe = (OneYaoCeInfo *)malloc(sizeof(OneYaoCeInfo));
		}
		else
			pYaoCe = (OneYaoCeInfo *)realloc(pYaoCe,sizeof(OneYaoCeInfo)*(Nums+1));
		pYaoCe[Nums] = *p;
		Nums++;
	}
	//用类型号检索一个遥测
	
	OneYaoCeInfo *GetYaoCe(SG_SHORT type)
	{
		for(SG_INT i=0;i<Nums;i++)
			if(pYaoCe[i].Type == type)return &pYaoCe[i];
		return NULL;
	}
};
/***********************************************
	Part 30 对象属性表域信息结构
***********************************************/
//对象属性表域信息结构
/*
struct FieldInfoStruct{
	SG_FIELDNAME FieldName;
	SG_SHORT FieldType;
	SG_SHORT FieldLen;
	SG_SHORT SqlType;			// for oracle
	SG_USHORT ConPtr;			//字段内容在一条记录中的终止相对位置
	SG_UCHAR CanBeNull:1;
	SG_UCHAR Primary:1;
	SG_UCHAR UpdateFlag:1;		//创建sql语句时是否可以被update
	SG_UCHAR ExtAttribFlag:1;	//外扩展数据源中的属性标示--只用于LocalLib加载标注信息用
	SG_UCHAR CommonFlag:1;		//条件属性
	SG_UCHAR GraphFlag:1;		//几何属性标志——自定义表中的几何域，只允许通过几何结构相关的方法赋值
	SG_UCHAR SgGisOID:1;		//唯一决定LocalLib中一条记录的字段
	SG_UCHAR ArcGisOID:1;		//只读字段标记
	SG_UCHAR ChangeFlag:1;		//列值是否修改---StartEditTable后的操作用
	//两个域信息是否一致
	SG_BOOL Equal(FieldInfoStruct *p){
		if(strcmp(FieldName,p->FieldName))return false;
		if(FieldType!=p->FieldType)return false;
		if(FieldLen!=p->FieldLen)return false;
		if(ConPtr!=p->ConPtr)return false;
		return true;
	}
	FieldInfoStruct(){memset(this,0,sizeof(FieldInfoStruct));UpdateFlag=true;}
};
*/
/***********************************************
	Part 40 对象拓扑障碍点属性结构
	系统的拓扑计算方式可以分为特定的种类并编号，
	每种计算方式下对象是否参与计算通过对应的标记位记录
***********************************************/
//

struct SG_CORE_API ObjectBarrierPointStruct{
	
	SG_UCHAR	CalStyle1:1;	//地理和电气拓扑时作为终止设备
	
	SG_UCHAR	CalStyle2:1;
	
	SG_UCHAR	CalStyle3:1;
	
	SG_UCHAR	CalStyle4:1;
	
	SG_UCHAR	CalStyle5:1;
	
	SG_UCHAR	CalStyle6:1;
	
	SG_UCHAR	CalStyle7:1;
	
	SG_UCHAR	CalStyle8:1;
	
	SG_UCHAR	CalStyle9:1;
	
	SG_UCHAR	CalStyle10:1;
	
	SG_UCHAR	CalStyle11:1;
	
	SG_UCHAR	CalStyle12:1;
	
	SG_UCHAR	CalStyle13:1;
	
	SG_UCHAR	CalStyle14:1;
	
	SG_UCHAR	CalStyle15:1;
	
	SG_UCHAR	CalStyle16:1;
	
	ObjectBarrierPointStruct(SG_USHORT value=0){
		SetValue(value);
	}
	
	void SetValue(SG_USHORT value){
		SG_USHORT *p = (SG_USHORT*)this;
		*p = value;
	}
	
	SG_USHORT GetValue(){
		SG_USHORT *p = (SG_USHORT*)this;
		return *p;
	}
};



/*******************************************************
	Part 50	平面几何属性相关结构
*******************************************************/

struct GeoMetrySelPara{
	
	SG_BOOL	PointFirst:1;		//是否点优先还是线优先，对点选有效
	
	SG_BOOL WholeContain:1;		//是否完全包含，对非点选有效
	
	SG_BOOL SearchAll:1;		//是否搜索所有的对象
	
	SG_BOOL UseTolerance:1;		//点选有效
	
	SG_BOOL AdvanceObjFirst:1;	//复杂对象优先 定义在 usefulfunc.h 中 IsAdvancetObj
	
	SG_BOOL SelectWhileVisible:1;//图层控制可见时才可选择
								//图层控制对象不可选时肯定不参与选择
	
	SG_BOOL OnlySelectBeDrawObj:1;	//仅仅选择 Draw后的对象

	SG_BOOL OnlySelectDispObj:1;	//仅仅显示可见设备
	
	GeoMetrySelPara(){
		PointFirst	=	true;
		WholeContain = false;
		SearchAll = false;
		UseTolerance = true;
		AdvanceObjFirst = true;
		SelectWhileVisible = false;
		OnlySelectBeDrawObj	= false;
		OnlySelectDispObj	= false;
	}
};


///* 点型对象的几何属性管理类----可由任意多点组成 */
//class  CSgPoint
//{
//public:
//	CSgPoint();
//	~CSgPoint();
//	CSgPoint(const CSgPoint&xPoint);
//public:
//	/* 点的数量 */
//	SG_INT pointnums;
//	/* 所有的组成多点的点线性排列 */
//	SgPoint *pPoint;	
//	//几何属性可用判断
//	SG_BOOL IsNull(){
//		if(pointnums<1)return true;
//		if(!pPoint)return true;
//		return false;
//	}
//	// --- 所有点位偏移一定距离
//	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset){
//		for(SG_INT i=0;i<pointnums;i++)
//			pPoint[i].Offset(xOffset,yOffset);
//	}
//public:
//	//设置点数量
//	virtual void SetPointNums(SG_UINT PointNums);
//	CSgPoint& operator = (const CSgPoint &p);
//	SG_BOOL operator == (const CSgPoint &p);
//	//获得组成对象的点到一点的最小距离和点位置
//	SG_DOUBLE GetMinLen(SgPoint *pInPoint,SG_INT *pPointPos=NULL);
//	//网络同步传输用
//	SG_INT GetStructLen();			//获得点型结构的占用内存大小
////	void CreateMem(void *pCon);	//创建传输内存	方法外创建内存
////	void Build(void *pCon);		//根据网络传输来的LocalLib重构结构
//	SG_BOOL Serialize(CSgArchive&ar);
//};

//线型对象的几何属性管理类
//存储结构 (N个Part M个点)【PartNums】【Part0】...【PartN-1】【Point0】...【PointM－1】
//class  CSgLine
//{
//public:	
//	CSgLine();
//	~CSgLine();
//	CSgLine(const CSgLine&);
//	
//public:
//	//对象由几段组成
//	SG_INT GetPartNums();
//	//每段的终止点 － Base 0
//	SG_INT *GetPartBound();
//	//几何属性可用判断
//	SG_BOOL IsNull();
//	//获得总点数
//	SG_INT GetPointNums();
//	//获得起始点
//	SgPoint *GetFirstPoint();
//	//获得起始点
//	SgPoint *GetSecondPoint();
//	//获得终止点
//	SgPoint *GetLastPoint();
//	//获得倒数第二点
//	SgPoint *GetLastPoint1();
//	// --- 所有点位偏移一定距离
//	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset);
//	// --- 校正点位,使点位在SDE中提交时合法????? --- 最小单位为0.35um
//	void Correct();
//
//public:
//	// 判断段是否直线
//	inline SG_BOOL SegmentIsLine(SG_SHORT i,SG_CHAR* desc,SG_SHORT descLength)
//	{
//		if(!desc || i>=descLength) return true;
//		SG_UCHAR seg_type = (SG_UCHAR)(desc[i]);
//		seg_type &= 0x0f;   // 低四位 --- 类型
//		switch(seg_type) 
//		{
//		case SG_FE_Arc:
//		case SG_FE_BezeirLine:
//		case SG_FE_Curve:
//			return false;
//			break;
//		}
//		return true;
//	}
//	SG_BOOL AddSegment(SG_SHORT&/*第几段*/,SG_SHORT /*整条线第几个点开始*/,SG_SHORT* /*指针,第几个点结束*/);
//	SG_BOOL AddPoint(SgPoint pt,SG_SHORT /*整条线第几个点后插入*/);
//	SG_BOOL RemovePoint(SG_SHORT /*整条线第几个点移走*/);
//	SG_BOOL SplitLine(SG_SHORT idx/*整条线第几个点分断*/,CSgLine&newline);
//	SG_BOOL SplitLine(SG_SHORT idx/*整条线第几个点后分断*/,SgPoint pt,CSgLine&newline);
//	SG_BOOL JoinSegment(SG_SHORT idx/*idx段向前段合并*/);
//	SG_SHORT nth(SG_SHORT pt_idx/*idx是第几段上的点*/);
//	// --- 增加段
//	void AddPart(CSgLine &AddLine);
//	//设置点数量----面向一个段的线对象
//	void SetPointNums(SG_INT PointNums);
//	//设置点数量----面向多段的线对象
//	void SetPointNums(SG_INT PartNums,SG_INT PointNums);
//	//设置点数量----面向多段的线对象
//	void SetPointNums(SG_INT PartNums,SG_INT*pPartBound,SgPoint*pPoint);
//	/* 重载=号 */
//	CSgLine& operator = (const CSgLine &p);
//	/* 重载==号 */
//	SG_BOOL operator == (const CSgLine &p);
//	/* 重载!=号 */
//	SG_BOOL operator != (const CSgLine &p);
//	//计算线的长度
//	SG_DOUBLE GetLength();
//	//长度小于入参数
//	SG_BOOL LessThan(SG_FLOAT len);
//	//点在线的线段上判断 --- pos为线上的线段位置
//	SG_BOOL IsPointOn(SgPoint*pInPoint,SG_SHORT pos=0);
//	//点在线段上的位置
//	SG_INT PointOnLinePos(SgPoint*pInPoint);
//	//是复杂边上的点
//	SG_BOOL IsOnEdgeObj(CSgPoint*pInPoint,SG_INT &PointPos);
//	//是复杂边上的线
//	SG_BOOL IsOnEdgeObj(CSgLine*pInLine,SG_INT &PointPos);
//	//获得组成对象的点到一点的最小距离和点位置
//	SG_DOUBLE GetMinLen(SgPoint *pInPoint,SG_INT *pPointPos=NULL);
//	//翻转点序
//	void ReversePoint();
////	void CreateMem(void *pCon);	//创建传输内存	方法外创建内存
////	void Build(void *pCon);		//根据网络传输来的LocalLib重构结构
//	SG_BOOL Serialize(CSgArchive&ar);
//
//public:
//	// --- 强制破坏内存指针
//	void	SetMemPtrNull(){m_pMem=NULL;}
//	// --- 获得数据区首地址
//	SG_INT	*GetMemPtr(){return m_pMem;}
//	//获得线型结构的占用内存大小
//	SG_INT GetStructLen();			//获得线型结构的占用内存大小
//	// --- 获得结构指针部分分配的内存长度
//	SG_INT GetMemLen();
//private:
//	// --- 内存的首地址
//	SG_INT *m_pMem;
//};



/*与CSgPoint的差异在于
	1:其占用内存较大,但运行中需要动态改变点的数量时的效率较高
	2:重新设置点数量时,不丢失原先的内容
*/

class SG_CORE_API CSgSupperPoint
{
public:
	
	CSgSupperPoint(SG_INT step=3);
	
	~CSgSupperPoint();
public:
	
	SG_INT pointnums;
	
	SgPoint *pPoint;
protected:
	
	CSgSupperPoint(const CSgSupperPoint&);
	/* 开辟内存的长度(点数) */
	
	SG_INT MemLen;
	/* 开辟内存的步长(点数) */
	
	SG_INT Step;
	//	
public:
	
	SG_BOOL IsNull(){
		if(pointnums<1)return true;
		if(!pPoint)return true;
		return false;
	}
public:
	//获得点数量
	
	SG_INT GetPointNums(){return pointnums;}
	//设置点数量
	
	void SetPointNums(SG_UINT PointNums);
	//计算点组成的线的长度
	
	SG_DOUBLE GetLength();
	//等距创建一组点
	
	void CreateSameLengthPoint(CSgPoint *InP,SG_DOUBLE *pLen);
	//
	
	CSgSupperPoint& operator = (const CSgSupperPoint &p);
};

/*******************************************************
	Part 60	系统枚举类型定义
*******************************************************/

enum SG_ObjDispType{
	SG_OBJ_DISP_NORMAL	=	0,			//正常
	SG_OBJ_DISP_POWEROFF,				//失电
	SG_OBJ_DISP_NORMAL_SEL,				//正常被选择
	SG_OBJ_DISP_POWEROFF_SEL,			//失电被选择
};

enum SG_TopControlType{
	TOP_CONTROL_TYPE_USEITONLAY		=0,	//仅仅让对象可用
	TOP_CONTROL_TYPE_ERROR_RETURN	=1,	//该对象为错误方向上的对象
	TOP_CONTROL_TYPE_STOP			=2,	//该对象停止深度搜索
	TOP_CONTROL_TYPE_OBJ			=3,	//该对象为目标对象
};

//	内控属性的标志位枚举
enum SG_NetControlFlag
{
	NCF_TOP_USE				= 0x00000001,
	NCF_TOP_MAIN			= 0x00000002,
	NCF_TOP_STOP			= 0x00000004,
	NCF_TOP_ERR_DIR			= 0x00000008,

	NCF_SEARCH				= 0x00000010,
	NCF_TARGET				= 0x00000020,
	NCF_CHANGE				= 0x00000040,
	NCF_OVERLOAD			= 0x00000080,
};

//开关对象操作错误类型
enum SG_ObjOperErrorType
{
	SG_OBJ_OPER_ERROR_NOOBJ			=0,		//对象未找到
	SG_OBJ_OPER_ERROR_STATUSERROR	=1,		//入参数错误
	SG_OBJ_OPER_ERROR_SAME			=2,		//当前状态与操作后的状态一致,没有必要操作
	SG_OBJ_OPER_ERROR_MANSET		=3,		//对象置数,禁止遥控
	SG_OBJ_OPER_ERROR_SIGN			=4,		//对象挂禁止遥控性质牌
	SG_OBJ_OPER_ERROR_HASLOAD		=5,		//不允许带负荷分合
	SG_OBJ_OPER_ERROR_PUTGROUND		=6,		//停电区域内有设备接地
	SG_OBJ_OPER_ERROR_HUAWANG		=7,		//操作导致环网供电
	SG_OBJ_OPER_ERROR_SQUENCEOPER	=8,		//闸刀操作顺序问题	
	SG_OBJ_OPER_ERROR_FORBIDOPER	=9,		//设备不可操作
	SG_OBJ_OPER_ERROR_REVERSEPOWER  =10,    //变压器倒供电
	SG_OBJ_OPER_ERROR_RP_OPER       =11,     //变压器倒供电(开关可带负荷操作)
    SG_OBJ_OPER_ERROR_BIAODIAN      =12,     //保电
	SG_OBJ_OPER_ERROR_NO_POWERNO	=13,     //有不能通电的牌
	SG_OBJ_OPER_ERROR_NO_POWEROFF	=14,     //有不能失电的牌
};

#define	OPERTYPE_YK			0
#define	OPERTYPE_MANSET		1

static const char *SG_ObjOperErrorInfo[] =
{
	"对象未在电气网络中找到",
	"入参数状态错误",
	"当前状态与操作后的状态一致",
	"对象置数,禁止遥控",
	"对象挂禁止遥控性质牌",
	"不允许带负荷分合",
	"停电区域内有设备接地",
	"操作导致环网供电",
	"闸刀操作顺序问题",
	"对象不可操作",
	"变压器倒供电","",
    "停电区域内有保电设备"
};

//调度接口算法编号
enum SG_MMI_TOKEN_FUNC_TYPE
{
    SG_MMI_TOKEN_FUNC_MANTOKEN		=1,			//人字牌
    SG_MMI_TOKEN_FUNC_GROUNDTOKEN	=2,			//接地牌
    SG_MMI_TOKEN_FUNC_JIANXIU		=3,			//检修牌
    SG_MMI_TOKEN_FUNC_NOTYK			=4,			//禁止遥控
    SG_MMI_TOKEN_FUNC_KAIDUAN		=5,			//开断
    SG_MMI_TOKEN_FUNC_BAOANSUO		=6,			//保安锁符
    SG_MMI_TOKEN_FUNC_BUGTOKEN		=7,			//缺陷牌
    SG_MMI_TOKEN_FUNC_BUKEBING		=8,			//不可并符
    SG_MMI_TOKEN_FUNC_ZHONGYAOYONGHU=9,			//重要用户符
    SG_MMI_TOKEN_FUNC_LINSHIBAODIAN	=10,		//临时保电符 
    SG_MMI_TOKEN_FUNC_WEIXIANFU		=11,		//尾线符
    SG_MMI_TOKEN_FUNC_ZIQIEFU		=12,		//自切符 
    SG_MMI_TOKEN_FUNC_DANQIEFU		=13,		//单切符 
    SG_MMI_TOKEN_FUNC_TINGYONGFU	=14,		//停用符 
    SG_MMI_TOKEN_FUNC_SHOUDONGFU	=15,		//手动符 
    SG_MMI_TOKEN_FUNC_XINHAOFU		=16,		//信号符  
    SG_MMI_TOKEN_FUNC_BAODIANFU		=17,		//保电符
    SG_MMI_TOKEN_FUNC_YK			=18,		//可遥控符
    SG_MMI_TOKEN_FUNC_LINSHIFU		=19,		//临时符
    SG_MMI_TOKEN_FUNC_FANGLEIFU		=20,		//防雷符
    SG_MMI_TOKEN_FUNC_KKD           =21         //开口点牌(市东提出)
};
// GIS 表应用类型定义
enum SG_TableAppType{
	SG_T_APPTYPE_SYS=0,		//系统结构数据
	SG_T_APPTYPE_GIS=1,		//系统台帐数据
	SG_T_APPTYPE_MNG=2,		//系统管理数据
	SG_T_APPTYPE_OPT=3		//系统业务数据
};

// GIS 自由绘图图元类型定义
/*
create table SYS_OBJECT_NO 	-- 非对象表
(
	"ID" 					NUMBER(4) NOT null primary key ,--标识号
	"NAME"		 			VARCHAR2(40) not null,			--外部名
	"LOAD_USE_WORLD_ID" 	NUMBER(3) default 0,			--按照WorldID装载
	"UNIVERSE_VIEW"			NUMBER(9),						--与Universe类型的关系：
	"EXT_FEATURE_TYPE"		NUMBER(4),			---非对象化图形扩展特征类型
	"SPATIAL_DS_TYPE"		NUMBER(9),			--空间数据源类型：0不具有空间数据属性、1-SDE、2-Coverage、3-Shape、4-OracleSpatial、5-SelfDefTable、6-.DXF
	"SPATIAL_DS_INFO"		VARCHAR2(48),		--空间数据源信息：
	SG_SYS_O_SPATIAL_DS_TABLE_NAME	VARCHAR2(32),		--空间数据表名
	"BRUSH_ATTRIB"          NUMBER(10),
	"PEN_ATTRIB"            NUMBER(10),
	"PEN_WIDTH"             NUMBER(4)
);
grant select on SYS_OBJECT_NO to public;
create unique index SYS_OBJECT_NO_Ind on SYS_OBJECT_NO(NAME);
*/

//空间数据源类型
enum SG_SDLoadType{
	SG_SPATIALTYPE_NONE		=	0,
	SG_SPATIALTYPE_SDE		=	1,
	SG_SPATIALTYPE_COVERAGE,
	SG_SPATIALTYPE_SHAPEFILE,
	SG_SPATIALTYPE_ORACLESPATIAL,
	SG_SPATIALTYPE_SELFDEFTABLE,
	SG_SPATIALTYPE_DXF,
	SG_SPATIALTYPE_MAPINFO,
	SG_SPATIALTYPE_SPATIALWARE
};
//属性数据源类型
enum SG_ADLoadType{
	SG_DBF_TYPE_NONE=0,		//	0不具有扩展台帐属性
	SG_DBF_TYPE_ORACLE,		//	1-Oracle
	SG_DBF_TYPE_SYBASE,		//	2-Sybase
	SG_DBF_TYPE_SQLSERVER,	//	3-SqlServer
	SG_DBF_TYPE_DB2,		//	4-DB2
	SG_DBF_TYPE_SELFDS		//	5-Self Data Server（必须为只读）
};


// --- 对象模型变换方式
enum SG_ModelChange_TYPE
{
	SG_MODELCHANGE_NONE 		=	0,	//不处理
	SG_MODELCHANGE_NORMAL		=	1,	//缺省规则
	SG_MODELCHANGE_PASSBY		=	2,	//直通化简(如闸刀、跨接线往往如此简化)
	SG_MODELCHANGE_TRANS4Point	=	3,	//三卷变四点模型
	SG_MODELCHANGE_TRANS2Point	=	4	//两卷变两点模型
};
//对象分类
enum SG_ObjectKind_TYPE
{
	SG_ObjectKind_BASEOBJ	=0,	//基础对象
	SG_ObjectKind_YAOCEOBJ	=1,	//遥测
	SG_ObjectKind_LABELOBJ	=2,	//标注
	SG_ObjectKind_ExtObj	=3	//扩展对象
};

//宇宙类型
enum SG_UniverseType
{
	SG_UNIVERSETYPE_GIS				=0x01,		//地理全图
	SG_UNIVERSETYPE_SINGLELINE		=0x02,		//单线图
	SG_UNIVERSETYPE_MULTILINE		=0x04,		//网络图
	SG_UNIVERSETYPE_SCHEMATICS		=0x08,		//电气接线图
	SG_UNIVERSETYPE_APPOINTOBJ		=0x10,		//选择集图(指定对象属性层和行号后形成单独视图)
	SG_UNIVERSETYPE_ZNJXT			=0x20,		//站内接线图
	SG_UNIVERSETYPE_PLANE			=0x40,		//间隔布置图(变电站间隔布置图、平面布置图、其它自由写划的图)
	SG_UNIVERSETYPE_PIPEROUTE		=0x80,		//电缆通道图	
	SG_UNIVERSETYPE_MIRROR			=0x100,		//设备镜像图(工作票/检修任务书)
	SG_UNIVERSETYPE_CORRIDOR		=0x200,		//走廊图
	SG_UNIVERSETYPE_ANVI			=0x400,		//导航图
    SG_UNIVERSETYPE_1JXT			=0x800,		//站内一次图。反映具体位置,无拓扑
    SG_UNIVERSETYPE_SYMBOL			=0x1000,	//符号编辑图
	SG_UNIVERSETYPE_OFFLINE			=0x2000,	//离线图(SYS_OBJECT中对象与Universe的关系配置无效，针对该类型视图，具有更复杂的处理过程，参考“概要设计_图形实用化改进”中的“离线图的支持”一章)
	SG_UNIVERSETYPE_PRINT_LAYOUT	=0x4000,	//打印布局图,用于从不同的视图中选择部分组合而成的视图
	SG_UNIVERSETYPE_TEMPLATE		=0x8000,	//编辑模版图
	SG_UNIVERSETYPE_LV_MULTILINES	=0X10000,	//低压台区图
	SG_UNIVERSETYPE_STATION_RANGE	=0X20000,	//电站分布图
	SG_UNIVERSETYPE_GXMAP			=0X40000,	//用户接入方案图
	SG_UNIVERSETYPE_SUPPLYPOINT		=0X80000,	//接电点内部图
	SG_UNIVERSETYPE_MEASURESPACE	=0X100000,	//计量间内部图	
	SG_UNIVERSETYPE_GEO_LAYOUT		=0X200000,	//规划地理走向图
	SG_UNIVERSETYPE_PROTECTOR		=0X400000,	//保护二次图
	SG_UNIVERSETYPE_THEME			=0x800000,	//专题图	

	SG_UNIVERSETYPE_PIPE_SECTION	=0x1000000,	//管道截面图
	SG_UNIVERSETYPE_GIS_BAY			=0x2000000,	//规划间隔布置图
	SG_UNIVERSETYPE_SPECIAL			=0x3000000,	//特殊图
	SG_UNIVERSETYPE_CUSTOM3			=0x4000000,	//未用
	SG_UNIVERSETYPE_POLLUTE			=15,		//暂时不用
	SG_UNIVERSETYPE_GUARDLINE		=25,		//暂时不用
	SG_UNIVERSETYPE_LOOPED_NETWORT  =26,		//配电监测用环网图	
	SG_UNIVERSETYPE_LV_MONITOR		=27,		//低压电网监控图
	SG_UNIVERSETYPE_LAYOUT_STA				=261,		//自动布局电站索引图
	SG_UNIVERSETYPE_LAYOUT_RANGE			=262,		//自动布局供电范围图
	SG_UNIVERSETYPE_LAYOUT_SCHEMATIC		=263,		//自动布局电系图
	SG_UNIVERSETYPE_LAYOUT_SCHEMATIC_LINE	=264,		//自动布局布局电系单线图
        SG_UNIVERSETYPE_LAYOUT_BREAKER_STA		=265,		//开关站图
        SG_UNIVERSETYPE_REALTIME               =266,//实时数据
        SG_UNIVERSETYPE_LAYOUT_SCHEMATIC_DETAIL_LINE	=267,//单线详图
        SG_UNIVERSETYPE_LAYOUT_QWXTT			=268,		//全网专题图
        SG_UNIVERSETYPE_LAYOUT_QWFT				=269,		//全网辅图
        SG_UNIVERSETYPE_LAYOUT_ROUTE			=270,		//线路图
        SG_UNIVERSETYPE_MAN_HOLE_SECTION        =520,		//电缆井剖面图
};

//网络类型
enum SG_NetWorkType{
	SG_NETWORKTYPE_NONE=1,			//无
	SG_NETWORKTYPE_GEO=2,			//地理网络
	SG_NETWORKTYPE_ELECTRIC=3,		//电气网络
	SG_NETWORKTYPE_STREET=4,		//路网网络
	SG_NETWORKTYPE_PIPELINE=5,		//管线网络
	SG_NETWORKTYPE_COMMULINE=6,		//通信网络
	SG_NETWORKTYPE_WORK	= 7,		//作业网络
	SG_NETWORKTYPE_CARRIER = 8,		//载波网络
	SG_NETWORKTYPE_TLINE = 9,		//有线网络
	SG_NETWORKTYPE_TNOLINE = 10,	//无线网络
	SG_NETWORKTYPE_LAYOUT = 11,		//自动布局电系图网络
	SG_NETWORKTYPE_WATER = 12,		//水网
	SG_NETWORKTYPE_GAS = 13,		//气网
	SG_NETWORKTYPE_HEATING = 14		//热网
};

//World居中显示性质
enum SG_ActiveCenterType
{
	SG_ACTIVECENTERTYPE_NOCHANGE=0,			//不改变视野范围
	SG_ACTIVECENTERTYPE_SETWIDTH=1,			//按设定的视野改变视野范围
	SG_ACTIVECENTERTYPE_AUTODEAL=2,			//当前对象自适应窗口;
	SG_ACTIVECENTERTYPE_CONTAINER=3,		//适用于没有几何属性的容器类对象,以子设备（递归）集合居中定位；
};

//电系性质
enum SG_PowerType
{
	SG_POWERTYPE_NORMAL=0,				//通常对象
	SG_POWERTYPE_POWERPOINT=1,			//可作为电源点
	SG_POWERTYPE_GROUNDPOINT=2,			//作为接地点
	SG_POWERTYPE_SUBPOWER=3,			//二级电源点
	SG_POWERTYPE_LINE_START=4,			//作为线路起点
	SG_POWERTYPE_LINE_END=5,			//作为线路终点
	SG_POWERTYPE_CKKG=6,				//作为出口开关
	SG_POWERTYPE_LLKG=7,				//作为联络开关
	SG_POWERTYPE_CKLLKG=8				//即可作为出口开关，又可作为联络开关
};

enum SG_Ground_Attrib
{
	SG_GROUND_ATRRIB_COMMON		=0,		//接入大地
	SG_GROUND_ATRRIB_TRANS		=1,		//变压器中性点接地
};

//电气性质
enum SG_ElectricType{
	SG_ELECTRICTYPE_NORMAL=0,			//一般设备
	SG_ELECTRICTYPE_LINE=1,				//导线
	SG_ELECTRICTYPE_BREAK=2,			//开断
	SG_ELECTRICTYPE_TRANS=3,			//变压
	SG_ELECTRICTYPE_BUS=4,				//电力系统母线
	SG_ELECTRICTYPE_SIGNAL=5,			//信号量对象
	SG_ELECTRICTYPE_LINKLINE=6,			//连接线对象
	SG_ELECTRICTYPE_LARGERESISTOR=7,	//无穷大电阻
	SG_ELECTRICTYPE_DUMMY_POLE=8,		//虚拟杆
	SG_ELECTRICTYPE_CABLE=9,            //电缆设备  
	SG_ELECTRICTYPE_FIBER_NODE=10,		//光缆接头类设备
	SG_ELECTRICTYPE_CAPACITOR=11,		//电容器
	SG_ELECTRICTYPE_SERI_REACTOR=12,	//串联电抗器
	SG_ELECTRICTYPE_PARA_REACTOR=13,	//并联电抗器
	SG_ELECTRICTYPE_MOTOR		=14		//发电机

};

//设施设备分类
enum SG_DeviceClass{
	SG_DEVICECLASS_ONCE			=1,		//一次设备
	SG_DEVICECLASS_TWICE		=2,		//继保设备
	SG_DEVICECLASS_MONITOR		=3,		//自动化设备
	SG_DEVICECLASS_LINE			=4,		//线路设备
	SG_DEVICECLASS_CABLE		=5,		//电缆设备
	SG_DEVICECLASS_BUILDING		=6,		//土建设备
    SG_DEVICECLASS_PRINTWARE	=7,     //打印固件
    SG_DEVICECLASS_1JXT			=8,     //一次图设备
    SG_DEVICECLASS_INSPECT		=9,     //高效巡线设备
	SG_DEVICECLASS_USERDEVICE	=10,    //用户设备
    SG_DEVICECLASS_ASSISDEVICE	=11,	//辅助设备【如：消防拴、空调，GAP三期中扩充】
	SG_DEVICECLASS_DESIGN		=16,	//设计类设备
	SG_DEVICECLASS_GUARDLINE	=17,	//黄线相关设备
	SG_DEVICECLASS_CITYPLAN		=18,	//城市规划数据
	SG_DEVICECLASS_BPA		=19,		//BPA设备
	SG_DEVICECLASS_PRODUCT		=20,	//生产设备(引用)
	SG_DEVICECLASS_DUMMYDEVICE	=99		//虚拟设备
};

//做图规则
#ifdef AUTO_MAP
enum SG_DrawRule{

	SG_DRAWRULE_NONE=1,				//无
	SG_DRAWRULE_RECT,				//拉框矩形
	SG_DRAWRULE_ROUND_RECT,			//拉框圆角矩形
	SG_DRAWRULE_CLICK,				//点击
	SG_DRAWRULE_PLINE,				//轨迹线
	SG_DRAWRULE_TWOCLICK,			//两点设备间成图
	SG_DRAWRULE_LINE,				//两点设备,线段
	SG_DRAWRULE_MULTIDEVICE,		//多选设备
	SG_DRAWRULE_POLYGON,			//多边形
	SG_DRAWRULE_TEMPLATE,			//按模板生成
	SG_DRAWRULE_CIRCLE,			//圆轨迹
	SG_DRAWRULE_ELLIPSE,			//椭圆轨迹
	SG_DRAWRULE_BEZIER,			//贝赛尔曲线
	SG_DRAWRULE_ARC,				//弧线
	SG_DRAWRULE_PIE,				//扇
	SG_DRAWRULE_ANCHOR_LINE,		//锚点线
	SG_DRAWRULE_TEXT_LINE,				//文字线
	SG_DRAWRULE_LINE_POLE,			//杆线并录
	SG_DRAWRULE_CUSTOM_MESSAGE,		//响应一个消息
	//SG_DRAWRULE_NONE=0x00,				//无
	//SG_DRAWRULE_RECT=0x01,				//拉框
	//SG_DRAWRULE_CLICK=0x02,				//点击
	//SG_DRAWRULE_PLINE=0x04,				//轨迹线
	//SG_DRAWRULE_TWOCLICK=0x08,			//两点设备间成图
	//SG_DRAWRULE_LINE=0x10,				//两点设备
	//SG_DRAWRULE_MULTIDEVICE=0x20,		//多选设备
	//SG_DRAWRULE_POLYGON=0x40,			//多边形
	//SG_DRAWRULE_TEMPLATE=0x80,			//按模板生成
	//SG_DRAWRULE_CIRCLE=0x200,			//圆轨迹
	//SG_DRAWRULE_ELLIPSE=0x400,			//椭圆轨迹
	//SG_DRAWRULE_BEZIER=0x800,			//贝赛尔曲线
	//SG_DRAWRULE_ARC=0x1000				//弧线
};
#else
//做图规则
enum SG_DrawRule{
	SG_DRAWRULE_NONE=0x00,				//无
	SG_DRAWRULE_RECT=0x01,				//拉框
	SG_DRAWRULE_CLICK=0x02,				//点击
	SG_DRAWRULE_PLINE=0x04,				//轨迹线
	SG_DRAWRULE_TWOCLICK=0x08,			//两点设备间成图
	SG_DRAWRULE_LINE=0x10,				//两点设备
	SG_DRAWRULE_MULTIDEVICE=0x20,		//多选设备
	SG_DRAWRULE_POLYGON=0x40,			//多边形
	SG_DRAWRULE_TEMPLATE=0x80,			//按模板生成
	SG_DRAWRULE_CIRCLE=0x200,			//圆轨迹
	SG_DRAWRULE_ELLIPSE=0x400,			//椭圆轨迹
	SG_DRAWRULE_BEZIER=0x800,			//贝赛尔曲线
	SG_DRAWRULE_ARC=0x1000,				//弧线
	SG_DRAWRULE_PIE=0x2000,				//扇
	SG_DRAWRULE_ANCHOR_LINE=0x4000,		//锚点线
	SG_DRAWRULE_TEXT_LINE=0x8000,			//文字线
	SG_DRAWRULE_LINE_POLE=0x10000,			//杆线并录
	SG_DRAWRULE_CUSTOM_MESSAGE=0x20000,		//响应一个消息
	SG_DRAWRULE_ROUND_RECT=0x40000
};
#endif


//线符号特性
enum SG_LineSymbolType{
	SG_LINESYMBOLTYPE_NORMALLINE=0,				//常规线
	SG_LINESYMBOLTYPE_NORMALSYMBOL=1,			//首尾点做铆点挂符号
	SG_LINESYMBOLTYPE_STARTPOINTSYMBOL=2,		//首端点挂点符号
	SG_LINESYMBOLTYPE_ENDPOINTSYMBOL=3,			//末端点挂点符号
	SG_LINESYMBOLTYPE_LINESYMBOL=4,				//线符号
	SG_LINESYMBOLTYPE_TWOSYMBOL=5,				//首尾线段都挂符号(P0)-(P1)挂符号，(Pl)-(Pl-1)挂符号+1
	SG_LINESYMBOLTYPE_TWOSYMBOL_AND_LINE=6,		//首尾线段都挂符号且画线
	SG_LINESYMBOLTYPE_CFGSYMBOL=7				//根据SYMMODE的配置信息确定是否需要绘制符号			
};

enum SG_LineSymbol_SymMode{
	SG_LINESYMBOLTYPE_SYMMODE_NONE=0,				//常规线
	SG_LINESYMBOLTYPE_SYMMODE_START=1,			//首点做铆点挂符号
	SG_LINESYMBOLTYPE_SYMMODE_END=2,			//尾点做铆点挂符号
	SG_LINESYMBOLTYPE_SYMMODE_BOTH=3			//首尾点做铆点挂符号				
};

//点符号特性
enum SG_PointSymbolType{
	SG_POINTSYMBOLTYPE_NORMAL=0,				//常规点----（可用视图的参数Obj_Scale调整显示大小）
	SG_POINTSYMBOLTYPE_SYMBOL=4						//点符号----(自身的尺寸和角度形成地理铆点)
};

//点选（点对象）的方法
enum SG_PointSelType{
	SG_POINTSELTYPE_TOLERANCE=0,			//用容差成圆包含点位
	SG_POINTSELTYPE_INREGION=1,				//点位落在对象的图形区域内
};


//点选（线区域对象）的方法
enum SG_LineRegionSel_Type{
	SG_LINEREGIONSELTYPE_TOLERANCE=0,			//用容差成圆相交轮廓线
	SG_LINEREGIONSELTYPE_INREGION=1,			//点位落在对象的图形区域内
};

//"对象类型"具有的内控属性类型
enum SG_Obj_InsideAttrib_Type{
	SG_OBJ_INSIDEATTRIB_NONE=		0x00,			//无
	SG_OBJ_INSIDEATTRIB_LABEL=		0x01,			//设备可标注
	SG_OBJ_INSIDEATTRIB_COMMON=		0x02,			//一般属性
	SG_OBJ_INSIDEATTRIB_VALUE=		0x04,			//值属性
	SG_OBJ_INSIDEATTRIB_YC=			0x08,			//遥测属性
	SG_OBJ_INSIDEATTRIB_MANSET=		0x10,			//置数属性
	SG_OBJ_INSIDEATTRIB_PUTSIGN=	0x20,			//挂牌属性
	SG_OBJ_INSIDEATTRIB_DIRECTION=	0x40,			//方向特征属性
	SG_OBJ_INSIDEATTRIB_OVERLOAD=	0x80,			//过载属性
};


//拓扑计算方式
enum SG_TopCalType{
	SG_TOPCALTYPE_NONE=0x00,					//
	SG_TOPCALTYPE_TWOPOINT1=0x01,				//一条线路内两点之间设备统计
	SG_TOPCALTYPE_TWOPOINT2=0x02,				//两条环网线路两点之间设备统计
	SG_TOPCALTYPE_ONEPOINT=0x04,				//一点开始向负荷侧的统计
	SG_TOPCALTYPE_MAINPATH=0x08,				//两点之间主路径计算
};

//域属性－输入方式
enum SysFieldInputMode{
	INPUTMODE_NONE		=0,		//无扩展属性
	INPUTMODE_BOOL,				//是否类型
	//数字索引字符型-DoMain
	// CTableObj的实例为扩展类型,如果TableName=="SYS_DOMAIN_TABLE",内容不用加载,从CObjModel中获得
	//							否则要检索m_OtherTable中是否已加载,加载内容
	//FuncStr种的内容位选择条件.
	INPUTMODE_MATHINDEX		,
	//***多可选项相或 解决如一个对象可以在多种Universe中出现的配置问题
	//	采用该策略,将各种可选的宇宙类型按位有效,可以大大减少系统的表级一对多问题导致的表数量增加.
	//该属性设置后,其具有INPUTMODE_MATHINDEX的其他特征
	INPUTMODE_ORMULTIVALUE	,
	//系统的所有的度量规范后可以有效解决计算问题,但往往不能满足显示的需要
	//	该输入方式下,FuncStr中存储变化系数和显示的单位字符串.用","分开
	INPUTMODE_CHANGEUNIT	,	//***单位变化型
	INPUTMODE_COLOR	,			//颜色值
	INPUTMODE_FONT	,			//字体
	INPUTMODE_RELATIONTABLE	,	//关系对照表类型
	INPUTMODE_GISOBJNAME	,	//获得GIS对象表征名称
	INPUTMODE_DATE			,	//日期型
	INPUTMODE_TIME			,	//时间型
	INPUTMODE_BOUNDCHECK	,	//边界检测类型
	INPUTMODE_CALCULATE		,	//计算组合型
	INPUTMODE_RULE			,	//编码规则型
	INPUTMODE_COUNT			,	//自动累加
	INPUTMODE_MANNAME		,	//操作人员型
	INPUTMODE_DYNAMIC_DOMAIN,	//动态domain
    INPUTMODE_TREE          ,   //设备树选择型
	INPUTMODE_DEPART        ,   //操作人员所属部门
	INPUTMODE_FMTYPE        ,   //铭牌选择型
	INPUTMODE_WORKER        ,   //人员选择型
	INPUTMODE_COMPANY        ,   //单位选择
};

enum SYS_MANDATORY
{
    MT_OTHER					=0,		//其它
    MT_COMMON 			        =1,		//一般
    MT_IMPORTANT   			    =2,		//重要
    MT_DELETE        			=3,		//待删除
    MT_NECESSARY        		=4	    //必须
};
//数据来源属性
enum SysDataFrom{
	SysDataFrom_Man		=0,		//手工输入
	SysDataFrom_CHY		=1,		//测绘院
	SysDataFrom_3D		=2,		//三维测量
};

//网络传输用定义
enum SG_NET_DEF
{
	SG_NET_DATASET_RELOAD   =0,
	SG_NET_DATASET_INSERT	=1,
	SG_NET_DATASET_UPDATE	=2,
	SG_NET_DATASET_DELETE	=3,
	SG_NET_ATTRIB_CREATE	=4,
	SG_NET_ATTRIB_MODIFY	=5,
	SG_NET_ATTRIB_DELETE	=6,
	SG_NET_OBJ_ARRAY		=7,//对象队列
	SG_NET_DATASET_ORI		=8,//修改前的原始对象
	SG_NET_FDU_CHANGE		=9,//FDU变更同步处理
	SG_NET_WHOLE_CHANGE		=10, //整表变更
};

//对象修改标记 --- 无版本控制时通过属性区分对象的性质
enum SG_OBJ_EDIT_DEF
{
	SG_OBJ_EDIT_NOCHANGE	=0,
	SG_OBJ_EDIT_ADD			=1,
	SG_OBJ_EDIT_MODI		=2,
	SG_OBJ_EDIT_DELETE		=3,
};


// --- 空间数据加载方式
enum	SG_SYS_SDE_LOAD
{
	SG_SYS_SDE_LOAD_NULL	=0,		//不加载
	SG_SYS_SDE_LOAD_STRUCT	=1,		//只加载结构
	SG_SYS_SDE_LOAD_ALL		=2,		//全部加载
	SG_SYS_SDE_LOAD_WORLDID	=3,		//按照WorldID加载
	SG_SYS_SDE_LOAD_RANGE	=4,		//按照空间范围
	SG_SYS_SDE_LOAD_FATHER	=5	,	//'父设备对象控制'
	SG_SYS_SDE_LOAD_CHILD	=6	,	//'基础对象控制'
	SG_SYS_SDE_LOAD_COMPANY	=7	,	//'按照所属公司加载'
	SG_SYS_SDE_LOAD_VOLTLEVEL=8	,	//按照电压等级加载
	SG_SYS_SDE_LOAD_SQL		=9,		//标准Sql语句方式控制加载
	SG_SYS_SDE_LOAD_THROUGH	=10,	//直通模式加载，服务端仅作为透明通道，服务端不缓存任何数据
    SG_SYS_SDE_LOAD_RANGE_AND1=11,  //按范围与(条件优先)
    SG_SYS_SDE_LOAD_OBJNODE=12,     //按基础设备的NODE过滤(如导线搭头)
	SG_SYS_SDE_LOAD_RANGE1_AND=13  //按范围与(范围优先)
};
// --- 属性数据加载方式
enum	SG_SYS_FM_LOAD
{
	SG_SYS_FM_LOAD_NULL		=0	,		//'不启用'
	SG_SYS_FM_LOAD_FATHER	=1	,		//'父设备对象控制'
	SG_SYS_FM_LOAD_CHILD	=2	,		//'基础对象控制'
	SG_SYS_FM_LOAD_COMPANY	=3	,		//'按照所属公司加载'
	SG_SYS_FM_LOAD_IDRANGE	=4	,		//'按照ID范围加载'
};

// 线路的 SUBTYPE 定义
enum SG_SYS_LINE_SUBTYPE
{
	SG_SYS_LINE_NULL		= 0 ,
	SG_SYS_LINE_OVERHEAD	= 1	,		// 架空线路
	SG_SYS_LINE_CABLE		= 2	,		// 电缆线路, 配电线路
};

enum SG_DynamicLoadType
{
	fullLoad		=0,					//	全加载
	fullDynamicLoad =1,					//	全动态加载
	halfDynamicLoad =2,					//  半动态加载
	worldLoad		=3,					//  按WORLD加载
	fduLoad			=4,					//  fdu方式加载
	customLoad		=5					//  自定义加载
};

enum SG_DataShareMode
{
	DataModeNormal	=0,					//	普通属性层数据
	DataModeShared	=1,					//	共享属性层数据
};

/*******************************************************
	Part 90	与SCADA接口结构定义
*******************************************************/
	

struct SG_SCADA_PACK_HEAD{
	
	unsigned SG_CHAR CompanyID;
	
	unsigned SG_CHAR ScadaID;
	
	unsigned SG_CHAR DataType;
	
	unsigned SG_CHAR RecordLen;
	
	unsigned short RecordNums;
};

/*******************************************************
	Part 100 视图的应用结构定义
*******************************************************/
#define		SG_SYS_VOLT_LEVEL_NUMS		100		//系统电压等级的内码最最大上限值


struct SG_LAYER_ATTRIB
{
	
	SG_BOOL		visible;		//可见
	
	SG_BOOL		selectAble;		//可选择
	
	SG_BOOL		editAble;		//可编辑
	
	SG_BOOL		labelAble;		//标注显示
	
	SG_LAYER_ATTRIB()
	{
		visible=true;
		selectAble=true;
		editAble=false;
		labelAble=true;
	}
};

//
//获得线属性的入参数

struct SG_LINE_ATTRIB_GET_PARA
{
	
	ObjAttribStruct_Base *pObjAttrib;	//内控属性
	
	ObjType_IA_Cfg_Struct*pObjConfig;	//配置参数
	
	SG_LINE_ATTRIB*		  pLineConfig;	//线对象缺省配置参数
	
	SG_UCHAR CalStatus;					//计算状态
	
	SG_UCHAR Disp_Type;					//显示方式
	
	SG_SHORT Volt_Level;					//电压等级

	//扩充 by lanbb 2015-12-14 专题图对象的关联的基础对象的内控属性，专题图的带电状态取决于关联的地理图
	//可为空
	ObjAttribStruct_Base *pBaseObjAttrib;	//关联对象的内控属性
	SG_LINE_ATTRIB_GET_PARA()
	{
		pObjAttrib = NULL;
		pObjConfig = NULL;
		pLineConfig = NULL;
		pBaseObjAttrib = NULL;
	}
};

/*******************************************************
	Part 110 视图相关枚举类型定义
*******************************************************/
//世界处于的状态
enum SG_WORLD_STATUS{
	SG_WORLD_STATUS_VIWER = 0,		//浏览
	SG_WORLD_STATUS_EDIT,			//编辑
    SG_WORLD_STATUS_PRINT,          //打印
	//复用
	SG_WORLD_STATUS_SAFE,           //安全运行模式
	SG_WORLD_STATUS_STUDY           //模拟态
};
//系统显示策略
enum SG_WORLD_DISP_TYPE{
	SG_WORLD_DISP_TYPE_DEFAULT=0,	//缺省各种设备按照设定的图层颜色显示
	SG_WORLD_DISP_TYPE_REAL,		//实时按照红合绿分的原则动态着色
	SG_WORLD_DISP_TYPE_LINE,		//按线路的色标配色动态着色
	SG_WORLD_DISP_TYPE_POWERPOINT,	//按照电源点的覆盖范围动态着色
	SG_WORLD_DISP_TYPE_PROMIN,		//系统设定的方式着重显示具有特定标记的对象
	SG_WORLD_DISP_VOLTAGE_LEVEL,	//按照电压等级方式，目前只是占位
	SG_WORLD_DISP_INTERSEPT_BMP,	//截取位图时的显示方式，带电设备为红色、不带电为黑色	
};

enum SG_MAINT_STATUS
{
	SG_M_STATUS_TRUE_ADD			=1,		//实际增加操作引起的记录增加
	SG_M_STATUS_TRUE_DELETE_BASEOBJ	=2,		//实际删除操作引,对基表的删除
	SG_M_STATUS_TRUE_DELETE_A_OBJ	=3,		//实际删除操作引,对A表的删除
	SG_M_STATUS_MODI_DELETE_BASEOBJ	=4,		//修改导致的删除,对基表的删除
	SG_M_STATUS_MODI_ADD_BASEOBJ	=5,		//修改导致的增加,对基表的增加
	SG_M_STATUS_MODI_DELETE_A_OBJ	=6,		//修改导致的删除,对A表的删除
	SG_M_STATUS_MODI_ADD_A_OBJ		=7		//修改导致的增加,对A表的增加
};

/*******************************************************
	part 130 系统特定表结构
*******************************************************/
//牌对象属性固定字段 见 csignlayer.h 中的描述

struct SG_SIGN_LAYER_STRUCT
{
	
	SG_SHORT	id;
	
	SG_SHORT	BaseObjType;
	
	SG_SHORT	BaseObjID;
	
	SG_SHORT	SignType;
	
	SG_SHORT	Offsetx;
	
	SG_SHORT	Offsety;
	
	SG_SHORT	LineColor;
};
//牌性质固定字段 见 csignlayer.h 中的描述

struct SG_SIGN_ATTRIB_STRUCT
{
	
	SG_SHORT	id;
	
	SG_SHORT	name;
	
	SG_SHORT	OperPowerOn;
	
	SG_SHORT	OperPowerOff;
	
	SG_SHORT	OperManset;
	
	SG_SHORT	RefuseYk;
	
	SG_SHORT	PutGround;
	
	SG_SHORT	BreakOpen;
	
	SG_SHORT	MmiFuncCheck;
};
//特殊对象的扩展标注字段索引
enum SGF_EXTEND_POS
{
	SG_FETCH_PARENT_OBJ_FDPOS=501,   //获取父对象的字段POS
	SG_FETCH_GRANDPA_OBJ_FDPOS
};

// --- 服务器加载控制参数

struct	SG_CORE_API LoadControlPara
{
	
	SG_SHORT	ObjType;		//对象(或扩展对象)的类型
	
//	SG_UCHAR	IsObj;			//是否是对象(相对于扩展对象)
	
	SG_UCHAR	SdeLoadType;	//几何属性加载类型
	SG_UCHAR    IsWorldLoad;    //WORLD是否已加载
	SG_UCHAR	IsPluginLoad;	//是否在插件中已加载
	
	SG_LONG		WorldID;		//当前的WorldID
	
	CSgString	FieldName;		//加载的字段名为空或空字符串时缺省选择所有字段
	
	CSgString	WhereClause;	//加载的Where子句
	
	SG_UCHAR	OnlyLoadTableInfo;	//仅加载表结构

	SG_UCHAR	IsLoadVer;
	
	LoadControlPara(){
		ObjType = 0;
//		IsObj	= true;
		SdeLoadType = SG_SYS_SDE_LOAD_ALL;
//为图形版本增加 start
		IsWorldLoad=false;
//为图形版本增加 end
		WorldID = 0;
		OnlyLoadTableInfo=0;
		IsPluginLoad=0;
		IsLoadVer = 0;
	}
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
	virtual SG_BOOL Serialize2(CSgArchive&ar);
};

// --- 网络收发数据集删除组织结构
//注意：发送和接收不对称  接收时不读取Flag、发送时发送Flag

struct SG_CORE_API NetSendDbfDeleteStruct{
	
	SG_INT		VersionNo;		// --- 版本号
	
	SG_INT		Flag;			// --- 删除标志
	
	CSgString	m_TableName;	// --- 表名
	
	CSgObjects	m_IDs;			// --- 对象ID
	
	SG_BOOL Serialize(CSgArchive&ar);
	
	NetSendDbfDeleteStruct();
	
	SG_CHAR*GetName(){
		return m_TableName.GetSafeBuffer();
	}
};

//////////////////////////////////////////////////////////////////////////
struct SG_CORE_API RefObject
{
	SG_SHORT	ObjType;
	SG_LONG		ObjID;
	SG_SHORT	status;
	RefObject(){
		ObjType=0;
		ObjID=0;
		status=-1;
	}
	
};

struct SG_CORE_API RefObjectSet
{
	SG_UINT MemNums;
	SG_UINT ObjNums;
	RefObject *pObj;
	RefObjectSet(){MemNums=0;ObjNums=0;pObj=0;}
	~RefObjectSet(){
		if(pObj)free(pObj);
		pObj = NULL;
	}
	void SetSize(SG_UINT nums){
		if(nums<=MemNums){
			if(pObj!=NULL)return;
		}
		if(pObj==NULL)
			pObj = (RefObject*)malloc(sizeof(RefObject)*nums);
		else{
			SG_CHAR*p = (SG_CHAR*)malloc(sizeof(RefObject)*nums);
			memcpy(p,pObj,sizeof(RefObject)*MemNums);
			free(pObj);
			pObj=(RefObject*)p;
		}
		MemNums=nums;
	}
	void Add(RefObject obj){
		if(obj.ObjType<0 || obj.ObjID<0)return;
		if(ObjNums>=MemNums)
			SetSize(ObjNums+ObjNums/3+1);
		pObj[ObjNums].ObjType=obj.ObjType;
		pObj[ObjNums].ObjID=obj.ObjID;
		pObj[ObjNums].status=obj.status;
		ObjNums++;
	}
	void Add(SG_LONG OType,SG_LONG OID,SG_SHORT OStatus){
		if(OType<1||OID<0)return;
		if(ObjNums>=MemNums)
			SetSize(ObjNums+ObjNums/3+1);
		pObj[ObjNums].ObjType = OType;
		pObj[ObjNums].ObjID = OID;
		pObj[ObjNums].status = OStatus;
		ObjNums++;
	}
	//清空对象
	void ClearObj(SG_BOOL ResetFlag=true){
		ObjNums = 0;
	}
	//除掉第ptr个成员，最后一个成员填充在ptr位置
	void RemoveAt(SG_UINT ptr)
	{
		if(ObjNums<1)return;
		if(ptr>=ObjNums)return;
		if(ptr<ObjNums-1)
		{
			pObj[ptr] = pObj[ObjNums-1];
		}
		ObjNums--;
	}

	int GetObjPtr(int nObjType,int nObjID)
	{
		for(int i =0; i< ObjNums; i++)
		{
			if(pObj[i].ObjType == nObjType && pObj[i].ObjID == nObjID)
				return i;
		}
		return -1;
	}

	int GetObjPtr(int nObjType,int nObjID,int nStatus)
	{
		for(int i =0; i< ObjNums; i++)
		{
			if(pObj[i].ObjType == nObjType 
				&& pObj[i].ObjID == nObjID && pObj[i].status == nStatus)
				return i;
		}
		return -1;
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{		
		SG_SHORT type;SG_LONG  id;
		SG_SHORT	status;
		SG_LONG num=0;
		if(ar.IsLoading())
		{
			ar>>num;
			if(num>0){
				SetSize(num);
				for(SG_INT i=0;i<num;i++)
				{
					ar>>type;
					ar>>id;
					ar>>status;
					pObj[i].ObjType = type;
					pObj[i].ObjID = id;
					pObj[i].status =status;
				}
				ObjNums = num;
			}
			else{
				ClearObj();
			}
		}
		else
		{
			if(ObjNums>0)
			{
				num = ObjNums;
				ar<<num;
				for(SG_INT i=0;i<ObjNums;i++)
				{
					type	=	pObj[i].ObjType;
					id		=	pObj[i].ObjID;
					status	=	pObj[i].status;
					ar<<type;
					ar<<id;
					ar<<status;
				}
			}
			else{
				ar<<num;
			}
		}
		return true;
	}
};

//停电故障对象结构定义
struct S_EventObjs
{
	CSgString		EventDesc;
	SG_Date			EventDate;
	SG_INT			nRid;
	RefObjectSet	EventObjs;

	S_EventObjs()
	{
		nRid		=0;
		EventDesc	="";
		EventObjs.ClearObj();
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>nRid;		
		else
			ar<<nRid;		
		EventDesc.Serialize(ar);
		EventDate.Serialize(ar);
		EventObjs.Serialize(ar);
		return true;
	}
};

//网络节点变更结构定义
struct S_NetNodeChange
{
	SG_SHORT		NetWorkType;	
	CSgObjects		NodeChangePair; //节点变更队列，为偶数集合。基数为原始值，紧邻的偶数值为新值。

	S_NetNodeChange()
	{
		NetWorkType		=0;
		NodeChangePair.ClearObj();
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>NetWorkType;		
		else
			ar<<NetWorkType;		
		NodeChangePair.Serialize(ar);
		return true;
	}
};

//网络节点变更结构定义
struct S_TaskDevSync
{
	SG_SHORT		SyncType; //0--图形服务号，具体图形服务号在SyncList中，1--按公司全部同步，公司号在SyncList中
							  //2--按设备同步，具体设备在SyncList中，3--按任务，具体任务在SyncList中
	CSgString		SyncList; //当为SyncType=2时，为容器对象PMSID的队列，当SyncType=3时，为任务队列,多个任务用";"分隔

	S_TaskDevSync()
	{
		SyncType		=0;
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>SyncType;		
		else
			ar<<SyncType;
		SyncList.Serialize(ar);
		return true;
	}
};

enum   //符号绘图状态 draw status
{
    SG_SYMBOL_DS_NORMAL				=	0x00000001,	//
	SG_SYMBOL_DS_SELECT				=	0x00000002,	//优先级 3
	SG_SYMBOL_DS_MOVING				=	0x00000004,	//优先级 1
	SG_SYMBOL_DS_BLACKWHITEPRT		=	0x00000008,	//优先级 2
	SG_SYMBOL_DS_NORMALPRT			=	0x00000010,	//优先级 2.5
	SG_SYMBOL_DS_CUSTOM				=	0x00000020,	//用户指定颜色
	SG_SYMBOL_DS_ONPOWER			=	0x00000800,	//带电状态
	SG_SYMBOL_DS_POINT				=	0x00001000	//点设备状态
};
//
//

enum SG_ObjDispColor
{
	PEN_COLOR_VOLT_NONE = MYRGB( 255 , 255 , 255 ),	// 白色，有电压等级字段，其值无效
	PEN_COLOR_DEFAULT	= MYRGB( 255 ,   0 ,   0 ),	// 缺省无电压等级属性线颜色
	PEN_COLOR_POWEROFF	= MYRGB( 192 , 192 , 192 ),	// 失电&接地
	PEN_COLOR_SELECT	= MYRGB( 255 ,   0 , 255 ),	// 选中
	PEN_COLOR_MANSET    = MYRGB( 255 ,   0 , 255 ),	// 置数颜色

	PEN_COLOR_BLACK		= MYRGB(   0 ,   0 ,   0 ),
	PEN_COLOR_RED		= MYRGB( 255 ,   0 ,   0 ),
	PEN_COLOR_GREEN		= MYRGB(   0 , 255 ,   0 ),
	PEN_COLOR_BLUE		= MYRGB(   0 ,   0 , 255 ),
	PEN_COLOR_YELLOW	= MYRGB( 255 , 255 ,   0 ),
	PEN_COLOR_FUCHSIA	= MYRGB( 255 ,   0 , 255 ),
	PEN_COLOR_CYAN		= MYRGB(   0 , 255 , 255 ),
	PEN_COLOR_WHITE		= MYRGB( 255 , 255 , 255 )
};


struct SG_SAFE_OPER_INFO 
{
	
	SG_CHAR   target_status;  //target_status--将要改变成的状态; 
	
	SG_CHAR   current_status; //current_status--当前的状态;
	
	SG_CHAR   operate_type;
	
	SG_UCHAR  error_type;
	
	SG_CHAR   bOperWithload;  //可以带负荷操作
	
	SG_CHAR   error_info[511];
	
	SG_OBJECT error_obj;
	
	SG_SAFE_OPER_INFO(){error_info[0]='\0';}
};

enum cyc_connect_strategy
{
	no_wait=1,       //不重连
	wait_10times,  //10次
	wait_5min,     //5分钟
	wait_forever   //永远重连
};
//----空间引擎的类型÷
enum GDBSRV_TYPE
{
	GDBSRV_TYPE_GAP		=1, //GAP空间引擎
	GDBSRV_TYPE_PSP		=2  //PSP空间引擎
};

//----客户端数据加载方式÷
enum CLIENT_LOAD_TYPE
{
	LOAD_FROM_GDBSRV	=1, //客户端从空间引擎加载
	LOAD_FROM_SDE		=2, //客户端从SDE中加载
	LOAD_FROM_DBF		=3	//客户端从DBF中加载	
};
//
enum CLIENT_LOAD_FILTER
{
	CLIENT_LOAD_ALL			=1,		//全部加载
	CLIENT_LOAD_BY_TASK		=2,		//按照任务号加载
	CLIENT_LOAD_BY_RANGE	=3,	//按照空间范围加载(只对从SDE表中加载起作用)
	CLIENT_LOAD_BY_SQL		=4	//SQL
};
//定义零长度值
//static SG_DOUBLE DISTANC_ZERO;
#endif /* SG_Def_h */

//定义本地扩展多边形
#define	LOCAL_POLYGON_TYPE	  4500
#define LOCAL_EX_POLYGON_NAME "本地扩展多边形"
#define POINT_SIZE_AS_REGION	2