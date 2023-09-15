
#ifndef _NET_DEF_H_
#define _NET_DEF_H_
#include "sgConst.h"
#include "VersionDefines.h"
#include "csgdataset.h"
#include "NetCommand.h"
#include "command/GdbCommand.h"

/**********************************************************************
	���Ķ�����ռ�������ͨ����ع��ܺź���ؽṹ
	Part	1:		ָ���
	Part	2:		
**********************************************************************/
//********************ָ���ʼ*******************//


//********************ָ������*******************//

enum GDBSRV_STATUS
{
	gdbsrv_status_normal		=0,
	gdbsrv_status_exception	=1,
	gdbsrv_status_backup		=2
};
//********************ָ���*******************//

struct SG_CORE_API ClientRequestUserInfo
{
	
	ClientRequestUserInfo();
	virtual ~ClientRequestUserInfo();
	
	SG_BOOL		ModiByApp;	// --- ��Ӧ�ýӿ��޸ı�ǣ������봫�ݣ�
	SG_ULONG	Company;	// --- �û��Ĺ�˾��Ϣ
	SG_ULONG	UserID;		// --- ������û�

	virtual SG_BOOL Serialize(CSgArchive&ar);
};

// --- ���������������
/*enum version_status_goto
{
	vlm_ask_run_ver      =0,
	vlm_same_ver_downto_up,
	vlm_same_ver_upto_down,
	vlm_diff_ver_goto,
	vlm_run_to_edit
};
*/
/************************************************************************/
/*                  �ռ���������ͨ������ṹ		                    */
/************************************************************************/
struct SG_CORE_API S_SgNetCommandHead:public CNetCmdHead
{
	SG_UINT		VerNo;			//���а桢�༭�桢�滮��
//	SG_UINT		Reserve;	//Ԥ��
	S_SgNetCommandHead()
	{
		VerNo		= 0;
	};
//	SG_BOOL CheckVersion();
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	
};
/************************************************************************/
/*						�ռ����������������		                    */
/************************************************************************/
struct S_SgNetCommandPara
{
	virtual SG_BOOL GetTaskList(CSgObjects**TaskList)=0;
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1)=0;
};
/************************************************************************/
/*                  �ռ��������󷵻ز�������		                    */
/************************************************************************/
struct S_SgNetCommandRtn
{
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1)=0;
};

struct SG_CORE_API Ver_ObjInfoRequestPara
{
	CSgString	TableName;		//����
	CSgString	FieldName;		//�ֶ���
	CSgString	WhereClause;	//����
	SG_INT		FeatureType;
	GIS_Schema	SchemeInfo;		//������Ϣ
	CSgLine		Range;

	Ver_ObjInfoRequestPara()
	{
		TableName="";
		FieldName="";
		WhereClause="";
		FeatureType=0;
	}
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno=-1);
};

struct SG_CORE_API ObjAttribRequestPara:public LoadControlPara,public CNetCmdHead
{
	
	//SG_UCHAR	VersionNo;		// --- �汾��
	CSgString	LocalName;		//���ؿ���
	CSgObjects	TaskList_base;	//ǰһ�����б���Ҫ��ID���ϣ�
	CSgObjects	TaskList;		//���������б���Ҫ��ID���ϣ�
	GIS_Schema	SchemeInfo;		//�滮����id
	
	SG_UCHAR	ReqGeometry;	// --- ��̬���ؼ���������
	SG_UCHAR    LoadFlag;       //����TaskList_base��TaskList�Ĵ���ʽ(version_status_goto)  
	SG_UCHAR	LoadType;		//	�������ͣ�1 ���ػ������ݡ�2 ��չ���ݡ�3 ȫ���� ���μ� LoadType ö�ٶ���	
	SG_UCHAR	Reserve2;	//Ԥ��
	
