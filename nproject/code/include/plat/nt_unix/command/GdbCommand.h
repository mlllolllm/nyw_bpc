#ifndef __GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__

#pragma once

#include "csgdataset.h"

#include "NetCommand.h"
#include "command/NetCommandID.h"
#include "command/NetCmdHelper.h"

//==================================================================================================
// ����滮��Ϣϵͳ�пռ����������
namespace NetCommand
{
	enum GdbCommandID		//	�ռ��������չ����� 100 ��ʼ���� 600 ����
	{


		commitVersion					=	VerCmdMin,			//�ύ�汾
		rollBackVersion					=	VerCmdMin+1,		//�ع��汾
		updateManSet					=	VerCmdMin+2,		//�˹�����
		updateRunStyle					=	VerCmdMin+4,
		QueryDeleteObjs					=	VerCmdMin+5,		//����ɾ���ļ�¼
		QueryRunVerObjs					=	VerCmdMin+6,		//����ĳһ�豸�������а汾�¶�Ӧ�ļ�¼
		getGdbVerEnable					=	VerCmdMin+7,		//�ռ������Ƿ����ð汾
		Ver_readSdetable				=	VerCmdMin+8,		//������objs��3D��Ϣ
		Ver_ObjUpdatePierce				=	VerCmdMin+9,		//��͸�汾���޸�
		Ver_EMObjSync					=	VerCmdMin+10,		//̨��ͬ����Ϣ
		ForceObjModi					=	VerCmdMin+11,		//ǿ�ƶ����޸ģ��յ�������������ļ�¼�ع���
																//���µļ�¼�����޸ġ������֧�ּ����ֶε��޸�
		Ver_EMDatSetSync				=	VerCmdMin+12,		//̨��ͬ����Ϣ,����������ObjTransManager
		TSrvSaveSnapCmd					=	VerCmdMin+13,		//ʱ̬�������浱ǰϵͳ����
		getTSrvInfo						=	VerCmdMin+14,		//��ȡʱ̬�������Ϣ
		Ver_ReadDBVerRecord				=	VerCmdMin+15,		//�����ݿ��ȡ�汾�ļ�¼
		Ver_FmGetObjLockFlag			=	VerCmdMin+16,		//̨�ʻ�ȡ�����Ƿ�������Ϣ
		TSrvSaveSnapClientCmd			=	VerCmdMin+17,		//ʱ̬�������浱ǰϵͳ����,�����Կͻ��˷���
		TSrvReCreateSnapList			=	VerCmdMin+18,		//����ʵ������������ʱ�������Ϣ

		GIS_LOAD_LAYER					=	VerCmdMin+19,		//	��������ͼ�������,�ɸ���������Ϣ������
		GIS_LOAD_WORLD					=	VerCmdMin+20,		//	���� WORLDID ��������
		GIS_LOAD_ARRAY					=	VerCmdMin+21,		//	���� ID �б��������
		GIS_LOAD_CELLS					=	VerCmdMin+22,		//	�������������������

		GIS_LOAD_BY_LINES				=	VerCmdMin +23,		//���մ���ļ��ζ����ѡ��
		GIS_LOAD_BY_PYBLUR				=	VerCmdMin +24,		//����ƴ��ģ����ѯ

		readObjAttrib					=	VerCmdMin +25,		//��ȡ�豸����
		objAdd							=	VerCmdMin +26,		//������������
		objModi							=	VerCmdMin +27,		//�����޸�����
		objDelete						=	VerCmdMin +28,		//����ɾ������
		objTransOper					=	VerCmdMin +29,		//�����������
		
		GIS_LOAD_BY_APDOBJTYPE			=	VerCmdMin +30,		//���ݸ����豸�����ͼ������豸,���豸�о���BASE_OBJ_TYPE�ֶ�
		GIS_SCHEMES_TASKDIFF			=	VerCmdMin +31,		//�Ƚ������������������
		GIS_ROLLBACK					=	VerCmdMin +33,		//�滮��Ŀ(������)�鵵
		GIS_GET_RELDAT					=	VerCmdMin +34,		//��ú���Ŀ(������)��ص�������Ϣ
		GIS_RELDAT_REPLACE				=	VerCmdMin +35,		//����Ŀ(������)��ص������¾��豸��������
		GIS_LOAD_BY_MULTICOND			=	VerCmdMin +36,		//���ݼ��ζ���κ�where��������ѡ������

