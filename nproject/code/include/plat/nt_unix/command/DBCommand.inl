#pragma once

#include "DBCommand.h"

//==================================================================================================
#ifndef __DB_INCLUDE_CPP__
#	define DBCMD_INLINE inline 
#else
#	define DBCMD_INLINE
#endif

//==================================================================================================
/*DBCMD_INLINE int CNetCmdHead::buf_size()
{
	return sizeof(CmdType)+sizeof(FrameLen)+sizeof(CmdVersion)+sizeof(ZipFlag)+
		+sizeof(RetVal)+sizeof(DBNo)+sizeof(FrameNo)+sizeof(FinishFlag)+RetInfo.buf_size()+WorkSpaces.buf_size();
}

DBCMD_INLINE SG_BOOL CNetCmdHead::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	DBCMD_GETVERSION(VerNo)
		if(ar.IsLoading())
		{
			ar >> CmdType;
			ar >> FrameLen;
			ar >> CmdVersion;
			if(CmdVersion>DBCMD_NET_VERSION)
				return false;
			ar >> ZipFlag;
			ar >> RetVal;
			WorkSpaces.clear();
			if(CmdVersion<=DBCMD_NET_VERSION_1)
			{
				ACE_UINT32 WorkSpace;
				ar>>WorkSpace;
				WorkSpaces.push_back(WorkSpace);
			}
			ar >> DBNo;
			if(CmdVersion>DBCMD_NET_VERSION_2)
			{
				ar >> FrameNo;
				ar >> FinishFlag;			
			}
			else
			{
				FrameNo=0;
				FinishFlag=true;
			}
	}
		else
		{
			CmdVersion=VerNo;
			ar << CmdType;
			ar << FrameLen;
			ar << CmdVersion;
			ar << ZipFlag;
			ar << RetVal;
			if(CmdVersion<=DBCMD_NET_VERSION_1)
			{
				ACE_UINT32 WorkSpace=0;
				if(WorkSpaces.size()>0)
					WorkSpace=WorkSpaces[0];
				ar << WorkSpace;
			}
			ar << DBNo;
			if(CmdVersion>DBCMD_NET_VERSION_2)
			{
				ar << FrameNo;
				ar << FinishFlag;			
			}
		}
		RetInfo.Serialize(ar);
		if(CmdVersion>DBCMD_NET_VERSION_1)
			WorkSpaces.Serialize(ar);

		if(RetVal==DB_RETVAL_ERROR||RetVal==DB_RETVAL_COMM_ERROR)
			return false;
	return true;
}
*/
//==================================================================================================
DBCMD_INLINE int CReadDatNetCmd_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(MaxRow)+sizeof(StartRow);
}

DBCMD_INLINE SG_BOOL CReadDatNetCmd_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> StartRow;
		SG_UINT SendVal;
		ar >> SendVal;

	//	if(VerNo>=SG_NET_VERSION_53)
		{
			MaxRow=SendVal&0x3FFFFFFF;
			SortFlag=SendVal/0x40000000;
		}
	/*	else
		{
			MaxRow=SendVal;
			SortFlag=0;
		}
	*/
	}
	else
	{
		ar << StartRow;
		SG_UINT SendVal;
	//	if(VerNo>=SG_NET_VERSION_53)
			SendVal=SortFlag*0x40000000+MaxRow;
	//	else
	//		SendVal=MaxRow;
		ar << SendVal;
	}
	return true;
}

//==================================================================================================
DBCMD_INLINE int CDBCmd_ReadRecorder_Req::buf_size()
{
	return CReadDatNetCmd_Req::buf_size()+SQLBuf.buf_size();
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadRecorder_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CReadDatNetCmd_Req::Serialize(ar,VerNo)==false)
			return false;
	SQLBuf.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CDBCmd_CompileReadRecorder_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CompileReadRecorder_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CDBCmd_ReadRecorder_Req::Serialize(ar,VerNo)==false)
		return false;
	if(pDataSet)
		pDataSet->Serialize(ar);
	else
		DataSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_ReadGeoRecorder_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDBCmd_ReadGeoRecorder_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CDBCmd_ReadRecorder_Req::Serialize(ar,VerNo)==false)
			return false;
	if(pSgLine)
		pSgLine->Serialize(ar);
	else
		SgLine.Serialize(ar);
	pszAndOr.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> relationType;
	}
	else
	{
		ar << relationType;
	}
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CNetCmdVerInfo::buf_size()
{
	return sizeof(DatVerNo);

}

DBCMD_INLINE SG_BOOL CNetCmdVerInfo::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (ar.IsLoading())
	{
		ar >> DatVerNo;
	}
	else
	{
		ar << DatVerNo;
	}
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_ReadVerRecorder_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDBCmd_ReadVerRecorder_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CReadDatNetCmd_Req::Serialize(ar, VerNo) == false)
		return false;
	if (CNetCmdVerInfo::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ObjType;
		ar >> IsGeoFlag;
	}
	else
	{
		ar << ObjType;
		ar << IsGeoFlag;
	}
	Fields.Serialize(ar);
	WhereSQL.Serialize(ar);
	if (pCompileDataSet)
		pCompileDataSet->Serialize(ar);
	else
		CompileDataSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_ReadTableInfo_Req::buf_size()
{
	return CNetCmdHead::buf_size()+TblName.buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_ReadTableInfo_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	TblName.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_ReadTableInfo_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadTableInfo_Res::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_InsertVerRecorder_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDBCmd_InsertVerRecorder_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (CNetCmdVerInfo::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ObjType;
		ar >> IsGeoFlag;
	}
	else
	{
		ar << ObjType;
		ar << IsGeoFlag;
	}
	if (pDataSet)
		pDataSet->Serialize(ar);
	else
		DataSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_CommitDatVer_Req::buf_size()
{
	return CNetCmdHead::buf_size()+ CNetCmdVerInfo::buf_size()+sizeof(ObjType)+sizeof(IsGeoFlag);

}

DBCMD_INLINE SG_BOOL CDBCmd_CommitDatVer_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (CNetCmdVerInfo::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ObjType;
		ar >> IsGeoFlag;
	}
	else
	{
		ar << ObjType;
		ar << IsGeoFlag;
	}
	return true;
}

//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_CompareDatVer_Req::buf_size()
{
	return CNetCmdHead::buf_size() + sizeof(ObjType) + sizeof(IsGeoFlag) + DatVer[0].buf_size() + DatVer[1].buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_CompareDatVer_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ObjType;
		ar >> IsGeoFlag;
	}
	else
	{
		ar << ObjType;
		ar << IsGeoFlag;
	}
	int i;
	for (i = 0; i < 2; i++)
		DatVer[i].Serialize(ar);
	return true;
}

//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_CompareDatVer_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDBCmd_CompareDatVer_Res::Serialize(CSgArchive &ar, SG_INT VerNo)
{

	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (pDatSetArray)
		pDatSetArray->Serialize(ar);
	else
		DatSetArray.Serialize(ar);
	return true;
}

