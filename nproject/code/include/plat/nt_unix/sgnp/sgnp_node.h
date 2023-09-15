//==================================================================================================
//	Summary:
//		物理节点信息采集相关头文件
//
//	Comment:
//		<1>	
//
//	---------------------------------------------------------------------------------------------
//	Author:  yanh,shaoy,zhangyy,liuh,wzk           Version: 1.00.000              Date: 2012-02-19
//==================================================================================================

#ifndef __PHYNODE_INFO_HEADER__
#define __PHYNODE_INFO_HEADER__

#include "ace/pre.h"
#include "sgnp_base.h"
#include "sgarchive.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#  pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class ACE_Message_Block;
class CSgArchive;

#define TOPIC_COLLECTOR "collector"

enum COLLECTOR_TYPE
{
	NODE_USAGE						=0x01,		//物理节点常规信息
	NODE_STAT						=0x02,		//物理节点运行数据统计
	PROC_STAT						=0x03,		//进程运行数据统计
	NODE_STATUS						=0x04,		//节点在线状态
	DISK_STAT						=0x05,		//逻辑磁盘统计
	NET_STAT						=0x06,		//网络统计
	DISKPOOL_STAT					=0x07		//主路径占用统计
};

template <class T>
class CP_Collector_Data_T : public SerializeBase
{
public:

	int		type;
	T		data;


	virtual int		buf_size()					{ return sizeof(int)+data.buf_size();}
	virtual void	serialize(CSgArchive&ar)	
	{ 
		if(ar.IsLoading()) ar >> type;
		else ar << type;
		data.serialize(ar); 
	}
};

//云平台逻辑磁盘运行工况统计表
struct  SGNP_Export CP_LogicDisk_Stat
{
	struct Disk_Stat
	{
		Disk_Stat(){ memset(this,0,sizeof(Disk_Stat)); }
		void serialize(CSgArchive&ar);
		char		diskid[32];
		ACE_UINT32  total;
		ACE_UINT32  free;
	};

	std::vector<Disk_Stat> m_stat;

	int		buf_size();
	void	serialize(CSgArchive&);
};

//云平台网络运行工况统计表
struct  SGNP_Export CP_Net_Stat
{
	struct Net_Stat
	{
		Net_Stat()
		{
			memset(phyAddr,0,sizeof(phyAddr));
			speed=load=0;
			inFlow = outFlow=0;
			speed=0;
		}
		void serialize(CSgArchive&ar);
		int buf_size();
		
		ACE_CString adapter;
		char phyAddr[24];
		ACE_UINT32  speed;

		ACE_UINT32  inFlow;		//ellipse时间内的接收
		ACE_UINT32	outFlow;	//ellipse时间内的发送
		short		load;
		short		ellipse;
	};

	std::vector<Net_Stat> m_stat;

	int		buf_size();
	void	serialize(CSgArchive&);
};

//物理节点常规信息	
struct  SGNP_Export CP_PhyNode_Usage
{
	char		name[32];						//名称
	char		os[64];							//操作系统信息
	char		cpu[64];						//cpu，多个？？？
	char		ip[128];						//IP
	ACE_UINT32	totalPhyMemory;					//安装物理内存大小
	ACE_UINT32	totalVisibleMemory;				//可见物理内存大小
	ACE_UINT32	totalVirtualMemory;				//可用虚拟内存大小

	CP_PhyNode_Usage(){ memset(this,0,sizeof(CP_PhyNode_Usage)); }

	int		buf_size() { return sizeof(CP_PhyNode_Usage);}
	void	serialize(CSgArchive&);
};

//物理节点运行工况信息
struct SGNP_Export CP_PhyNode_Stat
{
	short			memLoad;						//内存占用比
	short			cpuLoad;						//CPU使用率
	ACE_UINT32		availMem;						//可用内存


	CP_PhyNode_Stat() { memset(this,0,sizeof(CP_PhyNode_Stat)); }

	int		buf_size()	{ return sizeof(CP_PhyNode_Stat);}
	void	serialize(CSgArchive&);
};

//存储主路径
struct SGNP_Export CP_DiskPool_Stat
{
	struct DiskPool_Stat
	{
		ACE_UINT32 poolID;
		ACE_UINT32 used;
		ACE_UINT32 free;
	};

	std::vector<DiskPool_Stat>  m_stat;

	int		buf_size()	{ return sizeof(ACE_UINT32)*(m_stat.size()*3+1);}
	void	serialize(CSgArchive&);
};

//进程运行工况统计
struct  SGNP_Export CP_Proc_Stat
{
public:

	struct Proc_Stat
	{
		int		cmd;					//命令ID
		int		total_call;				//调用次数
		double  total_send;				//发送数据量
		double	total_recv;				//接收数据量
		double	total_time;				//累计响应时间

		Proc_Stat() { memset(this,0,sizeof(Proc_Stat)); }
		void serialize(CSgArchive&);
	};

	ACE_CString				m_procName;			//进程名
	std::vector<Proc_Stat>	m_stats;			//统计信息

protected:
	int			buf_size();
	void		serialize(CSgArchive&);
};
//节点在线状态
struct SGNP_Export CP_Node_Status {
	
