	// csgdataset.h
//

#if !defined(CSgDataSet_h)
#define CSgDataSet_h


#include "nt_unix/sgdataset.h"
#include "nt_unix/sgmicro.h"

#include "nt_unix/csgtableinfo.h"
#include "nt_unix/sgfieldsfilter.h"
#include "nt_unix/cvarcharcontainer.h"
#include "nt_unix/chashdataset.h"
#include "nt_unix/objlockman.h"
#include "nt_unix/sgnp/NetCommand.h"

#ifdef WIN32
#pragma   warning   (disable:   4083   4786)   
#include <set>
#else
#include <set>
#endif

//#ifndef NOT_AUTOLINK
//#if defined(_MSC_VER) && !defined(_USE_CPP_) && !defined(_DATASET_DLL_) && !defined(GDB_SRV)
//#	ifdef _LIB
//#		ifdef _DEBUG
//#			pragma comment(lib , "SgDataSetSD.lib" )
//#		else
//#			pragma comment(lib , "SgDataSetS.lib" )
//#		endif
//#	else
//#		ifdef _DEBUG
//#			pragma comment(lib , "SgDataSetD.lib" )
//#		else
//#			pragma comment(lib , "SgDataSet.lib" )
//#		endif
//#	endif
//#endif /* _MSC_VER */
//#endif
enum SG_DATASET_TYPE
{
	SG_DATASET_TYPE_NORMAL	=	0,
	SG_DATASET_TYPE_GEO		=	1,
	SG_DATASET_TYPE_LOB	=	2,

};

/*
 * 数据访问后的记录集；
 */
class CSgArchive;
class CHashDataSet;
struct HashSetAndFields;

class RecordBase
{
public:

	RecordBase(CVarCharContainer*&pVarChars)
		:m_pVarChars(pVarChars)
	{
		m_pStart =NULL;
		m_pTableInfo =NULL;
	}