	ObjAttribRequestPara()
	{
		LocalName.Empty();

		TaskList_base.ClearObj();
		TaskList.ClearObj();

	//	VersionNo	= SG_NET_VERSION;
		ReqGeometry = true;
		LoadFlag	= cvsRequestRunVer;
		LoadType	= CLT_LOAD_ALL;
		Reserve2	= 0;
	}
	
	//SG_BOOL CheckVersion();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- �����������󷵻ز���

struct SG_CORE_API ObjAttribRequestReturnPara:public CNetCmdHead
{
	
	
	SG_UCHAR	HasGeometry;	// --- ���ص���Ϣ���Ƿ���м�������
	
	SG_UCHAR	NotRunVersion;	//�������ݲ������а汾����
	
	
	ObjAttribRequestReturnPara(){
		NotRunVersion=0;
	}
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};


struct SG_CORE_API ServerInfoRequestReturnPara:public ObjAttribRequestReturnPara
{
	union{
		SG_LONG ServerNo;
		SG_LONG FeatureLineID;
		SG_LONG FeatureStationID;
		SG_LONG GrpVerNo;
	};
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
};

// --- �����������������

struct SG_CORE_API TableContentRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
/*	SG_UCHAR	VersionNo;		// --- �汾��
	
	SG_UCHAR	Reserve0;	//Ԥ��
	
	SG_UCHAR	Reserve1;	//Ԥ��
	
	SG_UCHAR	Reserve2;	//Ԥ��
*/	
	CSgString	TableName;		//���� --- ������Ϊ��ʱ,WhereClause��Ϊ���������ݿ����Sql���
	
	CSgString	FieldName;		//�ֶ���
	
	CSgString	WhereClause;	//����
	
	CSgString	OrderField;		//�����ֶ�
	
	TableContentRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
	}
	
//	SG_BOOL CheckVersion();
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- �������������󷵻ز���

struct SG_CORE_API TableContentReturnPara:public CNetCmdHead
{
	
//	SG_UCHAR	VersionNo;		// --- �汾��
	SG_UINT		VerNo;			//����̬���༭̬���о�̬
	SG_UINT		TaskNo;			//--- �����
	
/*	SG_UCHAR	RtnValue;		// --- ������ȷ���Ǵ���
	
	SG_UCHAR	Reserve1;	//Ԥ��
	
	SG_UCHAR	Reserve2;	//Ԥ��
	
	CSgString	RtnInfo;	// --- ������Ϣ,��ȷʱΪ��,����ʱΪ������Ϣ
*/	
	TableContentReturnPara()
	{
		//VersionNo	=	SG_NET_VERSION;
		TaskNo=0;
		VerNo=0;
	}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

// --- ���ݿ�ִ��(Exec)�������

struct SG_CORE_API DbfExecuteRequestPara:public CNetCmdHead
{
	
//	SG_UCHAR	VersionNo;		// --- �汾��
	
	SG_UCHAR	Commit;			// --- �Ƿ��ύ
	
//	SG_UCHAR	Reserve1;	//Ԥ��
	
//	SG_UCHAR	Reserve2;	//Ԥ��
	
	CSgString	SqlWord;
	
	DbfExecuteRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
	}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- ���ݿ�ִ��(Exec)���ز���
typedef TableContentReturnPara ModiCommandReturnPara;

// --- SDE��ͨ���ȡ�������
typedef TableContentRequestPara SdeTableContentRequestPara;
// --- SDE��ͨ���ȡ���󷵻ز���
typedef TableContentReturnPara SdeTableContentReturnPara;
// --- ����������SDE���ȡ�������

struct SG_CORE_API SdeSpatialTableRequestPara:public TableContentRequestPara
{
	
	SdeSpatialTableRequestPara(){
		Flag = 0;
	}
	
	SG_INT	Flag;
	
	CSgLine Range;
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- ����������SDE���ȡ���ز���
typedef TableContentReturnPara SdeSpatialTableReturnPara;


// --- ��������������
struct SG_CORE_API InsertCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	InsertCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
		TaskNo=0;
	}
	
