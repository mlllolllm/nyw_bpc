//==================================================================================================
//	Summary:
//		����ڵ���Ϣ�ɼ����ͷ�ļ�
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
	NODE_USAGE						=0x01,		//����ڵ㳣����Ϣ
	NODE_STAT						=0x02,		//����ڵ���������ͳ��
	PROC_STAT						=0x03,		//������������ͳ��
	NODE_STATUS						=0x04,		//�ڵ�����״̬
	DISK_STAT						=0x05,		//�߼�����ͳ��
	NET_STAT						=0x06,		//����ͳ��
	DISKPOOL_STAT					=0x07		//��·��ռ��ͳ��
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

//��ƽ̨�߼��������й���ͳ�Ʊ�
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

//��ƽ̨�������й���ͳ�Ʊ�
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

		ACE_UINT32  inFlow;		//ellipseʱ���ڵĽ���
		ACE_UINT32	outFlow;	//ellipseʱ���ڵķ���
		short		load;
		short		ellipse;
	};

	std::vector<Net_Stat> m_stat;

	int		buf_size();
	void	serialize(CSgArchive&);
};

//����ڵ㳣����Ϣ	
struct  SGNP_Export CP_PhyNode_Usage
{
	char		name[32];						//����
	char		os[64];							//����ϵͳ��Ϣ
	char		cpu[64];						//cpu�����������
	char		ip[128];						//IP
	ACE_UINT32	totalPhyMemory;					//��װ�����ڴ��С
	ACE_UINT32	totalVisibleMemory;				//�ɼ������ڴ��С
	ACE_UINT32	totalVirtualMemory;				//���������ڴ��С

	CP_PhyNode_Usage(){ memset(this,0,sizeof(CP_PhyNode_Usage)); }

	int		buf_size() { return sizeof(CP_PhyNode_Usage);}
	void	serialize(CSgArchive&);
};

//����ڵ����й�����Ϣ
struct SGNP_Export CP_PhyNode_Stat
{
	short			memLoad;						//�ڴ�ռ�ñ�
	short			cpuLoad;						//CPUʹ����
	ACE_UINT32		availMem;						//�����ڴ�


	CP_PhyNode_Stat() { memset(this,0,sizeof(CP_PhyNode_Stat)); }

	int		buf_size()	{ return sizeof(CP_PhyNode_Stat);}
	void	serialize(CSgArchive&);
};

//�洢��·��
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

//�������й���ͳ��
struct  SGNP_Export CP_Proc_Stat
{
public:

	struct Proc_Stat
	{
		int		cmd;					//����ID
		int		total_call;				//���ô���
		double  total_send;				//����������
		double	total_recv;				//����������
		double	total_time;				//�ۼ���Ӧʱ��

		Proc_Stat() { memset(this,0,sizeof(Proc_Stat)); }
		void serialize(CSgArchive&);
	};

	ACE_CString				m_procName;			//������
	std::vector<Proc_Stat>	m_stats;			//ͳ����Ϣ

protected:
	int			buf_size();
	void		serialize(CSgArchive&);
};
//�ڵ�����״̬
struct SGNP_Export CP_Node_Status {
	
	std::vector< std::pair<ACE_UINT32, ACE_UINT8> > m_status;

	int			buf_size();
	void		serialize(CSgArchive&);
};
//////////////////////////////////////////////////////////////////////////
//����״̬
struct SGNP_Export Proc_Status
{
	Proc_Status()
	{
		memset(this,0,sizeof(Proc_Status));
		pid = ACE_INVALID_PID;
	}
	int			buf_size() { return sizeof(Proc_Status); }
	void		serialize(CSgArchive&);

	char		name[16];		//������
	ACE_INT32	pid;			//-1(ACE_INVALID_PID),����δ����,pid��Ч��˵�������������������������Ƿ�������������ȷ��,
	ACE_UINT32	startTime;		//���һ�γɹ�������ʱ���
	ACE_UINT32  stopTime;		//���һ���˳���ʱ���
	ACE_UINT32	startCount;		//��������
	ACE_UINT32  stopCount;		//�˳�����
	short		useable;		//�����������б��(���ɽ��̻�PCM����)
	short		apply;			//�Ƿ������ػ����(���ɽ��̻�PCM����)
	short		cpu;			//CPUʹ����
	ACE_UINT32	memory;			//�ڴ�ռ��
};

//���н���״̬
struct  SGNP_Export CP_PhyNode_ProcStatus
{
public:

	std::vector<Proc_Status>	m_status;

	int			buf_size();
	void		serialize(CSgArchive&);
};

//�������п���
struct SGNP_Export Proc_Control
{
	short		cmd;			//���̿�������(1-ֹͣ,2-��PCMֹͣ��
	short		logSwitch;		//��־�������(0-�أ�1-����
	ACE_UINT32	logPriority;	//��־����������
	char		reserve[64];	//Ԥ��
};

//����
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


//��ƽ̨����
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
