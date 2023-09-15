// configfile.h
#if !defined(_SG_CONFIG_ENV_H_)
#define _SG_CONFIG_ENV_H_
#ifndef	PASS_PATH_DEF
//通用
#define	 SGGIS_ROOT_PATH			"SGHOME"
//网络中用
#define		SG_HOME_ENV			 SGGIS_ROOT_PATH
#define		SG_FILE_ENV			 SGGIS_ROOT_PATH
//SCADA中用
#define		SG_HOMEPATH			 SGGIS_ROOT_PATH

#endif
#endif /* _SG_CONFIG_ENV_H_ */

#ifndef __SG_SYSTEM_ENVIRONMENT_DEFINE__
#define __SG_SYSTEM_ENVIRONMENT_DEFINE__

// 配置项目的定义
#define SECT_SYS_ENV				"系统环境"

// 关键字的定义
#define KEY_DATABASE				"数据库"


#endif//__SG_SYSTEM_ENVIRONMENT_DEFINE__