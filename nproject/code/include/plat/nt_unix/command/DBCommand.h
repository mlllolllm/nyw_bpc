#ifndef __COMMON_DATABASE_COMMAND_DEFINE_HEADER__
#define __COMMON_DATABASE_COMMAND_DEFINE_HEADER__


#include "csgdataset.h"
//#include "CommandBase.h"
#include "sgmail.h"
#include "sgconst_cloud.h"
#include "lobdefine.h"
#include "NetCmdHelper.h"
#include "NetCommand.h"
#include "NetCommandID.h"
#include "rdpbasedef.h"
#include "rdp_const.h"
#include "sgdef.h"
#include "DbBaseSession.h"
//==================================================================================================

/*enum DB_REQUEST_RETVAL
{
	NETCMD_RETVAL_COMM_ERROR			=-2,			//���ӷ������
	NETCMD_RETVAL_ERROR					=-1,			//DB���ش���
	NETCMD_RETVAL_SUCCESS				=0,				//DB���سɹ�
	NETCMD_RETVAL_WARNING				=1,				//DB���ؾ���
};
#define DBCMD_NET_VERSION_1		1
#define DBCMD_NET_VERSION_2		2
#define DBCMD_NET_VERSION		3
#define	DBCMD_GETVERSION(VERSION) 	if(VERSION<0) { VERSION=DBCMD_NET_VERSION; if(VERSION<0) return false; }
//==================================================================================================
class CNetCmdHead
{
public:
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int			buf_size();
	CNetCmdHead()
	{
		CmdVersion=DBCMD_NET_VERSION;
//		ClientIdentify=0;
		RetVal=NETCMD_RETVAL_SUCCESS;
		ZipFlag=0;
		RetInfo="";
		CmdType=0;
		FrameLen=0;
		FrameNo=0;
		FinishFlag=true;
		DBNo=DEFAULT_DBNO;
		WorkSpaces.clear();
	};
public:
	SG_USHORT			CmdType;				//�����
	SG_UCHAR			ZipFlag;				//ѹ�����
	SG_UCHAR			FinishFlag;	//��������־
	SG_INT				FrameNo;	//�����,��0��ʼ
	ACE_UINT32			CmdVersion;				//����汾��
	ACE_UINT32			FrameLen;				//�����
	ACE_UINT32			DBNo;					//���������ݿ�No
	ACE_UINT32			RetVal;					//������
	ARR_UINT32			WorkSpaces;				//�����ռ伯��
	CSgString			RetInfo;				//������Ϣ
};
*/
typedef CNetCmdHead CDBCmdHead;
class CReadDatNetCmd_Req:public CNetCmdHead
{
public:
	SG_UCHAR SortFlag;	//0:������  1:����  2:����
	SG_UINT StartRow;
	SG_UINT MaxRow;
	CReadDatNetCmd_Req()
	{
		StartRow=0;
		MaxRow=0;
		SortFlag=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//           ��ϵ��ӿ�
//==================================================================================================
//	��ȡ���ݿ��¼������
class CDBCmd_ReadRecorder_Req : public CReadDatNetCmd_Req
{
public:
//	SG_UINT			StartRow;
//	SG_UINT			MaxRow;
	CSgString		SQLBuf;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_ReadRecorder_Req()
	{
	//	StartRow=0;
	//	MaxRow=0;
		SQLBuf="";
	};
};
class CDBCmd_CompileReadRecorder_Req: public CDBCmd_ReadRecorder_Req
{
public:
	CSgDataSet		*pDataSet;
	CSgDataSet		DataSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_CompileReadRecorder_Req()
	{
		pDataSet=NULL;
	};
};
typedef CDBCmd_ReadRecorder_Req CDBCmd_ReadLobRecorder_Req;
typedef CDBCmd_CompileReadRecorder_Req CDBCmd_CompileReadLobRecorder_Req;

class CDBCmd_ReadGeoRecorder_Req : public CDBCmd_ReadRecorder_Req
{
public:
	CSgLine			*pSgLine;
	CSgLine			SgLine;
	SG_INT			relationType;
	CSgString       pszAndOr;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_ReadGeoRecorder_Req()
	{
		pSgLine=NULL;
		relationType = 10; // SPATIAL_INSIDE;
		pszAndOr="and";
	};
};
class CNetCmdVerInfo
{
public:
	SG_INT		DatVerNo;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CNetCmdVerInfo()
	{
		DatVerNo = DEFAULT_DATVER_RUN;
	};
};

class CDBCmd_ReadVerRecorder_Req : public CReadDatNetCmd_Req,public CNetCmdVerInfo
{
public:
	SG_INT		ObjType; //�豸����
	SG_UCHAR	IsGeoFlag; //�Ƿ��Ǽ��α�
	CSgString	Fields;
	CSgString	WhereSQL;
	CSgDataSet	*pCompileDataSet; //��������
	CSgDataSet	CompileDataSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_ReadVerRecorder_Req()
	{
		ObjType = 0;
		IsGeoFlag = false;
		Fields = "";
		WhereSQL = "";
		pCompileDataSet = NULL;
	};
};

//	��ȡ���ݿ��¼�ķ���
template <class T>
class CDBCmd_ReadRecorder_ResT: public CNetCmdHead
{
public:
	T		RetDat;
	T		*pRetDat;	//���pRetDat!=NULL ��ʹ��pRetDat�������л�
	CDBCmd_ReadRecorder_ResT()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_UINT StartRow,SG_UINT RowCnt,SG_INT VerNo=-1)
	{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
				return false;
		T *pDatSet=pRetDat;
		if(pDatSet==NULL)
			pDatSet=&RetDat;
		if(RowCnt==0&&StartRow==0)
		{
	/*		if(ar.IsLoading())
				pDatSet->AppendDataSet(ar);
			else
	*/
				pDatSet->Serialize(ar);
		}
		else
		{

			int send_rownum;
			if(RowCnt>pDatSet->GetRecordNums()-StartRow||RowCnt==0)
				send_rownum=pDatSet->GetRecordNums()-StartRow;
			else send_rownum=RowCnt;

			CSgObjects rows;
			rows.SetSize(send_rownum);
			for(int i=0;i<send_rownum;i++)
				rows.AddNoCheck(StartRow+i);
			pDatSet->Serialize(ar,&rows);
		}
		return true;
	};
	virtual SG_BOOL		AppendSerialize(CSgArchive & ar,SG_INT VerNo=-1)
	{
		if(ar.IsLoading()==false)
			return false;
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
				return false;
		T *pDatSet=pRetDat;
		if(pDatSet==NULL)
			pDatSet=&RetDat;
		pDatSet->AppendDataSet(ar);
		return true;
	};
/*	virtual SG_BOOL	AppendSerialize(VECT_VOIDPT &ArList,SG_INT VerNo=-1)
	{
		CSgArchive *arPtr;
		int i;
		for(i=0;i<ArList.size();i++)
		{
			arPtr=(CSgArchive *)ArList[i];
			if(arPtr==NULL)
				continue;
			if(arPtr->IsLoading()==false)
				return false;
			if(CNetCmdHead::Serialize(*arPtr,VerNo)==false)
				return false;
		}
		T *pDatSet=pRetDat;
		if(pDatSet==NULL)
			pDatSet=&RetDat;
		((CSgDataSet *)pDatSet)->AppendDataSet(ArList);
		return true;
	};
*/
	virtual int buf_size()
	{
		return INT_MAX;
	};
};
typedef CDBCmd_ReadRecorder_ResT <CSgDataSet >   CDBCmd_ReadRecorder_Res;
typedef CDBCmd_ReadRecorder_ResT <CSgLobDataSet >   CDBCmd_ReadLobRecorder_Res;
typedef CDBCmd_ReadRecorder_ResT <CSgGeoDataSet >   CDBCmd_ReadGeoRecorder_Res;
typedef CDBCmd_ReadRecorder_Res CDBCmd_CompileReadRecorder_Res;
typedef CDBCmd_ReadLobRecorder_Res CDBCmd_CompileReadLobRecorder_Res;
typedef CDBCmd_ReadLobRecorder_Res CDBCmd_ReadVerRecorder_Res;

class CDBCmd_ReadTableInfo_Req :public CNetCmdHead
{
public:
	CSgString TblName;
	CDBCmd_ReadTableInfo_Req()
	{
		TblName = "";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
class CDBCmd_ReadTableInfo_Res : public CNetCmdHead
{
public:
	CSgDataSet		RetDat;
	CSgDataSet		*pRetDat;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_ReadTableInfo_Res()
	{
		pRetDat = NULL;
		RetDat.Reset();
	};
};

class CDBCmd_BatchReadRecorder_Req: public CNetCmdHead
{
public:
	CSgDataSet		DataSet;
	CSgDataSet		*pDataSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_BatchReadRecorder_Req()
	{
		pDataSet=NULL;
		DataSet.Reset();
	};
};
class CDBCmd_BatchReadRecorder_Res: public CNetCmdHead
{
public:
	CSgDataSet				RetInfo_DatSet;		//������Ϣ�ļ���,��RETVAL RETINFO�����ֶ�,
	CSgDataSetArray_ObjOper	RetDataSetArray;		//OperType�̶�Ϊ1
	CSgDataSetArray_ObjOper	*pRetDataSetArray;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_BatchReadRecorder_Res()
	{
		pRetDataSetArray=NULL;
	};
};


//�������ݿ��¼������
template <class T>
class CDBCmd_InsertRecorder_ReqT : public CNetCmdHead
{
public:
	T		DatSet;
	T		*pDatSet;	//���pRetDat!=NULL ��ʹ��pRetDat�������л�
	CDBCmd_InsertRecorder_ReqT()
	{
		pDatSet=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1)
	{
			if(CNetCmdHead::Serialize(ar,VerNo)==false)
				return false;
		if(pDatSet)
			pDatSet->Serialize(ar);
		else
			DatSet.Serialize(ar);
		return true;
	};
	virtual int buf_size()
	{
		return INT_MAX;
	};
};
typedef CDBCmd_InsertRecorder_ReqT <CSgDataSet >   CDBCmd_InsertRecorder_Req;
typedef CDBCmd_InsertRecorder_ReqT <CSgLobDataSet >   CDBCmd_InsertLobRecorder_Req;
typedef CDBCmd_InsertRecorder_ReqT <CSgGeoDataSet >   CDBCmd_InsertGeoRecorder_Req;

class CDBCmd_InsertVerRecorder_Req : public CNetCmdHead,public CNetCmdVerInfo
{
public:
	SG_INT	ObjType;
	SG_UCHAR IsGeoFlag;
	CSgLobDataSet		DataSet;
	CSgLobDataSet		*pDataSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_InsertVerRecorder_Req()
	{
		ObjType = 0;
		IsGeoFlag = 0;
		pDataSet = NULL;
		DataSet.Reset();
	};
};

//�������ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_InsertRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertVerRecorder_Res;

//�޸����ݿ��¼������
template <class T>
class CDBCmd_UpdateRecorder_ReqT : public CNetCmdHead
{
public:
	T		DatSet;
	T		*pDatSet;	//���pRetDat!=NULL ��ʹ��pRetDat�������л�
	CDBCmd_UpdateRecorder_ReqT()
	{
		pDatSet=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1)
	{
			if(CNetCmdHead::Serialize(ar,VerNo)==false)
				return false;
		if(pDatSet)
			pDatSet->Serialize(ar);
		else
			DatSet.Serialize(ar);
		return true;
	};
	virtual int buf_size()
	{
		return INT_MAX;
	};
};
typedef CDBCmd_UpdateRecorder_ReqT <CSgDataSet >   CDBCmd_UpdateRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgLobDataSet >   CDBCmd_UpdateLobRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgGeoDataSet >   CDBCmd_UpdateGeoRecorder_Req;
typedef CDBCmd_InsertVerRecorder_Req CDBCmd_UpdateVerRecorder_Req;

//�޸����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_UpdateRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateVerRecorder_Res;

//�ϲ����ݿ��¼������
typedef CDBCmd_UpdateRecorder_ReqT <CSgDataSet >   CDBCmd_MergeRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgLobDataSet >   CDBCmd_MergeLobRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgGeoDataSet >   CDBCmd_MergeGeoRecorder_Req;
typedef CDBCmd_InsertVerRecorder_Req CDBCmd_MergeVerRecorder_Req;
//�ϲ����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_MergeRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeVerRecorder_Res;

//ɾ�����ݿ��¼������
typedef CDBCmd_UpdateRecorder_ReqT <CSgDataSet >   CDBCmd_DeleteRecorder_Req;
typedef CDBCmd_UpdateVerRecorder_Req   CDBCmd_DeleteVerRecorder_Req;
//ɾ�����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_DeleteRecorder_Res ;
typedef CNetCmdHead CDBCmd_DeleteVerRecorder_Res;

class CDBCmd_CommitDatVer_Req : public CNetCmdHead, public CNetCmdVerInfo
{
public:
	SG_INT		ObjType; //�豸����
	SG_UCHAR	IsGeoFlag; //�Ƿ��Ǽ��α�
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_CommitDatVer_Req()
	{
		ObjType = 0;
		IsGeoFlag = false;
	};
};
typedef CDBCmd_CommitDatVer_Req CDBCmd_RollBackDatVer_Req;
typedef CNetCmdHead CDBCmd_CommitDatVer_Res;
typedef CNetCmdHead CDBCmd_RollBackDatVer_Res;
class CDBCmd_CompareDatVer_Req : public CNetCmdHead
{
public:
	SG_INT		ObjType; //�豸����
	SG_UCHAR	IsGeoFlag; //�Ƿ��Ǽ��α�
	CNetCmdVerInfo DatVer[2];
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_CompareDatVer_Req()
	{
		ObjType = 0;
		IsGeoFlag = false;
		DatVer[0].DatVerNo = 0;
		DatVer[1].DatVerNo = 0;
	};
};
class CDBCmd_CompareDatVer_Res : public CNetCmdHead
{
public:
	CSgDataSetArray_ObjOper DatSetArray;
	CSgDataSetArray_ObjOper *pDatSetArray;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
	CDBCmd_CompareDatVer_Res()
	{
		pDatSetArray = NULL;
	};
};

typedef CDBCmd_CompareDatVer_Req	CDBCmd_CopyDatVer_Req;
typedef CNetCmdHead					CDBCmd_CopyDatVer_Res;
//	ִ�����ݿ��¼������
class CDBCmd_ExecSQL_Req : public CNetCmdHead
{
public:
	CSgString		SQLBuf;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CDBCmd_CompileExecSQL_Req: public CDBCmd_ExecSQL_Req
{
public:
	CSgDataSet		*pDataSet;
	CSgDataSet		DataSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_CompileExecSQL_Req()
	{
		pDataSet=NULL;
	};
};
//	ִ�����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_ExecSQL_Res ;
typedef CNetCmdHead CDBCmd_CompileExecSQL_Res ;

//	ִ�����ݿ�����������𴥷�������������
class CDBCmd_ExecSQLNotTrigger_Req: public CNetCmdHead
{
public:
	CSgString		SQLBuf;
	CSgString		TblName;	//���Ӱ��ı�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	ִ�����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_ExecSQLNotTrigger_Res ;

//�����������ݵ�����
class CDBCmd_TransOper_Req : public CNetCmdHead
{
public:
	CSgDataSetArray_ObjOper		OperDatSetArray;
	CSgDataSetArray_ObjOper    *pOperDatSetArray;
	CDBCmd_TransOper_Req()
	{
		pOperDatSetArray = NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�����������ݵķ���
typedef CNetCmdHead CDBCmd_TransOper_Res ;

//������Դ�����������ݵ�����
class CDBCmd_MultiDBTransOper_Req : public CNetCmdHead
{
public:
	CSgDataSetArray_ObjDBOper		OperDatSetArray;
	CSgDataSetArray_ObjDBOper		*pOperDatSetArray;
	CDBCmd_MultiDBTransOper_Req()
	{
		pOperDatSetArray = NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//������Դ�����������ݵķ���
typedef CNetCmdHead CDBCmd_MultiDBTransOper_Res;

//������Դ�������� �汾���ݵ�����
class CDBCmd_MultiDBTransVerOper_Req : public CNetCmdHead
{
public:
	VECT_TWOINT						OperDatInfoArray; //Va11:IsGeoFlag Val2:DatVerNo
	CSgDataSetArray_ObjDBOper		OperDatSetArray;
	VECT_TWOINT						*pOperDatInfoArray; //Va11:IsGeoFlag Val2:DatVerNo
	CSgDataSetArray_ObjDBOper		*pOperDatSetArray;
	CDBCmd_MultiDBTransVerOper_Req()
	{
		pOperDatInfoArray = NULL;
		pOperDatSetArray = NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
//������Դ�������� �汾���ݵķ���
typedef CNetCmdHead CDBCmd_MultiDBTransVerOper_Res;

//��ȡLob�ֶ����ݵ�����
class CDBCmd_ReadLobField_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	CSgString		LobFieldName;
	CSgString		WhereSQL;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ȡLob�ֶ����ݿ��¼�ķ���
class CDBCmd_ReadLobField_Res : public CNetCmdHead
{
public:
	CSgLobBlock		RetDat;
	CSgLobBlock    *pRetDat;
	CDBCmd_ReadLobField_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//д��Lob�ֶ����ݵ�����
class CDBCmd_WriteLobField_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	CSgString		LobFieldName;
	CSgString		WhereSQL;
	CSgLobBlock     DatSet;
	CSgLobBlock     *pDatSet;
	CDBCmd_WriteLobField_Req()
	{
		pDatSet=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//д��Lob�ֶ����ݿ��¼�ķ���
typedef CNetCmdHead CDBCmd_WriteLobField_Res ;
#ifndef SG_MINIBOX_PLAT
typedef CNetCmdHead CDBCmd_GetDBType_Req;
typedef CNetCmdHead CDBCmd_GetDBType_Res;
#endif
//��ȡ��ǰ��ϵͳʱ��
typedef CNetCmdHead CDBCmd_GetSysDate_Req ;
//��ȡ��ǰ��ϵͳʱ��ķ���
class CDBCmd_GetSysDate_Res : public CNetCmdHead
{
public:
	SG_UINT		SysTime;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

class CDBCmd_GetIDVal_Req : public CNetCmdHead
{
public:
	CSgString		AllocName;
	SG_UINT			Cnt;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

class CDBCmd_GetIDVal_New_Req: public CNetCmdHead
{
public:
	CSgString		AllocName;
	SG_UINT			Cnt;
	SG_INT			ReqWS;	//����ID�Ĺ����ռ�
	CDBCmd_GetIDVal_New_Req()
	{
		Cnt=1;
		ReqWS=0;
		AllocName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CDBCmd_GetIDVal_Res : public CNetCmdHead
{
public:
	CSgObjects	ObjIDS;
	CSgObjects  *pObjIDS;
	CDBCmd_GetIDVal_Res()
	{
		pObjIDS=NULL;
	};
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CDBCmd_GetSDEOwner_Req;
class CDBCmd_GetSDEOwner_Res : public CNetCmdHead
{
public:
	CSgString	Owner;
	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//ͼ�ε��ӷ�������
class CDBCmd_GeoOverlay_Req : public CNetCmdHead
{
public:
	CSgLine			*pLine1;
	CSgLine			*pLine2;
	CSgLine			Line1;
	CSgLine			Line2;
	CDBCmd_GeoOverlay_Req()
	{
		pLine1=pLine2=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//ͼ�ε��ӷ������󷵻�
class CDBCmd_GeoOverlay_Res : public CNetCmdHead
{
public:
	SG_INT		 CommonNums;
	CSgLine      *pCommonLines;
	CDBCmd_GeoOverlay_Res()
	{
		pCommonLines=NULL;
	};
	~CDBCmd_GeoOverlay_Res()
	{
		if(pCommonLines)
			delete []pCommonLines;
		pCommonLines=NULL;
		CommonNums=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//ͼ��͹����������
class CDBCmd_CalGeoBuffer_Req : public CNetCmdHead
{
public:
	SG_SHORT		nFeatureType;
	SG_DOUBLE		dWidth;
	CSgPoint		*pPoints;
	CSgPoint		Points;
	CDBCmd_CalGeoBuffer_Req()
	{
		pPoints=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//ͼ��͹���������󷵻�
class CDBCmd_CalGeoBuffer_Res : public CNetCmdHead
{
public:
	CSgLine				*pLine;
	CSgLine				Line;
	CDBCmd_CalGeoBuffer_Res()
	{
		pLine=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CDBCmd_CalLineGeoBuffer_Req : public CNetCmdHead
{
public:
	SG_SHORT		nFeatureType;
	SG_DOUBLE		dWidth;
	CSgLine				*pLine;
	CSgLine				Line;
	CDBCmd_CalLineGeoBuffer_Req()
	{
		pLine=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//ͼ��͹���������󷵻�
class CDBCmd_CalLineGeoBuffer_Res : public CNetCmdHead
{
public:
	CSgLine				*pLine;
	CSgLine				Line;
	CDBCmd_CalLineGeoBuffer_Res()
	{
		pLine=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ȡ������
class CDBCmd_ReadTableName_Req : public CNetCmdHead
{
public:
	CSgString		DBName;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CDBCmd_ReadTableName_Res : public CNetCmdHead
{
public:
	CSgDataSet		RetDat;
	CSgDataSet		 *pRetDat;
	CDBCmd_ReadTableName_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//������
class CDBCmd_CreateTable_Req : public CNetCmdHead
{
public:
	CSgDataSet		DatSet;
	CSgDataSet		 *pDatSet;
	CDBCmd_CreateTable_Req()
	{
		pDatSet=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CDBCmd_CreateTable_Res;
//ɾ���ļ�
class CDBCmd_RemoveFile_Req: public CNetCmdHead
{
public:
	CSgString		DBName;
	CSgString		FileName;
	CDBCmd_RemoveFile_Req()
	{
		DBName="";
		DBNo=DEFAULT_SYS_DBNO;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CDBCmd_RemoveFile_Res;
//��ȡ�ļ���Ϣ
typedef CDBCmd_RemoveFile_Req CDBCmd_GetFileInfo_Req;
class CDBCmd_GetFileInfo_Res: public CNetCmdHead
{
public:
	S_NoSqlFileInfo		FileInfo;
	S_NoSqlFileInfo		*pFileInfo;
	CDBCmd_GetFileInfo_Res()
	{
		pFileInfo=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ȡ�ļ��б�
class CDBCmd_GetFileNameArray_Req: public CNetCmdHead
{
public:
	CSgString		ReqStr;
	CSgString		DBName;
	CDBCmd_GetFileNameArray_Req()
	{
		ReqStr="";
		DBName="";
		DBNo=DEFAULT_SYS_DBNO;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

class CDBCmd_GetFileNameArray_Res: public CNetCmdHead
{
public:
	CSgStringArray		FileNameList;
	CSgStringArray		*pFileNameList;
	CDBCmd_GetFileNameArray_Res()
	{
		pFileNameList=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//==================================================================================================
//    �������ӿ�         
//==================================================================================================
class CEvtSrv_SendRawEvt_Req:public CNetCmdHead
{
public:
	VECT_RAWEVENT	RawEvtList;
	VECT_RAWEVENT	*pRawEvtList;
	CEvtSrv_SendRawEvt_Req()
	{
		RawEvtList.clear();
		pRawEvtList=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//����ϵͳ��װĿ¼
typedef CNetCmdHead		CEvtSrv_SendRawEvt_Res;

//==================================================================================================
//    ʵʱ��ӿ�         
//==================================================================================================

//	��ȡ���ݿ��¼������
typedef CDBCmd_ReadRecorder_Req CHSDA_ReadRecorder_Req;
typedef CDBCmd_ReadRecorder_Res CHSDA_ReadRecorder_Res;

//	��ȡ���ݿ���¼������
class CHSDA_ReadTblRecorder_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//	��ȡ���ݿ��¼�ķ���
//typedef CDBCmd_ReadRecorder_Res CHSDA_ReadTblRecorder_Res;
//	��ȡ���ݿ��¼�ķ���
class CHSDA_ReadTblRecorder_Res : public CNetCmdHead
{
public:
	CSgDataSet		RetDat;
	CSgDataSet		*pRetDat;
	CHSDA_ReadTblRecorder_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};


//	ִ�����ݿ��¼������
typedef CDBCmd_ExecSQL_Req CHSDA_ExecSQL_Req;
typedef CDBCmd_ExecSQL_Res CHSDA_ExecSQL_Res;

// ����ʵʱ������������
class CHSDA_SubscribeData_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	CSgString		Fields;
	SG_SHORT		FreshTime;	//ˢ��ʱ��
	CSgDataSet		DatSet;	//�����¼����Ϊ0�����ı��е����ж���
	CSgDataSet		*pDatSet;	//�����¼����Ϊ0�����ı��е����ж���
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CHSDA_SubscribeData_Req()
	{
		FreshTime=3;
		pDatSet=NULL;
	};
};

// ����ʵʱ�������ݷ���
class CHSDA_SubscribeData_Res : public CNetCmdHead
{
public:
	SG_UINT64			StreamHandle;
	CSgDataSet		RetDat;
	CSgDataSet		*pRetDat;
	CHSDA_SubscribeData_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

// ȡ��ʵʱ������������
class CHSDA_CancelSubscribe_Req : public CNetCmdHead
{
public:
	SG_UINT64			StreamHandle;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
// ȡ��ʵʱ�������ݷ���
typedef CNetCmdHead CHSDA_CancelSubscribe_Res ;


// ��ȡ����ʵʱ�����仯��������
class CHSDA_GetChangeData_Req : public CNetCmdHead
{
public:
	SG_UINT64			StreamHandle;
	SG_UCHAR		GetType;	//2:��ȡ�仯����  1:��ȡȫ����
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
// ��ȡ����ʵʱ�����仯����
typedef CHSDA_SubscribeData_Res CHSDA_GetChangeData_Res;
#define SG_YK_OPERTYPE_EXEC_DIRECT		0	//ֱ��ִ��
#define SG_YK_OPERTYPE_SELECT			1	//Ԥ��
#define SG_YK_OPERTYPE_EXEC				2	//ִ��
#define SG_YK_OPERTYPE_CANCEL			3	//ȡ��

//ң�ز���
class CHSDA_YKOper_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType;//	0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
	SG_INT			ObjType;
	SG_INT			ObjID;
	SG_INT			Value;
	CSgString		OperMan;
	CSgString		CheckMan;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	void operator = (const CHSDA_YKOper_Req &obj)
	{
		OperType=obj.OperType;
		ObjType=obj.ObjType;
		ObjID=obj.ObjID;
		Value=obj.Value;
		OperMan=obj.OperMan;
		CheckMan=obj.CheckMan;
	};
};
typedef CNetCmdHead CHSDA_YKOper_Res;

//ң������
class CHSDA_YTOper_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType; //0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
	SG_INT			ObjType;
	SG_INT			ObjID;
	SG_UCHAR		ValueType;	//
	SG_DOUBLE		Value;
	CSgString		OperMan;
	CSgString		CheckMan;
	void operator = (const CHSDA_YTOper_Req &obj)
	{
		OperType=obj.OperType;
		ObjType=obj.ObjType;
		ObjID=obj.ObjID;
		ValueType=obj.ValueType;
		Value=obj.Value;
		OperMan=obj.OperMan;
		CheckMan=obj.CheckMan;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_YTOper_Res;

//�˹����ò���
class CHSDA_LockRtData_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType;	//0:�������� 1:����  2:����
	SG_INT			ObjType;
	SG_INT			ObjID;
	SG_DOUBLE		Value;
	void operator = (const CHSDA_LockRtData_Req &obj)
	{
		OperType=obj.OperType;
		ObjType=obj.ObjType;
		ObjID=obj.ObjID;
		Value=obj.Value;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_LockRtData_Res;

class CHSDA_ManSetRtData_Req: public CNetCmdHead
{
public:
	SG_UCHAR	OperType;   //0:����ȡ��  1:���ò�ȷ�ϱ�λ  2:ȷ�ϱ�λ����������
	SG_INT		ObjType;		 
	SG_INT		ObjID;
	SG_INT		DevType;
	SG_INT		DevID;
	SG_USHORT   Terminal;
	SG_USHORT	MeasType;
	SG_DOUBLE	Val;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_ManSetRtData_Res;

//����ǰ�õ��������
class CHSDA_CommSrvCmd_Req : public CNetCmdHead
{
public:
	SG_INT			   RtuID; //mcu id
	S_COMMRTU_TASKINFO TaskInfo;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_CommSrvCmd_Res;
//����ǰ�õ��������
class CHSDA_CommSrvCmd_New_Req: public CHSDA_CommSrvCmd_Req
{
public:
	CSgDataSetArray_ObjOper	DataSetArray;		//OperType�̶�Ϊ1
	CSgDataSetArray_ObjOper	*pDataSetArray;
	CHSDA_CommSrvCmd_New_Req()
	{
		pDataSetArray=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_CommSrvCmd_New_Res;
//����״̬�ı�����
#ifndef SG_MINIBOX_PLAT
class CHSDA_ChangeEvtStatus_Req:public CNetCmdHead
{
public:
	VECT_EVT_NOTIYMSG  MsgList;
	VECT_EVT_NOTIYMSG  *pMsgList;
	CHSDA_ChangeEvtStatus_Req()
	{
		MsgList.clear();
		pMsgList=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_ChangeEvtStatus_Res;

#endif
class CHSDA_GetDevPointInfo_Req: public CNetCmdHead
{
public:
	int				ObjType;		//��������� 500:yc 501:yx 502:kwh 
	short int		DevType;
	int				DevID;
	short int       Terminal;
	short int		MeasType;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	void operator = (const CHSDA_GetDevPointInfo_Req &obj)
	{
		ObjType=obj.ObjType;
		DevType=obj.DevType;
		DevID=obj.DevID;
		Terminal=obj.Terminal;
		MeasType=obj.MeasType;
	};
};

class CHSDA_GetDevPointInfo_Res: public CNetCmdHead
{
public:
	CSgDataSet	RetDat;
	CSgDataSet	*pRetDat;
	CHSDA_GetDevPointInfo_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CHSDA_GetPointInfo_Req: public CNetCmdHead
{
public:
	SG_INT			ObjType;	//����豸����
	CSgString		QueryFields;	//������ֶ�
	VECT_INT		PtIDList;
	VECT_INT		*pPtIDList;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CHSDA_GetPointInfo_Req()
	{
		PtIDList.clear();
		pPtIDList=NULL;
	};
};
typedef CHSDA_GetDevPointInfo_Res CHSDA_GetPointInfo_Res;

#ifndef SG_MINIBOX_PLAT
class CHSDA_GetDevPointInfo_New_Req: public CHSDA_GetDevPointInfo_Req
{
public:
	CSgString		QueryFields;	//������ֶ�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	void operator = (const CHSDA_GetDevPointInfo_New_Req &obj)
	{
		ObjType=obj.ObjType;
		DevType=obj.DevType;
		DevID=obj.DevID;
		Terminal=obj.Terminal;
		MeasType=obj.MeasType;
		QueryFields=obj.QueryFields;
	};
};
class CHSDA_GetDevsPointInfo_Req: public CNetCmdHead
{
public:
	SG_INT			ObjType;	//����豸����
	CSgString		QueryFields;	//������ֶ�
	CSgDataSet	DatSet; //���� OBJTYPE OBJID TERMINAL MEASURE�ֶ�
	CSgDataSet	*pDatSet;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1,CSgObjects *pRcdNoList=NULL);
	virtual int buf_size();
	CHSDA_GetDevsPointInfo_Req()
	{
		pDatSet=NULL;
	};
};
typedef CHSDA_GetDevPointInfo_Res CHSDA_GetDevPointInfo_New_Res;
typedef CHSDA_GetDevPointInfo_Res CHSDA_GetDevsPointInfo_Res;

#define SG_HSDA_RDBOPER_CHECKRDB			1	//���ʵʱ��
#define SG_HSDA_RDBOPER_CHECKRDBRCD			2	//���ʵʱ�������
#define SG_HSDA_RDBOPER_BACKUPTBL			3	//����ʵʱ���
#define SG_HSDA_RDBOPER_LOADRTBL			4	//���¼���ʵʱ��
#define SG_HSDA_RDBOPER_UNLOCKTBL			5	//������ʵʱ���

class CHSDA_RDBMemOper_Req : public CNetCmdHead
{
public:
	SG_INT			OperType;	//��������
	CSgString		TblName;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1, CSgObjects *pRcdNoList = NULL);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_RDBMemOper_Res;
//�½�һ������ʵʱ��
#define SG_RDB_SCHEMA_PROCMODE_CANFREE			0x00000001 //���ǳ�פ�ڴ�
#define SG_RDB_SCHEMA_PROCMODE_RECV_PARACHAN		0x00000002 //���ܲ����仯����
#define SG_RDB_SCHEMA_PROCMODE_RECV_DATCHAN		0x00000004 //�������ݱ仯����
#define SG_RDB_SCHEMA_PROCMODE_CLOUDSYNC			0x00000008 //��������ͬ��
class CHSDA_RTDBLoadPara
{
public:
	SG_INT				LoadType; //0: �����ݿ����  1�����ļ�����
	SG_INT				RtDBVerNo;
	SG_INT				SchemaDBNo;
	SG_INT				SchemaProcMode;
	CSgString			SrvTypeStr;  //LoadType=0 ��SrvType��Ϣ 
	CSgString			FileName;  //LoadType=1:���ļ�������
	VECT_TWOSTRING		ReplaceKey; //��������
	CHSDA_RTDBLoadPara()
	{
		Init();
	};
	int Init()
	{
		LoadType = 0;
		RtDBVerNo = SG_RDB_VERNO;
		SrvTypeStr = "";
		FileName = "";
		SchemaDBNo = 1;
		SchemaProcMode = SG_RDB_SCHEMA_PROCMODE_CANFREE;
		ReplaceKey.clear();
		return true;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();

};
class CHSDA_RDB_NewCCRtDB_Req : public CNetCmdHead
{
public:
	CHSDA_RTDBLoadPara LoadPara;
	CHSDA_RTDBLoadPara *pLoadPara;
	CHSDA_RDB_NewCCRtDB_Req()
	{
		pLoadPara = NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_RDB_NewCCRtDB_Res;
//ɾ��һ������ʵʱ��
typedef CNetCmdHead CHSDA_RDB_DeleteCCRtDB_Req;
typedef CNetCmdHead CHSDA_RDB_DeleteCCRtDB_Res;
//��ȡһ���µ�SchemaHandler
typedef CNetCmdHead CHSDA_GetNewSchemaHandler_Req;
typedef CNetCmdHead CHSDA_GetNewSchemaHandler_Res;

#endif
//==================================================================================================
//    ��ʷ��ӿ�         
//==================================================================================================

//	���ղ���ѯ��ʷ���ݵ�����
class CTSDA_QueryDataByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//�������
	SG_UINT		StartYMD;	//��ʼ������
	SG_UINT		EndYMD;		//����������
	SG_UINT		Interval;	//��ȡ���,����Ϊ��λ
	CSgDataSet	DatSet;		//��ȡ�Ĳ��id���� ��ID�ֶ� FALG�ֶ�
	CSgDataSet  *pDatSet;
	CTSDA_QueryDataByPt_Req()
	{
		pDatSet=NULL;
		Interval=0;
	};
	void  operator = (const CTSDA_QueryDataByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ղ���ѯ��ʷ���ݵķ���
class CTSDA_QueryDataByPt_Res : public CNetCmdHead
{
public:
	CSgDataSet	RetDat;		//��ȡ�Ľ����
	CSgDataSet	*pRetDat;
	CTSDA_QueryDataByPt_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ղ���ѯ��ʷ���ݵ�����
class CTSDA_QueryDataByPt_New_Req: public CTSDA_QueryDataByPt_Req
{
public:
	SG_INT		StartHMS;	//��ʼʱ����
	SG_INT		EndHMS;		//����ʱ����
	CTSDA_QueryDataByPt_New_Req()
	{
		StartHMS=0;
		EndHMS=235959;
	};
	void  operator = (const CTSDA_QueryDataByPt_New_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef  CTSDA_QueryDataByPt_Res CTSDA_QueryDataByPt_New_Res;
//#ifndef SG_MINIBOX_PLAT
#define SG_TSDA_QUERYMODE_ONLYCNT			0x00000001	//Ϊ1ʱֻ���ؼ�¼����
#define SG_TSDA_QUERYMODE_PUTLACKBYLAST		0x00000002	//Ϊ1ʱ����ȱ�ٲ�� ��ǰ����㲹��
#define SG_TSDA_QUERYMODE_PUTLACKBYSLOPE	0x00000004	//Ϊ1ʱ����ȱ�ٲ�� ��ǰ����㲹��
//	���ղ���ѯ��ʷ���ݵ�����
class CTSDA_QueryDataByPt_Append_Req: public CTSDA_QueryDataByPt_New_Req
{
public:
	SG_UINT		QueryMode;		//����ģʽ,��λ���: bit0:Ϊ1ʱֻ���ؼ�¼����
	CSgString	AppendWhereSql;	//���ӵ��������
	CTSDA_QueryDataByPt_Append_Req()
	{
		QueryMode=0;
		AppendWhereSql.Format("");
	};
	void  operator = (const CTSDA_QueryDataByPt_Append_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef  CTSDA_QueryDataByPt_New_Res CTSDA_QueryDataByPt_Append_Res;
//#endif
//	���ղ���ѯ��ʷͳ�����ݵ�����
class CTSDA_QueryStatByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//�������
	SG_UINT		StartYMD;	//��ʼ������
	SG_UINT		EndYMD;		//����������
	CSgDataSet	DatSet;		//��ȡ�Ĳ��id���� ��ID�ֶ� FALG�ֶ�
	CSgDataSet	*pDatSet;		//��ȡ�Ĳ��id���� ��ID�ֶ� FALG�ֶ�
	CTSDA_QueryStatByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_QueryStatByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ղ���ѯ��ʷͳ�����ݵķ���
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryStatByPt_Res;
 
//	���ղ���ѯ��ʷ�������ݵ�����
class CTSDA_QueryValuesByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//�������
	SG_UINT		YMD;		//������
	SG_UINT		HMS;		//ʱ����
	CSgDataSet	DatSet;		//��ȡ�Ĳ��id���� ��ID�ֶ� FALG�ֶ�
	CSgDataSet	*pDatSet;		//��ȡ�Ĳ��id���� ��ID�ֶ� FALG�ֶ�
	CTSDA_QueryValuesByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_QueryValuesByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ղ���ѯ��ʷ�������ݵķ���
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryValuesByPt_Res;

//	�����豸��ѯ��ʷ���ݵ�����
typedef CTSDA_QueryDataByPt_Req CTSDA_QueryDataByDev_Req;
typedef CTSDA_QueryDataByPt_New_Req CTSDA_QueryDataByDev_New_Req;
typedef CTSDA_QueryDataByPt_Append_Req CTSDA_QueryDataByDev_Append_Req;

//	�����豸��ѯ��ʷ���ݵķ���
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryDataByDev_Res;
typedef CTSDA_QueryDataByPt_New_Res CTSDA_QueryDataByDev_New_Res;
typedef CTSDA_QueryDataByPt_Append_Res CTSDA_QueryDataByDev_Append_Res;

//	�����豸��ѯ��ʷͳ�����ݵ�����
typedef CTSDA_QueryStatByPt_Req CTSDA_QueryStatByDev_Req;
//	�����豸��ѯ��ʷͳ�����ݵķ���
typedef CTSDA_QueryStatByPt_Res CTSDA_QueryStatByDev_Res;

//	�����豸��ѯ��ʷ�������ݵ�����
typedef CTSDA_QueryValuesByPt_Req CTSDA_QueryValuesByDev_Req;
//	�����豸��ѯ��ʷ�������ݵķ���
typedef CTSDA_QueryValuesByPt_Res CTSDA_QueryValuesByDev_Res;


//	���ղ���ѯ��ʷ���ݵ����緵��
class CTSDA_QueryDataByDev_NetRes : public CNetCmdHead
{
public:
	CSgDataSet	RetPara;	//��ȡ�Ĳ�����
	CSgDataSet	RetDat;		//��ȡ�Ľ����
	CSgDataSet	*pRetPara;	//��ȡ�Ĳ�����
	CSgDataSet	*pRetDat;		//��ȡ�Ľ����
	CTSDA_QueryDataByDev_NetRes()
	{
		pRetDat=pRetPara=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	�����豸��ѯ��ʷͳ�����ݵ����緵��
typedef CTSDA_QueryDataByDev_NetRes CTSDA_QueryStatByDev_NetRes;
//	�����豸��ѯ��ʷ�������ݵ����緵��
typedef CTSDA_QueryDataByDev_NetRes CTSDA_QueryValuesByDev_NetRes;

//	���ղ�������ʷ���ݵ�����
class CTSDA_SaveDataByPt_Req : public CNetCmdHead
{
public:
	SG_INT		ObjType;	//�������
	CSgDataSet	DatSet;		//��ȡ�Ĳ��id���� ��YMD  HMS  ID  FLAG  VALUE STATUS
	CSgDataSet	*pDatSet;	//��ȡ�Ĳ��id���� ��YMD  HMS  ID  FLAG  VALUE STATUS
	CTSDA_SaveDataByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_SaveDataByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//��ȡ���ݿ�����״��
#ifndef SG_MINIBOX_PLAT
typedef  CNetCmdHead CCloud_GetDBLinkStat_Req;
class CCloud_GetDBLinkStat_Res: public CNetCmdHead
{
public:
	CSgDataSet	RetDat;		//��ȡ�Ĳ��id���� ��SRVNO MIN_LINK MAX_LINK REAL_LINK ACTIVE_LINK
	CSgDataSet	*pRetDat;	//��ȡ�Ĳ��id���� ��SRVNO MIN_LINK MAX_LINK REAL_LINK ACTIVE_LINK
	CCloud_GetDBLinkStat_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
#endif
//	���ղ�������ʷ���ݵķ���
typedef CNetCmdHead CTSDA_SaveDataByPt_Res;

//	�����豸������ʷ���ݵ�����
typedef CTSDA_SaveDataByPt_Req CTSDA_SaveDataByDev_Req;
typedef CTSDA_SaveDataByPt_Res CTSDA_SaveDataByDev_Res;

//	���ղ��ɾ����ʷ���ݵ�����
typedef CTSDA_SaveDataByPt_Req CTSDA_DelDataByPt_Req;
typedef CTSDA_SaveDataByPt_Res CTSDA_DelDataByPt_Res;

//	�����豸ɾ����ʷ���ݵ�����
typedef CTSDA_DelDataByPt_Req CTSDA_DelDataByDev_Req;
typedef CTSDA_DelDataByPt_Res CTSDA_DelDataByDev_Res;

//==================================================================================================
//    �ļ�����ӿ�         
//==================================================================================================
class CFPS_Download_Req : public CNetCmdHead
{
public:
	SG_UINT	ClassID ;
	CSgString ID , Hash ;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

class CFPS_Download_Res : public CNetCmdHead
{
public:
	CSgLobBlock Content ;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

class CFPS_Publish_Req : public CNetCmdHead
{
public:
	SG_UINT	ClassID ;
	CSgString ID , Hash ;
	CSgLobBlock Content ;

	virtual SG_BOOL Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size( );
};

class CFPS_Publish_Res : public CNetCmdHead
{

};

//==================================================================================================
//    ���Ʒ���ӿ�         
//==================================================================================================
//	���ĳ���߼����ݵ�Ԫ�İ汾��
class CREP_GetLogicCellVer_Req : public CNetCmdHead
{
public:
	SG_INT				 SrvType;	//��������
	S_LOGICCELLINFO		 LogicCell;	//�߼����ݵ�Ԫ
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ĳ���߼����ݵ�Ԫ�İ汾�ŵķ���
class CREP_GetLogicCellVer_Res : public CNetCmdHead
{
public:
	VECT_TWOINT			 LogicCellVer;	//�����߼����ݵ�Ԫ�İ汾��
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//	���ĳ���߼����ݵ�Ԫ�İ汾��
class CREP_GetLogicCellDat_Req : public CNetCmdHead
{
public:
	SG_INT				SrvType;	//��������
	S_LOGICCELLINFO		LogicCell;	//�߼����ݵ�Ԫ
	SG_INT				NodeID;		//�汾�еĽڵ��
	SG_UINT				StartVer;	//��ʼ�汾
	SG_UINT				EndVer;		//��ֹ�汾
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ĳ���߼����ݵ�Ԫ�İ汾�ŵķ���
class CREP_GetLogicCellDat_Res : public CNetCmdHead
{
public:
	SG_UINT				StartVer;	//��ʼ�汾
	SG_UINT				EndVer;		//��ֹ�汾
	CSgDataSetArray_ObjOper		DatArray;	//���ݼ�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//    CPS����ӿ�         
//==================================================================================================
//==================================================================================================
//	������ɺ�ķ��ͱ���,�����̲�ͬ�̷߳�����Ϣ,���迼���ֽ���
class CCPS_ProcOver_Req
{
public:
	SG_INT						CmdType;	//�����
	SG_UINT						HandlerCmdCnt;		//�ڸ������е������
	SG_INT						RequestNo;		//��ͬһ�������е����
	S_TWOINT					NodePort;		//�ڵ�˿ں�
	SG_INT						RetCode;	//���ش���
	SG_BOOL						EndFlag;
	NetCommandReceiveExplain	*pChildRecvData;
};
//	��õ�ǰʵʱ������дָ��
typedef CNetCmdHead CCPS_QueryRealEvtWritePt_Req ;
//	��õ�ǰʵʱ�����ķ���
class CCPS_QueryRealEvtWritePt_Res : public CNetCmdHead
{
public:
//	SG_INT				WriteCircuitCnt; //ʵʱ��������е�ѭ������
	SG_UINT				WritePt;	//дָ��
	CCPS_QueryRealEvtWritePt_Res()
	{
//		WriteCircuitCnt=-1;
		WritePt=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//	���ʵʱ�����ļ�¼
class CCPS_QueryRealEvt_Req : public CNetCmdHead
{
public:
//	SG_INT				StartCircuitCnt; //ʵʱ��������е�ѭ������
	SG_UINT				StartReadPt;	//��ʼ��ָ��
	SG_INT				MaxRowNum;	//����¼����
	SG_INT				ConfirmFlag;	//0:��������  1��δȷ������  2����ȷ������
	CCPS_QueryRealEvt_Req()
	{
		StartReadPt=MaxRowNum=0;
		ConfirmFlag=0;
//		StartCircuitCnt=-1;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ʵʱ�����ļ�¼�ķ���
class CCPS_QueryRealEvt_Res : public CNetCmdHead
{
public:
//	SG_INT				LastReadCircuitCnt; //ʵʱ��������е�ѭ������
	SG_UINT				LastReadPt;	//�´ζ�ȡ��ָ��
//	SG_INT				WriteCircuitCnt; //ʵʱ��������е�ѭ������
	SG_UINT				WritePt;	//дָ��
	CSgDataSet			RetDat;		//���ص����ݼ�
	CSgDataSet			*pRetDat;
	CCPS_QueryRealEvt_Res()
	{
		LastReadPt=WritePt=0;
//		LastReadCircuitCnt=WriteCircuitCnt=-1;
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	ȷ��ʵʱ�����¼
class CCPS_ConfirmRealEvt_Req: public CNetCmdHead
{
public:
	SG_UINT				EvtID;	//ʵʱ����ID
	SG_INT				EvtYMD;	//����ķ���ʱ��
	SG_INT				EvtHMS;	//����ķ���ʱ��
	CCPS_ConfirmRealEvt_Req()
	{
		EvtID=0;
		EvtYMD=EvtHMS=-1;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CCPS_ConfirmRealEvt_Res ;
#ifndef SG_MINIBOX_PLAT
typedef CNetCmdHead CCPS_GetCenterID_Req;
typedef CNetCmdHead CCPS_GetCenterID_Res;
#endif

//==================================================================================================
//==================================================================================================
//  ͬ��������
class CDBS_SyncTableData_Req : public CNetCmdHead
{
public:
	SG_INT				SrvType;	//��������
	S_LOGICCELLINFO		LogicCell;	//�߼����ݵ�Ԫ
	SG_INT				NodeID;		//�ڵ��
	SG_UINT64				StartVer;	//��ʼ�汾
	SG_UINT64				EndVer;		//��ֹ�汾
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	���ĳ���߼����ݵ�Ԫ�İ汾�ŵķ���
class CDBS_SyncTableData_Res : public CNetCmdHead
{
public:
	SG_UINT64				EndVer;		//��ֹ�汾
	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//
class CMSGCmd_Post_Req : public CNetCmdHead
{
public:
	SgMail msg;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
};
//==================================================================================================
//           IDMAP����ӿ�
//==================================================================================================
//	��ϵͳת��������ϵͳ������
class CIDMAPCmd_Self2Other_Req : public CNetCmdHead
{
public:
	SG_INT		ClassType;	//���ձ�����
	SG_OBJECTS	SelfObjs;	//��ϵͳ�豸�б�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Self2Other_Req()
	{
		ClassType=1;
	};
};
class CIDMAPCmd_Self2Other_Res: public CNetCmdHead
{
public:
	CSgDataSet	RetDat;	//���ر�ϵͳ����ϵͳ���ձ�  OBJTYPE,OBJID OTHER_ID
	CSgDataSet	*pRetDat;	//���ر�ϵͳ����ϵͳ���ձ�  OBJTYPE,OBJID OTHER_ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Self2Other_Res()
	{
		pRetDat=NULL;
	};
};
//==================================================================================================
//==================================================================================================
//	����ϵͳת���ɱ�ϵͳ������
class CIDMAPCmd_Other2Self_Req : public CNetCmdHead
{
public:
	SG_INT		ClassType;	//���ձ�����
	VECT_STRING		OtherObjs; //�ⲿϵͳ�豸�б�
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Other2Self_Req()
	{
		ClassType=1;
	};
};
class CIDMAPCmd_Other2Self_Res: public CNetCmdHead
{
public:
	CSgDataSet	RetDat;	//���ر�ϵͳ����ϵͳ���ձ�  OBJTYPE,OBJID OTHER_ID
	CSgDataSet	*pRetDat;	//���ر�ϵͳ����ϵͳ���ձ�  OBJTYPE,OBJID OTHER_ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Other2Self_Res()
	{
		pRetDat=NULL;
	};
};
//==================================================================================================
//           ���ݴ������ӿ�
//==================================================================================================
class CDataSrv_Login_Req : public CNetCmdHead
{
public:
	SG_INT		NodeID;		//	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_Login_Req()
	{
	};
};
typedef CNetCmdHead CDataSrv_Login_Res;
//==================================================================================================

typedef CDataSrv_Login_Req CDataSrv_UnLogin_Req;
typedef CNetCmdHead CDataSrv_UnLogin_Res;
//==================================================================================================
class CDataSrv_Operator_Req : public CNetCmdHead
{
public:
	SG_USHORT	Operation;	//	0: ��Ч 1��ң�� 2��ң��
	SG_USHORT	OperType;	//	0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
	SG_INT		ObjType;	//	500��yc 501��yx 
	SG_INT		ObjID;		//	���ID
	SG_DOUBLE	Value;		//	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_Operator_Req()
	{
		Operation=1;
		OperType=0;
	};
};
typedef CNetCmdHead CDataSrv_Operator_Res;
//==================================================================================================
class CDataSrv_SetValue_Req : public CNetCmdHead
{
public:
	SG_USHORT	OperType;	//	0������ 1������ 2������	
	SG_INT	ObjType;	//	
	SG_INT	ObjID;		//	
	SG_DOUBLE	Value;		//	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_SetValue_Req()
	{
	};
};
typedef CNetCmdHead CDataSrv_SetValue_Res;
//==================================================================================================
class CDataSrv_SendRawRtDat_Req : public CNetCmdHead
{
public:
	SG_INT	ObjType;	//	500��yc 501��yx 502��kwh  600:RTU״̬
	CSgDataSet  DatSet;		//  ���ݼ���  YC�����ֶ�:ID FLAG,VALUE STATUS PROCTIME 
							//YX�����ֶ�:ID FLAG,VALUE STATUS PROCTIME MS
							//KWH�����ֶ�:ID FLAG,VALUE STATUS PROCTIME
							//RTU״̬�����ֶ�: ID STATUS PROCTIME
	CSgDataSet  *pDatSet;	//
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_SendRawRtDat_Req()
	{
		pDatSet=NULL;
	};
};
typedef CNetCmdHead CDataSrv_SendRawRtDat_Res;
//==================================================================================================
class CDataSrv_SendHisDat_Req : public CNetCmdHead
{
public:
	SG_INT	ObjType;	//	500��yc 501��yx 502��kwh
	SG_INT	TaskID;		//����Ǻ�̨����ĳ�������,���ǳ��������
	CSgDataSet  DatSet;		//  ���ݼ���  �����ֶ�:ID YMD,HMS,FLAG,STATUS,VALUE
	CSgDataSet  *pDatSet;	//
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_SendHisDat_Req()
	{
		pDatSet=NULL;
	};
};
typedef CNetCmdHead CDataSrv_SendHisDat_Res;
class CDataSrv_SendFile_Req: public CNetCmdHead
{
public:
	SG_INT		Res;	//�����ֶβ���
	SG_INT		TaskID;
	CSgLobDataSet  DatSet;		//���ݼ���  �����ֶ�:YMD,HMS,OBJTYPE,OBJID,DAT
	CSgLobDataSet  *pDatSet;	//
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_SendFile_Req()
	{
		pDatSet=NULL;
		TaskID=0;
	};
};
typedef CNetCmdHead CDataSrv_SendFile_Res;

class CDataSrv_SendRawEvt_Req: public CNetCmdHead
{
public:
	VECT_RAWEVENT		RawEvtList;
	VECT_RAWEVENT		*pRawEvtList;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_SendRawEvt_Req()
	{
		pRawEvtList=NULL;
	};
};
typedef CNetCmdHead CDataSrv_SendRawEvt_Res;

typedef CNetCmdHead CDataSrv_MiniBoxLinkCmd_Req;
typedef CNetCmdHead CDataSrv_MiniBoxLinkCmd_Res;

typedef CNetCmdHead CDataSrv_GetMiniBoxLinkNode_Req;
class CDataSrv_GetMiniBoxLinkNode_Res: public CNetCmdHead
{
public:
	CSgObjects			NodeIDList;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDataSrv_GetMiniBoxLinkNode_Res()
	{
		NodeIDList.ClearObj();
	};
};

//==================================================================================================
//           ǰ�÷���ӿ�
//==================================================================================================
class CCommSrv_Operator_Req:public CNetCmdHead
{
public:
	SG_USHORT	Operation;	//	0: ��Ч 1��ң�� 2��ң��
	SG_USHORT	OperType;	//	0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
	SG_INT		ObjType;	//	500��yc 501��yx 
	SG_INT		ObjID;		//	���ID
	SG_DOUBLE	Value;		//	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_Operator_Req()
	{
		Operation=1;
		OperType=0;
	};
};
typedef CNetCmdHead CCommSrv_Operator_Res;
//==================================================================================================
class CCommSrv_WriteProtSetting_Req:public CNetCmdHead
{
public:
	SG_USHORT	OperType;		//	0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
	SG_INT		RtuID;			//	�ն�ID
	SG_INT		DevAddr;		//	�豸��ַ
	SG_INT		SettingArea;	//	��������
	CSgDataSet  DatSet;		//  ���ݼ���  �����ֶ�:��ֵ��ţ�NO�����Ĵ����ֽڳ��ȣ�DATLEN������ֵ��VAL��
	CSgDataSet  *pDatSet;	//
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_WriteProtSetting_Req()
	{
		pDatSet=NULL;
		OperType=0;
	};
};
typedef CNetCmdHead CCommSrv_WriteProtSetting_Res;
//==================================================================================================
class CCommSrv_ReadProtSetting_Req:public CNetCmdHead
{
public:
	SG_INT		RtuID;			//	�ն�ID
	SG_INT		DevAddr;		//	�豸��ַ
	SG_INT		SettingArea;	//	��������
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_ReadProtSetting_Req()
	{
	};
};
class CCommSrv_ReadProtSetting_Res:public CNetCmdHead
{
public:
	CSgDataSet  RetDat;		//  ���ݼ���  �����ֶ�:��ֵ��ţ�NO�����Ĵ����ֽڳ��ȣ�DATLEN������ֵ��VAL��
	CSgDataSet  *pRetDat;	//
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_ReadProtSetting_Res()
	{
		pRetDat=NULL;
	};
};
//==================================================================================================

class CCommSrv_ReadHisDat_Req:public CNetCmdHead
{
public:
	SG_INT		StartYMD;	//��ʼ������ yyyymmdd
	SG_INT		EndYMD;		//��ֹ������ yyyymmdd
	SG_INT		ObjType;	//	500��yc 502��kwh 
	SG_INT		TaskID;		//	����ID
	VECT_INT	PtIDList;	//���ID�б�	
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_ReadHisDat_Req()
	{
		StartYMD=EndYMD=0;
		TaskID=0;
		ObjType=500;
		PtIDList.clear();
	};
};
typedef CNetCmdHead CCommSrv_ReadHisDat_Res;

//==================================================================================================
//           ���̹������ӿ�
//==================================================================================================
class CPCM_StartProc_Req: public CNetCmdHead
{
public:
	//SG_INT		NodeID;		//�ڵ�ID,����CNetCmdHead��WorkSpace�� ��<=0����Ϊ�鱾��
	CSgString	ProcName;	//�������ƣ����npa,1���ʾ��Ҫ��pcm2.ini�е��������Ϊ����1
	CSgString	StartPara;	//�������
	CPCM_StartProc_Req()
	{
		ProcName="";
		StartPara="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CPCM_StartProc_Res;

class CPCM_EndProc_Req: public CNetCmdHead
{
public:
	//SG_INT		NodeID;		//�ڵ�ID,����CNetCmdHead��WorkSpace�� ��<=0����Ϊ�鱾��
	//SG_INT		OnlyStopProcFlag;	//����ֹͣ���� 
	CSgString	ProcName;	//�������� ���npa,1���ʾ��Ҫ��pcm2.ini�е��������Ϊֹͣ
	CSgString	EndPara;	//ֹͣ�������
	CPCM_EndProc_Req()
	{
		//OnlyStopProcFlag=false;
		ProcName="";
		EndPara="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CPCM_EndProc_Res;

class CPCM_MiniBoxSendCmd_Req: public CNetCmdHead
{
public:
	//SG_INT		NodeID;		//�ڵ�ID,����CNetCmdHead��WorkSpace�� ��<=0����Ϊ�鱾��
	SG_INT			SendCmdType;	//�����������
	CSgLobData		LobDat;	//�����������
	CSgLobData		*pLobDat;	//
	CPCM_MiniBoxSendCmd_Req()
	{
		LobDat.Init();
		pLobDat=NULL;
		SendCmdType=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CPCM_MiniBoxSendCmd_Res;


#define IDPPROC_ASKSTAT_PROC	1		//ѯ�ʵ�������״��
#define IDPPROC_ASKSTAT_SRV		2		//ѯ�ʷ���������״��
class CPCM_AskStatus_Req: public CNetCmdHead	
{
public:
	//SG_INT		NodeID;		//�ڵ�ID,����CNetCmdHead��WorkSpace�� ��<=0����Ϊ�鱾��
	SG_INT		SubType;	//������
	CSgString	ProcName;	//��������
	CPCM_AskStatus_Req()
	{
		SubType=IDPPROC_ASKSTAT_SRV;
		ProcName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

#define IDPPROC_PROCSTAT_OK			1		//��������
#define IDPPROC_PROCSTAT_STOP		2		//����ֹͣ
#define IDPPROC_PROCSTAT_WARNING	3		//���������о���
class CPCM_ProcStatus
{
public:
	SG_INT			ProcID;	//����ID
	SG_INT			State;	//��������
	std::string		ProcName;	//��������
	CPCM_ProcStatus()
	{
		ProcID=-1;
		State=IDPPROC_PROCSTAT_OK;
		ProcName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();

};
typedef std::vector<CPCM_ProcStatus > VECT_PROCINFO;
class CPCM_AskStatus_Res:public CNetCmdHead	
{
public:
	VECT_PROCINFO	ProcInfoArray;
	VECT_PROCINFO	*pProcInfoArray;
	CPCM_AskStatus_Res()
	{
		ProcInfoArray.clear();
		pProcInfoArray=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CPCM_StartCalcProc_Req : public CNetCmdHead
{
public:
	SG_INT			CalcProcType;	//�����������
	VECT_TWOSTRING	ReplaceKeyList;	//�滻������Ϣ
	CPCM_StartCalcProc_Req()
	{
		CalcProcType = 0;
		ReplaceKeyList.clear();
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
class CPCM_StartCalcProc_Res : public CNetCmdHead
{
public:
	SG_UINT64			ProcID;	//���ؽ���ID
	CPCM_StartCalcProc_Res()
	{
		ProcID = 0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
class CPCM_AskCalcProcState_Req : public CNetCmdHead
{
public:
	SG_UINT64			ProcID;	//���ؽ���ID
	CPCM_AskCalcProcState_Req()
	{
		ProcID = 0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};
class CPCM_AskCalcProcState_Res : public CNetCmdHead
{
public:
	CPCM_ProcStatus			ProcStatus;	//���ؽ���ID
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};

//����ϵͳ��װĿ¼
typedef CNetCmdHead		CPCM_SysEnvPath_Req;
class CPCM_SysEnvPath_Res: public CNetCmdHead	
{
public:
	CSgString	PathName;	//·�����ƣ���ϵͳ����·��
	CPCM_SysEnvPath_Res()
	{
		PathName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//����Ŀ¼�µ��ļ���Ϣ����������Ŀ¼
class CPCM_PathFileInfo_Req: public CNetCmdHead	
{
public:
	CSgString	PathName;	//·�����ƣ���ϵͳ����·��
	CPCM_PathFileInfo_Req()
	{
		PathName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CPCM_FileInfo
{
public:
	std::string		FileName;
	SG_UCHAR		IsPathFlag;
	SG_INT64		FileSize;
	SG_UINT			UpdateTime;
	CPCM_FileInfo()
	{
		IsPathFlag=false;
		FileName="";
		FileSize=0;
		UpdateTime=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef std::vector<CPCM_FileInfo >	VECT_PCM_FILEINFO;
class CPCM_PathFileInfo_Res: public CNetCmdHead	
{
public:
	CSgString			PathName;	//·�����ƣ���ϵͳ����·��
	VECT_PCM_FILEINFO	FileInfoArray;
	VECT_PCM_FILEINFO	*pFileInfoArray;
	CPCM_PathFileInfo_Res()
	{
		PathName="";
		pFileInfoArray=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//����Ŀ¼�µ��ļ���Ϣ����������Ŀ¼
#define PCM_FILEOPER_FILE_DEL			1
#define PCM_FILEOPER_FILE_RENAME		2
#define PCM_FILEOPER_FILE_CP			3
#define PCM_FILEOPER_PATH_CRT			4
#define PCM_FILEOPER_PATH_DEL			5
class CPCM_FileOper_Req: public CNetCmdHead	
{
public:
	SG_INT		OperType;		//1: ɾ��     2���޸�����  3:���� 4����Ŀ¼  5:ɾ��Ŀ¼
	CSgString	FileName;		//��·�����ƣ���ϵͳ����·��
	CSgString	NewFileName;	//��·�����ƣ���ϵͳ����·��
	CPCM_FileOper_Req()
	{
		FileName="";
		OperType=0;
		NewFileName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CPCM_FileOper_Res;

//�����ļ�����
class CPCM_DownLoadFile_Req: public CNetCmdHead	
{
public:
	CSgString	FileName;		//��·�����ƣ���ϵͳ����·��
	SG_INT		TransNo;		//����İ��ţ���0��ʼ
	SG_INT64	FileStartPos;	//������ļ���ʼλ��
	SG_INT	    SendMaxSize;	//���͵��ļ���������ֽ���
	CPCM_DownLoadFile_Req()
	{
		FileName="";
		TransNo=0;
		FileStartPos=0;
		SendMaxSize=10*1024*1024;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CPCM_AutoReallocMem
{
public:
	SG_INT	 BuffSize;
	SG_UCHAR *pBuff;
	CPCM_AutoReallocMem()
	{
		BuffSize=0;
		pBuff=NULL;
	};
	int SetSize(SG_INT len)
	{
		if(len<=BuffSize)
			return true;
		pBuff=(SG_UCHAR *)realloc(pBuff,(len+100));
		if(pBuff==NULL)
		{
			BuffSize=0;
			return false;
		}
		BuffSize=len+100;
		return true;
	};
	~CPCM_AutoReallocMem()
	{
		if(pBuff)
			free(pBuff);
		pBuff=NULL;
		BuffSize=0;
	};
};
class CPCM_FileLoadInfo
{
public:
	SG_INT64	FileSize;
	SG_UINT		UpdateTime;
	SG_INT		TransNo;		//����İ��ţ���0��ʼ
	SG_INT64	FileStartPos;	//������ļ���ʼλ��
	SG_INT	    SendSize;		//���͵��ļ������ֽ���
	CPCM_FileLoadInfo()
	{
		FileSize=0;
		UpdateTime=0;
		TransNo=0;
		FileStartPos=0;
		SendSize=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef std::map<SG_INT,CPCM_FileLoadInfo >		MAP_INT_FILELOADINFO;
class CPCM_DownLoadFile_Res: public CNetCmdHead	
{
public:
	CSgString	FileName;		//��·�����ƣ���ϵͳ����·��
	CPCM_FileLoadInfo LoadInfo;
	CPCM_AutoReallocMem SendBuf;
	CPCM_AutoReallocMem	*pSendBuf;
	CPCM_DownLoadFile_Res()
	{
		FileName="";
		pSendBuf=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�����ļ�����
class CPCM_UpLoadFile_Req: public CNetCmdHead	
{
public:
	CSgString	FileName;		//��·�����ƣ���ϵͳ����·��
	CPCM_FileLoadInfo LoadInfo;
	CPCM_AutoReallocMem SendBuf;
	CPCM_AutoReallocMem	*pSendBuf;
	CPCM_UpLoadFile_Req()
	{
		FileName="";
		pSendBuf=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�����ļ�����
class CPCM_UpLoadFile_Res: public CNetCmdHead	
{
public:
	CSgString	FileName;		//��·�����ƣ���ϵͳ����·��
	SG_INT		TransNo;		//����İ��ţ���0��ʼ
	SG_UCHAR	RecvOKFlag;
	VECT_INT	ExistTransNoList;//������Ѵ��ڵİ����
	CPCM_UpLoadFile_Res()
	{
		FileName="";
		TransNo=0;
		RecvOKFlag=false;
		ExistTransNoList.clear();
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//�����ļ�����
/*class CPCM_UpLoadFile_New_Res: public CPCM_UpLoadFile_Res
{
public:
	VECT_INT	ExistTransNoList;//������Ѵ��ڵİ����
	CPCM_UpLoadFile_New_Res()
	{
		ExistTransNoList.clear();
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
*/
class CDBCmd_UpLoadFile_Req:public CPCM_UpLoadFile_Req
{
public:
	CSgString DBName;
	CSgString ContentType;
	CDBCmd_UpLoadFile_Req()
	{
		DBName="";
		ContentType="";
		DBNo=DEFAULT_SYS_DBNO;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CPCM_UpLoadFile_Res CDBCmd_UpLoadFile_Res;
#define DBCMD_DOWNLOAD_BY_FILENAME		0	//���ļ�����ȡ�ļ�����
#define DBCMD_DOWNLOAD_BY_REQSTR		1	//����������ȡ�ļ�����
class CDBCmd_DownLoadFile_Req:public CPCM_DownLoadFile_Req
{
public:
	SG_UCHAR  ReqType; //0:���ļ�����ȡ�ļ�����,  1:����������ȡ�ļ����� 
	CSgString DBName;
	CSgString ReqStr;
	CDBCmd_DownLoadFile_Req()
	{
		ReqType=DBCMD_DOWNLOAD_BY_FILENAME;
		ReqStr="";
		DBName="";
		DBNo=DEFAULT_SYS_DBNO;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CDBCmd_DownLoadFile_Res:public CPCM_DownLoadFile_Res
{
public:
	CSgString ReqStr;
	S_NoSqlFileInfo		FileInfo;
	S_NoSqlFileInfo		*pFileInfo;

	CDBCmd_DownLoadFile_Res()
	{
		ReqStr="";
		pFileInfo=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//===================================================================================================
//===================================================================================================
#define PCM_SRVCTRL_RESTART		0 //��������
#define PCM_SRVCTRL_STOP		1 //ֹͣ�������
#define PCM_SRVCTRL_START		2 //�����������
class CPCM_RestartSrv_Req:public CNetCmdHead
{
public:
	SG_INT	StartFlag;		//0:��������  1��ֹͣ�������  2�������������
	CPCM_RestartSrv_Req()
	{
		StartFlag=PCM_SRVCTRL_RESTART;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

typedef CNetCmdHead CPCM_RestartSrv_Res;
//===================================================================================================
//===================================================================================================
class CPCM_ShellCmd_Req: public CNetCmdHead
{
public:
	CSgString	ExePath;	//ִ��·��PATH
	CSgString	ShellCmd;	//Shell�������
	CPCM_ShellCmd_Req()
	{
		ExePath="";
		ShellCmd="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CPCM_ShellCmd_Res: public CNetCmdHead
{
public:
	CSgString	OutInfo;	//����ִ�������Ϣ
	CSgString	CurrentPath; //��ǰ·��
	CPCM_ShellCmd_Res()
	{
		OutInfo="";
		CurrentPath="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//===================================================================================================
//===================================================================================================
class CPCM_GetFileInfo_Req: public CNetCmdHead
{
public:
	CSgString	FileName;	//��·�����ļ�����
	CPCM_GetFileInfo_Req()
	{
		FileName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
class CPCM_GetFileInfo_Res: public CNetCmdHead
{
public:
	SG_UINT		FileTime;	//�ļ�ʱ��
	SG_UINT		FileSize;	//�ļ���С
	SG_UCHAR	FileMD5[16];	//�ļ�MD5У��ֵ
	CPCM_GetFileInfo_Res()
	{
		FileTime=FileSize=0;
		memset(FileMD5,0,sizeof(FileMD5));
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//===================================================================================================
//===================================================================================================
/*class CPCM_ExecSQLFile_Req: public CNetCmdHead
{
public:
	CSgString	DsName;			//����Դ������
	CSgString	SQLFile;		//ִ�е�SQL�ļ����ƣ���·�����ƣ���ϵͳ����·��
	CSgString	LogFile;		//�����־�ļ�����·�����ƣ���ϵͳ����·��
	CPCM_ExecSQLFile_Req()
	{
		DsName="cloud";
		SQLFile="";
		LogFile="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CPCM_ExecSQLFile_Res;
*/

//===================================================================================================
//===================================================================================================
typedef CNetCmdHead CMiniBoxMan_Login_Req;
typedef CNetCmdHead CMiniBoxMan_Login_Res;

class CMiniBoxMan_SendStatus_Req: public CNetCmdHead
{
public:
	short			memLoad;						//�ڴ�ռ�ñ�
	short			cpuLoad;						//CPUʹ����
	ACE_UINT32		availMem;						//�����ڴ�
	CMiniBoxMan_SendStatus_Req()
	{
		memLoad=0;
		cpuLoad=0;
		availMem=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CMiniBoxMan_SendStatus_Res;
class CMiniBoxMan_SendDiskStatus_Req: public CNetCmdHead
{
public:
	typedef struct S_SENDDISKSTATUS
	{
		std::string DiskName;
		SG_INT		TotalSize;
		SG_INT		FreeSize;
	}S_SENDDISKSTATUS;
	typedef std::vector<S_SENDDISKSTATUS > VECT_DISKSTATUS;
	VECT_DISKSTATUS	*pDiskStatusList;
	VECT_DISKSTATUS DiskStatusList;
	CMiniBoxMan_SendDiskStatus_Req()
	{
		pDiskStatusList=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CMiniBoxMan_SendDiskStatus_Res;

//==================================================================================================
//           ���������
//==================================================================================================
//���������
#define SRVCMD_PROCESS_OPER(PROCFUNC,REQUEST_INFO,RESPONSE_INFO,COMPRESS_LEVEL) \
	NetCommandReceiveExplain explain(&pmb);	\
	REQUEST_INFO request;	\
	RESPONSE_INFO responser; \
	ret = request.Serialize(*explain.ars); \
	if(request.CmdVersion>SG_NET_VERSION)	\
	responser.CmdVersion=SG_NET_VERSION;	\
	else	\
	responser.CmdVersion=request.CmdVersion;	\
    responser.CmdType=request.CmdType; \
	if(ret==false)	\
{	\
	responser.RetVal=NETCMD_RETVAL_ERROR;	\
	responser.RetInfo.Format("�������л�ʧ�� SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
}	\
	else \
	ret = PROCFUNC(request,responser);\
	NetCommandSendParaPrepare prepare;	\
	responser.Serialize(*prepare.ars,responser.CmdVersion);\
	prepare.End();\
	ret=true;\
	if(write_mb(pSockStream,(char*)prepare.fs->GetBufferPtr(),prepare.fs->GetLength(),msg_type,10*ACE_DEFAULT_TIMEOUT,COMPRESS_LEVEL)<0)	\
	ret=false;

#define SRVCMD_PROCESS_OPER_DBROW(PROCFUNC,REQUEST_INFO,RESPONSE_INFO,COMPRESS_LEVEL) \
	NetCommandReceiveExplain explain(&pmb);	\
	REQUEST_INFO request;	\
	RESPONSE_INFO responser; \
	ret = request.Serialize(*explain.ars); \
	if(request.CmdVersion>SG_NET_VERSION)	\
	responser.CmdVersion=SG_NET_VERSION;	\
	else	\
	responser.CmdVersion=request.CmdVersion;	\
    responser.CmdType=request.CmdType; \
	if(ret==false)	\
{	\
	responser.RetVal=NETCMD_RETVAL_ERROR;	\
	responser.RetInfo.Format("�������л�ʧ�� SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
}	\
	else \
	ret = PROCFUNC(request,responser);\
	NetCommandSendParaPrepare prepare;	\
	responser.Serialize(*prepare.ars,request.StartRow,request.MaxRow,responser.CmdVersion);\
	prepare.End();\
	ret=true;\
	if(write_mb(pSockStream,(char*)prepare.fs->GetBufferPtr(),prepare.fs->GetLength(),msg_type,10*ACE_DEFAULT_TIMEOUT,COMPRESS_LEVEL)<0)	\
	ret=false;
#define SRVCMD_PROCESS_MEMOPER(PROCFUNC,REQUEST_INFO,RESPONSE_INFO) \
	REQUEST_INFO request;	\
	RESPONSE_INFO responser; \
	responser.RetVal=NETCMD_RETVAL_ERROR;	\
	Net_Stream_Load sl(pLobBuf, LobLen);	\
	CSgArchive & ar = sl.Archive();	\
	ret = request.Serialize(ar); sl.End();\
	if(request.CmdVersion>SG_NET_VERSION)	\
		responser.CmdVersion=SG_NET_VERSION;	\
	else	responser.CmdVersion=request.CmdVersion;	\
	responser.CmdType=request.CmdType; \
	if(ret==false)	\
		responser.RetInfo.Format("�������л�ʧ�� SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
	else 	ret = PROCFUNC(request,responser);\
	CSgArchive r_ar(&MemFile, CSgArchive::store, 4096 * 4096);\
	responser.Serialize(r_ar,responser.CmdVersion);\
	r_ar.Close();\
	ret=true;
#define SRVCMD_PROCESS_MEMOPER_DBROW(PROCFUNC,REQUEST_INFO,RESPONSE_INFO) \
	REQUEST_INFO request;	\
	RESPONSE_INFO responser; \
	responser.RetVal=NETCMD_RETVAL_ERROR;	\
	Net_Stream_Load sl(pLobBuf, LobLen);	\
	CSgArchive & ar = sl.Archive();	\
	ret = request.Serialize(ar); sl.End();\
	if(request.CmdVersion>SG_NET_VERSION)	\
		responser.CmdVersion=SG_NET_VERSION;	\
	else	responser.CmdVersion=request.CmdVersion;	\
	responser.CmdType=request.CmdType; \
	if(ret==false)	\
		responser.RetInfo.Format("�������л�ʧ�� SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
	else 	ret = PROCFUNC(request,responser);\
	CSgArchive r_ar(&MemFile, CSgArchive::store, 4096 * 4096);\
	responser.Serialize(r_ar,request.StartRow,request.MaxRow,responser.CmdVersion);\
	r_ar.Close();\
	ret=true;

//==================================================================================================
//	���ݶ���Ҫ������Ƿ񽫺���ʵ������
//#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/DBCommand.inl"
//#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
