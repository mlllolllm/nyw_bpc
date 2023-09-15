// fieldsfilter.h
//
/*****************************************************************
	����������ϣ�֧�ֶ������������� ����������δʵ��
	��Sql�������ƣ��ϸ񸴺� select * from tablename where f1=aa and f2<bb or f3>cc order by ww,hh �Ĺ���
					��ʱ��֧����֮��Ĺ�ϵ����f1��f2
					��ʱ��֧�ֿ��֮��Ĳ���
*****************************************************************/

#if !defined(SgFieldsFilter_h)
#define SgFieldsFilter_h

#include "sgfieldfilter.h"
//#include <afxcoll.h>

class CSgDataSet;


//�ڴ���������ѯ��������

class _DATASET_DLL_EXPORT_ CSgFieldsFilter
{
public:
	
	CSgFieldsFilter();
	
	~CSgFieldsFilter();

public:
	
	void SetConFieldNums(SG_INT nums);			//���������ֶ�����
	
	CSgFieldFilter *GetConField(SG_UINT ptr);	//��������ֶβ���ָ��
	
	SG_INT GetConFieldNums(){return m_ConFieldNums;}

public:
	//where�Ӿ����
	//pDataSetΪ�ο���¼����whereΪһ��������sql����where�Ӿ�
	
	void SplitWhereWorld(CSgDataSet *,const char *where);
	//������where�Ӿ� --- ȥ���� where �ؼ���
	
	void SplitSimpleWhereWord(CSgDataSet *,char *where);
	
	void ConMultiWhereWord(CSgDataSet *pDataSet, char *where);
	
	void SplitMultiWhere(char *where,CSgStringArray &strArray);

private:
	
	char * GetSimpleWhereRule(char *where,SG_INT &rule,SG_INT &pos);

private:
	
	SG_INT m_ConFieldNums;			//�����ֶ�����
	
	CSgFieldFilter *m_pConField;	//�����ֶ���Ϣ
};

#endif /* SgFieldsFilter_h */
