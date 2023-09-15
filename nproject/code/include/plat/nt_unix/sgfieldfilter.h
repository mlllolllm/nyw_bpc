// fieldfilter.h
//
/*****************************************************************
	�������
*****************************************************************/

#if !defined(SgFieldFilter_h)
#define SgFieldFilter_h

#include "sgfieldvariant.h"


class _DATASET_DLL_EXPORT_ CSgFieldFilter{
public:
	
	CSgFieldFilter();
	
	~CSgFieldFilter();
	
	char * GetFieldName();			//�������
	
	SG_SHORT GetFieldPtr();			//�����λ��
	
	SG_SHORT GetFieldType();		//���������--��ֵ�����ַ���
	
	SG_SHORT GetLastRelation();
	
	SG_SHORT GetFieldClass();
	SG_SHORT GetFieldRule()
	{
		return m_Rule;
	};

public:
//������Ϣ������ȷ��DataSet���Զ�������ֵ,���ȳ�ʼ��
	
	void SetFieldName(char*p);					//��������
	
	void SetFieldPtr(SG_SHORT pos);				//������λ��
	
	void SetFieldType(SG_SHORT type);			//����������--��ֵ�����ַ���

//ʹ��ǰ������д
	
	void	SetRule(SG_SHORT rule);							//�����жϹ���--����������
	
	void	SetLastRelation(SG_SHORT relation);				//������ǰһ�����ֶεĹ�ϵ
	
	SG_BOOL SetFieldValue(void *inputvalue,SG_INT pos=-1);	//���÷�ֵ,���pos=-1����,�����дָ��λ�õ�ֵ
	
	SG_BOOL decide(void *inputvalue);						//�ж�ֵ�Ƿ���ѡ��Χ��

	
	CSgFieldVariantArray *GetFieldValueArray(){return &m_ConValue;}

private:
	
	SG_FIELDNAME	m_FieldName;
	
	SG_USHORT		m_FieldPtr;
	
	SG_USHORT		m_FieldType;				//m_FieldType
	
	SG_USHORT		m_Rule;					//�жϹ��� 0--���� 
	
	SG_UCHAR		m_Rela_LastCondition:1;		//��ǰһ�����ֶεĹ�ϵ 0-and 1-or
	
	SG_UCHAR		m_FieldClass:2;				//���� 0�ַ�/1����/2����
	
	CSgFieldVariantArray	m_ConValue;
};


#endif /* SgFieldFilter_h */