		TSrvRepairADTable				=	VerCmdMin+37,		 //ʱ̬�������ʵ����������޸�A/D���е�����
		TSrvChangeObjsTime				=	VerCmdMin+38,		 //ʱ̬�������һ���豸�Ĳ���ʱ��

		GIS_SCHEMES_DIFFOBJ				=	VerCmdMin+39,		 //���������汾�Ĳ�������

		GIS_QueryPSRByPoint				=	VerCmdMin+50,		//���ݴ���ĵ������ѯ��������ͼ�еĵ�����Դ��Ϣ
		GIS_QueryPSRByCircle			=	VerCmdMin+51,		//���ݴ����Բ��ѯ��������ͼ�еĵ�����Դ��Ϣ
		GIS_QueryPSRByRect				=	VerCmdMin+52,		//���ݴ���ľ��β�ѯ��������ͼ�еĵ�����Դ��Ϣ
		GIS_QueryPSRByPolygon			=	VerCmdMin+53,		//���ݴ���Ķ���β�ѯ��������ͼ�еĵ�����Դ��Ϣ
		GIS_QueryPSRByFather			=	VerCmdMin+54,		//�������豸�ĵ�����Դ��Ϣ
		GIS_QueryPSRByCompany			=	VerCmdMin+55,		//��������ĵ�λID ͳ�Ƹõ�λ��Ͻ�����ڵĵ�����Դ
		GIS_QueryPSRByPYBlur			=	VerCmdMin+56,		//����ƴ��ģ����ѯ������Դ

		GIS_LoadByIDArray				=	VerCmdMin+57,		//���ݴ�����豸id���飬������Ҫ���豸��Ϣ�ֶ�
		GIS_LoadByWhereSQL				=	VerCmdMin+58,		//����WHERE SQL��䣬������Ҫ���豸��Ϣ�ֶ�

		GIS_QueryLineLengthByCompany	=	VerCmdMin+59,		//��������ĵ�λID,��ȡ��·���ܳ���

		GIS_LoadModel_ObjType			=	VerCmdMin+60,		//��ȡ�豸ģ��
		GIS_LoadModel_ObjField			=	VerCmdMin+61,		//��ȡ�豸������

		GIS_QueryEnCloseRectByIDArray	=	VerCmdMin+62,		//���ݴ�����豸id���飬�����豸����Ӿ���
		GIS_LoadDispByIDArray		=	VerCmdMin+63,		//���ݴ�����豸id���飬������Ҫ������ʾ���豸��Ϣ�ֶ�
		GIS_LoadDispByWhereSQL		=	VerCmdMin+64,		//����WHERE SQL��䣬������Ҫ������ʾ���豸��Ϣ�ֶ�
		GIS_QueryPSRByChild			=	VerCmdMin+65,		//���Ҹ��豸�ĵ�����Դ��Ϣ
		GIS_QueryChildPSRByLine		=	VerCmdMin+66,		//������·�����е�����Դ��Ϣ

		GAP_GetSeqValue				=	VerCmdMin+67,		//��ȡID������ֵ
	};
};

//==================================================================================================
//	�滮��Ϣϵͳ��̬���������ͨ����Ϣ
struct GIS_Common
{
	SG_UINT		WorldID;		//	�����Ҫ�����豸��ע����ô�ñ�����������豸��ע
	SG_UINT		ObjectType;		//	Ҫ���ص��豸���ͣ�������豸���� WorldID ���أ���ô������ WorldID ָ��������
	SG_UINT		LoadType;		//	�������ͣ�1 ���ػ������ݡ�2 ��չ���ݡ�3 ȫ���� ���μ� LoadType ö�ٶ���
	SG_UINT		Reserved;		//	�������ݣ�/****�Ƿ���ض�Ӧ���豸��ע****/
	ARR_UINT32	AppendObjTypes;	//	������ص�����豸�����б�

	GIS_Common( )
	{
		WorldID			= 0	;
		ObjectType		= 0	;
		LoadType		= 0 ;

		Reserved		= 0	;
		AppendObjTypes.clear();
	}

	inline void operator = ( const GIS_Common & rhs )
	{
		WorldID			= rhs.WorldID		;
		ObjectType		= rhs.ObjectType	;
		LoadType		= rhs.LoadType		;

		Reserved		= rhs.Reserved		;
		AppendObjTypes	= rhs.AppendObjTypes;
	}

	inline int buf_size()
	{
		return BUF_SIZE( 4 , 0 , 0 )+AppendObjTypes.buf_size();
	}

