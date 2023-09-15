// cobjectbaseattrib.h
//

#if !defined(SgMicro_h)
#define SgMicro_h

#include "limits.h"

#define		NULLSTR			/**/
/*
		part	1		��ģ�崦��
		part	2			����������
		part	3		LocalLib��������Ԫ�ض�ȡ��д�������
		part	4		ȫ��Ψһʵ����Ĺ��÷���������
		part	5		��ֵ�������ݰ�λ���������

		part	8		�ַ�����ȫ����
		part	9		����ʹ��
						----�ַ�������
*/


/*
		part	1		��ģ�崦��
*/

template <class Obj> class SG_Chain
{
public:
	SG_Chain();
	~SG_Chain();
	void RemoveAll();
	SG_INT GetSize() const;
	void Add(Obj obj,SG_BOOL CheckExist=false);
	SG_BOOL GetAt(SG_INT index,Obj &obj);
	void Remove(Obj delobj);
	void RemoveAt(SG_INT index);
	SG_BOOL Exist(Obj obj);

protected:
	struct Element{
		Element *pNext;
		Obj cur;
	};
	
	Element *pFirst;
};

template <class Obj>SG_Chain<Obj>::SG_Chain()
{
	pFirst = NULL;
}
template <class Obj>SG_Chain<Obj>::~SG_Chain()
{
	RemoveAll();
}
template <class Obj>
void SG_Chain<Obj>::RemoveAll()
{
	Element *p ;
	p = pFirst;
	pFirst = NULL;
	while(p)
	{
		p = p->pNext;
		delete p;
	}
}
template <class Obj>
SG_INT SG_Chain<Obj>::GetSize() const
{
	SG_INT nums=0;
	Element *p ;
	p = pFirst;
	while(p)
	{
		p = p->pNext;
		nums++;
	}
	return nums;
}
template <class Obj>
void SG_Chain<Obj>::Add(Obj obj,SG_BOOL CheckExist)
{
	if(CheckExist)
		if(Exist(obj))return;
	Element *temp = new Element;
	temp->cur = obj;
	temp->pNext = pFirst;
	pFirst = temp;
}
template <class Obj>
SG_BOOL SG_Chain<Obj>::GetAt(SG_INT index,Obj &obj)
{
	SG_INT nums=0;
	Element *p;
	p = pFirst;
	while(p)
	{
		if(index==nums){
			obj = p->cur;
			return true;
		}
		p = p->pNext;
		nums++;
	}
	return false;
}
	 
template <class Obj>
void SG_Chain<Obj>::Remove(Obj delobj)
{
	Element *p,*pLast=NULL;
	p = pFirst;
	while(p)
	{
		if(pFirst->cur == delobj){
			if(pLast==NULL)
				pFirst = p->pNext;
			else
				pLast->pNext = p->pNext;
			delete p;
			return;
		}
		pLast = p;
		p = p->pNext;
	}
}
template <class Obj>
void SG_Chain<Obj>::RemoveAt(SG_INT index)
{
	SG_INT nums=0;
	Element *p,*pLast=NULL;
	p = pFirst;
	while(p)
	{
		if(index==nums){
			if(pLast==NULL)
				pFirst = p->pNext;
			else
				pLast->pNext = p->pNext;
			delete p;
			return;
		}
		pLast = p;
		p = p->pNext;
		nums++;
	}
}
template <class Obj>
SG_BOOL SG_Chain<Obj>::Exist(Obj obj)
{
	for(Element *p=pFirst;p!=NULL;p=p->pNext)
	{
		if(p->cur == obj)return true;
	}
	return false;
}

/*
		part	2			����������
*/
#define SG_CHAIN_LAYERMANAGE		SG_Chain<CObjectBaseLayer *>
#define SG_CHAIN_OBJATTRIBMANAGE	SG_Chain<CObjectBaseAttrib *>
#define SG_CHAIN_INT			SG_Chain<SG_INT>

/*
		part	3		LocalLib��������Ԫ�ض�ȡ��д�������
*/
#define GET_AT(DATATYPE) \
	GetAt(SG_INT row,SG_SHORT col,DATATYPE *value);
#define SET_AT(DATATYPE) \
	SetAt(SG_INT row,SG_SHORT col,DATATYPE *value);

#define DataSetGet(DATATYPE)								\
SG_BOOL Get(SG_INT row,SG_CHAR *fieldname,DATATYPE *con)	\
{															\
	SG_INT col = GetFieldPtr(fieldname);					\
	if(col<0)return false;									\
	return GetAt(row,col,con);								\
}															\


/*
		part	4		ȫ��Ψһʵ����Ĺ��÷���������
*/
#define		UNIQUE_INS_H(classname) \
private:\
	static classname*m_pInstance;\
public:\
	static	classname* GetInstance();\
	static  void  FreeInstance();\

