	// csgdataset.h
//

#if !defined(CSgDataSet_h)
#define CSgDataSet_h


#include "nt_unix/sgdataset.h"
#include "nt_unix/sgmicro.h"

#include "nt_unix/csgtableinfo.h"
#include "nt_unix/sgfieldsfilter.h"
#include "nt_unix/cvarcharcontainer.h"
#include "nt_unix/chashdataset.h"
#include "nt_unix/objlockman.h"
#include "nt_unix/sgnp/NetCommand.h"

#ifdef WIN32
#pragma   warning   (disable:   4083   4786)   
#include <set>
#else
#include <set>
#endif

//#ifndef NOT_AUTOLINK
//#if defined(_MSC_VER) && !defined(_USE_CPP_) && !defined(_DATASET_DLL_) && !defined(GDB_SRV)
//#	ifdef _LIB
//#		ifdef _DEBUG
//#			pragma comment(lib , "SgDataSetSD.lib" )
//#		else
//#			pragma comment(lib , "SgDataSetS.lib" )
//#		endif
//#	else
//#		ifdef _DEBUG
//#			pragma comment(lib , "SgDataSetD.lib" )
//#		else
//#			pragma comment(lib , "SgDataSet.lib" )
//#		endif
//#	endif
//#endif /* _MSC_VER */
//#endif
enum SG_DATASET_TYPE
{
	SG_DATASET_TYPE_NORMAL	=	0,
	SG_DATASET_TYPE_GEO		=	1,
	SG_DATASET_TYPE_LOB	=	2,

};

/*
 * ���ݷ��ʺ�ļ�¼����
 */
class CSgArchive;
class CHashDataSet;
struct HashSetAndFields;

class RecordBase
{
public:

	RecordBase(CVarCharContainer*&pVarChars)
		:m_pVarChars(pVarChars)
	{
		m_pStart =NULL;
		m_pTableInfo =NULL;
	}

