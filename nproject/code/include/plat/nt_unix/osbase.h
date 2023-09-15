#ifndef __SG__OS_BASE__HHH
#define __SG__OS_BASE__HHH

#if ! defined( ACE_Proper_Export_Flag )
#   include "ace/config.h"
#endif

#if defined(_DATASET_DLL_)
#define _SG_OSBASE_DLL_PORT ACE_Proper_Export_Flag
#else
#define _SG_OSBASE_DLL_PORT ACE_Proper_Import_Flag
#endif

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "sgdataset.h"
#include "rdp_const.h"
//#include "sys_configenv.h"
#include <float.h>
#ifdef WIN32
#include <direct.h>
#include <io.h>
#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <dirent.h>
#include <strings.h>
#endif
#include "sgconst.h"
#include "sgnp_base.h"
#ifdef	RDP_USE_RW_LOCK
class ACE_RW_Thread_Mutex;
class ACE_RW_Process_Mutex;
#else
class ACE_Thread_Mutex;
class ACE_Process_Mutex;
#endif

typedef  unsigned int   SG_CriterionTime;	//从1970年1月1日到寻求时间的秒数
typedef struct S_SG_SHARE_MEMINFO
{
	int MemSize;
	int LastUsePID;
	int CrtPID;
	int AttchNum;
	SG_UINT AttachTime;
	SG_UINT DelTime;
	SG_UINT ChangeTime;
	S_SG_SHARE_MEMINFO()
	{
		Init();
	};
	int Init()
	{
		MemSize = LastUsePID = CrtPID = AttchNum = AttachTime = DelTime = ChangeTime = 0;
		return true;
	};
}S_SG_SHARE_MEMINFO;
//类：CSG_OS_ShareMem
//---------------------------------------------------------------------------
//以下是关于共享内存的类
//---------------------------------------------------------------------------
// CSG_OS_ShareMem	用于共享内存的创建、映射、删除等管理
//---------------------------------------------------------------------------
class _SG_OSBASE_DLL_PORT CSG_OS_ShareMem
{
//	unsigned char m_ShmType; //0:一般共享内存  1:和文件绑定的共享内存
	void * m_hMap;
public:
	int CheckShm(int shmkey);
	void *CreateShm(int  shmkey,size_t  shmlen, void *&pHMap);
#ifdef WIN32
	void * CreateShm(char *shmkey,size_t len, void *&pHMap);
	void *CreateAndMapping(char *shmkey,size_t  shmlen,void *&pHMap,int *createf=NULL);
	void *MappingShm(char *shmkey, void *&pHMap);
#endif
	void *GetHandle();
	void *MappingShm(int shmkey, void *&pHMap);
	int UnmapShm(void *shmaddr , void * handle);
	int DeleteShm(int ShMemKey,void *ShMemAddr, void *ShmHandle);
	int GetShmInfo(int ShMemKey, S_SG_SHARE_MEMINFO &ShMemInfo);
	void *CreateAndMapping(int shmkey,size_t  shmlen, void *&pHMap, int *createf=NULL);

};

//---------------------------------------------------------------------------
// CSG_OS_FileShareMem	用于共享内存的创建、映射、删除等管理
//---------------------------------------------------------------------------

class _SG_OSBASE_DLL_PORT CSG_OS_FileShareMem
{
	void * m_hMap;
	int m_ShmLen;
public:
	void *CreateShm(char *filename,int  shmkey,size_t  shmlen);
	void *MappingShm(char *filename,int shmkey,size_t *shmlen);
	int UnmapShm(void *shmaddr,size_t shmlen);
	void MemSync(void *shmaddr,size_t shmlen); //将内存->文件

};
/*
*----------------------------------------------------------------------------------------------------------------
*类   ：CSG_OS_FileCtrl用于操作本地文件
*----------------------------------------------------------------------------------------------------------------
*/
#define SG_OS_FILENAME_LEN 256