//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CDBCmd_GetSDEOwner_Res::buf_size()
{
	return Owner.buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_GetSDEOwner_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	return Owner.Serialize(ar);
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_GeoOverlay_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_GeoOverlay_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pLine1)
		pLine1->Serialize(ar);
	else
		Line1.Serialize(ar);
	if(pLine2)
		pLine2->Serialize(ar);
	else
		Line2.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_GeoOverlay_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_GeoOverlay_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	int i;
	if(ar.IsLoading())
	{
		ar >> CommonNums;
		pCommonLines=NULL;
		if(CommonNums>0)
		{
			pCommonLines=new CSgLine[CommonNums];
			for(i=0;i<CommonNums;i++)
				pCommonLines[i].Serialize(ar);
		}
	}
	else
	{
		ar << CommonNums;
		for(i=0;i<CommonNums;i++)
			pCommonLines[i].Serialize(ar);
	}
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_BatchReadRecorder_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_BatchReadRecorder_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pDataSet)
		pDataSet->Serialize(ar);
	else
		DataSet.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_BatchReadRecorder_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_BatchReadRecorder_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	RetInfo_DatSet.Serialize(ar);
	if(pRetDataSetArray)
		pRetDataSetArray->Serialize(ar);
	else
		RetDataSetArray.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_CalGeoBuffer_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CalGeoBuffer_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> nFeatureType;
		ar >> dWidth;
	}
	else
	{
		ar << nFeatureType;
		ar << dWidth;
	}
	if(pPoints)
		pPoints->Serialize(ar);
	else
		Points.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_CalGeoBuffer_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CalGeoBuffer_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pLine)
		pLine->Serialize(ar);
	else
		Line.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_CalLineGeoBuffer_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CalLineGeoBuffer_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> nFeatureType;
		ar >> dWidth;
	}
	else
	{
		ar << nFeatureType;
		ar << dWidth;
	}
	if(pLine)
		pLine->Serialize(ar);
	else
		Line.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_CalLineGeoBuffer_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CalLineGeoBuffer_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{

	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pLine)
		pLine->Serialize(ar);
	else
		Line.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_ExecSQL_Req::buf_size()
{
	return CNetCmdHead::buf_size()+SQLBuf.buf_size();
}

DBCMD_INLINE SG_BOOL CDBCmd_ExecSQL_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	SQLBuf.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_CompileExecSQL_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CompileExecSQL_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CDBCmd_ExecSQL_Req::Serialize(ar,VerNo)==false)
		return false;
	if(pDataSet)
		pDataSet->Serialize(ar);
	else
		DataSet.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_ExecSQLNotTrigger_Req::buf_size()
{
	return CNetCmdHead::buf_size()+SQLBuf.buf_size()+TblName.buf_size();
}

DBCMD_INLINE SG_BOOL CDBCmd_ExecSQLNotTrigger_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SQLBuf.Serialize(ar);
	TblName.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CDBCmd_TransOper_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_TransOper_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pOperDatSetArray)
		pOperDatSetArray->Serialize(ar);
	else
		OperDatSetArray.Serialize(ar);
	return true;
}

//==================================================================================================
DBCMD_INLINE int CDBCmd_MultiDBTransOper_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_MultiDBTransOper_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if (pOperDatSetArray)
		pOperDatSetArray->Serialize(ar);
	else
		OperDatSetArray.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CDBCmd_MultiDBTransVerOper_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_MultiDBTransVerOper_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	SG_INT	Cnt, i;
	S_TWOINT	TwoInt;
	CSgDataSetArray_ObjDBOper *pUseDatSetArray = pOperDatSetArray;
	if (pUseDatSetArray = NULL)
		pUseDatSetArray = &(OperDatSetArray);
	VECT_TWOINT *pUserInfoArray = pOperDatInfoArray;
	if (pUserInfoArray == NULL)
		pUserInfoArray = &OperDatInfoArray;

	if (ar.IsLoading())
	{
		pUserInfoArray->clear();
		ar >> Cnt;
		for (i = 0; i < Cnt; i++)
		{
			TwoInt.Serialize(ar);
			pUserInfoArray->push_back(TwoInt);
		}
	}
	else
	{
		Cnt = pUserInfoArray->size();
		ar << Cnt;
		for (i = 0; i < Cnt; i++)
			(*pUserInfoArray)[i].Serialize(ar);
	}
	pUseDatSetArray->Serialize(ar);
	return true;
}



//==================================================================================================
DBCMD_INLINE int CDBCmd_ReadLobField_Req::buf_size()
{
	return CNetCmdHead::buf_size()+TableName.buf_size()+LobFieldName.buf_size()+WhereSQL.buf_size();
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadLobField_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	TableName.Serialize(ar);
	LobFieldName.Serialize(ar);
	WhereSQL.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_ReadLobField_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadLobField_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CDBCmd_WriteLobField_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_WriteLobField_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	TableName.Serialize(ar);
	LobFieldName.Serialize(ar);
	WhereSQL.Serialize(ar);
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_GetSysDate_Res::buf_size()
{
	return sizeof(SysTime);
}

DBCMD_INLINE SG_BOOL CDBCmd_GetSysDate_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> SysTime;
	}
	else
	{
		ar << SysTime;
	}
	return true;
}

DBCMD_INLINE SG_BOOL CDBCmd_GetIDVal_Req::Serialize(CSgArchive & ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	AllocName.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> Cnt;
	}
	else
	{
		ar << Cnt;
	}
	return true;
}

DBCMD_INLINE int CDBCmd_GetIDVal_Req::buf_size()
{
	return CNetCmdHead::buf_size()+AllocName.buf_size()+sizeof(Cnt);
}

DBCMD_INLINE SG_BOOL CDBCmd_GetIDVal_New_Req::Serialize(CSgArchive & ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	AllocName.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> Cnt;
		ar >> ReqWS;
	}
	else
	{
		ar << Cnt;
		ar << ReqWS;
	}
	return true;
}

DBCMD_INLINE int CDBCmd_GetIDVal_New_Req::buf_size()
{
	return CNetCmdHead::buf_size()+AllocName.buf_size()+sizeof(Cnt)+sizeof(ReqWS);
}

DBCMD_INLINE SG_BOOL CDBCmd_GetIDVal_Res::Serialize(CSgArchive & ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pObjIDS)
		return pObjIDS->Serialize(ar);
	return ObjIDS.Serialize(ar);
}

DBCMD_INLINE int CDBCmd_GetIDVal_Res::buf_size()
{
	return CNetCmdHead::buf_size()+ObjIDS.buf_size();
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_ReadTableName_Req::buf_size()
{
	return CNetCmdHead::buf_size()+DBName.buf_size();
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadTableName_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	DBName.Serialize(ar);
	return true;
}
DBCMD_INLINE int CDBCmd_ReadTableName_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_ReadTableName_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

DBCMD_INLINE int CDBCmd_CreateTable_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CDBCmd_CreateTable_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}


//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_ReadTblRecorder_Req::buf_size()
{
	return CNetCmdHead::buf_size()+TableName.buf_size();
}