	std::vector< std::pair<ACE_UINT32, ACE_UINT8> > m_status;

	int			buf_size();
	void		serialize(CSgArchive&);
};
//////////////////////////////////////////////////////////////////////////
//进程状态
struct SGNP_Export Proc_Status
{
	Proc_Status()
	{
		memset(this,0,sizeof(Proc_Status));
		pid = ACE_INVALID_PID;
	}
	int			buf_size() { return sizeof(Proc_Status); }
	void		serialize(CSgArchive&);

	char		name[16];		//程序名
	ACE_INT32	pid;			//-1(ACE_INVALID_PID),进程未启动,pid有效仅说明进程已启动，但是启动后是否正常运行则不能确定,
	ACE_UINT32	startTime;		//最近一次成功启动的时间戳
	ACE_UINT32  stopTime;		//最近一次退出的时间戳
	ACE_UINT32	startCount;		//启动次数
	ACE_UINT32  stopCount;		//退出次数
	short		useable;		//进程正常运行标记(可由进程或PCM设置)
	short		apply;			//是否启用守护标记(可由进程或PCM设置)
	short		cpu;			//CPU使用率
	ACE_UINT32	memory;			//内存占用
};

//所有进程状态
struct  SGNP_Export CP_PhyNode_ProcStatus
{
public:

	std::vector<Proc_Status>	m_status;

	int			buf_size();
	void		serialize(CSgArchive&);
};

//进程运行控制
struct SGNP_Export Proc_Control
{
	short		cmd;			//进程控制命令(1-停止,2-由PCM停止）
	short		logSwitch;		//日志输出开关(0-关，1-开）
	ACE_UINT32	logPriority;	//日志输出级别控制
	char		reserve[64];	//预留
};

//进程
class SGNP_Export CP_Proc
{
	friend class CP_ProcManager;
public:

	enum { NO_STOP=0,STOP_FLAG=1,STOP_BY_PCM=2 };

	CP_Proc();

	void StopCmd(short cmd);
	short StopCmd();

	bool UseAble();
	void UseAble(bool b);

	void GetName(ACE_CString&);

	pid_t GetPID();

	bool EnableLog();
	void EnableLog(bool b);

	void LogPriority(ACE_UINT32 Priority );
	ACE_UINT32 LogPriority();

	bool Apply();
	void Apply(bool b);

	ACE_UINT32	StartTime();
	ACE_UINT32  StopTime();

	ACE_UINT32	StartCount();
	ACE_UINT32  StopCount();

	void OnExit();
	void OnStart(pid_t pid);

protected:
	void * pproc;
};

struct struct_procs;
struct struct_proc;
class SGNP_Export CP_ProcManager
{
public:

	enum { MAX_PROC_NUMS=32 };

	CP_ProcManager();
	virtual ~CP_ProcManager();

	virtual int	Open();
	void	Close();
	bool	IsOpen(){ return m_lpProcs!=NULL; }

	void	SetCmd(short cmd);
	short	GetCmd();

	bool FindProc(pid_t pid,CP_Proc&); 
	bool FindProc(const char* name,CP_Proc&);
	bool AddProc(const char*name,CP_Proc&);

	int	GetProcNums();
	bool GetProc(int idx,CP_Proc&);

	bool GetProcsStatus(CP_PhyNode_ProcStatus&);
	
	void StopAllProc(bool bWaitAllProcExit=true );
	bool IsAllProcExit();

protected:
	void SetProcNums(int nums);
#ifdef ACE_WIN32
	ACE_HANDLE 	m_hHanle;
#endif
	struct_procs*		m_lpProcs;
	struct_proc*		m_lpProc;
};


//云平台事项
struct SGNP_Export CP_Event
{
	CP_Event()
	{
		ymd=hms=event_type=obj_type=obj_id=0;
		new_status=old_status=0;
		new_value=old_value=0;
	}

	ACE_UINT32 ymd;
	ACE_UINT32 hms;
	ACE_UINT32 event_type;
	ACE_UINT32 obj_type;
	ACE_UINT32 obj_id;
	short		new_status;
	short		old_status;
	double		new_value;
	double		old_value;
	ACE_CString obj_name;
	ACE_CString obj_name2;
	ACE_CString append;

	int			buf_size();
	void		serialize(CSgArchive&);
};


//////////////////////////////////////////////////////////////////////////
class SGNP_Export CCollectorImpl
{
public:

	CCollectorImpl(){};
	virtual ~CCollectorImpl(){}

	virtual bool CollectUsage(CP_PhyNode_Usage&ni);
	virtual bool CollectStat(CP_PhyNode_Stat&stat){ return false; }
	virtual bool CollectDiskStat(CP_LogicDisk_Stat&stat){ return false; }
	virtual bool CollectNetStat(CP_Net_Stat&stat){ return false; }
	virtual bool CollectDiskPoolStat(CP_DiskPool_Stat&stat){ return false; }
	virtual bool CollectProcessUsage(Proc_Status&s){ return false; }

protected:
	void CollectHostIPs(CP_PhyNode_Usage&ni);
};

#include "ace/post.h"

#endif /* __PHYNODE_INFO_HEADER__ */