class 	 _SG_OSBASE_DLL_PORT CSG_OS_FileCtrl
{
	VECT_STRINT		m_FileNameArray;
public:
	CSG_OS_FileCtrl();
	~CSG_OS_FileCtrl();
	SG_INT64		GetFileLen(char *filename);
	int		DelFile(char *filename);
	int     GetFileTime(char *filename);
	int    FileRename(char *oldfile,char *newfile);
	int		CreatePath(char *pathname);
	int		DelPath(char *pathname);
	int		CopyFile(char *srcfile,char*desfile);
	int		SetFileTime(char *pFileName,int FileTime);
//----------------------------------------------------------------------------------------------------------------
//*查找目录下的文件 
//*pathname: 查找的目录
//*filenum:	目录下有多少个文件 outpara,具体名称通过GetFileName获得
//* ret: -1 出错  0 成功
//*----------------------------------------------------------------------------------------------------------------
	int		GetFileNameInPath(char *pathname,int *filenum,unsigned char HasPathFlag=false);
	//必须在GetFileNameInPath之后调用，fileno从0开始，返回为NULL无效
	char *GetFileName(int FileNo,unsigned char *pPathFlag=NULL);
};
#define PROCFILE_MAXNUM		5	// 处理同一个文件的最大次数
class _SG_OSBASE_DLL_PORT CErrFileProc
{
	std::map <std::string,int> m_FileList;
public:
	CErrFileProc();
	~CErrFileProc();
	short int DelFile(char *filename,unsigned char delflag=0);
	short int ReNameErrFile(char *filename,char *new_filename);
};

//进程控制类
#if defined( __linux ) || defined(__unix)
#define	END_PROC_SIGNAL		SIGKILL
#elif defined(WIN32)
#define END_PROC_SIGNAL		WM_CLOSE
#endif

class _SG_OSBASE_DLL_PORT CSG_OS_ProcCtrl
{
public:
	CSG_OS_ProcCtrl()
	{
	};
	~CSG_OS_ProcCtrl()
	{
	};
	//获取某个进程的ID
	int		GetProcID(char *ProcName,std::vector<int > *pPIDList=NULL);
	//杀死某个进程
	void	KillProc(char *ProcName,int ProcID=-1);
	void	KillProc(int ProcID);
	//获取运行进程的名称
	void	GetProcName(CSgString &ProcName);
};


//压缩类
#define  ZIP_BITS				15		
#define  ZIP_MAX_CODE			0x7fff
#define  ZIP_TABLE_SIZE			35023	
#define  ZIP_TABLE_BANKS		0x89
#define  ZIP_END_OF_STREAM		256
#define  ZIP_BUMP_CODE			257
#define  ZIP_FLUSH_CODE			258
#define  ZIP_FIRST_CODE			259
#define  ZIP_UNUSED				-1

#define  ZIP_COMPRESSMEMSIZE_FACTOR				16				
#define  ZIP_COMPRESSMEMADDSIZE_FACTOR			16				
#define  ZIP_EXPANDMEMSIZE_FACTOR				1				
#define  ZIP_EXPANDMEMADDSIZE_FACTOR			1				

#define  COMPRESS_OK		0
#define  COMPRESS_ERR		-1
#define  EXPAND_OK			0
#define  EXPAND_ERR			-1
#define  COMPRESS_KEY		0xEB90

#define  DATAISPRESSED 		1
#define  DATAUNPRESSED		0

typedef struct {
	char *stream;
	unsigned char mask;
	short int rack;
} SBIT_STREAM;


typedef struct {
	short int code_value;
	short int parent_code;
	char character;
} SDICTIONARY;

class _SG_OSBASE_DLL_PORT CSG_OS_ARJZip 
{
private:
	char decode_stack[ZIP_TABLE_SIZE];
	unsigned short int next_code;
	unsigned char  current_code_bits;
	unsigned short int next_bump_code;
	SDICTIONARY *dictp;
	SBIT_STREAM *tbit_out,*tbit_in;
	int   tbitout_maxsize;
	char  *tbitout_stream;
	int   toutput_maxsize;
	char  *toutput;
	
	void InitializeDictionary(void);
	SBIT_STREAM *InitializeCompress(int outputlen);
	unsigned short int find_child_node(unsigned short int parent_code, unsigned short int child_character);
	
