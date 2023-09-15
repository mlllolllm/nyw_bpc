#pragma once

#include "GGisCommand.h"

//==================================================================================================
#ifndef __GIS_INCLUDE_CPP__
#	define GIS_INLINE inline 
#else
#	define GIS_INLINE
#endif

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BASEINFO::buf_size()
{
	return SchemeInfo.buf_size() + ObjTypes.buf_size()+sizeof(WholeContain)+sizeof(SearchAll)
		+sizeof(Tolerance)+sizeof(WorldScale)+sizeof(MaxSelObjNum);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BASEINFO::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(ar.IsLoading())
	{
		ar >> WholeContain;
		ar >> SearchAll;
		ar >> Tolerance;
		ar >> WorldScale;
		ar >> MaxSelObjNum;
	}
	else
	{
		ar << WholeContain;
		ar << SearchAll;
		ar << Tolerance;
		ar << WorldScale;
		ar << MaxSelObjNum;

	}
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOADMODEL_OBJTYPE_REQ::buf_size()
{
	return CNetCommand::buf_size();
}

GIS_INLINE SG_BOOL GIS_LOADMODEL_OBJTYPE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	return CNetCommand::Serialize(ar,VerNo);
}
//....................................................................................................
GIS_INLINE int GIS_LOADMODEL_OBJTYPE_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOADMODEL_OBJTYPE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	ObjTypes.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOADMODEL_OBJFIELD_REQ::buf_size()
{
	return sizeof(ObjType)+CNetCommand::buf_size();
}

GIS_INLINE SG_BOOL GIS_LOADMODEL_OBJFIELD_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar >> ObjType;
	else
		ar << ObjType;
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LOADMODEL_OBJFIELD_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOADMODEL_OBJFIELD_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	ObjFields.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYPOINT_REQ::buf_size()
{
	return CNetCommand::buf_size()+ReqBaseInfo.buf_size()+sizeof(CenterPoint);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYPOINT_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ReqBaseInfo.Serialize(ar,VerNo)==false)
		return false;
	CenterPoint.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYRECT_REQ::buf_size()
{
	return CNetCommand::buf_size()+ReqBaseInfo.buf_size()+sizeof(SelRect);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYRECT_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ReqBaseInfo.Serialize(ar,VerNo)==false)
		return false;
	SelRect.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYCIRCLE_REQ::buf_size()
{
	return CNetCommand::buf_size()+ReqBaseInfo.buf_size()+sizeof(CenterPoint)
		+sizeof(Circle_R);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYCIRCLE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ReqBaseInfo.Serialize(ar,VerNo)==false)
		return false;
	CenterPoint.Serialize(ar);
	if(ar.IsLoading())
		ar >> Circle_R;
	else
		ar << Circle_R;
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYPOLYGON_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYPOLYGON_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	if(ReqBaseInfo.Serialize(ar,VerNo)==false)
		return false;
	Range.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYFATHER_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+
		ObjTypes.buf_size()+sizeof(FatherObj);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYFATHER_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> FatherObj.ObjType;
		ar >> FatherObj.ObjID;
	}
	else
	{
		ar << FatherObj.ObjType;
		ar << FatherObj.ObjID;
	}
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYCHILD_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+
		ObjTypes.buf_size()+ChildObj.buf_size();
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYCHILD_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	ChildObj.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_QUERYPSR_BYCHILD_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYCHILD_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}


//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYDEPARTMENT_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+
		ObjTypes.buf_size()+sizeof(Department);
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYDEPARTMENT_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	if(ar.IsLoading())
		ar >> Department;
	else
		ar << Department;
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_RES::buf_size()
{
	return CNetResponse::buf_size()+SelObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SelObject.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYPSR_BYPYBLUR_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+ObjTypes.buf_size()
		+ObjAttrib.buf_size()+KeyWord.buf_size();
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYPYBLUR_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	ObjAttrib.Serialize(ar);
	KeyWord.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_QUERYPSR_BYPYBLUR_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_QUERYPSR_BYPYBLUR_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOAD_BYIDARRAY_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(ObjType)
		+sizeof(HasTransDat)+sizeof(RtnGeometry)+ObjAttribs.buf_size()+ObjIDs.buf_size();
}

