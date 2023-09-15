#ifndef _INCLUDE_DPP_VEROPER_H_
#define _INCLUDE_DPP_VEROPER_H_
#include "sgdebuginfo.h"
#include "rdp_const.h"
#include "DbBaseOper.h"
#include "osbase.h" 
#include "DBCommand.h"
#ifndef SG_MINIBOX_PLAT
class CDB_SysModelInfo
{
	typedef struct S_DPPMODELINFO
	{
		int				Enableed;	//bit0:有空间表  bit1:有属性表
		std::string		DatVerNoFieldName; //版本字段名称
		S_STRINGINT		TblNameVerType[2]; //0:空间表  1：属性表  StrVal:TblName IntVal:版本类型 0:没有版本   1:全量版本  2：增量版本
	}S_DPPMODELINFO;
	typedef std::map<SG_INT, S_DPPMODELINFO> MAP_INT_MODELINFO;
	static 	CSG_OS_ThreadVar	m_DBSysModelLock;
	static	MAP_INT_MODELINFO	m_ObjModelInfoList; //first:ObjType;
public:
	int GetTblName(CDBOperBaseSession *pSysDBOper,void *pSvc,int ObjType, SG_UCHAR IsGeoFlag, CSgString &TblName, int &VerType,CSgString &DatVerField);
	int RDB_ReadRecorder(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_ReadVerRecorder_Req &Request, CDBCmd_ReadVerRecorder_Res &Response);
	int RDB_InsertRecorder(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_InsertVerRecorder_Req &Request, CDBCmd_InsertVerRecorder_Res &Response);
	int RDB_UpdateRecorder(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_UpdateVerRecorder_Req &Request, CDBCmd_UpdateVerRecorder_Res &Response);
	int RDB_DeleteRecorder(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_DeleteVerRecorder_Req &Request, CDBCmd_DeleteVerRecorder_Res &Response);
	int RDB_MergeRecorder(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_MergeVerRecorder_Req &Request, CDBCmd_MergeVerRecorder_Res &Response);
	int RDB_CommitDatVer(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_CommitDatVer_Req &Request, CDBCmd_CommitDatVer_Res &Response);
	int RDB_RollBackDatVer(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_RollBackDatVer_Req &Request, CDBCmd_RollBackDatVer_Res &Response);
	int RDB_CompareDatVer(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_CompareDatVer_Req &Request, CDBCmd_CompareDatVer_Res &Response);
	int RDB_CopyDatVer(CDBOperBaseSession *pDBOper, CSgString &TblName, int VerType, CSgString &DatVerField, CDBCmd_CopyDatVer_Req &Request, CDBCmd_CopyDatVer_Res &Response);

	int RDB_InsertRecord(CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, int VerType, int IsGeoFlag,
		CSgString &DatVerField, int  DatVerNo, CSgLobDataSet *pDatSet, CSgString &RetInfo);
	int RDB_UpdateRecord(CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, int VerType, int IsGeoFlag,
		CSgString &DatVerField, int  DatVerNo, CSgLobDataSet *pDatSet, CSgString &RetInfo);
	int RDB_DeleteRecord(CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, int VerType, int IsGeoFlag,
		CSgString &DatVerField, int  DatVerNo, CSgLobDataSet *pDatSet, CSgString &RetInfo);
	int RDB_MergeRecord(CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, int VerType, int IsGeoFlag,
		CSgString &DatVerField, int  DatVerNo, CSgLobDataSet *pDatSet, CSgString &RetInfo);

private:
	int ReadInfo(CDBOperBaseSession *pSysDBOper,void *pSvc);
	int RDB_ReadVerRecorder_AllDat(int VerType, CDBOperBaseSession *pDBOper,void *pSvc, CSgString &TblName, CSgString &DatVerField, int  IsGeoFlag,
		CDBCmd_ReadVerRecorder_Req &Request, CDBCmd_ReadVerRecorder_Res &Response);
	int RDB_ReadVerRecorder_Increment(int VerType, CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName,CSgString &DatVerField, int  IsGeoFlag,
		int DatVerNo, CSgString &Fields, CSgString &WhereSQL, CSgDataSet *pCompileDatSet, 
		int StartRow, int MaxRow, CSgLobDataSet &RetDatSet, int *ExistRcdNum, CSgString &ErrMsg);

	int RDB_ReadVerRecorder_ADTbl(int VerType, CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, CSgString &DatVerField, int  IsGeoFlag,
		int DatVerNo, CSgString &Fields, CSgString &WhereSQL, CSgDataSet *pCompileDatSet,
		int StartRow, int MaxRow, CSgLobDataSet &RetDatSet, int *ExistRcdNum,SET_INT *pDelIDList,CSgLobDataSet *pBaseDatSet,CSgString &ErrMsg);
	CSgLobDataSet *DatSetExtendVerField(CSgString &DatVerField, CSgLobDataSet &DatSet, CSgLobDataSet *pDatSet, int DatVerNo);
	int RDB_InsertVerRecorder_Increment(int VerType, CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, CSgString &DatVerField, int IsGeoFlag, int DatVerNo,
		CSgLobDataSet &DataSet,CSgString &ErrMsg);
	int RDB_InsertVerRecorder_ADTbl(int VerType, CDBOperBaseSession *pDBOper, void *pSvc, CSgString &TblName, CSgString &DatVerField, int IsGeoFlag, int DatVerNo,
		CSgLobDataSet &DataSet, CSgString &ErrMsg);
	int CmpGeoDat(SG_INT FeatureType, void *pGeoDat1, void *pGeoDat2);
	int DataSetCompare(CSgLobDataSet &NewDatSet, int NewRcdNo, CSgLobDataSet &OldDatSet, int OldRcdNo,
		int CmpGeoField, CSgObjects &NewFieldList, CSgObjects &OldFieldList, VECT_TWOINT LobFieldPtrList);
	int DatSetCompare(int IsGeoFlag, CSgString &DatVerField, CSgLobDataSet &NewDatSet, CSgLobDataSet &OldDatSet,
		CSgObjects &DelInOldRowList, CSgObjects &UpdateRowList, CSgObjects &InsertInNewRowList, CSgString &MsgStr);
	int DatSetCompare(int IsGeoFlag, CSgString &DatVerField, CSgLobDataSet &NewDatSet, CSgLobDataSet &OldDatSet,
		CSgDataSetArray_ObjOper &DatSetArray, CSgString &MsgStr);

};
#endif
#endif