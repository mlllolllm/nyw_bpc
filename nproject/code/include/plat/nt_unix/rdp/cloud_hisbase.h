
#ifndef _HH_RDP_HISBASE_HHH_
#define _HH_RDP_HISBASE_HHH_
#ifdef WIN32
#pragma   warning   (disable:   4083 4786)   
#include <map>
#include <vector>
//using   namespace   std;   
#else
#include <map>
#include <vector>
#endif
#include "rdpbasedef.h"
#include "rdbmem.h"
#include "dppclient.h"

#define SG_HISTBL_CRTTYPE_MON		1		//按月建表
#define SG_HISTBL_CRTTYPE_YEAR		2		//按年建表
#define SG_HISTBL_CRTTYPE_ALL		3		//仅一张表

#define SG_HISTBL_TBLCLASS_REAL		1		//实时表
#define SG_HISTBL_TBLCLASS_DAY		2		//日统计表
#define SG_HISTBL_TBLCLASS_MON		3		//月统计表
#define SG_HISTBL_TBLCLASS_YEAR		4		//年统计表
#define SG_HISTBL_TBLCLASS_MAN		5		//手抄统计表
typedef struct SHDB_TBLDEFINFO
{
	SG_INT		HisTblID;			//历史表ID
	string		HisTblName;		//表名		真实的表名为 TBLNAMEyyyymm_xxxx_yyyy      xxxx:WorkSpace   yyyy:sectionID
	string		RtTblName;		//对象所在的实时库表
	string		CrtTblFile;		//建表所用的脚本文件
	string		RtKeyField;		//实时库中主键域名
	string		RtWSField;		//实时库中WorkSpace域名
	SG_INT		LogicCellType;	//逻辑数据单元的类型
	SG_INT		DataType;		//历史数据类型
	SG_INT		ObjType;			//存储的对象类型   如果为0，则和对象无关
	SG_SHORT	RtTblNo;		//实时库表的No号
	SG_SHORT	TblClass;			//表类型  1:实时表  2:日统计表 3:月统计标   4:年统计表  5:计划数据表
	SG_SHORT	CrtTblType;		//建表类型	1:按月建表 2:按年建表  3:仅一张表
	SG_UCHAR	UseWorkSpaceFlag; //建表是否使用WorkSpace  1:使用   2:不使用
	SG_UCHAR	InsertMode;		//插入模式 0:首先采用批插入，不成功后删除记录后，插入 1:删除记录后，插入 2:按主键删除后,进行批插入 4:将原有纪录读出后，将PROCSTATUS相或后存储
	SG_INT		IDSection;		//建表ID分段的大小		 0:不使用ID分段
}SHDB_TBLDEFINFO;
typedef struct  S_CREATETBLINFO
{
	string		CrtTblFile;
	SG_INT		RtTblNo;
	SG_UCHAR	UseWorkSpaceFlag;
	SG_INT		IDSection;
}S_CREATETBLINFO;
typedef struct S_HTBLBASEINFO
{
	int		SrvNo;
	string	HTblName;
	int		StartYMD;
	int		EndYMD;
	int		TblClass;
}S_HTBLBASEINFO;
typedef std::vector<S_HTBLBASEINFO > VECT_HTBLBASEINFO;
typedef std::vector<S_CREATETBLINFO > VECT_CREATETBLINFO;
typedef std::vector<SHDB_TBLDEFINFO> VECT_HDBTBLINFO;
typedef struct  S_RDP_RTTBL_WORKSPACE
{
	SG_INT TblID;
	SG_INT WorkSpace;
	static int	Compare(const S_RDP_RTTBL_WORKSPACE &obj1,const S_RDP_RTTBL_WORKSPACE &obj2)
	{
		if(obj1.TblID<obj2.TblID)
			return -1;
		if(obj1.TblID==obj2.TblID)
		{
			if(obj1.WorkSpace<obj2.WorkSpace)
				return -1;
			else if(obj1.WorkSpace==obj2.WorkSpace)
				return 0;
		}
		return 1;
	};

}S_RDP_RTTBL_WORKSPACE;
struct CSRDPHisTblWorkSpaceLess:
	public std::binary_function<S_RDP_RTTBL_WORKSPACE, S_RDP_RTTBL_WORKSPACE, bool> {
		bool operator()(const S_RDP_RTTBL_WORKSPACE & obj1, const S_RDP_RTTBL_WORKSPACE & obj2) const
		{
			if(S_RDP_RTTBL_WORKSPACE::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
typedef struct  S_RDP_OBJTBLCLASS
{
	SG_SHORT ObjType;
	SG_SHORT TblClass;
	static int	Compare(const S_RDP_OBJTBLCLASS &obj1,const S_RDP_OBJTBLCLASS &obj2)
	{
		if(obj1.ObjType<obj2.ObjType)
			return -1;
		if(obj1.ObjType==obj2.ObjType)
		{
			if(obj1.TblClass<obj2.TblClass)
				return -1;
			else if(obj1.TblClass==obj2.TblClass)
				return 0;
		}
		return 1;
	};

}S_RDP_OBJTBLCLASS;
struct CSRDPObjTblClassLess:
	public std::binary_function<S_RDP_OBJTBLCLASS, S_RDP_OBJTBLCLASS, bool> {
		bool operator()(const S_RDP_OBJTBLCLASS & obj1, const S_RDP_OBJTBLCLASS & obj2) const
		{
			if(S_RDP_OBJTBLCLASS::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
typedef std::set<S_RDP_RTTBL_WORKSPACE,CSRDPHisTblWorkSpaceLess > SET_TBLWORKSPACE;
//实时库应用基本操作类
class CRDP_RtTblBaseProc
{
	CSG_OS_ThreadVar		m_DatLock;
	MAP_STRING_VOIDPT		m_TblCode2RtTbl;		//将表名转换成实时库表
	MAP_INT_STRING			m_ObjType2MapRtTblName;	//将设备对象转换成映射实时库表名
	MAP_INT_STRING			m_ObjType2RtTblName;	//将设备对象转换成实时库表名
	MAP_INT_STRING			m_ObjType2DevPtRtTblName;	//将设备对象转换成设备测点信息表名
	MAP_STRING_INT			m_RtTblName2ObjType;	//将实时库表名转换成设备对象
	SG_BOOL					m_InitFlag;
	int FreeObjType2RtTbl();
	int InitRtTblInfoList(CGAP_DppSrvClient_Real &DbfEngine);
	//int GetRtblWorkSpaceNotLock(int ObjType,int KeyID,int *pWorkSpace,CSgString *pTblCode=NULL);
	int GetMapRtblWorkSpace(std::string  &TblCode,int KeyID,int *pWorkSpace);
	int GetObjMeasInfo(int PtObjType,MAP_INT_STRING &TblNameList, VECT_RDBCOND &CondInfoList,MAP_DEVMEAS_TWOINT &PtList,int &ExistFlag);
public:
	CRDP_RtTblBaseProc();
	~CRDP_RtTblBaseProc();
	int Init(CGAP_DppSrvClient_Real &DbfEngine);
	int FInit();
	int GetObjMeasInfo(int PtObjType,int ObjType,int ObjID,int Terminal,int MeasType,MAP_DEVMEAS_TWOINT &PtList,CSgString *pTblCode=NULL);
	int GetRtblWorkSpace(int ObjType,int KeyID,int *pWorkSpace,CSgString *pTblCode=NULL);
	int GetRtblWorkSpace(CSgString &TblCode,int KeyID,int *pWorkSpace);
};
//历史信息存储功能类
//typedef std::multimap<string,SG_INT >   MULTMAP_STRING_INT;
class CTSDA_HisTblBaseProc
{
	typedef struct S_RDP_ID_RANGE
	{
		int Max_ID;
		int Min_ID;
		int RealMaxID;
	}S_RDP_ID_RANGE;
	typedef std::map<SG_INT,SHDB_TBLDEFINFO > MAP_INT_HDBTBLINFO;
	typedef std::map<S_RDP_RTTBL_WORKSPACE,S_RDP_ID_RANGE,CSRDPHisTblWorkSpaceLess > MAP_HISTBL_IDRANGE;
	typedef std::map<S_RDP_OBJTBLCLASS,SG_INT,CSRDPObjTblClassLess > MAP_TBLCLASS_INT;
	CRDP_RtTblBaseProc		m_RtTblBaseProc;
	CSG_OS_ThreadVar		m_DatLock;
	SG_INT					m_SrvType;
	SG_INT					m_CenterID;
	SG_UCHAR				m_IDSplitByWorkSpace;
	MAP_INT_HDBTBLINFO		m_HDBTblInfoList;
	MAP_HISTBL_IDRANGE		m_HisTblIDRangeList;
	MAP_INT_INT				m_ObjType2MetaType;		//设备对象转换成元方对象
	MAP_INT_INT				m_MetaType2ObjType;		//设备对象转换成元方对象
	MAP_INT_INT				m_Flag2StatTypeList;	//统计对象到历史表类型的转换
	SET_TBLWORKSPACE		m_TblWorkSpaceList;
	MULTMAP_STRING_INT		m_HTblName2HTblID;
	MAP_TBLCLASS_INT		m_HTblClass2HTblID;
	MULTMAP_INT_INT			m_HisDataType2HTblID;
private:
	int InitFlag2StatTypeList(CGAP_DppSrvClient_Real &DbfEngine);
	int InitHDBTblInfoList(CGAP_DppSrvClient_Real &DbfEngine);
	int InitHisTblIDRangeList(CGAP_DppSrvClient_Real &DbfEngine);
	int	InitObjType2MetaTypeList(CGAP_DppSrvClient_Real &DbfEngine);
	int	InitWorkSpaceList();
	int GetOneFileCrtSectionList(S_CREATETBLINFO &CrtTblInfo,S_RDP_RTTBL_WORKSPACE &RtTblWorkSpace,SET_TBLWORKSPACE &CrtSecitonList);
public:
	CTSDA_HisTblBaseProc();
	~CTSDA_HisTblBaseProc();
	int Init(CGAP_DppSrvClient_Real &DbfEngine);
	int FInit();
	int GetNeedCreateTblList(VECT_CREATETBLINFO &CrtTblList,SG_BOOL CrtAllFlag);
	int GetOneFileCrtSectionList(S_CREATETBLINFO &CrtTblInfo,SET_TBLWORKSPACE &CrtSecitonList);
	int GetOneFileCrtSectionList(S_RDP_OBJTBLCLASS &ObjTblClass,SET_TBLWORKSPACE &CrtSecitonList);
	int	GetHisTblInfo(CSgString &HisFileHead,VECT_HDBTBLINFO &HisTblInfo);
	int GetHisTblInfo(int CellType,VECT_HDBTBLINFO &HisTblInfo);
	int	GetHisTblInfoByTblName(CSgString &TblName,SHDB_TBLDEFINFO *pHisTblInfo);
	int GetHisTblName(SHDB_TBLDEFINFO &HisTblInfo,int YMD,int KeyID,int Flag,string &TblName,int *pWorkSpace,int *pSection);
	int GetHisTblName(SHDB_TBLDEFINFO &HisTblInfo,int YMD,int WorkSpace,string &TblName);
	int GetHisTblName(int ObjType,int StartYMD,int EndYMD,int KeyID,int Flag,VECT_HTBLBASEINFO &TblNameList,int WorkSpace,int *pTblClass);
	int GetHisTblName(int ObjType,int StartYMD,int EndYMD,int WorkSpace,VECT_HTBLBASEINFO &TblNameList);
	int GetHisTblNameByHisDataType(int HisDataType,int StartTime,int EndTime,int WorkSpace,int SectionID,VECT_HTBLBASEINFO &TblNameList);
	int GetHisTblName(SHDB_TBLDEFINFO &HisTblInfo,int StartYMD,int EndYMD,CSgString &TblTail,VECT_HTBLBASEINFO &TblNameList);
	int GetHisTblNameForCrtTbl(SHDB_TBLDEFINFO &HisTblInfo,int StartYMD,int EndYMD,CSgString &TblTail,VECT_HTBLBASEINFO &TblNameList);

	int GetHisTblHead(int ObjType,int Flag,string &TblHead);
	int GetObjTypeByMetaType(int MetaType);
	int GetMetaTypeByObjType(int ObjType);
	int GetObjMeasInfo(int PtObjType,int ObjType,int ObjID,int Terminal,int MeasType,MAP_DEVMEAS_TWOINT &PtList);
};

//extern SG_BOOL GetDevMeasInf(int pointtype,int devtype,int devid,int terminal,int meastype,MAP_DEVMEAS_INT &devlist);

#endif