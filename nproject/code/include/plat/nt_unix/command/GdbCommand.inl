#pragma once

#include "GdbCommand.h"

//==================================================================================================
#ifndef __GIS_INCLUDE_CPP__
#	define GIS_INLINE inline 
#else
#	define GIS_INLINE
#endif

//==================================================================================================
GIS_INLINE int GIS_LOAD_BASIC_REQ::buf_size()
{
	return BUF_BASE( CNetCommand ) + OBJ_SIZE( Common ) + OBJ_SIZE( Schema );
}

GIS_INLINE SG_BOOL GIS_LOAD_BASIC_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;

	SERIALIZE_OBJECT( ar , Common		);
	SERIALIZE_OBJECT( ar , Schema		);
	return true;
}

GIS_INLINE int GIS_LOAD_BASIC_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOAD_BASIC_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
		SG_NET_GETVERSION(VerNo)

	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_OBJECT( ar , Common		);
	SERIALIZE_OBJECT( ar , dsAttrib		);
	SERIALIZE_OBJECT( ar , dsTblInfo	);
	SERIALIZE_OBJECT( ar , dsAppends	);
	return true;
}

//==================================================================================================
GIS_INLINE int GIS_LOAD_LAYER_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_REQ );
}

GIS_INLINE SG_BOOL GIS_LOAD_LAYER_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_REQ::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

GIS_INLINE int GIS_LOAD_LAYER_RES::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_RES );
}

GIS_INLINE SG_BOOL GIS_LOAD_LAYER_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(GIS_LOAD_BASIC_RES::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

//==================================================================================================
GIS_INLINE int GIS_LOAD_WORLD_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_REQ );
}

GIS_INLINE SG_BOOL GIS_LOAD_WORLD_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(GIS_LOAD_BASIC_REQ::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

GIS_INLINE int GIS_LOAD_WORLD_RES::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_RES );
}

GIS_INLINE SG_BOOL GIS_LOAD_WORLD_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(GIS_LOAD_BASIC_RES::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

//==================================================================================================
GIS_INLINE int GIS_LOAD_ARRAY_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_REQ ) + OBJ_SIZE( arrObjects );
}

GIS_INLINE SG_BOOL GIS_LOAD_ARRAY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_REQ::Serialize(ar,VerNo)==false)
		return false;

	SERIALIZE_OBJECT( ar , arrObjects			);
	return true;
}

GIS_INLINE int GIS_LOAD_ARRAY_RES::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_RES );
}

GIS_INLINE SG_BOOL GIS_LOAD_ARRAY_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_RES::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

//==================================================================================================
GIS_INLINE int GIS_LOAD_CELLS_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_REQ ) + OBJ_SIZE( arrCells );
}

GIS_INLINE SG_BOOL GIS_LOAD_CELLS_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_REQ::Serialize(ar,VerNo)==false)
		return false;

	SERIALIZE_OBJECT( ar , arrCells				);
	return true;
}

GIS_INLINE int GIS_LOAD_CELLS_RES::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_RES );
}

GIS_INLINE SG_BOOL GIS_LOAD_CELLS_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_RES::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

GIS_INLINE int GIS_LOAD_BYLINES_REQ::buf_size()
{
	return BUF_BASE( CNetCommand ) + OBJ_SIZE( SchemeInfo ) + OBJ_SIZE( ObjTypes )
			+ sizeof( RtnGeometry ) + OBJ_SIZE( ObjAttrib ) + Range.GetStructLen();
}

GIS_INLINE SG_BOOL GIS_LOAD_BYLINES_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_MEMBER( ar , RtnGeometry		);

	SERIALIZE_OBJECT( ar , SchemeInfo		);
	SERIALIZE_OBJECT( ar , ObjTypes			);
	SERIALIZE_OBJECT( ar , ObjAttrib		);
	SERIALIZE_OBJECT( ar , Range			);
	return true;
}
GIS_INLINE int GIS_LOAD_BYLINES_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOAD_BYLINES_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;

	RtnDataSets.Serialize(ar);
	return true;
}
GIS_INLINE int GIS_LOAD_MULTICOND_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BYLINES_REQ ) + OBJ_SIZE( WhereClause );
}

GIS_INLINE SG_BOOL GIS_LOAD_MULTICOND_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BYLINES_REQ::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_OBJECT( ar , WhereClause		);
	return true;
}

GIS_INLINE int GIS_LOAD_PYBLUR_REQ::buf_size()
{
	return BUF_BASE( CNetCommand ) + OBJ_SIZE( SchemeInfo ) + OBJ_SIZE( ObjTypes )
			+ sizeof( RtnGeometry ) + OBJ_SIZE( ObjAttrib ) + OBJ_SIZE( KeyWord );
}

GIS_INLINE SG_BOOL GIS_LOAD_PYBLUR_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{ 
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_MEMBER( ar , RtnGeometry		);

	SERIALIZE_OBJECT( ar , SchemeInfo		);
	SERIALIZE_OBJECT( ar , ObjTypes			);
	SERIALIZE_OBJECT( ar , ObjAttrib		);
	SERIALIZE_OBJECT( ar , KeyWord			);
	return true;
}

GIS_INLINE int GIS_LOAD_PYBLUR_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOAD_PYBLUR_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;

	RtnDataSets.Serialize(ar);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_LOAD_BY_APDOBJTYPE_REQ::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_REQ );
}

GIS_INLINE SG_BOOL GIS_LOAD_BY_APDOBJTYPE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_REQ::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

