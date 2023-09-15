	// csgtableinfo.h
//

#if !defined(CSgTableInfo_h)
#define CSgTableInfo_h
#include <stdio.h>
#include <string.h>

#include "sgdataset.h"
#include "sgmicro.h"

#define		TABLEINFO_USEABLE		1
#define		TABLE_USEABLE			2

#define		CHAR_TO_VARCHAR_LEN		16	//��Ӧ���ȳ���16���ֽڵ��ַ����ֶ��ڴ�����VarChar��¼
#define		VARCHAR_TO_CHAR_LEN		8	//���ڳ���С��8�ı߳��ַ����ڴ�����CHAR��¼

/***********************************************
		�������Ա�����Ϣ�ṹ
***********************************************/
//�������Ա�����Ϣ�ṹ

class _DATASET_DLL_EXPORT_ CSgFieldInfo
{
private:
	
	CSgString FieldName;
public:
	
	SG_SHORT FieldType;
	
	SG_SHORT FieldLen;
	
	SG_SHORT SqlType;			// for oracle
	
	SG_USHORT ConPtr;			//�ֶ�������һ����¼�е���ֹ���λ��
	union{
		SG_USHORT SerializeValue;
		struct
		{
#if defined(__sun)||defined(_AIX)
            SG_UCHAR Reserved:5;
			SG_UCHAR SdeRowIDFiled:1;
           SG_UCHAR SdeAttribFlag:1;
			SG_UCHAR ChangeFlag:1;		//��ֵ�Ƿ��޸�---StartEditTable��Ĳ�����
			SG_UCHAR IsBlob:1;			//�Ƿ�Blob�ֶΣ���CSgVariate����
			SG_UCHAR IsVarChar:1;		//�Ƿ�VarChar����CSgString����
			SG_UCHAR GraphFlag:1;		//�������Ա�־�����Զ�����еļ�����ֻ����ͨ�����νṹ��صķ�����ֵ
			SG_UCHAR CommonFlag:1;		//��������
            SG_UCHAR ExtAttribFlag:1;
			SG_UCHAR UpdateFlag:1;		//����sql���ʱ�Ƿ���Ա�update
			SG_UCHAR Primary:1;//����
            SG_UCHAR CanBeNull:1;//�����
#else
            SG_UCHAR CanBeNull:1;//�����
			SG_UCHAR Primary:1;//����
			SG_UCHAR UpdateFlag:1;		//����sql���ʱ�Ƿ���Ա�update
			/*
			 *	����չ����Դ�е����Ա�ʾ��ͼ������δ������ǰ����SdeAttribFlag����
			 *  �����ദ��󣬿���ͬʱΪ1
			 *  ����ǰ��λ��Ψһ���Ϊ��DataSet��ExtendFieldInfo������һ�������ݼ���Combin�����Զ�����
			 *  �����Ĵ���ʽ�������������������Combin������ԭ������
			 */
			SG_UCHAR ExtAttribFlag:1;
			SG_UCHAR CommonFlag:1;		//��������
			SG_UCHAR GraphFlag:1;		//�������Ա�־�����Զ�����еļ�����ֻ����ͨ�����νṹ��صķ�����ֵ
			SG_UCHAR IsVarChar:1;		//�Ƿ�VarChar����CSgString����
			SG_UCHAR IsBlob:1;			//�Ƿ�Blob�ֶΣ���CSgVariate����
			SG_UCHAR ChangeFlag:1;		//��ֵ�Ƿ��޸�---StartEditTable��Ĳ�����
			/*
			 *	�������ֶ�Ϊͼ������Դ�е����ԣ�ȱʡֵΪ0���ñ�ǵĽ�����Ψһ���Ϊ��
			 *  ArcSDE�ӿ��л�ü�¼�����Ϣʱ�������Ϊ��1
			 */
			SG_UCHAR SdeAttribFlag:1;
			SG_UCHAR SdeRowIDFiled:1;
            SG_UCHAR Reserved:5;
#endif
        }BitVal;
	};
	/*
	 *	���±�����Ӧ�û�����أ����������紫�䴫��
	 */
	SG_UCHAR Catch_EffectView:1;		//���ݱ仯ʱ�Ƿ���CheckChangeFlag�����н�����Ӱ����ͼ�����
	SG_UCHAR Catch_EffectIndex:1;		//���ݱ仯ʱ�Ƿ���CheckChangeFlag�����н�����Ӱ�����������
	SG_UCHAR Catch_EffectLoadRange:1;	//���ݱ仯ʱ�Ƿ���CheckChangeFlag�����н�����Ӱ����ء����
public:
	CSgFieldInfo();
	~CSgFieldInfo();
	//��������
	void SetFieldName(SG_PCSTR pFieldName);
	//�������
	SG_PSTR GetFieldName();
	/*
	 *  ��;���ж���������Ϣ�Ƿ�һ��
	 *  �оݣ����������ơ����͡��򳤶��Ƿ���ȫһ��
	 *  ע�⣺DecideConPtr�����Ƿ��ж����ڱ���Ϣ�е�������Գ��ȡ�ͨ�����ж�����DataSet��ȫһ��ʱ�����Ϊtrue��
	 */ 
	SG_BOOL Equal(CSgFieldInfo *p,SG_BOOL DecideConPtr);
	//�ж����������Ƿ�һ��
	SG_BOOL EqualName(SG_PCSTR p);
	//�ж����Ƿ�������оݣ�����SdeAttribFlag����ExtAttrib����
	SG_BOOL IsBaseField();
	//���кŴ���
	SG_BOOL Serialize(CSgArchive&ar);