	virtual SG_BOOL		Serialize(CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		
		SERIALIZE_MEMBER( rStream , WorldID			);
		SERIALIZE_MEMBER( rStream , ObjectType		);
		SERIALIZE_MEMBER( rStream , LoadType		);

		SERIALIZE_MEMBER( rStream , Reserved		);
		SERIALIZE_OBJECT( rStream , AppendObjTypes	);
		return true;
	}
};

enum GIS_Common_LoadType
{
	CLT_LOAD_BASIC	= 0x00000001,						//	���ػ����ֶ�
	CLT_LOAD_EXTRA	= 0x00000002,						//	������չ�ֶ�
	CLT_LOAD_ALL	= CLT_LOAD_BASIC|CLT_LOAD_EXTRA,	//  ����ȫ���ֶ�

	CLT_SYNC_APPENDDEV	= 0x00000004,	//	ͬ����������豸
	CLT_ONLY_TABLE		= 0x00000008,	//	�����ر�ṹ
	CLT_LOAD_COMBIN		= 0x00000010	//  ��ϼ���
};

//==================================================================================================
//	�滮��Ϣϵͳͨ�õ�����������Ϣ
struct GIS_Schema				
{
	ACE_UINT32 m_nVersion;		//	��汾�ţ����ݴ�汾����ȷ�����ص���������
	ACE_UINT32 m_nSchema;		//	������ţ�����ʱ̬�����ֵ�洢��Ӧ������
	ACE_UINT32 m_nSchemaYMD;	//	�ͻ��˲쿴ʱ��ѡ��鿴��ʱ���
								//���Ϊ0���鿴��ʱ���Ϊ��������ʼʱ��
	ACE_UINT32 m_nHighLoadYMD;	//	���Ϊʱ̬���񣬸�ֵ��Ϊ�㣬��Ϊ��߸����յ�������
	ACE_UINT32 m_nHighLoadHMS;	//	���Ϊʱ̬������Ϊ��߸��ɷ�����ʱ����
	
	ARR_UINT32 m_arrScheme;		//	��Ĭ���ӷ������б�

	inline GIS_Schema()
	{
		m_nVersion	= 0;
		m_nSchema	= 0;
		m_nSchemaYMD= 0;
		m_nHighLoadYMD=0;
		m_nHighLoadHMS=0;
	}

	inline int buf_size()
	{
		return OBJ_SIZE( m_arrScheme ) + BUF_SIZE( 5 , 0 , 0 );
	}

	inline SG_BOOL Serialize( CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		SERIALIZE_MEMBER( rStream , m_nVersion	);
		SERIALIZE_MEMBER( rStream , m_nSchema	);
		SERIALIZE_MEMBER( rStream , m_nSchemaYMD	);
		
		SERIALIZE_OBJECT( rStream , m_arrScheme	);
		SERIALIZE_MEMBER( rStream , m_nHighLoadYMD	);
		SERIALIZE_MEMBER( rStream , m_nHighLoadHMS	);
		return true;
	}

	inline void Assign( const GIS_Schema & rhs )
	{
		if( & rhs == this ) return ;
		
		m_nVersion	= rhs.m_nVersion	;
		m_nSchema	= rhs.m_nSchema		;
		m_nSchemaYMD	= rhs.m_nSchemaYMD	;
		m_nHighLoadYMD	= rhs.m_nHighLoadYMD	;
		m_nHighLoadHMS	= rhs.m_nHighLoadHMS	;
		m_arrScheme	= rhs.m_arrScheme	;
	}

	inline GIS_Schema( const GIS_Schema & rhs )
	{
		Assign( rhs );
	}

	inline GIS_Schema & operator = ( const GIS_Schema & rhs )
	{
		Assign( rhs );
		return * this;
	}

	bool operator == ( const GIS_Schema & rhs ) const
	{
		return	( m_nVersion	== rhs.m_nVersion	)
			 &&	( m_nSchema		== rhs.m_nSchema	)
			 &&	( m_nSchemaYMD	== rhs.m_nSchemaYMD	)
			 &&	( m_nHighLoadYMD== rhs.m_nHighLoadYMD	)
			 &&	( m_nHighLoadHMS== rhs.m_nHighLoadHMS	)
			 &&	( m_arrScheme	== rhs.m_arrScheme	);
	}

	inline void FromString(const char* lpszVerName)
	{
		if(lpszVerName)
		{
			int len = strlen(lpszVerName);
			for(int i=0;i<len;i++) m_arrScheme.push_back(lpszVerName[i]);
		}
	}

