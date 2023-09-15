/*
	������Ϣ���
*/

#ifndef SgDebugInfoPrint_INCLUDE
#define SgDebugInfoPrint_INCLUDE

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include "sgdataset.h"
#include "sgmicro.h"

//�����ڴ泤��
#define OUTMESSAGE_SHARE_MEM_LEN		40960
//һ����Ϣ��󳤶�
#define ONE_MESSAGE_MAX_LEN				5000 //4096
//
#define FILE_MAP_WRITE      SECTION_MAP_WRITE

// --- �����Ϣ���ƿ���

struct _DATASET_DLL_EXPORT_ PrintControl{
	
	SG_BOOL m_OutFlag;		// --- �ܿؿ���
	
	SG_BOOL m_SysRunInfo;	// --- ϵͳ����������Ϣ
	
	SG_BOOL m_SysRunError;	// --- ϵͳ�����쳣��Ϣ
	
	SG_BOOL m_SysEfficInfo;	// --- ϵͳ����Ч�ʼ����Ϣ
	
	SG_BOOL m_SysNetInfo;	// --- ϵͳ����������Ϣ
	
	SG_BOOL m_DbfAccessInfo;// --- ���ݿ������Ϣ
	
	SG_BOOL m_ProgramInfo;  // --- ϵͳ�������̼����Ϣ --- ������
};

//������Ϣ�����

class _DATASET_DLL_EXPORT_ CSgDebugInfoPrint:public PrintControl
{
protected:
	
	CSgDebugInfoPrint();
public:
	
	~CSgDebugInfoPrint();

private:
	
	char * m_OutStr; //�Ѹĳɾֲ�����,û����ʹ��,Ϊ����汾������,�����ñ���
	
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

	// --- ϵͳ����������Ϣ
	
	void PrintSysRunInfo(const char *format,...);
	// --- ϵͳ�����쳣��Ϣ
	
	void PrintSysRunError(const char *format,...);
	// --- ϵͳ����Ч�ʼ����Ϣ
	
	void PrintSysEfficInfo(const char *format,...);
	// --- ϵͳ����������Ϣ
	
	void PrintSysNetInfo(const char *format,...);
	// --- ϵͳ�������̼����Ϣ --- ������
	
	void PrintProgramInfo(const char *format,...);
	// --- ϵͳ�������̼����Ϣ --- ������
	
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
#define PUTDEBUG_INFO		1 //�����Ϣ
#define PUTDEBUG_WARNING	2
#define PUTDEBUG_ERROR		3 //���������Ϣ

void _DATASET_DLL_EXPORT_ RDP_PutDebug(unsigned char type,char *fmt,...);
void _DATASET_DLL_EXPORT_ RDP_FreeDebug( );

#endif
