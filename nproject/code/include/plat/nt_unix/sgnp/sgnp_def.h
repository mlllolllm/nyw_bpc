//sgnp_def.h
/*******************************************************************************
*******************************************************************************/
#ifndef	SGNPDEF_H
#define	SGNPDEF_H
//#include "sys_moduledef.h"

#define  SG_DEFAULT_SGNP_SRV_PORT		6100			/*name srv缺省端口定义*/
#define  SG_DEFAULT_SGNP_AGENT_PORT		6101
#define  SG_DEFAULT_MQS_PORT			6102			/*消息服务缺省端口定义*/
#define  SG_DEFAULT_FPS_SRV_PORT		6103			/*rdb srv缺省端口定义*/
#define  SG_DEFAULT_MONITOR_AGENT_PORT	6104			/*monitor agent缺省端口定义*/
#define  SG_DEFAULT_GDB_SRV_PORT		6105			/*gdb srv缺省端口定义*/
#define  SG_DEFAULT_BKG_SRV_PORT		6106			/*bkg srv缺省端口定义*/
#define  SG_DEFAULT_LITTLE_SRV_PORT		6107			/*little srv缺省端口定义 简单服务*/
#define  SG_DEFAULT_EP_SRV_PORT			6108			/*ep srv缺省端口定义*/
#define  SG_DEFAULT_LOGMSGSRV_PORT		6109			/*日志消息服务缺省端口定义*/
#define  SG_DEFAULT_DEBUG_CENTER_PORT	6110			/*monitor center UDP包接受端口定义*/
#define  SG_DEFAULT_PUB_SRV_PORT		6111			/*pub srv缺省端口定义*/

#define  SG_DEFAULT_RDP_RECV_PORT		6112			/*中央实时服务接收数据缺省端口定义*/
#define  SG_DEFAULT_RDP_SEND_PORT		6113			/*中央实时服务发送数据缺省端口定义*/
#define  SG_DEFAULT_HSDASRV_PORT		6114			/*实时服务实时数据服务缺省端口定义*/
#define  SG_DEFAULT_TSDASRV_PORT		6115			/*实时服务历史数据服务缺省端口定义*/
#define  SG_DEFAULT_RDP_PROCSRV_PORT	6116			/*IDP进程监控缺省端口定义*/
#define  SG_DEFAULT_EVTSRV_PORT			6117			/*事服务端口*/
#define  SG_DEFAULT_SGDPP_SRV_PORT		6118			/*数据库通道缺省端口定义*/
#define  SG_DEFAULT_SGDPS_SRV_PORT		5700			/*数据处理通道缺省端口定义*/
#define  SG_DEFAULT_SGCOMM_SRV_PORT		5701			/*前置服务缺省端口定义*/
#define  SG_DEFAULT_SGREP_SRV_PORT		6119			/*复制服务缺省端口定义*/
#define  SG_DEFAULT_SGIDMAP_PORT		6121			/*设备ID对应服务端口定义*/
#define  SG_DEFAULT_SGCPS_PORT			6120			/*云平台应用服务缺省端口定义*/
#define  SG_DEFAULT_SGCPS_REP_PORT		6122			/*云平台应用服务为复制服务服务的进程缺省端口定义*/
#define  SG_DEFAULT_XSCAL_SRV_PORT		6123			/*线损计算 srv缺省端口定义*/
#define  SG_DEFAULT_TOPO_SRV_PORT		6124			/*拓扑服务 srv缺省端口定义*/
#define  SG_DEFAULT_MINIBOXMAN_PORT		5702			/*微盒子管理服务端口*/
#define  SG_DEFAULT_GAPTERMSEND_PORT	6998			/*网闸发送服务端口*/
#define  SG_DEFAULT_GAPCOMM_PORT		6999			/*网闸通讯程序端口*/


#define  SG_DEFAULT_TGDB_SRV_PORT_START	6125			/*时态空间引擎缺省起始端口定义*/
#define  SG_DEFAULT_TGDB_SRV_PORT_END	6140			/*时态空间引擎缺省终止端口定义*/