DBCMD_INLINE SG_BOOL CHSDA_ReadTblRecorder_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	TableName.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CHSDA_ReadTblRecorder_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CHSDA_ReadTblRecorder_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_SubscribeData_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CHSDA_SubscribeData_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> FreshTime;
	}
	else
	{
		ar << FreshTime;
	}
	TableName.Serialize(ar);
	Fields.Serialize(ar);
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
//==================================================================================================
DBCMD_INLINE int CHSDA_SubscribeData_Res::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CHSDA_SubscribeData_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> StreamHandle;
	}
	else
	{
		ar << StreamHandle;
	}

	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_CancelSubscribe_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(StreamHandle);
}

DBCMD_INLINE SG_BOOL CHSDA_CancelSubscribe_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> StreamHandle;
	}
	else
	{
		ar << StreamHandle;
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_GetChangeData_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(StreamHandle)+sizeof(GetType);
}

DBCMD_INLINE SG_BOOL CHSDA_GetChangeData_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> StreamHandle;
		ar >> GetType;
	}
	else
	{
		ar << StreamHandle;
		ar << GetType;
	}
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_YKOper_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(Value)
		+OperMan.buf_size()+CheckMan.buf_size();
}

DBCMD_INLINE SG_BOOL CHSDA_YKOper_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> OperType;
		ar >> ObjType;
		ar >> ObjID;
		ar >> Value;
	}
	else
	{
		ar << OperType;
		ar << ObjType;
		ar << ObjID;
		ar << Value;
	}
	OperMan.Serialize(ar);
	CheckMan.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_YTOper_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(ValueType)+sizeof(Value)
		+OperMan.buf_size()+CheckMan.buf_size();
}

DBCMD_INLINE SG_BOOL CHSDA_YTOper_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> OperType;
		ar >> ObjType;
		ar >> ObjID;
		ar >> ValueType;
		ar >> Value;
	}
	else
	{
		ar << OperType;
		ar << ObjType;
		ar << ObjID;
		ar << ValueType;
		ar << Value;
	}
	OperMan.Serialize(ar);
	CheckMan.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_LockRtData_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(Value);
		
}

DBCMD_INLINE SG_BOOL CHSDA_LockRtData_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> OperType;
		ar >> ObjType;
		ar >> ObjID;
		ar >> Value;
	}
	else
	{
		ar << OperType;
		ar << ObjType;
		ar << ObjID;
		ar << Value;
	}
	return true;
}
DBCMD_INLINE int CHSDA_ManSetRtData_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+sizeof(ObjType)+sizeof(DevType)+sizeof(DevID)
		+sizeof(MeasType)+sizeof(ObjID)+sizeof(Val)+sizeof(Terminal);

}

DBCMD_INLINE SG_BOOL CHSDA_ManSetRtData_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>OperType;
		ar>>ObjType;
		ar>>DevType;
		ar>>DevID;
		ar>>Terminal;
		ar>>MeasType;
		ar>>ObjID;
		ar>>Val;
	}
	else
	{
		ar<<OperType;
		ar<<ObjType;
		ar<<DevType;
		ar<<DevID;
		ar<<Terminal;
		ar<<MeasType;
		ar<<ObjID;
		ar<<Val;
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_CommSrvCmd_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(RtuID)+TaskInfo.buf_size();

}

DBCMD_INLINE SG_BOOL CHSDA_CommSrvCmd_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar>>RtuID;
	else
		ar<<RtuID;

	return TaskInfo.Serialize(ar,VerNo);
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_CommSrvCmd_New_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_CommSrvCmd_New_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CHSDA_CommSrvCmd_Req::Serialize(ar,VerNo)==false)
		return false;
	if(pDataSetArray)
		pDataSetArray->Serialize(ar);
	else
		DataSetArray.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
#ifndef SG_MINIBOX_PLAT
DBCMD_INLINE int CHSDA_ChangeEvtStatus_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_ChangeEvtStatus_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT i,Cnt;
	VECT_EVT_NOTIYMSG *pProcList;
	if(pMsgList)
		pProcList=pMsgList;
	else
		pProcList=&MsgList;
	if(ar.IsLoading())
	{
		ar>>Cnt;
		S_RDP_EVT_NOTIFYMSG Msg;
		for(i=0;i<Cnt;i++)
		{
			Msg.Serialize(ar);
			pProcList->push_back(Msg);
		}
	}
	else
	{
		Cnt=pProcList->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
			(*pProcList)[i].Serialize(ar);
	}

	return true;
}
#endif

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_GetDevPointInfo_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(ObjType)+sizeof(DevType)+sizeof(DevID)
		+sizeof(MeasType)+sizeof(Terminal);

}

DBCMD_INLINE SG_BOOL CHSDA_GetDevPointInfo_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>ObjType;
		ar>>DevType;
		ar>>DevID;
		ar>>Terminal;
		ar>>MeasType;
	}
	else
	{
		ar<<ObjType;
		ar<<DevType;
		ar<<DevID;
		ar<<Terminal;
		ar<<MeasType;
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
#ifndef SG_MINIBOX_PLAT
DBCMD_INLINE int CHSDA_GetDevPointInfo_New_Req::buf_size()
{
	return CHSDA_GetDevPointInfo_Req::buf_size()+QueryFields.buf_size();

}

DBCMD_INLINE SG_BOOL CHSDA_GetDevPointInfo_New_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CHSDA_GetDevPointInfo_Req::Serialize(ar,VerNo)==false)
		return false;
	QueryFields.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_GetDevsPointInfo_Req::buf_size()
{
	return INT_MAX;
}

DBCMD_INLINE SG_BOOL CHSDA_GetDevsPointInfo_Req::Serialize(CSgArchive &ar,SG_INT VerNo,CSgObjects *pRcdNoList)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar>>ObjType;
	else
		ar<<ObjType;
	QueryFields.Serialize(ar);
	if(pDatSet)
		pDatSet->Serialize(ar,pRcdNoList);
	else
		DatSet.Serialize(ar,pRcdNoList);

	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_RDBMemOper_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+TblName.buf_size();

}

DBCMD_INLINE SG_BOOL CHSDA_RDBMemOper_Req::Serialize(CSgArchive &ar, SG_INT VerNo, CSgObjects *pRcdNoList)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
		ar >> OperType;
	else
		ar << OperType;
	TblName.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_RTDBLoadPara::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_RTDBLoadPara::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	CSgString sgstr;
	int KeyNum = 0;
	int i;
	S_TWOSTRING TwoStr;
	if (ar.IsLoading())
	{
		ar >> LoadType;
		ar >> RtDBVerNo;
		ar >> SchemaDBNo;
		ar >> SchemaProcMode;
		ar >> KeyNum;
		ReplaceKey.clear();
		for (i = 0; i < KeyNum; i++)
		{
			sgstr.Serialize(ar);
			TwoStr.Val1 = sgstr.GetSafeBuffer();
			sgstr.Serialize(ar);
			TwoStr.Val2 = sgstr.GetSafeBuffer();
			ReplaceKey.push_back(TwoStr);
		}
	}
	else
	{
		ar << LoadType;
		ar << RtDBVerNo;
		ar << SchemaDBNo;
		ar << SchemaProcMode;
		KeyNum = ReplaceKey.size();
		ar << KeyNum;
		for (i = 0; i < KeyNum; i++)
		{
			sgstr = ReplaceKey[i].Val1.data();
			sgstr.Serialize(ar);
			sgstr = ReplaceKey[i].Val2.data();
			sgstr.Serialize(ar);
		}

	}
	SrvTypeStr.Serialize(ar);
	FileName.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_RDB_NewCCRtDB_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_RDB_NewCCRtDB_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	CHSDA_RTDBLoadPara *pOperPara = pLoadPara;
	if (pOperPara == NULL)
		pOperPara = &LoadPara;
	return pOperPara->Serialize(ar, VerNo);
}

