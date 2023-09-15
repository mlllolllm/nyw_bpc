#ifndef DASBASE_H_
#define DASBASE_H_
#include "ACE_Includes.h"
#pragma once

#ifdef DASBASE_DLL 
#   define DASBASE_DLL_API ACE_Proper_Export_Flag
#else
#   define DASBASE_DLL_API ACE_Proper_Import_Flag
#endif

#define TABLENAME_CODEVALUE		"plat.meta_code_value"
#define TABLENAME_DASCONFIG		"dev.das_config"

class CRDBLoadSetting;
typedef struct DAS_CONFIG;
typedef struct DAS_LOG;

class DASBASE_DLL_API CDasBase
{
public:
	CDasBase();
	CDasBase(int appID, const char* appCode=NULL);
	~CDasBase();

	//创建或映射实时库
	//schemaHandler < 0 不创建实时库，0 <= schemaHandler <= 1000, 创建常驻内存实时库， schemaHandler > 1000创建非常驻内存实时库
	//常驻内存实时库配置到rdbcfg.ini, 创建汇聚库, 非常驻内存的, 自己配置LoadSetting
	bool Init(int schemaHandler, CRDBLoadSetting *pLoadSetting = NULL);

	//计算
	virtual void Exec() = 0;

	//读配置表
	virtual int ReadConfig() = 0;

	//读模型表等
	virtual int Read() = 0;

	//写结果表
	virtual int Write() = 0;
	
	//读取应用的配置信息
	void ReadDasConfig(std::vector<DAS_CONFIG>& configs);

	//写应用日志表
	//void SaveLog(DAS_LOG log);
	//void SaveLog(std::vector<DAS_LOG> & logs);
	void SaveLog(std::string text);
	void SaveLog(std::vector<std::string>& texts);

protected:

	//内存库句柄
	int m_SchemaHandler;
	//应用ID
	int m_AppID;
	//应用代码
	char m_AppCode[64];

private:
    bool GetAppCode();
};

#endif