	SG_BOOL SetRecordPointer(CSgTableInfo*pTableInfo,char *p)
	{
		if(!p) return false;
		m_pStart = p;
		m_pTableInfo = pTableInfo;
		return true;
	}

public:
	//
	template <class MATHTYPE>
	SG_BOOL	SetAt(SG_SHORT col,MATHTYPE*msg)
	{
		if(col <0) return false;

		char * ptemp = m_pStart;
		if(col>0) ptemp += m_pTableInfo->GetColConPtr(col-1);

		switch(m_pTableInfo->GetFieldType(col))	
		{ 
		case SG_FIELDTYPE_BIT: 
		case SG_FIELDTYPE_TINYINT: 
			{ 
				SG_UCHAR value = (SG_UCHAR)(*msg);
				memcpy(ptemp,&value,sizeof(SG_UCHAR));	
			} 
			break;
		case SG_FIELDTYPE_SMALLINT: 
			{ 
				SG_SHORT value = (SG_SHORT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_SHORT));	
			} 
			break; 
		case SG_FIELDTYPE_USHORT:
		case SG_FIELDTYPE_BINARY:
			{ 
				SG_USHORT value = (SG_USHORT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_USHORT));
			}
			break;
		case SG_FIELDTYPE_INT:
		case SG_FIELDTYPE_LONG:
			{ 
				SG_INT value = (SG_INT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_INT));
			} 
			break; 
		case SG_FIELDTYPE_INT64:
			{ 
				SG_INT64 value = (SG_INT64)(*msg);
				memcpy(ptemp,&value,sizeof(SG_INT64));
			} 
			break; 
		case SG_FIELDTYPE_REAL:
			{ 
				SG_FLOAT value = (SG_FLOAT)(*msg);
				memcpy(ptemp,&value,sizeof(SG_FLOAT));	
			} 
			break; 
		case SG_FIELDTYPE_FLOAT: 
			{ 
				SG_DOUBLE value = (SG_DOUBLE)(*msg);
				memcpy(ptemp,&value,sizeof(SG_DOUBLE));	
			} 
			break; 
		default: 
			return false; 
		} 
		return true;
	}

	SG_BOOL	SetAt(SG_SHORT col,const SG_CHAR*);
	SG_BOOL SetAt(SG_SHORT col,void *p,SG_UINT len);

	template <class MATHTYPE>
	SG_BOOL	GetAt(SG_SHORT col,MATHTYPE*msg)
	{
		if(col <0) return false;

		char * ptemp = m_pStart;
		if(col>0) ptemp += m_pTableInfo->GetColConPtr(col-1);

		switch(m_pTableInfo->GetFieldType(col))
		{
		case SG_FIELDTYPE_BIT:
		case SG_FIELDTYPE_TINYINT:
			{ 
				unsigned char p; 
				p = *(unsigned char *)ptemp;
				*msg = (MATHTYPE)p; 
			} 
			break;
		case SG_FIELDTYPE_SMALLINT: 
			{ 
				SG_SHORT p; 
				memcpy(&p,ptemp,sizeof(SG_SHORT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_USHORT: 
		case SG_FIELDTYPE_BINARY: 
			{ 
				SG_USHORT p; 
				memcpy(&p,ptemp,sizeof(SG_USHORT)); 
				*msg = (MATHTYPE)p; 
			} 
			break;
		case SG_FIELDTYPE_INT: 
		case SG_FIELDTYPE_LONG: 
			{ 
				SG_INT p; 
				memcpy(&p,ptemp,sizeof(SG_INT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_INT64: 
			{ 
				SG_INT64 p; 
				memcpy(&p,ptemp,sizeof(SG_INT64)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_REAL: 
			{ 
				SG_FLOAT p; 
				memcpy(&p,ptemp,sizeof(SG_FLOAT)); 
				*msg = (MATHTYPE)p; 
			} 
			break; 
		case SG_FIELDTYPE_FLOAT: 
			{ 
				SG_DOUBLE p; 
				memcpy(&p,ptemp,sizeof(SG_DOUBLE)); 
				*msg = (MATHTYPE)p; 
			} 
			break;
		default: 
			return false; 
		} 
		return true;
	}

    SG_BOOL	GetAt(SG_SHORT col,SG_CHAR*);
	SG_BOOL GetAt(SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_SHORT col,CSgString &msg);

protected:

	void SafeSetChar(SG_CHAR*pAddress,const SG_CHAR*pInStr,SG_INT LimitLen);
	void SafeSetVarChar(VarCharAddress*pAddress,const SG_CHAR*pInStr,SG_INT LimitLen);
	//
protected:
	
	CSgTableInfo*		m_pTableInfo;
	CVarCharContainer*&	m_pVarChars;
	char*				m_pStart;
};

class _DATASET_DLL_EXPORT_ CSgDataSet:public CSgTableInfo,public CHashObjIndex,public CObjLock_RCS,public RefCountNoLock
{
public:
	
    CSgDataSet();
	
    virtual ~CSgDataSet();
	//---���ʵ������
	
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_NORMAL;}
	//����CSgDataSetʵ��
	static CSgDataSet* CreateInstance();

public:
	//�������ݼ��������ɵļ�¼����
	SG_BOOL SetRecordSize(SG_UINT size);
	SG_UINT	GetRecordSize(){ return m_RecordSize; }
	//�����ڴ棬����KeepRecordNums����¼�Ĵ洢�ռ�
	//������ΪӦ�ô����Ч�ʣ��÷������������ݼ������Ĵ���
	virtual	SG_BOOL	PackMemSize(SG_UINT KeepRecordNums);
	//���ü�¼����
	
    virtual SG_BOOL SetRecordNums(SG_UINT nums);
	//���ü�¼���� --- ���ܷ�������ϵ���Ӽ�¼
	
	SG_BOOL AutoAddReacorNums(SG_INT*pAddNums=0);
	/*
	 *	����У�Է���
	 *	�����:   PosΪ������ڴ���У�DataSetΪ�洢�����ݵ����ݼ���rowΪ�����ݶ�Ӧ����pDataSet�е��к�
	 *  �������: ModiAttrib�ĳ�ʼ���ڵ��ô����У�Check�Ĺ���ֻ��λ�����
	 *  ����ֵ��  ������ܽ���Ϣ��ModiAttrib�У����changeflagλ��ʶ������ϸ
	 *  �Ż����ܷ�����ѭ������ʱ���ڵ��ô�ѭ��������һ��CSgObjects��������ΪIndex�������������������ݼ��Ľṹ��Ӧ��Ϣ
	 */
	SG_BOOL CheckChangeFlag(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*Index=NULL);
	SG_BOOL CheckChangeFlag(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*pFields1,CSgObjects*pFields2);
	/*
	 *	����У�Է���������ȷ�������ݼ��ṹ��ȫһ�µ�����µ���
	 */
	SG_BOOL CheckChangeFlag_Same(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib);
    /*
     * �������ݲ����׼SQL���
     */
	
    SG_CHAR* CreateInsertStr(SG_UINT recno, SG_CHAR * tablename);
    /*
     * �������ݸ��ı�׼SQL��䣬
	 �������pwhere��Ϊ�գ����ص�Sql�������������Ӿ���Ϊ����
		�������Ӧ�ô���֪�����򣨻�������ƣ�KeyWord��Ϊ�գ����ص�Sql������������KeyWord��������
			���������ݼ����������������
	�����������޸�
     */
	
    SG_CHAR* CreateUpdateStr(SG_UINT recno, SG_CHAR* KeyWord, SG_CHAR* tablename, SG_CHAR* pwhere);
    /*
     * ��������ѡ���׼SQL��� select fieldname from tab
     */
	
    SG_CHAR * CreateSelectStr(SG_CHAR * tablename);
	//

	// --- ���(�ͷ�)����
	
	void Reset();
	// --- �ͷ�VarCharռ���ڴ�
	
	void ReleaseVarChar(SG_UINT start,SG_UINT nums);
	// --- ������
	
	void Pack();
	/*���Ʊ���Ϣ,��¼����Ϊ0
	  �����:FullDataSetFlag��SgGIS�е��ض��÷�,��BaseAttrib���е�
			m_pGeoDataSet����SDE�е����Խṹ�ͱ�ע�ֶ�������϶���,�����Ϊfalseʱֻ���SDE���Ա���Ϣ
	*/
	
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,SG_BOOL FullDataSetFlag=true);
	//UseSrcTblOrder=true  ���ɵļ�¼�����ֶ�˳���Դ����ͬ,����selfields��˳��
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,CSgObjects &selfields,SG_BOOL UseSrcTblOrder=true);
	/*
		����start�� nums ����¼�����ݼ�
		start>=��¼�� �� nums<1 ֻ���Ʊ���Ϣ
	*/
	
	virtual void CopyDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,CSgObjects &rows);
	
	/*
	  ������չ����Ϣ,��¼����Ϊ0
	*/
	
	void CopyExtTableInfo(CSgDataSet &srcDataSet);
	
	void SetExtFieldAttrib(SG_BOOL Flag);
	/*
		����start�� nums ����¼����չ�������ݼ�
		start>=��¼�� �� nums<1 ֻ���Ʊ���Ϣ
	*/
	
	void CopyExtDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);

	//��������DataSet
	
	void operator=(CSgDataSet &srcDataSet);
	//�Ƚ����ݼ�pDataSet�뱾���ݼ��Ĺ�ϵ
	//	=0��һ�� =1��ȫһ�� =2�����ݼ�����pDataSet =3pDataSet���������ݼ�
	
	SG_UCHAR CompareTableInfo(CSgDataSet *pDataSet);

	//�Ƚϱ����ݼ��ı�ṹ�Ƿ�������ݼ�pDataSet,�����ֶε�˳���ID�ֶ�
	//	=0��һ�� =1��ȫһ�� =2�����ݼ�����pDataSet =3pDataSet���������ݼ�
	
	SG_UCHAR CompareTableInfoIgnoreOrder(CSgDataSet *pDataSet);

	//���pRow=NULL�������л�������¼��,����ֻ���л�pRow����ָ�кŶ�Ӧ�ļ�¼
	//��ṹ��Ϣֻ����һ��
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	//�����л���¼���������ݣ�
	
	SG_BOOL SerializeRecord(CSgArchive&ar,SG_INT row);
	//����������л�
	
	SG_BOOL BaseClassSerialize(CSgArchive&ar,CSgObjects*objs=NULL){
		return CSgDataSet::Serialize(ar,objs);
	}

	SG_BOOL Sort(CSgString &strFields,bool asc=true);

public:

	SG_BOOL SetAt(SG_INT row,SG_SHORT col,SG_UCHAR*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_SHORT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_USHORT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_INT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_UINT*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_INT64*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_UINT64*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_DOUBLE*msg);
	SG_BOOL	SetAt(SG_INT row,SG_SHORT col,SG_FLOAT*msg);

	//�洢������ʼ--���к�/�к�
    SG_BOOL	SetAt(SG_INT row,SG_SHORT col,const char*);
	SG_BOOL SetAt(SG_INT row,SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL SetAt(SG_INT row,SG_CHAR *col,void *p,SG_UINT len);

	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UCHAR*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_SHORT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_USHORT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_INT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UINT*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_INT64*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_UINT64*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_DOUBLE*msg);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_FLOAT*msg);

	SG_BOOL GetAt(SG_INT row,SG_SHORT col,SG_CHAR *);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_INT row,SG_CHAR *col,void *p,SG_UINT len);
	SG_BOOL GetAt(SG_INT row,SG_SHORT col,CSgString &msg);

	SG_BOOL Get(SG_INT row,SG_CHAR *fieldname,CSgString &msg);
	//����ֶ����ݣ�����ɾ��ʱ������
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_CHAR*msg);
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_UCHAR &msg);
	SG_BOOL SetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_UCHAR &msg);
	SG_BOOL GetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_LONG &msg);
	SG_BOOL SetAt_IgnoreDel(SG_INT row,SG_SHORT col,SG_LONG &msg);
	
	//��ȡ������ʼ--���к�/�ֶ���	
	template <class T>
	SG_BOOL Get(SG_INT row,SG_PCSTR fieldname,T *con)	
	{															
		SG_INT col = GetFieldPtr(fieldname);					
		if(col<0)return false;									
		return GetAt(row,col,con);								
	}		
	//��ü�¼�׵�ַ
	//SG_CHAR *GetRecordHeadPos(SG_UINT row);
	//����������׵�ַ
	//const SG_CHAR* GetContent();
	