//==================================================================================================
//==================================================================================================
#endif
//=====================================================================================================

DBCMD_INLINE int CHSDA_GetPointInfo_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_GetPointInfo_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	int i,Cnt,PtID;
	VECT_INT		*pProcList;
	if(pPtIDList)
		pProcList=pPtIDList;
	else
		pProcList=&PtIDList;
	if(ar.IsLoading())
	{
		ar>>ObjType;
		ar>>Cnt;
		pProcList->clear();
		for(i=0;i<Cnt;i++)
		{
			ar>>PtID;
			pProcList->push_back(PtID);
		}
	}
	else
	{
		ar<<ObjType;
		Cnt=pProcList->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
		{
			PtID=(*pProcList)[i];
			ar<<PtID;
		}
	}
	QueryFields.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CHSDA_GetDevPointInfo_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CHSDA_GetDevPointInfo_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CTSDA_QueryDataByPt_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryDataByPt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CReadDatNetCmd_Req::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> ObjType;
		ar >> StartYMD;
		ar >> EndYMD;
		ar >> Interval;
	}
	else
	{
		ar << ObjType;
		ar << StartYMD;
		ar << EndYMD;
		ar << Interval;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
DBCMD_INLINE void CTSDA_QueryDataByPt_Req::operator = (const CTSDA_QueryDataByPt_Req &obj)
{
	ObjType=obj.ObjType;
	StartYMD=obj.StartYMD;
	EndYMD=obj.EndYMD;
	Interval=obj.Interval;
	StartRow=obj.StartRow;
	MaxRow=obj.MaxRow;
};
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CTSDA_QueryDataByPt_New_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryDataByPt_New_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CTSDA_QueryDataByPt_Req::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> StartHMS;
		ar >> EndHMS;
	}
	else
	{
		ar << StartHMS;
		ar << EndHMS;
	}
	return true;
}
DBCMD_INLINE void CTSDA_QueryDataByPt_New_Req::operator = (const CTSDA_QueryDataByPt_New_Req &obj)
{
	ObjType=obj.ObjType;
	StartYMD=obj.StartYMD;
	EndYMD=obj.EndYMD;
	StartHMS=obj.StartHMS;
	EndHMS=obj.EndHMS;
	Interval=obj.Interval;
	SortFlag=obj.SortFlag;
	StartRow=obj.StartRow;
	MaxRow=obj.MaxRow;
};

//=====================================================================================================
//==================================================================================================
//#ifndef SG_MINIBOX_PLAT
DBCMD_INLINE int CTSDA_QueryDataByPt_Append_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryDataByPt_Append_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CTSDA_QueryDataByPt_New_Req::Serialize(ar,VerNo)==false)
		return false;

	if(ar.IsLoading())
	{
		ar >> QueryMode;
		AppendWhereSql.Serialize(ar);
		AppendWhereSql.Trim();
	}
	else
	{
		ar << QueryMode;
		AppendWhereSql.Trim();
		AppendWhereSql.Serialize(ar);
	}
	return true;
}
DBCMD_INLINE void CTSDA_QueryDataByPt_Append_Req::operator = (const CTSDA_QueryDataByPt_Append_Req &obj)
{
	ObjType=obj.ObjType;
	StartYMD=obj.StartYMD;
	EndYMD=obj.EndYMD;
	StartHMS=obj.StartHMS;
	EndHMS=obj.EndHMS;
	Interval=obj.Interval;
	SortFlag=obj.SortFlag;
	StartRow=obj.StartRow;
	MaxRow=obj.MaxRow;
	QueryMode=obj.QueryMode;
	AppendWhereSql=obj.AppendWhereSql;
};
//#endif
//==================================================================================================
DBCMD_INLINE int CTSDA_QueryDataByPt_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryDataByPt_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CTSDA_QueryStatByPt_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryStatByPt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CReadDatNetCmd_Req::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> ObjType;
		ar >> StartYMD;
		ar >> EndYMD;
	}
	else
	{
		ar << ObjType;
		ar << StartYMD;
		ar << EndYMD;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
DBCMD_INLINE void CTSDA_QueryStatByPt_Req::operator = (const CTSDA_QueryStatByPt_Req &obj)
{
	ObjType=obj.ObjType;
	StartYMD=obj.StartYMD;
	EndYMD=obj.EndYMD;
};
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CTSDA_QueryValuesByPt_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryValuesByPt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CReadDatNetCmd_Req::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> ObjType;
		ar >> YMD;
		ar >> HMS;
	}
	else
	{
		ar << ObjType;
		ar << YMD;
		ar << HMS;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
DBCMD_INLINE void CTSDA_QueryValuesByPt_Req::operator = (const CTSDA_QueryValuesByPt_Req &obj)
{
	ObjType=obj.ObjType;
	YMD=obj.YMD;
	HMS=obj.HMS;
};
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CTSDA_SaveDataByPt_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_SaveDataByPt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> ObjType;
	}
	else
	{
		ar << ObjType;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
DBCMD_INLINE void CTSDA_SaveDataByPt_Req::operator = (const CTSDA_SaveDataByPt_Req &obj)
{
	ObjType=obj.ObjType;
};
#ifndef SG_MINIBOX_PLAT
DBCMD_INLINE int CCloud_GetDBLinkStat_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CCloud_GetDBLinkStat_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}
#endif
//==================================================================================================
//=====================================================================================================
DBCMD_INLINE int CTSDA_QueryDataByDev_NetRes::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CTSDA_QueryDataByDev_NetRes::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(pRetPara)
		pRetPara->Serialize(ar);
	else
		RetPara.Serialize(ar);
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
DBCMD_INLINE SG_BOOL CFPS_Download_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;

	if(ar.IsLoading())
	{
		ar >> ClassID;
	}
	else
	{
		ar << ClassID;
	}

	ID.Serialize( ar );
	Hash.Serialize( ar );

	return true;
}

DBCMD_INLINE int CFPS_Download_Req::buf_size( )
{
	return INT_MAX ;
}

DBCMD_INLINE SG_BOOL CFPS_Download_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;

	return Content.Serialize( ar );
}

DBCMD_INLINE int CFPS_Download_Res::buf_size( )
{
	return CNetCmdHead::buf_size( ) + Content.GetLength( ) ;
}