	SG_BOOL SetRecordPointer(CSgTableInfo*pTableInfo,char *p)
	{
		if(!p) return false;
		m_pStart = p;
		m_pTableInfo = pTableInfo;
		return true;
	}

public:
	//
	template <class MATHTYPE>
	SG_BOOL	SetAt(SG_SHORT col,MATHTYPE*msg)
	{
		if(col <0) return false;

		char * ptemp = m_pStart;
		if(col>0) ptemp += m_pTableInfo->GetColConPtr(col-1);

		switch(m_pTableInfo->GetFieldType(col))	
		{ 
		case SG_FIELDTYPE_BIT: 
		case SG_FIELDTYPE_TINYINT: 
			{ 
				SG_UCHAR value = (SG_UCHAR)(*msg);
				memcpy(ptemp,&value,sizeof(SG_UCHAR));	
			} 
			break;
		case SG_FIELDTYPE_SMALLINT: 
			{ 
				SG_SHORT value = (SG_SHORT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_SHORT));	
			} 
			break; 
		case SG_FIELDTYPE_USHORT:
		case SG_FIELDTYPE_BINARY:
			{ 
				SG_USHORT value = (SG_USHORT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_USHORT));
			}
			break;
		case SG_FIELDTYPE_INT:
		case SG_FIELDTYPE_LONG:
			{ 
				SG_INT value = (SG_INT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_INT));
			} 
			break; 
		case SG_FIELDTYPE_INT64:
			{ 
				SG_INT64 value = (SG_INT64)(*msg);
				memcpy(ptemp,&value,sizeof(SG_INT64));
			} 
			break; 
		case SG_FIELDTYPE_REAL:
			{ 
				SG_FLOAT value = (SG_FLOAT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_FLOAT));	
			} 
			break; 
		case SG_FIELDTYPE_FLOAT: 
			{ 
				SG_DOUBLE value = (SG_DOUBLE)(*msg);
				memcpy(ptemp,&value,sizeof(SG_DOUBLE));	
			} 
			break; 
		default: 
			return false; 
		} 
		return true;
	}

	SG_BOOL	SetAt(SG_SHORT col,const SG_CHAR*);
	SG_BOOL SetAt(SG_SHORT col,void *p,SG_UINT len);

	template <class MATHTYPE>
	SG_BOOL	GetAt(SG_SHORT col,MATHTYPE*msg)
	{
		if(col <0) return false;

		char * ptemp = m_pStart;
		if(col>0) ptemp += m_pTableInfo->GetColConPtr(col-1);

		switch(m_pTableInfo->GetFieldType(col))
		{
		case SG_FIELDTYPE_BIT:
		case SG_FIELDTYPE_TINYINT:
			{ 
				unsigned char p; 
				p = *(unsigned char *)ptemp;
				*msg = (MATHTYPE)p; 
			} 
			break;
		case SG_FIELDTYPE_SMALLINT: 
			{ 
				SG_SHORT p; 
				memcpy(&p,ptemp,sizeof(SG_SHORT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_USHORT: 
		case SG_FIELDTYPE_BINARY: 
			{ 
				SG_USHORT p; 
				memcpy(&p,ptemp,sizeof(SG_USHORT)); 
				*msg = (MATHTYPE)p; 
			} 
			break;
		case SG_FIELDTYPE_INT: 
		case SG_FIELDTYPE_LONG: 
			{ 
				SG_INT p; 
				memcpy(&p,ptemp,sizeof(SG_INT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_INT64: 
			{ 
				SG_INT64 p; 
				memcpy(&p,ptemp,sizeof(SG_INT64)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_REAL: 
			{ 
				SG_FLOAT p; 
				memcpy(&p,ptemp,sizeof(SG_FLOAT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_FLOAT: 
			{ 
				SG_DOUBLE p; 
				memcpy(&p,ptemp,sizeof(SG_DOUBLE)); 
				*msg = (MATHTYPE)p; 
			} 
			break;
		default: 
			return false; 
		} 
		return true;
	}

    SG_BOOL	GetAt(SG_SHORT col,SG_CHAR*);
	SG_BOOL GetAt(SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_SHORT col,CSgString &msg);

protected:

	void SafeSetChar(SG_CHAR*pAddress,const SG_CHAR*pInStr,SG_INT LimitLen);
	void SafeSetVarChar(VarCharAddress*pAddress,const SG_CHAR*pInStr,SG_INT LimitLen);
	//
protected:
	
	CSgTableInfo*		m_pTableInfo;
	CVarCharContainer*&	m_pVarChars;
	char*				m_pStart;
};

class _DATASET_DLL_EXPORT_ CSgDataSet:public CSgTableInfo,public CHashObjIndex,public CObjLock_RCS,public RefCountNoLock
{
public:
	
    CSgDataSet();
	
    virtual ~CSgDataSet();
	//---获得实例类型
	
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_NORMAL;}
	//创建CSgDataSet实例
	static CSgDataSet* CreateInstance();

public:
	//设置数据集可以容纳的记录数量
	SG_BOOL SetRecordSize(SG_UINT size);
	SG_UINT	GetRecordSize(){ return m_RecordSize; }
	//紧缩内存，保持KeepRecordNums个记录的存储空间
	//声明：为应用处提高效率，该方法不考虑数据集索引的处理
	virtual	SG_BOOL	PackMemSize(SG_UINT KeepRecordNums);
	//设置记录数量
	
    virtual SG_BOOL SetRecordNums(SG_UINT nums);
	//设置记录数量 --- 智能反对数关系增加记录
	
	SG_BOOL AutoAddReacorNums(SG_INT*pAddNums=0);
	/*
	 *	差异校对方法
	 *	入参数:   Pos为变更的内存库行；DataSet为存储新内容的数据集；row为新内容对应的在pDataSet中的行号
	 *  处理过程: ModiAttrib的初始化在调用处进行，Check的过程只置位不清除
	 *  返回值：  差异的总结信息在ModiAttrib中，域的changeflag位标识差异明细
	 *  优化性能方法：循环处理时，在调用处循环外声明一个CSgObjects变量，作为Index参数用来缓存两个数据集的结构对应信息
	 */
	SG_BOOL CheckChangeFlag(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*Index=NULL);
	SG_BOOL CheckChangeFlag(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*pFields1,CSgObjects*pFields2);
	/*
	 *	差异校对方法，在明确两个数据集结构完全一致的情况下调用
	 */
	SG_BOOL CheckChangeFlag_Same(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib);
    /*
     * 创建数据插入标准SQL语句
     */
	
    SG_CHAR* CreateInsertStr(SG_UINT recno, SG_CHAR * tablename);
    /*
     * 创建数据更改标准SQL语句，
	 当入参数pwhere不为空，返回的Sql语句用入参数的子句作为条件
		否则：如果应用处已知主键域（或特殊控制）KeyWord不为空，返回的Sql语句用入参数的KeyWord域做条件
			否则：用数据集自身的主键做条件
	主键不允许修改
     */
	
    SG_CHAR* CreateUpdateStr(SG_UINT recno, SG_CHAR* KeyWord, SG_CHAR* tablename, SG_CHAR* pwhere);
    /*
     * 创建数据选择标准SQL语句 select fieldname from tab
     */
	
    SG_CHAR * CreateSelectStr(SG_CHAR * tablename);
	//

	// --- 清空(释放)内容
	
	void Reset();
	// --- 释放VarChar占用内存
	
	void ReleaseVarChar(SG_UINT start,SG_UINT nums);
	// --- 紧缩表
	
	void Pack();
	/*复制表信息,记录数置为0
	  入参数:FullDataSetFlag是SgGIS中的特定用法,其BaseAttrib类中的
			m_pGeoDataSet是由SDE中的属性结构和标注字段属性组合而成,当标记为false时只获得SDE属性表信息
	*/
	
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,SG_BOOL FullDataSetFlag=true);
	//UseSrcTblOrder=true  生成的记录集的字段顺序和源表相同,否则按selfields的顺序
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,CSgObjects &selfields,SG_BOOL UseSrcTblOrder=true);
	/*
		复制start起 nums 条记录的数据集
		start>=记录数 或 nums<1 只复制表信息
	*/
	
	virtual void CopyDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,CSgObjects &rows);
	
	/*
	  复制扩展表信息,记录数置为0
	*/
	
	void CopyExtTableInfo(CSgDataSet &srcDataSet);
	
	void SetExtFieldAttrib(SG_BOOL Flag);
	/*
		复制start起 nums 条记录的扩展属性数据集
		start>=记录数 或 nums<1 只复制表信息
	*/
	
	void CopyExtDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);

	//复制整个DataSet
	
	void operator=(CSgDataSet &srcDataSet);
	//比较数据集pDataSet与本数据集的关系
	//	=0不一样 =1完全一致 =2本数据集包含pDataSet =3pDataSet包含本数据集
	
	SG_UCHAR CompareTableInfo(CSgDataSet *pDataSet);

	//比较本数据集的表结构是否包含数据集pDataSet,忽略字段的顺序和ID字段
	//	=0不一样 =1完全一致 =2本数据集包含pDataSet =3pDataSet包含本数据集
	
	SG_UCHAR CompareTableInfoIgnoreOrder(CSgDataSet *pDataSet);

	//如果pRow=NULL，则序列化整个记录集,否则只序列化pRow中所指行号对应的记录
	//表结构信息只复制一份
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	//反序列化记录（属性数据）
	
	SG_BOOL SerializeRecord(CSgArchive&ar,SG_INT row);
	//纯基表的序列化
	
	SG_BOOL BaseClassSerialize(CSgArchive&ar,CSgObjects*objs=NULL){
		return CSgDataSet::Serialize(ar,objs);
	}

	SG_BOOL Sort(CSgString &strFields,bool asc=true);

public:

	SG_BOOL SetAt(SG_INT row,SG_SHORT col,SG_UCHAR*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_SHORT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_USHORT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_INT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_UINT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_INT64*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_UINT64*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_DOUBLE*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_FLOAT*msg);

	//存储方法开始--用行号/列号
    SG_BOOL	SetAt(SG_INT row,SG_SHORT col,const char*);
	SG_BOOL SetAt(SG_INT row,SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL SetAt(SG_INT row,SG_CHAR *col,void *p,SG_UINT len);

	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UCHAR*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_SHORT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_USHORT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_INT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UINT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_INT64*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UINT64*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_DOUBLE*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_FLOAT*msg);

	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_CHAR *);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_INT row,SG_CHAR *col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,CSgString &msg);

	SG_BOOL Get(SG_INT row,SG_CHAR *fieldname,CSgString &msg);
	//获得字段内容，当被删除时允许获得
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_CHAR*msg);
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_UCHAR &msg);
	SG_BOOL SetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_UCHAR &msg);
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_LONG &msg);
	SG_BOOL SetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_LONG &msg);
	
	//读取方法开始--用行号/字段名	
	template <class T>
	SG_BOOL Get(SG_INT row,SG_PCSTR fieldname,T *con)	
	{															
		SG_INT col = GetFieldPtr(fieldname);					
		if(col<0)return false;									
		return GetAt(row,col,con);								
	}		
	//获得记录首地址
	//SG_CHAR *GetRecordHeadPos(SG_UINT row);
	//获得数据区首地址
	//const SG_CHAR* GetContent();
	