	//	��ֵ����
	CSgFieldInfo & Assign( const CSgFieldInfo & rhs );
	CSgFieldInfo & operator = ( const CSgFieldInfo & rhs );

	SG_BOOL IsMathType();
};


class _DATASET_DLL_EXPORT_ CSgTableInfo : public CSgPtrArray
{
public:
	
	CSgTableInfo();
	
	virtual ~CSgTableInfo();
	
	virtual void RemoveAll();
	
	void ResetTableInfo();

protected:
	// --- ���±�����Ա�����Ͳ��ܱ�����������л����紫�䣩
	
    SG_UINT		m_RecordNums;	//��¼������
	
	SG_UINT		m_RecordSize;	//��¼ʵ�ʿ����ڴ������
	
    SG_SHORT	m_ObjectType;	//�������豸����
	
	SG_SHORT	m_ArcGisID_ptr;	//
	
	SG_SHORT	m_ID_ptr;		//
	
	SG_USHORT	m_FieldNums;	//�ֶ�����
	
    SG_USHORT	m_RecordLen;	//ÿ��¼�ĳ���
	
	SG_UCHAR	m_FeatureType;	//�����Ķ��������������
	
	SG_UCHAR	m_UseAble;		//DataSet�Ƿ����
	
	SG_UCHAR	m_HasGeometryFlag;	//�Ƿ���м����ֶ�
	
protected:
	
	SG_CHAR		m_Flag_ptr;		//
	// --- ʵ�������ͣ������������紫���н��ղ�ķ����л�����
	// ֧�ַ��Ͳ�Ϊ���࣬���ܲ�������Ϊ�����࣬��֮�����ϵͳ��ͨ���쳣
	//SG_UCHAR	m_InstanceType;
	//�ڿ��������� --- �������󻯺�,ϵͳ�Զ��������ӵ��ڿ���Ϣ����
	
	ObjType_IA_Cfg_Struct m_ObjControlAttrib;
	//
	
    CSgString	m_ObjectTypeName;
	
    CSgString	m_TableName;//������
	//�������ݼ���Where�Ӿ�
	
	CSgString	m_WhereWord;
	//
	//��¼ƫ�����������ݴ���
	SG_SHORT	m_AD_ID_ptr;//A/D�������
	SG_SHORT	m_TaskID_ptr;
	
public:
	//
	SG_UCHAR GetBaseFeatureType(){ return m_FeatureType;}
	void SetBaseFeatureType(SG_UCHAR ft){ m_FeatureType=ft;}
	
