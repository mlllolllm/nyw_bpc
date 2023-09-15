//==================================================================================================
//	Summary:
//		Cloud Platform Common Define Header
//
//	Comment:
//		<1>	
//
//	---------------------------------------------------------------------------------------------
//	Author:  yanh,shaoy,zhangyy,liuh,wzk           Version: 1.00.000              Date: 2012-01-06
//==================================================================================================

#ifndef __CP_COMMON_HEADER__
#define __CP_COMMON_HEADER__

#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#  pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

//==================================================================================================
//云服务分类定义
enum CP_SvcClass
{
	CP_DPP_SVC = 1,			//数据库服务
	CP_HDA_SVC = 2,			//实时库服务
	CP_TSDA_SVC = 3,			//历史库服务
	CP_DPS_SVC = 4,			//数据处理服务
	CP_GDB_SVC = 5,			//图形服务
	CP_FILE_SVC = 6,			//文件服务
	CP_NP_AGENT = 7,			//网络平台代理
	CP_CPS_SVC = 8,		    //云平台应用服务
	CP_NPS = 9,			//网络平台服务
	CP_IDMAP_SVC = 12 		//资源匹配服务
};
//==================================================================================================

//==================================================================================================
//云服务节点分类定义
enum CP_NodeClass
{
	CP_NORMAL_NODE = 1,			//云处理节点
	CP_SCD_NODE = 2,			//云采集节点	
	CP_SCDBAK_NODE = 3, 			//云采集备份节点	
	CP_COMM_TERM_NODE = 4, 			//云通讯终端节点	
};
//云服务节点状态定义
enum CP_NodeStatus
{
	CP_NODESTATUS_ERROR = 0,			//异常状态
	CP_NODESTATUS_NORMAL = 1,			//正常状态
};
//云服务节点备份蓝盒子状态定义
enum CP_BakBlueBoxStatus
{
	CP_BAKBLUEBOX_STATUS_BAK = 0,			//备份状态
											//	CP_BAKBLUEBOX_STATUS_WAIT		=1,			//等待成为主机状态
	CP_BAKBLUEBOX_STATUS_MAIN = 1,			//主机状态
};

//==================================================================================================
//云服务数据单元维护模式定义
enum CP_CellMode
{
	CP_CELLMODE_NONE = 0,			//不维护
	CP_CELLMODE_MANUAL = 1,			//手动维护（如实时库服务）
	CP_CELLMODE_AUTO = 2 			//自动维护(如历史库服务）
};

//==================================================================================================

//==================================================================================================
//云平台关系库表名定义
#define TBL_CP_CENTER				"CP_CENTER_PARA"		//云平台服务中心参数表
#define TBL_CP_PHYNODE_PARA			"CP_PHYNODE_PARA"		//云平台物理节点参数表
#define TBL_CP_PHYNODE				"CP_PHYNODE"			//
#define TBL_CP_DISKPOOL_PARA		"CP_DISKPOOL_PARA"		//存储资源池参数表
#define TBL_CP_LOGICDISK_STAT		"CP_LOGICDISK_STAT"		//云平台逻辑磁盘运行工况统计表
#define TBL_CP_WORKSPACE			"CP_WORKSPACE"			//云平台工作空间表

//#define TBL_CP_SRVCLASS				"CP_SRVCLASS"			//云平台服务分类表
//#define TBL_CP_SRVCONFIG			"CP_SRVCONFIG"			//云平台服务配置表
//#define TBL_CP_LOGICCELL_TYPE		"CP_LOGICCELLTYPE"		//云平台逻辑数据单元定义表
//#define TBL_CP_SRVTYPE_INFO			"CP_SRVTYPE_INFO"		//云平台服务类型信息表
#define TBL_CP_LOGICCELL			"CP_LOGICCELL"			//云平台资源组表
#define TBL_CP_LONGICNODE			"CP_LOGICNODE_PARA"		//云平台逻辑节点表
#define TBL_CP_REL_CELLNODE			"CP_REL_CELLNODE"		//云平台逻辑节点分布表
#define TBL_CP_WKS_BLUEBOX			"CP_WKS_BLUEBOX"		//工作空间与蓝盒子关联表