public:
	//SgGIS对象内控属性处理
	//设置"对象类型"控制属性
	
	void SetControlAttrib(ObjType_IA_Cfg_Struct type);
	//获得"对象类型"控制属性
	
	inline ObjType_IA_Cfg_Struct *GetControlAttrib(){return &m_ObjControlAttrib;}
	//设置记录是否可用
	
	void SetRecordUseAble(const SG_UINT row,SG_BOOL flag);
	//获得记录是否可用
	
	SG_BOOL GetRecordUseAble(const SG_UINT row);
	//内控属性
	
	void SetInsideAttrib(const SG_UINT TargerRow,const SG_UINT SourceRow);
	//设置"对象实例"控制属性
	
	void SetControlAttrib(const SG_UINT row,ObjAttribStruct_Base *p);
	//获得"对象实例"控制属性
	
	ObjAttribStruct_Base *GetControlAttrib(const SG_UINT row);
	
	ObjAttribStruct_Ext *GetControlAttribExt(const SG_UINT row);
	/*维护用专用方法*/
	//设置对象为容器内对象 如果具有FLAG域，其Inside位置为flag的内值
	
	void SetObjInside(SG_INT row,SG_BOOL flag);
	//将FLAG字段中的前几个数据库属性位导入 inside 属性
	
	void ValueToInside(SG_INT row);
	//将FLAG字段中的前几个数据库属性位导入 inside 属性
	//---置位UseItFlag
	
	void ValueToInside(SG_INT row,SG_SHORT col);
	//将内控结构中的状态值写入Flag内存字段
	
	void InsideStatusToFlag();
	//获得起始拓扑端子
	
	SG_NODEINT GetFNode(SG_INT row);
	//获得终止拓扑端子
	
	SG_NODEINT GetTNode(SG_INT row);
	// --- 将具有不唯一内容的记录选出放入dataset
	// 入参:Fields为处理的字段
	// --- 注意:该方法中将几何属性强制置为SG_B_Feature_NULL
	
	void GetDupContent(CSgObjects&Fields,CSgDataSet&dataset);

	// --- 安全处理
	// --- 检测Flag特殊字段的内值
	
	void SafeFlagField(SG_INT row);

	//构建控制属性——系统特定处理 --- BackLen为需要保留原来扩展属性值的记录数
	
	void BuildControlAttrib(SG_UINT BackLen);

