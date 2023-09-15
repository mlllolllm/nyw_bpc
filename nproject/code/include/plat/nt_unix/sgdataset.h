#if !defined(_SgDataset_Def_h)
#define _SgDataset_Def_h

#include "sgconst.h"
#include <memory.h>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
//缺省的几何数据拥有者名称
#define DEFAULT_SPATIALOWNER	"GEO"
//几何属性
enum SG_FEATURE_TYPE_EXT
{ 
	SG_FE_Unknow		=0,
	SG_FE_Point			=1,
	SG_FE_StraightLine	=2,
	SG_FE_PolyLine		=3,
	SG_FE_Polygon		=4,
	SG_FE_Rectangle		=5,
	SG_FE_RoundRectangle=6, 
	SG_FE_Circle		=7,
	SG_FE_Ellipse		=8,
	SG_FE_Arc			=9,
	SG_FE_Pie			=10, //segment 复用 做反弧
	SG_FE_Chord			=11,
	SG_FE_BezeirLine	=12,
	SG_FE_AnchorLine	=13,
	SG_FE_Text          =14,
	SG_FE_Curve         =15,
	//important 拜托,不能再扩了!!!
	SG_FE_LinkPt		=20	 //该定义只在符号元件中判断连接点用，不做他用
};

//线、段的显示特性
enum SG_SYSLINE_DISPLAY
{
	SG_FEATURE_DISPLAY_SHOW=1,
    SG_FEATURE_DISPLAY_HIDE,            //隐藏
    SG_FEATURE_DISPLAY_HEAD_ARROW,       //首端显示箭头
    SG_FEATURE_DISPLAY_TAIL_ARROW,       //末端显示箭头
    SG_FEATURE_DISPLAY_HEAD_END,        //首端有端线
	SG_FEATURE_DISPLAY_BOTH_ARROW=5,    //两端有箭头,复用首端有端线
    SG_FEATURE_DISPLAY_TAIL_END,        //末端有端线
    SG_FEATURE_DISPLAY_BOTH_END,        //两端有端线
    SG_FEATURE_DISPLAY_HEAD_R_ARROW,     //首端显示及反箭头
    SG_FEATURE_DISPLAY_TAIL_R_ARROW,     //末端显示及反箭头
	//important 拜托,不能再扩了!!!
};


// GIS 基础特征类型定义
enum SG_BaseFeatureTypeDef{
	SG_B_Feature_NULL=0,
	SG_B_Feature_POINT=1,
	SG_B_Feature_MULTIPOINT,
	SG_B_Feature_LINE,
	SG_B_Feature_REGION,
	SG_B_Feature_TEXT,
	SG_B_Feature_3DPOINT,
	SG_B_Feature_3DLINE,
	SG_B_Feature_3DREGION,
	SG_B_Feature_MULTILINE,
	SG_B_Feature_3DMULTILINE,
	SG_B_Feature_MULTIREGION,
	SG_B_Feature_UNKNOW =99,
};

//对象实例类型
enum SG_OBJ_APPTYPE{
	SG_OBJ_APPTYPE_INSULATE		=1,		//	孤立对象--表对象
	SG_OBJ_APPTYPE_KERNALLINE	=2,		//	核心设备线型
	SG_OBJ_APPTYPE_KERNALPOINT	=3,		//	核心设备点型
	SG_OBJ_APPTYPE_LINEREGION	=4,		//	显式容器对象
	SG_OBJ_APPTYPE_CONTAINER	=5,		//	隐式容器对象
	SG_OBJ_APPTYPE_COMBIN		=6,		//	纯（点）组合对象
	SG_OBJ_APPTYPE_SIZELABEL	=7,		//	尺寸标注对象
	SG_OBJ_APPTYPE_SPECIALSYMBOL=8,		//	特效符号显示对象
	SG_OBJ_APPTYPE_SYSLINE		=9,		//	系统线对象
	SG_OBJ_APPTYPE_ROUTER_NZ	=10,	//	耐张对象
	SG_OBJ_APPTYPE_ROUTER_FZ	=11,	//	分支对象
	SG_OBJ_APPTYPE_STREET_LINE	=12,	//	街道中心线
	SG_OBJ_APPTYPE_ROUTER_ROAD	=13,	//	路径对象
	SG_OBJ_APPTYPE_GPSCAR		=14,	//	GPS车位对象
	SG_OBJ_APPTYPE_TEXT			=15,	//	文本对象
	SG_OBJ_APPTYPE_ONBASE		=16,	//	依附对象
	SG_OBJ_APPTYPE_YCBASE		=17,	//	遥测库---遥测管理基础对象
	SG_OBJ_APPTYPE_OFFSET		=18,	//	偏移量处理对象
	SG_OBJ_APPTYPE_CONTAIN_RELATON=19,	//	容器关系管理对象
	//SG_OBJ_APPTYPE_OBJLABEL_RELATON=20,	//	设备标注关系管理对象
	//以下为特殊配置对象---配置为与Universe不产生关系,系统特定处理
	SG_OBJ_APPTYPE_YAOCE		=21,			//	遥测标注点
	SG_OBJ_APPTYPE_OBJLABEL		=22,			//	设备标注
	SG_OBJ_APPTYPE_OBJSIGN		=23,			//	挂牌对象
	SG_OBJ_APPTYPE_PIPELINE		=24,			//	管线对象
	SG_OBJ_APPTYPE_ROUTER_WHOLELINE	=25,		//整线——超路径的派生对象
	SG_OBJ_APPTYPE_OBJLINKER	=26,			//对象连接对象
	SG_OBJ_APPTYPE_GRID			=27,			//格网(网格)对象
	SG_OBJ_APPTYPE_PIPEHOLE		=28,			//管孔对象
	SG_OBJ_APPTYPE_LABELPOINT	=29,			//标注点对象
	//
	SG_OBJ_APPTYPE_COMBIN_LINE	=30,			//纯（线型）组合对象
	SG_OBJ_APPTYPE_YXBASE		=31,			//	遥信库
	SG_OBJ_APPTYPE_REALEVENT	=32,			//	实时事项
    //
    SG_OBJ_APPTYPE_PRINT_WARE   =33,            //单线图打印固件
	SG_OBJ_APPTYPE_OBJ_TEXT     =34,            //通用对象注计
	SG_OBJ_APPTYPE_M_SIZELABEL  =35,            //特殊的多段标注对象
	SG_OBJ_APPTYPE_TEMP_OBJECT  =36,            //临时对象
	SG_OBJ_APPTYPE_SYMBOL_ELEMENT=37,           //符号图元管理对象
	SG_OBJ_APPTYPE_HPERLINK      =38,           //超连接线
	SG_OBJ_APPTYPE_ANCHOR_LABEL	 =39,			//标注铆点
	SG_OBJ_APPTYPE_STATISTICAL	 =40,			//统计信息对象
	SG_OBJ_APPTYPE_ANCHOR_LINE	 =41,			//标注铆点线
	SG_OBJ_APPTYPE_REGION		 =42,			//区域对象(如行政区)
	SG_OBJ_APPTYPE_LAYOUT_POINT	 =44,			//地理走向图点对象	
	SG_OBJ_APPTYPE_SCHEME_RANGE	 =45,			//规划方案加载范围	
	SG_OBJ_APPTYPE_BAY			 =47,			//仓位
	SG_OBJ_APPTYPE_PART_CNTR	=48,			//组合容器对象
	SG_OBJ_APPTYPE_LINE_PART	=49,			//组合容器部件

	//
	SG_OBJ_APPTYPE_TEXT_SDE		=50,			//CTextLayerSde
	SG_OBJ_APPTYPE_TEXT_SHAPE	=51,			//CTextLayerShape	//
	SG_OBJ_APPTYPE_PHASE		=52,			//相序指示器
	SG_OBJ_APPTYPE_CROSSSPAN	=53,			//交叉跨越
	SG_OBJ_APPTYPE_SPANBREAKER	=54, 			//跨接线
	SG_OBJ_APPTYPE_USER_POWER_POINT=55,			//用户供电点
	SG_OBJ_APPTYPE_POLLUTE_SRC	=56,			//污秽源图层CSgPolluteSrcLayer
	SG_OBJ_APPTYPE_MEASURE_LABEL=57,			//量测标注
	SG_OBJ_APPTYPE_ADHERE_LABEL	=58,			//标注依附对象
	SG_OBJ_APPTYPE_MAKER		=59,            //图标显示层
	//
	
	SG_OBJ_APPTYPE_ADJACENCY	=60,			//供电区域
	SG_OBJ_APPTYPE_CLIMB_POLE	=61,			//登杆设备
	SG_OBJ_APPTYPE_POWERPOINT	=62,			//电源点设备
	SG_OBJ_APPTYPE_DWZ_SWITCH	=63,			//多位置闸刀
	SG_OBJ_APPTYPE_DWZ_SWITCH_PART	=64,		//多位置闸刀部件
	SG_OBJ_APPTYPE_CROSS_SECTION =65,			//截面对象
	SG_OBJ_APPTYPE_YC_ADHERE_LINE =66,			//带遥测信息的线（如令克熔丝箱）
	SG_OBJ_APPTYPE_USER_INFO	=67,			//用户信息
    SG_OBJ_APPTYPE_GATHER_ELEMENT =68,          //拼图单元
	SG_OBJ_APPTYPE_YX_SIGNAL=69,				//遥信信号量(子类型对应具体的设备)
    SG_OBJ_APPTYPE_THUNDER=70,                  //雷电设备
    SG_OBJ_APPTYPE_THEME=71,					//专题图
    SG_OBJ_APPTYPE_KEY_POINT=72,                //作业关键点设备
    SG_OBJ_APPTYPE_PROTECT_SIGNAL=73,           //保护信号量
    SG_OBJ_APPTYPE_SCREEN=74,                  //保护屏
	SG_OBJ_APPTYPE_CARRIER=75,                  //载波机
	SG_OBJ_APPTYPE_LATTICE=76,					//格子对象
	SG_OBJ_APPTYPE_TCAREA	=77,					//电信小区
	