GIS_INLINE SG_BOOL GIS_LOAD_BYIDARRAY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjAttribs.Serialize(ar);
	ObjIDs.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ObjType;
		ar >> HasTransDat;
		ar >> RtnGeometry;
	}
	else
	{
		ar << ObjType;
		ar << HasTransDat;
		ar << RtnGeometry;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LOAD_BYIDARRAY_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOAD_BYIDARRAY_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDataSets.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOADDISP_BYIDARRAY_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(ObjType)
		+ObjAttribs.buf_size()+ObjIDs.buf_size();
}

GIS_INLINE SG_BOOL GIS_LOADDISP_BYIDARRAY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjAttribs.Serialize(ar);
	ObjIDs.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ObjType;
	}
	else
	{
		ar << ObjType;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LOADDISP_BYIDARRAY_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOADDISP_BYIDARRAY_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOAD_BYSQL_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(ObjType)
		+sizeof(RtnGeometry)+sizeof(HasTransDat)+ObjAttribs.buf_size()
		+WhereClause.buf_size();
}

GIS_INLINE SG_BOOL GIS_LOAD_BYSQL_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjAttribs.Serialize(ar);
	WhereClause.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ObjType;
		ar >> HasTransDat;
		ar >> RtnGeometry;
	}
	else
	{
		ar << ObjType;
		ar << HasTransDat;
		ar << RtnGeometry;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LOAD_BYSQL_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOAD_BYSQL_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDataSets.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LOADDISP_BYSQL_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(ObjType)
		+ObjAttribs.buf_size()+WhereClause.buf_size();
}

GIS_INLINE SG_BOOL GIS_LOADDISP_BYSQL_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjAttribs.Serialize(ar);
	WhereClause.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ObjType;
	}
	else
	{
		ar << ObjType;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LOADDISP_BYSQL_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_LOADDISP_BYSQL_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_LINELENGTH_BYDEPARTMENT_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+ObjTypes.buf_size()
		+sizeof(Department);
}

GIS_INLINE SG_BOOL GIS_LINELENGTH_BYDEPARTMENT_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	if(ar.IsLoading())
		ar >> Department;
	else
		ar << Department;
	return true;
}
//....................................................................................
GIS_INLINE int GIS_LINELENGTH_BYDEPARTMENT_RES::buf_size()
{
	return CNetResponse::buf_size()+sizeof(TotalLength);
}

GIS_INLINE SG_BOOL GIS_LINELENGTH_BYDEPARTMENT_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar >> TotalLength;
	else
		ar << TotalLength;
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_QUERYRECT_BYIDARRAY_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+Objects.buf_size();
}

GIS_INLINE SG_BOOL GIS_QUERYRECT_BYIDARRAY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	Objects.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_QUERYRECT_BYIDARRAY_RES::buf_size()
{
	return CNetResponse::buf_size()+sizeof(EncloseRect);
}

