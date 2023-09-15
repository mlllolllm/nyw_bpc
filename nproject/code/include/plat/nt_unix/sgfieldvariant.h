// SgFilter.h
//
/*****************************************************************
	������ֵ���������ļ���Ϊ����ʹ�ý�������ֵ������
*****************************************************************/

#if !defined(_SgFieldVariant_h_)
#define _SgFieldVariant_h_

//����������
enum FIELD_CON_TYPE{
	FIELD_CON_EQUEL		=0,	//����
	FIELD_CON_LESS		,	//С��
	FIELD_CON_LEEQ		,	//С�ڵ���
	FIELD_CON_MORE		,	//����
	FIELD_CON_MOEQ		,	//���ڵ���
	FIELD_CON_UNEQUEL	,	//������
	FIELD_CON_BETWEEN	,	//��ֵ֮��(ֻ������ֵ����)
	FIELD_CON_IN		,	//in
	FIELD_CON_LIKE			//like
};
//�������ϵ
enum FIELD_CON_RELATION{
	FIELD_CON_AND		=0,	//����
	FIELD_CON_OR			//���
};
//�������ڿ�ֵ����
enum FIELD_CON_VALUE_TYPE{
	FIELD_CON_VALUE_CHAR	=0,	//�ַ���
	FIELD_CON_VALUE_FLOAT	=1,	//����
	FIELD_CON_VALUE_INT		=2	//����
};

//������ֵ�洢�ṹ

union SgFieldVariant{
	
	SG_CHAR		*pcValue;
	
	SG_DOUBLE	dValue;
	
	SG_FLOAT	fValue;
	
	SG_UINT		uiValue;
	
	SG_INT		iValue;
	
	SG_UINT64	ulValue;

	SG_INT64	lValue;
	
	SG_USHORT	usValue;
	
	SG_SHORT	sValue;
	
	SG_UCHAR	ucValue;
};

//������ֵ����

class _DATASET_DLL_EXPORT_ CSgFieldVariantArray:public CSgPtrArray
{
public:
	
	CSgFieldVariantArray();
	
	virtual ~CSgFieldVariantArray();

	//����������--�ڿ�ֵ
	
	void SetFieldClass(SG_CHAR type);
	//ɾ�����ж���
	
	void RemoveAll();
	//����һ����ѡֵ
	
	void AddValue(void *value);
	//����ֵ
	
	void SetValue(SgFieldVariant *fv ,void *value);
	//��ÿ�ѡֵ -- Variant�ṹ
	
	SgFieldVariant *GetValue(SG_INT pos);
	//ֵIn
	
	SG_BOOL IsValueIn(void *value);

private:
	
	SG_USHORT m_FieldClass;
};

#endif /* _SgFieldVariant_h_ */