//=====================================================================================================
DBCMD_INLINE SG_BOOL CFPS_Publish_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;

	if(ar.IsLoading())
	{
		ar >> ClassID;
	}
	else
	{
		ar << ClassID;
	}

	ID.Serialize( ar );
	Hash.Serialize( ar );

	return Content.Serialize( ar );
}

DBCMD_INLINE int CFPS_Publish_Req::buf_size( )
{
	return INT_MAX ;
}

//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CREP_GetLogicCellVer_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CREP_GetLogicCellVer_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> SrvType;
	}
	else
	{
		ar << SrvType;
	}
	LogicCell.Serialize(ar);
	return true;
}
//=====================================================================================================
DBCMD_INLINE int CREP_GetLogicCellVer_Res::buf_size()
{
	return	INT_MAX;

}

DBCMD_INLINE SG_BOOL CREP_GetLogicCellVer_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	SG_INT	Cnt,i;
	S_TWOINT	LogicVer;
	if(ar.IsLoading())
	{
		LogicCellVer.clear();
		ar >> Cnt;
		for(i=0;i<Cnt;i++)
		{
			LogicVer.Serialize(ar);
			LogicCellVer.push_back(LogicVer);
		}
	}
	else
	{
		Cnt=LogicCellVer.size();
		ar << Cnt;
		for(i=0;i<Cnt;i++)
			LogicCellVer[i].Serialize(ar);
	}
	return true;
}
//=====================================================================================================
//=====================================================================================================
DBCMD_INLINE int CREP_GetLogicCellDat_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CREP_GetLogicCellDat_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> SrvType;
		ar >> NodeID;
		ar >> StartVer;
		ar >> EndVer;
	}
	else
	{
		ar << SrvType;
		ar << NodeID;
		ar << StartVer;
		ar << EndVer;
	}
	LogicCell.Serialize(ar);
	return true;
}
//=====================================================================================================
DBCMD_INLINE int CREP_GetLogicCellDat_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CREP_GetLogicCellDat_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
			return false;
	if(ar.IsLoading())
	{
		ar >> StartVer;
		ar >> EndVer;
	}
	else
	{
		ar << StartVer;
		ar << EndVer;
	}
	
	DatArray.Serialize(ar);
	return true;
}

DBCMD_INLINE SG_BOOL CMSGCmd_Post_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	msg.serialize(ar);
	return true;
}


//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CCPS_QueryRealEvtWritePt_Res::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(WritePt);

}

DBCMD_INLINE SG_BOOL CCPS_QueryRealEvtWritePt_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> WritePt;
//		ar >>WriteCircuitCnt;
	}
	else
	{
		ar << WritePt;
//		ar << WriteCircuitCnt;
	}
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CCPS_QueryRealEvt_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(StartReadPt)+sizeof(MaxRowNum)+sizeof(ConfirmFlag);

}

DBCMD_INLINE SG_BOOL CCPS_QueryRealEvt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
//		ar >> StartCircuitCnt;
		ar >> StartReadPt;
		ar >> MaxRowNum;
		if(VerNo>=SG_NET_VERSION_52)
			ar >> ConfirmFlag;
	}
	else
	{
//		ar << StartCircuitCnt;
		ar << StartReadPt;
		ar << MaxRowNum;
		if (VerNo>=SG_NET_VERSION_52)
			ar << ConfirmFlag;
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CCPS_QueryRealEvt_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CCPS_QueryRealEvt_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
//		ar >> LastReadCircuitCnt;
		ar >> LastReadPt;
//		ar >> WriteCircuitCnt;
		ar >> WritePt;
	}
	else
	{
//		ar << LastReadCircuitCnt;
		ar << LastReadPt;
//		ar << WriteCircuitCnt;
		ar << WritePt;
	}
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CCPS_ConfirmRealEvt_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(EvtID)+sizeof(EvtYMD)+sizeof(EvtHMS);

}

DBCMD_INLINE SG_BOOL CCPS_ConfirmRealEvt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if (ar.IsLoading())
	{
		ar >> EvtID;
		ar >> EvtYMD;
		ar >> EvtHMS;
	} else
	{
		ar << EvtID;
		ar << EvtYMD;
		ar << EvtHMS;
	}
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CIDMAPCmd_Self2Other_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(ClassType)+SelfObjs.buf_size();

}

DBCMD_INLINE SG_BOOL CIDMAPCmd_Self2Other_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> ClassType;
	}
	else
	{
		ar << ClassType;
	}
	SelfObjs.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CIDMAPCmd_Self2Other_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CIDMAPCmd_Self2Other_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CIDMAPCmd_Other2Self_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CIDMAPCmd_Other2Self_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT Cnt,i;
	CSgString sgstr;
	string mapstr;
	if(ar.IsLoading())
	{
		ar >> ClassType;
		ar >> Cnt;
		for(i=0;i<Cnt;i++)
		{
			sgstr.Serialize(ar);
			mapstr=sgstr.GetSafeBuffer();
			OtherObjs.push_back(mapstr);
		}
	}
	else
	{
		ar << ClassType;
		Cnt=OtherObjs.size();
		ar << Cnt;
		for(i=0;i<Cnt;i++)
		{
			sgstr=OtherObjs[i].data();
			sgstr.Serialize(ar);
		}
	}

	return true;
}
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CIDMAPCmd_Other2Self_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CIDMAPCmd_Other2Self_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_Login_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(NodeID);

}

DBCMD_INLINE SG_BOOL CDataSrv_Login_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>NodeID;
	}
	else
	{
		ar<<NodeID;

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_Operator_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(Operation)+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(Value);

}

DBCMD_INLINE SG_BOOL CDataSrv_Operator_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>Operation;
		ar>>OperType;
		ar>>ObjType;
		ar>>ObjID;
		ar>>Value;
	}
	else
	{
		ar<<Operation;
		ar<<OperType;
		ar<<ObjType;
		ar<<ObjID;
		ar<<Value;

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_SetValue_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(Value);

}

DBCMD_INLINE SG_BOOL CDataSrv_SetValue_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>OperType;
		ar>>ObjType;
		ar>>ObjID;
		ar>>Value;
	}
	else
	{
		ar<<OperType;
		ar<<ObjType;
		ar<<ObjID;
		ar<<Value;

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_SendRawRtDat_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDataSrv_SendRawRtDat_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar>>ObjType;
	else
		ar<<ObjType;
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_SendHisDat_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDataSrv_SendHisDat_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>ObjType;
		ar>>TaskID;
	}
	else
	{
		ar<<ObjType;
		ar<<TaskID;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_SendFile_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDataSrv_SendFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>Res;
		ar>>TaskID;
	}
	else
	{
		ar<<Res;
		ar<<TaskID;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_SendRawEvt_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDataSrv_SendRawEvt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT Cnt=0;
	VECT_RAWEVENT *pSendList;
	if(pRawEvtList)
		pSendList=pRawEvtList;
	else
		pSendList=&RawEvtList;
	int i;
	if(ar.IsLoading())
	{
		ar>>Cnt;
		pSendList->clear();
		S_RAW_EVENT RawEvt;
		for(i=0;i<Cnt;i++)
		{
			if(RawEvt.Serialize(ar)==false)
				break;
			pSendList->push_back(RawEvt);
		}
	}
	else
	{
		Cnt=pSendList->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
			(*pSendList)[i].Serialize(ar);
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDataSrv_GetMiniBoxLinkNode_Res::buf_size()
{
	return CNetCmdHead::buf_size()+NodeIDList.buf_size();

}

DBCMD_INLINE SG_BOOL CDataSrv_GetMiniBoxLinkNode_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	NodeIDList.Serialize(ar);
	return true;
}

//=====================================================================================================
//                     前置服务接口
//==================================================================================================
DBCMD_INLINE int CCommSrv_Operator_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(Operation)+sizeof(OperType)+sizeof(ObjType)+sizeof(ObjID)+sizeof(Value);

}