#define SG_DEFAULT_SGUBS_SRV_PORT       6150            /*三相不平衡优化服务端口定义*/

//5801~5899 dps
#define  SG_DEFAULT_SGDPS_SRV_PORT_BAK		5801			/*数据处理通道缺省端口定义*/
//5901~5999 MiniBoxMan
#define  SG_DEFAULT_MINIBOXMAN_PORT_BAK		5901			/*微盒子管理服务端口*/

//
#define  SG_DEFAULT_QUEUE_MAX		(1024*1024*16)	/*队列缺省最大缓存16M*/
#define	 SG_HEARTBEAT_CLIENT		10				/*客户端心跳间隔--10 seconds*/
#define  SG_HEARTBEAT_SRV			15				/*服务端心跳间隔--15 seconds*/	
//
#define  SG_UDP_BUF_LEN				1024			//1k
/*消息类型定义*/
enum SG_MT_DEF
{
	SG_MT_STOP = 0xFFFF,
	SG_MT_CHECK = 0xFFFE,		//检测报文
	/*系统消息类型定义*/
	SG_SYS_STATUS = 0x01,
	SG_SYS_HEARTBEAT = 0x02,		/*心跳*/
	//
	SG_SYS_CMD_POST = 0x03,		/*系统命令*/
	SG_SYS_CMD_RECV = 0x04,
	//
	SG_SYS_EVENT_POST = 0x05,		/*系统事项*/
	SG_SYS_EVENT_RECV = 0x06,
	//other
	SG_SYS_LINKTYPE = 0x07,		/*设置链路类型*/
	SG_SYS_TIME = 0x08,		/*获得系统时间*/
	SG_SYS_TIME_REPLY = 0x09,		/*获得系统时间回复*/
	/*邮件消息类型定义*/
	SG_MAIL_POST = 0x10,		/*寄信*/
	SG_MAIL_RECV = 0x11,		/*收信*/
	SG_MAIL_REG = 0x12,		/*注册邮箱*/
	SG_MAIL_UNREG = 0x13,		/*注销邮箱*/
	SG_MAIL_REREG = 0x14,		/*重新注册邮箱*/
	SG_MAIL_COUNT = 0x15,		/*邮件计数*/
	SG_MAIL_REGET = 0x16,		/*重连后获得备份数据*/
	SG_MAIL_REGET_EX = 0x17,		/*为了兼容老系统而增加,重连后获得备份数据扩展*/
	//
	SG_MAIL_POST2 = 0x20,	//需返回消息发送确认
	SG_MAIL_COUNT2 = 0x21,
	//
	SG_PROC_START = 0x30,		/*进程启动*/
	SG_PROC_EXIT = 0x31,		/*进程退出*/
	//
	SG_CHANGE_SRV = 0x40,		/*改变agent中的服务指向*/
	//
	SG_NAME_BIND = 0x50,		/*绑定名字*/
	SG_NAME_BIND_REPLY = 0x51,		/*绑定名字回复*/
	SG_NAME_UNBIND = 0x52,		/*解除绑定*/
	SG_NAME_RESOLVE = 0x53,		/*解析名字*/
	SG_NAME_RESOLVE_REPLY = 0x54,		/*解析名字回复*/
	SG_NAME_REBIND = 0x55,		/*重新绑定*/
	/*实时库消息类型定义*/
	SG_MT_ALLDATA = 0x100,		/*全数据请求*/
	SG_MT_PARTDATA = 0x101,		/*部分数据请求*/
	SG_MT_UPDATE = 0x102,		/*数据更新*/
	SG_MT_OPEN_STREAM = 0x103,		/*建立流请求*/
	SG_MT_CLOSE_STREAM = 0x104,		/*关闭流请求*/
	SG_MT_STREAM = 0x105,		/*发送流数据（变化数据）请求消息,由定时器触发*/
	SG_MT_STREAM_INDEX = 0x106,		/*创建流索引*/
	SG_MT_MODIFY_INDEX = 0x107,		/*修改流索引*/
	SG_MT_UPDATE_FLAG = 0x108,		/*设置流修改标记*/
	SG_MT_DESC = 0x109,		/*描述表结构*/

