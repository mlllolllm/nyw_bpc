// CHashDataSetBase.h
//

#if !defined(_HASH_DATA_SET_BASE_H)
#define _HASH_DATA_SET_BASE_H

#include "chashset.h"

/*******************************************************************
 				Hash�������������ݼ��е�Ӧ�û���
*******************************************************************/
class CSgTableInfo;
class CSgDataSet;
//#ifdef GDB_SRV
class ACE_Thread_Mutex;
//#endif


struct _DATASET_DLL_EXPORT_ HashSetAndFields
{
	
	CSgObjects	fields;			//Hash���ݼ����ֶ�
	
	CHashSet	hashset;		//hash���ݼ�
	
	SG_BOOL		ClearMemFlag;	//��ü�ֵǰ�Ƿ�����ڴ�
	
	SG_SHORT	MemLen;		//�ڴ泤��
	
	SG_CHAR		*pTempMem;	//�ڴ�ָ��
	
	HashSetAndFields();
	
	~HashSetAndFields();
	/**************************************************
						����Ӧ�÷���
	**************************************************/
	//��ռ�ֵ�����ڴ�
	SG_BOOL	ClearTmpMem();
	/*
	 *	����ʱ��ֵ�洢����pTempMem�С�������ֵ
	 *  ע�⣺fieldptr=�ڱ���Ϣ�е�λ��
	 *  ��;������DataSet����֪��ֵ����Ҫ�������ֵʱ���ø÷����γ��������ҵļ�ֵ
	 */
	void CreateKeyValue(CSgTableInfo*pTableInfo,SG_SHORT fieldptr,void*KeyValue);
	void CreateCharKeyVal(CSgTableInfo*pTableInfo,SG_SHORT fieldptr,const char*KeyValue,SG_INT strlen);
};

struct HashObjIndexStruct
{
	HashObjIndexStruct();
	~HashObjIndexStruct();
	// --- �ض�����ָ��
	HashSetAndFields	*pIDHashSet;
	//��BaseObjType��BaseObjID�ϵ�����
	HashSetAndFields	*pBaseObjHashSet;
	HashSetAndFields	*pArcGisIDHashSet;
	// --- CHashSet����
	CSgPtrArray			m_HashSets;
};


class _DATASET_DLL_EXPORT_ CHashObjIndex
{
public:
	
	CHashObjIndex();
	
	~CHashObjIndex();

//public:
//	// --- �����ݼ�
//	
//	void BindDataSet(void *pDataSet){}			//�����ݼ�

public: 
	/*
	 *	����ע�᷽������ؼ�������ֻ����ע�ᣬ������ʵ������
	 */
	//����������ֶ��ϡ�ע��������
	virtual HashSetAndFields* RegisterIndexOn(CSgObjects &IndexField);
	virtual HashSetAndFields* RegisterIndexOn(const char*szFieldName);
	//��ArcGISID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterIndexOnArcGisID();
	//��SgGISID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterIndexOnID();
	//�ڻ����������ͺͻ�������ID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterIndexOnBaseObj();

	/* 
	 *  ������������ָ��pHashSetʱֻ��pHashSet������������
	 *	����������������´�������
	 */
	virtual SG_BOOL CreateIndex(HashSetAndFields*pHashSet=NULL);
	/*
	 *	���´����������ı���ֵ������������ָ��pHashSetʱֻ��pHashSet������������
	 */
	virtual SG_BOOL ReCreateIndex(HashSetAndFields*pHashSet=NULL,SG_INT *pModValue=NULL);
	/*
	 *	ɾ�������������������������ɾ��
	 */
	void	DropIndex();
	void	DropIndex(HashSetAndFields*pHashSet);
	
	/*
	 *	ע�Ტ������������ؼ���������������ע�Ტ����
	 *  ע�⣺���Ѿ��������������Ѿ�������������ֱ���˳�
	 */
	HashSetAndFields* RegisterAndCreateOn(CSgObjects &IndexField);
	HashSetAndFields* RegisterAndCreateOn(const char*szFieldName);
	//��ArcGISID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterAndCreateOnArcGisID();
	//��SgGISID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterAndCreateOnID();
	//�ڻ����������ͺͻ�������ID�ֶ��ϡ�ע��������
	HashSetAndFields* RegisterAndCreateOnBaseObj();
	
public:
	//***ɾ����row���ϵ�����***
	virtual SG_BOOL DeleteIndexOnRow(SG_LONG row);
	//***��row���Ͻ�������***
	virtual SG_BOOL CreateIndexOnRow(SG_LONG row);
	//�ض�Ӧ�ã���û����豸���ͺͻ����豸ID�ļ�ֵ
	void MakeKeyValue(SG_OBJECT*pBuffer,SG_SHORT otype,SG_LONG oid);
	
public:
	/*
	 *	 ʹ�÷��������HashSet��ָ�룬�������ġ�ע�ᡱ����
	 */
	//���IndexField��Ӧ��hashset
	virtual HashSetAndFields* GetHashSet(CSgObjects &IndexField);
	virtual HashSetAndFields* GetHashSet(const char*szFieldName);
	//���ArcGisID��Ӧ��hashset
	virtual HashSetAndFields* GetArcGisIdSet();
	//���GisID��Ӧ��hashset
	virtual HashSetAndFields* GetSgGisIdSet();
	//��û����������ͺͻ�������ID�ֶ��ϵ�hashset
	virtual HashSetAndFields* GetBaseObjTypeIDSet();

public:

	CSgPtrArray* GetAllHashSetAndFields(){ return m_pHashIndex?&m_pHashIndex->m_HashSets:NULL;}
	//�������ռ�õ��ڴ�
	SG_LONG GetIndexMemLen();
	/*
	 *	������ȷ��У�顾����ֵ��1��ȷ��0����
	 */
	SG_BOOL	IndexCheck(CSgString&ErrorInfo);
	//���������ǰ��ģֵ
	virtual SG_UINT GetCurModVal();
	//�������ȱʡ��ģֵ
	//ע�������ж������ʱ�����ص�һ��������ģֵ
	virtual SG_UINT GetDefaultModVal();

protected:
	//��������󶨶���ı�ͷ��Ϣ
	virtual CSgTableInfo*GetTableInfo(){return NULL;}
	//������ݼ��� ��row�� �������� IndexField�ļ�ֵ
	virtual void *GetKeyValue(HashSetAndFields*p,SG_LONG row){return NULL;}
	/*
	 *	������ݼ��� ��row�� �������� IndexField�ļ�ֵ�ı���Ϣ
	 *  ����ֵ��1������ȷ��ã�0����δ��ȷ��á���ɾ����
	 */
	virtual SG_BOOL GetKeyString(HashSetAndFields*p,SG_LONG row,SG_CHAR*pInfo){return NULL;}
	//��ö�������
	virtual SG_UINT GetObjNums(){return 0;}
	
private:
	HashObjIndexStruct*		m_pHashIndex;
};

#endif /* _HASH_DATA_SET_BASE_H */
