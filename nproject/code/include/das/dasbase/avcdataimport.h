#ifndef AVCDATAIMPORT_H_
#define AVCDATAIMPORT_H_
#include <vector>
#pragma once

#ifdef AVC_DLL 
#   define AVC_DLL_API ACE_Proper_Export_Flag
#else
#   define AVC_DLL_API ACE_Proper_Import_Flag
#endif


typedef struct MODEL_D_COMPENSATOR;

//AVC应用配置信息（AVC在DAS_CONFIG中的配置内容）
typedef struct AVC_CONFIG
{	
	bool avc_IsShortOptimConfirm;		//是否运行短时间尺度电压优化	 
	bool avc_IsShortOptimCycleConfirm;	//是否循环运行短时间尺度电压优化
	int avc_ShortOptimlCycleInterval;	//短时间尺度电压优化的循环运行时间间隔
	bool avc_IsLongOptimConfirm;		//是否运行长时间尺度电压优化
	bool avc_IsLongOptimCycleConfirm;	//是否循环运行长时间尺度电压优化
	int avc_LongOptimlCycleInterval;	//长时间尺度电压优化的循环运行时间间隔
	bool avc_IsConsiderCB;				//是否考虑电容器组

}AVC_CONFIG;

class AVC_DLL_API CAVCDataImport
{
public:
	CAVCDataImport();	
	~CAVCDataImport();

	void SetRDBSchemaHandler(int schemaHandler);

	//读模型表
	int ReadModels(std::vector<MODEL_D_COMPENSATOR> vCompensators);

	//读配置表
	int ReadConfig(std::vector<DAS_CONFIG> dasconfigs, AVC_CONFIG &avcConfig);

private:
	//内存库句柄
	int m_SchemaHandler;
};

#endif

