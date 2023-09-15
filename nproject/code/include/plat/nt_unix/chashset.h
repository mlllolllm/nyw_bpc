// chashset.h
//

#if !defined(_HASH_SET_H)
#define _HASH_SET_H

#include "sgdataset.h"
/*
 				Hash��������
    ����:	
		��ֵ		-- ������������ֵ,��������
		����ֵ		-- ��ֵ��Ӧ������ֵ,��������
		��ֵ����	-- һ����ֵ��������ռ���ڴ�ĳ���
		����ֵ����	-- һ������ֵ��������ռ���ڴ�ĳ���
		ģֵ		-- ����hash��ַʱ���õ�ģ��ֵ,�޷���������
		��������	-- ��ֵ�����洢���������ڴ����,��Ϊ��������
		Hash��ַ����-- һ��hash��ַ��Ӧ�Ķ����������,�ɶ������������ɵĽṹΪhash��ַ����
*/


struct _DATASET_DLL_EXPORT_ HashSetData{
	
	SG_SHORT m_KeyValue_Len;	//	��ֵ����	-- һ����ֵ��������ռ���ڴ�ĳ���
	
	SG_SHORT m_IndexValue_Len;	//	����ֵ����	-- һ������ֵ��������ռ���ڴ�ĳ���
	
	SG_ULONG m_ModuleValue;		//	ģֵ		-- ����hash��ַʱ���õ�ģ��ֵ,�޷���������
	// --- ��ü�������ռ���ڴ�ĳ���
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

	// --- �Ƿ����
	
	SG_BOOL IsUseAble(){return m_UseAble;}

	//�������
	
	void ResetHash(SG_BOOL ReInit=false);
	//��ʼ�� --- �����Ϊ:��ֵ����,����ֵ����,ģֵ
	
	void InitHash(SG_SHORT KeyValueLen,SG_SHORT IndexValueLen,SG_ULONG Module);
	//�������� --	����ֵKeyValue����һ������ֵ
	//				CheckFlagΪ����Ƿ��Ѿ����д��ڸ��������Ʊ���
	
	SG_BOOL Bind(void* KeyValue,void* IndexValue,SG_BOOL CheckFlag=false);
	//ɾ����
	SG_BOOL UnBind(void* KeyValue,void* IndexValue);
	//�������	--	��ü�ֵKeyValue��Ӧ������ֵ
	SG_BOOL Find(void* KeyValue,void *IndexValue);
	SG_BOOL Find(SG_LONG KeyValue,void *IndexValue);
	SG_BOOL Find(SG_INT64 KeyValue,void *IndexValue);
	//�������	--	��ü�ֵKeyValue��Ӧ������ֵ,������ֵǿ��ת��Ϊ������
	
	SG_BOOL Finds(void* KeyValue,CSgObjects &rows);
	SG_BOOL Finds(SG_LONG KeyValue,CSgObjects &rows);
	SG_BOOL Finds(SG_INT64 KeyValue,CSgObjects &rows);
	/*
	 *	���hash��ַ�Ͼۼ��ļ�ֵ����
	 *	Լ����������Ϊ�ض�Ӧ�ã�ֻ�ʺϼ�ֵΪ4�ֽ�������ֵ�����
	 */
	SG_BOOL GetAddrKeyValue(SG_LONG index,CSgObjects *pArray);

public:
	//������ʽ���洢���������������ݵ����ʽ����
	void	CreateFormatArea();
	//��������ʽ���洢�����Ż��ڴ�洢�����������ݵ����ʽ����
	void	PackMem();
	//�������ռ�õ��ڴ�
	
	SG_LONG GetMemLen();
	
protected:
	// --- ��ü�ֵ��hash����
	
	SG_ULONG GetHashIndex(void*KeyValue);
	
private:
	//�Ƿ��Ѿ����ø�ʽ���洢
	SG_BOOL	IsUseFormatStore();
	/************************************************************************/
	/*                     ������ţ���ӣ�����ʽ��                         */
	/*			�����ɹ�������ַ�뷵��true�����򷵻�false�������ַ��		*/
	/************************************************************************/
	SG_BOOL PushToFormatArea0(void *KeyValue,void *IndexValue,struct HashAddressCode&ac);
	/************************************************************************/
	/*				 Hash��ַ�����ţ���ӣ�����ʽ���� 	 		        */
	/*			�����ɹ�������ַ�뷵��true�����򷵻�false�������ַ��		*/
	/************************************************************************/
	SG_BOOL PushToFormatArea(SG_INT AreaNo,struct HashAddressObj &ha,struct HashAddressCode&ac);
	/************************************************************************/
	/*		��ac��Ӧ����������������Key/Index���ת�浽�´洢��		        */
	/*		�����ɹ��󲢽�ԭ�洢���ͷţ����¸�дac����						*/
	/*				���򷵻�false��ϵͳ���κα��							*/
	/************************************************************************/
	SG_BOOL ChangeToFormatArea(SG_INT AreaNo,struct HashAddressCode&ac,void*KeyValue,void*IndexValue);
	/************************************************************************/
	/*             hash��ַ����δ��������£�������ŵ�������		        */
	/*			�����ɹ�������ַ�뷵��true�����򷵻�false�������ַ��		*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(void *KeyValue,void *IndexValue,struct HashAddressCode&ac);
	/************************************************************************/
	/*             hash��ַ����δ��������£�������ŵ�������		        */
	/*			�����ɹ�������ַ�뷵��true�����򷵻�false�������ַ��		*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(struct HashAddressObj &ha,struct HashAddressCode&ac);
	/************************************************************************/
	/*             hash��ַ�����Ѿ���������£�������ŵ�������		        */
	/*						�ô��������ַ��								*/
	/************************************************************************/
	SG_BOOL PushToFreeArea(SG_INT FreeNo,void *KeyValue,void *IndexValue,SG_BOOL CheckFlag,struct HashAddressCode&ac);
	//�����ac���ĸ�ʽ�����Ƿ��Ѿ����ڼ���Ҫ�أ��Ѵ��ڷ���true
	SG_BOOL LocateAtFormatArea(struct HashAddressCode&ac,void *KeyValue,void *IndexValue);
	//�Ӹ�ʽ������ȡ���ݸ��Ƶ�hash��ַ����
	SG_BOOL FormatDataToAddressObj(struct HashAddressCode&ac,struct HashAddressObj &ha);
	/************************************************************************/
	/*					 �ͷŸ�ʽ�����ڴ�ռ��		 		 		        */
	/*			�����ʽ������ַ�ϵļ�������Ϊ0���ͷ��ڴ�ռ��				*/
	/************************************************************************/
	SG_BOOL FormatAreaFreeMem(struct HashAddressCode&ac);
	//�Ӹ�ʽ��������
	SG_BOOL FindInFormatArea(SG_INT AreaNo,SG_INT Pos,void*KeyValue,void*IndexValue);
	SG_BOOL FindsInFormatArea(SG_INT AreaNo,SG_INT Pos,void*KeyValue,CSgObjects &rows);
	//��ַ��������
	CSgObjects	*m_pAddrIndex;
	//������дָ��
	SG_INT	m_FreeAreaWritePtr;
	//��ʽ���洢������
	CSgPtrArray	*m_pFormatArray;

private:
	// --- hash��ַ�����ַ����
	
	CSgPtrArray *m_pHashObjAddress;
	
	SG_BOOL m_UseAble;	//HashSet���ñ��
};

#endif /* _HASH_SET_H */
