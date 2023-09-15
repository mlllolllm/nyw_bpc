#ifndef __GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__

#pragma once
#include "csgdataset.h"

#include "NetCommand.h"
#include "command/NetCommandID.h"
#include "command/NetCmdHelper.h"
#include "command/GdbCommand.h"
//Ŀǰ��Щ����Ĵ�������ǻ��汾
struct	GIS_QUERYPSR_BASEINFO
{
	GIS_Schema		SchemeInfo;		//�滮����id
	ARR_UINT32		ObjTypes;		//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_CHAR			WholeContain;	//�Ƿ�ȫ����
	SG_CHAR			SearchAll;		//�Ƿ�ȫ����������
	SG_FLOAT		Tolerance;		//ѡ���ݲ�
	SG_DOUBLE		WorldScale;		//�������ȫ���������������ʾ�������ҳ�����������������
	SG_INT			MaxSelObjNum;	//���ѡ����豸���͸���
	GIS_QUERYPSR_BASEINFO()
	{
		WholeContain=0;
		SearchAll=1;
		WorldScale=1.0;
		Tolerance=0.0;
		MaxSelObjNum=5000;
	};
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ȡ�豸�����б�
struct GIS_LOADMODEL_OBJTYPE_REQ: public CNetCommand
{
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_LOADMODEL_OBJTYPE_RES: public CNetResponse
{
	CSgDataSet		ObjTypes;							// ���������ֶ� OBJTYPE,NAME,DESC
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//��ȡ�豸���͵��ֶ���Ϣ
struct GIS_LOADMODEL_OBJFIELD_REQ: public CNetCommand	// �����ĸ��ֶ� NAME,DESC,FIELDTYPE,FIELDLEN
{
	SG_INT		ObjType;	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADMODEL_OBJFIELD_RES: public CNetResponse
{
	CSgDataSet		ObjFields;	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//ѡ���������
struct GIS_QUERYPSR_RES : public CNetResponse
{
	SG_OBJECTS		SelObject;						//����ѡ��ļ�¼��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//����ѡ�����
struct GIS_QUERYPSR_BYPOINT_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO				ReqBaseInfo;	//ѡ����Դ�Ļ�����Ϣ
	SgPoint								CenterPoint;	//��������ĵ�
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYPOINT_RES;
//������ѡ�����
struct GIS_QUERYPSR_BYRECT_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO				ReqBaseInfo;	//ѡ����Դ�Ļ�����Ϣ
	SgRect								SelRect;		//����ľ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYRECT_RES;
//��Բѡ�����
struct GIS_QUERYPSR_BYCIRCLE_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO	    ReqBaseInfo;			//ѡ����Դ�Ļ�����Ϣ
	SgPoint						 CenterPoint;			//Բ��
	SG_DOUBLE					 Circle_R;				//Բ�İ뾶
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYCIRCLE_RES;

//������ѡ�����
struct GIS_QUERYPSR_BYPOLYGON_REQ : public CNetCommand
{
	GIS_QUERYPSR_BASEINFO	    ReqBaseInfo;		//ѡ����Դ�Ļ�����Ϣ
	CSgLine						 Range;				//ѡ��ļ��η�Χ
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYPOLYGON_RES;
//���ݸ��豸���������豸����Ϣ
struct GIS_QUERYPSR_BYFATHER_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//�滮����id
	ARR_UINT32		ObjTypes;						//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_OBJECT		FatherObj;						//���豸����
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYFATHER_RES;
//������·�豸���������豸����Ϣ
typedef GIS_QUERYPSR_BYFATHER_REQ GIS_QUERYPSR_BYLINE_REQ;
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYLINE_RES;

//���ݵ�λ���������豸����Ϣ
struct GIS_QUERYPSR_BYDEPARTMENT_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//�滮����id
	ARR_UINT32		ObjTypes;						//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_INT				Department;					//��˾��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_QUERYPSR_RES GIS_QUERYPSR_BYDEPARTMENT_RES;

//����ƴ������ģ������
struct GIS_QUERYPSR_BYPYBLUR_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//�滮����id
	ARR_UINT32		ObjTypes;						//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	CSgString	ObjAttrib;							//��ģ����ѯ���ֶ�����
	CSgString	KeyWord;							//ģ����ѯ�ؼ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//����ƴ������ģ����������
struct GIS_QUERYPSR_BYPYBLUR_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;						//����ѡ��ļ�¼��  �����ֶ�OBJTYPE,OBJID,ObjAttrib(��ģ����ѯ���ֶ�����)
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};


//���豸ID�飬������Ҫ���ֶ���Ϣ
struct GIS_LOAD_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//�滮����id
	SG_SHORT		ObjType;						//�豸����
	ARR_UINT32	ObjIDs;								//��Ҫ��ѯ���豸ID
	SG_UCHAR			RtnGeometry; 				//�Ƿ񷵻ؼ�������
	SG_UCHAR		HasTransDat;					//�Ƿ���Ҫ��������Datset
	CSgString		ObjAttribs;						//����ѯ���ֶ�����
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYIDARRAY_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;					//���ؼ�¼�� ����н����ķ����ֶ����ݼ����򷵻�����datset,���������ݼ���¼������ȫ��ͬ
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//���豸ID�飬������Ҫ��ʾ���ֶ���Ϣ
struct GIS_LOADDISP_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//�滮����id
	SG_SHORT		ObjType;						//�豸����
	ARR_UINT32		ObjIDs;							//��Ҫ��ѯ���豸ID
	CSgString		ObjAttribs;						//����ѯ���ֶ�����,���صļ�¼���ֶ���������п��ܲ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADDISP_BYIDARRAY_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;					//���ؼ�¼��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//��sql������������Ҫ���ֶ���Ϣ
struct GIS_LOAD_BYSQL_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//�滮����id
	SG_SHORT		ObjType;						//�豸����
	SG_UCHAR		HasTransDat;					//�Ƿ���Ҫ��������Datset
	SG_UCHAR		RtnGeometry; 					//�Ƿ񷵻ؼ�������
	CSgString		ObjAttribs;						//����ѯ���ֶ�����
	CSgString		WhereClause;					//�����Ӿ�
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOAD_BYSQL_RES : public CNetResponse
{
	CSgGeoDataSetArray RtnDataSets;				//���ؼ�¼��������н����ķ����ֶ����ݼ����򷵻�����datset,���������ݼ���¼������ȫ��ͬ
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//��sql������������Ҫ��ʾ���ֶ���Ϣ
struct GIS_LOADDISP_BYSQL_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;							//�滮����id
	SG_SHORT		ObjType;						//�豸����
	CSgString		ObjAttribs;						//����ѯ���ֶ�����
	CSgString		WhereClause;					//�����Ӿ�
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_LOADDISP_BYSQL_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;				//���ؼ�¼��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//���ݵ�λ��������·�ĳ�����Ϣ
struct GIS_LINELENGTH_BYDEPARTMENT_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		ObjTypes;					//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻�������·
	SG_INT				Department;				//��˾��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//ѡ���������
struct GIS_LINELENGTH_BYDEPARTMENT_RES : public CNetResponse
{
	SG_DOUBLE			TotalLength;	//�ܳ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//���豸��������Щ�豸����Ӿ���
struct GIS_QUERYRECT_BYIDARRAY_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;						//�滮����id
	SG_OBJECTS	Objects;						//�豸����
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

struct GIS_QUERYRECT_BYIDARRAY_RES : public CNetResponse
{
	SgRect				EncloseRect;		//��Ӿ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//�������豸�����丸�豸����Ϣ
struct GIS_QUERYPSR_BYCHILD_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//�滮����id
	ARR_UINT32		ObjTypes;						//����ѯ���豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_OBJECTS		ChildObj;						//���豸����
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�������豸�����丸�豸����Ϣ
struct GIS_QUERYPSR_BYCHILD_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//���������ֶ� OBJ_TYPE ID PTYPE PID 
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

#define GIS_TOPO_SPCOSTTYPE_NULL		0	//������
#define GIS_TOPO_SPCOSTTYPE_LINGTH		1	//�ܵ�����
#define GIS_TOPO_SPCOSTTYPE_CABLENUM	2	//�����ܵ�����
//�������·������
struct GIS_TOPO_SHORTPATH_CABLE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		ObjTypes;					//�����صĹ����豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_UCHAR			CalMode;				//����ģʽ  1:��·���  2:�����ܵ�����
	SG_UCHAR			JudgePipeUse;			//���ǹܿ׵Ŀ�����
	SG_SHORT			UsePipeNum;				//������Ҫ�Ĺܿ׸���   ȱʡΪ1
	SG_OBJECT			StartObj;				//��ʼ�ܵ��豸
	SG_OBJECT			EndObj;					//��ֹ�ܵ��豸
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�������·����������
struct GIS_TOPO_SHORTPATH_CABLE_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//���������ֶ� OBJTYPE OBJID PIPEID 
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//��·���·������
struct GIS_TOPO_SHORTPATH_ROAD_REQ : public CNetCommand
{
	ARR_UINT32		ObjTypes;					 //�����صĹ����豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SgPoint				StartPos;				//��ʼλ��
	SgPoint				EndPos;					//��ֹλ��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��·���·����������
struct GIS_TOPO_SHORTPATH_ROAD_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//�����ĵ�· ���������ֶ� ID,NAME
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//��ͨ�Է���
struct GIS_TOPO_CONNECTIVITY_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	SG_UCHAR			ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	SG_UCHAR			SearchInStation;		//����վ������   0��վ��վ�ⶼ��  1������վ����   2������վ����
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT			Obj1;					//����1
	SG_OBJECT			Obj2;					//����2
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ͨ�Է���
struct GIS_TOPO_CONNECTIVITY_RES : public CNetResponse
{
	SG_SHORT			ConnectFlag;	//�Ƿ���ͨ
	SG_OBJECTS		SelObject;	//���ؾ������豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//���緶Χ����
struct GIS_TOPO_SUPPLYRANGE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	ARR_UINT32		StopObjTypes;		  		//����ֹͣ���豸���ͣ����ObjTyps.size<=0 �򲻰����жϽ�������ֹͣ
	SG_UCHAR			ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	SG_UCHAR			SearchInStation;		//����վ������   0��վ��վ�ⶼ��  1������վ����   2������վ����
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//���緶Χ��������
struct GIS_TOPO_SUPPLYRANGE_RES : public CNetResponse
{
	SG_OBJECTS		SelObject;	//���ؾ������豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//����뾶����
struct GIS_TOPO_SUPPLYRADIUS_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	SG_UCHAR			ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	SG_UCHAR			RuleType;				//��������   1��������  2��ȫ��
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//����뾶����
struct GIS_TOPO_SUPPLYRADIUS_RES : public CNetResponse
{
	SG_DOUBLE			PowerSupplyRadius;		//����뾶
	SG_OBJECTS		SelObject;					//���ؾ������豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//��Դ�����
struct GIS_TOPO_POWERSOURCE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	ARR_UINT32		StopObjTypes;		  		//����ֹͣ���豸���ͣ����ObjTyps.size<=0 �򲻰����жϽ�������ֹͣ
	SG_UCHAR			ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	SG_UCHAR			SearchInStation;		//����վ������   0��վ��վ�ⶼ��  1������վ����   2������վ����
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT			StartObj;				//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��Դ���������
struct GIS_TOPO_POWERSOURCE_RES : public CNetResponse
{
	SG_OBJECT			PowerSourceObj;			//��Դ�豸
	SG_OBJECTS		SelObject;					//���ؾ������豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//ͣ�緶Χ����
struct GIS_TOPO_OUTAGERANGE_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		StopObjTypes;		  		//����ֹͣ���豸���ͣ����ObjTyps.size<=0 �򲻰����жϽ�������ֹͣ
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//ͣ�緶Χ����
struct GIS_TOPO_OUTAGERANGE_RES : public CNetResponse
{
	SG_OBJECTS		OnPowerObject;					//���ؿ��ض������е���豸��
	SG_OBJECTS		OffPowerObject;					//���ؿ��ض�����ͣ����豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//������·���ȷ���
struct GIS_CABLELINECORRIDOR_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;						//�滮����id
	SG_OBJECT			CableObj;					//��Ҫ�����ĵ��¶���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//������·���ȷ�������
struct GIS_CABLELINECORRIDOR_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;						//�����ĵ�· ���������ֶ� OBJTYPE,OBJID,PIPEID
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//---------------------------------------------------------------------------------------------------
//��·���·������
struct GIS_TOPO_SHORTPATH_ROAD_NEW_REQ : public CNetCommand
{
	SgPoint				StartPos;				//��ʼλ��
	SgPoint				EndPos;					//��ֹλ��
	CSgPoint			AvoidPos;				//���õ�
	CSgPoint			PathPos;				//�ؾ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
#define GIS_TOPO_ROAD_PASSPOS_NOT		0	//�Ǳؾ���
#define GIS_TOPO_ROAD_PASSPOS_START		1	//�ؾ�����·�������·�ε���ʼ��
#define GIS_TOPO_ROAD_PASSPOS_END		2	//�ؾ�����·�������·�ε���ֹ��
//��·���·����������
struct GIS_TOPO_SHORTPATH_ROAD_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;					//�����ĵ�· ���������ֶ� OBJ_TYPE,ID,PTYPE,PID,NAME,FLAG,PASSPOS_FLAG,PASSPOS_X,PASSPOS_Y
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
#define		GIS_TOPO_CONNECT_ANALYSETYPE_ONESIDE	1		//������ͨ�Է���
#define		GIS_TOPO_CONNECT_ANALYSETYPE_BOTHSIDE	2		//������ͨ�Է���
#define		GIS_TOPO_CONNECT_ANALYSETYPE_PATH		3		//·����ͨ�Է���
#define		GIS_TOPO_CONNECT_ANALYSETYPE_TWOPOS		4		//������ͨ�Է���
#define		GIS_TOPO_CONNECT_ANALYSETYPE_DIRECTLINK	5		//ֱ������
//��ͨ�Է���
struct GIS_TOPO_CONNECTIVITY_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//�滮����id
	SG_UCHAR		AnalyseType;			//��������
	ARR_UINT32		RtnObjTypes;		  	//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_UCHAR		OverVoltLevel;			//���ѹ�ȼ�
	SG_UCHAR		ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	CSgDataSet		UserKGStatus;			//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	ARR_UINT32		StopObjTypes;			//ֹͣ���豸����
	SG_OBJECTS		StopObjs;				//�߽��豸�������ѵ������豸��ֹͣ
	SG_OBJECT		Obj1;					//����1
	SG_OBJECT		Obj2;					//����2
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ͨ�Է���
struct GIS_TOPO_CONNECTIVITY_NEW_RES : public CNetResponse
{
	SG_SHORT		ConnectFlag;	//�Ƿ���ͨ
	CSgDataSet		RtnDatSet;		//�����豸��  �ֶΣ�OBJ_TYPE ID ISTLINK  ISTERM
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//��ͨ�Է���
struct GIS_TOPO_MULTICONNECTIVITY_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//�滮����id
	SG_UCHAR		AnalyseType;			//��������
	ARR_UINT32		RtnObjTypes;		  	//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	SG_UCHAR		OverVoltLevel;			//���ѹ�ȼ�
	SG_UCHAR		ConsiderKGStatus;		//�Ƿ��ǿ������豸��״̬
	CSgDataSet		UserKGStatus;			//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	ARR_UINT32		StopObjTypes;			//ֹͣ���豸����
	SG_OBJECTS		StopObjs;				//�߽��豸�������ѵ������豸��ֹͣ
	SG_OBJECTS		Objs;					//�������������1���豸����	
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef GIS_TOPO_CONNECTIVITY_NEW_RES GIS_TOPO_MULTICONNECTIVITY_RES;
//���緶Χ����
struct GIS_TOPO_SUPPLYRANGE_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	ARR_UINT32		StopObjTypes;		  		//����ֹͣ���豸���ͣ����ObjTyps.size<=0 �򲻰����жϽ�������ֹͣ
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT		StartObj;				//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//���緶Χ��������
struct GIS_TOPO_SUPPLYRANGE_NEW_RES : public CNetResponse
{
	SG_OBJECTS		RtnObjects;	//���ؾ������豸��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//����뾶����
struct GIS_TOPO_SUPPLYRADIUS_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;				//�滮����id
	SG_UCHAR		OverKGStation;			//�Ƿ��Խ����վ
	CSgDataSet		UserKGStatus;			//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECTS		PowerObjs;				//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//����뾶����
struct GIS_TOPO_SUPPLYRADIUS_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;			//���ع���뾶����Ϣ  �ֶΣ�OBJ_TYPE ID TERM_OBJTYPE TERM_OBJID LINE_OBJTYPE,LINE_OBJID RADIUS
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//��Դ�����
struct GIS_TOPO_POWERSOURCE_NEW_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  		//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	ARR_UINT32		VoltLevels;					//�����ĵ�ѹ�ȼ���Χ
	ARR_UINT32		StopObjTypes;		  		//����ֹͣ���豸���ͣ����ObjTyps.size<=0 �򲻰����жϽ�������ֹͣ
	CSgDataSet		UserKGStatus;				//ģ��Ŀ���״̬��Ϣ �������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECTS		TermObjs;					//��ʼ�����Ķ���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��Դ���������
struct GIS_TOPO_POWERSOURCE_NEW_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;				//�����豸�� ���ֶ�: TERM_OBJTYPE,TERM_OBJID,POWER_OBJTYPE,POWER_OBJID,PATH_OBJTYPE,PATH_OBJID
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//����·������
struct GIS_TOPO_SUPPLYPATH_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;					//�滮����id
	ARR_UINT32		RtnObjTypes;		  	//�����ص��豸���ͣ����ObjTyps.size<=0 �򷵻����еĶ���
	CSgDataSet	    UserKGStatus;			//ģ��Ŀ���״̬��Ϣ�������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECT		PowerObj;				//��Դ����
	SG_OBJECT		TermObj;				//�ն˶���
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//����·������
struct GIS_TOPO_SUPPLYPATH_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//�����豸�� �ֶΣ�OBJ_TYPE ID ISTLINK  ISTERM
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//���û������ϵ����
struct GIS_TOPO_GDD_POWERSOURCE_REQ : public CNetCommand
{
	GIS_Schema	SchemeInfo;					//�滮����id
	CSgDataSet	    UserKGStatus;			//ģ��Ŀ���״̬��Ϣ�������ֶ�OBJTYPE,OBJID,FLAG
	SG_OBJECTS		GDDObjs;				//��������
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//���û������ϵ����
struct GIS_TOPO_GDD_POWERSOURCE_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//�����豸�� �ֶΣ�������豸����(OBJ_TYPE)  �����ID(ID) 
	                                //�Ƿ��е�����·(HAS_CABLELINE) �Ƿ��мܿ���·(HAS_OVERHEADLINE) �Ƿ�ֱ����(IS_SPECIAL)
	                                //վ�豸����(STATION_OBJTYPE) վID(STATION_OBJID) ��·�豸����(LINE_OBJTYPE) ��·ID(LINE_OBJID)
	                                //��������(BREAK_OBJTYPE) ����ID(BREAK_OBJID)   ��ѹ������(TRANS_OBJTYPE) ��ѹ��ID(TRANS_OBJID)
	virtual SG_BOOL	Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//��ö���Ŀ�������
struct GIS_TOPO_GETCTRLATTRIB_REQ : public CNetCommand
{
	GIS_Schema		SchemeInfo;					//�滮����id
	SG_INT			ObjType;					//��������
	CSgString		Where;						//��������
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ö���Ŀ�������
struct GIS_TOPO_GETCTRLATTRIB_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//�����豸�� �ֶΣ��豸ID(ID) ��������(FLAG) ������Դ(SYSNO) ��·(LINENO)
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//ת��·�������Ա�
struct GIS_TOPO_TRANSPATH_REQ : public CNetCommand
{	
	CSgDataSet	    ObjDevStatus;	//ת��·���豸�������ֶ�OBJTYPE,OBJID,FLAG,���е�������¼Ϊ��Դ�����һ��Ϊ�ܵ��豸����Դ��ѹ�ȼ���С���ܵ��豸��ѹ�ȼ�
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_TOPO_TRANSPATH_RES : public CNetResponse
{
	CSgDataSet		RtnDatSet;		//�����豸�� �ֶΣ��豸����(OBJTYPE)���豸ID(OBJID) ·����(PATHNO)-���㿪ʼ
	SG_SHORT		LineNo;			//����·�����
	CSgLine			PathLine;		//����·������λ��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};
//ҵ����װ ������Դ��
struct GIS_TOPO_SEARCHPOWER_YKBZ_REQ : public CNetCommand
{	
	GIS_Schema		SchemeInfo;		//�滮����id
	SgPoint						 CenterPoint;			//��װ������
	SG_DOUBLE					 Circle_R;				//�����뾶
	SG_INT						VoltLevel;				//��ѹ�ȼ�
	ARR_UINT32		GDDObjTypes;		//���������
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
struct GIS_TOPO_SEARCHPOWER_YKBZ_RES : public CNetResponse
{
	CSgDataSetArray		PathObjDatSetArray;		//�����豸��,ÿ��DataSet��һ���������豸·��  �ֶΣ��豸����(OBJTYPE)���豸ID(OBJID)  ·����(PATHNO)-���㿪ʼ  ��һ���豸�ǹ����  ���һ���豸�ǵ�Դ��
	CSgGeoDataSet       PathCoordinate;			//�ֶ�:�������(NO,��0��ʼ)  �����ֶ�,ÿ����¼��Ӧһ������,��¼��ź�PathObjDatSetArray��DataSet���ƥ��
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};


//==================================================================================================
struct GIS_STAT_ANALYSE_REQ : public CNetCommand
{
	CSgString	Field;			//	ͳ�Ƶ��ֶΣ�Ϊ����ͳ�Ƽ�������
	CSgString	Where;			//	ͳ��������Ϊ���򲻹���
	ACE_UINT32	ObjType;		//	�豸���ͣ��������豸��ͳ�������͵����豸

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_STAT_ANALYSE_RES : public CNetResponse
{
	double	Result;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_SYMBOL_REQ : public CNetCommand
{
	ACE_UINT32 DisplaySchema , ObjType ;		//	��ʾ�������豸����

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_SYMBOL_RES : public CNetResponse
{
	CSgDataSet RtnDatSet;		//	

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_LABEL_REQ : public CNetCommand
{
	CSgRect	Extent;				//	��Ұ��Χ
	ARR_UINT32	ObjTypes;		//	�豸����
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

struct GIS_GET_LABEL_RES : public CNetResponse
{
	CSgGeoDataSet RtnDatSet;	//	��ע ID , NAME , Geometry;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int		buf_size();
};

//==================================================================================================
//	���ݶ���Ҫ������Ƿ񽫺���ʵ������
#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/GGisCommand.inl"
#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_GGIS_COMMAND_DEFINE_HEADER__