	inline void ToString(ACE_CString&strVerName)
	{
		int len = m_arrScheme.size();
		strVerName.resize( len+1 );
		strVerName[len]=NULL;
		for(int i=0;i<len;i++)  strVerName[i] = m_arrScheme[i];
	}

};
typedef struct S_WorkSchemaInfo
{
	GIS_Schema	SchemaInfo;
	int			ProcTaskNo;
}S_WorkSchemaInfo;

//==================================================================================================
//	
struct GIS_Attrib
{
	//	ֱ�ӵ��û�������л�����
	inline SG_BOOL Serialize( CSgArchive & rStream,SG_INT VerNo=-1)
	{
		if(VerNo<0)
		{
			VerNo=SgNetVersion;
			if(VerNo<0)
				return false;
		}
		// ����Ƿ����л����ݣ�����ָ�벻����
		if( rStream.IsLoading() && lpGeoDataSet == NULL )
		{
			//	����һ�����ݼ�����
			lpGeoDataSet = new CSgGeoDataSet;
		}

		if( lpGeoDataSet == NULL )
		{
			// ������󲻴��ڣ����л��ռ�¼��
			CSgGeoDataSet().Serialize( rStream );
		}
		else
		{
			// ֱ�����л���¼��
			lpGeoDataSet->Serialize( rStream );
		}
		return true;
	}

	// ���ؼ���ֵ������ú�������
	inline int buf_size()
	{
		return INT_MAX ;
	}

	inline void Release()
	{
		if( lpGeoDataSet )
		{ 
			delete lpGeoDataSet; 
			lpGeoDataSet = NULL; 
		}
	}

	GIS_Attrib() : lpGeoDataSet( NULL ) { }
	~GIS_Attrib() { Release(); }

	CSgGeoDataSet * lpGeoDataSet;
};