public:
	//SgGIS�����ڿ����Դ���
	//����"��������"��������
	
	void SetControlAttrib(ObjType_IA_Cfg_Struct type);
	//���"��������"��������
	
	inline ObjType_IA_Cfg_Struct *GetControlAttrib(){return &m_ObjControlAttrib;}
	//���ü�¼�Ƿ����
	
	void SetRecordUseAble(const SG_UINT row,SG_BOOL flag);
	//��ü�¼�Ƿ����
	
	SG_BOOL GetRecordUseAble(const SG_UINT row);
	//�ڿ�����
	
	void SetInsideAttrib(const SG_UINT TargerRow,const SG_UINT SourceRow);
	//����"����ʵ��"��������
	
	void SetControlAttrib(const SG_UINT row,ObjAttribStruct_Base *p);
	//���"����ʵ��"��������
	
	ObjAttribStruct_Base *GetControlAttrib(const SG_UINT row);
	
	ObjAttribStruct_Ext *GetControlAttribExt(const SG_UINT row);
	/*ά����ר�÷���*/
	//���ö���Ϊ�����ڶ��� �������FLAG����Insideλ��Ϊflag����ֵ
	
	void SetObjInside(SG_INT row,SG_BOOL flag);
	//��FLAG�ֶ��е�ǰ�������ݿ�����λ���� inside ����
	
	void ValueToInside(SG_INT row);
	//��FLAG�ֶ��е�ǰ�������ݿ�����λ���� inside ����
	//---��λUseItFlag
	
	void ValueToInside(SG_INT row,SG_SHORT col);
	//���ڿؽṹ�е�״ֵ̬д��Flag�ڴ��ֶ�
	
	void InsideStatusToFlag();
	//�����ʼ���˶���
	
	SG_NODEINT GetFNode(SG_INT row);
	//�����ֹ���˶���
	
	SG_NODEINT GetTNode(SG_INT row);
	// --- �����в�Ψһ���ݵļ�¼ѡ������dataset
	// ���:FieldsΪ������ֶ�
	// --- ע��:�÷����н���������ǿ����ΪSG_B_Feature_NULL
	
	void GetDupContent(CSgObjects&Fields,CSgDataSet&dataset);

	// --- ��ȫ����
	// --- ���Flag�����ֶε���ֵ
	
	void SafeFlagField(SG_INT row);

	//�����������ԡ���ϵͳ�ض����� --- BackLenΪ��Ҫ����ԭ����չ����ֵ�ļ�¼��
	
	void BuildControlAttrib(SG_UINT BackLen);

