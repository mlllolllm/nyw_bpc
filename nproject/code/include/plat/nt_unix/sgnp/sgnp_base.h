
/*******************************************************************************
*******************************************************************************/

#ifndef SGNETBASE_H
#define SGNETBASE_H 

#if defined(_MSC_VER)
#	pragma warning(disable:4786)
#   pragma warning(disable:4267)
#endif /* _MSC_VER */

#include "ACE_Includes.h"
#include "sgnp_export.h"
#include "sgnp_def.h"
#ifdef ACE_HAS_STANDARD_CPP_LIBRARY
#include <vector>
#include <list>
using namespace std;

typedef vector<void*> PtrArray;
typedef vector<ACE_CString>StringArray;

#else

#include "ace/Vector_T.h"
#include "ace/Free_List.h"

typedef ACE_Vector<void*> PtrArray;
typedef ACE_Vector<ACE_CString>StringArray;

#endif


typedef ACE_Hash_Map_Manager<void*, void*, ACE_Null_Mutex> Ptr2Ptr;
typedef ACE_Hash_Map_Manager<ACE_CString, void*, ACE_Null_Mutex>String2Ptr;
typedef ACE_Hash_Map_Manager<ACE_INT32, void*, ACE_Null_Mutex>Int2Ptr;
typedef ACE_Hash_Map_Manager<ACE_CString, ACE_INT32, ACE_Null_Mutex>String2Int;
typedef ACE_Hash_Map_Manager<ACE_INT32, ACE_INT32, ACE_Null_Mutex>Int2Int;

#ifdef WIN32
SGNP_TEMPLATE template class SGNP_Export ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>;
#endif
typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> Svc_Handler_Base;
typedef ACE_Connector<Svc_Handler_Base, ACE_SOCK_CONNECTOR> Connector_Base;

#ifdef ACE_WIN32
typedef ACE_Malloc_T<ACE_PAGEFILE_MEMORY_POOL, ACE_Process_Mutex, ACE_PI_Control_Block> SHM_Allocator;
//	typedef ACE_Malloc_FIFO_Iterator_T<ACE_PAGEFILE_MEMORY_POOL,ACE_Process_Mutex,ACE_PI_Control_Block>SHM_Allocator_Iterator;
#else
typedef ACE_Malloc_T<ACE_SHARED_MEMORY_POOL, ACE_Process_Mutex, ACE_PI_Control_Block> SHM_Allocator;
//	typedef ACE_Malloc_FIFO_Iterator_T<ACE_SHARED_MEMORY_POOL,ACE_Process_Mutex,ACE_PI_Control_Block>SHM_Allocator_Iterator;
#endif



class  Header
{
public:

	enum HeaderFlag
	{
		byte_order_flag = 1, /*字节序*/
		zip_flag = 2,	/*压缩标记*/
		encrypt_flag = 4	/*加密标记*/
	};

	Header()
	{
		length_ = type_ = flag_ = 0;
	}

	ACE_UINT32		get_length() { return length_; }
	void			set_length(ACE_UINT32 length) { length_ = length; }

	ACE_UINT32		get_type() { return type_; }
	void			set_type(ACE_UINT32 type) { type_ = type; }

	ACE_UINT16		get_crc() { return crc_; }
	void			set_crc(ACE_UINT16 crc) { crc_ = crc; }

	ACE_UINT16		get_flag() { return flag_; }
	void			set_flag(ACE_UINT16 flag) { flag_ = flag; }

	ACE_UINT32		get_byte_order() { return flag_ & byte_order_flag; }
	void			set_byte_order() { flag_ |= byte_order_flag; }

	ACE_UINT32		get_zip() { return flag_ & zip_flag; }
	void			set_zip() { flag_ |= zip_flag; }

	ACE_UINT32		get_encrypt() { return flag_ & encrypt_flag; }
	void			set_encrypt() { flag_ |= encrypt_flag; }

	char* get_buf() { return buf_; }
	int				buf_length() { return sizeof(ACE_UINT32) * 3; }