GIS_INLINE int GIS_LOAD_BY_APDOBJTYPE_RES::buf_size()
{
	return BUF_BASE( GIS_LOAD_BASIC_RES );
}

GIS_INLINE SG_BOOL GIS_LOAD_BY_APDOBJTYPE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(GIS_LOAD_BASIC_RES::Serialize(ar,VerNo)==false)
		return false;
	return true;
}

//==================================================================================================
GIS_INLINE int GIS_SCHEMES_TASKDIFF_REQ::buf_size()
{
	return BUF_BASE( CNetCommand ) +OBJ_SIZE(SchemeInfo1)+OBJ_SIZE(SchemeInfo2);
}

GIS_INLINE SG_BOOL GIS_SCHEMES_TASKDIFF_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_OBJECT( ar , SchemeInfo1);
	SERIALIZE_OBJECT( ar , SchemeInfo2);
	return true;
}

GIS_INLINE int GIS_SCHEMES_TASKDIFF_RES::buf_size()
{
	return BUF_BASE( CNetResponse ) +OBJ_SIZE(TaskList_Scheme1)+OBJ_SIZE(TaskList_Scheme2);
}

GIS_INLINE SG_BOOL GIS_SCHEMES_TASKDIFF_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SERIALIZE_OBJECT( ar , TaskList_Scheme1);
	SERIALIZE_OBJECT( ar , TaskList_Scheme2);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_LOADFDU_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(FDM_ID) + sizeof(WorldID)
		+ Base_FDUArray.buf_size()+Ver_FDUArray.buf_size();
}

GIS_INLINE SG_BOOL GIS_LOADFDU_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> FDM_ID;
		ar >> WorldID;
		ar >> HasScatterFDU;
	}
	else
	{
		ar << FDM_ID;
		ar << WorldID;
		ar << HasScatterFDU;
	}
	Base_FDUArray.Serialize(ar);
	Ver_FDUArray.Serialize(ar);
	SchemeInfo.Serialize(ar);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_ROLLBACK_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(RollBackType)+sizeof(RollBackID);
}

GIS_INLINE SG_BOOL GIS_ROLLBACK_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> RollBackType;
		ar >> RollBackID;
	}
	else
	{
		ar << RollBackType;
		ar << RollBackID;
	}
	SchemeInfo.Serialize(ar);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_ROLLBACK_RES::buf_size()
{
	return CNetResponse::buf_size();
}

GIS_INLINE SG_BOOL GIS_ROLLBACK_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	return CNetResponse::Serialize(ar,VerNo);
}

//==================================================================================================
GIS_INLINE int GIS_GET_RELDAT_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_GET_RELDAT_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RelDat.Serialize(ar);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_RELDAT_REPLACE_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_RELDAT_REPLACE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
	{
		ar >> RollBackType;
		ar >> RollBackID;
	}
	else
	{
		ar << RollBackType;
		ar << RollBackID;
	}
	SchemeInfo.Serialize(ar);
	RelDat.Serialize(ar);
	return true;
}
//==================================================================================================
GIS_INLINE int GIS_RELDAT_REPLACE_RES::buf_size()
{
	return CNetResponse::buf_size();
}

GIS_INLINE SG_BOOL GIS_RELDAT_REPLACE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	return CNetResponse::Serialize(ar,VerNo);
}
//==================================================================================================
GIS_INLINE int TSRV_CHG_OBJSTIME_REQ::buf_size()
{
	return sizeof(SrcYMD)+sizeof(DesYMD)+sizeof(ObjType)+sizeof(ObjKID);
}

GIS_INLINE SG_BOOL TSRV_CHG_OBJSTIME_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(ar.IsLoading())
	{
		ar >> SrcYMD;
		ar >> DesYMD;
		ar >> ObjType;
		ar >> ObjKID;
	}
	else
	{
		ar << SrcYMD;
		ar << DesYMD;
		ar << ObjType;
		ar << ObjKID;
	}
	return true;
}
//=====================================================================================================
GIS_INLINE int GIS_SCHEMES_DIFFOBJ_REQ::buf_size()
{
	return CNetCommand::buf_size()+ObjTypes.buf_size()+SchemeInfo1.buf_size()+SchemeInfo2.buf_size();
}

GIS_INLINE SG_BOOL GIS_SCHEMES_DIFFOBJ_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	ObjTypes.Serialize(ar);
	SchemeInfo1.Serialize(ar);
	SchemeInfo2.Serialize(ar);
	return true;
}
GIS_INLINE int GIS_SCHEMES_DIFFOBJ_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_SCHEMES_DIFFOBJ_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	DiffObjs.Serialize(ar);
	return true;
}

//=====================================================================================================
GIS_INLINE int GAP_GETSEQVALUE_REQ::buf_size()
{
	return CNetCommand::buf_size()+SeqName.buf_size()+sizeof(WorkSpace)+sizeof(Cnt);
}

GIS_INLINE SG_BOOL GAP_GETSEQVALUE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
		if(CNetCommand::Serialize(ar,VerNo)==false)
			return false;
	SeqName.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> WorkSpace;
		ar >> Cnt;
	}
	else
	{
		ar << WorkSpace;
		ar << Cnt;
	}
	return true;
}
GIS_INLINE int GAP_GETSEQVALUE_RES::buf_size()
{
	return CNetResponse::buf_size()+ObjIDS.buf_size();
}

GIS_INLINE SG_BOOL GAP_GETSEQVALUE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo)
		if(CNetResponse::Serialize(ar,VerNo)==false)
			return false;
	ObjIDS.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================
