// fieldfilter.h
//
/*****************************************************************
	域过滤器
*****************************************************************/

#if !defined(SgFieldFilter_h)
#define SgFieldFilter_h

#include "sgfieldvariant.h"


class _DATASET_DLL_EXPORT_ CSgFieldFilter{
public:
	
	CSgFieldFilter();
	
	~CSgFieldFilter();
	
	char * GetFieldName();			//获得域名
	
	SG_SHORT GetFieldPtr();			//获得域位置
	
	SG_SHORT GetFieldType();		//获得域类型--数值还是字符串
	
	SG_SHORT GetLastRelation();
	
	SG_SHORT GetFieldClass();
	SG_SHORT GetFieldRule()
	{
		return m_Rule;
	};

public:
//以下信息可以在确定DataSet后自动关联赋值,最先初始化
	
	void SetFieldName(char*p);					//设置域名
	
	void SetFieldPtr(SG_SHORT pos);				//设置域位置
	
	void SetFieldType(SG_SHORT type);			//设置域类型--数值还是字符串

//使用前必须填写
	
	void	SetRule(SG_SHORT rule);							//设置判断规则--条件域类型
	
	void	SetLastRelation(SG_SHORT relation);				//设置与前一条件字段的关系
	
	SG_BOOL SetFieldValue(void *inputvalue,SG_INT pos=-1);	//设置阀值,如果pos=-1增加,否则改写指定位置的值
	
	SG_BOOL decide(void *inputvalue);						//判断值是否在选择范围内

	
	CSgFieldVariantArray *GetFieldValueArray(){return &m_ConValue;}

private:
	
	SG_FIELDNAME	m_FieldName;
	
	SG_USHORT		m_FieldPtr;
	
	SG_USHORT		m_FieldType;				//m_FieldType
	
	SG_USHORT		m_Rule;					//判断规则 0--等于 
	
	SG_UCHAR		m_Rela_LastCondition:1;		//与前一条件字段的关系 0-and 1-or
	
	SG_UCHAR		m_FieldClass:2;				//分类 0字符/1浮点/2整数
	
	CSgFieldVariantArray	m_ConValue;
};


#endif /* SgFieldFilter_h */