	int encode(char* buf)
	{
		ACE_UINT32 length = htonl(length_);
		ACE_UINT32 type = htonl(type_);
		ACE_UINT16 crc = ntohs(crc_);
		ACE_UINT16 flag = ntohs(flag_);

		memcpy(buf, &length, sizeof(ACE_UINT32));
		memcpy(buf + sizeof(ACE_UINT32), &type, sizeof(ACE_UINT32));
		memcpy(buf + sizeof(ACE_UINT32) + sizeof(ACE_UINT32), &crc, sizeof(ACE_UINT16));
		memcpy(buf + sizeof(ACE_UINT32) + sizeof(ACE_UINT32) + sizeof(ACE_UINT16), &flag, sizeof(ACE_UINT16));

		return buf_length();
	}

	int encode()
	{
		return encode(buf_);
	}

	void decode()
	{
		decode(buf_);
	}

	void decode(const char* buf)
	{
		ACE_UINT32 length, type;
		ACE_UINT16 crc, flag;

		memcpy(&length, buf, sizeof(ACE_UINT32));
		memcpy(&type, buf + sizeof(ACE_UINT32), sizeof(ACE_UINT32));
		memcpy(&crc, buf + sizeof(ACE_UINT32) + sizeof(ACE_UINT32), sizeof(ACE_UINT16));
		memcpy(&flag, buf + sizeof(ACE_UINT32) + sizeof(ACE_UINT32) + sizeof(ACE_UINT16), sizeof(ACE_UINT16));

		length_ = ntohl(length);
		type_ = ntohl(type);
		crc_ = ntohs(crc);
		flag_ = ntohs(flag);
	}

private:

	ACE_UINT32		length_;		/*正文长度*/
	ACE_UINT32		type_;			/*报文类型*/
	ACE_UINT16		crc_;			/*crc-ccitt值*/
	ACE_UINT16		flag_;			/*标记*/

	char buf_[24];
};

int SGNP_Export write_mb(ACE_SOCK_Stream& peer, ACE_Message_Block* pmb, int so = ACE_DEFAULT_TIMEOUT, int level = 0, int packetsize = -1);
int SGNP_Export write_mb(ACE_SOCK_Stream& peer, char* data, size_t len, size_t msg_type, int so = ACE_DEFAULT_TIMEOUT, int level = 0, int packetsize = -1);
int SGNP_Export write_mb_base(ACE_SOCK_Stream& peer, char* data, size_t len, size_t msg_type, int so = ACE_DEFAULT_TIMEOUT, int level = 0, int packetsize = -1, int DesFlag = 0);
int SGNP_Export read_mb(ACE_SOCK_Stream& peer, ACE_Message_Block*& pmb, int to = ACE_DEFAULT_TIMEOUT);
int SGNP_Export read_mb_base(ACE_SOCK_Stream& peer, ACE_Message_Block*& pmb, int to = ACE_DEFAULT_TIMEOUT,int *pProcMode=NULL);

ssize_t SGNP_Export ns_recv(ACE_HANDLE handle, void* buf, size_t len, const ACE_Time_Value* timeout = 0, size_t* bt = NULL);
ssize_t SGNP_Export ns_send(ACE_HANDLE handle, const void* buf, size_t len, const ACE_Time_Value* timeout = 0, size_t* bt = 0, int packet = -1);

//
int SGNP_Export write_mb_udp(ACE_SOCK_Dgram& dgram_local, ACE_Addr& remote_addr, ACE_Message_Block* pmb);
int SGNP_Export write_mb_udp(ACE_SOCK_Dgram& dgram_local, ACE_Addr& remote_addr, char* data, size_t len, size_t msg_type);
int SGNP_Export read_mb_udp(ACE_SOCK_Dgram& dgram_local, ACE_Addr& remote_addr, ACE_Message_Block*& pmb);
int SGNP_Export read_mb_udp(ACE_SOCK_Dgram& dgram_local, ACE_Addr& remote_addr, char* data, int& len, size_t& msg_type);
//
int SGNP_Export check_num_c(ACE_SOCK_Stream& peer);
int SGNP_Export check_num_s(ACE_SOCK_Stream& peer);
//
int SGNP_Export get_addrs(const ACE_CString& str, vector<ACE_INET_Addr>& addrs);
int SGNP_Export get_sgnp_srv_addr(ACE_INET_Addr& addr);
int SGNP_Export get_float_ip(ACE_CString& strip);
bool SGNP_Export get_sgmc_addr(ACE_INET_Addr& addr);
//
int SGNP_Export get_now(ACE_CString& dt);
int SGNP_Export get_datetime(ACE_CString& strdt, ACE_Date_Time* dt);
int SGNP_Export get_datetime(ACE_CString& strdt, ACE_Time_Value* dt);
//
int SGNP_Export get_sub_home(const char* dir, ACE_TString& sub_home);
int SGNP_Export log_sgnp_error(const char* err);
int SGNP_Export get_proc_name(ACE_TString& pname);
bool SGNP_Export ProcIsExist(char* procname);
ACE_UINT32 SGNP_Export get_qbuffer_size();
//获得物理节点ID,返回值<1，表明失败
int SGNP_Export get_node_id();
int SGNP_Export write_string_buffer(ACE_CString& strBuffer, const void* pBuffer, size_t Length);
int SGNP_Export resize_string_buffer(ACE_CString& strBuffer, size_t Length);