GIS_INLINE SG_BOOL GIS_QUERYRECT_BYIDARRAY_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	EncloseRect.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SHORTPATH_CABLE_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+ObjTypes.buf_size()
		+sizeof(CalMode)+sizeof(JudgePipeUse)+sizeof(UsePipeNum)+
		sizeof(StartObj)+sizeof(EndObj);
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_CABLE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	ObjTypes.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> CalMode;
		ar >> JudgePipeUse;
		ar >> UsePipeNum;
		ar >>StartObj.ObjType;
		ar >>StartObj.ObjID;
		ar >>EndObj.ObjType;
		ar >>EndObj.ObjID;
	}
	else
	{
		ar << CalMode;
		ar << JudgePipeUse;
		ar << UsePipeNum;
		ar <<StartObj.ObjType;
		ar <<StartObj.ObjID;
		ar <<EndObj.ObjType;
		ar <<EndObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SHORTPATH_CABLE_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_CABLE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SHORTPATH_ROAD_REQ::buf_size()
{
	return CNetCommand::buf_size()+ObjTypes.buf_size()+sizeof(StartPos)+sizeof(EndPos);
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_ROAD_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	ObjTypes.Serialize(ar);
	StartPos.Serialize(ar);
	EndPos.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SHORTPATH_ROAD_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_ROAD_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_CONNECTIVITY_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_CONNECTIVITY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConsiderKGStatus;
		ar >> SearchInStation;
		ar >> Obj1.ObjType;
		ar >> Obj1.ObjID;
		ar >> Obj2.ObjType;
		ar >> Obj2.ObjID;
	}
	else
	{
		ar << ConsiderKGStatus;
		ar << SearchInStation;
		ar << Obj1.ObjType;
		ar << Obj1.ObjID;
		ar << Obj2.ObjType;
		ar << Obj2.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_CONNECTIVITY_RES::buf_size()
{
	return CNetResponse::buf_size()+sizeof(ConnectFlag)+SelObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_CONNECTIVITY_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SelObject.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConnectFlag;
	}
	else
	{
		ar << ConnectFlag;
	}
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SUPPLYRANGE_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRANGE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	StopObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConsiderKGStatus;
		ar >> SearchInStation;
		ar >> StartObj.ObjType;
		ar >> StartObj.ObjID;
	}
	else
	{
		ar << ConsiderKGStatus;
		ar << SearchInStation;
		ar << StartObj.ObjType;
		ar << StartObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SUPPLYRANGE_RES::buf_size()
{
	return CNetResponse::buf_size()+SelObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRANGE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SelObject.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SUPPLYRADIUS_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRADIUS_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConsiderKGStatus;
		ar >> RuleType;
		ar >> StartObj.ObjType;
		ar >> StartObj.ObjID;
	}
	else
	{
		ar << ConsiderKGStatus;
		ar << RuleType;
		ar << StartObj.ObjType;
		ar << StartObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SUPPLYRADIUS_RES::buf_size()
{
	return CNetResponse::buf_size()+sizeof(PowerSupplyRadius)+SelObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRADIUS_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SelObject.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> PowerSupplyRadius;
	}
	else
	{
		ar << PowerSupplyRadius;
	}
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_POWERSOURCE_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_POWERSOURCE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	StopObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConsiderKGStatus;
		ar >> SearchInStation;
		ar >> StartObj.ObjType;
		ar >> StartObj.ObjID;
	}
	else
	{
		ar << ConsiderKGStatus;
		ar << SearchInStation;
		ar << StartObj.ObjType;
		ar << StartObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_POWERSOURCE_RES::buf_size()
{
	return CNetResponse::buf_size()+sizeof(PowerSourceObj)+SelObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_POWERSOURCE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	SelObject.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> PowerSourceObj.ObjType;
		ar >> PowerSourceObj.ObjID;
	}
	else
	{
		ar << PowerSourceObj.ObjType;
		ar << PowerSourceObj.ObjID;
	}
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_OUTAGERANGE_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_OUTAGERANGE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	StopObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	UserKGStatus.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_OUTAGERANGE_RES::buf_size()
{
	return CNetResponse::buf_size()+OnPowerObject.buf_size()+OffPowerObject.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_OUTAGERANGE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	OnPowerObject.Serialize(ar);
	OffPowerObject.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_CABLELINECORRIDOR_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(CableObj);
}

GIS_INLINE SG_BOOL GIS_CABLELINECORRIDOR_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> CableObj.ObjType;
		ar >> CableObj.ObjID;
	}
	else
	{
		ar << CableObj.ObjType;
		ar << CableObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_CABLELINECORRIDOR_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_CABLELINECORRIDOR_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SHORTPATH_ROAD_NEW_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_ROAD_NEW_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	StartPos.Serialize(ar);
	EndPos.Serialize(ar);
	AvoidPos.Serialize(ar);
	PathPos.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SHORTPATH_ROAD_NEW_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SHORTPATH_ROAD_NEW_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_CONNECTIVITY_NEW_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_CONNECTIVITY_NEW_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	StopObjs.Serialize(ar);
	StopObjTypes.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> AnalyseType;
		ar >> ConsiderKGStatus;
		ar >> OverVoltLevel;
		ar >> Obj1.ObjType;
		ar >> Obj1.ObjID;
		ar >> Obj2.ObjType;
		ar >> Obj2.ObjID;
	}
	else
	{
		ar << AnalyseType;
		ar << ConsiderKGStatus;
		ar << OverVoltLevel;
		ar << Obj1.ObjType;
		ar << Obj1.ObjID;
		ar << Obj2.ObjType;
		ar << Obj2.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_CONNECTIVITY_NEW_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_CONNECTIVITY_NEW_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> ConnectFlag;
	}
	else
	{
		ar << ConnectFlag;
	}
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_MULTICONNECTIVITY_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_MULTICONNECTIVITY_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	StopObjs.Serialize(ar);
	StopObjTypes.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> AnalyseType;
		ar >> ConsiderKGStatus;
		ar >> OverVoltLevel;		
	}
	else
	{
		ar << AnalyseType;
		ar << ConsiderKGStatus;
		ar << OverVoltLevel;		
	}
	Objs.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SUPPLYRANGE_NEW_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRANGE_NEW_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	StopObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> StartObj.ObjType;
		ar >> StartObj.ObjID;
	}
	else
	{
		ar << StartObj.ObjType;
		ar << StartObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SUPPLYRANGE_NEW_RES::buf_size()
{
	return CNetResponse::buf_size()+RtnObjects.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRANGE_NEW_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnObjects.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SUPPLYRADIUS_NEW_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRADIUS_NEW_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	UserKGStatus.Serialize(ar);
	PowerObjs.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> OverKGStation;
	}
	else
	{
		ar >> OverKGStation;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SUPPLYRADIUS_NEW_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYRADIUS_NEW_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}
//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_POWERSOURCE_NEW_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_POWERSOURCE_NEW_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	VoltLevels.Serialize(ar);
	StopObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	TermObjs.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_POWERSOURCE_NEW_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_POWERSOURCE_NEW_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_SUPPLYPATH_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYPATH_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	RtnObjTypes.Serialize(ar);
	UserKGStatus.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> PowerObj.ObjType;
		ar >> PowerObj.ObjID;
		ar >> TermObj.ObjType;
		ar >> TermObj.ObjID;
	}
	else
	{
		ar << PowerObj.ObjType;
		ar << PowerObj.ObjID;
		ar << TermObj.ObjType;
		ar << TermObj.ObjID;
	}
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_SUPPLYPATH_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SUPPLYPATH_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_GDD_POWERSOURCE_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_GDD_POWERSOURCE_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	UserKGStatus.Serialize(ar);
	GDDObjs.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_GDD_POWERSOURCE_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_GDD_POWERSOURCE_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//==================================================================================================