public:
	/*********************************************************
			SgGIS ��չӦ��----����һ�������ݼ��Ĺ���
	*********************************************************/
	//���ƥ���¼���к�,�����ֶ�Ϊ����,����ֵΪ����,���ص�һ��ƥ��ļ�¼,-1Ϊû���ҵ�
	//		startpos ��������ʼ�к�,ȱʡֵΪ0
	//�÷������Զ�λ���������ݼ��г���ĳһ��ֵ����ʼλ��.
	
	SG_LONG GetFetchRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);

	SG_BOOL GetFetchRows(SG_USHORT fieldpos,SG_LONG fieldvalue,CSgObjects&RetRows);

	//��ú�ָ������ȵļ�¼���ݣ���������������������ң�������GetFetchRow����к�
	SG_LONG GetMatchingRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);

	SG_BOOL GetMatchingRows(SG_USHORT fieldpos,SG_LONG fieldvalue,CSgObjects&RetRows);

	//���ƥ���¼���к�,�����ֶ�Ϊ�ַ�������,����ֵ�ַ���,���ص�һ��ƥ��ļ�¼,-1Ϊû���ҵ�
	//		startpos ��������ʼ�к�,ȱʡֵΪ0
	//�÷������Զ�λ���������ݼ��г���ĳһ��ֵ����ʼλ��.
	
	SG_LONG GetFetchRow(SG_USHORT fieldpos,SG_CHAR* fieldvalue,SG_LONG startpos=0);
	//����ֶζ�λ���ֶ���ֵһһ��Ӧ
	SG_LONG GetFetchRow(CSgObjects&FieldPos,CSgObjects&FieldVal,SG_LONG startpos=0);
	//��ò�ƥ���¼���к�,�����ֶ�Ϊ����,����ֵΪ����,���ص�һ����ƥ��ļ�¼,-1Ϊû���ҵ�
	//		startpos ��������ʼ�к�,ȱʡֵΪ0
	//�÷������Զ�λ���������ݼ��г�����һ��ֵ����ʼλ��.
	
	SG_LONG GetNotFetchRow(SG_USHORT fieldpos,SG_LONG fieldvalue,SG_LONG startpos=0);
	//�������ɸ����ݼ���Where�Ӿ�
	
	void SetWhereWord(const char *word){m_WhereWord=word;}
	
	CSgString& GetWhereWord(){return m_WhereWord; }
	//��չ��������Ϣ,����������AddFieldNums����,��׷������Ϊ������(ExtAttribFlag=true)
	
	virtual void ExtendFieldInfo(SG_INT AddFieldNums,CSgFieldInfo *dtfmt);
	//���ö��󳤶� --- ϵͳ������
	
	void SetObjLen(SG_INT row,SG_DOUBLE len);
	//���ݶ����ID��ö�����к� --- SafeCheck����������ͨ�������޷�����кź��Ƿ�������м�¼
	
	SG_LONG GetObjRow(SG_LONG oid,SG_INT startrow=-1,SG_BOOL SafeCheck=true);
	//
	
	SG_BOOL GetObjRows(SG_LONG oid,SG_SHORT fieldPtr,CSgObjects&rows,SG_BOOL SafeCheck=true);

	//���ݶ����KID��ö�����к�
	SG_LONG GetArcGisObjRow(SG_LONG kid,SG_INT startrow=-1,SG_BOOL SafeCheck=true);
	//�ж�������¼���е����˶����ֶε������Ƿ�һ��
	
	SG_BOOL TopNodeSame(SG_LONG row1,CSgDataSet*pDataSet2,SG_LONG row2);
	//�ж�������¼���е�GisID�ֶε������Ƿ�һ��
	
	SG_BOOL GisIDSame(SG_LONG row1,CSgDataSet*pDataSet2,SG_LONG row2);
	/*
	 *  ���ܣ�	  ���Ӽ�¼��ͬ��ά������                                    
	 *	ʹ�÷�Χ���ͻ��ˡ�����ˡ�PubServer��Ӧ�ø÷����д���ʽ����ȫһ��
	 *  ����ֵ�������������к�
	 */
	SG_LONG PostAdd(CSgDataSet*pSrcDataSet,SG_LONG SrcRow);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	������������ṹ���ܲ���ȫһ�£�ͬ���ֶν����޸�
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void UpdateUseName(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	������������ṹ��Ҫ��ȫһ��
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void Update_Same(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	����������toSrcFieldPtr���õ�ǰ���ݼ����ֶε�Դ���ݼ����ֶεĶ�Ӧ��ϵ
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void Update_FieldIndex(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&toSrcFieldPtr,SG_BOOL MaintIndex=false,SG_BOOL ClearNoExistFieldFlag=true);
	//��srcPtrArray��ָ�����ֶθ���Ŀ��DATASET��destPtrArray��ָ�����ֶ�
	virtual void Update_FieldIndex2(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&srcPtrArray,CSgObjects&destPtrArray,SG_BOOL MaintIndex=false);
	
	//�ϲ����ص����ݼ�,���pPrimaryKeyField!=NULL ������ͻ�Ĳ��ܽ��кϲ�
	SG_INT UniteDataSet(CSgDataSet &SrcDatSet,CSgString *pPrimaryKeyField=NULL);
	//
	//׷�����ݼ�,�������ݼ�Ҫ��ṹ��ȫ��ͬ
	virtual SG_INT AppendDataSet(CSgDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	/*
	 *  ���ܣ�	  ɾ����¼��ͬ��ά������                                    
	 *	ʹ�÷�Χ���ͻ��ˡ�����ˡ�PubServer��Ӧ�ø÷����д���ʽ����ȫһ�� 
	 */
	void PostDelete(SG_LONG row);
		
	//�����������ȡ�����ݼ���ȫ�ֶ��Ӽ�
	//���ؽ��Ϊ�к�
	
	void GetSubDataSet(SG_STRING whereClause,CSgObjects &rows,SG_LONG startRow=0,SG_LONG endRow=-1);
	//�����������ȡ�����ݼ��Ĳ����ֶ��Ӽ�
	//pRtnDataSetΪ���ؽ�������ݼ����ô�����ʵ��,FieldsΪҪѡ����ֶ���","�ֿ�,��������ͬ"ȫ�ֶ��Ӽ�"����
	
	void GetSubDataSet(CSgDataSet*pRtnDataSet,SG_PCSTR Fields,SG_STRING whereClause,CSgObjects &rows);
	//�����������ȡ�����ݼ��Ĳ����ֶ��Ӽ�
	//FieldsΪҪѡ����ֶ�λ��,��������ͬ��
	
	virtual void GetSubDataSet(CSgDataSet*pRtnDataSet,CSgObjects&Fields,SG_STRING whereClause,CSgObjects &rows);
	
	//���������ֶε�λ�ú�ֵ����ȡ���������ļ�¼��
	void GetSubDataSet(int idxfieldptr,int val,CSgObjects &rows,unsigned char crt_idxflag=false);
	void GetSubDataSet(CSgObjects &IdxFields,CSgObjects &IntVals,CSgObjects &RetRows,unsigned char CrtIdxFlag=false);
	SG_BOOL GetRecordKeyFilter(int nRow,char*pSzKeyWhere,CSgStringArray&FieldArray);
	void PrintTblInfo(FILE *pFile=NULL);	

protected:
	//���ݵ�������ȡ�����ݼ����Ӽ�
	//�����:SelFlagΪѡ�б������,relation�����߼�����ϵ
	
	void GetSubSetByFilter(CSgFieldFilter*pSimpleFilter,CSgObjects &SelFlag,FIELD_CON_RELATION relation,SG_LONG startRow=0,SG_LONG endRow=-1);
	/*  �Ƚ��������ݼ����е������Ƿ�һ��
	*   Index=NULLʱ��ʾ�ṹһ�£�����Index�д洢�Ŵӵ�ǰ���ݼ��ֶε�pDataSet�ֶε�����
	 *	����ֵ��0���ޱ仯��1�����ڲ���
	 */
	SG_BOOL CompareContent(SG_INT Pos,CSgDataSet *pDataSet,SG_INT row,SG_MODI_MESSAGE &ModiAttrib,CSgObjects*Index=NULL);
	SG_BOOL CompareField(SG_INT row1,SG_INT field1,CSgDataSet *pDataSet2,SG_INT row2,SG_INT field2,SG_MODI_MESSAGE &ModiAttrib);
	SG_UCHAR *GetRecordPointer(int row);

public:
	/*
	 *	*******�������ʵ��*******
	 */
	//��������󶨶���ı�ͷ��Ϣ
	virtual CSgTableInfo*GetTableInfo();
	//������ݼ��� ��row�� �������� IndexField�ļ�ֵ
	virtual void *GetKeyValue(HashSetAndFields*p,SG_LONG row);
	//������ݼ��� ��row�� �������� IndexField�ļ�ֵ�ı���Ϣ
	virtual SG_BOOL GetKeyString(HashSetAndFields*p,SG_LONG row,SG_CHAR*pInfo);
	//������ݼ���¼����
	virtual	SG_UINT GetObjNums();
		
	//�������ռ�õ��ڴ�
	
	virtual void GetMemLen(MemUseCheck&mc);
	
	void GetVarcharInfo(VarcharStaticInfo&mc);
	// --- ��ñ����Ϣ����
	
	void GetTableInfoDescrib(CSgString &msg,SG_INT No);

	// --- ��ӡ��¼���е�row������
	
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
	//���ٶ�row�м�¼�Ķ�д
	
	void SetDebugRow(SG_LONG row);
#ifdef LOCALLIB_RECORD_CHECK
	//�鿴Row����Ϣ
	
	void DebugRow(SG_LONG row,SG_SHORT Col=0);
#endif

	//����
	virtual SG_CHAR *GetColumnHeadPos(SG_INT row,SG_SHORT col);
	virtual SG_CHAR *GetContent() { return m_pContent;}
	//
protected:

	virtual SG_BOOL SetRecordPointer(RecordBase& rb,int row,SG_SHORT& col,bool );
	//��ü�¼���׵�ַ
	
	

protected:
	//������ڿ�����
	class CControlAttribMan*m_pInsideContrlAttrib;
	//---DataSetռ�õĴ��䳤��
	
	SG_ULONG	m_DataSetLen;
	//
	//RecordBase* m_pRecordBase;

#ifdef LOCALLIB_RECORD_CHECK
	
	static SG_OBJECT m_RecordCheck;
#endif

	
    SG_BOOL CheckSafeRowCol(SG_UINT row, SG_USHORT col);

	
    SG_CHAR *	m_pContent;
#ifdef USE_UNIQUE_VARCHARCONTAINER
	
	static CVarCharContainer*m_pVarChars;
#else
	CVarCharContainer*m_pVarChars;
#endif

};


class _DATASET_DLL_EXPORT_ CDataSetLockMan
{
public:
	
	CDataSetLockMan(CSgDataSet*p,SG_BOOL ReadLock=true);
	
	~CDataSetLockMan();
protected:
	
	CSgDataSet*pDataSet;
};

//////////////////////////////////////////////////////////////////////////
//

class _DATASET_DLL_EXPORT_ GeoDataMan
{
public:
	
	GeoDataMan(){}
	
	virtual ~GeoDataMan(){};
	virtual SG_BOOL	CheckGeoChange(SG_UINT ptr,void *p)=0;
	virtual SG_BOOL SetGeometry(SG_UINT ptr,void*p)=0;
	
	virtual SG_BOOL SetGeometry(SG_UINT ptr,void*p,SG_BOOL &ChangeFlag)=0;
	
	virtual SG_BOOL IsNull()=0;
	
	virtual void Copy(GeoDataMan*pGeoData,SG_UINT size)=0;
	
	virtual void Serialize(CSgArchive&,SG_UINT size)=0;

	virtual void AppendData(CSgArchive&,SG_INT StartRow,SG_UINT ObjNum)=0;
	
	virtual void Serialize(CSgArchive&,SG_UINT size,CSgObjects*objs)=0;
	
	virtual SG_INT GetMemLen(SG_UINT size)=0;
	
	virtual void * GetGeometry(SG_UINT ptr)=0;
	
//	virtual SG_LONG FromShape(SG_UINT row,void*shape)=0;
	
//	virtual SG_LONG ToShape(SG_UINT row,void*shape,SG_UCHAR ft)=0;
	
	virtual void * GetInnerPtr()=0;
	
	virtual SG_BOOL Is3DGeo()=0;
	
	virtual SG_BOOL IsLine()=0;
};
//

template <typename TGeoClass>
class _DATASET_DLL_EXPORT_ GeoDataManT:public GeoDataMan
{
public:
	
	GeoDataManT(SG_UINT size){
		m_pGeoData = new TGeoClass [size];
	}
	
	virtual ~GeoDataManT(){
		if(m_pGeoData){
			delete [] m_pGeoData;
			m_pGeoData =NULL;
		}
	}
	
	SG_BOOL IsNull(){
		return !m_pGeoData;
	}
	SG_BOOL	CheckGeoChange(SG_UINT ptr,void *p)
	{
		if(!m_pGeoData) return false;
		return !(m_pGeoData[ptr]==*((TGeoClass*)p));
	}
	
	SG_BOOL SetGeometry(SG_UINT ptr,void *p){
		if(!m_pGeoData) return false;
		m_pGeoData[ptr]=*(TGeoClass*)p;
		return true;
	}
	
	SG_BOOL SetGeometry(SG_UINT ptr,void *p,SG_BOOL &ChangeFlag){
		if(!m_pGeoData) return false;
		if(m_pGeoData[ptr]==*((TGeoClass*)p)) return true;
		m_pGeoData[ptr]=*(TGeoClass*)p;
		ChangeFlag = true;
		return true;
	}
	
	void * GetGeometry(SG_UINT ptr){
		return &m_pGeoData[ptr];
	}
	
	void Copy(GeoDataMan*pGeoDataMan,SG_UINT size)
	{
		if(m_pGeoData&&pGeoDataMan){
			TGeoClass * p = (TGeoClass*)pGeoDataMan->GetInnerPtr();
			memcpy(m_pGeoData,p,sizeof(TGeoClass)*size);
			for(SG_UINT i=0;i<size;i++){
				p[i].SetMemPtrNull();
			}
		}
	}
	
	void Serialize(CSgArchive&ar,SG_UINT size)
	{
		for(SG_UINT i=0;i<size;i++)
			m_pGeoData[i].Serialize(ar);
	}
	void AppendData(CSgArchive &ar,SG_INT StartRow,SG_UINT ObjNum)
	{
		if(!ar.IsLoading())
			return;
		for(SG_UINT i=StartRow;i<StartRow+ObjNum;i++)
			m_pGeoData[i].Serialize(ar);
	};	
	void Serialize(CSgArchive&ar,SG_UINT size,CSgObjects *objs)
	{
		for(SG_UINT i=0;i<objs->ObjNums;i++){
			if(objs->pObj[i]>=size)continue;
			m_pGeoData[objs->pObj[i]].Serialize(ar);
		}
	}

	
	SG_INT GetMemLen(SG_UINT size)
	{
		SG_INT len=0;
		for(SG_UINT i=0;i<size;i++){
			len += m_pGeoData[i].GetStructLen();
		}
		return len;
	}
	//
/*	
	SG_LONG FromShape(SG_UINT row,void*shape){

		return m_pGeoData[row].FromShape(shape);
	}
	
	SG_LONG ToShape(SG_UINT row,void*shape,SG_UCHAR ft){
		return m_pGeoData[row].ToShape(shape,ft);
	}
*/
	
	void * GetInnerPtr(){
		return m_pGeoData;
	}
	
	SG_BOOL Is3DGeo(){
		return TGeoClass::Has3D();
	}
	
	SG_BOOL IsLine(){
		return TGeoClass::IsLine();
	}
protected:
	
	TGeoClass	* m_pGeoData;
};
class CSgDataSetArray_ObjOper;
class _DATASET_DLL_EXPORT_ CSgGeoDataSet:public CSgDataSet
{
public:
	
	//����CSgGeoDataSetʵ��
	static CSgGeoDataSet* CreateInstance();

	CSgGeoDataSet();
	virtual ~CSgGeoDataSet();

	//---���ʵ������
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_GEO;}

	//��¼row�Ƿ����
	virtual SG_BOOL IsLoad(int row){ return true;}
	//
public:
	//��ö���ļ��������ֶ���������ArcSDE���������ÿռ�����������Դ��Ч
	SG_PSTR	GetGeoFieldName(){return m_geoFieldName.GetSafeBuffer();}
	//���ü����ֶ���
	void		SetGeoFieldName(SG_PCSTR pFieldName){ m_geoFieldName = pFieldName; }
	//�����ڴ棬����KeepRecordNums����¼�Ĵ洢�ռ�
	SG_BOOL	PackMemSize(SG_UINT KeepRecordNums);
	//���ö��������
	
	virtual SG_BOOL		SetRecordNums(SG_UINT);
	//�Ƿ���м�������
	virtual SG_BOOL		HasGeometry();
	//ɾ����������
	virtual void		DeleteGeometry();
	//У�鼸�������Ƿ���
    virtual SG_BOOL	CheckGeoChange(SG_UINT ptr,void *pGeoMetry);
	//���ö���ļ�������
	virtual SG_BOOL	SetGeometry(SG_UINT ptr,void*p);
	//���ö���ļ������� --- ChangeFlag���������Ƿ�仯
	virtual SG_BOOL	SetGeometry(SG_UINT ptr,void*p,SG_BOOL &ChangeFlag);
	//��ö���ļ�������
	virtual void *	GetGeometry(SG_UINT ptr);
	//��ò������豸�ļ�������
	virtual void *	GetGeometry_IgnoreDel(SG_UINT ptr);
	//�Ƚϼ��������Ƿ����
	virtual SG_BOOL CompareGeometry(int row1,CSgGeoDataSet *pDataSet,int row2);
	//��ü�¼�������Եĵ�һ���㣬���PointNums��Ϊ�շ��ص�����
	SgPoint*GetRefPoint(SG_INT row,SG_INT*PointNums=NULL);
	//��ȡ�������Ե��ַ���
	
	SG_CHAR* GetGeometry_str(SG_UINT row,SG_INT&len,SG_CHAR*pCoords=0);
	//���reference
	
	virtual void GetCoordRefExtent(SgRect&rc){return;}
	//(��)�豸����������ȷ���ж�
	
	SG_BOOL IsObjInRefRange(void *pGeoMetry){return true;}
	//���pRow=NULL�������л�������¼��,����ֻ���л�pRow����ָ�кŶ�Ӧ�ļ�¼
	//��ṹ��Ϣֻ����һ��
	//�����������⣬��������������
	
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,SG_BOOL FullDataSetFlag=true);
	//UseSrcTblOrder=true  ���ɵļ�¼�����ֶ�˳���Դ����ͬ,����selfields��˳��
	virtual void CopyTableInfo(CSgDataSet &srcDataSet,CSgObjects &selfields,SG_BOOL UseSrcTblOrder=true);
	//�ж�һ����¼�Ƿ������ݼ���(ע����ṹ����һ��)
	//SG_BOOL IsObjIn(CSgGeoDataSet *pDataSet,SG_UINT row);
	//�����������ȡ�����ݼ��Ĳ����ֶ��Ӽ�
	//FieldsΪҪѡ����ֶ�λ��,��������ͬ��
	
	void GetSubDataSet(CSgGeoDataSet*pRtnDataSet,CSgObjects&Fields,SG_CHAR* whereClause,CSgObjects &rows);
	//GEODATASET�еļ���������3D��2D
	virtual SG_BOOL Is3DGeo();
	virtual SG_BOOL IsLine();
	//
	void Change3D_2D();	
	void Change2D_3D();
	//
	//׷�����ݼ�,�������ݼ�Ҫ��ṹ��ȫ��ͬ
	virtual SG_INT AppendDataSet(CSgGeoDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,SG_UINT start,SG_UINT nums=1);
	virtual void CopyDataSet(CSgDataSet &srcDataSet,CSgObjects &rows);
public:
	//SgGIS �����⴦��
	/*
		�� pAddDataSet ���ӵ����ݼ���
		ֻ�ܴ����������ݼ��ṹ��ȫһ�µ����,�б����������Ψһ�������ֶ�
		KeyFiledPos����Ψһ�������ֶ�λ��--��ΪУ����
		����Ĺ���Ϊ:�����Ƿ����ͬһ��¼,�����,��pAddDataSet�е�Ϊ׼
	*/
	
	SG_BOOL Add(CSgGeoDataSet *pAddDataSet,SG_UINT KeyFiledPos);
	/*
		���ܣ���pExtDataSet�ۺϵ����ݼ��У����ExtAttribFlag������λ
		Լ������ǰ���ݼ���pExtDataSet��ʶΪ�������ֶ����Ʊ���ͬ��������Ϊ�����ֶ�
		�������KeyFiledPosΪpExtDataSet�������ֶ�λ��
		�������:������Լ��ʱ���������κδ������ش���
				���pExtDataSet�е��������ݼ����Ѿ�����,��λExtAttribFlag����������Ƿ�ƥ�䣬��ƥ�䷵�ؾ�����Ϣ
				�����Ҫ������������ExtendFieldInfo����λExtAttribFlag
	*/
	
	SG_BOOL Combin(CSgDataSet *pExtDataSet,SG_UINT KeyFiledPos,CSgString*WarningInfo=NULL);
    //ɾ����¼�У���ά������
	int  DeleteRows(std::set<int,std::greater<int> > &delrows);
	int  DeleteRows(CSgObjects &delrows);

	SG_BOOL Is3DGeo_SDE(){ return m_bIs3D_SDE;}
	void Set3DGeo_SDE(SG_BOOL b){m_bIs3D_SDE = b; }
	
public:
//���Զ������Ч�ķ���
	//�Զ��������ID�ֶκ��������X1��Y1.....Sg��Yn�ֶ���Ϊ�Ƕ��㼸���ֶ�
	//��ö���ļ������Եĵ���������������Ӧ�����Զ���Ϊ�����ֶ�
	
	SG_INT GetPointNums();
	//�������ֶ�����ʸ������ǰ���Ǿ��м��ε��ֶΡ�����ȷ������������
	
	void Vector();
	//���������Ե����Զ�������������
	
	void UnVector();
	//���������Ϣ
	
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
	
public:

	//���reference
	virtual SgRect* GetCoordRef(){return NULL;}
	//	�ͷ���չ����
	virtual void FreeDynamicRecords( SG_UINT StartPos = 0 , SG_UINT Numbers = INT_MAX );

	//	�������ռ�õ��ڴ�
	virtual void GetMemLen(MemUseCheck&mc);

protected:

	SG_BOOL		m_bIs3D_SDE;			
	GeoDataMan * m_pGeoDataMan;
	CSgString m_geoFieldName;
};
typedef  CSgGeoDataSet CSgSdeGeoDataSet;