//云平台实时库表名定义
#define RTBL_PHYNODE				"PHYNODE"				//物理节点表
#define RTBL_LOGICNODE				"LOGICNODE"				//逻辑节点表
#define RTBL_DISKPOOL				"DISKPOOL"				//存储资源表
#define RTBL_DISKSTAT				"DISKSTAT"				//逻辑磁盘统计表
#define RTBL_SRVCONFIG				"SRVCONFIG"				//服务配置表
#define RTBL_NETSTAT				"NETSTAT"				//网络统计表
#define RTBL_WKSBLUEBOX				"WKS_BLUEBOX"			//工作空间与蓝盒子关系表
#define RTBL_PROCINFO				"PROCSTAT"				//进程表
#define RTBL_REALEVENT				"REALEVT"				//实时事项表
#define RTBL_REALEVENTINFO			"REALEVTINFO"			//实时事项信息表

#define FIELD_PHYNODE				"PHYNODE"				//物理节点ID字段
#define FIELD_SRVCLASS				"SRVCLASS"				//服务分类
#define FIELD_DISKID				"DISKID"				//逻辑磁盘ID
#define FIELD_TOTAL					"TOTAL"
#define FIELD_FREE					"FREE"
#define FIELD_USED					"USED"
#define FIELD_HOMEPATH				"HOMEPATH"	
#define FIELD_MAXSIZE				"MAXSIZE"
#define FIELD_ALLOC					"ALLOC"
#define FIELD_CELLID				"CELLID"
#define FIELD_CELLMODE				"CELLMODE"
#define FIELD_WORKSPACEFLAG			"WORKSPACEFLAG"
#define FIELD_TIMESECTION			"TIMESECTION"
#define FIELD_IDSECTION			    "IDSECTION"
#define FIELD_STARTYM				"STARTYM"
#define FIELD_ENDYM					"ENDYM"
#define FIELD_STARTPTID				"STARTPTID"
#define FIELD_ENDPTID				"ENDPTID"
#define FIELD_CELLTYPE				"CELLTYPE"
#define FIELD_DISKRESID				"DISKRESID"
#define FIELD_DISKSIZE				"DISKSIZE"


//云平台监控事项邮箱定义
#define CP_EVENT_MAILBOX			"CP_EVENT"
#define CP_EVENT_CLASS				4
#define PHYNODE_OBJTYPE				1000

//云服务数据单元维护模式定义
enum CP_EVENT_TYPE
{
	CP_EVENT_PHYNODE = 200,			//物理节点在线状态变更事件
	CP_EVENT_PROC = 201,			//进程启停事件
	CP_EVENT_DISKRES = 202,			//资源状态报警
	CP_EVENT_MEMORY = 203,			//内存越限
	CP_EVENT_CPU = 204,			//CPU越限
	CP_EVENT_DB = 205,			//数据库故障
	CP_EVENT_PROCWARNING = 210,			//进程报警
	CP_EVENT_PROCKILLED = 211,			//进程被杀
	CP_EVENT_SRVUPDATE = 212,			//服务升级

};
#define SG_CENTERFLAG_LINKOTHERCENTER		0x0001 //可以读取异分区的数据
#define SG_CENTERFLAG_SYNCOTHERCENTER		0x0002 //可以同步异分区的数据
#define SG_CENTERFLAG_HASSELFDB				0x0004//有自己的数据库
#define SG_CENTERFLAG_MAINTSELFDB			0x0008 //数据库自身维护
#define SG_CENTERFLAG_OPENSELFDAT			0x0010 //对外开放数据
#define SG_CENTERFLAG_MINIBOXHISDBNUMBYSET	0x0020 //MINIBOX历史数据的备份个数按照配置,为0时,则备份数为配置数+1
//考虑有些现场磁盘大小紧张,可能不能做历史数据双备份
#define SG_CENTERFLAG_HISDB_SINGLE			0x0040 //历史数据库在中心单份配置
#define SG_CENTERFLAG_DB_NOTSYNC			0x0080 //参数库不同步
#define SG_CENTERFLAG_STAT_ONLYUSESTATION	0x0100 //公司电量历史数据只采用电站历史来加
#define SG_CENTERFLAG_STAT_ACCNOTPROCLACK	0x0200 //电站总加不处理均摊
#define SG_CENTERFLAG_SYNCMODE_ONLYUP		0x0400 //参数仅向上同步

#include /**/ "ace/post.h"

#endif /* __CSP_COMMON_HEADER__ */