//==================================================================================================
GIS_INLINE int GIS_TOPO_GETCTRLATTRIB_REQ::buf_size()
{
	return CNetCommand::buf_size()+SchemeInfo.buf_size()+sizeof(ObjType)
		+Where.buf_size();
}

GIS_INLINE SG_BOOL GIS_TOPO_GETCTRLATTRIB_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;
	SchemeInfo.Serialize(ar);
	if(ar.IsLoading())
		ar >> ObjType;
	else
		ar << ObjType;
	Where.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_GETCTRLATTRIB_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_GETCTRLATTRIB_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	RtnDatSet.Serialize(ar);
	return true;
}

//=====================================================================================================
//=====================================================================================================

GIS_INLINE int GIS_TOPO_TRANSPATH_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_TRANSPATH_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;	
	ObjDevStatus.Serialize(ar);
	return true;
}
//....................................................................................
GIS_INLINE int GIS_TOPO_TRANSPATH_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_TRANSPATH_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;
	if(ar.IsLoading())
		ar >> LineNo;
	else
		ar << LineNo;
	PathLine.Serialize(ar);
	RtnDatSet.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================

GIS_INLINE int GIS_TOPO_SEARCHPOWER_YKBZ_REQ::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SEARCHPOWER_YKBZ_REQ::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetCommand::Serialize(ar,VerNo)==false)
		return false;	
	SchemeInfo.Serialize(ar,VerNo);
	CenterPoint.Serialize(ar);
	GDDObjTypes.Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> Circle_R;
		ar >> VoltLevel;
	}
	else
	{
		ar << Circle_R;
		ar << VoltLevel;
	}

	return true;
}

GIS_INLINE int GIS_TOPO_SEARCHPOWER_YKBZ_RES::buf_size()
{
	return INT_MAX;
}

GIS_INLINE SG_BOOL GIS_TOPO_SEARCHPOWER_YKBZ_RES::Serialize(CSgArchive &ar,SG_INT VerNo)
{
	SG_NET_GETVERSION(VerNo);
	if(CNetResponse::Serialize(ar,VerNo)==false)
		return false;	
	PathObjDatSetArray.Serialize(ar);
	PathCoordinate.Serialize(ar);
	return true;
}
//=====================================================================================================
//=====================================================================================================