	SG_OBJ_APPTYPE_RAILWAY	=80,			//铁路
	SG_OBJ_APPTYPE_XYPOINT	=81,			//X,Y扩展点
	SG_OBJ_APPTYPE_MULTILINE=82,			//复杂线
	
	SG_OBJ_APPTYPE_TOPO_DUMMYLINE	=100,	//拓扑虚拟线设备
	SG_OBJ_APPTYPE_TOPO_DUMMYPOWER	=101,	//拓扑虚拟电源设备
	SG_OBJ_APPTYPE_HOTLINKER		=110,	//热点对象
	SG_OBJ_APPTYPE_RECT			=1000,			//矩形
	SG_OBJ_APPTYPE_CIRCLE		=1001,			//圆
	SG_OBJ_APPTYPE_ARC			=1002,			//弧
	SG_OBJ_APPTYPE_BEZEIRLINE	=1003,			//多义线
	SG_OBJ_APPTYPE_ELLIPSE		=1004,				//椭圆
	SG_OBJ_APPTYPE_MAP		=10001,				//图形对象
	SG_LINE_LOSS_LABLE     = 504,        //线损显示点   
	SG_FAULT_DISP_POINT   =  505
};

enum SG_SYS_CAL_STATUS{
	SG_SYS_CAL_STATUS_REAL=0,	//运行态
	SG_SYS_CAL_STATUS_STUDY=1	//模拟态
};




#include "sggeodef_template.h"


struct _DATASET_DLL_EXPORT_ SgRect
{
	
    SG_DOUBLE    l;
	
    SG_DOUBLE    t;
	
    SG_DOUBLE    r;
	
    SG_DOUBLE    b;
	
	SgRect(){l=t=b=r=0;}
	
	SG_BOOL		IsNull();					//是否都是0值
	
	void		Reset();					//全设为0值
	
	void		GetCenter(SgPoint *c);		//获得中心点
	
	SgPoint		GetCenter();				//获得中心点
	
	SG_DOUBLE	GetCaterCorner();			//获得对角线长度
	
	SgRect		GetGeoRect();				//获得与地理坐标一致的矩形

	void		ScaleZoom(SG_DOUBLE scale);
	
	SG_BOOL Serialize(CSgArchive&ar);

};

/* 矩形对象的几何属性管理类 */

class _DATASET_DLL_EXPORT_ CSgRect : public SgRect
{
public:
	
	CSgRect(){}
	
	CSgRect(SgRect rect);
	
	CSgRect(SG_DOUBLE left, SG_DOUBLE top, SG_DOUBLE right, SG_DOUBLE bottom);
	
	CSgRect(SgPoint topLeft, SgPoint bottomRight);
	//
	
	CSgRect & operator=(const CSgRect & src) ;
	
	CSgRect & operator=(const SgRect & src);
	
	CSgRect & operator+=(SgRect&rc);	//两个矩形相加 --- rect都是NormalizeRect()后的结果 --- 顶小底大
	//
	
	CSgRect operator*(SG_DOUBLE scale);	//缩放矩形 --- 顶小底大
	
	inline SG_DOUBLE Width(){return (r-l);}
	
	inline SG_DOUBLE Height(){if(b>t)return b-t; else return t-b;}
	
	inline SG_DOUBLE Scale(){if(r==l)return 0;return Width()/Height();}
	
	
	void NormalizeRect();	//格式化矩形, 变位顶小底大 -- 与屏幕坐标一致
	
	void UnNormalizeRect();	//返还为地理坐标
	//膨胀矩形, rect是NormalizeRect()后的结果 --- 顶小底大
	
	void InflateRect(SG_DOUBLE x, SG_DOUBLE y);
	void DeflateRect(SG_DOUBLE x, SG_DOUBLE y);
	
	void OffsetRect(SG_DOUBLE x, SG_DOUBLE y) ;
	void ScaleRect(SG_DOUBLE scale);

	//点包含于矩形 --- 
	
	SG_BOOL PtInRect(SgPoint &point);
	
	SG_BOOL IntersectRect(SgRect * lpRect);

	bool Intersect(CSgRect rcExt,CSgRect*lpIntersectRect=NULL);
	//包含于传入矩形判断 --- rect都是NormalizeRect()后的结果 --- 顶小底大
	
	SG_BOOL InRect(SgRect *  lpRect);
	//包含传入矩形判断 --- rect都是NormalizeRect()后的结果 --- 顶小底大
	
	SG_BOOL IncludeRect(SgRect * lpRect);
	
	SgPoint GetLeftTop();				//获得左顶点
	
	SgPoint GetLeftBottom();			//获得左底点
	
	SgPoint GetRightTop();				//获得右顶点
	
	SgPoint GetRightBottom();			//获得右底点
};

//对象集合的记录表征结构

class _DATASET_DLL_EXPORT_ CSgObjects
{
public:
	
	CSgObjects()
	{
		pLayer = 0; 
		ObjNums=0; 
		pObj=0; 
		MemNums=0;
	}

	
	~CSgObjects();
public:
	
	SG_LONG ObjNums;
	
	SG_NODEINT *pObj;
	union
	{
		SG_LONG ObjType;
		void *pLayer;		//对象所在层的指针
	};
public:
	// --- 设定长度(可用于压缩内存),当设定的数量小于ObjNums时取ObjNums
	
	void SetSize(SG_INT MemLen);
	
	SG_LONG GetSize(){return MemNums;}
	//
	
	void Add(SG_NODEINT id);
	
	void AddNoCheck(SG_NODEINT id);
	
	SG_BOOL IsObjIn(SG_NODEINT id);
	
	SG_LONG ObjPtr(SG_NODEINT id);
	
	void RemoveAt(SG_LONG ptr);
	
	void ClearObj(SG_BOOL ReleaseMem=false);
	// --- 两个结构内容一致
	
	SG_BOOL IsSame(CSgObjects &InObj);
	
    SG_BOOL vmax(SG_NODEINT &val);
	
    SG_BOOL vmin(SG_NODEINT &val);
	//
	void Pack();

	void operator = (const CSgObjects&InObj);
	void operator += (const CSgObjects&InObj);
	void operator -= (const CSgObjects&InObj);
	// --- 内存占用
	
	SG_LONG GetMemLen(){return sizeof(SG_LONG)*ObjNums;}
	
	SG_BOOL Serialize(CSgArchive&ar);
	int buf_size();
protected:
	
	SG_INT MemNums;
};


/*******************************************************
	Part 80	系统指针管理类
*******************************************************/


struct _DATASET_DLL_EXPORT_ CSgPtrArray
{
public:
	
	CSgPtrArray();
	
	virtual ~CSgPtrArray();
public:
	
	void SetSize(SG_UINT size);	//本方法只处理了为0的情况
	void SetMemSize(SG_UINT memsize);
	
	SG_UINT GetSize() const;
	
	virtual void Add(void *p);
	
	virtual SG_BOOL SetAt(SG_UINT index,void *p);
	
	virtual void RemoveAll();
	
	virtual void RemoveAt(SG_UINT index);
	//删除单元，后面的成员向前平移，当队列成员过多时存在效率问题
	virtual void RemoveAt_Ex(SG_UINT index);
	
	const void * GetAt(SG_UINT index) const;
	void * GetAt(SG_UINT index);

	const void * operator[](SG_UINT index) const{return GetAt(index);}
	void * operator[](SG_UINT index){return GetAt(index);}
	
	void operator=(CSgPtrArray&inarray){return;}
	
	SG_BOOL Exist(void *p);
	
	void	Remove(void *p);
	//
	
	SG_LONG GetMemLen(){return sizeof(void*)*m_MemLen;}
	//
	
	SG_BOOL IsNull();

protected:
	
	SG_UINT m_MemLen;
	
	SG_UINT m_ObjNums;
	
	void **m_pArray;

	
	inline SG_BOOL CheckIndexSafe(SG_UINT index) const
	{
		if(index>=m_ObjNums)return false;
		return true;
	}
};

template< typename T , bool AutoRelease = false >
class CPtrArrayT
{
public:
	CPtrArrayT()
	{

	}

	~CPtrArrayT()
	{
		RemoveAll();
	}

public:
	typedef std::vector< T * > Vector_Type ;
	typedef typename Vector_Type::iterator Vector_Itr; 

public:
	inline void SetSize(SG_UINT size)
	{
		m_Array.reserve( size );
	}

	inline SG_UINT GetSize() const
	{
		return (SG_UINT)m_Array.size();
	}
	
	inline void SetAt(SG_UINT index , T * p )
	{
		if(!CheckIndexSafe(index))return;
		m_Array[ index ] = p;
	}

	inline void Add(T * p)
	{
		m_Array.push_back( p );
	}
	
	inline void RemoveAll()
	{
		if( AutoRelease )
		{
			SG_UINT nLast = m_Array.size();
			for( SG_UINT nPtr = 0 ; nPtr < nLast ; nPtr ++ )
			{
				if( m_Array[nPtr] ) delete m_Array[nPtr];
			}
		}
		
		m_Array.clear();
	}
	