public:
	/*********************************************************
			SgGIS 扩展应用----具有一定的数据集的功能
	*********************************************************/
	//获得匹配记录的行号,条件字段为整形,条件值为整形,返回第一个匹配的记录,-1为没有找到
	//		startpos 检索的起始行号,缺省值为0
	//该方法可以定位排序后的数据集中出现某一数值的起始位置.
	
	SG_LONG GetFetchRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);

	SG_BOOL GetFetchRows(SG_USHORT fieldpos,SG_LONG fieldvalue,CSgObjects&RetRows);

	//获得和指定域相等的记录内容，如果有索引，按索引查找，否则用GetFetchRow获得行号
	SG_LONG GetMatchingRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);

	SG_BOOL GetMatchingRows(SG_USHORT fieldpos,SG_LONG fieldvalue,CSgObjects&RetRows);

	//获得匹配记录的行号,条件字段为字符串类型,条件值字符串,返回第一个匹配的记录,-1为没有找到
	//		startpos 检索的起始行号,缺省值为0
	//该方法可以定位排序后的数据集中出现某一数值的起始位置.
	
	SG_LONG GetFetchRow(SG_USHORT fieldpos,SG_CHAR* fieldvalue,SG_LONG startpos=0);
	//多个字段定位，字段与值一一对应
	SG_LONG GetFetchRow(CSgObjects&FieldPos,CSgObjects&FieldVal,SG_LONG startpos=0);
	//获得不匹配记录的行号,条件字段为整形,条件值为整形,返回第一个不匹配的记录,-1为没有找到
	//		startpos 检索的起始行号,缺省值为0
	//该方法可以定位排序后的数据集中出现另一数值的起始位置.
	
	SG_LONG GetNotFetchRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);
	//设置生成该数据集的Where子句
	
	void SetWhereWord(const char *word){m_WhereWord=word;}
	
	CSgString& GetWhereWord(){return m_WhereWord; }
	//扩展属性域信息,无条件增加AddFieldNums个域,将追加域置为外属性(ExtAttribFlag=true)
	
	virtual void ExtendFieldInfo(SG_INT AddFieldNums,CSgFieldInfo *dtfmt);
	//设置对象长度 --- 系统级描述
	
	void SetObjLen(SG_INT row,SG_DOUBLE len);
	//根据对象的ID获得对象的行号 --- SafeCheck参数决定在通过索引无法获得行号后是否遍历所有记录
	
	SG_LONG GetObjRow(SG_LONG oid,SG_INT startrow=-1,SG_BOOL SafeCheck=true);
	//
	
	SG_BOOL GetObjRows(SG_LONG oid,SG_SHORT fieldPtr,CSgObjects&rows,SG_BOOL SafeCheck=true);

	//根据对象的KID获得对象的行号
	SG_LONG GetArcGisObjRow(SG_LONG kid,SG_INT startrow=-1,SG_BOOL SafeCheck=true);
	//判断两个记录集中的拓扑端子字段的内容是否一致
	
	SG_BOOL TopNodeSame(SG_LONG row1,CSgDataSet*pDataSet2,SG_LONG row2);
	//判断两个记录集中的GisID字段的内容是否一致
	
	SG_BOOL GisIDSame(SG_LONG row1,CSgDataSet*pDataSet2,SG_LONG row2);
	/*
	 *  功能：	  增加记录，同步维护索引                                    
	 *	使用范围：客户端、服务端、PubServer都应用该方法切处理方式都完全一致
	 *  返回值：新增对象后的行号
	 */
	SG_LONG PostAdd(CSgDataSet*pSrcDataSet,SG_LONG SrcRow);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：表结构可能不完全一致，同名字段进行修改
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void UpdateUseName(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：表结构需要完全一致
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void Update_Same(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：toSrcFieldPtr放置当前数据集中字段到源数据集中字段的对应关系
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void Update_FieldIndex(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&toSrcFieldPtr,SG_BOOL MaintIndex=false,SG_BOOL ClearNoExistFieldFlag=true);
	//用srcPtrArray中指定的字段更新目标DATASET在destPtrArray中指定的字段
	virtual void Update_FieldIndex2(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&srcPtrArray,CSgObjects&destPtrArray,SG_BOOL MaintIndex=false);
	
	//合并返回的数据集,如果pPrimaryKeyField!=NULL 主键冲突的不能进行合并
	SG_INT UniteDataSet(CSgDataSet &SrcDatSet,CSgString *pPrimaryKeyField=NULL);
	//
	//追加数据集,两个数据集要求结构完全相同
	virtual SG_INT AppendDataSet(CSgDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	/*
	 *  功能：	  删除记录，同步维护索引                                    
	 *	使用范围：客户端、服务端、PubServer都应用该方法切处理方式都完全一致 
	 */
	void PostDelete(SG_LONG row);
		
	//根据条件语句取得数据集的全字段子集
	//返回结果为行号
	
	void GetSubDataSet(SG_STRING whereClause,CSgObjects &rows,SG_LONG startRow=0,SG_LONG endRow=-1);
	//根据条件语句取得数据集的部分字段子集
	//pRtnDataSet为返回结果的数据集调用处构类实例,Fields为要选择的字段用","分开,其它参数同"全字段子集"方法
	
	void GetSubDataSet(CSgDataSet*pRtnDataSet,SG_PCSTR Fields,SG_STRING whereClause,CSgObjects &rows);
	//根据条件语句取得数据集的部分字段子集
	//Fields为要选择的字段位置,其它参数同上
	
	virtual void GetSubDataSet(CSgDataSet*pRtnDataSet,CSgObjects&Fields,SG_STRING whereClause,CSgObjects &rows);
	
	//根据索引字段的位置和值，获取符合条件的记录号
	void GetSubDataSet(int idxfieldptr,int val,CSgObjects &rows,unsigned char crt_idxflag=false);
	void GetSubDataSet(CSgObjects &IdxFields,CSgObjects &IntVals,CSgObjects &RetRows,unsigned char CrtIdxFlag=false);
	SG_BOOL GetRecordKeyFilter(int nRow,char*pSzKeyWhere,CSgStringArray&FieldArray);
	void PrintTblInfo(FILE *pFile=NULL);	

protected:
	//根据单个条件取得数据集的子集
	//入参数:SelFlag为选中标记数组,relation表征逻辑与或关系
	
	void GetSubSetByFilter(CSgFieldFilter*pSimpleFilter,CSgObjects &SelFlag,FIELD_CON_RELATION relation,SG_LONG startRow=0,SG_LONG endRow=-1);
	/*  比较两个数据集合中的内容是否一致
	*   Index=NULL时表示结构一致；否则Index中存储着从当前数据集字段到pDataSet字段的索引
	 *	返回值：0－无变化；1－存在差异
	 */
	SG_BOOL CompareContent(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*Index=NULL);
	SG_BOOL CompareField(SG_INT row1,SG_INT field1,CSgDataSet *pDataSet2,SG_INT row2,SG_INT field2,SG_MODI_MESSAGE &ModiAttrib);
	SG_UCHAR *GetRecordPointer(int row);

public:
	/*
	 *	*******索引相关实现*******
	 */
	//获得索引绑定对象的表头信息
	virtual CSgTableInfo*GetTableInfo();
	//获得数据集在 第row行 基于索引 IndexField的键值
	virtual void *GetKeyValue(HashSetAndFields*p,SG_LONG row);
	//获得数据集在 第row行 基于索引 IndexField的键值文本信息
	virtual SG_BOOL GetKeyString(HashSetAndFields*p,SG_LONG row,SG_CHAR*pInfo);
	//获得数据集记录数量
	virtual	SG_UINT GetObjNums();
		
	//获得索引占用的内存
	
	virtual void GetMemLen(MemUseCheck&mc);
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	// --- 获得表的信息描述
	
	void GetTableInfoDescrib(CSgString &msg,SG_INT No);

	// --- 打印记录集中第row行内容
	
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
	//跟踪对row行记录的读写
	
	void SetDebugRow(SG_LONG row);
#ifdef LOCALLIB_RECORD_CHECK
	//查看Row行信息
	
	void DebugRow(SG_LONG row,SG_SHORT Col=0);
#endif

	//慎用
	virtual SG_CHAR *GetColumnHeadPos(SG_INT row,SG_SHORT col);
	virtual SG_CHAR *GetContent() { return m_pContent;}
	//
protected:

	virtual SG_BOOL SetRecordPointer(RecordBase& rb,int row,SG_SHORT& col,bool );
	//获得记录列首地址
	
	

protected:
	//对象的内控属性
	class CControlAttribMan*m_pInsideContrlAttrib;
	//---DataSet占用的传输长度
	
	SG_ULONG	m_DataSetLen;
	//
	//RecordBase* m_pRecordBase;

#ifdef LOCALLIB_RECORD_CHECK
	
	static SG_OBJECT m_RecordCheck;
#endif

	
    SG_BOOL CheckSafeRowCol(SG_UINT row, SG_USHORT col);

	
    SG_CHAR *	m_pContent;
#ifdef USE_UNIQUE_VARCHARCONTAINER
	
	static CVarCharContainer*m_pVarChars;
#else
	CVarCharContainer*m_pVarChars;
#endif

};


class _DATASET_DLL_EXPORT_ CDataSetLockMan
{
public:
	
	CDataSetLockMan(CSgDataSet*p,SG_BOOL ReadLock=true);
	
	~CDataSetLockMan();
protected:
	
	CSgDataSet*pDataSet;
};

//////////////////////////////////////////////////////////////////////////
//

class _DATASET_DLL_EXPORT_ GeoDataMan
{
public:
	
	GeoDataMan(){}
	
	virtual ~GeoDataMan(){};
	virtual SG_BOOL	CheckGeoChange(SG_UINT ptr,void *p)=0;
	virtual SG_BOOL SetGeometry(SG_UINT ptr,void*p)=0;
	
	virtual SG_BOOL SetGeometry(SG_UINT ptr,void*p,SG_BOOL &ChangeFlag)=0;
	
	virtual SG_BOOL IsNull()=0;
	
	virtual void Copy(GeoDataMan*pGeoData,SG_UINT size)=0;
	
	virtual void Serialize(CSgArchive&,SG_UINT size)=0;

	virtual void AppendData(CSgArchive&,SG_INT StartRow,SG_UINT ObjNum)=0;
	
	virtual void Serialize(CSgArchive&,SG_UINT size,CSgObjects*objs)=0;
	
	virtual SG_INT GetMemLen(SG_UINT size)=0;
	
	virtual void * GetGeometry(SG_UINT ptr)=0;
	
//	virtual SG_LONG FromShape(SG_UINT row,void*shape)=0;
	
//	virtual SG_LONG ToShape(SG_UINT row,void*shape,SG_UCHAR ft)=0;
	
	virtual void * GetInnerPtr()=0;
	
	virtual SG_BOOL Is3DGeo()=0;
	
	virtual SG_BOOL IsLine()=0;
};
//

template <typename TGeoClass>
class _DATASET_DLL_EXPORT_ GeoDataManT:public GeoDataMan
{
public:
	
	GeoDataManT(SG_UINT size){
		m_pGeoData = new TGeoClass [size];
	}
	
	virtual ~GeoDataManT(){
		if(m_pGeoData){
			delete [] m_pGeoData;
			m_pGeoData =NULL;
		}
	}
	
	SG_BOOL IsNull(){
		return !m_pGeoData;
	}
	SG_BOOL	CheckGeoChange(SG_UINT ptr,void *p)
	{
		if(!m_pGeoData) return false;
		return !(m_pGeoData[ptr]==*((TGeoClass*)p));
	}
	
	SG_BOOL SetGeometry(SG_UINT ptr,void *p){
		if(!m_pGeoData) return false;
		m_pGeoData[ptr]=*(TGeoClass*)p;
		return true;
	}
	
	SG_BOOL SetGeometry(SG_UINT ptr,void *p,SG_BOOL &ChangeFlag){
		if(!m_pGeoData) return false;
		if(m_pGeoData[ptr]==*((TGeoClass*)p)) return true;
		m_pGeoData[ptr]=*(TGeoClass*)p;
		ChangeFlag = true;
		return true;
	}
	
	void * GetGeometry(SG_UINT ptr){
		return &m_pGeoData[ptr];
	}
	
	void Copy(GeoDataMan*pGeoDataMan,SG_UINT size)
	{
		if(m_pGeoData&&pGeoDataMan){
			TGeoClass * p = (TGeoClass*)pGeoDataMan->GetInnerPtr();
			memcpy(m_pGeoData,p,sizeof(TGeoClass)*size);
			for(SG_UINT i=0;i<size;i++){
				p[i].SetMemPtrNull();
			}
		}
	}
	
	void Serialize(CSgArchive&ar,SG_UINT size)
	{
		for(SG_UINT i=0;i<size;i++)
			m_pGeoData[i].Serialize(ar);
	}
	void AppendData(CSgArchive &ar,SG_INT StartRow,SG_UINT ObjNum)
	{
		if(!ar.IsLoading())
			return;
		for(SG_UINT i=StartRow;i<StartRow+ObjNum;i++)
			m_pGeoData[i].Serialize(ar);
	};	
	void Serialize(CSgArchive&ar,SG_UINT size,CSgObjects *objs)
	{
		for(SG_UINT i=0;i<objs->ObjNums;i++){
			if(objs->pObj[i]>=size)continue;
			m_pGeoData[objs->pObj[i]].Serialize(ar);
		}
	}

	
	SG_INT GetMemLen(SG_UINT size)
	{
		SG_INT len=0;
		for(SG_UINT i=0;i<size;i++){
			len += m_pGeoData[i].GetStructLen();
		}
		return len;
	}
	//
/*	
	SG_LONG FromShape(SG_UINT row,void*shape){

		return m_pGeoData[row].FromShape(shape);
	}
	
	SG_LONG ToShape(SG_UINT row,void*shape,SG_UCHAR ft){
		return m_pGeoData[row].ToShape(shape,ft);
	}
*/
	
	void * GetInnerPtr(){
		return m_pGeoData;
	}
	
	SG_BOOL Is3DGeo(){
		return TGeoClass::Has3D();
	}
	
	SG_BOOL IsLine(){
		return TGeoClass::IsLine();
	}
protected:
	
	TGeoClass	* m_pGeoData;
};
class CSgDataSetArray_ObjOper;
class _DATASET_DLL_EXPORT_ CSgGeoDataSet:public CSgDataSet
{
public:
	
	//创建CSgGeoDataSet实例
	static CSgGeoDataSet* CreateInstance();

	CSgGeoDataSet();
	virtual ~CSgGeoDataSet();

	//---获得实例类型
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_GEO;}

	//记录row是否加载
	virtual SG_BOOL IsLoad(int row){ return true;}
	//
public:
	//获得对象的几何属性字段名－－对ArcSDE或其它商用空间引擎类数据源有效
	SG_PSTR	GetGeoFieldName(){return m_geoFieldName.GetSafeBuffer();}
	//设置几何字段名
	void		SetGeoFieldName(SG_PCSTR pFieldName){ m_geoFieldName = pFieldName; }
	//紧缩内存，保持KeepRecordNums个记录的存储空间
	SG_BOOL	PackMemSize(SG_UINT KeepRecordNums);
	//设置对象的数量
	
	virtual SG_BOOL		SetRecordNums(SG_UINT);
	//是否具有几何属性
	virtual SG_BOOL		HasGeometry();
	//删除几何属性
	virtual void		DeleteGeometry();
	//校验几何属性是否变更
    virtual SG_BOOL	CheckGeoChange(SG_UINT ptr,void *pGeoMetry);
	//设置对象的几何属性
	virtual SG_BOOL	SetGeometry(SG_UINT ptr,void*p);
	//设置对象的几何属性 --- ChangeFlag参数返回是否变化
	virtual SG_BOOL	SetGeometry(SG_UINT ptr,void*p,SG_BOOL &ChangeFlag);
	//获得对象的几何属性
	virtual void *	GetGeometry(SG_UINT ptr);
	//获得不可用设备的几何属性
	virtual void *	GetGeometry_IgnoreDel(SG_UINT ptr);
	//比较几何数据是否相等
	virtual SG_BOOL CompareGeometry(int row1,CSgGeoDataSet *pDataSet,int row2);
	//获得记录几何属性的第一个点，如果PointNums不为空返回点数量
	SgPoint*GetRefPoint(SG_INT row,SG_INT*PointNums=NULL);
	//获取几何属性的字符串
	
	SG_CHAR* GetGeometry_str(SG_UINT row,SG_INT&len,SG_CHAR*pCoords=0);
	//获得reference
	
	virtual void GetCoordRefExtent(SgRect&rc){return;}
	//(新)设备几何属性正确性判断
	
	SG_BOOL IsObjInRefRange(void *pGeoMetry){return true;}
	//如果pRow=NULL，则序列化整个记录集,否则只序列化pRow中所指行号对应的记录
	//表结构信息只复制一份
	//除属性数据外，还包括几何数据
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,SG_BOOL FullDataSetFlag=true);
	//UseSrcTblOrder=true  生成的记录集的字段顺序和源表相同,否则按selfields的顺序
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,CSgObjects &selfields,SG_BOOL UseSrcTblOrder=true);
	//判断一条记录是否在数据集中(注：表结构必须一致)
	//SG_BOOL IsObjIn(CSgGeoDataSet *pDataSet,SG_UINT row);
	//根据条件语句取得数据集的部分字段子集
	//Fields为要选择的字段位置,其它参数同上
	
	void GetSubDataSet(CSgGeoDataSet*pRtnDataSet,CSgObjects&Fields,SG_CHAR* whereClause,CSgObjects &rows);
	//GEODATASET中的几何数据是3D或2D
	virtual SG_BOOL Is3DGeo();
	virtual SG_BOOL IsLine();
	//
	void Change3D_2D();	
	void Change2D_3D();
	//
	//追加数据集,两个数据集要求结构完全相同
	virtual SG_INT AppendDataSet(CSgGeoDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,CSgObjects &rows);
