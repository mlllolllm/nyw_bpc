
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
	appGdb					=0,				//空间引擎
	appLocalFile			=1,				//本地文件
	appTGdb					=2,				//时态服务
	appDb					=3,				//直连数据库
};
enum SG_GClientLinkDBType
{
	GClientLinkDBType_DB					=1,				//直连数据库
	GClientLinkDBType_DppSrv				=2,				//连dppsrv
	GClientLinkDBType_GdbSrv				=3,				//连图形服务
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
	CSgDataSet* GetDataSetEx(const char* lpszTableName,const char*lpszWhere);//检索DATASET考虑WHERE
	void AddDataSet(CSgDataSet*pDateSet);
	
	SGNP* GetSGNP()											{ return m_pSGNP;}
	void  SetSGNP(SGNP*p)									{ m_pSGNP = p;	 }

	virtual DA_Proxy*		GetDAProxy()					{ return NULL; }
	virtual CGdbEngine*		GetGdbEngine()					{ return NULL; }
	virtual CDbfEngine*		GetDbfEngine()					{ return NULL; }

	ACE_Thread_Mutex& GetLock();

protected:
	//禁止在外部创建CAppResource对象
	CAppResource(SG_PCSTR strID,CAppResourceManager*pManager);

	virtual bool Initialize(CAppEnvBase*p)					{ return true; }
	virtual bool Initialize_db(CAppEnvBase*p)					{ return true; }

protected:
	//	所有应用资源唯一的管理器获取函数
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
	SG_UCHAR			m_LinkDBType;	//数据操作联接类型 1:连本地数据库 2：连dppsrv  3:连gdbsrv
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

//每个时态服务用一个AppResource表达
//基状态,用Schema中的m_nVersion表达
//每个断面用Schema中的m_nSchema表达,从而区分一个AppResource中的不同AppEnv
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
	
	//	本地背景图层管理器指针
	virtual CMapBlockManager * MapBlockManager( );
	CMapBlockManager * m_lpMapBlockManager;

	CSgRect     m_rcRefExt;				//	空间引擎坐标参照范围
	SG_SHORT	m_nServerNo;			//	空间引擎器号
	CSgLine		m_lnLoadRange;			//	服务器中的管理加载范围
	CSgString	m_strServerName;		//	空间引擎名称
	SG_LONG		m_nTopCompanyNo;		//	顶层公司号


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