	//��á�����DataSet�����Ķ�������
	
	void SetObjType(SG_SHORT type){ m_ObjectType=type;}
	SG_SHORT GetObjType(){ return m_ObjectType;}

	//��á�����DataSet�����Ķ�������
	void SetObjectName(const char* name){ m_ObjectTypeName=name;}
	SG_PCSTR GetObjectName(){ return m_ObjectTypeName.GetSafeBuffer();}
	//���ݼ����ã����м�¼
	SG_BOOL GetUseAble(){ return m_UseAble==TABLE_USEABLE;}
	//��ü�¼����
	SG_USHORT GetRecordLen(){ return m_RecordLen;}
	//����Ϣ����
	
	SG_BOOL GetTableInfoUseAble(){return m_UseAble==TABLEINFO_USEABLE||m_UseAble==TABLE_USEABLE;}
	//����Ƿ���м������Ա�� --- �����ڱ༭ʱUpdate�����Ŀ���
	
	SG_UCHAR GetHasGeometry(){return m_HasGeometryFlag;}
	//�����Ƿ���м������� --- �����ڱ༭ʱUpdate�����Ŀ���
	
	void SetHasGeometry(SG_UCHAR flag);
	//���÷��ʵı���
	
    void SetTableName(SG_PCSTR tablename);
	//��ñ�����
	
    SG_PSTR GetTableName();
	//������name�Ƿ�һ��
	
	SG_BOOL IsNameEqual(SG_PCSTR name);
	//���ñ�ͷ��Ϣ
	
    SG_BOOL SetFieldNums(SG_INT nums);						//�ֶ�����
	
    void SetFieldName(SG_INT fieldptr, SG_PCSTR name);		//�ֶ���
	
    void SetFieldType(SG_INT fieldptr, SG_INT type);		//�ֶ�����
	
	void SetFieldInfo(SG_INT ptr,CSgFieldInfo*fi);		//�����ֶνṹ��Ϣ
	
    void SetFieldLen(SG_INT fieldptr, SG_INT len);			//�ֶγ���
	
    void SetFieldCanBeNull(SG_INT ptr, SG_BOOL flag);		//����Ϊ��
	
    void SetFieldPrimary(SG_INT fieldptr, SG_BOOL value);	//�ֶ�Ϊ����
	
    void SetFieldPrimary(SG_CHAR* fieldname);				//�ֶ�Ϊ����
	
    void SetFieldSqlType(SG_INT fieldptr, SG_INT type);		//�ֶη�������Դ�ļ�����
	
    void SetUpdateFlag(SG_BOOL flag);						//���������ֶε��Ƿ�ɱ�Update����
	
    void SetUpdateFlag(SG_INT ptr, SG_BOOL flag);			//�ֶ��Ƿ�ɱ�Update����
	
	void SetChangeFlag(SG_BOOL flag=true);					//���������ֶεı����ı�־
	
	void SetChangeFlag(SG_INT ptr,SG_BOOL Flag);			//�����ֶα����ı�־
	
	void SetFieldIsGisID(SG_INT ptr);					//�����ֶ�Ϊϵͳ�Ķ���ID
	
	void SetFieldIsArcGisID(SG_INT ptr);				//�����ֶ�ΪArcSDE��ObjectID
	
	void SetIdIsSysID();								//ID�ֶ�ΪSgGis/ArcGisID/����
	void SetIsSdeField(SG_INT ptr,SG_BOOL IsSdeAttrib);	//�����Ƿ�Ϊ�洢��Sde�е�����
	// --- �������������ڵ�ǰ�е���ֹ���λ��
	void SetFieldIsSdeRowID(SG_INT ptr, SG_BOOL flag);		//�����ֶ��Ƿ���SDE��RowID�ֶ�
	SG_BOOL GetFieldIsSdeRowID(SG_INT ptr);
	SG_INT GetColConPtr(SG_SHORT FieldPos);
	//�Ƿ����ĳ�������ֶ�
	