	//SG_UCHAR	VersionNo;		// --- ���ݸ�ʽ�汾��
	
	SG_UCHAR	Commit;			// --- �Ƿ��ύ
	
//	SG_UCHAR	Reserve1;	//Ԥ��
	
//	SG_UCHAR	Reserve2;	//Ԥ��
	GIS_Schema	SchemeInfo;		//�滮����id
	SG_UINT		TaskNo;			//--- �����
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}

	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- �޸�����������

struct SG_CORE_API UpdateCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	UpdateCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		GeometryValid = true;
		Commit = true;
		TaskNo=0;
		OperExtAttrib = false;
	}
	
//	SG_UCHAR	VersionNo;		// --- �汾��
	
	SG_UCHAR	Commit;			// --- �Ƿ��ύ
	
	SG_UCHAR	GeometryValid;	// --- ���������Ƿ���Ч
	
	SG_UCHAR	OperExtAttrib;	// --- �Ƿ��д̨����չ����
	CSgString	WhereClause;	//
	GIS_Schema	SchemeInfo;		//�滮����id
	SG_UINT		TaskNo;			//--- �����

	CSgObjects	TaskList;		//�͸���������ͬһ��汾�µ������б������ж���ͼ���Ƿ���������Ϊ GAP ������ݱ���
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
// --- ̨��ͬ���������
struct SG_CORE_API EmSyncRequestPara:public ClientRequestUserInfo
{
	EmSyncRequestPara()
	{
		TaskNo=0;
	}
	SG_UINT		TaskNo;			//--- �����
	SG_INT		OperType;	//��������(1-����,2-�޸�,3-ɾ��)
	SG_INT		ObjType;	//̨�ʸı�Ķ�������
	SG_INT		ObjID;		//̨�ʸı�Ķ���ID
	SG_INT		TableID;	//̨�ʸı�ı�id
	SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno);
};



// --- ̨��ͬ�����ݼ��������
struct SG_CORE_API EmSyncDatSetRequestPara:public ClientRequestUserInfo
{
	EmSyncDatSetRequestPara()
	{
		TaskNo=0;
	}
	SG_UINT		TaskNo;			//--- �����

	CSgDataSetArray_ObjOper	m_pObjs;				//�����������Ϣ
	SG_BOOL Serialize(CSgArchive&ar,SG_INT versionno);
};

/*struct SG_CORE_API Ver_PierceRequestPara:public ClientRequestUserInfo
{
	
	CSgGeoDataSet DatSet;
	SG_BOOL Serialize(CSgArchive&ar,SG_INT version=SG_NET_VERSION);
};
*/
// --- ɾ������������

struct SG_CORE_API DeleteCommandRequestPara:public ClientRequestUserInfo,public CNetCmdHead
{
	
	DeleteCommandRequestPara(){
	//	VersionNo	=	SG_NET_VERSION;
		Commit = true;
		TaskNo=0;
	}
	
//	SG_UCHAR	VersionNo;		// --- �汾��
	
	SG_UCHAR	Commit;			// --- �Ƿ��ύ
	
//	SG_UCHAR	Reserve1;	//Ԥ��
	
//	SG_UCHAR	Reserve2;	//Ԥ��
	
	GIS_Schema	SchemeInfo;		//�滮����id
	SG_UINT		TaskNo;			//--- �����
	CSgObjects	TaskList;		//�͸���������ͬһ��汾�µ������б������ж���ͼ���Ƿ�������
	CSgString	TableName;		// --- ����
	
	CSgObjects  Objs;			// --- ArcGisID
	
