	// csgtableinfo.h
//

#if !defined(CSgTableInfo_h)
#define CSgTableInfo_h
#include <stdio.h>
#include <string.h>

#include "sgdataset.h"
#include "sgmicro.h"

#define		TABLEINFO_USEABLE		1
#define		TABLE_USEABLE			2

#define		CHAR_TO_VARCHAR_LEN		16	//对应长度超出16个字节的字符串字段内存中用VarChar记录
#define		VARCHAR_TO_CHAR_LEN		8	//对于长度小于8的边长字符串内存中用CHAR记录

/***********************************************
		对象属性表域信息结构
***********************************************/
//对象属性表域信息结构

class _DATASET_DLL_EXPORT_ CSgFieldInfo
{
private:
	
	CSgString FieldName;
public:
	
	SG_SHORT FieldType;
	
	SG_SHORT FieldLen;
	
	SG_SHORT SqlType;			// for oracle
	
	SG_USHORT ConPtr;			//字段内容在一条记录中的终止相对位置
	union{
		SG_USHORT SerializeValue;
		struct
		{
#if defined(__sun)||defined(_AIX)
            SG_UCHAR Reserved:5;
			SG_UCHAR SdeRowIDFiled:1;
           SG_UCHAR SdeAttribFlag:1;
			SG_UCHAR ChangeFlag:1;		//列值是否修改---StartEditTable后的操作用
			SG_UCHAR IsBlob:1;			//是否Blob字段－用CSgVariate管理
			SG_UCHAR IsVarChar:1;		//是否VarChar－用CSgString管理
			SG_UCHAR GraphFlag:1;		//几何属性标志——自定义表中的几何域，只允许通过几何结构相关的方法赋值
			SG_UCHAR CommonFlag:1;		//条件属性
            SG_UCHAR ExtAttribFlag:1;
			SG_UCHAR UpdateFlag:1;		//创建sql语句时是否可以被update
			SG_UCHAR Primary:1;//主键
            SG_UCHAR CanBeNull:1;//允许空
#else
            SG_UCHAR CanBeNull:1;//允许空
			SG_UCHAR Primary:1;//主键
			SG_UCHAR UpdateFlag:1;		//创建sql语句时是否可以被update
			/*
			 *	外扩展数据源中的属性标示，图形属性未做冗余前，与SdeAttribFlag互斥
			 *  在冗余处理后，可能同时为1
			 *  改造前置位的唯一入口为：DataSet的ExtendFieldInfo方法，一般由数据集的Combin方法自动调用
			 *  改造后的处理方式会产生变更，变更方法见Combin方法的原型描述
			 */
			SG_UCHAR ExtAttribFlag:1;
			SG_UCHAR CommonFlag:1;		//条件属性
			SG_UCHAR GraphFlag:1;		//几何属性标志——自定义表中的几何域，只允许通过几何结构相关的方法赋值
			SG_UCHAR IsVarChar:1;		//是否VarChar－用CSgString管理
			SG_UCHAR IsBlob:1;			//是否Blob字段－用CSgVariate管理
			SG_UCHAR ChangeFlag:1;		//列值是否修改---StartEditTable后的操作用
			/*
			 *	表明该字段为图形数据源中的属性，缺省值为0，该标记的建立的唯一入口为：
			 *  ArcSDE接口中获得记录或表信息时，将标记为置1
			 */
			SG_UCHAR SdeAttribFlag:1;
			SG_UCHAR SdeRowIDFiled:1;
            SG_UCHAR Reserved:5;
#endif
        }BitVal;
	};
	/*
	 *	以下变量与应用环境相关，不参与网络传输传输
	 */
	SG_UCHAR Catch_EffectView:1;		//内容变化时是否在CheckChangeFlag方法中建立“影响视图”标记
	SG_UCHAR Catch_EffectIndex:1;		//内容变化时是否在CheckChangeFlag方法中建立“影响索引”标记
	SG_UCHAR Catch_EffectLoadRange:1;	//内容变化时是否在CheckChangeFlag方法中建立“影响加载”标记
public:
	CSgFieldInfo();
	~CSgFieldInfo();
	//设置域名
	void SetFieldName(SG_PCSTR pFieldName);
	//获得域名
	SG_PSTR GetFieldName();
	/*
	 *  用途：判断两个域信息是否一致
	 *  判据：两个域名称、类型、域长度是否完全一致
	 *  注意：DecideConPtr决定是否判断域在表信息中的内容相对长度【通常当判断两个DataSet完全一致时入参数为true】
	 */ 
	SG_BOOL Equal(CSgFieldInfo *p,SG_BOOL DecideConPtr);
	//判断两个域名是否一致
	SG_BOOL EqualName(SG_PCSTR p);
	//判断域是否基础域，判据：具有SdeAttribFlag或不是ExtAttrib的域
	SG_BOOL IsBaseField();
	//序列号处理
	SG_BOOL Serialize(CSgArchive&ar);