	inline void RemoveAt(SG_UINT index)
	{
		if(!CheckIndexSafe(index))return;

		if( AutoRelease ) 
		{
			T* p = m_Array[index];
			if( p ) delete p;
		}

		int nLast = m_Array.size() - 1;
		m_Array[index] = m_Array[ nLast ];
		m_Array.pop_back();
	}

	//删除单元，后面的成员向前平移，当队列成员过多时存在效率问题
	inline void RemoveAt_Ex(SG_UINT index)
	{
		if(!CheckIndexSafe(index))return;
		if(m_Array[index]!=NULL) delete m_Array[index];

		SG_UINT nLast = m_Array.size() - 1;
		for( SG_UINT nPtr = index ; nPtr < nLast ; nPtr ++ )
		{
			m_Array[nPtr] = m_Array[nPtr + 1];
		}

		m_Array.pop_back();
	}
	
	inline SG_BOOL Exist(T *p)
	{
		return std::find( m_Array.begin() , m_Array.end() , p ) != m_Array.end();
	}
	
	inline void	Remove(T *p)
	{
		Vector_Itr itr = std::find( m_Array.begin() , m_Array.end() , p );
		if( itr == m_Array.end() ) return;
		if( AutoRelease ) { delete p; };

		int nLast = m_Array.size() - 1;
		* itr = m_Array[ nLast ];
		m_Array.pop_back();
	}

	inline T * GetAt(SG_UINT index)
	{
		if(index>=m_Array.size())
			return NULL;
		return m_Array[index]; 
	}
	inline T * operator[](SG_UINT index)
	{ 
		if(index>=m_Array.size())
			return NULL;
		return m_Array[index]; 
	}
	inline SG_LONG GetMemLen(){ return m_Array.capacity(); }
	inline SG_BOOL IsNull() { return m_Array.size() == 0 ; }

protected:
	Vector_Type m_Array;

	inline SG_BOOL CheckIndexSafe(SG_UINT index)
	{
		if(index>= m_Array.size() )return false;
		return true;
	}

private:
    const CPtrArrayT& operator=(const CPtrArrayT&);
    CPtrArrayT(const CPtrArrayT&);
};

//
template <class T,const int MAX_NUMS=128>
class CMyArrayT
{
protected:

	int	m_nums;
	T * m_p;
	int m_memSize;
	T  m_array[MAX_NUMS]; //避免频繁在堆上分配内存

public:

	CMyArrayT()
	{
		m_memSize =0;
		m_nums=0;
		m_p=NULL;
	}

	~CMyArrayT()
	{
		if(m_p) 
		{
			delete [] m_p;
			m_p=NULL;
		}
	}

	void SetNums(int nums)
	{
		if(!m_p)
		{
			if( nums<=MAX_NUMS )
			{
				m_nums=nums;
				return;
			}
		}

		if(!m_p)
		{
			m_memSize = nums;
			m_p = new T[nums];
			memcpy(m_p,m_array,MAX_NUMS*sizeof(T));
		}
		else
		{
			if(nums>m_memSize)
			{
				T* p = new T[nums];
				memcpy(p,m_p,sizeof(T)*m_memSize);
				delete [] m_p;
				m_p=p;
				m_memSize=nums;
			}
		}
		m_nums=nums;
	}

    SG_INT GetNums(){
        return m_nums;
    }

	T* GetPtr(){
		return m_p?m_p:m_array;
	}
};
/***********************************************
	 	part 0	对象的记录表征结构
***********************************************/
//单一对象记录结构

struct _DATASET_DLL_EXPORT_ SG_OBJECT
{
	union
	{
		SG_LONG		row;		//对象的标识，行号
		SG_LONG    ObjID;
	};
	union
	{
		void *pLayer;		//对象所在层的指针
		SG_LONG ObjType;
	};

	SG_OBJECT( void * pLayer = NULL , SG_LONG row = 0 );
	SG_OBJECT( SG_LONG ObjType , SG_LONG ObjID = 0 );
	SG_BOOL operator == ( const SG_OBJECT & obj );
	//支持做map的key
	//friend SG_BOOL operator<(const SG_OBJECT &obj1,const SG_OBJECT &obj2);
};

_DATASET_DLL_EXPORT_ SG_BOOL operator<(const SG_OBJECT &obj1,const SG_OBJECT &obj2);

struct _DATASET_DLL_EXPORT_ CSSgObjectLess:public std::binary_function<SG_OBJECT, SG_OBJECT, bool> 
{
	bool operator()(const SG_OBJECT & obj1, const SG_OBJECT & obj2) const
	{
		if(obj1.ObjType<obj2.ObjType)
			return true;
		if(obj1.ObjType==obj2.ObjType)
		{
			if(obj1.ObjID<obj2.ObjID)
				return true;
		}
		return false;
	}
};

// 对象集合的记录表征结构
struct _DATASET_DLL_EXPORT_ SG_OBJECTS
{
	
	SG_LONG MemNums;
	
	SG_LONG ObjNums;
	
	SG_OBJECT *pObj;
	
	SG_OBJECTS(){MemNums=0;ObjNums=0;pObj=0;}
	
	~SG_OBJECTS();
	
	void SetSize(SG_INT nums);
	
	void Add(SG_OBJECT obj);
	
	void Add(void *layer,SG_LONG row);
	
	void Add(SG_LONG OType,SG_NODEINT OID);
	//增加对象,不校验是否具有重复对象
	
	void AddNoCheck(void *layer,SG_LONG row);
	void AddNoCheck(SG_LONG OType,SG_NODEINT OID);
	//对象集合相加,不管是否有重复对象,,2003/10/21 
	
	const SG_OBJECTS& operator+=(const SG_OBJECTS&);
	//对象是否已存在
	
	SG_BOOL IsObjIn(void *layer,SG_LONG row);
	
	SG_BOOL IsObjIn(SG_LONG OType,SG_NODEINT OID);
	//是否具有层指针一致的对象
	
	SG_BOOL IsObjIn(void *player);
	//删除匹配的对象
	
	void RemoveObj(void *layer,SG_LONG row);
	//对象是否已存在 ,如果存在返回位置,否则返回-1
	
	SG_INT ObjPtr(SG_LONG OType,SG_NODEINT OID);
	//层/行对应的对象位置
	
	SG_INT ObjPtr(void *layer,SG_LONG row);
	//与一个层匹配的对象
	
	SG_INT LayerObjPtr(void*player,SG_INT startpos=0);
	//清空对象
	
	void ClearObj(SG_BOOL ResetFlag=true);
	//除掉重复的成员
	
	void Pack();
	//除掉第ptr个成员，最后一个成员填充在ptr位置
	
	void RemoveAt(SG_UINT ptr);
	
	SG_LONG GetDyncMemLen();

public:
	SG_BOOL Serialize(CSgArchive&ar);
	int buf_size();
private:
	
	const SG_OBJECTS& operator=(const SG_OBJECTS&);
	
	SG_OBJECTS(const SG_OBJECTS&);
};

//设备树状表征结构

struct _DATASET_DLL_EXPORT_ SG_OBJECTS_TREE
{
	
	SG_OBJECT FatherObj;
	
	SG_OBJECTS ChildObjs;
};

//队列管理，结构为TMyObject
template<class TMyObject> 
class TMyObjectsArray : public CSgPtrArray
{
public:
	virtual ~TMyObjectsArray(){
		RemoveAll();
	}
	void RemoveAt(SG_UINT index){
		if(m_ObjNums<1)return;
		if(!CheckIndexSafe(index))return;
		if(m_pArray[index]!=NULL)delete (TMyObject*)m_pArray[index];
		CSgPtrArray::RemoveAt(index);
	}
	void RemoveAt_Ex(SG_UINT index){
		if(m_ObjNums<1)return;
		if(!CheckIndexSafe(index))return;
		if(m_pArray[index]!=NULL)delete (TMyObject*)m_pArray[index];
		CSgPtrArray::RemoveAt_Ex(index);
	}
	void RemoveAll()
	{
		for(SG_UINT i=0;i<m_ObjNums;i++)
		{
			TMyObject *p = (TMyObject *)m_pArray[i];
			if(p!=NULL)
			{
				delete p;
			}
		}
		CSgPtrArray::RemoveAll();
	}
	//在index处创建对象【如果已经存在返回已经存在的对象；index超界返回NULL】
	TMyObject *Create(SG_UINT index)
	{
		if(!CheckIndexSafe(index))return NULL;
		TMyObject*p = (TMyObject*)m_pArray[index];
		if(p!=NULL)return p;
		p = new TMyObject;
		m_pArray[index] = p;
		return p;
	}
};

//对象集队列,指针结构为 CSgObjects
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<CSgObjects>;
#endif
class _DATASET_DLL_EXPORT_ CSgObjectsArray:public TMyObjectsArray<CSgObjects>
{
public:
	//通过成员中的ObjType属性定位队列中的位置
	SG_BOOL GetObjects(SG_INT ObjType,CSgObjects**p,SG_INT&ptr);
	void From(const SG_OBJECTS&);
	void Append(const SG_OBJECTS&);
	void Append(const CSgObjectsArray&);
	void Exclude(const SG_OBJECTS&);
	void Exclude(const CSgObjectsArray&);
};
//对象集队列,指针结构为 SG_OBJECTS
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<SG_OBJECTS>;
#endif
typedef TMyObjectsArray<SG_OBJECTS> CSG_OBJECTSArray;
//对象集队列,指针结构为 SG_OBJECTS_TREE
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<SG_OBJECTS_TREE>;
#endif
typedef TMyObjectsArray<SG_OBJECTS_TREE> CSG_OBJECTS_TREEArray;
//
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_  TMyObjectsArray<CSgRect>;
#endif
typedef TMyObjectsArray<CSgRect> CSgRectArray;