	CSgString	WhereClause;	// --- ��ArcGisID����
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};
//�汾�ύ��ع��Ĳ���
struct SG_CORE_API	CommitVersionPara:public ClientRequestUserInfo,public CNetCmdHead
{
	CommitVersionPara(){
//		VersionNo	=	SG_NET_VERSION;
		Commit = true;
	}
	SG_UCHAR	VersionNo;		// --- �汾��
	SG_UCHAR	Commit;			// --- �Ƿ��ύ	
	SG_UCHAR	Reserve1;	//Ԥ��
	SG_UCHAR	OnlyCheckPoint;	//���������������
	GIS_Schema	SchemeInfo;		//�滮����id
	CSgObjects	TaskList;			//�༭�����
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

//�������豸�������IDͬ��

struct SG_CORE_API SYNC_ID_CHANGE 
{
	
	SG_SHORT ObjType;
	
	SG_INT ObjID_old;
	
	SG_INT ObjID_new;
	
	void Serialize(CSgArchive&ar);
};
// --- ������ʽ������������ṹ
class CSgDataSet;
class CSgGeoDataSet;
class CSgDataSetArray;
class CSgGeoDataSetArray;

struct ObjTransModiStruct
{
	
	ObjTransModiStruct();
	
	~ObjTransModiStruct();
	// --- ���Ӵ�����ֶ�
	
	void AttribFieldChange(SG_SHORT col);
	// --- ���е��ֶζ�����
	
	void AttribFieldChangeAll();
	//
	
	SG_BOOL GetAttribFieldChangeAll();
	
	CSgObjects *GetChangeFields(){return ChangeField;}
public:
	
	SG_UCHAR	GeoMetryOnly;	//GeoMetryOnly ����������CSgGeoDataSet�е���������(�����в�����������������)
	
	SG_UCHAR	HasGeoMetry;	//�Ƿ�������Ƿ���������,�������������������ʱ���Լ����ֶν��в���
protected:
	
	CSgObjects*	ChangeField;	//�����ŵ�����Ҫ�ı���ֶε�λ����(��������в�����û�иı����Ϣ)
};

class CObjModel;
#define VER_SRVSYNCMAIL_OPERTYPE_EDIT		0		//�ɱ༭�����ͬ��
#define VER_SRVSYNCMAIL_OPERTYPE_ROLLBACK   1		//�ɻع������ͬ��
#define VER_SRVSYNCMAIL_OPERTYPE_COMMIT		2		//���ύ�����ͬ��
class SG_CORE_API ObjTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	ObjTransManager();
	virtual ~ObjTransManager();
	
public:
	// --- ����������
	
	void Reset();


	// --- ���ӵĶ���������
	virtual SG_BOOL ObjAdd(CSgGeoDataSet*pDataSet,SG_LONG row);
	// --- ��pDataSet�е����г�Ա�������������
	virtual SG_BOOL ObjsAdd(CSgGeoDataSet*pDataSet);


	// --- �޸ĵĶ���������
	virtual SG_BOOL ObjModi(CSgGeoDataSet*pDataSet,SG_LONG	row,ObjTransModiStruct&modiattrib,SG_BOOL bOrigin=false);
	// --- ��pDataSet�е����г�Ա�������������
	virtual SG_BOOL ObjsModi(CSgGeoDataSet*pDataSet,SG_BOOL bOrigin=false);


