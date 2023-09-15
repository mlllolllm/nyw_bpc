#ifndef __HH_CCSERVICE_H__
#define __HH_CCSERVICE_H__
#include "sgnp_base.h"
#include "sgconst_cloud.h"
#include "sgservice.h"
#include "rdbmem.h"
class _RDP_REALDB_DLL_PORT CSgCalcService:public SG_Service
{
	SG_UINT64 m_RtDBSchemaHandler;
	SG_INT		m_LoadRtDBFlag;
public:
	CSgCalcService(const char *pSvcName,const char *pSvcDesc);
	virtual	~CSgCalcService();

protected:

	virtual int OnRun()=0;
	virtual int Init();
	virtual int FInit();
private:
	virtual void	Run(int argc, char**argv);
	int		LoadModule(int argc, char**argv);
	virtual void	Stop();
public:
	//��������ʱ���ã������������
	//window�²��� -d ��������  -i ����װ -u ����ж��
	//SchemaHandler=10001 ����ʵʱ��ʱ�ľ��
	//LoadType=0		 ����ʵʱ��ʱ�ļ������ͣ�ȱʡ��0
	//RtDBVer=2			����ʵʱ��ʱ��ʵʱ��汾�� ȱʡ��2
	//SrvType=3		����ʵʱ��ʱ��ʵʱ��������ͣ�û��ȱʡֵ�����봫��
	//SchemaDBNo=2  ����ʵʱ��ʱ��ʵʱ��� ȱʡ��1
	//Of_Substation=3��Of_Volt_Level=5�� ʵʱ������ʱ����Ҫ���õ�����滻������meta_rtdb_tblload�е�����
	virtual int		Start(int argc, char**argv);	
	//CalcProcType����meta_calc_procinfo�����õļ������ͣ����ݼ������ͣ���ȡʵʱ����ز���
	int LoadRtDBByPara(int CalcProcType, CSgString &ErrMsg);
	//��ȡʵʱ���SchemaHandler
	SG_UINT64 GetRtDBSchemaHandler();
	//����ʵʱ��SchemaHandler���������ã���ӳ������������л�ȡ
	int  SetRtDBSchemaHandler(SG_UINT64 	SchemaHanler);
	int GetStopFlag();
};

#endif