	//SG_DATA_POST					=0x120,		/*投递数据包*/
	//SG_DATA_RECV					=0x121,		/*接收数据包*/
	SG_SYS_HEARTBEAT_EX = 0x200,		/*为了兼容老系统而增加*/
	SG_SYS_LINKTYPE_EX = 0x201,		/*在原结构上新增物理节点ID信息*/

	SG_NODE_STATS = 0x300,		/*节点运行统计数据*/
	SG_PROC_STATS = 0x301,		/*进程运行统计数据*/
	SG_NODE_EVENT = 0x302,		/*节点事项*/
};

//调试信息级别定义
enum DEBUG_LEVEL
{
	DEBUG_INVALID = -1,					//无效调试级别

	DEBUG_NONE = 0,					//不输出调试信息
	DEBUG_STARTUP = 0100,					//LM_STARTUP,进程启动信息
	DEBUG_SHUTDOWN = 01,					//LM_SHUTDOWN,进程正常退出信息
	DEBUG_LM_TRACE = 02,					//LM_TRACE,函数调用跟踪
	DEBUG_NORMAL = 04,					//LM_DEBUG,	常用调试级别
	DEBUG_WARNING = 040,					//LM_WARNING,/警告
	DEBUG_ERROR = 0200,					//LM_ERROR,错误
};

/*监控命令定义*/
enum  MONITOR_CMD
{
	CMD_INVALID = 0,			//do nothing

	/*进程控制*/
	CMD_RESET0 = 1,			//reset（进程自己处理该命令)
	CMD_RESET1 = 2,			//kill+startup
	CMD_RESET2 = 3,			//quit+startup
	CMD_STARTUP = 4,			//启动进程
	CMD_KILL = 5,			//杀死进程（被动）
	CMD_QUIT = 6,			//使进程主动退出
	CMD_PROCESS = 7,			//进程信息
	CMD_PROCESS_GUARD = 8,			//守护进程

	/*系统相关*/
	CMD_REBOOT = 20,			//reboot机器
	CMD_SHUTDOWN = 21,			//关机
	CMD_SCHEDULE_REBOOT = 22,			//定时reboot机器
	CMD_SCHEDULE_SHUTDOWN = 23,			//定时关机
	CMD_SCREEN = 24,			//拷屏
	CMD_SCREEN_TIMER = 25,			//定期拷屏
	CMD_HOST_INFO = 26,			//获得主机信息
	CMD_GET_TIME = 27,			//获得主机时间
	CMD_SET_TIME = 28,			//设置主机时间