//	level 为压缩级别，取值从 1 - 9 ， space 为解压缩后的大小，如果 strOutput 已经设定了长度，可以使用默认值
ssize_t SGNP_Export package_data(ACE_CString& strOutput, const void* pBuffer, size_t Length, int level = 5);
ssize_t SGNP_Export extract_data(ACE_CString& strOutput, const void* pBuffer, size_t Length, int space = 0);

int SGNP_Export zipdata(char* src, ACE_UINT32 srcLen, char*& dest, ACE_UINT32& destLen, int level);
int SGNP_Export unzipdata(ACE_Message_Block* pmbSrc, ACE_Message_Block*& pmbDest);

//////////////////////////////////////////////////////////////////////////
class SGNP_Export SG_Connector : public Connector_Base
{
public:

	SG_Connector() :handler_(0), stop_flag_(0), breconnect_(false) {};
	int close();
	/*阻塞重连*/
	int reconnect(size_t interval = 2);

	void set_addr(ACE_INET_Addr& addr) { addr_ = addr; }
	void set_addr(const char* straddr) { str_addr_ = straddr; }
	ACE_INET_Addr& get_addr() { return addr_; }
	void set_handler(Svc_Handler_Base* handler) { handler_ = handler; }
	//
	bool is_reconnect() { return breconnect_; }
	void clear_reconnect() { breconnect_ = false; }

protected:
	virtual int connect_svc_handler
	(Svc_Handler_Base*& svc_handler,
		const ACE_SOCK_Connector::PEER_ADDR& remote_addr,
		ACE_Time_Value* timeout,
		const ACE_SOCK_Connector::PEER_ADDR& local_addr,
		int reuse_addr, int flags, int perms);
	//
	Svc_Handler_Base* handler_;
	ACE_INET_Addr		addr_;		/*服务地址*/
	size_t				stop_flag_;
	bool				breconnect_;
	ACE_CString			str_addr_;
};
//////////////////////////////////////////////////////////////////////////
class SGNP_Export SG_Svc_Handler : public Svc_Handler_Base
{
public:

	SG_Svc_Handler();
	~SG_Svc_Handler();
	virtual int open(void*);

	int stop();
	ACE_UINT32		get_remote_ip() { return m_ClientHostIP; }
	ACE_CString& get_remote_name() { return m_ClientHostName; }
	void		SetHandleActiveTime();
	unsigned int GetHandleActiveTime()
	{
		return m_ActiveTime;
	};
	//
	virtual int handle_input(ACE_HANDLE handle);
	virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = 0);
protected:
	virtual int put(ACE_Message_Block*, ACE_Time_Value* = 0);
	virtual int svc();
	virtual int	process(ACE_Message_Block* pmb);
	void		remote_ip();
protected:
	ACE_UINT32			m_ClientHostIP;
	ACE_CString			m_ClientHostName;
	unsigned int		m_ActiveTime;  //连接有效标志
	unsigned char		m_ConnectFlag;  //连接标志
};

