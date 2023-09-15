	// cvarcharcontainer.h
//

#if !defined(CVarCharContainer_h)
#define CVarCharContainer_h

#include "sgdataset.h"

/*
 			VarChar������
	CVarCharManager�д�ŵ�һ���ȵ��ַ���:
		m_ObjLenΪ�ַ����ĳ��ȣ�m_MemNumsΪ�ѷ����ڴ�������ַ�����������m_ObjNumsΪ�ַ�����������m_pMemΪ�����ڴ�
	�ڴ����֯��ʽΪ:ÿ��VarChar����ĳ���Ϊm_ObjLen+1,������Ч�ַ�����0����������δ������Ѿ�ɾ�����ַ����Է�0����
	|			m_ObjLen			|0
	|-------------------------------|1
	|-------------------------------|1
	���� CVarCharManager���ڴ�ռ��Ϊsizeof(CVarCharManager)+4+(m_ObjLen+1)*m_MemNums
*/
// --- VarChar��Ѱַ�ṹ

struct VarCharAddress
{
	
	SG_UINT	high;		// --- ��λ������ŵ���CVarCharManagerʵ����Ѱַ��ַ
	
	SG_UINT low;		// --- ��λ������ŵ���VarCharʵ����Ѱַ��ַ
};

//---�䳤�ַ���ͳ����Ϣ

struct VarcharStaticInfo{
	
	SG_INT AllMemLen;		//�ڴ����
	
	SG_INT ObjsMemLen;		//���õ��Ķ���ռ�õ��ڴ�����
	
	SG_INT ObjsNums;		//���õ�������
	
	SG_INT NullStrNums;		//���ַ���������
	
	SG_INT CharNums[256];	//ʹ�õ��ַ������� CharNums[0]=Ϊ�յ��ַ��������ܺ�
	
	SG_INT IDleNums[256];	//���е��ַ�������
	
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
	// --- ����һ���ַ���
	//�������	���ô����뱣֤pInChar���ַ������Ȳ�С��m_ObjLen
	//���أ�	�ַ�����Ѱַ��ַ
	
	VarCharAddress	AddObj(const SG_CHAR*pInChar);
	// --- ɾ��һ���ַ���
	//����������Ľ������Ÿ�Ϊ�����ã���0�����޸�дָ��
	
	void			DeleteObj(VarCharAddress Addr);
	// --- �滻һ���ַ���
	//����������������滻ΪpInChar�еģ�Լ��ͬAddObj
	
	void			ModiObj(VarCharAddress Addr,const SG_CHAR*pInChar);
	//---��ö�������(��ȡ�ַ�������)
	//Լ����pOutChar���ڴ泤�ȱ�����ڵ����ַ����ĳ��ȣ�1
	
	void	GetObj(VarCharAddress Addr,SG_CHAR*pOutChar);
	
	void	GetObj(VarCharAddress Addr,CSgString&msg);
	SG_PCSTR GetObj( VarCharAddress Addr );
	//���VarChar����Ϣ
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	
public:
	// --- �����ڴ�����
	
	void SetStep(SG_SHORT Step){m_Step=Step;}
	// --- ���ö��������
	
	SG_BOOL SetSize(SG_INT MemSize);
	// --- ��չ���������趨��������չ����
	
	SG_BOOL ExtendSize();
	// --- �����洢(���貽��)
	
	void Pack();

protected:
	// --- ��ö�����ڴ��ַ
	//��������������Ե�ַ
	
	inline SG_CHAR *GetObjMemAddress(SG_INT ObjAddr){
		return m_pMem+(m_ObjLen+1)*ObjAddr;
	}

protected:
	
	SG_INT	m_MemNums;		// --- �ڴ��п��Դ�ŵĶ��������
	
	SG_INT	m_ObjNums;		// --- ռ�õ��Ķ�������
	
	SG_INT	m_WritePos;		// --- дָ��
	
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

	// --- ��ȡVarChar
	//Լ����pOutChar���ڴ泤�ȱ�����ڵ����ַ����ĳ��ȣ�1
	
	void GetVarchar(VarCharAddress Addr,SG_CHAR*pOutChar);
	void GetVarchar(VarCharAddress Addr,CSgString&msg);
	SG_PCSTR GetVarchar( VarCharAddress Addr );

	// --- ���VarChar
	//Լ����pInChar���ڴ泤�ȱ�����ڵ����ַ����ĳ���
	
	VarCharAddress SetVarchar(VarCharAddress Addr,const SG_CHAR*pInChar,SG_INT strLength);
	//���VarChar����Ϣ
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	// --- �����洢(���貽��)
	
	void Pack(SG_SHORT Step=10);

protected:
	// --- �ַ�������
	CSgPtrArray m_VarcharArray;

	// --- ���Ƴ���
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