public:
	//SgGIS 用特殊处理
	/*
		将 pAddDataSet 增加到数据集中
		只能处理两个数据集结构完全一致的情况,切必须具有整形唯一主键的字段
		KeyFiledPos整形唯一主键的字段位置--作为校验用
		处理的规则为:检索是否具有同一记录,如果有,以pAddDataSet中的为准
	*/
	
	SG_BOOL Add(CSgGeoDataSet *pAddDataSet,SG_UINT KeyFiledPos);
	/*
		功能：将pExtDataSet聚合到数据集中，域的ExtAttribFlag属性置位
		约束：当前数据集与pExtDataSet标识为主键的字段名称必须同名，并且为整数字段
		入参数：KeyFiledPos为pExtDataSet的主键字段位置
		处理规则:不符合约束时，并不做任何处理，返回错误
				如果pExtDataSet中的域名数据集中已经存在,置位ExtAttribFlag，检测类型是否匹配，不匹配返回警告信息
				如果需要扩充属性域，在ExtendFieldInfo中置位ExtAttribFlag
	*/
	
	SG_BOOL Combin(CSgDataSet *pExtDataSet,SG_UINT KeyFiledPos,CSgString*WarningInfo=NULL);
    //删除记录行，会维护索引
	int  DeleteRows(std::set<int,std::greater<int> > &delrows);
	int  DeleteRows(CSgObjects &delrows);

	SG_BOOL Is3DGeo_SDE(){ return m_bIs3D_SDE;}
	void Set3DGeo_SDE(SG_BOOL b){m_bIs3D_SDE = b; }
	
