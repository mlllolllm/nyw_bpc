// SgFilter.h
//
/*****************************************************************
	条件域值变量定义文件，为方便使用建立了域值队列类
*****************************************************************/

#if !defined(_SgFieldVariant_h_)
#define _SgFieldVariant_h_

//条件域类型
enum FIELD_CON_TYPE{
	FIELD_CON_EQUEL		=0,	//等于
	FIELD_CON_LESS		,	//小于
	FIELD_CON_LEEQ		,	//小于等于
	FIELD_CON_MORE		,	//大于
	FIELD_CON_MOEQ		,	//大于等于
	FIELD_CON_UNEQUEL	,	//不等于
	FIELD_CON_BETWEEN	,	//两值之间(只处理数值类型)
	FIELD_CON_IN		,	//in
	FIELD_CON_LIKE			//like
};
//条件域关系
enum FIELD_CON_RELATION{
	FIELD_CON_AND		=0,	//相与
	FIELD_CON_OR			//相或
};
//条件域内控值类型
enum FIELD_CON_VALUE_TYPE{
	FIELD_CON_VALUE_CHAR	=0,	//字符串
	FIELD_CON_VALUE_FLOAT	=1,	//浮点
	FIELD_CON_VALUE_INT		=2	//整形
};

//条件内值存储结构

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

//条件域值队列

class _DATASET_DLL_EXPORT_ CSgFieldVariantArray:public CSgPtrArray
{
public:
	
	CSgFieldVariantArray();
	
	virtual ~CSgFieldVariantArray();

	//设置域类型--内控值
	
	void SetFieldClass(SG_CHAR type);
	//删除所有对象
	
	void RemoveAll();
	//增加一个可选值
	
	void AddValue(void *value);
	//设置值
	
	void SetValue(SgFieldVariant *fv ,void *value);
	//获得可选值 -- Variant结构
	
	SgFieldVariant *GetValue(SG_INT pos);
	//值In
	
	SG_BOOL IsValueIn(void *value);

private:
	
	SG_USHORT m_FieldClass;
};

#endif /* _SgFieldVariant_h_ */