//点队列
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<CSgPoint>;
#endif
class _DATASET_DLL_EXPORT_ CSgPointArray:public TMyObjectsArray<CSgPoint>
{
public:
	SG_BOOL IsNull(SG_UINT index);
};

//线队列
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<CSgLine>;
#endif
class _DATASET_DLL_EXPORT_ CSgLineArray:public TMyObjectsArray<CSgLine>
{
public:
	SG_BOOL IsNull(SG_UINT index);
};

class _DATASET_DLL_EXPORT_ CSgString
{
public:
	
	CSgString();
	
	CSgString(CSgString &str);
	
	CSgString(const SG_CHAR *str);
	
	~CSgString();

	// --- 存在字符串并且内容不为空
	
	SG_BOOL IsEmpty();
	
	void Format(const char *format,...);
	
	void operator=( SG_CHAR inChar);
	void operator=( SG_PCSTR instr);
	
	void operator+=(SG_PCSTR instr);
	
	void operator+=(SG_CHAR inchar);
	
	void SetValue(SG_PCSTR instr,SG_INT startpos=-1,SG_INT endpos=-1);
	
	SG_CHAR operator[](SG_INT index);
	SG_CHAR GetAt(SG_INT index);
	
	const CSgString &operator = (const CSgString& str);
	
	SG_INT Find(CSgString &str);	//字符串查找 
	
	SG_INT Find(SG_CHAR inchar);	//字符查找
	
	SG_INT Find(const SG_CHAR *instr);
	
	void Left(SG_UINT pos,CSgString&TargetStr);	//取左字符串
	CSgString Left(SG_UINT pos);	//取左字符串

	void Right(SG_UINT pos,CSgString&TargetStr);	//取左字符串
	CSgString Right(SG_UINT pos);	//取左字符串

	void Mid(SG_UINT pos,CSgString&TargetStr);	//
	CSgString Mid(SG_UINT pos);	//
	
	void MakeLower();
	void MakeUpper();

	
	SG_BOOL operator==(SG_PCSTR instr);
	
	SG_BOOL operator==(CSgString &instr);
	
	SG_BOOL operator!=(SG_PCSTR instr);
	
	SG_BOOL operator!=(CSgString &instr);

	bool operator <(const CSgString &instr) const;
	// 类型转换操作符
	inline operator SG_PCSTR() { return GetSafeBuffer(); }
	
	void Trim();
	
	void TrimLeft();
	
	void TrimRight();
	//pCharOld：要替换的旧字符串  pCharNew:替换后的新字符串  bStrCaseFlag:大小写是否敏感 
	void Replace(const char *pCharOld,const char *pCharNew,SG_BOOL bStrCaseFlag=true);
	
	virtual int buf_size( ){ return GetLength() + sizeof( SG_INT ); }
	virtual SG_BOOL Serialize(CSgArchive&ar);

public:
	
	SG_CHAR *GetBuffer() const;
	
	SG_PSTR GetSafeBuffer();
	
	SG_UINT GetLength() const;
	
	void Empty();
	
	inline SG_LONG GetAllMemLen(){return (m_pValue!=NULL)?(sizeof(CSgString)+GetLength()+1):sizeof(CSgString);}
protected:
	
	inline void Alloc(SG_UINT inlen,SG_BOOL KeepMem=false);
	
	SG_CHAR *m_pValue;
};

class _DATASET_DLL_EXPORT_ CSgErrorInfo
{
public:
	SG_BOOL HasError() { return IsFailure(); }
	SG_LONG GetErrorCode(){ return m_nErrorCode; }
	SG_PCSTR GetErrorInfo(){ return m_strError.GetSafeBuffer(); }

public:
	SG_BOOL IsSuccess(){ return (m_nErrorCode >= 0); }
	SG_BOOL IsFailure(){ return (m_nErrorCode < 0); }

public:
	SG_LONG SetError(const CSgErrorInfo& errInfo)
	{
		m_strError = errInfo.m_strError;
		m_nErrorCode = errInfo.m_nErrorCode;
		return m_nErrorCode;
	}

	SG_LONG SetError(SG_LONG nErrorCode, SG_PCSTR lpszError = NULL)
	{
		m_strError = lpszError ? lpszError : "";
		m_nErrorCode = nErrorCode;
		return m_nErrorCode;
	}

public:
	CSgErrorInfo() : m_nErrorCode(0) {}
	virtual ~CSgErrorInfo() {}

public:
	CSgErrorInfo(const CSgErrorInfo& errInfo)
	{
		SetError(errInfo);
	}

	CSgErrorInfo(SG_LONG nError, SG_PCSTR lpszError = NULL)
	{
		SetError(nError, lpszError);
	}

	CSgErrorInfo operator = (const CSgErrorInfo& errInfo)
	{
		SetError(errInfo);
		return *this;
	}

private:
	CSgString m_strError;
	SG_LONG m_nErrorCode;
};


class _DATASET_DLL_EXPORT_ CSgStringArray:public CSgPtrArray
{
public:
	
	virtual ~CSgStringArray();
	// --- 指定位置删除字符串
	
	void RemoveAt(SG_UINT index);
	// --- 清空队列
	
	void RemoveAll();
	// --- 加入字符串
	
	void Add(CSgString *str);
	// --- 加入字符串
	
	void Add(SG_PCSTR p);
	// --- 加入字符串
	
	void Add(CSgString &str);
	// --- 加入字符串
	
	void Add(SG_PCSTR p,SG_INT sp,SG_INT ep);
	// --- 
	
	SG_PSTR operator[](SG_INT index);
	
	CSgString &Get(SG_INT ptr);

	//	移除无效或长度为零的字符串
	SG_UINT RemoveEmpty( );

	// --- 是否具有空字符串
	SG_BOOL HasNullStr( );
protected:
	
	static CSgString m_BlankStr;
};

static const char *SysFontName[] = { "宋体","隶书","仿宋_GB2312","楷体_GB2312","黑体","微软雅黑" };

const SG_INT g_font_idx_nums = sizeof(SysFontName)/sizeof( const char *);

struct _DATASET_DLL_EXPORT_ SG_TEXT_ATTRIB
{
protected:
	
	SG_UCHAR	fontindex;
public:
	
	SG_UCHAR	align;
	
	SG_USHORT	angle;
	
	SG_ULONG	size;
	
	SG_ULONG	color;
	
	SG_ULONG	bkmode:2;
	
	SG_ULONG	bkcolor:30;
public:

	
	SG_BOOL IsValid();
	
	const SG_CHAR* GetFontName();
	
	SG_UCHAR SetFontName(const SG_CHAR*p);
	
	void SetFontIndex(SG_UCHAR index);
	
	SG_UCHAR GetFontIndex();
	
	void Serialize(CSgArchive&ar);
};

//时间结构

struct _DATASET_DLL_EXPORT_ SG_Time
{
	
	SG_UCHAR	hour;  
	
	SG_UCHAR	minute;
	
	SG_UCHAR	second;
	SG_UCHAR	res1;
	SG_Time(){
		hour = 1;
		minute = 1;
		second = 1;
	}
	void Serialize(CSgArchive&ar)
	{
		SG_UCHAR res=0;
		if(ar.IsLoading())
		{
			ar>>hour;
			ar>>minute;
			ar>>second;
			ar>>res;
		}
		else
		{
			ar<<hour;
			ar<<minute;
			ar<<second;
			ar<<res;
			
		}
	};
};
//日期结构

struct _DATASET_DLL_EXPORT_ SG_Date
{
	
	SG_SHORT	year;
	
	SG_UCHAR	month;
	
	SG_UCHAR	day;
	
	SG_Time		Time;
	//输入 yyyy-mm-dd 字符串结构
	
	void SetDate(const char *value);
	//输入yyyymmdd
	void SetDate(int nYmd);
	//
	void SetTime(const char *value);
	//输入hhmmss
	void SetTime(int nHms);
	//输入内存结构
	
	void SetValue(void *value);
	//获得标准日期字符串
	
	void GetDate(char *date);
	
	void GetTime(char*time);
	//返回yyyymmdd
	int  GetYmd();
	//返回hhmmss
	int  GetHms();
	
	void GetAll(char*value);
	
	void GetAll(CSgString&value);
	
	SG_SHORT GetSafeYear(){
		if(year<1899 || year>9999)year=1970;
		return year;
	}
	
	SG_UCHAR GetSafeMonth(){
		if(month<1 || month>12)month=1;
		return month;
	}
	
	SG_UCHAR GetSafeDay(){
		if(day<1 || day>31)day=1;
		return day;
	}
	//将当前时间赋予SG_Date
	SG_BOOL NowTime();
	SG_BOOL operator==(SG_Date &in_date);
	SG_BOOL operator!=(SG_Date &in_date);
	void operator = (const SG_Date&InObj);
	void Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>year;
			ar>>month;
			ar>>day;
		}
		else
		{
			ar<<year;
			ar<<month;
			ar<<day;			
		}
		Time.Serialize(ar);
	};

};


//SQL语句解析出的结构

struct SG_SQLINFO {
	
	CSgString		TableName;
	
	CSgString		FieldsName;
	
	CSgString		Where;
	
	CSgStringArray  OrderArray;
};