	// --- ɾ���Ķ���������
	//RecAllAttrib	Ϊtrueʱ�����е����Լ�¼���������ھ��пɴ洢�߳���Ϣ�Ķ��󽫸߳���Ϣ��¼����
	//				Ϊfalse
	virtual SG_BOOL ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row,SG_BOOL RecAllAttrib=false);
	// --- ��pDataSet�е����г�Ա�������������
	virtual SG_BOOL ObjsDelete(CSgGeoDataSet*pDataSet);

	/******************��������еĶ���**************************
	��Σ�
	   inObjType --�豸���ͣ� pTableName--����ı���
	   inObjID	 --�豸ID
	   nEditFlag --�μ���ö��ֵ���壬������SG_NET_ATTRIB_CREATE	=4,
									�޸�	��SG_NET_ATTRIB_MODIFY	=5,
									ɾ����SG_NET_ATTRIB_DELETE	=6,
    ���Σ�
	    outRow --�ö����ڷ���DATASET�е��к�
	����ֵ��
	    �ö������ڵ�DATASET,���û�У��򷵻�NULL
	**************************************************************/
	virtual CSgGeoDataSet*GetTransObj(SG_SHORT inObjType,SG_INT inObjID,SG_SHORT nEditFlag,SG_INT&outRow);
	//
	virtual CSgGeoDataSet*GetTransObj(char* pTableName,SG_INT inObjID,SG_SHORT nEditFlag,SG_INT&outRow);

	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	//
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	//
	
	CSgObjects* GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgGeoDataSetArray* GetOperDataSetArray(){return m_pObjs;}
	
	
public:
	
//	SG_UCHAR	VersionNo;		// --- �汾��
	
	
	SG_UCHAR	MixFlag;	//0: Ϊ��һ�༭̬������̬��Ϣ  
							//1:���б༭̬��ϢҲ������̬��Ϣ,������������ͬ��ʱ�����
	
	SG_UCHAR	PierceFlag;	//��͸��־

	
	SG_UCHAR	Reserve2;	//Ԥ��
	//
	GIS_Schema	SchemeInfo;		//�滮����id
	SG_UINT		TaskNo;			//--- �����
	CSgObjects	TaskList;		//�͸���������ͬһ��汾�µ������б������ж���ͼ���Ƿ�������
protected:	
	
	CSgObjects			m_ObjsOperAttrib;		//����(��¼)��������
	
	CSgGeoDataSetArray*	m_pObjs;				//�����������Ϣ
};

// --- ������ʽ����������Ӧ�ṹ

class SG_CORE_API ObjTransReturnStruct:public ModiCommandReturnPara
{
public:
	
	ObjTransReturnStruct();
	~ObjTransReturnStruct();

	// --- ������������
	
	void SetSize(SG_INT Nums);
	// --- ���ӵĶ���������
	
	void ObjAdd(CSgGeoDataSet*pDataSet,int row=-1);
	// --- �޸ĵĶ���������
	
	void ObjModi(CSgGeoDataSet*pDataSet,int row=-1);
	// --- ɾ���Ķ���������
	
	void ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row);
	//
	
	CSgObjects *GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgGeoDataSetArray* GetOperDataSetArray(){return m_pObjs;}

	
	SG_BOOL Serialize(CSgArchive&ar);

	void Reset();

protected:
	
	CSgObjects			m_ObjsOperAttrib;		//����(��¼)��������
	
	CSgGeoDataSetArray*	m_pObjs;				//�����������Ϣ
};

class ACE_Thread_Mutex;

class SG_CORE_API ObjNetSendStruct:public ObjTransManager
{
public:
	
	ObjNetSendStruct();
	
	~ObjNetSendStruct();
	
	void Reset();
	
