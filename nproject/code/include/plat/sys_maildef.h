/*常见邮箱定义*/
#define SG_MB_GIS				SG_GIS
#define SG_GIS_EVENT_SAVE		"SGESS"
#define SG_GIS_SYNC				"SGEMSYNC"
#define SG_GIS_RDB				"RDB"
#define SG_MB_LOG				"LOG"
#define SG_MB_LOG_SAVE			"SGLOGS"	
#define SG_DS_LOG_SAVE			"DSSAVE"
#define SG_MB_MONITOR_CENTER	"SGMC"
#define SG_GIS_ADAPTER			"SCADAADAPTER"
#define SG_SYNC					"SGSYNC"
#define SG_SYSTEM				"SGSYS"
#define SG_SYS_MODI_EVENT		"SGMODI"	//系统图形编辑产生的事项
//
#define SG_GIS_EDIT				"SGEDIT"
#define SG_GIS_EDIT_SRV			"SGEDIT_S"
#define SG_MB_TGDB				"SGTGDB"   //时态服务邮箱
#define	CP_MAILBOX_PARACHAN		"DATAEDIT"	//参数改变邮箱
#define	CP_MAILBOX_YX_RETURN	"YX_RESET"	//SCADA事项复归邮箱
#define CP_MAILBOX_YX_RECEIVE   "YX_RECEIVE" //
#define CP_MAILBOX_YX_ALLRESET      "YX_ALLRESER"//SCADA事项全部复归邮箱
//
//#define	RDP_MAILBOX_PARACHAN		"SG_RDB_PARACHAN"	//参数改变邮箱
#define	RDP_MAILBOX_PARACHAN		"SG_RDB_PARACHAN"	//参数改变邮箱
#define	RDP_MAILBOX_MANSET			"SG_RDB_MANSET"	//人工设置邮箱
//#define	RDP_MAILBOX_COMMON			"SG_RDB_COMMON"	//综合数据平台通用邮箱
#define	IDP_MAILBOX_PROCCTRL		"SG_RDB_PCTRL"	//综合数据平台进程管理邮箱

#define	RDP_MAILBOX_RAWEVENT		"SG_RDB_RAWEVENT"	//生事件邮件
#define	RDP_MAILBOX_EVENT		"SG_RDB_EVENT"	//事件邮件
#define	RDP_MAILBOX_EVTMSG		"SG_RDB_EVTMSG"	//事件确认解除消息邮件
#define RDP_MAILBOX_FALOSY       "SG_RDB_FALOSY" //故障定位
#define DBS_MAILBOX_SRV			"DBS_SYNC_SRV"		//数据库同步服务接收邮箱
#define DBS_MAILBOX_TOOL		"DBS_SYNC_TOOL"		//数据同步工具发送邮箱

#define	SG_MAILBOX_EVENT		"SGEVENT"	//事项邮箱
#define SG_MAILBOX_THUNDER		"SGTHUNDER"	//雷击邮箱
#define SG_MAIL_RENDER          "SGRENDER" //强制refresh
#define SG_MAILBOX_LL			"SGLINELOSE" //线损邮箱
#define	SG_MAILBOX_SGEVENT		"SGSGEVENT"	//事故事项邮箱

#define SG_POWERCUT_EVENT		"POWERCUT_EVENT" //停电事项有限

//	在规划中已经取消,因为服务端程序可以与生产管理公用，所以不要删除
 #define SG_MAILBOX_EDIT_MANAGER	"SGEdtMgr"	// 编辑版本邮箱
 #define SG_MAILBOX_SYNC_MISSION	"SGEmVer"	// 台帐同步邮箱
//20140222，接收网络设备节点变化邮件
#define SG_MB_NODE_CHANGE		"NET_NODE_CHG"	//网络设备节点变更邮件

#define	SG_MB_TASK_SYNC			"TASK_SYNC"		//异动流程数据同步

#define	RDP_MB_SIMULATE			"RDB_SIMULATE"	//模拟测点数据邮箱