	//	赋值操作
	CSgFieldInfo & Assign( const CSgFieldInfo & rhs );
	CSgFieldInfo & operator = ( const CSgFieldInfo & rhs );

	SG_BOOL IsMathType();
};


class _DATASET_DLL_EXPORT_ CSgTableInfo : public CSgPtrArray
{
public:
	
	CSgTableInfo();
	
	virtual ~CSgTableInfo();
	
	virtual void RemoveAll();
	
	void ResetTableInfo();

protected:
	// --- 以下保护成员的类型不能变更（参与序列化网络传输）
	
    SG_UINT		m_RecordNums;	//记录的数量
	
	SG_UINT		m_RecordSize;	//记录实际开辟内存的数量
	
    SG_SHORT	m_ObjectType;	//依附的设备类型
	
	SG_SHORT	m_ArcGisID_ptr;	//
	
	SG_SHORT	m_ID_ptr;		//
	
	SG_USHORT	m_FieldNums;	//字段数量
	
    SG_USHORT	m_RecordLen;	//每记录的长度
	
	SG_UCHAR	m_FeatureType;	//依附的对象基础特征类型
	
	SG_UCHAR	m_UseAble;		//DataSet是否可用
	
	SG_UCHAR	m_HasGeometryFlag;	//是否具有几何字段
	
protected:
	
	SG_CHAR		m_Flag_ptr;		//
	// --- 实例的类型，仅仅用于网络传输中接收侧的反序列化控制
	// 支持发送侧为基类，接受侧声明的为派生类，反之会造成系统的通信异常
	//SG_UCHAR	m_InstanceType;
	//内控属性类型 --- 决定对象化后,系统自动给其增加的内控信息类型
	
	ObjType_IA_Cfg_Struct m_ObjControlAttrib;
	//
	
    CSgString	m_ObjectTypeName;
	
    CSgString	m_TableName;//表名称
	//创建数据集的Where子句
	
	CSgString	m_WhereWord;
	//
	//记录偏移量，不数据传递
	SG_SHORT	m_AD_ID_ptr;//A/D表的主键
	SG_SHORT	m_TaskID_ptr;
	
public:
	//
	SG_UCHAR GetBaseFeatureType(){ return m_FeatureType;}
	void SetBaseFeatureType(SG_UCHAR ft){ m_FeatureType=ft;}
	
	//获得、设置DataSet依附的对象类型
	
	void SetObjType(SG_SHORT type){ m_ObjectType=type;}
	SG_SHORT GetObjType(){ return m_ObjectType;}

	//获得、设置DataSet依附的对象名称
	void SetObjectName(const char* name){ m_ObjectTypeName=name;}
	SG_PCSTR GetObjectName(){ return m_ObjectTypeName.GetSafeBuffer();}
	//数据集可用－具有记录
	SG_BOOL GetUseAble(){ return m_UseAble==TABLE_USEABLE;}
	//获得记录长度
	SG_USHORT GetRecordLen(){ return m_RecordLen;}
	//表信息可用
	
	SG_BOOL GetTableInfoUseAble(){return m_UseAble==TABLEINFO_USEABLE||m_UseAble==TABLE_USEABLE;}
	//获得是否具有几何属性标记 --- 仅用于编辑时Update动作的控制
	
	SG_UCHAR GetHasGeometry(){return m_HasGeometryFlag;}
	//设置是否具有几何属性 --- 仅用于编辑时Update动作的控制
	
	void SetHasGeometry(SG_UCHAR flag);
	//设置访问的表名
	
    void SetTableName(SG_PCSTR tablename);
	//获得表名称
	
    SG_PSTR GetTableName();
	//表名与name是否一致
	
	SG_BOOL IsNameEqual(SG_PCSTR name);
	//设置表头信息
	
    SG_BOOL SetFieldNums(SG_INT nums);						//字段数量
	
    void SetFieldName(SG_INT fieldptr, SG_PCSTR name);		//字段名
	
    void SetFieldType(SG_INT fieldptr, SG_INT type);		//字段类型
	
	void SetFieldInfo(SG_INT ptr,CSgFieldInfo*fi);		//设置字段结构信息
	
    void SetFieldLen(SG_INT fieldptr, SG_INT len);			//字段长度
	
    void SetFieldCanBeNull(SG_INT ptr, SG_BOOL flag);		//允许为空
	
    void SetFieldPrimary(SG_INT fieldptr, SG_BOOL value);	//字段为主键
	
    void SetFieldPrimary(SG_CHAR* fieldname);				//字段为主键
	
    void SetFieldSqlType(SG_INT fieldptr, SG_INT type);		//字段访问数据源的简化类型
	
    void SetUpdateFlag(SG_BOOL flag);						//设置所有字段的是否可被Update操作
	