/***********************************************
	Part 14 "对象类型"具有的内控属性配置信息内存存储结构
	当配置对象只具有一般属性时(GetValue()==1)时, DataSet中内控属性为 ObjAttribStruct_Base
		当具有结构中的其它属性时,DataSet中内控属性为 ObjAttribStruct_Ext
	结构的内值通过对象属性的内控属性字段获得
	配置时的可选项见枚举 
***********************************************/
struct _DATASET_DLL_EXPORT_ ObjType_IA_Cfg_Struct
{
#if defined(__sun)||defined(_AIX)
	SG_UCHAR hasoverloadf:1;	//过载
	SG_UCHAR hasdirectionf:1;	//方向特征
	SG_UCHAR hassignf:1;		//可以挂牌
	SG_UCHAR hasmansetf:1;		//具有置数属性
	SG_UCHAR hasycf:1;			//具有遥测
	SG_UCHAR hasvaluef:1;		//具有值属性
	SG_UCHAR hasCommonAttrib:1;	//具有一般属性
	SG_UCHAR haslabelf:1;		//具有标注属性
#else
	SG_UCHAR haslabelf:1;		//具有标注属性
	SG_UCHAR hasCommonAttrib:1;	//具有一般属性
	SG_UCHAR hasvaluef:1;		//具有值属性
	SG_UCHAR hasycf:1;			//具有遥测
	SG_UCHAR hasmansetf:1;		//具有置数属性
	SG_UCHAR hassignf:1;		//可以挂牌
	SG_UCHAR hasdirectionf:1;	//方向特征
	SG_UCHAR hasoverloadf:1;	//过载
#endif
	ObjType_IA_Cfg_Struct();
	SG_BOOL CommonAttribOnly();
	SG_BOOL HasExtAttrib();
	
	void SetValue(SG_USHORT value);
	
	SG_UCHAR GetValue();
};


//对象修改标记 --- 控制对象修改后的关系重建用

struct _DATASET_DLL_EXPORT_ SG_MODI_MESSAGE
{
	union {
		SG_ULONG Value;
		struct
		{
			SG_UCHAR Add:1;				//增加对象
			SG_UCHAR Modi:1;			//修改对象
			SG_UCHAR Delete:1;			//删除对象
			SG_UCHAR ModiGisID:1;		//修改对象的ID
			SG_UCHAR ModiTopNode:1;		//修改对象的拓扑端子
			SG_UCHAR ModiGeoMetry:1;	// --- 几何属性修改(当只发生几何属性修改时Modi=false)
			SG_UCHAR ModiStatus:1;		//FLAG字段内容被修改(开关状态变化要网络拓扑)
			//
			SG_UCHAR ByNet:1;			//对象被网络平台修改标记
			SG_UCHAR EffectView:1;		//影响视图的变更出现
			SG_UCHAR EffectIndex:1;		//影响hash索引的变更出现
			SG_UCHAR EffectLoadRange:1;	//影响加载的修改出现
//			SG_UCHAR ModiWorldid:1;			//WorldID被修改
//			SG_UCHAR ModiLine:1;			//所属线被修改
//			SG_UCHAR ModiStation:1;			//所属站被修改
//			SG_UCHAR ModiName:1;			//设备名称被修改
//			SG_UCHAR ModiObjSym:1;			//符号被修改
//			SG_UCHAR ModiSubType:1;			//子类型被修改
		}BitVal;
	};
	
	SG_MODI_MESSAGE();
	void ClearModiFlag();
	// --- 将 ByNet 置位为对应的成员
	
	void SetByNet();
	void Merge(SG_MODI_MESSAGE&AddValue);
	// --- 需要Build索引的修改(except top modi and delete)
	
	SG_BOOL IsNeedBuildIndex();
	// --- 是否需要重建动态路名
	
	SG_BOOL IsNeedBuildDyncName();
	//---是否影响PubSrv的视图
	
	SG_BOOL IsInfectPubView();
};


//"对象实例"基础属性结构
#define	SG_FLAG_MASK_VALUE		0x3f

struct _DATASET_DLL_EXPORT_ ObjAttribStruct_Base
{
	/*				多功能标记 --- 容器/组合对象内设备
	数据源存储: 在GeoDataBase的SGF_FLAG字段中
	Case 1: 对象的父设备为显式容器
	系统处理方法:当不显示内部信息时不显示 --- 通过拓扑获得该这种对象时，需要从容器关系类中获得其包容对象
	Case 2: 对象的父设备为组合容器(如多路开关)
	系统处理方法:对象只是一个GIS管理的对象，一般不参与显示、但支持拓扑,通过拓扑获得该这种对象时，
		需要从容器关系类中获得组合对象进行列表，本身不参与查询、统计
	Case 3:同case2, 不同之处在于基础对象具有对应的台帐(如杆塔/主变)
	*/
	union{
		SG_UINT KernelValue;
		struct
		{
#if defined(__sun)||defined(_AIX)
			SG_UCHAR lastdrawf:5;		//Draw对象时已经被Draw标记
			SG_UCHAR reserved2:1;		//保留1
			SG_UCHAR poweronf:1;		//在PUBSRV上被用作记录带电状态，同非开关类设备的status
			SG_UCHAR outRegionf:1;		//范围外标记
			
			SG_UCHAR changef:1;		// --- 网络拓扑用，与上次计算相比值属性是否出现变化
			SG_UCHAR overloadf:1;	//过载
			SG_UCHAR directionf:1;	//方向特征 F－T＝0 T－F=1,当value=0时无效
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR lockf:1;		//接地标志/闭锁标志
			SG_UCHAR mansetf:1;		//置数
			SG_UCHAR studyvalue_bak:1;	//模拟态状态值备份
			SG_UCHAR status_bak:1;		//状态值/带电标志 -- 备份
			// --- 以上为8 bit
			
			SG_UCHAR TargetObjF:1;	//拓扑计算时 --- 目标对象
			SG_UCHAR TopStopF:1;		//拓扑计算时 --- 该对象停止深度搜索			
			SG_UCHAR TopErrDirF:1;		//拓扑计算时 --- 该对象为错误方向上的对象
			SG_UCHAR TopMainPath:1;		//拓扑计算时 --- 该对象在主路径上
			SG_UCHAR SearchFlag:1;		//拓扑计算中 --- 被检索过标记
			SG_UCHAR TopUseFlag:1;		//拓扑计算中 --- 该对象是否可用
			SG_UCHAR TwinkleFlag:1;		//闪烁标志位
			SG_UCHAR SelFlag:1;			//选择标志位
			SG_UCHAR studyvalue:1;		//模拟态状态值
			SG_UCHAR UseItFlag:1;		//当前对象是否参与查询统计分析
			// --- 以上为16 bit

			//---以下6 bit位置不能变更
			SG_UCHAR StaticTopStopF:1;	//静态网络拓扑点
			SG_UCHAR status:1;			//状态值/带电标志
			SG_UCHAR visible_subtype:1; //由符号或者子类型控制其显示
			SG_UCHAR visible:1;         //控制显示 优先级高于visible_subtype
			SG_UCHAR hasdrawf:1;		//对象已经显示标记，视图选择实现“不可见不可选”应用该标记
			SG_UCHAR InsideF:1;
#else
			SG_UCHAR InsideF:1;
			SG_UCHAR hasdrawf:1;		//对象已经显示标记，视图选择实现“不可见不可选”应用该标记
			SG_UCHAR visible:1;         //控制显示 优先级高于visible_subtype
			SG_UCHAR visible_subtype:1; //由符号或者子类型控制其显示
			SG_UCHAR status:1;			//状态值/带电标志
			SG_UCHAR StaticTopStopF:1;	//静态网络拓扑点
			//---以上6 bit位置不能变更
			SG_UCHAR UseItFlag:1;		//当前对象是否参与查询统计分析
			SG_UCHAR studyvalue:1;		//模拟态状态值
			SG_UCHAR SelFlag:1;			//选择标志位
			SG_UCHAR TwinkleFlag:1;		//闪烁标志位
			SG_UCHAR TopUseFlag:1;		//拓扑计算中 --- 该对象是否可用
			SG_UCHAR SearchFlag:1;		//拓扑计算中 --- 被检索过标记
			SG_UCHAR TopMainPath:1;		//拓扑计算时 --- 该对象在主路径上
			SG_UCHAR TopErrDirF:1;		//拓扑计算时 --- 该对象为错误方向上的对象
			SG_UCHAR TopStopF:1;		//拓扑计算时 --- 该对象停止深度搜索
			SG_UCHAR TargetObjF:1;	//拓扑计算时 --- 目标对象
			// --- 以上为16 bit
			SG_UCHAR status_bak:1;		//状态值/带电标志 -- 备份
			SG_UCHAR studyvalue_bak:1;	//模拟态状态值备份
			SG_UCHAR mansetf:1;		//置数
			SG_UCHAR lockf:1;		//接地标志/闭锁标志
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR directionf:1;	//方向特征 F－T＝0 T－F=1,当value=0时无效
			SG_UCHAR overloadf:1;	//过载
			SG_UCHAR changef:1;		// --- 网络拓扑用，与上次计算相比值属性是否出现变化
			// --- 以上为8 bit
			SG_UCHAR outRegionf:1;		//范围外标记
            SG_UCHAR poweronf:1;			//在PUBSRV上被用作记录带电状态，同非开关类设备的status
            SG_UCHAR reserved2:1;		//保留2
            SG_UCHAR lastdrawf:5;		//Draw对象时已经被Draw标记
#endif			// --- 已经用满4字节
		}BitVal;
	};
	//
	//构造方法
	