public:
//对自定义表有效的方法
	//自定义表中在ID字段后紧跟出现X1、Y1.....Sg、Yn字段认为是定点几何字段
	//获得对象的几何属性的点数量，并将域相应属性自动置为几何字段
	
	SG_INT GetPointNums();
	//将自身字段内容矢量化，前提是具有几何点字段、具有确定的特征类型
	
	void Vector();
	//将几何属性导入自定义表的属性域中
	
	void UnVector();
	//输出调试信息
	
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
	
public:

	//获得reference
	virtual SgRect* GetCoordRef(){return NULL;}
	//	释放扩展数据
	virtual void FreeDynamicRecords( SG_UINT StartPos = 0 , SG_UINT Numbers = INT_MAX );

	//	获得索引占用的内存
	virtual void GetMemLen(MemUseCheck&mc);

protected:

	SG_BOOL		m_bIs3D_SDE;			
	GeoDataMan * m_pGeoDataMan;
	CSgString m_geoFieldName;
};
typedef  CSgGeoDataSet CSgSdeGeoDataSet;

class  CSgLobData_NoFree
{
	SG_INT		m_LobLen;
	SG_INT		m_SpaceLen;
	void		*m_pLobDat;
public:
	CSgLobData_NoFree();
	~CSgLobData_NoFree();
	SG_BOOL Init();
	SG_BOOL Reset(SG_BOOL FreeFlag=true);
	SG_BOOL Append(const SG_CHAR *pContent,SG_INT nPieceLen);
	SG_BOOL SetSpaceLen(int Len);
	void Free();
	int GetLobLen();
	void *GetLobData();
	SG_BOOL  Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_ CSgLobData
{
	SG_INT		m_LobLen;
	SG_INT		m_SpaceLen;
	void		*m_pLobDat;
public:
	CSgLobData();
	~CSgLobData();
	SG_BOOL Init();
	SG_BOOL Reset(SG_BOOL FreeFlag=true);
	SG_BOOL Append(const SG_CHAR *pContent,SG_INT nPieceLen);
	SG_BOOL SetSpaceLen(int Len);
	void Free();
	int GetLobLen();
	void *GetLobData();
	SG_BOOL  Serialize(CSgArchive&ar);
};

#define CSGLOBDATASET_LOBTYPE_DATASET			1
#define CSGLOBDATASET_LOBTYPE_DATASETARRAY		2
class CSgDataSetArray;
class _DATASET_DLL_EXPORT_ CSgLobDataSet:public CSgGeoDataSet
{
public:
	