    void SetUpdateFlag(SG_INT ptr, SG_BOOL flag);			//字段是否可被Update操作
	
	void SetChangeFlag(SG_BOOL flag=true);					//设置所有字段的被更改标志
	
	void SetChangeFlag(SG_INT ptr,SG_BOOL Flag);			//设置字段被更改标志
	
	void SetFieldIsGisID(SG_INT ptr);					//设置字段为系统的对象ID
	
	void SetFieldIsArcGisID(SG_INT ptr);				//设置字段为ArcSDE的ObjectID
	
	void SetIdIsSysID();								//ID字段为SgGis/ArcGisID/主键
	void SetIsSdeField(SG_INT ptr,SG_BOOL IsSdeAttrib);	//设置是否为存储在Sde中的属性
	// --- 获得列内容相对于当前行的终止相对位置
	void SetFieldIsSdeRowID(SG_INT ptr, SG_BOOL flag);		//设置字段是否是SDE的RowID字段
	SG_BOOL GetFieldIsSdeRowID(SG_INT ptr);
	SG_INT GetColConPtr(SG_SHORT FieldPos);
	//是否具有某种类型字段
	
	SG_BOOL HasField(SG_SHORT fieldtype);
	//是否具有Raw字段
	
	SG_BOOL HasRawField(){return HasField(SG_FIELDTYPE_RAW);}
	//是否具有日期时间字段
	
	SG_BOOL HasDateTimeField(){return HasField(SG_FIELDTYPE_DATETIME);}
	
    static SG_INT GetFieldTrueLen(CSgFieldInfo * p);
	// --- 获得最长的字符串字段的宽度
	
	SG_SHORT GetMaxCharLen();
	//
	
	virtual SG_BOOL BuildTableInfo();
	//
	
    SG_UINT GetRecordNums(){return m_RecordNums;}
	// --- 获得记录集的域数量
	SG_INT GetFieldNums(){ return m_FieldNums;}
	// --- 获得记录集中基础域的数量
	SG_SHORT GetBaseFieldNums();
	
	SG_SHORT GetGisIDPtr()	{ return m_ID_ptr;	} 			//对象功能位置ID字段的位置
	SG_SHORT GetFlagPtr()		{ return m_Flag_ptr;}
	
	SG_SHORT GetArcGisIDPtr()	{ return m_ArcGisID_ptr;}	//对象图元ID字段的位置
	SG_SHORT GetADTableIDPtr()	{ return m_AD_ID_ptr;}		//得到a/d表ad_id字段的位置
	SG_SHORT GetTaskIDPtr()		{ return m_TaskID_ptr; }	//得到a/d表中taskid字段的位置
	SG_BOOL	ArcGisID_Is_RowID();							//
	
	virtual SG_CHAR * GetSdeSelfKeyFieldName();			//获得自定义主键字段名，对客户端而言只能是KID或Sde的RowID
	virtual void SetSdeSelfKeyFieldName(SG_CHAR*name);	//设置自定义主键字段名
	SG_PSTR GetFieldName(SG_INT ptr);						//字段名
	
    SG_SHORT GetFieldPtr(SG_PCSTR fieldname);				//字段位置
	
    SG_SHORT GetFieldPtr(CSgString &fieldname);				//字段位置
	
    SG_INT GetFieldType(SG_INT ptr);						//字段类型
	
    CSgFieldInfo* GetFieldInfo(SG_INT ptr);				//获得字段结构信息
	
    SG_INT GetFieldLen(SG_INT ptr);							//字段长度
	
    SG_BOOL GetFieldCanBeNull(SG_INT ptr);					//允许为空
	
    SG_BOOL GetFieldPrimary(SG_INT ptr);					//字段为主键
	
    SG_BOOL GetFieldPrimary(SG_CHAR* fieldname);			//字段为主键
	
    SG_INT	GetFieldSqlType(SG_INT fieldptr);				//字段访问数据源的简化类型
	
    SG_BOOL GetUpdateFlag();								//数据集是否可被Update操作
	
    SG_BOOL GetUpdateFlag(SG_INT ptr);						//字段是否可被Update操作
	
    SG_BOOL GetFieldMathType(SG_INT ptr);					//字段是否数值类型
	
	SG_BOOL GetChangeFlag();								//数据集是否可被更改过
	
	SG_BOOL GetChangeFlag(SG_INT ptr);						//字段是否被更新
	
	SG_BOOL GetFieldIsGisID(SG_INT ptr);					//字段为系统的对象ID
	
	SG_BOOL	GetFieldIsArcGisID(SG_INT ptr);					//字段ArcSDE的ObjectID
	//
	
	void RemoveExtField();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	//
	
	CSgTableInfo& operator=(CSgTableInfo&ti);
};

#endif /* CSgTableInfo_h */