//////////////////////////////////////////////////////////////////////////
//class Quit_Handler : public ACE_Event_Handler 
//{
//public:
//	Quit_Handler (ACE_Reactor *r) : ACE_Event_Handler (r) {}
//
//	virtual int handle_exception (ACE_HANDLE) 
//	{
//		reactor ()->end_reactor_event_loop ();
//		return -1;
//	}
//
//	virtual int handle_close (ACE_HANDLE, ACE_Reactor_Mask)
//	{ 
//		delete this; 
//		return 0; 
//	}
//private:
//	virtual ~Quit_Handler () {}
//};
//////////////////////////////////////////////////////////////////////////
template<class T>
class Handler_List :public list<T>
{
public:
	int		lock() { return lock_.acquire(); }
	int		unlock() { return lock_.release(); }

	//already lock
	int		rem(const T& handler)
	{
		ACE_GUARD_RETURN(ACE_Thread_Mutex, ace_mon, this->lock_, -1);
		this->remove(handler);
		return this->size();
	}
	int		add(const T& handler)
	{
		ACE_GUARD_RETURN(ACE_Thread_Mutex, ace_mon, this->lock_, -1);
		this->push_back(handler);
		return this->size();
	}
	int     handler_size()
	{
		ACE_GUARD_RETURN(ACE_Thread_Mutex, ace_mon, this->lock_, -1);
		return this->size();
	}
	//
	ACE_Thread_Mutex& get_lock() { return lock_; }
	//
private:
	ACE_Thread_Mutex lock_;
};

//////////////////////////////////////////////////////////////////////////
class CSgArchive;
SGNP_Export CSgArchive& operator << (CSgArchive& ar, ACE_CString&);
SGNP_Export CSgArchive& operator >> (CSgArchive& ar, ACE_CString&);
SGNP_Export CSgArchive& operator << (CSgArchive& ar, ACE_Time_Value&);
SGNP_Export CSgArchive& operator >> (CSgArchive& ar, ACE_Time_Value&);

//////////////////////////////////////////////////////////////////////////
class SGNP_Export PROC_INFO
{
public:
	PROC_INFO()
	{
		pid_ = 0;
		watch_ = 0;
	}
	ACE_UINT32		pid_;
	ACE_CString		name_;
	ACE_CString		dt_;
	ACE_UINT32		watch_;
	//
	void serialize(CSgArchive&);
	int buf_size();
};
class PROCS_INFO : public  vector<PROC_INFO>
{
public:
	void serialize(CSgArchive&);
};
//

//////////////////////////////////////////////////////////////////////////
struct SGNP_Export SG_Addr
{
	ACE_UINT32  ip_;
	short		port_;
	ACE_UINT32  reserve_;
	SG_Addr(const ACE_INET_Addr& addr)
	{
		ip_ = addr.get_ip_address();
		port_ = addr.get_port_number();
		reserve_ = 0;
	}
	SG_Addr& operator=(const ACE_INET_Addr& addr)
	{
		ip_ = addr.get_ip_address();
		port_ = addr.get_port_number();
		reserve_ = 0;
		return *this;
	}
	SG_Addr() { memset(this, 0, sizeof(SG_Addr)); }
	void serialize(CSgArchive&);
	int buf_size() { return 2 * sizeof(ACE_UINT32) + sizeof(short); }
};
//

struct SGNP_Export SGNP_Cmd_Header
{
	SG_Addr			des_;
	SG_Addr			src_;
	ACE_UINT32		type_;
	//
	SGNP_Cmd_Header() { type_ = 0; }
	void serialize(CSgArchive&);
	int buf_size() { return des_.buf_size() * 2 + sizeof(ACE_UINT32); }
	//
	void from_pmb(ACE_Message_Block* pmb);
};
//
struct SGNP_Export SGNP_Cmd
{
	SGNP_Cmd_Header header_;
	ACE_CString		data_;
	//
	void serialize(CSgArchive&);
	int buf_size() { return header_.buf_size() + sizeof(ACE_UINT32) + data_.length(); }
	//
	void from_pmb(ACE_Message_Block* pmb);
	void to_pmb(ACE_Message_Block*& pmb);
	//
};
////
struct SGNP_Export SGNP_Event
{
	ACE_UINT32 type_;	//事项类型
	ACE_CString dt_;	//发生时间
	ACE_CString where_;	//发生地点
	ACE_CString data_;	//
	SGNP_Event()
	{
		type_ = EVENT_BASEID;
		char host[HOST_NAME_MAX];
		ACE_OS::hostname(host, HOST_NAME_MAX);
		where_ = host;
		get_now(dt_);
	}
	void serialize(CSgArchive&);
	int buf_size() { return sizeof(ACE_UINT32) * 4 + data_.length() + dt_.length() + where_.length(); }
	void decode(const char* buf, ACE_UINT32 len);
	void encode(char* buf, ACE_UINT32 len);
	//
	void from_pmb(ACE_Message_Block* pmb);
	void to_pmb(ACE_Message_Block*& pmb);
};
//

