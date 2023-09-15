// chashset.h
//

#if !defined(_HASH_SET_H)
#define _HASH_SET_H

#include "sgdataset.h"
/*
 				Hash表索引类
    概念:	
		键值		-- 创建索引的内值,二进制数
		索引值		-- 键值对应的索引值,二进制数
		键值长度	-- 一个键值二进制数占用内存的长度
		索引值长度	-- 一个索引值二进制数占用内存的长度
		模值		-- 计算hash地址时所用的模数值,无符号整形数
		键索对象	-- 键值索引存储在连续的内存块中,称为键索对象
		Hash地址对象-- 一个hash地址对应的多个键索对象,由多个键索对象组成的结构为hash地址对象
*/


struct _DATASET_DLL_EXPORT_ HashSetData{
	
	SG_SHORT m_KeyValue_Len;	//	键值长度	-- 一个键值二进制数占用内存的长度
	
	SG_SHORT m_IndexValue_Len;	//	索引值长度	-- 一个索引值二进制数占用内存的长度
	
	SG_ULONG m_ModuleValue;		//	模值		-- 计算hash地址时所用的模数值,无符号整形数
	// --- 获得键索对象占用内存的长度
public:
	
	SG_SHORT GetMemSize();
	
	SG_LONG  GetModuleValue();
	
	SG_SHORT GetKeyValue();
	
	SG_SHORT GetIndexValue();
};


class _DATASET_DLL_EXPORT_ CHashSet:public HashSetData
{
public:
	
	CHashSet();
	
	~CHashSet();

	// --- 是否可用
	
	SG_BOOL IsUseAble(){return m_UseAble;}

	//清空索引
	
	void ResetHash(SG_BOOL ReInit=false);
	//初始化 --- 入参数为:键值长度,索引值长度,模值
	
	void InitHash(SG_SHORT KeyValueLen,SG_SHORT IndexValueLen,SG_ULONG Module);
	//创建索引 --	给键值KeyValue创建一个索引值
	//				CheckFlag为检测是否已经具有存在该索引控制变量
	
	SG_BOOL Bind(void* KeyValue,void* IndexValue,SG_BOOL CheckFlag=false);
	//删除绑定
	SG_BOOL UnBind(void* KeyValue,void* IndexValue);
	//获得索引	--	获得键值KeyValue对应的索引值
	SG_BOOL Find(void* KeyValue,void *IndexValue);
	SG_BOOL Find(SG_LONG KeyValue,void *IndexValue);
	SG_BOOL Find(SG_INT64 KeyValue,void *IndexValue);
	//获得索引	--	获得键值KeyValue对应的索引值,将索引值强制转换为整形数
	
	SG_BOOL Finds(void* KeyValue,CSgObjects &rows);
	SG_BOOL Finds(SG_LONG KeyValue,CSgObjects &rows);
	SG_BOOL Finds(SG_INT64 KeyValue,CSgObjects &rows);
	/*
	 *	获得hash地址上聚集的键值内容
	 *	约束：本方法为特定应用，只适合键值为4字节整形数值的情况
	 */
	SG_BOOL GetAddrKeyValue(SG_LONG index,CSgObjects *pArray);

public:
	//创建格式化存储区，并将索引数据导入格式化区
	void	CreateFormatArea();
	//【创建格式化存储区后】优化内存存储，将索引数据导入格式化区
	void	PackMem();
	//获得索引占用的内存
	
	SG_LONG GetMemLen();
	
protected:
	// --- 获得键值的hash索引
	
	SG_ULONG GetHashIndex(void*KeyValue);
	
private:
	//是否已经启用格式化存储
	SG_BOOL	IsUseFormatStore();
	/************************************************************************/
	/*                     键索存放（添加）到格式区                         */
	/*			操作成功后建立地址码返回true，否则返回false不变更地址码		*/
	/************************************************************************/
	SG_BOOL PushToFormatArea0(void *KeyValue,void *IndexValue,struct HashAddressCode&ac);
	/************************************************************************/
	/*				 Hash地址对象存放（添加）到格式化区 	 		        */
	/*			操作成功后建立地址码返回true，否则返回false不变更地址码		*/
	/************************************************************************/
	SG_BOOL PushToFormatArea(SG_INT AreaNo,struct HashAddressObj &ha,struct HashAddressCode&ac);
	/************************************************************************/
	/*		将ac对应的索引内容与新增Key/Index打包转存到新存储区		        */
	/*		操作成功后并将原存储区释放，重新改写ac内容						*/
	/*				否则返回false对系统做任何变更							*/
	/************************************************************************/
	SG_BOOL ChangeToFormatArea(SG_INT AreaNo,struct HashAddressCode&ac,void*KeyValue,void*IndexValue);
	/************************************************************************/
	/*             hash地址对象未建立情况下，键索存放到自由区		        */
	/*			操作成功后建立地址码返回true，否则返回false不变更地址码		*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(void *KeyValue,void *IndexValue,struct HashAddressCode&ac);
	/************************************************************************/
	/*             hash地址对象未建立情况下，键索存放到自由区		        */
	/*			操作成功后建立地址码返回true，否则返回false不变更地址码		*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(struct HashAddressObj &ha,struct HashAddressCode&ac);
	/************************************************************************/
	/*             hash地址对象已经建立情况下，键索存放到自由区		        */
	/*						该处理不变更地址码								*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(SG_INT FreeNo,void *KeyValue,void *IndexValue,SG_BOOL CheckFlag,struct HashAddressCode&ac);
	//检查在ac表达的格式化区是否已经存在键索要素，已存在返回true
	SG_BOOL LocateAtFormatArea(struct HashAddressCode&ac,void *KeyValue,void *IndexValue);
	//从格式化区读取数据复制到hash地址对象
	SG_BOOL FormatDataToAddressObj(struct HashAddressCode&ac,struct HashAddressObj &ha);
	/************************************************************************/
	/*					 释放格式化区内存占用		 		 		        */
	/*			如果格式化区地址上的键索对象为0，释放内存占用				*/
	/************************************************************************/
	SG_BOOL FormatAreaFreeMem(struct HashAddressCode&ac);
	//从格式化区查找
	SG_BOOL FindInFormatArea(SG_INT AreaNo,SG_INT Pos,void*KeyValue,void*IndexValue);
	SG_BOOL FindsInFormatArea(SG_INT AreaNo,SG_INT Pos,void*KeyValue,CSgObjects &rows);
	//地址索引队列
	CSgObjects	*m_pAddrIndex;
	//自由区写指针
	SG_INT	m_FreeAreaWritePtr;
	//格式化存储区队列
	CSgPtrArray	*m_pFormatArray;

private:
	// --- hash地址对象地址队列
	
	CSgPtrArray *m_pHashObjAddress;
	
	SG_BOOL m_UseAble;	//HashSet可用标记
};

#endif /* _HASH_SET_H */
