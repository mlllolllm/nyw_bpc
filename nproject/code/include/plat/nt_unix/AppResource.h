
/********************************************************************
*********************************************************************/

#ifndef _CAPPRESOUCE_INCLUDE_H_
#define _CAPPRESOUCE_INCLUDE_H_


#include "sgconst.h"
#include "NetCommand.h"
#include "netdef.h"

#define DECLARE_CLASSNAME(x) \
	static const char* GetClassName() { return #x; }

class CAppResourceManager;
class CMapBlockManager;
class CAppEnvBase;
class SGNP;
class DA_Proxy;
class CGdbEngine;
class CDbfEngine;
class CSgSymbol;
class ObjGroupCats;
class ObjGroupAttribs;
class CColorManager;
class CSgDataSet;
class CGotoManager;
class CObjectBaseAttrib;
class CDynaDataMan;

enum SG_AppResourceType
{
	appGdb					=0,				//�ռ�����
	appLocalFile			=1,				//�����ļ�
	appTGdb					=2,				//ʱ̬����
	appDb					=3,				//ֱ�����ݿ�
};
enum SG_GClientLinkDBType
{
	GClientLinkDBType_DB					=1,				//ֱ�����ݿ�
	GClientLinkDBType_DppSrv				=2,				//��dppsrv
	GClientLinkDBType_GdbSrv				=3,				//��ͼ�η���
};

class SG_CORE_API CAppResource
{
	friend class CAppEnvBase;
	friend class COnlineAppEnvBase;
	friend class CFDUDataManager;
public:

	virtual ~CAppResource();
	
	CSgString&	GetID()					{ return m_strID; }
	SG_AppResourceType& GetType()		{ return m_type;  }
	CSgString&	GetLinkDBSrvIP()	{return m_LinkDBSrvIP;}
	SG_UCHAR		GetLinkDBType()	{return m_LinkDBType;}
	SG_INT GetLinkGDBNo() { return m_LinkGDBNo; };
	//
	CSgPtrArray& GetAppEnvs()			{ return m_AppEnvs;}
	virtual CAppEnvBase* FindAppEnv(GIS_Schema*pSchema);
	
	CReleaseAble* GetResource(const char*lpszClassName,bool bRemove=false);
	void  SetResource(const char*lpszClassName,CReleaseAble*p);
	
	CSgDataSet* GetDataSet(const char* lpszTableName);
	CSgDataSet* GetDataSetEx(const char* lpszTableName,const char*lpszWhere);//����DATASET����WHERE
	void AddDataSet(CSgDataSet*pDateSet);
	
	SGNP* GetSGNP()											{ return m_pSGNP;}
	void  SetSGNP(SGNP*p)									{ m_pSGNP = p;	 }

	virtual DA_Proxy*		GetDAProxy()					{ return NULL; }
	virtual CGdbEngine*		GetGdbEngine()					{ return NULL; }
	virtual CDbfEngine*		GetDbfEngine()					{ return NULL; }

	ACE_Thread_Mutex& GetLock();

protected:
	//��ֹ���ⲿ����CAppResource����
	CAppResource(SG_PCSTR strID,CAppResourceManager*pManager);

	virtual bool Initialize(CAppEnvBase*p)					{ return true; }
	virtual bool Initialize_db(CAppEnvBase*p)					{ return true; }

protected:
	//	����Ӧ����ԴΨһ�Ĺ�������ȡ����
	virtual CMapBlockManager * MapBlockManager( )			{ return NULL; }
	virtual CGotoManager*	GetGotoManger(CAppEnvBase*p)	{ return NULL; }
	virtual CSgSymbol*		GetSymbolLib()					{ return NULL; }
	virtual ObjGroupAttribs*GetObjGroupAttribs(CAppEnvBase*){ return NULL; }
	virtual ObjGroupCats*   GetObjGroupCats(CAppEnvBase*)	{ return NULL; }
	virtual CDynaDataMan*	GetDynaMan()					{ return NULL; }
	
	void AddAppEnv(CAppEnvBase*p);
	void RemoveAppEnv(CAppEnvBase*p);

protected:

	CAppResourceManager * m_pResManager;

	CSgString			m_strID;
	SG_AppResourceType	m_type;
	SG_UCHAR			m_LinkDBType;	//���ݲ����������� 1:���������ݿ� 2����dppsrv  3:��gdbsrv
	CSgString			m_LinkDBSrvIP;
	SG_INT				m_LinkGDBNo;
	//
	CSgPtrArray			m_AppEnvs;
	String2Ptr			m_cls2obj;
	CSgPtrArray			m_Attribs;
	CSgDataSetArrayEx	m_DataSets;
	
	SGNP				*m_pSGNP;

	ACE_Thread_Mutex	* m_pLock;
};

//ÿ��ʱ̬������һ��AppResource���
//��״̬,��Schema�е�m_nVersion���
//ÿ��������Schema�е�m_nSchema���,�Ӷ�����һ��AppResource�еĲ�ͬAppEnv
class SG_CORE_API CAppResourceGdb:public CAppResource
{
public:

	CAppResourceGdb(SG_PCSTR strID,CAppResourceManager*pManager);
	~CAppResourceGdb();

	virtual DA_Proxy*		GetDAProxy();
	virtual CGdbEngine*		GetGdbEngine();
	virtual CDbfEngine*		GetDbfEngine();

protected:

	virtual bool Initialize(CAppEnvBase*p);
	virtual bool Initialize_db(CAppEnvBase*p);

	virtual CSgSymbol*		GetSymbolLib();
	virtual CGotoManager*	GetGotoManger(CAppEnvBase*p);
	virtual ObjGroupAttribs*GetObjGroupAttribs(CAppEnvBase*p);
	virtual ObjGroupCats*   GetObjGroupCats(CAppEnvBase*p);
	virtual CDynaDataMan*	GetDynaMan();
	//
	DA_Proxy*			m_pDAProxy;
	CGdbEngine*			m_pGdbEngine;
	CDbfEngine*			m_pDbfEngine;

	CSgSymbol*			m_pSymbolLib;
	CGotoManager*		m_pGotoManager;
	ObjGroupAttribs*	m_pObjGroupAttribs;
	ObjGroupCats*		m_pObjGroupCats;
	CDynaDataMan*		m_pDynaMan;
	
	//	���ر���ͼ�������ָ��
	virtual CMapBlockManager * MapBlockManager( );
	CMapBlockManager * m_lpMapBlockManager;

	CSgRect     m_rcRefExt;				//	�ռ�����������շ�Χ
	SG_SHORT	m_nServerNo;			//	�ռ���������
	CSgLine		m_lnLoadRange;			//	�������еĹ�����ط�Χ
	CSgString	m_strServerName;		//	�ռ���������
	SG_LONG		m_nTopCompanyNo;		//	���㹫˾��


	bool				m_bInitialized;
};


class SG_CORE_API CAppResourceTGdb:public CAppResourceGdb
{
public:

	CAppResourceTGdb(SG_PCSTR strID,CAppResourceManager*pManager);
	~CAppResourceTGdb();	
};




class SG_CORE_API CAppResourceFile:public CAppResource
{
public:
	CAppResourceFile(SG_PCSTR strID,CAppResourceManager*pManager)
		:CAppResource(strID,pManager){ m_type = appLocalFile;}

public:
	virtual CAppEnvBase* FindAppEnv(GIS_Schema*pSchema);
};

class SG_CORE_API CAppResourceDb:public CAppResourceGdb
{
public:

	CAppResourceDb(SG_PCSTR strID,CAppResourceManager*pManager);
	~CAppResourceDb();
protected:
	virtual bool Initialize(CAppEnvBase*p);
};

class ACE_Recursive_Thread_Mutex;
class SG_CORE_API CAppResourceManager:public CSgPtrArray
{
public:

	static CAppResourceManager* instance(bool bCreateLock=false);
	static void release();

	CAppResource* GetAppResource(SG_AppResourceType type,CSgString strID);
	CAppResource* FindAppResource(SG_AppResourceType type,CSgString strID);
	CAppResource* CreateAppResource(SG_AppResourceType type,CSgString strID);

protected:

	CAppResourceManager();
	~CAppResourceManager();

	void CreateLock();

	static CAppResourceManager* c_pInstance;
	ACE_Recursive_Thread_Mutex	* m_pLock;
};


#endif