class SGNP_Export SG_Result
{
public:
	SG_Result() { init(); }
	//
	int get_result(int to = 60);
	int set_result(int ret);
	void init();
private:
	ACE_Auto_Event event_;
	int ret_value_;
};

struct SGNP_Export SG_LINKTYPE
{
	//
	ACE_UINT32		type_;
	ACE_CString		hostname_;
	//
	SG_LINKTYPE()
	{
		type_ = LINK_DATA;
		char host[HOST_NAME_MAX];
		memset(host, 0, sizeof(host));
		ACE_OS::hostname(host, HOST_NAME_MAX);
		hostname_ = host;
	}
	void serialize(CSgArchive&);
	int buf_size() { return sizeof(ACE_UINT32) * 2 + hostname_.length(); }
	//
	void from_pmb(ACE_Message_Block* pmb);
	void to_pmb(ACE_Message_Block*& pmb);
};
//
struct SGNP_Export SG_REGET_EX
{
	//
	SG_LINKTYPE		lt_;
	unsigned char	first_;
	ACE_UINT32		cur_no_;
	//
	SG_REGET_EX()
	{
		first_ = 0;
		cur_no_ = 0;
	}
	void serialize(CSgArchive&);
	int buf_size() { return lt_.buf_size() + sizeof(char) + sizeof(ACE_UINT32); }
	//
	void from_pmb(ACE_Message_Block* pmb);
	void to_pmb(ACE_Message_Block*& pmb);
};

struct SGNP_Export SG_FILEINFO
{
	ACE_CString fn_;
	ACE_UINT32  dwHighTime_;
	ACE_UINT32  dwLowTime_;
	void serialize(CSgArchive&);
};
class SGNP_Export FILES_INFO : public  vector<SG_FILEINFO>
{
public:
	void serialize(CSgArchive&);
	void from_pmb(ACE_Message_Block* pmb);
};

struct SGNP_Export SG_SYS_NOTIFY
{
public:
	ACE_UINT32	type_;
	ACE_CString data_;
	void serialize(CSgArchive&);
};

// --- 图形库访问网络命令发送前参数准备结构
class CSgMemFile;
class SGNP_Export NetCommandSendParaPrepare
{
public:
	NetCommandSendParaPrepare(int nGrowBytes = 4096);
	~NetCommandSendParaPrepare();
public:
	void End();
public:
	CSgMemFile* fs;
	CSgArchive* ars;
};

class SGNP_Export NetCommandReceiveExplain
{
public:
	NetCommandReceiveExplain(ACE_Message_Block** pmb);
	~NetCommandReceiveExplain();
public:
	bool Valid() {
		return ret > 0;
	}
public:
	ACE_Message_Block* m_pmb;
	int ret;
	int len;
	CSgMemFile* fs;
	CSgArchive* ars;
};

// --- 系统运行监控
class SGNP_Export CSysRunInfo
{
public:
	CSysRunInfo(int MsgType = 0, int SubType = 0);
	~CSysRunInfo();

public:
	// --- 输出服务请求
	void OutRequest();
	// --- 设置错误信息
	void SetErrorInfo(char* pErrorInfo);
	void SetErrorInfo(const char* format, ...);
	// --- 设置运行信息
	void SetRunInfo(char* pnfo);
	void SetRunInfo(const char* format, ...);
	//
	void GetRunInfo(ACE_CString& RunInfo);
	void GetErrorInfo(ACE_CString& ErrInfo);
	void ClearErrorInfo();

public:
	int	m_MsgType;				//命令号
	int	m_SubType;				//子命令号
	int IsError;				// --- 处理过程中用
	int m_IsUse;				//---是否在处理过程中
protected:
	ACE_CString m_ErrInfo;
	ACE_CString m_RunInfo;
	ACE_Thread_Mutex* m_pLock;
};

