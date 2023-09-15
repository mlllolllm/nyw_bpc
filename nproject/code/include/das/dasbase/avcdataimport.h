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

//AVCӦ��������Ϣ��AVC��DAS_CONFIG�е��������ݣ�
typedef struct AVC_CONFIG
{	
	bool avc_IsShortOptimConfirm;		//�Ƿ����ж�ʱ��߶ȵ�ѹ�Ż�	 
	bool avc_IsShortOptimCycleConfirm;	//�Ƿ�ѭ�����ж�ʱ��߶ȵ�ѹ�Ż�
	int avc_ShortOptimlCycleInterval;	//��ʱ��߶ȵ�ѹ�Ż���ѭ������ʱ����
	bool avc_IsLongOptimConfirm;		//�Ƿ����г�ʱ��߶ȵ�ѹ�Ż�
	bool avc_IsLongOptimCycleConfirm;	//�Ƿ�ѭ�����г�ʱ��߶ȵ�ѹ�Ż�
	int avc_LongOptimlCycleInterval;	//��ʱ��߶ȵ�ѹ�Ż���ѭ������ʱ����
	bool avc_IsConsiderCB;				//�Ƿ��ǵ�������

}AVC_CONFIG;

class AVC_DLL_API CAVCDataImport
{
public:
	CAVCDataImport();	
	~CAVCDataImport();

	void SetRDBSchemaHandler(int schemaHandler);

	//��ģ�ͱ�
	int ReadModels(std::vector<MODEL_D_COMPENSATOR> vCompensators);

	//�����ñ�
	int ReadConfig(std::vector<DAS_CONFIG> dasconfigs, AVC_CONFIG &avcConfig);

private:
	//�ڴ����
	int m_SchemaHandler;
};

#endif

