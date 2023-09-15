

#ifndef _FOLDERMANAGER_INCLUDE
#define _FOLDERMANAGER_INCLUDE

#include "sgnp_export.h"
//==================================================================================================
//	全局的目录管理类
class SGNP_Export FolderManager
{
public:
	//---------------------------------------------------------------------------------------------- 
	//	概述：
	//		获取当前应用的根目录
	//
	//	参数：
	//		szFolder	- [OUT]	根目录的全路径
	//		nLength		- [IN]	根目录的长度
	//
	//	返回：
	//		当前应用的根目录，等于零表明失败
	//---------------------------------------------------------------------------------------------- 
	static char * GetAppFolder(char * szFolder, int nLength = 260);

	//---------------------------------------------------------------------------------------------- 
	//	概述：
	//		获取当前应用特定的子目录
	//
	//	参数：
	//		szSubFolder	- [IN]	子目录的名称
	//		szFolder	- [OUT]	子目录的全路径
	//		nLength		- [IN]	根目录的长度
	//
	//	返回：
	//		子目录的全路径，等于零表明失败
	//---------------------------------------------------------------------------------------------- 
	static char * GetSubFolder(const char * szSubFolder, char * szFolder, int nLength = 260);

	//---------------------------------------------------------------------------------------------- 
	//	概述：
	//		获取当前应用特定的子目录
	//
	//	参数：
	//		szPath		- [IO]	目标路径
	//		szFile		- [IN]	附加的文件路径
	//		nMaxPath	- [IN]	目标路径的内存长度
	//
	//	返回：
	//		连接后的路径指针，等于零表明失败
	//---------------------------------------------------------------------------------------------- 
	static char * PathLinkPath(char * szPath , const char * szFile , int nMaxPath = 260);

public:
	//---------------------------------------------------------------------------------------------- 
	//	概述：
	//		获取当前应用特定子目录的函数族
	//
	//	返回：
	//		子目录的路径，等于零表明失败
	//---------------------------------------------------------------------------------------------- 
	static char * GetFolderBin(char * szFolder, int nLength = 260);
	static char * GetFolderBmp(char * szFolder, int nLength = 260);
	static char * GetFolderEtc(char * szFolder, int nLength = 260);
	static char * GetFolderLog(char * szFolder, int nLength = 260);
	static char * GetFolderLcf(char * szFolder, int nLength = 260);
	static char * GetFolderJava(char * szFolder, int nLength = 260);
};


namespace NpUtility
{
	int SGNP_Export GetProcessID(const char*lpszProcName, unsigned char IgnoreSelfFlag);
};
#endif