	ObjAttribStruct_Base()
	{
		KernelValue = 0;
		BitVal.visible=true;
		BitVal.visible_subtype=true;
		BitVal.UseItFlag	=true;
		BitVal.mansetf		=true;
		BitVal.fromscadaf	=false;
		BitVal.outRegionf   = false;
        BitVal.lastdrawf    = 16;
	}
	// --- 设置可用
	
	inline void SetIt2Use(){BitVal.UseItFlag=true; BitVal.visible=true; BitVal.visible_subtype=true;}
	// --- 用无符号短整形属初始化结构值
	
	inline void InitKernelValue(SG_USHORT value){KernelValue=value;}
	// --- 获得低16位字节的无符号短整形内值
	
	inline SG_USHORT GetKernelValue(){return KernelValue;}
	// --- 获得运行态的状态值（是否带电或开关分合）
	
	inline SG_UCHAR GetRTValue(){return BitVal.status;}
	// --- 设置运行态的状态值（是否带电或开关分合）
	
	inline void SetRTValue(SG_UCHAR v){BitVal.status=v;}
	// --- 设置存库值
	
	inline void ValueToInside(SG_UINT invalue){invalue&=0x3f;KernelValue&=(0xffffffff-0x3f);KernelValue|=invalue;BitVal.visible=true;BitVal.visible_subtype=true;}
	
	inline SG_BOOL ValueToInside_Change(SG_UINT invalue){SG_UCHAR BakStatus=GetRTValue();ValueToInside(invalue);return BakStatus!=GetRTValue();}
	//清除所有拓扑相关标志位
	
	inline void ClearTopFlag()
	{
		BitVal.TopUseFlag = 0;
		BitVal.SearchFlag = 0;
		BitVal.TopMainPath = 0;
		BitVal.TopErrDirF = 0;
		BitVal.TopStopF = 0;
		BitVal.TargetObjF = 0;
	}
	//设置（状态控制下的）值
	
	inline void SetStatusValue(SG_UCHAR CalStatus,SG_UCHAR Value)
	{
		switch(CalStatus)
		{
		case SG_SYS_CAL_STATUS_REAL:
			{
				BitVal.changef = (BitVal.status_bak!=Value);
				BitVal.status = Value;
			}
			break;
		case SG_SYS_CAL_STATUS_STUDY:
			{
				BitVal.changef = (BitVal.studyvalue_bak!=Value);
				BitVal.studyvalue = Value;
			}
			break;
		}
	}
	//获得（状态控制下的）值
	
	inline SG_UCHAR GetStatusValue(SG_UCHAR CalStatus)
	{
		switch(CalStatus)
		{
		case SG_SYS_CAL_STATUS_REAL:
			return(BitVal.status);
			break;
		case SG_SYS_CAL_STATUS_STUDY:
			return(BitVal.studyvalue);
			break;
		}
		return 0;
	}
	
	inline void ClearStatusValue(SG_UCHAR CalStatus)
	{
		switch(CalStatus)
		{
		case SG_SYS_CAL_STATUS_REAL:{
				BitVal.status_bak = BitVal.status;BitVal.status = 0;
			}
			break;
		case SG_SYS_CAL_STATUS_STUDY:{
				BitVal.studyvalue_bak = BitVal.studyvalue;BitVal.studyvalue = 0;
			}
			break;
		}
		BitVal.changef=0;
	}
	
	inline void RealValueToStudy(){BitVal.studyvalue = BitVal.status;}
};

//"对象实例"扩展属性结构

struct _DATASET_DLL_EXPORT_ ObjAttribStruct_Ext:ObjAttribStruct_Base
{
	//??????????????????????????????
	//线路号,即线系的信息,线系的内控ID号全局唯一
	//		用CObjectBaseAttrib记录,该处记载电源点在CObjectBaseAttrib中的行号,-1为不在线路内的对象
	
	SG_SHORT lineno;		//所在的线路号
	//系统号,即电源点的信息,每个应用服务器具有各自的电源点信息
	//		用CSgDataSet记录,该处记载电源点在DataSet中的行号,-1为不在系统内的对象
	//		该对象是系统硬描述,维护的方法是将设备设置为电源点时写入对应的表中
	
	SG_SHORT sysno;		//所在的系统号
};


/*******************************************************
		part 150 内存占用检测
*******************************************************/


struct _DATASET_DLL_EXPORT_ MemUseCheck
{
	
	SG_INT ClassLen;		//类占用
	
	SG_INT TableInfoLen;	//表头占用
	
	SG_INT AttribLen;		//属性占用
	
	SG_INT TextAttribLen;	//文本属性占用
	
	SG_INT GeoAttribLen;	//几何属性占用
	
	SG_INT IndexLen;		//索引占用
	
	SG_INT GeoIndexLen;		//几何索引占用
	
	SG_INT ExtAttribLen;	//扩展属性占用
	
	SG_INT AllLen;			//总占用
	
	MemUseCheck();
	
	void AddAll();
	
	void Reset();
	
	const MemUseCheck& operator+=(const MemUseCheck&m);
};


//遥信在实时库中的属性结构 

struct _DATASET_DLL_EXPORT_ YaoXinAttribStruct
{
	union{
		SG_UCHAR Value;
		struct {
#if defined(__sun)||defined(_AIX)
			SG_UCHAR res:5;
			SG_UCHAR changef:1;		// --- 数据更改标记
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR mansetf:1;		//置数
#else
			SG_UCHAR mansetf:1;		//置数
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR changef:1;		// --- 数据更改标记
			SG_UCHAR res:5;
#endif
		}BitVal;
	};
	
	YaoXinAttribStruct(){Value=0;}
	//设置内值
	
	void SetValue(SG_UCHAR value){Value = value;}
	//读取内值
	
	SG_UCHAR GetValue(){return Value;}
};

//"遥测实例"属性结构 通 遥测实时库中的属性结构 

struct _DATASET_DLL_EXPORT_ YaoCeAttribStruct
{
	union{
		SG_UCHAR Value;
		struct {
#if defined(__sun)||defined(_AIX)
			SG_UCHAR res:1;		
			SG_UCHAR changef:1;		// --- 数据更改标记
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR overlowf:1;	//越下限
			SG_UCHAR overhighf:1;	//越上限
			SG_UCHAR overloadf:1;	//过载
			SG_UCHAR deadf:1;		//死数标记
			SG_UCHAR mansetf:1;		//置数标记
#else
			SG_UCHAR mansetf:1;		//置数标记
			SG_UCHAR deadf:1;		//死数标记
			SG_UCHAR overloadf:1;	//过载
			SG_UCHAR overhighf:1;	//越上限
			SG_UCHAR overlowf:1;	//越下限
			SG_UCHAR fromscadaf:1;	//SCADA系统数据标记
			SG_UCHAR changef:1;		// --- 数据更改标记
			SG_UCHAR res:1;		
#endif
		}BitVal;
	};
	
	YaoCeAttribStruct(){Value=0;}
	//设置内值
	
	void SetValue(SG_UCHAR value){Value=value;}
	//读取内值
	
	SG_UCHAR GetValue()	{return Value;}
};

//Lock 自动管理
template <class T>
class CLockManager
{
public:
	CLockManager(T*p){
		m_t = p;
		if(m_t) m_t->Lock();
	}
	~CLockManager(){
		if(m_t) m_t->UnLock();
	}
protected:
	T * m_t;
};

template <class T>
class CLockManagerRead
{
public:
	CLockManagerRead(T*p){
		m_t = p;
		if(m_t) m_t->LockRead();
	}
	~CLockManagerRead(){
		if(m_t) m_t->UnLock();
	}
protected:
	T * m_t;
};