class  CSgLobData_NoFree
{
	SG_INT		m_LobLen;
	SG_INT		m_SpaceLen;
	void		*m_pLobDat;
public:
	CSgLobData_NoFree();
	~CSgLobData_NoFree();
	SG_BOOL Init();
	SG_BOOL Reset(SG_BOOL FreeFlag=true);
	SG_BOOL Append(const SG_CHAR *pContent,SG_INT nPieceLen);
	SG_BOOL SetSpaceLen(int Len);
	void Free();
	int GetLobLen();
	void *GetLobData();
	SG_BOOL  Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_ CSgLobData
{
	SG_INT		m_LobLen;
	SG_INT		m_SpaceLen;
	void		*m_pLobDat;
public:
	CSgLobData();
	~CSgLobData();
	SG_BOOL Init();
	SG_BOOL Reset(SG_BOOL FreeFlag=true);
	SG_BOOL Append(const SG_CHAR *pContent,SG_INT nPieceLen);
	SG_BOOL SetSpaceLen(int Len);
	void Free();
	int GetLobLen();
	void *GetLobData();
	SG_BOOL  Serialize(CSgArchive&ar);
};

#define CSGLOBDATASET_LOBTYPE_DATASET			1
#define CSGLOBDATASET_LOBTYPE_DATASETARRAY		2
class CSgDataSetArray;
class _DATASET_DLL_EXPORT_ CSgLobDataSet:public CSgGeoDataSet
{
public:
	