	int OutputBits(SBIT_STREAM *bit_out,unsigned  int code,unsigned char bit_count,
		int inputLength,int *memsizep,char **output_firstp);
	SBIT_STREAM *InitializeExpand(char* input);
	unsigned short int decode_string(unsigned short int count,unsigned short int code);
	unsigned  int InputBits(SBIT_STREAM *bit_in,unsigned char bit_count);
	char *ziprealloc_bitoutstream(int cursize);
	char *ziprealloc_output(int cursize);
public:
	CSG_OS_ARJZip(void);
	~CSG_OS_ARJZip(void);
	//outputLengthp 无须调用者释放
	int CompressData(char *input,int inputLength,char **outputp,int *outputLengthp);
	int IsCompressData(char *input,int inputLength);
	int ExpandData(char *exinput,int exinputLength,char **outputp,int *outputLengthp);
};

//---------------------------------------------------------------------------
//以下是关于时间转换时间。时间读取的函数集合类
//	CSG_OS_Time  类
//---------------------------------------------------------------------------
typedef struct {
	unsigned short   year;
	unsigned char    month;
	unsigned char    day;
	unsigned char    wday;
	unsigned char    hour;
	unsigned char    minute;
	unsigned char    second;
	unsigned short   msecond;
}SSG_OS_CLOCK ;
typedef struct
{
	int ymd;
	int hms;
	unsigned short ms;
}SSG_OS_HCLOCK; //历史数据的时间结构

class _SG_OSBASE_DLL_PORT CSG_OS_Time 
{
public:
	//时间转换函数
	//把SG_CriterionTime转换为SSG_OS_CLOCK
	void	CovertTime		(SG_CriterionTime intime,SSG_OS_CLOCK  *clockp);

//	//把SSG_OS_CLOCK转换为SG_CriterionTime
	void	CovertClock		(SSG_OS_CLOCK  *clockp,SG_CriterionTime *intime);

		
	//把SG_CriterionTime转换为SSG_OS_HCLOCK
	void	CovertTime		(SG_CriterionTime intime,SSG_OS_HCLOCK  *hclockp);

	void CovertTime(SG_CriterionTime intime,SG_Date  *datep);
		
	//把SG_Date转换为SSG_OS_HCLOCK
	void	CovertDate		(SG_Date  *datep,SSG_OS_HCLOCK *hclockp);
	void	CovertDate(SG_Date  *date,SG_CriterionTime *intimep);
	
	//把SSG_OS_HCLOCK转换为SG_Date
	void	CovertHClock		(SSG_OS_HCLOCK *hclockp,SG_Date  *datep);
	void	CovertHClock		(SSG_OS_HCLOCK *hclockp,SG_CriterionTime *intimep);

	//把SSG_OS_CLOCK转换为天数 (从1970年1月1日子时计算)和分钟(从零点计算)
	void	CovertDayMins	(SSG_OS_CLOCK *clockp,int *days ,int * mins=0);
	
	//取得对应SSG_OS_CLOCK的分钟数(从1970年1月1日子时计算)
	void    CovertMinutes	(const SSG_OS_CLOCK *clockp,int *minutes);
	
	//取得对应分钟数(从1970年1月1日子时计算)SSG_OS_CLOCK
	void    CovertByMinutes	(const  int minutes , SSG_OS_CLOCK *clockp);
	
	//转换年、月、日为星期
	int		GetWeekDay	(int year,int month,int day);
	
	//以下几个函数用于读取系统当前时间，但以不同的方式表示
	void	GetNow(SG_UINT64 *pNowTime);
	void	GetNow		(SSG_OS_CLOCK  *curclockp);
	void	GetNow		(SG_Date   *curdatep);
	void	GetNow		(SG_CriterionTime  *intertimep,unsigned  short  *msecp=NULL);
	void	GetNow		(SG_Time   *curtimep);
	void	GetNow		(SSG_OS_HCLOCK   *curhclockp);
	int		SetSysTime(SG_CriterionTime  nowtime);
	//得到两个时间中有多少天
	int GetDayNums(SSG_OS_HCLOCK shclock,SSG_OS_HCLOCK ehclock);
	//取curdatep的下一天
	void    GetNextDay  (SSG_OS_HCLOCK  *curdatep);
	
