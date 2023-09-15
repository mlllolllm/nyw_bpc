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
	//程序启动时调用，传入参数解析
	//window下参数 -d 调试启动  -i 服务安装 -u 服务卸载
	//SchemaHandler=10001 启动实时库时的句柄
	//LoadType=0		 启动实时库时的加载类型，缺省是0
	//RtDBVer=2			启动实时库时的实时库版本号 缺省是2
	//SrvType=3		启动实时库时的实时库服务类型，没有缺省值，必须传入
	//SchemaDBNo=2  启动实时库时的实时库号 缺省是1
	//Of_Substation=3、Of_Volt_Level=5等 实时库表加载时，需要配置的相关替换项，具体见meta_rtdb_tblload中的配置
	virtual int		Start(int argc, char**argv);	
	//CalcProcType，在meta_calc_procinfo中配置的计算类型，根据计算类型，获取实时库加载参数
	int LoadRtDBByPara(int CalcProcType, CSgString &ErrMsg);
	//获取实时库的SchemaHandler
	SG_UINT64 GetRtDBSchemaHandler();
	//设置实时库SchemaHandler，若不设置，则从程序启动参数中获取
	int  SetRtDBSchemaHandler(SG_UINT64 	SchemaHanler);
	int GetStopFlag();
};

#endif