template <class T>
class CLockManagerWrite
{
public:
	CLockManagerWrite(T*p){
		m_t = p;
		if(m_t) m_t->LockWrite();
	}
	~CLockManagerWrite(){
		if(m_t) m_t->UnLock();
	}
protected:
	T * m_t;
};
#ifdef WIN32
#pragma   warning   (disable:   4083 4786)   
#endif
#include <string>
#include <map>
#include <set>
#include <vector>
#include <deque>
#include <list>
typedef std::vector<int > VECT_INT;
typedef std::set<int> SET_INT;
typedef std::set<SG_NODEINT > SET_NODEINT;
typedef std::map< SG_NODEINT, SG_NODEINT >				MAP_NODEINT_NODEINT;
typedef std::vector<void *> VECT_VOIDPT;
typedef std::vector < SG_NODEINT >			VECT_NODEINT;
typedef std::deque<void *> DEQUE_VOIDPT;
typedef std::list<void *> LIST_VOIDPT;
typedef std::multimap<int,int>	MULTMAP_INT_INT;
typedef std::map<int,int>	MAP_INT_INT;
typedef std::map<int,double>	MAP_INT_DOUBLE;
typedef std::multimap< int,int >	MULTIMAP_INT_INT;
typedef std::multimap< int,void *>	MULTIMAP_INT_VOIDPT;
typedef std::multimap<int,std::string > MULTIMAP_INT_STRING;
typedef std::map<int,std::string > MAP_INT_STRING;
typedef std::map<std::string,int > MAP_STRING_INT;
typedef std::set<std::string > SET_STRING;
typedef std::set<void * > SET_VOIDPT;
typedef std::map<int,void *> MAP_INT_VOIDPT;
typedef std::map<SG_INT64, void *> MAP_INT64_VOIDPT;
typedef std::map<void *,int > MAP_VOIDPT_INT;
typedef std::map<std::string,void *> MAP_STRING_VOIDPT;
typedef std::vector <std::string > VECT_STRING;
typedef struct S_TWOINT
{
	int		Val1;
	int		Val2;
	static int	Compare(const S_TWOINT &obj1,const S_TWOINT &obj2)
	{
		if(obj1.Val1<obj2.Val1)
			return -1;
		if(obj1.Val1==obj2.Val1)
		{
			if(obj1.Val2<obj2.Val2)
				return -1;
			else if(obj1.Val2==obj2.Val2)
				return 0;
		}
		return 1;
	};
	SG_BOOL Serialize(CSgArchive &ar)
	{
		if(ar.IsLoading())
		{
			ar >> Val1;
			ar >> Val2;
		}
		else
		{
			ar << Val1;
			ar << Val2;
		}
		return true;
	}
}S_TWOINT;
struct CTwoIntLess:
	public std::binary_function<S_TWOINT, S_TWOINT, bool> {
		bool operator()(const S_TWOINT & obj1, const S_TWOINT & obj2) const
		{
			if(S_TWOINT::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
struct CTwoIntGreater:
	public std::binary_function<S_TWOINT,S_TWOINT,bool> {
	bool operator()(const S_TWOINT & obj1,const S_TWOINT & obj2) const
	{
		if(S_TWOINT::Compare(obj1,obj2)>0)
			return true;
		return false;
	}
};

template< typename T,int T_NUM >
class  CClassIntT
{
public:
	T			Val[T_NUM];
public:
	static int	Compare(const CClassIntT &obj1, const CClassIntT &obj2)
	{
		int i;
		for (i = 0; i < T_NUM; i++)
		{
			if (obj1.Val[i] < obj2.Val[i])
				return -1;
			if (obj1.Val[i] > obj2.Val[i])
				return 1;
		}
		return 0;
	};
	CClassIntT()
	{
		Init();
	};
	void Init()
	{
		int i;
		for (i = 0; i < T_NUM;i++)
			Val[i] = 0;
	};
	SG_BOOL Serialize(CSgArchive &ar)
	{
		int i;
		if (ar.IsLoading())
		{
			for (i = 0; i < T_NUM; i++)
				ar >> Val[i];
		}
		else
		{
			for (i = 0; i < T_NUM; i++)
				ar << Val[i];
		}
		return true;
	}
};
template< typename CLASSINT_T>
class  CClassIntLessT :
	public std::binary_function<CLASSINT_T, CLASSINT_T, bool> {
public:
	 bool operator()(const CLASSINT_T &obj1, const CLASSINT_T &obj2) const
	{
		if (CLASSINT_T::Compare(obj1, obj2) < 0)
			return true;
		return false;
	}
};
template< typename CLASSINT_T>
class  CClassIntGreaterT :
	public std::binary_function<CLASSINT_T, CLASSINT_T, bool> {
public:
	 bool operator()(const CLASSINT_T & obj1, const CLASSINT_T & obj2) const
	{
		if (CLASSINT_T::Compare(obj1, obj2) > 0)
			return true;
		return false;
	}
};
typedef CClassIntT<SG_INT64,2 > S_TWOINT64;
typedef CClassIntLessT<S_TWOINT64 > CTwoInt64Less;
typedef CClassIntGreaterT<S_TWOINT64 > CTwoInt64Greater;

typedef CClassIntT<SG_INT, 3 > S_THREEINT;
typedef CClassIntLessT<S_THREEINT > CThreeIntLess;
typedef CClassIntGreaterT<S_THREEINT > CThreeIntGreater;
typedef CClassIntT<SG_UINT, 3 > S_THREEUINT;
typedef CClassIntLessT<S_THREEUINT > CThreeUIntLess;
typedef CClassIntGreaterT<S_THREEUINT > CThreeUIntGreater;

typedef CClassIntT<SG_INT64, 3 > S_THREEINT64;
typedef CClassIntLessT<S_THREEINT64 > CThreeInt64Less;
typedef CClassIntGreaterT<S_THREEINT64 > CThreeInt64Greater;

typedef CClassIntT<SG_INT, 4 > S_FOURINT;
typedef CClassIntLessT<S_FOURINT > CFourIntLess;
typedef CClassIntGreaterT<S_FOURINT > CFourIntGreater;

typedef CClassIntT<SG_INT, 5 > S_FIVEINT;
typedef CClassIntLessT<S_FIVEINT > CFiveIntLess;
typedef CClassIntGreaterT<S_FIVEINT > CFiveIntGreater;

typedef CClassIntT<SG_NODEINT, 2 > S_TWONODEINT;
typedef CClassIntLessT<S_TWONODEINT > CTwoNodeIntLess;
typedef CClassIntGreaterT<S_TWONODEINT > CTwoNodeIntGreater;

typedef struct S_TWOSTRING
{
	std::string Val1;
	std::string Val2;
	static int	Compare(const S_TWOSTRING &obj1,const S_TWOSTRING &obj2)
	{
		int ret=strcmp(obj1.Val1.data(),obj2.Val1.data());
		if(ret==0)
			ret=strcmp(obj1.Val2.data(),obj2.Val2.data());
		return ret;
	};
}S_TWOSTRING;
struct CTwoStringLess:
	public std::binary_function<S_TWOSTRING, S_TWOSTRING, bool> {
		bool operator()(const S_TWOSTRING & obj1, const S_TWOSTRING & obj2) const
		{
			if(S_TWOSTRING::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
typedef struct S_TWOINTSTR
{
	int			IntVal[2];
	std::string StrVal;
	static int	Compare(const S_TWOINTSTR &obj1,const S_TWOINTSTR &obj2)
	{
		int i;
		for(i=0;i<2;i++)
		{
			if(obj1.IntVal[i]<obj2.IntVal[i])
				return -1;
			if(obj1.IntVal[i]>obj2.IntVal[i])
				return 1;
		}
		int ret=strcmp(obj1.StrVal.data(),obj2.StrVal.data());
		return ret;
	};
	void Init()
	{
		IntVal[0]=IntVal[1]=0;
		StrVal="";
	};
}S_TWOINTSTR;
struct CTwoIntStrLess:
	public std::binary_function<S_TWOINTSTR,S_TWOINTSTR,bool> {
	bool operator()(const S_TWOINTSTR & obj1,const S_TWOINTSTR & obj2) const
	{
		if(S_TWOINTSTR::Compare(obj1,obj2)<0)
			return true;
		return false;
	}
};
/*
typedef struct S_TWONODEINT
{
	SG_NODEINT Val[2];
	static int	Compare(const S_TWONODEINT &obj1,const S_TWONODEINT &obj2)
	{
		if(obj1.Val[0]<obj2.Val[0])
			return -1;
		if(obj1.Val[0]==obj2.Val[0])
		{
			if(obj1.Val[1]<obj2.Val[1])
				return -1;
			else if(obj1.Val[1]==obj2.Val[1])
				return 0;
		}
		return 1;
	};
	void Init()
	{
		Val[0]=Val[1]=0;
	};
}S_TWONODEINT;
struct CTwoNodeIntLess:
	public std::binary_function<S_TWONODEINT, S_TWONODEINT, bool> {
		bool operator()(const S_TWONODEINT & obj1, const S_TWONODEINT & obj2) const
		{
			if(S_TWONODEINT::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
*/
typedef struct S_STRINGINT
{
	std::string		StrVal;
	SG_INT			IntVal;
	static int	Compare(const S_STRINGINT &obj1,const S_STRINGINT &obj2)
	{
		if(obj1.IntVal<obj2.IntVal)
			return -1;
		if(obj1.IntVal>obj2.IntVal)
			return 1;
		return strcmp(obj1.StrVal.data(),obj2.StrVal.data());
	};
}S_STRINGINT;
struct CStringIntLess:
	public std::binary_function<S_STRINGINT,S_STRINGINT,bool> {
	bool operator()(const S_STRINGINT & obj1,const S_STRINGINT & obj2) const
	{
		if(S_STRINGINT::Compare(obj1,obj2)<0)
			return true;
		return false;
	}
};
typedef union SG_UNION_UINT64
{
	SG_UINT64 Int64Val;
	struct
	{
#if defined(__sun)||defined(_AIX)
		SG_UINT IntVal1;
		SG_UINT IntVal2;
#else
		SG_UINT IntVal2;
		SG_UINT IntVal1;
#endif
	}IntVal;
}SG_UNION_UINT64;

typedef struct S_TWOVOIDPT
{
	void *pVoid[2];
}S_TWOVOIDPT;
typedef struct SG_INTDBL
{
	SG_INT		IntVal;
	SG_DOUBLE	DblVal;
}SG_INTDBL;
typedef struct S_VOIDPTINT
{
	int			IntVal;
	void		*pVoid;
	static int	Compare(const S_VOIDPTINT &obj1, const S_VOIDPTINT &obj2)
	{
		if (obj1.pVoid < obj2.pVoid)
			return -1;
		if (obj1.pVoid == obj2.pVoid)
		{
			if (obj1.IntVal < obj2.IntVal)
				return -1;
			else if (obj1.IntVal == obj2.IntVal)
				return 0;
		}
		return 1;
	};
}S_VOIDPTINT;
struct CVoidPtIntLess :
	public std::binary_function<S_VOIDPTINT, S_VOIDPTINT, bool> {
	bool operator()(const S_VOIDPTINT & obj1, const S_VOIDPTINT & obj2) const
	{
		if (S_VOIDPTINT::Compare(obj1, obj2) < 0)
			return true;
		return false;
	}
};
typedef struct SG_STRDBL
{
	std::string	StrVal;
	SG_DOUBLE	DblVal;
}SG_STRDBL;
typedef struct S_TWODBL
{
	SG_DOUBLE	Val1;
	SG_DOUBLE	Val2;
}S_TWODBL;
typedef struct S_VOIDPTTWOINT
{
	S_TWOINT	IntVal;
	void		*pVoid;
}S_VOIDPTTWOINT;
typedef struct S_STRINT64
{
	std::string	StrVal;
	SG_INT64	IntVal;
}S_STRINT64;
typedef std::map<SG_INT,S_VOIDPTINT > MAP_INT_VOIDPTINT;
typedef std::set<S_VOIDPTINT, CVoidPtIntLess > SET_VOIDPTINT;
typedef std::map<S_VOIDPTINT,void *,CVoidPtIntLess > MAP_VOIDPTINT_VOIDPT;
typedef std::map<void *, S_VOIDPTINT > MAP_VOIDPT_VOIDPTINT;
typedef std::map<std::string,S_VOIDPTINT > MAP_STRING_VOIDPTINT;
typedef std::map<SG_INT,SG_INTDBL > MAP_INT_INTDBL;
typedef std::map<SG_INT,SG_STRDBL > MAP_INT_STRDBL;
typedef std::vector<SG_INTDBL > VECT_INTDBL;
typedef std::multimap<SG_INT,SG_INTDBL > MULTMAP_INT_INTDBL;
typedef std::map<SG_INT,S_TWOVOIDPT> MAP_INT_TWOVOIDPT;

typedef std::vector<S_STRINT64	>	VECT_STRINT64;
typedef std::vector<S_THREEINT64>   VECT_THREEINT64;
typedef std::vector<S_STRINGINT	>		VECT_STRINT;
typedef std::map<SG_INT,S_STRINGINT> MAP_INT_STRINT;
typedef std::map<S_STRINGINT,SG_INT,CStringIntLess> MAP_STRINT_INT;
typedef std::set<S_STRINGINT, CStringIntLess> SET_STRINT;
typedef std::map<S_STRINGINT,S_TWOINT,CStringIntLess> MAP_STRINT_TWOINT;
typedef std::multimap<SG_INT,S_STRINGINT> MULTIMAP_INT_STRINT;
typedef std::map<S_TWOINT,SG_DOUBLE,CTwoIntLess> MAP_TWOINT_DBL;
typedef std::multimap< int,S_TWOINT >	MULTIMAP_INT_TWOINT;
typedef std::set<S_TWOINT,CTwoIntLess> SET_TWOINT;
typedef std::set<S_TWOINT64, CTwoInt64Less> SET_TWOINT64;
typedef std::set<S_FIVEINT, CFiveIntLess> SET_FIVEINT;
typedef std::map<S_TWOINT64,SG_INT, CTwoInt64Less> MAP_TWOINT64_INT;
typedef std::map<S_FIVEINT,SG_INT, CFiveIntLess> MAP_FIVEINT_INT;
typedef std::map<SG_INT, S_FIVEINT> MAP_INT_FIVEINT;
typedef std::vector<S_TWOINT> VECT_TWOINT;
typedef std::vector<S_THREEINT> VECT_THREEINT;
typedef std::map<SG_INT,S_TWOINT> MAP_INT_TWOINT;
typedef std::map<SG_INT,S_TWOSTRING>	MAP_INT_TWOSTRING;
typedef std::multimap<SG_INT,S_TWOINT> MULTMAP_INT_TWOINT;
typedef std::map<S_TWOINTSTR,int,CTwoIntStrLess> MAP_TWOINTSTR_INT;
typedef std::map<S_TWOINTSTR,S_TWOINT,CTwoIntStrLess> MAP_TWOINTSTR_TWOINT;
typedef std::map<S_TWOSTRING,S_TWOINT,CTwoStringLess> MAP_TWOSTR_TWOINT;
typedef std::multimap<S_TWOINTSTR,int,CTwoIntStrLess> MULTMAP_TWOINTSTR_INT;
typedef std::map<S_TWOINT,int,CTwoIntLess> MAP_TWOINT_INT;
typedef std::map<S_TWOINT,double,CTwoIntGreater> MAP_GREATER_TWOINT_DBL;
typedef std::map<S_TWOINT,S_TWOINT,CTwoIntLess> MAP_TWOINT_TWOINT;
typedef std::map<S_TWOINT,void *,CTwoIntLess> MAP_TWOINT_VOIDPT;
typedef std::multimap<S_TWOINT,void *,CTwoIntLess> MULTIMAP_TWOINT_VOIDPT;
typedef std::multimap<S_TWOINT,S_THREEINT,CTwoIntLess> MULTIMAP_TWOINT_THREEINT;
typedef std::multimap<S_THREEINT,SG_INT,CThreeIntLess> MULTIMAP_THREEINT_INT;
typedef std::multimap<S_THREEINT,SG_INT,CThreeIntGreater> MULTIMAP_GREATER_THREEINT_INT;
typedef std::map<S_THREEINT, SG_DOUBLE, CThreeIntGreater> MAP_GREATER_THREEINT_DBL;
typedef std::map<std::string,S_TWOINT > MAP_STRING_TWOINT;
//typedef std::multimap<int,int,std::greater<int>> MULTIMAP_GREATER_INT_INT;
typedef std::multimap<std::string, SG_INT > MULTMAP_STRING_INT;
typedef std::multimap<SG_INT,std::string > MULTMAP_INT_STRING;
typedef std::map<S_THREEINT,S_TWOINT,CThreeIntLess> MAP_THREEINT_TWOINT;
typedef std::multimap<S_THREEINT,S_TWOINT,CThreeIntLess> MULTMAP_THREEINT_TWOINT;
typedef std::multimap<S_THREEINT,SG_INT,CThreeIntLess> MULTMAP_THREEINT_INT;
typedef std::multimap<S_TWOINT,SG_INT,CTwoIntLess> MULTIMAP_TWOINT_INT;
typedef std::multimap<S_TWOINT,S_TWOINT,CTwoIntLess> MULTIMAP_TWOINT_TWOINT;
typedef std::multimap<SG_INT,S_THREEINT> MULTIMAP_INT_THREEINT;
typedef std::map<std::string,S_THREEINT > MAP_STRING_THREEINT;
typedef std::map<std::string, S_FOURINT > MAP_STRING_FOURINT;
typedef std::map<int,S_THREEINT > MAP_INT_THREEINT;
typedef std::vector < S_TWONODEINT >			VECT_TWONODEINT;
typedef std::vector<S_TWOSTRING >			VECT_TWOSTRING;
typedef std::map<S_THREEINT,SG_INT,CThreeIntLess> MAP_THREEINT_INT;
typedef std::map<S_THREEUINT, SG_INT, CThreeUIntLess> MAP_THREEUINT_INT;
typedef std::deque<S_TWOINT		>  DEQUE_TWOINT;
typedef std::multimap<SG_INT,SG_NODEINT>	MULTIMAP_INT_NODEINT;
typedef std::multimap<SG_NODEINT,S_TWOINT>	MULTIMAP_NODEINT_TWOINT;
typedef std::multimap<S_TWOINT,SG_NODEINT,CTwoIntLess>	MULTIMAP_TWOINT_NODEINT;
typedef std::map<SG_NODEINT,S_TWOINT>	MAP_NODEINT_TWOINT;
typedef std::map< SG_NODEINT,SgPoint >					MAP_NODEINT_PT;
typedef std::map< SG_NODEINT,void * >					MAP_NODEINT_VOIDPT;
typedef std::multimap< SG_NODEINT,SG_INT>			MULTMAP_NODEINT_INT;
typedef std::map< SG_NODEINT,SG_INT>			MAP_NODEINT_INT;
typedef std::map<S_TWOINT,S_THREEINT,CTwoIntLess> MAP_TWOINT_THREEINT;
typedef std::map<S_FOURINT,S_TWOINT,CFourIntLess> MAP_FOURINT_TWOINT;
typedef std::multimap<S_TWOINT,S_THREEINT,CTwoIntLess> MULTIMAP_TWOINT_THREEINT;
typedef std::multimap<S_THREEINT,SG_INT,CThreeIntLess> MULTIMAP_THREEINT_INT;
typedef std::map<S_THREEINT,SG_DOUBLE,CThreeIntLess> MAP_THREEINT_DBL;
typedef std::set<S_THREEINT,CThreeIntLess>	SET_THREEINT;
typedef std::set<S_FOURINT,CFourIntLess>	SET_FOURINT;
typedef std::map<S_TWOINT,std::string,CTwoIntLess> MAP_TWOINT_STRING;
typedef std::map<SG_INT, S_VOIDPTTWOINT > MAP_INT_VOIDPTTWOINT;
typedef std::map<std::string, S_VOIDPTTWOINT > MAP_STRING_VOIDPTTWOINT;
typedef std::vector<SG_INT64> VECT_INT64;
typedef std::set<SG_INT64> SET_INT64;
typedef std::vector<S_TWOINT64> VECT_TWOINT64;
typedef std::multimap<SG_INT64,SG_INT64> MULTMAP_INT64_INT64;
typedef std::multimap<SG_INT64, SG_INT> MULTMAP_INT64_INT;
typedef std::map<SG_INT64, SG_INT64> MAP_INT64_INT64;
typedef std::map<SG_INT64, SG_INT> MAP_INT64_INT;
typedef std::map<std::string, std::string > MAP_STRING_STRING;
typedef std::map<SG_INT64, S_TWOVOIDPT> MAP_INT64_TWOVOIDPT;

#if defined(WIN32)
#define sg_strcasecmp(a,b) _stricmp((a),(b))
#else
#define sg_strcasecmp(a,b) strcasecmp((a),(b))
#endif

#endif