struct GIS_LOAD_BASIC_REQ : public CNetCommand
{
	GIS_Common	Common;
	GIS_Schema	Schema;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BASIC_RES : public CNetResponse
{
	GIS_Common	Common;

	GIS_Attrib			dsAttrib;
	GIS_Attrib			dsTblInfo;	//���ڽ������ػ����ֶε��࣬�ýṹ�з��豸��̬�ֶε���Ϣ
	CSgGeoDataSetArray	dsAppends;	//���Ӽ�¼�����������豸���ص���ظ����豸

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	��������ͼ������� , ��Ϊ������Ϣ�Ѿ��뱸������ֱ�ӿռ̳У�
struct GIS_LOAD_LAYER_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_LAYER_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	���� WORLDID �������� , ��Ϊ������Ϣ�Ѿ��뱸������ֱ�ӿռ̳У�
struct GIS_LOAD_WORLD_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_WORLD_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	���� ID �б��������
struct GIS_LOAD_ARRAY_REQ : public GIS_LOAD_BASIC_REQ
{
	ARR_UINT32	arrObjects;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_ARRAY_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	�������������������
struct GIS_LOAD_CELLS_REQ : public GIS_LOAD_BASIC_REQ
{
	ARR_UINT32	arrCells;

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_CELLS_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//	���ո����豸���ͼ������豸
struct GIS_LOAD_BY_APDOBJTYPE_REQ : public GIS_LOAD_BASIC_REQ
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BY_APDOBJTYPE_RES : public GIS_LOAD_BASIC_RES
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//������ѡ�����
struct GIS_LOAD_BYLINES_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;		//�滮����id
	ARR_UINT32	ObjTypes;		//����ѯ���豸����
	SG_CHAR		RtnGeometry; 	//�Ƿ񷵻ؼ�������
	CSgString	ObjAttrib;		//����ѯ���ֶ�����
	CSgLine		Range;			//ѡ��ļ��η�Χ
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYLINES_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;	//���ؼ�¼��
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//������+����ѡ�����
struct GIS_LOAD_MULTICOND_REQ : public GIS_LOAD_BYLINES_REQ
{
	CSgString	WhereClause;	//����
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_LOAD_BYLINES_RES GIS_LOAD_MULTICOND_RES ;


struct GIS_LOAD_PYBLUR_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;		//�滮����id
	ARR_UINT32	ObjTypes;		//��ģ����ѯ���豸����
	SG_CHAR		RtnGeometry; 	//�Ƿ񷵻ؼ�������
	CSgString	ObjAttrib;		//��ģ����ѯ���ֶ�����
	CSgString	KeyWord;		//ģ����ѯ�ؼ���
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_PYBLUR_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;	//���ؼ�¼��
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


struct GIS_SCHEMES_TASKDIFF_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo1;		//�滮����1
	GIS_Schema	SchemeInfo2;		//�滮����2
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_SCHEMES_TASKDIFF_RES : public CNetResponse
{
	ARR_UINT32	TaskList_Scheme1;		//�ڹ滮����1�У����ڹ滮����2������
	ARR_UINT32	TaskList_Scheme2;		//�ڹ滮����2�У����ڹ滮����1������
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


//���������Ϣ
struct GIS_SCHEMES_DIFFOBJ_REQ : public CNetCommand
{
	ARR_UINT32	ObjTypes;			//��Ҫ���豸����,�������Ϊ0�������ж���ȫ������
	GIS_Schema	SchemeInfo1;		//�滮����1
	GIS_Schema	SchemeInfo2;		//�滮����2
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//���������Ϣ����
struct GIS_SCHEMES_DIFFOBJ_RES : public CNetResponse
{
	CSgDataSetArray_ObjOper		DiffObjs;		//��������б�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


struct GIS_LOADFDU_REQ  : public  CNetCommand
{
public:
	GIS_Schema		SchemeInfo;
	SG_SHORT		FDM_ID;			//FDM��ID��
	SG_UCHAR		HasScatterFDU;
	ACE_UINT32		WorldID;		//�ͻ��������WorldID��
	SG_OBJECTS		Base_FDUArray;	//�����FDU����(BASE_OBJ_TYPE,BASE_OBJ_ID)
	SG_OBJECTS		Ver_FDUArray;	//��ǰ��汾��A��FUD����(BASE_OBJ_TYPE,BASE_OBJ_ID)

	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_LOAD_PYBLUR_RES GIS_LOADFDU_RES;

#define GIS_ROLLBACK_TYPE_TASK	1	//����鵵
#define GIS_ROLLBACK_TYPE_PRJ	2	//��Ŀ�鵵
struct GIS_ROLLBACK_REQ : public CNetCommand
{
public:
	GIS_Schema		SchemeInfo;		//�滮Ӧ�û���
	SG_SHORT		RollBackType;	//1:����鵵   2:��Ŀ�鵵
	SG_INT			RollBackID;		//��Ҫ�ع����������Ŀ��ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_ROLLBACK_RES : public CNetResponse
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

#define GIS_RELDAT_OPERMODE_DEL			1	//ɾ����ص�����
#define GIS_RELDAT_OPERMODE_REPLACE		2	//����������е� Դ�����ΪĿ�Ķ���

typedef  GIS_ROLLBACK_REQ	GIS_GET_RELDAT_REQ;

struct GIS_GET_RELDAT_RES : public CNetResponse
{
	CSgDataSet	RelDat;		//�����ֶ�ΪTABLE_NAME	OPERMODE OBJTYPE OBJID
public:
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_RELDAT_REPLACE_REQ : public CNetCommand
{
public:
	GIS_Schema		SchemeInfo;		//�滮Ӧ�û���
	SG_SHORT		RollBackType;	//1:����鵵   2:��Ŀ�鵵
	SG_INT			RollBackID;		//��Ҫ�ع����������Ŀ��ID
	CSgDataSet		RelDat;		//�����ֶ�ΪTABLE_NAME	OPERMODE SRC_OBJTYPE SRC_OBJID DES_OBJTYPE DES_OBJID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_RELDAT_REPLACE_RES : public CNetResponse
{
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct TSRV_CHG_OBJSTIME_REQ
{
public:
	SG_INT			SrcYMD;			//��Ҫ�����豸��ԭʼʱ��
	SG_INT			DesYMD;			//��Ҫ�����豸��ԭʼʱ��
	SG_SHORT		ObjType;		//�豸����,���Ϊ-1,��Ϊ���е��豸����
	SG_INT			ObjKID;			//�豸kid,���Ϊ-1,��Ϊ�����͵������豸
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//��ȡSequenceIDֵ
struct GAP_GETSEQVALUE_REQ : public CNetCommand
{
	CSgString		SeqName;
	SG_INT			WorkSpace;
	SG_UINT			Cnt;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GAP_GETSEQVALUE_RES : public CNetResponse
{
	CSgObjects			ObjIDS;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//	���ݶ���Ҫ������Ƿ񽫺���ʵ������
#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/GdbCommand.inl"
#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