class SGNP_Export SGNP_TimerProc
{
public:
	//
	SGNP_TimerProc(ACE_UINT32 msec);
	virtual ~SGNP_TimerProc() {};

	void release() { delete this; }
	//
	virtual bool IsExpired(ACE_UINT32 factor);
	virtual void OnTimer() = 0;

	void Interval(ACE_UINT32 v) { msec_ = v; }
	ACE_UINT32 Interval() { return msec_; }

	//virtual void Signal(){ bsig_ = true; }

protected:
	//
	ACE_UINT32  msec_;	//
	ACE_UINT32  count_;
	//bool		bsig_;
};
//
class SGNP_Export SGNP_Timer :public ACE_Task<ACE_MT_SYNCH>
{
public:

	SGNP_Timer(ACE_UINT32 factor = 200); //200毫秒
	~SGNP_Timer();
	//
	void SetTimer(SGNP_TimerProc* pTimerProc);
	void KillTimer(SGNP_TimerProc* pTimerProc);
	//
	int open();
	int	close();
	//
protected:

	Handler_List<SGNP_TimerProc*> timerProcs_;
	bool stop_;
	ACE_UINT32 factor_;
	//
	virtual int svc();
};



template <class TLOCK >
class RefCountT
{
public:
	RefCountT() : m_ref(1), m_bNoDelete(false) {}
	virtual ~RefCountT() {}

	void AddRef()
	{
		++m_ref;
	}

	void Release()
	{
		if (--m_ref == 0 && !m_bNoDelete)
		{
			m_bNoDelete = true;
			delete this;
		}
	}

	int GetRefCount() const
	{
		return m_ref.value();
	}

	void SetNoDelete(bool b)
	{
		m_bNoDelete = b;
	}

protected:

	bool m_bNoDelete;
	ACE_Atomic_Op<TLOCK, long> m_ref;

private:

	RefCountT(const RefCountT&);
	RefCountT& operator=(const RefCountT&);
};
#ifdef WIN32
SGNP_TEMPLATE template class SGNP_Export RefCountT<ACE_Thread_Mutex>;
SGNP_TEMPLATE template class SGNP_Export RefCountT<ACE_Null_Mutex>;
#endif
typedef RefCountT<ACE_Thread_Mutex> RefCount;
typedef RefCountT<ACE_Null_Mutex> RefCountNoLock;

class SGNP_Export CReleaseAble
{
public:
	virtual ~CReleaseAble() {}
	virtual void release() { delete this; }
};

class SGNP_Export CNonCopy
{
protected:

	CNonCopy() { }
	~CNonCopy() { }

private:

	CNonCopy(const CNonCopy&);
	const CNonCopy& operator=(const CNonCopy&);
};

template <class T>
class CMyAutoPtr : public CNonCopy
{
public:
	CMyAutoPtr(T* p) : m_p(p) { };
	~CMyAutoPtr() { if (m_p) m_p->Release(); }
	T* operator -> () { return m_p; }
	T* get() { return m_p; }
	//
	bool operator == (T* p) const { return m_p == p; }
	bool operator != (T* p) const { return m_p != p; }
	bool operator ! () { return !m_p; }
protected:
	T* m_p;
};

class SGNP_Export SerializeBase
{
public:
	virtual ~SerializeBase() {}

	virtual int					buf_size() = 0;
	virtual void				serialize(CSgArchive&) = 0;

	virtual ACE_Message_Block* to_msg(int type);
	virtual void				to_msg(int type, ACE_Message_Block& msg);
	virtual void				from_msg(ACE_Message_Block* pmb);
};

struct SGNP_Export SG_LINKTYPE_EX : public SerializeBase
{
	//
	SG_LINKTYPE		lt_;
	int				node_id_;
	ACE_UINT16		heartbeatInterval_;		//单位s,发送给服务端，心跳间隔时间heartbeatInterval
	char			reserve[30];
	//
	SG_LINKTYPE_EX()
	{
		node_id_ = 0;
		heartbeatInterval_ = 0;
		memset(reserve, 0, sizeof(reserve));
	}
	void serialize(CSgArchive&);
	int buf_size() { return lt_.buf_size() + sizeof(int) + sizeof(reserve); }
};

#endif