	//����CSgLobDataSetʵ��
	static CSgLobDataSet* CreateInstance();

	CSgLobDataSet();
	virtual ~CSgLobDataSet();
	//---���ʵ������
	virtual SG_UCHAR GetInstanceType(){return SG_DATASET_TYPE_LOB;}

	//��¼row�Ƿ����
	virtual SG_BOOL IsLoad(int row){ return true;}
	//
public:
	SG_BOOL HasLobData()
	{
		if(m_pLobDataArray==NULL)
			return false;
		if(m_pLobDataArray->size()<=0)
			return false;
		return true;
	};
	//���pRow=NULL�������л�������¼��,����ֻ���л�pRow����ָ�кŶ�Ӧ�ļ�¼
	//��ṹ��Ϣֻ����һ��
	//�����������⣬��������������
	virtual SG_BOOL Serialize(CSgArchive&ar,CSgObjects*objs=NULL);

	//�ж�һ����¼�Ƿ������ݼ���(ע����ṹ����һ��)
	//SG_BOOL IsObjIn(CSgGeoDataSet *pDataSet,SG_UINT row);
	//�����������ȡ�����ݼ��Ĳ����ֶ��Ӽ�
	//FieldsΪҪѡ����ֶ�λ��,��������ͬ��	
	void GetSubDataSet(CSgLobDataSet*pRtnDataSet,CSgObjects&Fields,SG_CHAR* whereClause,CSgObjects &rows);

