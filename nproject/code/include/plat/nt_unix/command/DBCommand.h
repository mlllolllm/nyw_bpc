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
	NETCMD_RETVAL_COMM_ERROR			=-2,			//连接服务错误
	NETCMD_RETVAL_ERROR					=-1,			//DB返回错误
	NETCMD_RETVAL_SUCCESS				=0,				//DB返回成功
	NETCMD_RETVAL_WARNING				=1,				//DB返回警告
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
	SG_USHORT			CmdType;				//命令号
	SG_UCHAR			ZipFlag;				//压缩标记
	SG_UCHAR			FinishFlag;	//结束包标志
	SG_INT				FrameNo;	//包序号,从0开始
	ACE_UINT32			CmdVersion;				//命令版本号
	ACE_UINT32			FrameLen;				//命令长度
	ACE_UINT32			DBNo;					//操作的数据库No
	ACE_UINT32			RetVal;					//返回码
	ARR_UINT32			WorkSpaces;				//工作空间集合
	CSgString			RetInfo;				//返回信息
};
*/
typedef CNetCmdHead CDBCmdHead;
class CReadDatNetCmd_Req:public CNetCmdHead
{
public:
	SG_UCHAR SortFlag;	//0:不排序  1:升序  2:降序
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
//           关系库接口
//==================================================================================================
//	读取数据库记录的请求
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
	SG_INT		ObjType; //设备对象
	SG_UCHAR	IsGeoFlag; //是否是几何表
	CSgString	Fields;
	CSgString	WhereSQL;
	CSgDataSet	*pCompileDataSet; //参数传入
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

//	读取数据库记录的返回
template <class T>
class CDBCmd_ReadRecorder_ResT: public CNetCmdHead
{
public:
	T		RetDat;
	T		*pRetDat;	//如果pRetDat!=NULL 则使用pRetDat进行序列化
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
	CSgDataSet				RetInfo_DatSet;		//返回信息的集合,含RETVAL RETINFO两个字段,
	CSgDataSetArray_ObjOper	RetDataSetArray;		//OperType固定为1
	CSgDataSetArray_ObjOper	*pRetDataSetArray;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CDBCmd_BatchReadRecorder_Res()
	{
		pRetDataSetArray=NULL;
	};
};


//插入数据库记录的请求
template <class T>
class CDBCmd_InsertRecorder_ReqT : public CNetCmdHead
{
public:
	T		DatSet;
	T		*pDatSet;	//如果pRetDat!=NULL 则使用pRetDat进行序列化
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

//插入数据库记录的返回
typedef CNetCmdHead CDBCmd_InsertRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_InsertVerRecorder_Res;

//修改数据库记录的请求
template <class T>
class CDBCmd_UpdateRecorder_ReqT : public CNetCmdHead
{
public:
	T		DatSet;
	T		*pDatSet;	//如果pRetDat!=NULL 则使用pRetDat进行序列化
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

//修改数据库记录的返回
typedef CNetCmdHead CDBCmd_UpdateRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_UpdateVerRecorder_Res;

//合并数据库记录的请求
typedef CDBCmd_UpdateRecorder_ReqT <CSgDataSet >   CDBCmd_MergeRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgLobDataSet >   CDBCmd_MergeLobRecorder_Req;
typedef CDBCmd_UpdateRecorder_ReqT <CSgGeoDataSet >   CDBCmd_MergeGeoRecorder_Req;
typedef CDBCmd_InsertVerRecorder_Req CDBCmd_MergeVerRecorder_Req;
//合并数据库记录的返回
typedef CNetCmdHead CDBCmd_MergeRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeLobRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeGeoRecorder_Res ;
typedef CNetCmdHead CDBCmd_MergeVerRecorder_Res;

//删除数据库记录的请求
typedef CDBCmd_UpdateRecorder_ReqT <CSgDataSet >   CDBCmd_DeleteRecorder_Req;
typedef CDBCmd_UpdateVerRecorder_Req   CDBCmd_DeleteVerRecorder_Req;
//删除数据库记录的返回
typedef CNetCmdHead CDBCmd_DeleteRecorder_Res ;
typedef CNetCmdHead CDBCmd_DeleteVerRecorder_Res;

class CDBCmd_CommitDatVer_Req : public CNetCmdHead, public CNetCmdVerInfo
{
public:
	SG_INT		ObjType; //设备对象
	SG_UCHAR	IsGeoFlag; //是否是几何表
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
	SG_INT		ObjType; //设备对象
	SG_UCHAR	IsGeoFlag; //是否是几何表
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
//	执行数据库记录的请求
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
//	执行数据库记录的返回
typedef CNetCmdHead CDBCmd_ExecSQL_Res ;
typedef CNetCmdHead CDBCmd_CompileExecSQL_Res ;

//	执行数据库操作（不引起触发操作）的请求
class CDBCmd_ExecSQLNotTrigger_Req: public CNetCmdHead
{
public:
	CSgString		SQLBuf;
	CSgString		TblName;	//语句影响的表
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	执行数据库记录的返回
typedef CNetCmdHead CDBCmd_ExecSQLNotTrigger_Res ;

//短事务处理数据的请求
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
//短事务处理数据的返回
typedef CNetCmdHead CDBCmd_TransOper_Res ;

//多数据源短事务处理数据的请求
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
//多数据源短事务处理数据的返回
typedef CNetCmdHead CDBCmd_MultiDBTransOper_Res;

//多数据源短事务处理 版本数据的请求
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
//多数据源短事务处理 版本数据的返回
typedef CNetCmdHead CDBCmd_MultiDBTransVerOper_Res;

//读取Lob字段数据的请求
class CDBCmd_ReadLobField_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	CSgString		LobFieldName;
	CSgString		WhereSQL;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//读取Lob字段数据库记录的返回
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

//写入Lob字段数据的请求
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
//写入Lob字段数据库记录的返回
typedef CNetCmdHead CDBCmd_WriteLobField_Res ;
#ifndef SG_MINIBOX_PLAT
typedef CNetCmdHead CDBCmd_GetDBType_Req;
typedef CNetCmdHead CDBCmd_GetDBType_Res;
#endif
//读取当前的系统时间
typedef CNetCmdHead CDBCmd_GetSysDate_Req ;
//读取当前的系统时间的返回
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
	SG_INT			ReqWS;	//请求ID的工作空间
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
//图形叠加分析请求
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
//图形叠加分析请求返回
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

//图形凸包计算请求
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
//图形凸包计算请求返回
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
//图形凸包计算请求返回
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
//读取表名称
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
//创建表
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
//删除文件
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
//获取文件信息
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
//获取文件列表
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
//    事项服务接口         
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
//请求系统安装目录
typedef CNetCmdHead		CEvtSrv_SendRawEvt_Res;

//==================================================================================================
//    实时库接口         
//==================================================================================================

//	读取数据库记录的请求
typedef CDBCmd_ReadRecorder_Req CHSDA_ReadRecorder_Req;
typedef CDBCmd_ReadRecorder_Res CHSDA_ReadRecorder_Res;

//	读取数据库表记录的请求
class CHSDA_ReadTblRecorder_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//	读取数据库记录的返回
//typedef CDBCmd_ReadRecorder_Res CHSDA_ReadTblRecorder_Res;
//	读取数据库记录的返回
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


//	执行数据库记录的请求
typedef CDBCmd_ExecSQL_Req CHSDA_ExecSQL_Req;
typedef CDBCmd_ExecSQL_Res CHSDA_ExecSQL_Res;

// 订阅实时库流数据请求
class CHSDA_SubscribeData_Req : public CNetCmdHead
{
public:
	CSgString		TableName;
	CSgString		Fields;
	SG_SHORT		FreshTime;	//刷新时间
	CSgDataSet		DatSet;	//如果记录个数为0，则订阅表中的所有对象
	CSgDataSet		*pDatSet;	//如果记录个数为0，则订阅表中的所有对象
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CHSDA_SubscribeData_Req()
	{
		FreshTime=3;
		pDatSet=NULL;
	};
};

// 订阅实时库流数据返回
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

// 取消实时库流数据请求
class CHSDA_CancelSubscribe_Req : public CNetCmdHead
{
public:
	SG_UINT64			StreamHandle;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
// 取消实时库流数据返回
typedef CNetCmdHead CHSDA_CancelSubscribe_Res ;


// 获取订阅实时库流变化数据请求
class CHSDA_GetChangeData_Req : public CNetCmdHead
{
public:
	SG_UINT64			StreamHandle;
	SG_UCHAR		GetType;	//2:获取变化数据  1:获取全数据
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
// 获取订阅实时库流变化返回
typedef CHSDA_SubscribeData_Res CHSDA_GetChangeData_Res;
#define SG_YK_OPERTYPE_EXEC_DIRECT		0	//直接执行
#define SG_YK_OPERTYPE_SELECT			1	//预置
#define SG_YK_OPERTYPE_EXEC				2	//执行
#define SG_YK_OPERTYPE_CANCEL			3	//取消

//遥控操作
class CHSDA_YKOper_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType;//	0：直接执行 1：预置（选择） 2：执行 3：取消	
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

//遥调操作
class CHSDA_YTOper_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType; //0：直接执行 1：预置（选择） 2：执行 3：取消	
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

//人工设置操作
class CHSDA_LockRtData_Req : public CNetCmdHead
{
public:
	SG_UCHAR		OperType;	//0:设置数据 1:锁定  2:解锁
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
	SG_UCHAR	OperType;   //0:设置取消  1:设置并确认变位  2:确认变位，但不设置
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

//发向前置的命令操作
class CHSDA_CommSrvCmd_Req : public CNetCmdHead
{
public:
	SG_INT			   RtuID; //mcu id
	S_COMMRTU_TASKINFO TaskInfo;
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_CommSrvCmd_Res;
//发向前置的命令操作
class CHSDA_CommSrvCmd_New_Req: public CHSDA_CommSrvCmd_Req
{
public:
	CSgDataSetArray_ObjOper	DataSetArray;		//OperType固定为1
	CSgDataSetArray_ObjOper	*pDataSetArray;
	CHSDA_CommSrvCmd_New_Req()
	{
		pDataSetArray=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_CommSrvCmd_New_Res;
//事项状态改变请求
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
	int				ObjType;		//表测点的类型 500:yc 501:yx 502:kwh 
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
	SG_INT			ObjType;	//测点设备对象
	CSgString		QueryFields;	//请求的字段
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
	CSgString		QueryFields;	//请求的字段
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
	SG_INT			ObjType;	//测点设备对象
	CSgString		QueryFields;	//请求的字段
	CSgDataSet	DatSet; //包含 OBJTYPE OBJID TERMINAL MEASURE字段
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

#define SG_HSDA_RDBOPER_CHECKRDB			1	//检查实时库
#define SG_HSDA_RDBOPER_CHECKRDBRCD			2	//检查实时库表内容
#define SG_HSDA_RDBOPER_BACKUPTBL			3	//备份实时库表
#define SG_HSDA_RDBOPER_LOADRTBL			4	//重新加载实时库
#define SG_HSDA_RDBOPER_UNLOCKTBL			5	//解锁是实时库表

class CHSDA_RDBMemOper_Req : public CNetCmdHead
{
public:
	SG_INT			OperType;	//操作类型
	CSgString		TblName;
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1, CSgObjects *pRcdNoList = NULL);
	virtual int buf_size();
};
typedef CNetCmdHead CHSDA_RDBMemOper_Res;
//新建一个算例实时库
#define SG_RDB_SCHEMA_PROCMODE_CANFREE			0x00000001 //不是常驻内存
#define SG_RDB_SCHEMA_PROCMODE_RECV_PARACHAN		0x00000002 //接受参数变化更新
#define SG_RDB_SCHEMA_PROCMODE_RECV_DATCHAN		0x00000004 //接受数据变化更新
#define SG_RDB_SCHEMA_PROCMODE_CLOUDSYNC			0x00000008 //接受数据同步
class CHSDA_RTDBLoadPara
{
public:
	SG_INT				LoadType; //0: 从数据库加载  1：从文件加载
	SG_INT				RtDBVerNo;
	SG_INT				SchemaDBNo;
	SG_INT				SchemaProcMode;
	CSgString			SrvTypeStr;  //LoadType=0 是SrvType信息 
	CSgString			FileName;  //LoadType=1:是文件的名称
	VECT_TWOSTRING		ReplaceKey; //启动参数
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
//删除一个算例实时库
typedef CNetCmdHead CHSDA_RDB_DeleteCCRtDB_Req;
typedef CNetCmdHead CHSDA_RDB_DeleteCCRtDB_Res;
//获取一个新的SchemaHandler
typedef CNetCmdHead CHSDA_GetNewSchemaHandler_Req;
typedef CNetCmdHead CHSDA_GetNewSchemaHandler_Res;

#endif
//==================================================================================================
//    历史库接口         
//==================================================================================================

//	按照测点查询历史数据的请求
class CTSDA_QueryDataByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//测点类型
	SG_UINT		StartYMD;	//起始年月日
	SG_UINT		EndYMD;		//结束年月日
	SG_UINT		Interval;	//读取间隔,以秒为单位
	CSgDataSet	DatSet;		//读取的测点id集合 含ID字段 FALG字段
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
//	按照测点查询历史数据的返回
class CTSDA_QueryDataByPt_Res : public CNetCmdHead
{
public:
	CSgDataSet	RetDat;		//读取的结果集
	CSgDataSet	*pRetDat;
	CTSDA_QueryDataByPt_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	按照测点查询历史数据的请求
class CTSDA_QueryDataByPt_New_Req: public CTSDA_QueryDataByPt_Req
{
public:
	SG_INT		StartHMS;	//起始时分秒
	SG_INT		EndHMS;		//结束时分秒
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
#define SG_TSDA_QUERYMODE_ONLYCNT			0x00000001	//为1时只返回记录个数
#define SG_TSDA_QUERYMODE_PUTLACKBYLAST		0x00000002	//为1时补充缺少测点 按前个测点补充
#define SG_TSDA_QUERYMODE_PUTLACKBYSLOPE	0x00000004	//为1时补充缺少测点 按前个测点补充
//	按照测点查询历史数据的请求
class CTSDA_QueryDataByPt_Append_Req: public CTSDA_QueryDataByPt_New_Req
{
public:
	SG_UINT		QueryMode;		//请求模式,按位表达: bit0:为1时只返回记录个数
	CSgString	AppendWhereSql;	//附加的条件语句
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
//	按照测点查询历史统计数据的请求
class CTSDA_QueryStatByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//测点类型
	SG_UINT		StartYMD;	//起始年月日
	SG_UINT		EndYMD;		//结束年月日
	CSgDataSet	DatSet;		//读取的测点id集合 含ID字段 FALG字段
	CSgDataSet	*pDatSet;		//读取的测点id集合 含ID字段 FALG字段
	CTSDA_QueryStatByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_QueryStatByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	按照测点查询历史统计数据的返回
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryStatByPt_Res;
 
//	按照测点查询历史断面数据的请求
class CTSDA_QueryValuesByPt_Req : public CReadDatNetCmd_Req
{
public:
	SG_INT		ObjType;	//测点类型
	SG_UINT		YMD;		//年月日
	SG_UINT		HMS;		//时分秒
	CSgDataSet	DatSet;		//读取的测点id集合 含ID字段 FALG字段
	CSgDataSet	*pDatSet;		//读取的测点id集合 含ID字段 FALG字段
	CTSDA_QueryValuesByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_QueryValuesByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	按照测点查询历史断面数据的返回
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryValuesByPt_Res;

//	按照设备查询历史数据的请求
typedef CTSDA_QueryDataByPt_Req CTSDA_QueryDataByDev_Req;
typedef CTSDA_QueryDataByPt_New_Req CTSDA_QueryDataByDev_New_Req;
typedef CTSDA_QueryDataByPt_Append_Req CTSDA_QueryDataByDev_Append_Req;

//	按照设备查询历史数据的返回
typedef CTSDA_QueryDataByPt_Res CTSDA_QueryDataByDev_Res;
typedef CTSDA_QueryDataByPt_New_Res CTSDA_QueryDataByDev_New_Res;
typedef CTSDA_QueryDataByPt_Append_Res CTSDA_QueryDataByDev_Append_Res;

//	按照设备查询历史统计数据的请求
typedef CTSDA_QueryStatByPt_Req CTSDA_QueryStatByDev_Req;
//	按照设备查询历史统计数据的返回
typedef CTSDA_QueryStatByPt_Res CTSDA_QueryStatByDev_Res;

//	按照设备查询历史断面数据的请求
typedef CTSDA_QueryValuesByPt_Req CTSDA_QueryValuesByDev_Req;
//	按照设备查询历史断面数据的返回
typedef CTSDA_QueryValuesByPt_Res CTSDA_QueryValuesByDev_Res;


//	按照测点查询历史数据的网络返回
class CTSDA_QueryDataByDev_NetRes : public CNetCmdHead
{
public:
	CSgDataSet	RetPara;	//读取的参数集
	CSgDataSet	RetDat;		//读取的结果集
	CSgDataSet	*pRetPara;	//读取的参数集
	CSgDataSet	*pRetDat;		//读取的结果集
	CTSDA_QueryDataByDev_NetRes()
	{
		pRetDat=pRetPara=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	按照设备查询历史统计数据的网络返回
typedef CTSDA_QueryDataByDev_NetRes CTSDA_QueryStatByDev_NetRes;
//	按照设备查询历史断面数据的网络返回
typedef CTSDA_QueryDataByDev_NetRes CTSDA_QueryValuesByDev_NetRes;

//	按照测点存入历史数据的请求
class CTSDA_SaveDataByPt_Req : public CNetCmdHead
{
public:
	SG_INT		ObjType;	//测点类型
	CSgDataSet	DatSet;		//读取的测点id集合 含YMD  HMS  ID  FLAG  VALUE STATUS
	CSgDataSet	*pDatSet;	//读取的测点id集合 含YMD  HMS  ID  FLAG  VALUE STATUS
	CTSDA_SaveDataByPt_Req()
	{
		pDatSet=NULL;
	};
	void operator = (const CTSDA_SaveDataByPt_Req &obj);
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//获取数据库连接状况
#ifndef SG_MINIBOX_PLAT
typedef  CNetCmdHead CCloud_GetDBLinkStat_Req;
class CCloud_GetDBLinkStat_Res: public CNetCmdHead
{
public:
	CSgDataSet	RetDat;		//读取的测点id集合 含SRVNO MIN_LINK MAX_LINK REAL_LINK ACTIVE_LINK
	CSgDataSet	*pRetDat;	//读取的测点id集合 含SRVNO MIN_LINK MAX_LINK REAL_LINK ACTIVE_LINK
	CCloud_GetDBLinkStat_Res()
	{
		pRetDat=NULL;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
#endif
//	按照测点存入历史数据的返回
typedef CNetCmdHead CTSDA_SaveDataByPt_Res;

//	按照设备存入历史数据的请求
typedef CTSDA_SaveDataByPt_Req CTSDA_SaveDataByDev_Req;
typedef CTSDA_SaveDataByPt_Res CTSDA_SaveDataByDev_Res;

//	按照测点删除历史数据的请求
typedef CTSDA_SaveDataByPt_Req CTSDA_DelDataByPt_Req;
typedef CTSDA_SaveDataByPt_Res CTSDA_DelDataByPt_Res;

//	按照设备删除历史数据的请求
typedef CTSDA_DelDataByPt_Req CTSDA_DelDataByDev_Req;
typedef CTSDA_DelDataByPt_Res CTSDA_DelDataByDev_Res;

//==================================================================================================
//    文件服务接口         
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
//    复制服务接口         
//==================================================================================================
//	获得某个逻辑数据单元的版本号
class CREP_GetLogicCellVer_Req : public CNetCmdHead
{
public:
	SG_INT				 SrvType;	//服务类型
	S_LOGICCELLINFO		 LogicCell;	//逻辑数据单元
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	获得某个逻辑数据单元的版本号的返回
class CREP_GetLogicCellVer_Res : public CNetCmdHead
{
public:
	VECT_TWOINT			 LogicCellVer;	//服务逻辑数据单元的版本号
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//	获得某个逻辑数据单元的版本号
class CREP_GetLogicCellDat_Req : public CNetCmdHead
{
public:
	SG_INT				SrvType;	//服务类型
	S_LOGICCELLINFO		LogicCell;	//逻辑数据单元
	SG_INT				NodeID;		//版本中的节点号
	SG_UINT				StartVer;	//起始版本
	SG_UINT				EndVer;		//终止版本
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	获得某个逻辑数据单元的版本号的返回
class CREP_GetLogicCellDat_Res : public CNetCmdHead
{
public:
	SG_UINT				StartVer;	//起始版本
	SG_UINT				EndVer;		//终止版本
	CSgDataSetArray_ObjOper		DatArray;	//数据集
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//==================================================================================================
//    CPS服务接口         
//==================================================================================================
//==================================================================================================
//	处理完成后的发送报文,本进程不同线程发送信息,无需考虑字节序
class CCPS_ProcOver_Req
{
public:
	SG_INT						CmdType;	//命令号
	SG_UINT						HandlerCmdCnt;		//在该请求中的命令号
	SG_INT						RequestNo;		//在同一次请求中的序号
	S_TWOINT					NodePort;		//节点端口号
	SG_INT						RetCode;	//返回代码
	SG_BOOL						EndFlag;
	NetCommandReceiveExplain	*pChildRecvData;
};
//	获得当前实时事项表的写指针
typedef CNetCmdHead CCPS_QueryRealEvtWritePt_Req ;
//	获得当前实时事项表的返回
class CCPS_QueryRealEvtWritePt_Res : public CNetCmdHead
{
public:
//	SG_INT				WriteCircuitCnt; //实时事项缓存器中的循环次数
	SG_UINT				WritePt;	//写指针
	CCPS_QueryRealEvtWritePt_Res()
	{
//		WriteCircuitCnt=-1;
		WritePt=0;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//	获得实时事项表的记录
class CCPS_QueryRealEvt_Req : public CNetCmdHead
{
public:
//	SG_INT				StartCircuitCnt; //实时事项缓存器中的循环次数
	SG_UINT				StartReadPt;	//起始读指针
	SG_INT				MaxRowNum;	//最大记录个数
	SG_INT				ConfirmFlag;	//0:所有事项  1：未确认事项  2：已确认事项
	CCPS_QueryRealEvt_Req()
	{
		StartReadPt=MaxRowNum=0;
		ConfirmFlag=0;
//		StartCircuitCnt=-1;
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	获得实时事项表的记录的返回
class CCPS_QueryRealEvt_Res : public CNetCmdHead
{
public:
//	SG_INT				LastReadCircuitCnt; //实时事项缓存器中的循环次数
	SG_UINT				LastReadPt;	//下次读取的指针
//	SG_INT				WriteCircuitCnt; //实时事项缓存器中的循环次数
	SG_UINT				WritePt;	//写指针
	CSgDataSet			RetDat;		//返回的数据集
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
//	确认实时事项记录
class CCPS_ConfirmRealEvt_Req: public CNetCmdHead
{
public:
	SG_UINT				EvtID;	//实时事项ID
	SG_INT				EvtYMD;	//事项的发生时间
	SG_INT				EvtHMS;	//事项的发生时间
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
//  同步表数据
class CDBS_SyncTableData_Req : public CNetCmdHead
{
public:
	SG_INT				SrvType;	//服务类型
	S_LOGICCELLINFO		LogicCell;	//逻辑数据单元
	SG_INT				NodeID;		//节点号
	SG_UINT64				StartVer;	//起始版本
	SG_UINT64				EndVer;		//终止版本
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};
//	获得某个逻辑数据单元的版本号的返回
class CDBS_SyncTableData_Res : public CNetCmdHead
{
public:
	SG_UINT64				EndVer;		//终止版本
	
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
//           IDMAP服务接口
//==================================================================================================
//	本系统转换成其他系统的请求
class CIDMAPCmd_Self2Other_Req : public CNetCmdHead
{
public:
	SG_INT		ClassType;	//对照表分类号
	SG_OBJECTS	SelfObjs;	//本系统设备列表
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
	CSgDataSet	RetDat;	//返回本系统和外系统对照表  OBJTYPE,OBJID OTHER_ID
	CSgDataSet	*pRetDat;	//返回本系统和外系统对照表  OBJTYPE,OBJID OTHER_ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Self2Other_Res()
	{
		pRetDat=NULL;
	};
};
//==================================================================================================
//==================================================================================================
//	其他系统转换成本系统的请求
class CIDMAPCmd_Other2Self_Req : public CNetCmdHead
{
public:
	SG_INT		ClassType;	//对照表分类号
	VECT_STRING		OtherObjs; //外部系统设备列表
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
	CSgDataSet	RetDat;	//返回本系统和外系统对照表  OBJTYPE,OBJID OTHER_ID
	CSgDataSet	*pRetDat;	//返回本系统和外系统对照表  OBJTYPE,OBJID OTHER_ID
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CIDMAPCmd_Other2Self_Res()
	{
		pRetDat=NULL;
	};
};
//==================================================================================================
//           数据处理服务接口
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
	SG_USHORT	Operation;	//	0: 无效 1：遥控 2：遥调
	SG_USHORT	OperType;	//	0：直接执行 1：预置（选择） 2：执行 3：取消	
	SG_INT		ObjType;	//	500：yc 501：yx 
	SG_INT		ObjID;		//	测点ID
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
	SG_USHORT	OperType;	//	0：设置 1：锁定 2：解锁	
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
	SG_INT	ObjType;	//	500：yc 501：yx 502：kwh  600:RTU状态
	CSgDataSet  DatSet;		//  数据集，  YC包含字段:ID FLAG,VALUE STATUS PROCTIME 
							//YX包含字段:ID FLAG,VALUE STATUS PROCTIME MS
							//KWH包含字段:ID FLAG,VALUE STATUS PROCTIME
							//RTU状态包括字段: ID STATUS PROCTIME
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
	SG_INT	ObjType;	//	500：yc 501：yx 502：kwh
	SG_INT	TaskID;		//如果是后台发起的抄收命令,则是抄收任务号
	CSgDataSet  DatSet;		//  数据集，  包含字段:ID YMD,HMS,FLAG,STATUS,VALUE
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
	SG_INT		Res;	//备用字段不用
	SG_INT		TaskID;
	CSgLobDataSet  DatSet;		//数据集，  包含字段:YMD,HMS,OBJTYPE,OBJID,DAT
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
//           前置服务接口
//==================================================================================================
class CCommSrv_Operator_Req:public CNetCmdHead
{
public:
	SG_USHORT	Operation;	//	0: 无效 1：遥控 2：遥调
	SG_USHORT	OperType;	//	0：直接执行 1：预置（选择） 2：执行 3：取消	
	SG_INT		ObjType;	//	500：yc 501：yx 
	SG_INT		ObjID;		//	测点ID
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
	SG_USHORT	OperType;		//	0：直接执行 1：预置（选择） 2：执行 3：取消	
	SG_INT		RtuID;			//	终端ID
	SG_INT		DevAddr;		//	设备地址
	SG_INT		SettingArea;	//	设置区域
	CSgDataSet  DatSet;		//  数据集，  包含字段:定值序号（NO），寄存器字节长度（DATLEN），定值（VAL）
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
	SG_INT		RtuID;			//	终端ID
	SG_INT		DevAddr;		//	设备地址
	SG_INT		SettingArea;	//	设置区域
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
	CCommSrv_ReadProtSetting_Req()
	{
	};
};
class CCommSrv_ReadProtSetting_Res:public CNetCmdHead
{
public:
	CSgDataSet  RetDat;		//  数据集，  包含字段:定值序号（NO），寄存器字节长度（DATLEN），定值（VAL）
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
	SG_INT		StartYMD;	//起始年月日 yyyymmdd
	SG_INT		EndYMD;		//终止年月日 yyyymmdd
	SG_INT		ObjType;	//	500：yc 502：kwh 
	SG_INT		TaskID;		//	任务ID
	VECT_INT	PtIDList;	//测点ID列表	
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
//           进程管理服务接口
//==================================================================================================
class CPCM_StartProc_Req: public CNetCmdHead
{
public:
	//SG_INT		NodeID;		//节点ID,放在CNetCmdHead的WorkSpace里 若<=0，则为查本机
	CSgString	ProcName;	//进程名称，如果npa,1则表示需要将pcm2.ini中的配置项改为启动1
	CSgString	StartPara;	//命令参数
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
	//SG_INT		NodeID;		//节点ID,放在CNetCmdHead的WorkSpace里 若<=0，则为查本机
	//SG_INT		OnlyStopProcFlag;	//仅仅停止进程 
	CSgString	ProcName;	//进程名称 如果npa,1则表示需要将pcm2.ini中的配置项改为停止
	CSgString	EndPara;	//停止命令参数
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
	//SG_INT		NodeID;		//节点ID,放在CNetCmdHead的WorkSpace里 若<=0，则为查本机
	SG_INT			SendCmdType;	//存放命令类型
	CSgLobData		LobDat;	//存放数据内容
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


#define IDPPROC_ASKSTAT_PROC	1		//询问单个进程状况
#define IDPPROC_ASKSTAT_SRV		2		//询问服务器进程状况
class CPCM_AskStatus_Req: public CNetCmdHead	
{
public:
	//SG_INT		NodeID;		//节点ID,放在CNetCmdHead的WorkSpace里 若<=0，则为查本机
	SG_INT		SubType;	//子命令
	CSgString	ProcName;	//进程名称
	CPCM_AskStatus_Req()
	{
		SubType=IDPPROC_ASKSTAT_SRV;
		ProcName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

#define IDPPROC_PROCSTAT_OK			1		//进程运行
#define IDPPROC_PROCSTAT_STOP		2		//进程停止
#define IDPPROC_PROCSTAT_WARNING	3		//进程运行有警告
class CPCM_ProcStatus
{
public:
	SG_INT			ProcID;	//进程ID
	SG_INT			State;	//进程命令
	std::string		ProcName;	//进程名称
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
	SG_INT			CalcProcType;	//存放命令类型
	VECT_TWOSTRING	ReplaceKeyList;	//替换参数信息
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
	SG_UINT64			ProcID;	//返回进程ID
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
	SG_UINT64			ProcID;	//返回进程ID
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
	CPCM_ProcStatus			ProcStatus;	//返回进程ID
	virtual SG_BOOL		Serialize(CSgArchive & ar, SG_INT VerNo = -1);
	virtual int buf_size();
};

//请求系统安装目录
typedef CNetCmdHead		CPCM_SysEnvPath_Req;
class CPCM_SysEnvPath_Res: public CNetCmdHead	
{
public:
	CSgString	PathName;	//路径名称，是系统绝对路径
	CPCM_SysEnvPath_Res()
	{
		PathName="";
	};
	virtual SG_BOOL		Serialize(CSgArchive & ar,SG_INT VerNo=-1);
	virtual int buf_size();
};

//请求目录下的文件信息，不包括子目录
class CPCM_PathFileInfo_Req: public CNetCmdHead	
{
public:
	CSgString	PathName;	//路径名称，是系统绝对路径
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
	CSgString			PathName;	//路径名称，是系统绝对路径
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

//请求目录下的文件信息，不包括子目录
#define PCM_FILEOPER_FILE_DEL			1
#define PCM_FILEOPER_FILE_RENAME		2
#define PCM_FILEOPER_FILE_CP			3
#define PCM_FILEOPER_PATH_CRT			4
#define PCM_FILEOPER_PATH_DEL			5
class CPCM_FileOper_Req: public CNetCmdHead	
{
public:
	SG_INT		OperType;		//1: 删除     2：修改名称  3:拷贝 4建立目录  5:删除目录
	CSgString	FileName;		//带路径名称，是系统绝对路径
	CSgString	NewFileName;	//带路径名称，是系统绝对路径
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

//下载文件请求
class CPCM_DownLoadFile_Req: public CNetCmdHead	
{
public:
	CSgString	FileName;		//带路径名称，是系统绝对路径
	SG_INT		TransNo;		//传输的包号，从0开始
	SG_INT64	FileStartPos;	//传输的文件起始位置
	SG_INT	    SendMaxSize;	//发送的文件内容最大字节数
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
	SG_INT		TransNo;		//传输的包号，从0开始
	SG_INT64	FileStartPos;	//传输的文件起始位置
	SG_INT	    SendSize;		//发送的文件内容字节数
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
	CSgString	FileName;		//带路径名称，是系统绝对路径
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
//上载文件请求
class CPCM_UpLoadFile_Req: public CNetCmdHead	
{
public:
	CSgString	FileName;		//带路径名称，是系统绝对路径
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
//上载文件返回
class CPCM_UpLoadFile_Res: public CNetCmdHead	
{
public:
	CSgString	FileName;		//带路径名称，是系统绝对路径
	SG_INT		TransNo;		//传输的包号，从0开始
	SG_UCHAR	RecvOKFlag;
	VECT_INT	ExistTransNoList;//服务端已存在的包序号
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
//上载文件返回
/*class CPCM_UpLoadFile_New_Res: public CPCM_UpLoadFile_Res
{
public:
	VECT_INT	ExistTransNoList;//服务端已存在的包序号
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
#define DBCMD_DOWNLOAD_BY_FILENAME		0	//按文件名获取文件内容
#define DBCMD_DOWNLOAD_BY_REQSTR		1	//按需求语句获取文件内容
class CDBCmd_DownLoadFile_Req:public CPCM_DownLoadFile_Req
{
public:
	SG_UCHAR  ReqType; //0:按文件名获取文件内容,  1:按需求语句获取文件内容 
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
#define PCM_SRVCTRL_RESTART		0 //重新启动
#define PCM_SRVCTRL_STOP		1 //停止服务进程
#define PCM_SRVCTRL_START		2 //启动服务进程
class CPCM_RestartSrv_Req:public CNetCmdHead
{
public:
	SG_INT	StartFlag;		//0:重新启动  1：停止服务进程  2：启动服务进程
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
	CSgString	ExePath;	//执行路径PATH
	CSgString	ShellCmd;	//Shell命令参数
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
	CSgString	OutInfo;	//命令执行输出信息
	CSgString	CurrentPath; //当前路径
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
	CSgString	FileName;	//带路径的文件名称
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
	SG_UINT		FileTime;	//文件时间
	SG_UINT		FileSize;	//文件大小
	SG_UCHAR	FileMD5[16];	//文件MD5校验值
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
	CSgString	DsName;			//数据源的名称
	CSgString	SQLFile;		//执行的SQL文件名称，带路径名称，是系统绝对路径
	CSgString	LogFile;		//输出日志文件，带路径名称，是系统绝对路径
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
	short			memLoad;						//内存占用比
	short			cpuLoad;						//CPU使用率
	ACE_UINT32		availMem;						//可用内存
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
//           命令解析宏
//==================================================================================================
//命令解析宏
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
	responser.RetInfo.Format("请求序列化失败 SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
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
	responser.RetInfo.Format("请求序列化失败 SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
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
		responser.RetInfo.Format("请求序列化失败 SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
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
		responser.RetInfo.Format("请求序列化失败 SrvVer:%d CurVer:%d\n",request.CmdVersion,SG_NET_VERSION);\
	else 	ret = PROCFUNC(request,responser);\
	CSgArchive r_ar(&MemFile, CSgArchive::store, 4096 * 4096);\
	responser.Serialize(r_ar,request.StartRow,request.MaxRow,responser.CmdVersion);\
	r_ar.Close();\
	ret=true;

//==================================================================================================
//	根据定义要求决定是否将函数实现内联
//#if !defined ( __GIS_INCLUDE_CPP__ )
#include "command/DBCommand.inl"
//#endif /* __GIS_INCLUDE_CPP__ */

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