	/*服务控制*/
	CMD_LOAD_SVC = 40,			//加载服务模块
	CMD_REMOVE_SVC = 41,			//卸载服务模块
	CMD_REPLACE_SVC = 42,			//替换服务模块
	CMD_RECONFIGURE = 43,			//重新启用服务配置文件
	CMD_REPLACE_MONITOR = 44,			//替换监控处理模块
	/*调试相关*/
	CMD_DEBUG_LEVEL = 50,			//设置调试级别
	CMD_DEBUG_OPT_UDP = 51,			//调试输出选项--UDP方式
	CMD_DEBUG_OPT_FILE = 52,			//调试输出选项--FILE方式
	CMD_DEBUG_OPT_IO = 53,			//调试输出选项--IO方式
	CMD_DEBUG_OPT_SPY = 54,			//调试输出选项--DebugSpy方式
	CMD_DEBUG_OPT_NONE = 55,			//调试输出选项--停止任何输出
	/*文件相关*/
	CMD_UPLOAD_FILE = 60,			//上传文件（节点－>中心）
	CMD_DOWNLAOD_FILE = 61,			//下传文件（中心－>节点)
	CMD_REMOVE_FILE = 62,			//删除文件
	CMD_RENAME_FILE = 63,			//重命名文件
	CMD_LCF_FILE = 64,			//获得LCF文件信息
	//
	CMD_ONLINE_HOSTS = 100,			//在线节点
	CMD_TOPMOST_SRV = 101,			//获得最上级SRV地址
	CMD_AGENT_INFO = 102,			//
	//
	CMD_BACK_MAIN_SWITCH = 200,			//主备切换
	//
	CMD_MAXID = 500

};
enum MONITOR_EVENT
{
	EVENT_BASEID = CMD_MAXID,
	//sgnp server 产生
	EVENT_LINK = EVENT_BASEID + 1,			//成功连接sgnpsrv
	EVENT_UNLINK = EVENT_BASEID + 2,			//与agent或下级sgnpsrv连接断开
	//sgnp server与agent产生
	EVENT_BRIDGE_BUILD = EVENT_BASEID + 3,			//build bridge
	EVENT_BRIDGE_BREAK = EVENT_BASEID + 4,			//bridge break
	EVENT_BRIDGE_HEARTBEAT = EVENT_BASEID + 5,			//bridge heartbeat
	EVENT_BRIDGE_PUTQ = EVENT_BASEID + 6,			//put message to bridge's message fail
	EVENT_MAIL_RESET = EVENT_BASEID + 7,			//邮件计数重置
	EVENT_MAIL_LOST = EVENT_BASEID + 8,			//邮件丢失
	//agent产生
	EVENT_PROG_START = EVENT_BASEID + 10,			//进程启动事项
	EVENT_PROG_QUIT = EVENT_BASEID + 11,			//进程退出事项
	EVENT_SGNP_SRV_CHANGE = EVENT_BASEID + 12,			//agent连接的SGNPSRV地址改变事项
	EVENT_SGNP_SRV_CHANGE_OK = EVENT_BASEID + 13,			//SGNPSRV地址改变后重联成功事项
	EVENT_CHUNNEL_STATUS = EVENT_BASEID + 15,			//通道状态
	//当邮件已满，激发该事件,网络平台对邮箱已满的默认处理策略是按FIFO删除邮件，直到邮箱非满,
	//果应用不想丢失任何一个邮件，就需要处理该事项
	EVENT_MAILBOX_FULL = EVENT_BASEID + 30,
	//gdbsrv产生
	//rdbsrv产生
};

/*链路类型定义*/
enum LINK_TYPE
{
	LINK_DATA = 0,	//数据链路
	LINK_BRIDGE = 1,	//桥接链路
//	LINK_MONITOR	=2,	//监控链路
};
// --- 邮件标识
enum MAIL_FLAG
{
	f_none = 0,
	f_local = 1,
	f_national = 2,
	f_international = 4,
	//
	f_notbakup = 8,
	//
	m_local = f_local,
	m_national = f_local | f_national,
	m_international = f_local | f_national | f_international
};
enum SYS_NOTIFY
{
	NOTIFY_NONE = -1,	//nothing
	//
	SYS_MSG = 10,	//通知消息
	SYS_LOCK = 11,
	SYS_UNLOCK = 12,
	SYS_START_EP = 31,	//开始异常处理方案
	SYS_END_EP = 32,	//结束异常处理方案
	SYS_GDB_START = 50,	//空间引擎启动
	SYS_GDB_INIT = 51,	//图形数据重新加载
};
//
/*错误号定义*/
#define E_MAIL_LINK_SRV			(-100)		/*mail agent can't link to mail server*/
#define E_MAIL_LINK_AGENT		(-101)		/*mail client can't link to local mail agent*/
#define E_MAIL_FIND_SRV			(-102)		/*can't find mail server addr*/

#define E_RDB_FIND_SRV			(-200)		/*can't find rdb server addr*/

#define E_NAMING_CONTEXT		(-300)		/*ACE_Naming_Context object does not exists*/
#define E_OPEN_NAME_SRV			(-301)		/*open name srv failed*/
#define E_BIND_NAME				(-302)		/*bind name failed*/
#define E_RESOLVE_NAME			(-303)		/*resolve name failed*/

#endif