	//取curdatep的上一天
	void    GetLastDay  (SG_Date  *curdatep);
	//取curdatep的下一天
	void    GetNextDay  (SG_Date  *curdatep);
	//取昨天
	void    GetYesterDay (SG_Date  *curdatep);
	//取明天
	void    GetTomorrow (SG_Date  *curdatep);
	
	//取得时间差，按秒计算
	int		GetInterval (SG_CriterionTime starttime,SG_CriterionTime endtime);
	int		GetInterval	(SSG_OS_CLOCK  *startclock,SSG_OS_CLOCK  *endclock);
	int		GetInterval	(SG_Time   *starttime,SG_Time  *endtime);
	
	//时间添加函数
	void	IncSecs 	(SSG_OS_CLOCK   *clockp,int  secs);
	void	IncDays 	(SSG_OS_CLOCK   *clockp,int  days);
	void	IncDays		(SG_Date    *clockp,int  days);
	//获取一个月有多少天
	int  GetMonthDays(int year,int month);
	
	//为字符串付上时间输出
	void	SetBufTime	(char *instr,char *outstr);
	
	//带时标打印输出
	void	Print		(char *printstr=NULL);
};
//#include "DllPortDef.h"

#define L_INC 16

typedef char **strtable;

#if defined __sun
#undef length
#endif

typedef int  (*IntFctPtr)(const void *, const void *);
typedef void (*VoidFctPtr)(...);
	
//---------------------------------------------------------------------------
//词法分析类：用于分析一行字符串中的各个单词
//---------------------------------------------------------------------------
#define  RDBLINE_MAX_WORD_LEN		4096

#define  RDBLINE_STRING_TYPE		0
#define  RDBLINE_NAME_TYPE			1
#define  RDBLINE_IDIGIT_TYPE		2
#define  RDBLINE_FDIGIT_TYPE		3
#define  RDBLINE_SYMBOL_TYPE		4

#define  RDBLINE_EOL_TYPE			254
#define  RDBLINE_ERROR				255

class _SG_OSBASE_DLL_PORT CWordAnalyse
{
	int		m_oldp;
	char *	m_pline;
	int		m_curp;
	int ChangeDigitFrom16To10(char *str16);
	int HexDigitValue(char char16);
		
public:
	char	m_word[RDBLINE_MAX_WORD_LEN];
	CWordAnalyse();
	CWordAnalyse(char *lp);
	void SetLine (char *lp);
	int GetCurPos() 
	{
		return m_curp;
	};
	void SetCurPos(int pos)
	{
		m_curp=pos;
	};
	int GetLastPos()
	{
		return m_oldp;
	}
	char *GetCurString()
	{
		return m_pline+m_curp;
	};
	int GetWord();
	int UngetWord();

};

class _SG_OSBASE_DLL_PORT CSG_OS_AutoMalloc
 {
	int  m_unitsize;
	int  m_maxnums;
	int  m_curnums;
	int  m_pernums;
	int  m_zerof;
	void *mem;
public :
	CSG_OS_AutoMalloc(int pn,int usize,int szerof=0);
	CSG_OS_AutoMalloc();
	~CSG_OS_AutoMalloc();
	void    SetPara (int pn,int usize,int szerof=0);
	void   *GetNextUnit ();
	int	  GetUnitNum (){return m_curnums;};
	void *  GetUnit(int sel);
	int     DelUnit(int sel);
	void   *GetMultUnit (int un);
	void   *GetMemInfo  (int *nums=NULL) {
		if(nums!=NULL)*nums=m_curnums;
		return(mem);
	};
	void   Zero ();
	void   FreeMem (); 
	};

class _DATASET_DLL_EXPORT_ CSG_OS_ProcessVar //每一个索引一个这样的实例
{
	// --- 线程读写锁
#ifdef	RDP_USE_RW_LOCK
	ACE_RW_Process_Mutex	*m_VarLock;
#else
	ACE_Process_Mutex	*m_VarLock;
#endif
	char m_LockName[512];
public:
	CSG_OS_ProcessVar(char *lockname);
	~CSG_OS_ProcessVar();
	// --- 锁控制方法
	void CreateLock();
	void LockRead();
	void LockWrite();
	void UnLock();
	SG_BOOL TryLockRead();
	SG_BOOL TryLockWrite();
};