	SG_BOOL HasField(SG_SHORT fieldtype);
	//�Ƿ����Raw�ֶ�
	
	SG_BOOL HasRawField(){return HasField(SG_FIELDTYPE_RAW);}
	//�Ƿ��������ʱ���ֶ�
	
	SG_BOOL HasDateTimeField(){return HasField(SG_FIELDTYPE_DATETIME);}
	
    static SG_INT GetFieldTrueLen(CSgFieldInfo * p);
	// --- �������ַ����ֶεĿ��
	
	SG_SHORT GetMaxCharLen();
	//
	
	virtual SG_BOOL BuildTableInfo();
	//
	
    SG_UINT GetRecordNums(){return m_RecordNums;}
	// --- ��ü�¼����������
	SG_INT GetFieldNums(){ return m_FieldNums;}
	// --- ��ü�¼���л����������
	SG_SHORT GetBaseFieldNums();
	
	SG_SHORT GetGisIDPtr()	{ return m_ID_ptr;	} 			//������λ��ID�ֶε�λ��
	SG_SHORT GetFlagPtr()		{ return m_Flag_ptr;}
	
	SG_SHORT GetArcGisIDPtr()	{ return m_ArcGisID_ptr;}	//����ͼԪID�ֶε�λ��
	SG_SHORT GetADTableIDPtr()	{ return m_AD_ID_ptr;}		//�õ�a/d��ad_id�ֶε�λ��
	SG_SHORT GetTaskIDPtr()		{ return m_TaskID_ptr; }	//�õ�a/d����taskid�ֶε�λ��
	SG_BOOL	ArcGisID_Is_RowID();							//
	
	virtual SG_CHAR * GetSdeSelfKeyFieldName();			//����Զ��������ֶ������Կͻ��˶���ֻ����KID��Sde��RowID
	virtual void SetSdeSelfKeyFieldName(SG_CHAR*name);	//�����Զ��������ֶ���
	SG_PSTR GetFieldName(SG_INT ptr);						//�ֶ���
	
    SG_SHORT GetFieldPtr(SG_PCSTR fieldname);				//�ֶ�λ��
	
    SG_SHORT GetFieldPtr(CSgString &fieldname);				//�ֶ�λ��
	
    SG_INT GetFieldType(SG_INT ptr);						//�ֶ�����
	
    CSgFieldInfo* GetFieldInfo(SG_INT ptr);				//����ֶνṹ��Ϣ
	
    SG_INT GetFieldLen(SG_INT ptr);							//�ֶγ���
	
    SG_BOOL GetFieldCanBeNull(SG_INT ptr);					//����Ϊ��
	
    SG_BOOL GetFieldPrimary(SG_INT ptr);					//�ֶ�Ϊ����
	
    SG_BOOL GetFieldPrimary(SG_CHAR* fieldname);			//�ֶ�Ϊ����
	
    SG_INT	GetFieldSqlType(SG_INT fieldptr);				//�ֶη�������Դ�ļ�����
	
    SG_BOOL GetUpdateFlag();								//���ݼ��Ƿ�ɱ�Update����
	
    SG_BOOL GetUpdateFlag(SG_INT ptr);						//�ֶ��Ƿ�ɱ�Update����
	
    SG_BOOL GetFieldMathType(SG_INT ptr);					//�ֶ��Ƿ���ֵ����
	
	SG_BOOL GetChangeFlag();								//���ݼ��Ƿ�ɱ����Ĺ�
	
	SG_BOOL GetChangeFlag(SG_INT ptr);						//�ֶ��Ƿ񱻸���
	
	SG_BOOL GetFieldIsGisID(SG_INT ptr);					//�ֶ�Ϊϵͳ�Ķ���ID
	
	SG_BOOL	GetFieldIsArcGisID(SG_INT ptr);					//�ֶ�ArcSDE��ObjectID
	//
	
	void RemoveExtField();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	//
	
	CSgTableInfo& operator=(CSgTableInfo&ti);
};

#endif /* CSgTableInfo_h */