	//创建CSgLobDataSet实例
	static CSgLobDataSet* CreateInstance();

	CSgLobDataSet();
	virtual ~CSgLobDataSet();
	//---获得实例类型
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_LOB;}

	//记录row是否加载
	virtual SG_BOOL IsLoad(int row){ return true;}
	//
public:
	SG_BOOL HasLobData()
	{
		if(m_pLobDataArray==NULL)
			return false;
		if(m_pLobDataArray->size()<=0)
			return false;
		return true;
	};
	//如果pRow=NULL，则序列化整个记录集,否则只序列化pRow中所指行号对应的记录
	//表结构信息只复制一份
	//除属性数据外，还包括几何数据
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);

	//判断一条记录是否在数据集中(注：表结构必须一致)
	//SG_BOOL IsObjIn(CSgGeoDataSet *pDataSet,SG_UINT row);
	//根据条件语句取得数据集的部分字段子集
	//Fields为要选择的字段位置,其它参数同上	
	void GetSubDataSet(CSgLobDataSet*pRtnDataSet,CSgObjects&Fields,SG_CHAR* whereClause,CSgObjects &rows);

	//获取某行，某列的记录长度
	SG_INT   GetLobLength(int RowNo,int ColNo);
	//获取某行，某列的内存块   pContent:申请好的内存块 LobLen：记录内存pContent的长度
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,void *p,SG_UINT len);
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSet &Dat);
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSetArray &Dat);
	//设置某行某列的记录,如果pContent==NULL,则删除该行该列的记录内容
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,void *p,SG_UINT len);
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSet &Dat);
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSetArray &Dat);
	//分块获取某行某列的数据   StartPt:本次读取的数据块的偏移位置   pContent:申请好的内存块 OnePieceLen：记录内存pContent的长度
	//函数返回值：本次读取的实际字节数，如果为-1，则表明已读取完毕
	SG_INT  GetLobOnePiece(SG_INT RowNo,SG_SHORT ColNo,SG_INT StartPt,void *pContent,SG_INT OnePieceLen);
	//设置某行某列的空间大小
	SG_BOOL SetLobDataSpaceSize(SG_INT RowNo,SG_SHORT ColNo,SG_INT SpaceLen);
	//分块放入某行某类的数据 pContent:本次放入的内存块 OnePieceLen：本次放入的长度
	SG_BOOL SetLobOnePiece(SG_INT RowNo,SG_SHORT ColNo,void *pContent,SG_INT OnePieceLen);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：表结构可能不完全一致，同名字段进行修改
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void UpdateUseName(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：表结构需要完全一致
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void Update_Same(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  功能：	  Update记录【可同步修改索引】
	 *	限制条件：toSrcFieldPtr放置当前数据集中字段到源数据集中字段的对应关系
	 *  入参数：  MaintIndex决定是否同步修改索引
	 */
	virtual void Update_FieldIndex(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&toSrcFieldPtr,SG_BOOL MaintIndex=false,SG_BOOL ClearNoExistFieldFlag=true);
	//用srcPtrArray中指定的字段更新目标DATASET在destPtrArray中指定的字段
	virtual void Update_FieldIndex2(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&srcPtrArray,CSgObjects&destPtrArray,SG_BOOL MaintIndex=false);
	//追加数据集,两个数据集要求结构完全相同
	virtual SG_INT AppendDataSet(CSgDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
private:
	SG_BOOL  Free();
protected:
	typedef std::map<S_TWOINT,CSgLobData_NoFree,CTwoIntLess> MAP_TWOINT_LOBDATA;
	MAP_TWOINT_LOBDATA	*m_pLobDataArray;
};

/************************************
	数据集队列处理类
************************************/
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<CSgDataSet>;
#endif
class _DATASET_DLL_EXPORT_ CSgDataSetArray:public TMyObjectsArray<CSgDataSet>
{
public:
	virtual ~CSgDataSetArray();

	SG_BOOL IsObjExist(SG_PCSTR name,SG_INT *startpos=0);

	CSgDataSet *GetObj(SG_PCSTR name,SG_INT *startpos=0);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

class _DATASET_DLL_EXPORT_ CSgGeoDataSetArray:public CSgDataSetArray
{
public:
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

class _DATASET_DLL_EXPORT_ CSgVerGeoDataSetArray//:public CSgGeoDataSetArray
{
	CSgPtrArray VerIDArray;
	CSgGeoDataSetArray DataSetArray;
public:
	~CSgVerGeoDataSetArray()
	{
		RemoveAll();
	}
	void RemoveAll()
	{
		VerIDArray.RemoveAll();
		DataSetArray.RemoveAll();
	}
	CSgGeoDataSet *GetObj(int verid);
	CSgGeoDataSet *GetAt(int idx);
	int GetAt_VerID(int idx);
	int SetObj(int verid,CSgGeoDataSet *pDatSet);
	void Add(void *p,int verid);
	int GetSize() {return DataSetArray.GetSize();};
	
};

//DataSet在析构时减少计数
class _DATASET_DLL_EXPORT_ CSgDataSetArrayEx:public CSgPtrArray
{
public:
	//
	virtual ~CSgDataSetArrayEx();
	virtual void RemoveAll();
	SG_BOOL IsObjExist(SG_PCSTR name,SG_INT *startpos=0);
	CSgDataSet *GetObj(SG_PCSTR name,SG_INT *startpos=0);
	CSgDataSet *GetDataSetEx(SG_PCSTR name,SG_PCSTR lpszWhere);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
enum SG_OBJ_OPERTYPE
{
	SG_OBJ_OPERTYPE_INSERT			=1,
	SG_OBJ_OPERTYPE_UPDATE			=2,
	SG_OBJ_OPERTYPE_MERGE			=3,
	SG_OBJ_OPERTYPE_DELETE			=4,
	SG_OBJ_OPERTYPE_EXECSQL			=5,
	SG_OBJ_OPERTYPE_CRTTBL			= 6
};
//对象操作数据集队列datasetnums+[opertype+dataset]+[opertype+dataset].....
class _DATASET_DLL_EXPORT_   CSgDataSetArray_ObjOper
{
	typedef struct COperDataSet
	{
		SG_INT m_OperType;
		CSgDataSet *m_pDataSet;
		COperDataSet()
		{
			m_OperType=0;
			m_pDataSet=NULL;
		};
	}CSgOperDataSet;
	typedef std::vector<CSgOperDataSet > VECT_OPERDATASET;
	VECT_OPERDATASET	m_DataSetArray;
public:
	CSgDataSetArray_ObjOper()
	{

	}
	~CSgDataSetArray_ObjOper()
	{
		RemoveAll();
	}
	void RemoveAll();
	SG_INT GetOperType(int no);
	CSgDataSet *GetAt(int no);
	void Add(int OperType,CSgDataSet *p);
	int GetSize();
	int SetAt(int no,int OperType,CSgDataSet *pDatSet,int FreeOldDatFlag=true);
	//如果MallocNewDatSetFlag=false，则清空源数据集
	int CopyDataSetArray(CSgDataSetArray_ObjOper &SrcDatSetArray,int MallocNewDatSetFlag=true);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_   CSgDataSetArray_ObjDBOper
{
	typedef struct CDBOperDataSet
	{
		SG_SHORT m_OperType;
		SG_SHORT m_DBNo;
		CSgDataSet *m_pDataSet;
		CDBOperDataSet()
		{
			m_OperType=0;
			m_DBNo=1;
			m_pDataSet=NULL;
		};
	}CDBOperDataSet;
	typedef std::vector<CDBOperDataSet > VECT_DBOPERDATASET;
	VECT_DBOPERDATASET	m_DataSetArray;
public:
	CSgDataSetArray_ObjDBOper()
	{

	}
	~CSgDataSetArray_ObjDBOper()
	{
		RemoveAll();
	}
	void RemoveAll();
	SG_SHORT GetOperType(int no);
	SG_SHORT GetDBNo(int no);
	void SetDBNo(int no,SG_SHORT DBNo);
	CSgDataSet *GetAt(int no);
	void Add(SG_SHORT DBNo,SG_SHORT OperType,CSgDataSet *p);
	int GetSize();
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_ CDataSetSortFunc
{
public:
	CDataSetSortFunc(CSgDataSet *pDataSet,CSgString &Fields,SG_BOOL Ascend=true);
	CDataSetSortFunc(CSgDataSet *pDataSet,VECT_INT &FieldPtrs,SG_BOOL Ascend=true);
	bool operator()(const int RcdNo1,const int RcdNo2);
private:
	CSgDataSet *m_pDataSet;
	VECT_INT	m_CmpFieldPtr;
	SG_BOOL		m_Ascend;
};


#endif /* CSgDataSet_h */