	void ObjAdd(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	void ObjModi(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	void ObjDelete(CSgGeoDataSet*pDataSet,SG_LONG row,SG_INT MailFlag,SG_INT verno=0,unsigned char pierceflag=0);
	
	CSgObjects *GetObjsMailFlag(){return &m_ObjsMailFlag;}
	//
	
	SG_BOOL Split(CSgPtrArray&ObjsArray);
	//
protected:
	
	void Lock();
	
	void UnLock();
	
	CSgObjects			m_ObjsMailFlag;
	CSgObjects			m_ObjsPierceFlag;
	CSgObjects			m_ObjsVerNo;	
	
	ACE_Thread_Mutex*	m_Lock;
};


class SG_CORE_API DbfTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	DbfTransManager();
	
	~DbfTransManager();
public:
	// --- ����������
	
	void Reset();
	// --- ���ӵĶ���������
	
	SG_BOOL ObjAdd(CSgDataSet*pDataSet,SG_LONG row);
	// --- �޸ĵĶ���������
	
	SG_BOOL ObjModi(CSgDataSet*pDataSet,SG_LONG row,ObjTransModiStruct&modiattrib);
	// --- ɾ���Ķ���������
	
	SG_BOOL ObjDelete(CSgDataSet*pDataSet,SG_LONG row);
	//
	
	SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	//
	
//	SG_BOOL CheckVersion()
//	{return SG_NET_CHECKVERSION(VersionNo);}
	//
	
	CSgObjects* GetObjsOperAttib(){return &m_ObjsOperAttrib;}
	//
	
	CSgDataSetArray* GetOperDataSetArray(){return m_pObjs;}

public:
	
/*	SG_UCHAR	VersionNo;		// --- �汾��
	
	SG_UCHAR	Reserve0;	//Ԥ��
	
	SG_UCHAR	Reserve1;	//Ԥ��
	
	SG_UCHAR	Reserve2;	//Ԥ��
*/
	//
protected:	
	
	CSgObjects			m_ObjsOperAttrib;		//����(��¼)��������
	
	CSgDataSetArray*	m_pObjs;				//�����������Ϣ
};
//

class SG_CORE_API DbfNetSendStruct:public DbfTransManager
{
public:
	
	void Reset();
	
	void ObjAdd(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	void ObjModi(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	void ObjDelete(CSgDataSet*pDataSet,SG_LONG row,SG_INT MailFlag);
	
	CSgObjects *GetObjsMailFlag(){return &m_ObjsMailFlag;}
protected:
	
	CSgObjects			m_ObjsMailFlag;
};


class SG_CORE_API CommTransManager:public ClientRequestUserInfo,public CNetCmdHead
{
public:
	
	CommTransManager();
	
	~CommTransManager();
	
	void ReSet();
	//�ռ��������� dataType:0-SDE������;1-ORACLE���е�����
	
	void AddSqlClause(CSgString sqlClause);	
	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
	
	char*	GetErrorInfo(){return m_ErrorInfo.GetSafeBuffer();}
	
	SG_BOOL AddSdeDataSet(CSgGeoDataSet *pDataSet, SG_LONG row=-1){return AddDataSet(pDataSet,0,row);}
	
	SG_BOOL ModiSdeDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return ModiDataSet(pDataSet,0,row);}
	
	SG_BOOL DelSdeDataSet(CSgGeoDataSet *pDataSet,SG_LONG  row=-1){return DelDataSet(pDataSet,0,row);}
	//
	
	SG_BOOL AddDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return AddDataSet(pDataSet,1,row);}
	
	SG_BOOL ModiDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG row=-1){return ModiDataSet(pDataSet,1,row);}
	
	SG_BOOL DelDbfDataSet(CSgGeoDataSet *pDataSet,SG_LONG  row=-1){return DelDataSet(pDataSet,1,row);}
	
	
	CSgGeoDataSetArray *GetAddSdeDataSet(){return m_pAddSdeDataSet;}
	
	CSgGeoDataSetArray *GetModiSdeDataSet(){return m_pModiSdeDataSet;}
	
	CSgGeoDataSetArray *GetDelSdeDataSet(){return m_pDelSdeDataSet;}
	
	CSgGeoDataSetArray *GetAddDbfDataSet(){return m_pAddDbfDataSet;}
	
	CSgGeoDataSetArray *GetModiDbfDataSet(){return m_pModiDbfDataSet;}
	
	CSgGeoDataSetArray *GetDelDbfDataSet(){return m_pDelDbfDataSet;}
	
	CSgStringArray	&GetSqlClauses(){return m_sqlArray;}
protected:	
	
	SG_BOOL AddDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0, SG_LONG row=-1);
	
	SG_BOOL ModiDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0,SG_LONG row=-1);
	
	SG_BOOL DelDataSet(CSgGeoDataSet *pDataSet,SG_SHORT dataType=0,SG_LONG  row=-1);
	
	CSgString m_ErrorInfo;
