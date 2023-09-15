// CHashDataSetBase.h
//

#if !defined(_HASH_DATA_SET_BASE_H)
#define _HASH_DATA_SET_BASE_H

#include "chashset.h"

/*******************************************************************
 				Hash表索引类在数据集中的应用基类
*******************************************************************/
class CSgTableInfo;
class CSgDataSet;
//#ifdef GDB_SRV
class ACE_Thread_Mutex;
//#endif


struct _DATASET_DLL_EXPORT_ HashSetAndFields
{
	
	CSgObjects	fields;			//Hash数据集的字段
	
	CHashSet	hashset;		//hash数据集
	
	SG_BOOL		ClearMemFlag;	//获得键值前是否清空内存
	
	SG_SHORT	MemLen;		//内存长度
	
	SG_CHAR		*pTempMem;	//内存指针
	
	HashSetAndFields();
	
	~HashSetAndFields();
	/**************************************************
						扩充应用方法
	**************************************************/
	//清空键值区域内存
	SG_BOOL	ClearTmpMem();
	/*
	 *	在临时键值存储区域【pTempMem中】创建键值
	 *  注意：fieldptr=在表信息中的位置
	 *  用途：对于DataSet外已知键值，需要获得索引值时，用该方法形成索引查找的键值
	 */
	void CreateKeyValue(CSgTableInfo*pTableInfo,SG_SHORT fieldptr,void*KeyValue);
	void CreateCharKeyVal(CSgTableInfo*pTableInfo,SG_SHORT fieldptr,const char*KeyValue,SG_INT strlen);
};

struct HashObjIndexStruct
{
	HashObjIndexStruct();
	~HashObjIndexStruct();
	// --- 特定索引指针
	HashSetAndFields	*pIDHashSet;
	//在BaseObjType和BaseObjID上的索引
	HashSetAndFields	*pBaseObjHashSet;
	HashSetAndFields	*pArcGisIDHashSet;
	// --- CHashSet集合
	CSgPtrArray			m_HashSets;
};


class _DATASET_DLL_EXPORT_ CHashObjIndex
{
public:
	
	CHashObjIndex();
	
	~CHashObjIndex();

//public:
//	// --- 绑定数据集
//	
//	void BindDataSet(void *pDataSet){}			//绑定数据集

public: 
	/*
	 *	索引注册方法，相关几个方法只进行注册，不创建实际索引
	 */
	//在入参数的字段上“注册索引”
	virtual HashSetAndFields* RegisterIndexOn(CSgObjects &IndexField);
	virtual HashSetAndFields* RegisterIndexOn(const char*szFieldName);
	//在ArcGISID字段上“注册索引”
	HashSetAndFields* RegisterIndexOnArcGisID();
	//在SgGISID字段上“注册索引”
	HashSetAndFields* RegisterIndexOnID();
	//在基础对象类型和基础对象ID字段上“注册索引”
	HashSetAndFields* RegisterIndexOnBaseObj();

	/* 
	 *  创建索引：当指定pHashSet时只给pHashSet“创建索引”
	 *	处理规则：无条件重新创建索引
	 */
	virtual SG_BOOL CreateIndex(HashSetAndFields*pHashSet=NULL);
	/*
	 *	重新创建索引：改变摸值创建索引，当指定pHashSet时只给pHashSet“创建索引”
	 */
	virtual SG_BOOL ReCreateIndex(HashSetAndFields*pHashSet=NULL,SG_INT *pModValue=NULL);
	/*
	 *	删除索引：将索引相关数据内容删除
	 */
	void	DropIndex();
	void	DropIndex(HashSetAndFields*pHashSet);
	
	/*
	 *	注册并创建索引，相关几个方法进行索引注册并创建
	 *  注意：当已经具有索引并且已经建立过索引，直接退出
	 */
	HashSetAndFields* RegisterAndCreateOn(CSgObjects &IndexField);
	HashSetAndFields* RegisterAndCreateOn(const char*szFieldName);
	//在ArcGISID字段上“注册索引”
	HashSetAndFields* RegisterAndCreateOnArcGisID();
	//在SgGISID字段上“注册索引”
	HashSetAndFields* RegisterAndCreateOnID();
	//在基础对象类型和基础对象ID字段上“注册索引”
	HashSetAndFields* RegisterAndCreateOnBaseObj();
	
public:
	//***删除在row行上的索引***
	virtual SG_BOOL DeleteIndexOnRow(SG_LONG row);
	//***在row行上建立索引***
	virtual SG_BOOL CreateIndexOnRow(SG_LONG row);
	//特定应用：获得基础设备类型和基础设备ID的键值
	void MakeKeyValue(SG_OBJECT*pBuffer,SG_SHORT otype,SG_LONG oid);
	
public:
	/*
	 *	 使用方法，获得HashSet的指针，无隐含的“注册”处理
	 */
	//获得IndexField对应的hashset
	virtual HashSetAndFields* GetHashSet(CSgObjects &IndexField);
	virtual HashSetAndFields* GetHashSet(const char*szFieldName);
	//获得ArcGisID对应的hashset
	virtual HashSetAndFields* GetArcGisIdSet();
	//获得GisID对应的hashset
	virtual HashSetAndFields* GetSgGisIdSet();
	//获得基础对象类型和基础对象ID字段上的hashset
	virtual HashSetAndFields* GetBaseObjTypeIDSet();

public:

	CSgPtrArray* GetAllHashSetAndFields(){ return m_pHashIndex?&m_pHashIndex->m_HashSets:NULL;}
	//获得索引占用的内存
	SG_LONG GetIndexMemLen();
	/*
	 *	索引正确性校验【返回值：1正确，0错误】
	 */
	SG_BOOL	IndexCheck(CSgString&ErrorInfo);
	//获得索引当前的模值
	virtual SG_UINT GetCurModVal();
	//获得索引缺省的模值
	//注：当具有多个索引时，返回第一个索引的模值
	virtual SG_UINT GetDefaultModVal();

protected:
	//获得索引绑定对象的表头信息
	virtual CSgTableInfo*GetTableInfo(){return NULL;}
	//获得数据集在 第row行 基于索引 IndexField的键值
	virtual void *GetKeyValue(HashSetAndFields*p,SG_LONG row){return NULL;}
	/*
	 *	获得数据集在 第row行 基于索引 IndexField的键值文本信息
	 *  返回值：1表征正确获得，0表征未正确获得【被删除】
	 */
	virtual SG_BOOL GetKeyString(HashSetAndFields*p,SG_LONG row,SG_CHAR*pInfo){return NULL;}
	//获得对象数量
	virtual SG_UINT GetObjNums(){return 0;}
	
private:
	HashObjIndexStruct*		m_pHashIndex;
};

#endif /* _HASH_DATA_SET_BASE_H */
