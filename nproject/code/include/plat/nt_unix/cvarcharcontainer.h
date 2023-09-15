	// cvarcharcontainer.h
//

#if !defined(CVarCharContainer_h)
#define CVarCharContainer_h

#include "sgdataset.h"

/*
 			VarChar管理类
	CVarCharManager中存放单一长度的字符串:
		m_ObjLen为字符串的长度；m_MemNums为已分配内存可容纳字符串的数量；m_ObjNums为字符串的数量；m_pMem为整块内存
	内存的组织方式为:每个VarChar对象的长度为m_ObjLen+1,对于有效字符串用0结束，对于未分配或已经删除的字符串以非0结束
	|			m_ObjLen			|0
	|-------------------------------|1
	|-------------------------------|1
	所以 CVarCharManager的内存占用为sizeof(CVarCharManager)+4+(m_ObjLen+1)*m_MemNums
*/
// --- VarChar的寻址结构

struct VarCharAddress
{
	
	SG_UINT	high;		// --- 高位表征存放的是CVarCharManager实例的寻址地址
	
	SG_UINT low;		// --- 低位表征存放的是VarChar实例的寻址地址
};

//---变长字符串统计信息

struct VarcharStaticInfo{
	
	SG_INT AllMemLen;		//内存分配
	
	SG_INT ObjsMemLen;		//曾用到的对象占用的内存总量
	
	SG_INT ObjsNums;		//曾用到的总量
	
	SG_INT NullStrNums;		//空字符串的数量
	
	SG_INT CharNums[256];	//使用的字符串数量 CharNums[0]=为空的字符串数量总和
	
	SG_INT IDleNums[256];	//空闲的字符串数量
	
	VarcharStaticInfo(){
		memset(this,0,sizeof(VarcharStaticInfo));
	}
};



class CVarCharManager
{
	friend class CVarCharManagerLockMan;
public:
	
	CVarCharManager(SG_SHORT ObjLen);
	
	~CVarCharManager();
	
public:
	// --- 增加一个字符串
	//入参数：	调用处必须保证pInChar的字符串长度不小于m_ObjLen
	//返回：	字符串的寻址地址
	
	VarCharAddress	AddObj(const SG_CHAR*pInChar);
	// --- 删除一个字符串
	//处理：将对象的结束符号改为不可用（非0），修改写指针
	
	void			DeleteObj(VarCharAddress Addr);
	// --- 替换一个字符串
	//处理：将对象的内容替换为pInChar中的，约束同AddObj
	
	void			ModiObj(VarCharAddress Addr,const SG_CHAR*pInChar);
	//---获得对象内容(读取字符串内容)
	//约束：pOutChar的内存长度必须大于等于字符串的长度＋1
	
	void	GetObj(VarCharAddress Addr,SG_CHAR*pOutChar);
	
	void	GetObj(VarCharAddress Addr,CSgString&msg);
	SG_PCSTR GetObj( VarCharAddress Addr );
	//获得VarChar的信息
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	
public:
	// --- 设置内存增量
	
	void SetStep(SG_SHORT Step){m_Step=Step;}
	// --- 设置对象的容量
	
	SG_BOOL SetSize(SG_INT MemSize);
	// --- 扩展容量按照设定的增量扩展容量
	
	SG_BOOL ExtendSize();
	// --- 紧缩存储(重设步长)
	
	void Pack();

protected:
	// --- 获得对象的内存地址
	//入参数：对象的相对地址
	
	inline SG_CHAR *GetObjMemAddress(SG_INT ObjAddr){
		return m_pMem+(m_ObjLen+1)*ObjAddr;
	}

protected:
	
	SG_INT	m_MemNums;		// --- 内存中可以存放的对象的数量
	
	SG_INT	m_ObjNums;		// --- 占用到的对象数量
	
	SG_INT	m_WritePos;		// --- 写指针
	
	SG_SHORT	m_ObjLen;
	
	SG_SHORT	m_Step;		//
	
	SG_CHAR	*m_pMem;

};

//

class _DATASET_DLL_EXPORT_ CVarCharContainer
{
public:
	
    CVarCharContainer(SG_SHORT LimitLen=SG_MAX_FIELD_WIDTH+1);
	
    ~CVarCharContainer();

	// --- 读取VarChar
	//约束：pOutChar的内存长度必须大于等于字符串的长度＋1
	
	void GetVarchar(VarCharAddress Addr,SG_CHAR*pOutChar);
	void GetVarchar(VarCharAddress Addr,CSgString&msg);
	SG_PCSTR GetVarchar( VarCharAddress Addr );

	// --- 存放VarChar
	//约束：pInChar的内存长度必须大于等于字符串的长度
	
	VarCharAddress SetVarchar(VarCharAddress Addr,const SG_CHAR*pInChar,SG_INT strLength);
	//获得VarChar的信息
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	// --- 紧缩存储(重设步长)
	
	void Pack(SG_SHORT Step=10);

protected:
	// --- 字符串队列
	CSgPtrArray m_VarcharArray;

	// --- 限制长度
	SG_SHORT	m_LimitLen;

#ifdef USE_UNIQUE_VARCHARCONTAINER
private:
	static	CVarCharContainer*m_pInstance;

public:
	static	CVarCharContainer* GetInstance();
	static  void  FreeInstance();
#endif
};

#endif
