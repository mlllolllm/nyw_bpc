
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

#define SG_HISTBL_CRTTYPE_MON		1		//���½���
#define SG_HISTBL_CRTTYPE_YEAR		2		//���꽨��
#define SG_HISTBL_CRTTYPE_ALL		3		//��һ�ű�

#define SG_HISTBL_TBLCLASS_REAL		1		//ʵʱ��
#define SG_HISTBL_TBLCLASS_DAY		2		//��ͳ�Ʊ�
#define SG_HISTBL_TBLCLASS_MON		3		//��ͳ�Ʊ�
#define SG_HISTBL_TBLCLASS_YEAR		4		//��ͳ�Ʊ�
#define SG_HISTBL_TBLCLASS_MAN		5		//�ֳ�ͳ�Ʊ�
typedef struct SHDB_TBLDEFINFO
{
	SG_INT		HisTblID;			//��ʷ��ID
	string		HisTblName;		//����		��ʵ�ı���Ϊ TBLNAMEyyyymm_xxxx_yyyy      xxxx:WorkSpace   yyyy:sectionID
	string		RtTblName;		//�������ڵ�ʵʱ���
	string		CrtTblFile;		//�������õĽű��ļ�
	string		RtKeyField;		//ʵʱ������������
	string		RtWSField;		//ʵʱ����WorkSpace����
	SG_INT		LogicCellType;	//�߼����ݵ�Ԫ������
	SG_INT		DataType;		//��ʷ��������
	SG_INT		ObjType;			//�洢�Ķ�������   ���Ϊ0����Ͷ����޹�
	SG_SHORT	RtTblNo;		//ʵʱ����No��
	SG_SHORT	TblClass;			//������  1:ʵʱ��  2:��ͳ�Ʊ� 3:��ͳ�Ʊ�   4:��ͳ�Ʊ�  5:�ƻ����ݱ�
	SG_SHORT	CrtTblType;		//��������	1:���½��� 2:���꽨��  3:��һ�ű�
	SG_UCHAR	UseWorkSpaceFlag; //�����Ƿ�ʹ��WorkSpace  1:ʹ��   2:��ʹ��
	SG_UCHAR	InsertMode;		//����ģʽ 0:���Ȳ��������룬���ɹ���ɾ����¼�󣬲��� 1:ɾ����¼�󣬲��� 2:������ɾ����,���������� 4:��ԭ�м�¼�����󣬽�PROCSTATUS����洢
	SG_INT		IDSection;		//����ID�ֶεĴ�С		 0:��ʹ��ID�ֶ�
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
//ʵʱ��Ӧ�û���������
class CRDP_RtTblBaseProc
{
	CSG_OS_ThreadVar		m_DatLock;
	MAP_STRING_VOIDPT		m_TblCode2RtTbl;		//������ת����ʵʱ���
	MAP_INT_STRING			m_ObjType2MapRtTblName;	//���豸����ת����ӳ��ʵʱ�����
	MAP_INT_STRING			m_ObjType2RtTblName;	//���豸����ת����ʵʱ�����
	MAP_INT_STRING			m_ObjType2DevPtRtTblName;	//���豸����ת�����豸�����Ϣ����
	MAP_STRING_INT			m_RtTblName2ObjType;	//��ʵʱ�����ת�����豸����
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
//��ʷ��Ϣ�洢������
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
	MAP_INT_INT				m_ObjType2MetaType;		//�豸����ת����Ԫ������
	MAP_INT_INT				m_MetaType2ObjType;		//�豸����ת����Ԫ������
	MAP_INT_INT				m_Flag2StatTypeList;	//ͳ�ƶ�����ʷ�����͵�ת��
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