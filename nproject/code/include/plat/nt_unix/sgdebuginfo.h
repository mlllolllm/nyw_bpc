/*
	调试信息输出
*/

#ifndef SgDebugInfoPrint_INCLUDE
#define SgDebugInfoPrint_INCLUDE

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include "sgdataset.h"
#include "sgmicro.h"

//共享内存长度
#define OUTMESSAGE_SHARE_MEM_LEN		40960
//一个信息最大长度
#define ONE_MESSAGE_MAX_LEN				5000 //4096
//
#define FILE_MAP_WRITE      SECTION_MAP_WRITE

// --- 输出信息控制开关

struct _DATASET_DLL_EXPORT_ PrintControl{
	
	SG_BOOL m_OutFlag;		// --- 总控开关
	
	SG_BOOL m_SysRunInfo;	// --- 系统运行正常信息
	
	SG_BOOL m_SysRunError;	// --- 系统运行异常信息
	
	SG_BOOL m_SysEfficInfo;	// --- 系统运行效率检测信息
	
	SG_BOOL m_SysNetInfo;	// --- 系统运行网络信息
	
	SG_BOOL m_DbfAccessInfo;// --- 数据库访问信息
	
	SG_BOOL m_ProgramInfo;  // --- 系统程序流程检测信息 --- 开发用
};

//调试信息输出类

class _DATASET_DLL_EXPORT_ CSgDebugInfoPrint:public PrintControl
{
protected:
	
	CSgDebugInfoPrint();
public:
	
	~CSgDebugInfoPrint();

private:
	
	char * m_OutStr; //已改成局部变量,没有再使用,为程序版本兼容性,保留该变量
	
	void * hStdOut;                 // handle of share memory
	
	char  *pStdOut;                 // pointer of share memory

	char * m_pProcName;
//#ifndef WIN32
	CSgString m_OutFileName;
//#endif

public:
	
	void SetOutOn(){m_OutFlag=true;}
	
	void SetOutOff(){m_OutFlag=false;}
	
	SG_BOOL GetOutOn(){return m_OutFlag;}

	// --- 系统运行正常信息
	
	void PrintSysRunInfo(const char *format,...);
	// --- 系统运行异常信息
	
	void PrintSysRunError(const char *format,...);
	// --- 系统运行效率检测信息
	
	void PrintSysEfficInfo(const char *format,...);
	// --- 系统运行网络信息
	
	void PrintSysNetInfo(const char *format,...);
	// --- 系统程序流程检测信息 --- 开发用
	
	void PrintProgramInfo(const char *format,...);
	// --- 系统程序流程检测信息 --- 开发用
	
	void PrintDbfAccessInfo(const char *format,...);

//private:
	//void PrintOut(const char *format,...);

private:
	
	static CSgDebugInfoPrint*m_pInstance;
//#ifndef WIN32
	int PrintLog2File(char *OutInfo);
//#endif
public:
	
	static	CSgDebugInfoPrint* GetInstance();
	
	static  void  FreeInstance();
};

#define AfxDebugPrint	CSgDebugInfoPrint::GetInstance
#define AfxDebugInfo	AfxDebugPrint()->PrintSysRunInfo
#define AfxDebugError	AfxDebugPrint()->PrintSysRunError
#define AfxDebugEffic	AfxDebugPrint()->PrintSysEfficInfo
#define PUTDEBUG_INFO		1 //输出信息
#define PUTDEBUG_WARNING	2
#define PUTDEBUG_ERROR		3 //输出错误信息

void _DATASET_DLL_EXPORT_ RDP_PutDebug(unsigned char type,char *fmt,...);
void _DATASET_DLL_EXPORT_ RDP_FreeDebug( );

#endif
