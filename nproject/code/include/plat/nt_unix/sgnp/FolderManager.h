

#ifndef _FOLDERMANAGER_INCLUDE
#define _FOLDERMANAGER_INCLUDE

#include "sgnp_export.h"
//==================================================================================================
//	ȫ�ֵ�Ŀ¼������
class SGNP_Export FolderManager
{
public:
	//---------------------------------------------------------------------------------------------- 
	//	������
	//		��ȡ��ǰӦ�õĸ�Ŀ¼
	//
	//	������
	//		szFolder	- [OUT]	��Ŀ¼��ȫ·��
	//		nLength		- [IN]	��Ŀ¼�ĳ���
	//
	//	���أ�
	//		��ǰӦ�õĸ�Ŀ¼�����������ʧ��
	//---------------------------------------------------------------------------------------------- 
	static char * GetAppFolder(char * szFolder, int nLength = 260);

	//---------------------------------------------------------------------------------------------- 
	//	������
	//		��ȡ��ǰӦ���ض�����Ŀ¼
	//
	//	������
	//		szSubFolder	- [IN]	��Ŀ¼������
	//		szFolder	- [OUT]	��Ŀ¼��ȫ·��
	//		nLength		- [IN]	��Ŀ¼�ĳ���
	//
	//	���أ�
	//		��Ŀ¼��ȫ·�������������ʧ��
	//---------------------------------------------------------------------------------------------- 
	static char * GetSubFolder(const char * szSubFolder, char * szFolder, int nLength = 260);

	//---------------------------------------------------------------------------------------------- 
	//	������
	//		��ȡ��ǰӦ���ض�����Ŀ¼
	//
	//	������
	//		szPath		- [IO]	Ŀ��·��
	//		szFile		- [IN]	���ӵ��ļ�·��
	//		nMaxPath	- [IN]	Ŀ��·�����ڴ泤��
	//
	//	���أ�
	//		���Ӻ��·��ָ�룬���������ʧ��
	//---------------------------------------------------------------------------------------------- 
	static char * PathLinkPath(char * szPath , const char * szFile , int nMaxPath = 260);

public:
	//---------------------------------------------------------------------------------------------- 
	//	������
	//		��ȡ��ǰӦ���ض���Ŀ¼�ĺ�����
	//
	//	���أ�
	//		��Ŀ¼��·�������������ʧ��
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
