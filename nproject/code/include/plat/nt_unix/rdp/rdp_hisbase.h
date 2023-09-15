
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
#ifdef IDP_IS3LEVER_TOPLEVEL  //三级综合数据平台的顶级服务
typedef struct 
{
	int Max_PointID;
	int Min_PointID;
	int RealMaxPointID;
}S_RDP_POINTID_RANGE;
typedef std::map<int,S_RDP_POINTID_RANGE >   MAP_INT_POINTRANGE;
#define SG_RDP_HISDAT_SECTINFO_PTYPENUM		4   //历史分段存储测点的测点类型个数
#define SG_RDP_HISDAT_SECTINFO_PTYPE_YC		0
#define SG_RDP_HISDAT_SECTINFO_PTYPE_YX		1
#define SG_RDP_HISDAT_SECTINFO_PTYPE_KWH	2
#define SG_RDP_HISDAT_SECTINFO_PTYPE_MANYC	3

class CHisDatPointSectionInfo
{
	MAP_INT_POINTRANGE   m_PointRangeList[SG_RDP_HISDAT_SECTINFO_PTYPENUM];
	MAP_INT_INT			 m_MaxID2Company[SG_RDP_HISDAT_SECTINFO_PTYPENUM];
	int CovertDBPointTypeToTypeNo(int pointtype,int pointid);
	int CovertDBPointTypeToTypeNo(int pointtype);
public:
	CHisDatPointSectionInfo()
	{
	};
	~CHisDatPointSectionInfo()
	{
	};
	int GetCompanyIDByPointID(int pointtype,int pointid);
	MAP_INT_POINTRANGE *GetPointIDRangleList(int pointtype);
	int InitPointRangeInfo(CDbfEngine &dbfengine);
};
#endif
extern SG_BOOL GetDevMeasInf(int pointtype,int devtype,int devid,int terminal,int meastype,MAP_DEVMEAS_INT &devlist);
#endif