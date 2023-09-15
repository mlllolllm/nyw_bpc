// fieldsfilter.h
//
/*****************************************************************
	域过滤器集合，支持多个条件相与相或 ？？？？还未实现
	对Sql语句的限制：严格复合 select * from tablename where f1=aa and f2<bb or f3>cc order by ww,hh 的规则
					暂时不支持域之间的关系。如f1《f2
					暂时不支持跨表之间的操作
*****************************************************************/

#if !defined(SgFieldsFilter_h)
#define SgFieldsFilter_h

#include "sgfieldfilter.h"
//#include <afxcoll.h>

class CSgDataSet;


//内存库检索（查询）过滤器

class _DATASET_DLL_EXPORT_ CSgFieldsFilter
{
public:
	
	CSgFieldsFilter();
	
	~CSgFieldsFilter();

public:
	
	void SetConFieldNums(SG_INT nums);			//设置条件字段数量
	
	CSgFieldFilter *GetConField(SG_UINT ptr);	//获得条件字段操作指针
	
	SG_INT GetConFieldNums(){return m_ConFieldNums;}

public:
	//where子句解析
	//pDataSet为参考记录集、where为一个完整的sql语句或where子句
	
	void SplitWhereWorld(CSgDataSet *,const char *where);
	//单纯的where子句 --- 去除了 where 关键字
	
	void SplitSimpleWhereWord(CSgDataSet *,char *where);
	
	void ConMultiWhereWord(CSgDataSet *pDataSet, char *where);
	
	void SplitMultiWhere(char *where,CSgStringArray &strArray);

private:
	
	char * GetSimpleWhereRule(char *where,SG_INT &rule,SG_INT &pos);

private:
	
	SG_INT m_ConFieldNums;			//条件字段数量
	
	CSgFieldFilter *m_pConField;	//条件字段信息
};

#endif /* SgFieldsFilter_h */