DBCMD_INLINE SG_BOOL CCommSrv_Operator_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>Operation;
		ar>>OperType;
		ar>>ObjType;
		ar>>ObjID;
		ar>>Value;
	}
	else
	{
		ar<<Operation;
		ar<<OperType;
		ar<<ObjType;
		ar<<ObjID;
		ar<<Value;

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CCommSrv_WriteProtSetting_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CCommSrv_WriteProtSetting_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>OperType;
		ar>>RtuID;
		ar>>DevAddr;
		ar>>SettingArea;
	}
	else
	{
		ar<<OperType;
		ar<<RtuID;
		ar<<DevAddr;
		ar<<SettingArea;
	}
	if(pDatSet)
		pDatSet->Serialize(ar);
	else
		DatSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CCommSrv_ReadProtSetting_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(RtuID)+sizeof(DevAddr)+sizeof(SettingArea);

}

DBCMD_INLINE SG_BOOL CCommSrv_ReadProtSetting_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>RtuID;
		ar>>DevAddr;
		ar>>SettingArea;
	}
	else
	{
		ar<<RtuID;
		ar<<DevAddr;
		ar<<SettingArea;
	}
	return true;
}
//==================================================================================================
DBCMD_INLINE int CCommSrv_ReadProtSetting_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CCommSrv_ReadProtSetting_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(pRetDat)
		pRetDat->Serialize(ar);
	else
		RetDat.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CCommSrv_ReadHisDat_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CCommSrv_ReadHisDat_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT i,PtID,Cnt;
	if(ar.IsLoading())
	{
		ar>>StartYMD;
		ar>>EndYMD;
		ar>>ObjType;
		ar>>TaskID;
		ar>>Cnt;
		PtIDList.clear();
		for(i=0;i<Cnt;i++)
		{
			ar>>PtID;
			PtIDList.push_back(PtID);
		}
	}
	else
	{
		ar<<StartYMD;
		ar<<EndYMD;
		ar<<ObjType;
		ar<<TaskID;
		Cnt=PtIDList.size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
		{
			PtID=PtIDList[i];
			ar<<PtID;
		}
	}
	return true;
}

//=====================================================================================================
//                     进程控制服务接口
//==================================================================================================
DBCMD_INLINE int CPCM_StartProc_Req::buf_size()
{
	return CNetCmdHead::buf_size()+ProcName.buf_size()+StartPara.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_StartProc_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	ProcName.Serialize(ar);
	StartPara.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_EndProc_Req::buf_size()
{
	return CNetCmdHead::buf_size()+ProcName.buf_size()+EndPara.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_EndProc_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
/*	if(ar.IsLoading())
	{
		ar>>OnlyStopProcFlag;
	}
	else
	{
		ar<<OnlyStopProcFlag;
	}
*/	ProcName.Serialize(ar);
	EndPara.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_MiniBoxSendCmd_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_MiniBoxSendCmd_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>SendCmdType;
	}
	else
	{
		ar<<SendCmdType;
	}
	if(pLobDat)
		pLobDat->Serialize(ar);
	else
		LobDat.Serialize(ar);
	return true;
}


//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_AskStatus_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(SubType)+ProcName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_AskStatus_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>SubType;
	}
	else
	{
		ar<<SubType;
	}
	ProcName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_ProcStatus::buf_size()
{
	CSgString sgstr;
	sgstr=ProcName.data();
	return sizeof(ProcID)+sizeof(State)+sgstr.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_ProcStatus::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	CSgString sgstr;
	if(ar.IsLoading())
	{
		ar>>ProcID;
		ar>>State;
		sgstr.Serialize(ar);
		ProcName=sgstr.GetSafeBuffer();
	}
	else
	{
		ar<<ProcID;
		ar<<State;
		sgstr=ProcName.data();
		sgstr.Serialize(ar);
	}
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_AskStatus_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_AskStatus_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	CSgString sgstr;
	SG_INT Cnt,i;
	VECT_PROCINFO *pArray;
	if(pProcInfoArray)
		pArray=pProcInfoArray;
	else
		pArray=&ProcInfoArray;
	CPCM_ProcStatus ProcStatus;
	if(ar.IsLoading())
	{
		ar>>Cnt;
		pArray->clear();
		for(i=0;i<Cnt;i++)
		{
			ProcStatus.Serialize(ar,VerNo);
			pArray->push_back(ProcStatus);

		}
	}
	else
	{
		Cnt=pArray->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
		{
		//	ProcStatus=;
			(*pArray)[i].Serialize(ar,VerNo);
		}
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_StartCalcProc_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_StartCalcProc_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	CSgString sgstr;
	SG_INT Cnt, i;
	S_TWOSTRING TwoStr;

	if (ar.IsLoading())
	{
		ar >> CalcProcType;
		ar >> Cnt;
		ReplaceKeyList.clear();
		for (i = 0; i < Cnt; i++)
		{
			sgstr.Serialize(ar);
			TwoStr.Val1 = sgstr.GetSafeBuffer();
			sgstr.Serialize(ar);
			TwoStr.Val2 = sgstr.GetSafeBuffer();
			ReplaceKeyList.push_back(TwoStr);

		}
	}
	else
	{
		ar << CalcProcType;
		Cnt = ReplaceKeyList.size();
		ar << Cnt;
		for (i = 0; i < Cnt; i++)
		{
			sgstr = ReplaceKeyList[i].Val1.data();
			sgstr.Serialize(ar);
			sgstr = ReplaceKeyList[i].Val2.data();
			sgstr.Serialize(ar);
		}
	}
	return true;
}
//=====================================================================================================
DBCMD_INLINE int CPCM_StartCalcProc_Res::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(ProcID);

}

DBCMD_INLINE SG_BOOL CPCM_StartCalcProc_Res::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ProcID;
	}
	else
	{
		ar << ProcID;
	}
	return true;
}

//=====================================================================================================
DBCMD_INLINE int CPCM_AskCalcProcState_Req::buf_size()
{
	return CNetCmdHead::buf_size() + sizeof(ProcID);

}