	//��ȡĳ�У�ĳ�еļ�¼����
	SG_INT   GetLobLength(int RowNo,int ColNo);
	//��ȡĳ�У�ĳ�е��ڴ��   pContent:����õ��ڴ�� LobLen����¼�ڴ�pContent�ĳ���
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,void *p,SG_UINT len);
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSet &Dat);
	 SG_BOOL GetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSetArray &Dat);
	//����ĳ��ĳ�еļ�¼,���pContent==NULL,��ɾ�����и��еļ�¼����
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,void *p,SG_UINT len);
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSet &Dat);
	 SG_BOOL SetLobDat(SG_INT RowNo,SG_SHORT ColNo,CSgDataSetArray &Dat);
	//�ֿ��ȡĳ��ĳ�е�����   StartPt:���ζ�ȡ�����ݿ��ƫ��λ��   pContent:����õ��ڴ�� OnePieceLen����¼�ڴ�pContent�ĳ���
	//��������ֵ�����ζ�ȡ��ʵ���ֽ��������Ϊ-1��������Ѷ�ȡ���
	SG_INT  GetLobOnePiece(SG_INT RowNo,SG_SHORT ColNo,SG_INT StartPt,void *pContent,SG_INT OnePieceLen);
	//����ĳ��ĳ�еĿռ��С
	SG_BOOL SetLobDataSpaceSize(SG_INT RowNo,SG_SHORT ColNo,SG_INT SpaceLen);
	//�ֿ����ĳ��ĳ������� pContent:���η�����ڴ�� OnePieceLen�����η���ĳ���
	SG_BOOL SetLobOnePiece(SG_INT RowNo,SG_SHORT ColNo,void *pContent,SG_INT OnePieceLen);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	������������ṹ���ܲ���ȫһ�£�ͬ���ֶν����޸�
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void UpdateUseName(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	������������ṹ��Ҫ��ȫһ��
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void Update_Same(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,SG_BOOL MaintIndex=false);
	/*
	 *  ���ܣ�	  Update��¼����ͬ���޸�������
	 *	����������toSrcFieldPtr���õ�ǰ���ݼ����ֶε�Դ���ݼ����ֶεĶ�Ӧ��ϵ
	 *  �������  MaintIndex�����Ƿ�ͬ���޸�����
	 */
	virtual void Update_FieldIndex(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&toSrcFieldPtr,SG_BOOL MaintIndex=false,SG_BOOL ClearNoExistFieldFlag=true);
	//��srcPtrArray��ָ�����ֶθ���Ŀ��DATASET��destPtrArray��ָ�����ֶ�
	virtual void Update_FieldIndex2(SG_LONG TargetRow,CSgDataSet*pSrcDataSet,SG_LONG SrcRow,CSgObjects&srcPtrArray,CSgObjects&destPtrArray,SG_BOOL MaintIndex=false);
	//׷�����ݼ�,�������ݼ�Ҫ��ṹ��ȫ��ͬ
	virtual SG_INT AppendDataSet(CSgDataSet *pDatSet,SG_BOOL MaintIndex=false);
	virtual SG_BOOL AppendDataSet(CSgArchive &ar);
//	virtual SG_BOOL AppendDataSet(VECT_VOIDPT &ArList);
	virtual void PrintRecord(SG_LONG row,FILE *pFile=NULL);
private:
	SG_BOOL  Free();
protected:
	typedef std::map<S_TWOINT,CSgLobData_NoFree,CTwoIntLess> MAP_TWOINT_LOBDATA;
	MAP_TWOINT_LOBDATA	*m_pLobDataArray;
};