//ȫ��Ψһʵ����Ĺ��÷���ʵ�ֺ�
//**********************************************************
// �������� :  GetInstance
// ����     :  ������ʵ��,����Ĵ����ӳٵ���һ�η���
// ��ע		:  Ӧ�ô�ģʽ��֤������ֻ����һ��ʵ�������ṩһ��ȫ�ַ��ʽӿ�(static)
//**********************************************************
//**********************************************************
// �������� :  FreeInstance
// ����     :  �ͷ�classname��ʵ��
//**********************************************************
#define UNIQUE_INS_CPP(classname)\
classname* classname::m_pInstance=NULL;\
classname*classname::GetInstance()\
{\
	if(m_pInstance==NULL)\
	{\
		m_pInstance=new classname;\
	}\
	return m_pInstance;\
}\
void classname::FreeInstance()\
{\
	if(m_pInstance)\
	{\
		delete m_pInstance;\
		m_pInstance=NULL;\
	}\
}\


/*
		part	5		��ֵ�������ݰ�λ���������
*/
#define	SETBIT(MATHTYPE)\
	static void SetBit(MATHTYPE *content,SG_SHORT ptr)	\
	{	\
		if(ptr<0 || ptr>=sizeof(MATHTYPE)*8)return;	\
		MATHTYPE value;	\
		value = 1;	\
		if(ptr > 0)	\
		{	\
			value <<= ptr;	\
		}	\
		*content |= value;	\
	}\

#define	CLEARBIT(MATHTYPE)	\
	static void ClearBit(MATHTYPE *content,SG_SHORT ptr)	\
	{	\
		if(ptr<0 || ptr>=sizeof(MATHTYPE)*8)return;	\
		MATHTYPE value;	\
		value = 1;	\
		if(ptr > 0)	\
		{	\
			value <<= ptr;	\
		}	\
		value ^= 0xffffffff;	\
		*content &= value;	\
	}	\

#define	GETBIT(MATHTYPE)	\
	static SG_BOOL GetBit(MATHTYPE content,SG_SHORT ptr)	\
	{	\
		if(ptr<0 || ptr>=sizeof(MATHTYPE)*8)return false;	\
		MATHTYPE value;	\
		value = 1;	\
		if(ptr > 0)	\
		{	\
			value <<= ptr;	\
		}	\
		content &= value;	\
		return content!=0;	\
	}	\

/*�Ա������а�λ����---ȫ��ֻ��һ��ʵ�� */

class CBitOper{
public:
	//����λ��������
	SETBIT(SG_UCHAR);
	CLEARBIT(SG_UCHAR);
	GETBIT(SG_UCHAR);
	SETBIT(SG_INT);
	CLEARBIT(SG_INT);
	GETBIT(SG_INT);
	SETBIT(SG_UINT);
	CLEARBIT(SG_UINT);
	GETBIT(SG_UINT);
//#ifdef _USE_INT64_
	SETBIT(SG_UINT64);
	CLEARBIT(SG_UINT64);
	GETBIT(SG_UINT64);
//#endif
};




/*
		part	8		�ַ�����ȫ����
*/
#define StringCpy(strDest,strSource,sizeDest)   \
    {                                           \
	if(sizeDest>strlen(strSource))				\
		strcpy(strDest,strSource);				\
	else{										\
		memcpy(strDest,strSource,sizeDest-1);	\
		CommonFunc::GetRidErrChineseCode(strDest,sizeDest);\
    }\
   }\

/*
		part	9		��̬��������
*/

static const char *DbfConditionSym[] = {"=","<","<=",">",">="};
static const char *DbfConditionConnectSym[] = {" AND "," OR "};

/*
part	10		Ψһ�Ի���ĺ궨��
*/

#define		UNIQUE_INS_DLG_H(classname,resourceID) \
private:\
	static bool       m_Instance; \
	static classname* m_pInstance;\
public:\
	static	classname* GetInstance();\
	UINT Create();\
	virtual BOOL DestroyWindow();\
	

//////////////////////////////////////////////////////
#define UNIQUE_INS_DLG_CPP(classname,resourceID)\
	bool classname::m_Instance=0; \
	classname* classname::m_pInstance=0;\
	UINT classname::Create()\
{\
	if(m_Instance) return 0;\
	UINT id=CDialog::Create(resourceID);\
	ShowWindow(SW_SHOW);\
	CenterWindow();\
	m_Instance=1; \
	return id;\
}\
	BOOL classname::DestroyWindow()\
{\
	m_pInstance=0;\
	m_Instance=0; \
	return CDialog::DestroyWindow();\
}\
	classname*classname::GetInstance()\
{\
	if(m_pInstance==NULL)\
{\
	m_pInstance=new classname;\
}\
	return m_pInstance;\
}\


#define IsKernelObj( ObjType ) ( 0 <= ObjType && ObjType < ObjMirrorStartID )
#define IsMirrorObj(objtype) ( ObjMirrorStartID <= objtype && objtype < ObjShadowStartID )
#define IsShadowObj(objtype) ( ObjShadowStartID <= objtype && objtype <= ObjShadowLastID )

inline int GetTrueObjType( int ObjType ) 
{
	if( IsKernelObj( ObjType ) ) return ObjType ;
	if( IsMirrorObj( ObjType ) ) return ObjType - ObjMirrorStartID ;
	if( IsShadowObj( ObjType ) ) return ObjType - ObjShadowStartID ;
	return INT_MAX ;
}

#endif /* SgMicro_h */