DBCMD_INLINE SG_BOOL CPCM_AskCalcProcState_Req::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	if (ar.IsLoading())
	{
		ar >> ProcID;
	}
	else
	{
		ar << ProcID;
	}
	return true;
}
//=====================================================================================================
DBCMD_INLINE int CPCM_AskCalcProcState_Res::buf_size()
{
	return CNetCmdHead::buf_size() + ProcStatus.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_AskCalcProcState_Res::Serialize(CSgArchive &ar, SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar, VerNo) == false)
		return false;
	return ProcStatus.Serialize(ar, VerNo);
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_PathFileInfo_Req::buf_size()
{
	return CNetCmdHead::buf_size()+PathName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_PathFileInfo_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	PathName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_SysEnvPath_Res::buf_size()
{
	return CNetCmdHead::buf_size()+PathName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_SysEnvPath_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	PathName.Serialize(ar);
	return true;
}

//=====================================================================================================
//==================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_FileInfo::buf_size()
{
	CSgString sgstr;
	sgstr=FileName.data();
	return sizeof(IsPathFlag)+sizeof(FileSize)+sizeof(UpdateTime)+sgstr.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_FileInfo::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	CSgString sgstr;
	if(ar.IsLoading())
	{
		ar>>IsPathFlag;
		ar>>FileSize;
		ar>>UpdateTime;
		sgstr.Serialize(ar);
		FileName=sgstr.GetSafeBuffer();
	}
	else
	{
		ar<<IsPathFlag;
		ar<<FileSize;
		ar<<UpdateTime;
		sgstr=FileName.data();
		sgstr.Serialize(ar);
	}
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_PathFileInfo_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_PathFileInfo_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	PathName.Serialize(ar);
	CSgString sgstr;
	SG_INT Cnt,i;
	VECT_PCM_FILEINFO *pArray;
	if(pFileInfoArray)
		pArray=pFileInfoArray;
	else
		pArray=&FileInfoArray;

	CPCM_FileInfo FileInfo;
	if(ar.IsLoading())
	{
		ar>>Cnt;
		pArray->clear();
		for(i=0;i<Cnt;i++)
		{
			FileInfo.Serialize(ar,VerNo);
			pArray->push_back(FileInfo);

		}
	}
	else
	{
		Cnt=pArray->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
		{
			//	ProcStatus=;
			(*pArray)[i].Serialize(ar,VerNo);
		}
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_FileOper_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(OperType)+FileName.buf_size()+NewFileName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_FileOper_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>OperType;
	}
	else
	{
		ar<<OperType;
	}
	FileName.Serialize(ar);
	NewFileName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_DownLoadFile_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(TransNo)+sizeof(FileStartPos)+sizeof(SendMaxSize)+FileName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_DownLoadFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>TransNo;
		ar>>FileStartPos;
		ar>>SendMaxSize;
	}
	else
	{
		ar<<TransNo;
		ar<<FileStartPos;
		ar<<SendMaxSize;
	}
	FileName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_FileLoadInfo::buf_size()
{
	return sizeof(FileSize)+sizeof(UpdateTime)+sizeof(TransNo)+sizeof(FileStartPos)+sizeof(SendSize);

}

DBCMD_INLINE SG_BOOL CPCM_FileLoadInfo::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(ar.IsLoading())
	{
		ar>>FileSize;
		ar>>UpdateTime;
		ar>>TransNo;
		ar>>FileStartPos;
		ar>>SendSize;
	}
	else
	{
		ar<<FileSize;
		ar<<UpdateTime;
		ar<<TransNo;
		ar<<FileStartPos;
		ar<<SendSize;
	}
	return true;
}
//=====================================================================================================
//==================================================================================================

DBCMD_INLINE int CPCM_DownLoadFile_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_DownLoadFile_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	FileName.Serialize(ar);
	CPCM_AutoReallocMem *pBuf;
	if(pSendBuf)
		pBuf=pSendBuf;
	else
		pBuf=&SendBuf;
	LoadInfo.Serialize(ar,VerNo);
	if(LoadInfo.SendSize>0)
	{
		if(ar.IsLoading())
		{
			pBuf->SetSize(LoadInfo.SendSize);
			ar.Read(pBuf->pBuff,LoadInfo.SendSize);
		}
		else
		{
			if(pBuf->pBuff==NULL||pBuf->BuffSize<LoadInfo.SendSize)
				return false;
			ar.Write(pBuf->pBuff,LoadInfo.SendSize);
		}

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_UpLoadFile_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_UpLoadFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	FileName.Serialize(ar);
	CPCM_AutoReallocMem *pBuf;
	if(pSendBuf)
		pBuf=pSendBuf;
	else
		pBuf=&SendBuf;
	LoadInfo.Serialize(ar,VerNo);
	if(LoadInfo.SendSize>0)
	{
		if(ar.IsLoading())
		{
			pBuf->SetSize(LoadInfo.SendSize);
			ar.Read(pBuf->pBuff,LoadInfo.SendSize);
		}
		else
		{
			if(pBuf->pBuff==NULL||pBuf->BuffSize<LoadInfo.SendSize)
				return false;
			ar.Write(pBuf->pBuff,LoadInfo.SendSize);
		}

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_UpLoadFile_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CPCM_UpLoadFile_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	FileName.Serialize(ar);
	if(ar.IsLoading())
	{
		ar>>TransNo;
		ar>>RecvOKFlag;
	}
	else
	{
		ar<<TransNo;
		ar<<RecvOKFlag;
	}
	SG_INT Cnt, i, TransNo;
	if (ar.IsLoading())
	{
		ExistTransNoList.clear();
		ar >> Cnt;
		for (i = 0; i < Cnt; i++)
		{
			ar >> TransNo;
			ExistTransNoList.push_back(TransNo);
		}
	}
	else
	{
		Cnt = ExistTransNoList.size();
		ar << Cnt;
		for (i = 0; i < Cnt; i++)
		{
			TransNo = ExistTransNoList[i];
			ar << TransNo;
		}

	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_ShellCmd_Req::buf_size()
{
	return CNetCmdHead::buf_size()+ExePath.buf_size()+ShellCmd.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_ShellCmd_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	ExePath.Serialize(ar);
	ShellCmd.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_ShellCmd_Res::buf_size()
{
	return CNetCmdHead::buf_size()+OutInfo.buf_size()+CurrentPath.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_ShellCmd_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	OutInfo.Serialize(ar);
	CurrentPath.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_GetFileInfo_Req::buf_size()
{
	return CNetCmdHead::buf_size()+FileName.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_GetFileInfo_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	FileName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================

DBCMD_INLINE int CPCM_GetFileInfo_Res::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(FileTime)+sizeof(FileSize)+sizeof(FileMD5);

}

DBCMD_INLINE SG_BOOL CPCM_GetFileInfo_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>FileTime;
		ar>>FileSize;
		ar.Read(FileMD5,sizeof(FileMD5));
	}
	else
	{
		ar<<FileTime;
		ar<<FileSize;
		ar.Write(FileMD5,sizeof(FileMD5));
	}
	return true;
}

//=====================================================================================================
//==================================================================================================

DBCMD_INLINE int CMiniBoxMan_SendStatus_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(memLoad)+sizeof(cpuLoad)+sizeof(availMem);

}

DBCMD_INLINE SG_BOOL CMiniBoxMan_SendStatus_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar>>memLoad;
		ar>>cpuLoad;
		ar>>availMem;
	}
	else
	{
		ar<<memLoad;
		ar<<cpuLoad;
		ar<<availMem;
	}
	return true;
}