/************************************
	���ݼ����д�����
************************************/
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ TMyObjectsArray<CSgDataSet>;
#endif
class _DATASET_DLL_EXPORT_ CSgDataSetArray:public TMyObjectsArray<CSgDataSet>
{
public:
	virtual ~CSgDataSetArray();

	SG_BOOL IsObjExist(SG_PCSTR name,SG_INT *startpos=0);

	CSgDataSet *GetObj(SG_PCSTR name,SG_INT *startpos=0);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

class _DATASET_DLL_EXPORT_ CSgGeoDataSetArray:public CSgDataSetArray
{
public:
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

class _DATASET_DLL_EXPORT_ CSgVerGeoDataSetArray//:public CSgGeoDataSetArray
{
	CSgPtrArray VerIDArray;
	CSgGeoDataSetArray DataSetArray;
public:
	~CSgVerGeoDataSetArray()
	{
		RemoveAll();
	}
	void RemoveAll()
	{
		VerIDArray.RemoveAll();
		DataSetArray.RemoveAll();
	}
	CSgGeoDataSet *GetObj(int verid);
	CSgGeoDataSet *GetAt(int idx);
	int GetAt_VerID(int idx);
	int SetObj(int verid,CSgGeoDataSet *pDatSet);
	void Add(void *p,int verid);
	int GetSize() {return DataSetArray.GetSize();};
	
};

//DataSet������ʱ���ټ���
class _DATASET_DLL_EXPORT_ CSgDataSetArrayEx:public CSgPtrArray
{
public:
	//
	virtual ~CSgDataSetArrayEx();
	virtual void RemoveAll();
	SG_BOOL IsObjExist(SG_PCSTR name,SG_INT *startpos=0);
	CSgDataSet *GetObj(SG_PCSTR name,SG_INT *startpos=0);
	CSgDataSet *GetDataSetEx(SG_PCSTR name,SG_PCSTR lpszWhere);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
enum SG_OBJ_OPERTYPE
{
	SG_OBJ_OPERTYPE_INSERT			=1,
	SG_OBJ_OPERTYPE_UPDATE			=2,
	SG_OBJ_OPERTYPE_MERGE			=3,
	SG_OBJ_OPERTYPE_DELETE			=4,
	SG_OBJ_OPERTYPE_EXECSQL			=5,
	SG_OBJ_OPERTYPE_CRTTBL			= 6
};
//����������ݼ�����datasetnums+[opertype+dataset]+[opertype+dataset].....
class _DATASET_DLL_EXPORT_   CSgDataSetArray_ObjOper
{
	typedef struct COperDataSet
	{
		SG_INT m_OperType;
		CSgDataSet *m_pDataSet;
		COperDataSet()
		{
			m_OperType=0;
			m_pDataSet=NULL;
		};
	}CSgOperDataSet;
	typedef std::vector<CSgOperDataSet > VECT_OPERDATASET;
	VECT_OPERDATASET	m_DataSetArray;
public:
	CSgDataSetArray_ObjOper()
	{

	}
	~CSgDataSetArray_ObjOper()
	{
		RemoveAll();
	}
	void RemoveAll();
	SG_INT GetOperType(int no);
	CSgDataSet *GetAt(int no);
	void Add(int OperType,CSgDataSet *p);
	int GetSize();
	int SetAt(int no,int OperType,CSgDataSet *pDatSet,int FreeOldDatFlag=true);
	//���MallocNewDatSetFlag=false�������Դ���ݼ�
	int CopyDataSetArray(CSgDataSetArray_ObjOper &SrcDatSetArray,int MallocNewDatSetFlag=true);
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_   CSgDataSetArray_ObjDBOper
{
	typedef struct CDBOperDataSet
	{
		SG_SHORT m_OperType;
		SG_SHORT m_DBNo;
		CSgDataSet *m_pDataSet;
		CDBOperDataSet()
		{
			m_OperType=0;
			m_DBNo=1;
			m_pDataSet=NULL;
		};
	}CDBOperDataSet;
	typedef std::vector<CDBOperDataSet > VECT_DBOPERDATASET;
	VECT_DBOPERDATASET	m_DataSetArray;
public:
	CSgDataSetArray_ObjDBOper()
	{

	}
	~CSgDataSetArray_ObjDBOper()
	{
		RemoveAll();
	}
	void RemoveAll();
	SG_SHORT GetOperType(int no);
	SG_SHORT GetDBNo(int no);
	void SetDBNo(int no,SG_SHORT DBNo);
	CSgDataSet *GetAt(int no);
	void Add(SG_SHORT DBNo,SG_SHORT OperType,CSgDataSet *p);
	int GetSize();
	virtual SG_BOOL Serialize(CSgArchive&ar);
};
class _DATASET_DLL_EXPORT_ CDataSetSortFunc
{
public:
	CDataSetSortFunc(CSgDataSet *pDataSet,CSgString &Fields,SG_BOOL Ascend=true);
	CDataSetSortFunc(CSgDataSet *pDataSet,VECT_INT &FieldPtrs,SG_BOOL Ascend=true);
	bool operator()(const int RcdNo1,const int RcdNo2);
private:
	CSgDataSet *m_pDataSet;
	VECT_INT	m_CmpFieldPtr;
	SG_BOOL		m_Ascend;
};


#endif /* CSgDataSet_h */