private:
	
	CSgGeoDataSetArray *m_pAddSdeDataSet;
	
	CSgGeoDataSetArray *m_pModiSdeDataSet;
	
	CSgGeoDataSetArray *m_pDelSdeDataSet;
	
	CSgGeoDataSetArray *m_pAddDbfDataSet;
	
	CSgGeoDataSetArray *m_pModiDbfDataSet;
	
	CSgGeoDataSetArray *m_pDelDbfDataSet;
	
	CSgStringArray  m_sqlArray;
	
	SG_SHORT sqlNum;
};


class SG_CORE_API CommTransRtnInfo:public CommTransManager
{
public:
	
	CommTransRtnInfo();
	
	~CommTransRtnInfo();
	
/*	SG_UCHAR	RtnValue;		// --- ������ȷ���Ǵ���
	
	SG_UCHAR	Reserve1;	//Ԥ��
	
	SG_UCHAR	Reserve2;	//Ԥ��
	
	CSgString	RtnInfo;	// --- ������Ϣ,��ȷʱΪ��,����ʱΪ������Ϣ
*/	
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);

};

//����ͬ�汾������
struct SG_CORE_API ObjAttribResponsePara:public ClientRequestUserInfo,public CNetCmdHead
{
	SG_UCHAR   run_;	//	�Ƿ�Ϊ���а����ݣ���Ҫע����ǣ����������������� IsWorldLoad ��ô�˴��ı�־��ζ���Ƿ����а�����ݺͱ༭����������ݽ����˺ϲ�
	CSgGeoDataSet* pAdd,*pModi;
	CSgObjects* pDel;
	ObjAttribResponsePara(SG_UCHAR is_run=1);
	void SetStatus(SG_UCHAR is_run){run_=is_run;}
	~ObjAttribResponsePara();
	virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
};

//����ɾ���ļ�¼
class SG_CORE_API RequestRefRecords:public ClientRequestUserInfo,public CNetCmdHead
{
public:
    RequestRefRecords();
    ~RequestRefRecords();
    virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
    void Reset();
public:
    CSgObjects  types;      //size=0--��������
    CSgObjects	TaskList;
    CSgGeoDataSetArray*	m_pGeoDs;
};
//����ԭ���ݣ��޸ļ�¼��ԭ���ݣ�
class SG_CORE_API RequestOriRecords:public ClientRequestUserInfo,public CNetCmdHead
{
public:
    RequestOriRecords();
    ~RequestOriRecords();
    virtual SG_BOOL Serialize(CSgArchive&ar,SG_INT VersionNo=-1);
    void Reset();
public:
    SG_INT   ObjType;      //type--�������ݵ��豸����
    CSgObjects	objs;	//--Ҫ�����豸��ID����
    CSgGeoDataSet*	m_pDataSet;
};
//ʱ̬������Ϣ
class SG_CORE_API S_TSrvInfo
{
public:
    virtual SG_BOOL Serialize(CSgArchive&ar,int versionno);
public:
    SG_INT   TSrvNo;      //ʱ̬��������
	SG_INT	 StartYMD;    //ʱ̬�������ʼ������
	SG_INT	 EndYMD;    //ʱ̬�������ֹ������
    CSgObjects	TaskList;	//ʱ̬������������б�
	
};

//ʱ̬������Ϣ
class SG_CORE_API S_TSrvInfoList
{
public:
    S_TSrvInfoList();
    ~S_TSrvInfoList();
    virtual SG_BOOL Serialize(CSgArchive&ar,int versionno);
	void Clear();
	int  AddTSrvInfo(S_TSrvInfo &tsrvinfo);
public:
    SG_OBJECTS	TSrvList;	//ʱ̬�������б�
	
};
#endif