class _DATASET_DLL_EXPORT_ CSG_OS_ProcessVarLock
{
public:
	CSG_OS_ProcessVarLock(CSG_OS_ProcessVar*p,SG_BOOL ReadLock=true);
	~CSG_OS_ProcessVarLock();
protected:
	CSG_OS_ProcessVar *pVarClass;
};
class ACE_RW_Thread_Mutex;

class _DATASET_DLL_EXPORT_ CSG_OS_ThreadVar //每一个索引一个这样的实例
{
	// --- 线程读写锁
/*#ifdef	RDP_USE_RW_LOCK
	ACE_RW_Thread_Mutex	*m_VarLock;
#else
	ACE_Thread_Mutex	*m_VarLock;
#endif
*/
	void *m_VarLock;
	unsigned char m_RWLockFlag;
public:
	CSG_OS_ThreadVar(unsigned char rwlock=0);
	~CSG_OS_ThreadVar();
	//设置锁的类型
	void SetRWLockFlag(SG_UCHAR RWLockFlag)
	{
		m_RWLockFlag=RWLockFlag;
	};
	// --- 锁控制方法
	void CreateLock();
	void LockRead();
	void LockWrite();
	void UnLock();
	SG_BOOL TryLockRead();
	SG_BOOL TryLockWrite();
};

class _DATASET_DLL_EXPORT_ CSG_OS_ThreadVarLock
{
public:
	CSG_OS_ThreadVarLock(CSG_OS_ThreadVar*p,SG_BOOL ReadLock=true);
	~CSG_OS_ThreadVarLock();
protected:
	CSG_OS_ThreadVar *pVarClass;
};
class _DATASET_DLL_EXPORT_ CSgLoadDllManager
{
	typedef	void *(FUNC_NEW_OPERSESSION)();
	typedef void (FUNC_DEL_OPERSESSION)(void *);
	typedef struct S_OPERSESSION_DLLINFO
	{
	//	string		DllName;
		void		*DllPt;
		FUNC_NEW_OPERSESSION *NewObjFunc;
		FUNC_DEL_OPERSESSION *DelObjFunc;
	}S_OPERSESSION_DLLINFO;
	typedef std::map<std::string, S_OPERSESSION_DLLINFO > MAP_STRING_DLLINFO;
	CSG_OS_ThreadVar    m_DllInfoLock;
	MAP_STRING_DLLINFO m_DllInfoList;
	CSgString m_NewFuncName;
	CSgString m_FreeFuncName;
	void FInit();
	SG_INT LoadDll(std::string &DllStr);
public:
	CSgLoadDllManager(char *pNewFuncName,char *pFreeFuncName);
	~CSgLoadDllManager();
	void *NewObj(char *pDllName);
	SG_INT DelObj(char *pDllName, void *pObj);
};


int _DATASET_DLL_EXPORT_ SG_OS_Sleep(int  msecs);
int _DATASET_DLL_EXPORT_ SG_OS_Sleep(int  secs,int  msecs);

#ifdef WIN32
typedef void *   SG_THREAD_HANDLE;
#else
typedef unsigned int    SG_THREAD_HANDLE;
#endif

//创建线程函数
typedef  void *(*SG_OS_PTHREAD_FUNC_DEF)(void *);

 _DATASET_DLL_EXPORT_  SG_THREAD_HANDLE SG_OS_CreateThread(SG_OS_PTHREAD_FUNC_DEF  pThreadFun,void *Argp,int StackSize /* =0 */);

int _DATASET_DLL_EXPORT_ SG_OS_EndThread(SG_THREAD_HANDLE threadid);
void _DATASET_DLL_EXPORT_ RDP_ToUpStr(char *p);
void _DATASET_DLL_EXPORT_ DelRightSpace(char *p);
void _DATASET_DLL_EXPORT_ DelLeftSpace(char *p);
int _DATASET_DLL_EXPORT_ MyGetLastError();

#endif //#ifndef __SG__OS_BASE__HHH