//==================================================================================================

DBCMD_INLINE int CMiniBoxMan_SendDiskStatus_Req::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CMiniBoxMan_SendDiskStatus_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT Cnt,i;
	CSgString sgstr;
	S_SENDDISKSTATUS DiskStatus;
	VECT_DISKSTATUS *pProcDiskList=pDiskStatusList;
	if(pProcDiskList==NULL)
		pProcDiskList=&DiskStatusList;

	if(ar.IsLoading())
	{
		pProcDiskList->clear();
		ar>>Cnt;
		for(i=0;i<Cnt;i++)
		{
			sgstr.Serialize(ar);
			DiskStatus.DiskName=sgstr.GetSafeBuffer();
			ar >> DiskStatus.TotalSize;
			ar >> DiskStatus.FreeSize;
			pProcDiskList->push_back(DiskStatus);
		}
	}
	else
	{
		Cnt=pProcDiskList->size();
		ar<<Cnt;
		for(i=0;i<Cnt;i++)
		{
			sgstr=(*pProcDiskList)[i].DiskName.data();
			sgstr.Serialize(ar);
			ar << (*pProcDiskList)[i].TotalSize;
			ar << (*pProcDiskList)[i].FreeSize;
		}

	}
	return true;
}

//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_UpLoadFile_Req::buf_size()
{
	return CPCM_UpLoadFile_Req::buf_size()+DBName.buf_size()+ContentType.buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_UpLoadFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CPCM_UpLoadFile_Req::Serialize(ar,VerNo)==false)
		return false;
	DBName.Serialize(ar);
	ContentType.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_DownLoadFile_Req::buf_size()
{
	return CPCM_DownLoadFile_Req::buf_size()+DBName.buf_size()+ReqStr.buf_size()+sizeof(ReqType);

}

DBCMD_INLINE SG_BOOL CDBCmd_DownLoadFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CPCM_DownLoadFile_Req::Serialize(ar,VerNo)==false)
		return false;
	if (ar.IsLoading())
	{
		ar>>ReqType;
	} else
	{
		ar<<ReqType;
	}
	DBName.Serialize(ar);
	ReqStr.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_DownLoadFile_Res::buf_size()
{
	S_NoSqlFileInfo *pInfo=pFileInfo;
	if (pInfo==NULL)
		pInfo=&FileInfo;
	return CPCM_DownLoadFile_Res::buf_size()+ReqStr.buf_size()+pInfo->buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_DownLoadFile_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CPCM_DownLoadFile_Res::Serialize(ar,VerNo)==false)
		return false;
	S_NoSqlFileInfo *pInfo=pFileInfo;
	if (pInfo==NULL)
		pInfo=&FileInfo;
	ReqStr.Serialize(ar);
	pInfo->Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_RemoveFile_Req::buf_size()
{
	return CNetCmdHead::buf_size()+DBName.buf_size()+FileName.buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_RemoveFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	DBName.Serialize(ar);
	FileName.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_GetFileInfo_Res::buf_size()
{
	S_NoSqlFileInfo *pInfo=pFileInfo;
	if (pInfo==NULL)
		pInfo=&FileInfo;
	return CNetCmdHead::buf_size()+pInfo->buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_GetFileInfo_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	S_NoSqlFileInfo *pInfo=pFileInfo;
	if (pInfo==NULL)
		pInfo=&FileInfo;
	pInfo->Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_GetFileNameArray_Req::buf_size()
{
	return CNetCmdHead::buf_size()+DBName.buf_size()+ReqStr.buf_size();

}

DBCMD_INLINE SG_BOOL CDBCmd_GetFileNameArray_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	DBName.Serialize(ar);
	ReqStr.Serialize(ar);
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CDBCmd_GetFileNameArray_Res::buf_size()
{
	return INT_MAX;

}

DBCMD_INLINE SG_BOOL CDBCmd_GetFileNameArray_Res::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	CSgStringArray *pStrArray=pFileNameList;
	if(pStrArray==NULL)
		pStrArray=&FileNameList;
	SG_INT i,Cnt;
	CSgString  sgstr;
	if(ar.IsLoading())
	{
		pStrArray->RemoveAll();
		ar >> Cnt;
		for(i=0;i<Cnt;i++)
		{
			sgstr.Serialize(ar);
			char *pStr=sgstr.GetSafeBuffer();
			pStrArray->Add(pStr);
		}

	}
	else
	{
		Cnt=pStrArray->GetSize();
		ar << Cnt;
		for(i=0;i<Cnt;i++)	
		{
			sgstr=(char *)(*pStrArray)[i];
			sgstr.Serialize(ar);
		}
	}
	return true;
}
//=====================================================================================================
//==================================================================================================
DBCMD_INLINE int CPCM_RestartSrv_Req::buf_size()
{
	return CNetCmdHead::buf_size()+sizeof(StartFlag);

}

DBCMD_INLINE SG_BOOL CPCM_RestartSrv_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	if (ar.IsLoading())
	{
		ar>>StartFlag;
	} else
	{
		ar<<StartFlag;
	}
	return true;
}
//=====================================================================================================
DBCMD_INLINE int CEvtSrv_SendRawEvt_Req::buf_size()
{
	return	INT_MAX;

}

DBCMD_INLINE SG_BOOL CEvtSrv_SendRawEvt_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if(CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	SG_INT	Cnt,i;
	VECT_RAWEVENT	*pProcList;
	S_RAW_EVENT RawEvt;
	pProcList=pRawEvtList;
	if(pProcList==NULL)
		pProcList=&RawEvtList;
	if(ar.IsLoading())
	{
		pProcList->clear();
		ar >> Cnt;
		for(i=0;i<Cnt;i++)
		{
			RawEvt.Serialize(ar);
			pProcList->push_back(RawEvt);
		}
	}
	else
	{
		Cnt=pProcList->size();
		ar << Cnt;
		for(i=0;i<Cnt;i++)
			(*pProcList)[i].Serialize(ar);
	}
	return true;
}
//=====================================================================================================
//=====================================================================================================

//=====================================================================================================
//==================================================================================================
/*DBCMD_INLINE int CPCM_ExecSQLFile_Req::buf_size()
{
	return CNetCmdHead::buf_size()+DsName.buf_size()+SQLFile.buf_size()+LogFile.buf_size();

}

DBCMD_INLINE SG_BOOL CPCM_ExecSQLFile_Req::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	if (CNetCmdHead::Serialize(ar,VerNo)==false)
		return false;
	DsName.Serialize(ar);
	SQLFile.Serialize(ar);
	LogFile.Serialize(ar);
	return true;
}
*/