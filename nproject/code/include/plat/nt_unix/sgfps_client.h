//**************************************************************************************************
//	File Publisher Service Client Support				�汾: 1.00.0000   ����: 2008-03-31 09:05
//	--------------------------------------------------------------------------------------------
//	�ļ���������ͻ���֧�ֽӿ�
//		<1>	�ļ�����������ӿڼ���װ�� ( IFileTransfer & FileTransferT & FileTransfer )
//		<2>	�ļ������������ӿڼ���װ�� ( IFileProvider & FileProviderT & FileProvider )
//		<3> �ļ�����������Ϣ�ӿڼ���װ�� ( IFileDatabase & FileDatabaseT & FileDatabase )
//	--------------------------------------------------------------------------------------------
//	Copyright (C) 2002 - 2008                       - All Rights Reserved
//**************************************************************************************************
#ifndef __SMART_GRID_FILE_PUBLISH_MANAGER_SERVICE_CLIENT_SUPPORT_INTERFACE_DECLARE_HEADER_H_FILE__
#define __SMART_GRID_FILE_PUBLISH_MANAGER_SERVICE_CLIENT_SUPPORT_INTERFACE_DECLARE_HEADER_H_FILE__

#include "sgconst.h"
//================================================================================================== 
#if defined( CORE_BUILD_DLL )
#	define FPS_Export ACE_Proper_Export_Flag
#else
#	define FPS_Export ACE_Proper_Import_Flag
#endif

//================================================================================================== 
#ifdef REFCLSID
#	define SG_SEQID CLSID&
#	define FPS_UUID CLSID
#endif

//================================================================================================== 
class ACE_Message_Block;
class ACE_Time_Value;
class CSgDataSet;
struct timeval;
//================================================================================================== 
//	ͷ�ļ��Ľӿڶ���
struct IFileIdentify;
struct IFileDocument;
struct IFileTransfer;
struct IFileProvider;
struct IFileDatabase;

//================================================================================================== 
//	�����ļ���ʶ�Ľṹ���ͱ�׼����ʽ���в�ͬ
struct FPS_SEQID { SG_UINT Data1; SG_USHORT Data2; SG_USHORT Data3; SG_UCHAR Data4[8]; };
typedef struct FPS_CHECK { SG_UINT Data[4]; } FPS_HASH , & SG_HASH , * const SG_PHASH ;

#ifndef SG_SEQID
#	define SG_SEQID FPS_SEQID &
#	define FPS_UUID FPS_SEQID
#endif
//================================================================================================== 
//	ȫ�ֵĹ����ӿ�,����һ���ļ����кţ���ʽΪ {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} �� 38 ���ַ�
FPS_Export SG_UINT CreateFileSequence(SG_PSTR szSequence, SG_UINT nLength, SG_UINT nVersion);

//================================================================================================== 
//	ȫ�ֵĹ����ӿ�,����һ���ļ����кţ���������ʽ���� 16 ���ֽ�
FPS_Export SG_UINT CreateSequenceCode(SG_SEQID szSequenceID, SG_UINT nVersion);

//================================================================================================== 
//	ȫ�ֵĹ����ӿ�,���ļ����кŵĶ����ƺ��ַ���֮����ת��
FPS_Export SG_UINT FileSequenceStr2ID(SG_SEQID rSeqID, SG_PCSTR szSequence, SG_UINT nLength);
FPS_Export SG_UINT FileSequenceID2Str(SG_SEQID rSeqID, SG_PSTR szSequence, SG_UINT nLength);

//================================================================================================== 
#ifndef FPS_METHOD
#	ifdef _WIN32
#		define FPS_METHOD(func) virtual SG_INT func
#		define FPS_IMPL(cls , func) SG_INT cls::func
#		define FPS_DEFINE(func) virtual SG_INT func
#	else
#		define FPS_METHOD(func) virtual SG_INT func
#		define FPS_IMPL(cls , func ) SG_INT cls::func
#		define FPS_DEFINE(func) virtual SG_INT func
#	endif
#endif

//==================================================================================================
//	��ö�ٶ�����ο����ݿ��ж�Ӧ�� GIS_SYS_FILE_PUBLISH_CATE_INFO �еĶ���
enum FileClassDefineInternational
{
	FCDI_Background_Maps	= 0x0000,	//	����ͼ
	FCDI_Work_Plan_Maps		= 0x0001,	//	�û����뷽��ͼ
	FCDI_Offline_Maps		= 0x0002,	//	����ͼ
	FCID_Design_Docs		= 0x0003,	//	����ĵ�
	FCDI_GIS_BUSINESS		= 0X0004,	//	�滮ҵ���ļ�

	FCID_WebService_File	= 0x270D,	//	WEB ����
	FCID_Except_Reporter	= 0x270E,	//	�������
	FCID_Online_Upgrader	= 0x270F,	//	��������
	FCID_Common_Archives	= 0x2710,	//	ͨ���ĵ�
	FCID_User_Class			= 0x2711,	//	�û����忪ʼ
};

enum FileOperationOption
{
	//==============================================================================================
	FOO_CLASS_TRANSFER		= 0x1000,	//	�ļ�������ص�

	FCT_ASYNC_TRANSFER		= 0x0001,	//	ʹ���첽��ʽ�����ļ�
	FCT_CALC_FILE_HASH		= 0x0002,	//	�����ļ��Ĺ�ϣ��
	FCT_SEARCH_PARENT		= 0x0004,	//	���ڱ�������������ļ��Ҳ�����Ҫ�������������Ѱ��
	FCT_SERVER_CACHE		= 0x0008,	//	����ļ��ǴӶ�������������ص��ģ��Ƿ񱾵ػ���
	FCT_LOCAL_CACHE			= 0x0010,	//	�ļ����غ��Ƿ񻺴浽���ؼ�����ϣ�
	FCT_SYNC_UPPER			= 0x0020,	//	����һ���ļ������������Ƿ�Ҫͬ�����ϼ�������
	FCT_SEND_SIZE			= 0x0040,	//	�����ļ�ʱ��ÿ�η��͵��������������λ���ֽ�
	FCT_COMPRESS			= 0x0080,	//	����ѹ���ȣ�0 Ϊ������ѹ������1 - 9 Ϊѹ��
	FCT_TIMEOUT				= 0x0100,	//	�����ļ�ʱ��ÿ�����ݵĳ�ʱʱ�䣬��λ����

	//==============================================================================================
	FOO_CLASS_PROVIDER		= 0x2000,	//	�ļ�������ص�

	FCP_STREAM_KEEK_ALIVE	= 0x0001,	//	�����������Ӳ��Ͽ���Ĭ��Ϊ������
	FCP_THREAD_POOL_COUNT	= 0x0002,	//	��̨�����̳߳��������������첽��������ǰ����

	FCP_ASYNCH_TASK_COUNT	= 0x0004,	//	��̨�첽�����������ֻ��ѡ�ֻ�ܻ�ȡ����������
};

struct FPS_CLASS_INFO
{
	SG_UINT nStrategy;		//	���ԣ��ο����Զ���
	SG_UINT nMaxLength;		//	�����ļ������ߴ�
	SG_UINT nMinLength;		//	�����ļ�����С�ߴ�
	SG_UINT nSpaceTotal;	//	����ռ���ܴ�С
	SG_UINT nCacheTotal;	//	�����ļ����ܸ���
	SG_UINT nNameSize;		//	���ƻ������Ĵ�С
	SG_UINT nPathSize;		//	·���������Ĵ�С
	SG_UINT nDescSize;		//	�����������Ĵ�С
	SG_PSTR lpStrName;		//	��������
	SG_PSTR lpStrPath;		//	����洢·������ΪĬ��·��
	SG_PSTR lpStrDesc;		//	��������
	SG_PSTR lpReserved;		//	��������������Ϊ 0
};

//================================================================================================== 
//	���Ҫʵ�� COM ��������Խ������滻Ϊ IUnknown
struct IInterfaceRoot
{
	FPS_METHOD( GetReference )() = 0;
	FPS_METHOD( DropInstance )() = 0;
};

//================================================================================================== 
//	�ص��ṩ�ߵĽӿ�
struct ICallbackOffer : public IInterfaceRoot
{
	//----------------------------------------------------------------------------------------------
	//	������
	//		�ص���֪ͨ�ӿ�
	//
	//	������
	//		nEvent		- [IN]	֪ͨ���¼����ô�����������
	//		iError		- [IN]	�������
	//		szError		- [IN]	��������
	//		pCaller		- [IN]	�û����������
	//		pDocument	- [IN]	�첽��������ʱ�������ĵ����������Ϊ NULL ���û���Ҫ�����ͷŶ���
	//
	//	���أ�
	//		������룬ϵͳ�������û����صĴ������
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Notify )( SG_UINT nEvent, SG_INT iError, SG_PCSTR szError, SG_PTR pCaller, IFileDocument* pDocument = NULL) = 0;
};

//================================================================================================== 
//	�쳣��Ϣ�ṩ���ӿ�
struct IExceptionInfo : public IInterfaceRoot
{
	FPS_METHOD( GetException )( SG_PINT pError , SG_PSTR pszError , SG_INT uLength ) = 0;
};

//==================================================================================================
//	�ļ���ŵ�ת���ӿ�
struct IFileIdentify : public IExceptionInfo
{
	FPS_METHOD( Create )( SG_PSTR szSequence , SG_UINT nLength = 39, SG_UINT nVersion = 0 ) = 0;
	FPS_METHOD( Create )( SG_SEQID rSequence , SG_UINT nVersion = 0 ) = 0;

	FPS_METHOD( ID2Str )( SG_PSTR szSequence , SG_UINT nLength, SG_SEQID rSequence ) = 0;
	FPS_METHOD( Str2ID )( SG_SEQID rSequence , SG_PCSTR szSequence , SG_UINT nLength = 39 ) = 0;
};

//================================================================================================== 
//	�ļ����ݵĻ��������
struct IFileDocument : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�ļ�����������
	//
	//	������
	//		rMessageBlock	- [OUT]	ѡ��ķ���
	//		pBuffer			- [OUT]	ѡ��ı��
	//		nLength			- [OUT]	ѡ���ֵ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetBuffer )( SG_PSTR & pBuffer , SG_UINT & nLength ) = 0;
	FPS_METHOD( GetBuffer )( ACE_Message_Block & rMessageBlock ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�ļ��ı༭����
	//
	//	������
	//		tvModify	- [OUT]	�ļ��ı༭����
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetModify )( ACE_Time_Value & tvModify ) = 0;
	FPS_METHOD( GetModify )( timeval & tvModify ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�ļ��� MD5 ��ϣУ����
	//
	//	������
	//		szHash		- [OUT]	ѡ��ķ���
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetHash )( SG_PSTR szHash ) = 0; 
	FPS_METHOD( GetHash )( SG_HASH szHash ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		���ļ��������ݻ����ݱ��浽�ļ�
	//
	//	������
	//		szFilePath	- [IN]	�ļ���·��
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Load )( SG_PCSTR szFilePath ) = 0;
	FPS_METHOD( Save )( SG_PCSTR szFilePath ) = 0;
};

//================================================================================================== 
//	�ļ�����������ӿ�
struct IFileTransfer : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	������
	//		���û��ȡ�ļ������ѡ��
	//
	//	������
	//		nClass		- [IN]	ѡ��ķ���
	//		nOption		- [IN]	ѡ��ı��
	//		nValue		- [IN]	ѡ���ֵ
	//		pValue		- [OUT] ѡ���ֵ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetOption )( SG_UINT nClass, SG_UINT nOption, SG_INT& nValue) = 0;
	FPS_METHOD( SetOption )( SG_UINT nClass, SG_UINT nOption, SG_INT& nValue) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		�����ļ�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı��룬֧�ֶ����ƺ��ַ������ָ�ʽ
	//		szHash		- [IN]	�ļ��Ĺ�ϣ���룬��ѡ
	//		uSize		- [IN]	�ļ��Ĵ�С
	//		pData		- [IN]	�ļ���������
	//		szFile		- [IN]	�����ļ�·��
	//		ptvEdit		- [IN]	�ļ��ı༭���ڣ���ѡ
	//		pDocument	- [OUT]	�ļ������ݹ�����ָ�룬�ýӿڱ��������˺�������
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_UINT uSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_UINT uSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_PCSTR szFile) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_PCSTR szFile) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		�����ļ�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı���
	//		szFile		- [IN]	�����ļ�·��
	//		szHash		- [I,O]	�ļ��Ĺ�ϣ���룬��ѡ
	//		uSize		- [OUT]	�ļ��Ĵ�С
	//		pData		- [OUT]	�ļ���������
	//		ptvEdit		- [OUT]	�ļ��ı༭���ڣ���ѡ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_UINT nSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_UINT nSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_PCSTR szFile) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_PCSTR szFile) = 0;
	
	//----------------------------------------------------------------------------------------------
	//	������
	//		�첽�����ļ�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı���
	//		szFile		- [IN]	�����ļ�·��
	//		szHash		- [IN]	�ļ��Ĺ�ϣ���룬��ѡ
	//		pDocument	- [OUT]	�ļ������ݹ�����ָ�룬ͬ����ʽͨ���ýӿڷ������ݸ��û�������Ϊ NULL
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//
	//	��ע��
	//		<1>	�ú������޸�ͬ�첽��־����������ͨ�����ᱻӰ�죬�ο� SetOption ����
	//		<2>	�ú������޸Ļص��ӿں��û��������������첽���ûᱻӰ�죬�ο� Callback ����
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, ICallbackOffer* pCallback, SG_PTR pUserData) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, ICallbackOffer* pCallback, SG_PTR pUserData) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		ͬ�������ļ�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı���
	//		szFile		- [IN]	�����ļ�·��
	//		szHash		- [IN]	�ļ��Ĺ�ϣ���룬��ѡ
	//		pDocument	- [OUT]	�ļ������ݹ�����ָ�룬ͬ����ʽͨ���ýӿڷ������ݸ��û�������Ϊ NULL
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//
	//	��ע��
	//		<1>	�ú������޸�ͬ�첽��־����������ͨ�����ᱻӰ�죬�ο� SetOption ����
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, IFileDocument* pDocument) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		ɾ���ļ�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı���
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Delete )( SG_UINT nClass, SG_PCSTR szID, SG_BOOL bDeleteParent) = 0;
	FPS_METHOD( Delete )( SG_UINT nClass, SG_SEQID szID, SG_BOOL bDeleteParent) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		���ûص��ӿ�
	//
	//	������
	//		lpCallback	- [IN]	�ص��ӿ�
	//		pUserData	- [IN]	�û������Ļص�����
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//
	//	��ע��
	//		<1>	�ص��ӿ�ֻ���첽��ʽ��Ч��һ����������ʹ�ã�ʹ�� NULL �ӿ�ȡ���ص��ӿڡ�
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Callback )( ICallbackOffer* lpCallback, SG_PTR pUserData = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ѯ�ļ���Ϣ
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı���
	//		szHash		- [OUT]	�ļ��Ĺ�ϣ����
	//		uSize		- [OUT]	�ļ��Ĵ�С
	//		ptvEdit		- [OUT]	�ļ��ı༭���ڣ���ѡ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( QueryInfo )( SG_UINT nClass, SG_PCSTR szID, SG_PSTR szHash, SG_UINT* pSize, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( QueryInfo )( SG_UINT nClass, SG_SEQID szID, SG_HASH szHash, SG_UINT* pSize, timeval* ptvEdit = NULL) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ѯ������Ϣ
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		rClassInfo	- [OUT]	�ļ�������Ϣ
	//		uFlags		- [IN]	��������
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( QueryClass )( SG_UINT nClass, FPS_CLASS_INFO & rClassInfo, SG_UINT uFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		�����ļ�����
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		rClassInfo	- [IN]	�ļ�������Ϣ
	//		uFlags		- [IN]	��������
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( CreateClass	)( SG_UINT nClass, FPS_CLASS_INFO & rClassInfo, SG_UINT uFlags = 0 ) = 0;
};

//================================================================================================== 
//	�ļ������������ӿ�
struct IFileProvider : public IFileTransfer
{
	//----------------------------------------------------------------------------------------------
	//	������
	//		ʹ��ָ���Ĳ�����ʼ�����ò���
	//
	//	������
	//		pszAddress	- [IN]	�������ĵ�ַ
	//		nThreads	- [IN]	�̳߳ص�����
	//		nFlags		- [IN]	��ʼ����־����ֵ����Ϊ 1 �����Զ���ʼ���������
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Initialize )( SG_PCSTR pszAddress = NULL, SG_UINT nThreads = 1, SG_UINT nFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ֹ�첽ִ����
	//
	//	������
	//		pszReserved	- [IN]	������������������Ϊ NULL 
	//		nFlags		- [IN]	��ʼ����־����ֵ����Ϊ 1 �����Զ���ʼ���������
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Terminate )( SG_PCSTR pszReserved = NULL, SG_UINT nFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ѯ����������Ϣ		
	//
	//	������
	//		nClass		- [IN]	��Ϣ����
	//		szValue		- [OUT]	��Ϣ����
	//		nSize		- [IN]	��Ϣ���ݻ�������С
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Information )( SG_UINT nClass, SG_PSTR szValue, SG_UINT nSize) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�������÷���������
	//
	//	������
	//		nClass	- [IN]	��������
	//		nOption	- [IN]	����ѡ��
	//		szValue	- [OUT]	ѡ������
	//		nSize	- [IN]	ѡ�����ݻ�������С
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( SetConfigure )( SG_UINT nClass, SG_UINT nOption, SG_PSTR szValue, SG_UINT nSize) = 0;
	FPS_METHOD( GetConfigure )( SG_UINT nClass, SG_UINT nOption, SG_PSTR szValue, SG_UINT nSize) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ѯͬ���ļ��б�
	//
	//	������
	//		nClass		- [IN]	�ļ��ķ���
	//		szID		- [IN]	�ļ��ı��룬��ѡ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	// FPS_METHOD( WaitSyncFile )( SG_UINT nClass, SG_PCSTR szID) = 0;
};

//================================================================================================== 
//	�ļ�����������Ϣ�ӿ�
struct IFileDatabase : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�������ļ�������Ϣ
	//
	//	������
	//		nClass	- [IN]	�ļ�����
	//		dsInfo	- [I/O]	������Ϣ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetClassInfo )( SG_UINT nClass, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetClassInfo )( SG_UINT nClass, CSgDataSet& dsInfo) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		��ȡ�������ļ���Ϣ
	//
	//	������
	//		nClass	- [IN]	�ļ�����
	//		szID	- [IN]	�ļ����
	//		dsInfo	- [I/O]	�ļ���Ϣ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetFileInfo )( SG_UINT nClass, SG_PCSTR szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( GetFileInfo )( SG_UINT nClass, SG_SEQID szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetFileInfo )( SG_UINT nClass, SG_PCSTR szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetFileInfo )( SG_UINT nClass, SG_SEQID szID, CSgDataSet& dsInfo) = 0;

	//----------------------------------------------------------------------------------------------
	//	������
	//		���÷��������Ϣ
	//
	//	������
	//		nClass		- [IN]	�ļ�����
	//		szName		- [IN]	��������
	//		szPath		- [IN]	����洢·��
	//		szComment	- [IN]	����������Ϣ
	//
	//	���أ�
	//		�����룬< 0 �����������󣬴���ԭ��ʹ�� GetException ��ȡ
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( SetClassInfo )( SG_UINT nClass, SG_PCSTR szName, SG_PCSTR szPath, SG_PCSTR szComment) = 0;
};

//==================================================================================================
//	�����ļ������������ؽӿ�
FPS_Export IFileIdentify * CreateFileIdentify( );
FPS_Export IFileDocument * CreateFileDocument( );
FPS_Export IFileTransfer * CreateFileTransfer( );
FPS_Export IFileProvider * CreateFileProvider( );
FPS_Export IFileDatabase * CreateFileDatabase( );

//==================================================================================================
//	�Խӿڽ��а�װ����
template < typename T > class WrapperT 
{
public:
	typedef T * PointerT; 
	WrapperT() : m_pWrapper(0) { }
	~WrapperT()	{ Release(); }

public:
	WrapperT( PointerT pWrapper )
	{
		m_pWrapper = pWrapper;
	}

public:
	void Attach( PointerT pWrapper )
	{
		Release();
		m_pWrapper = pWrapper;
	}

	PointerT Detach()
	{
		PointerT pWrapper = m_pWrapper;
		m_pWrapper = 0;
		return pWrapper;
	}

public:
	void Release()
	{
		if( m_pWrapper != 0 )
		{
			m_pWrapper->DropInstance();
			m_pWrapper = 0;
		}
	}

public:
	PointerT operator = ( PointerT pWrapper )
	{
		if( m_pWrapper ) m_pWrapper->DropInstance();
		if( pWrapper ) pWrapper->GetReference();
		return m_pWrapper = pWrapper;
	}

public:
	operator PointerT & () { return m_pWrapper; }
	PointerT operator -> () { return m_pWrapper; }
	bool operator ! () { return m_pWrapper == 0; }
	operator bool () { return m_pWrapper != 0; }

protected:
	PointerT m_pWrapper;
};

//==================================================================================================
// ��װ������Ͷ���
typedef WrapperT< IFileIdentify > FileIdentifyT;
typedef WrapperT< IFileDocument > FileDocumentT;
typedef WrapperT< IFileTransfer > FileTransferT;
typedef WrapperT< IFileProvider > FileProviderT;
typedef WrapperT< IFileDatabase > FileDatabaseT;

//==================================================================================================
// ����������Զ������ӿڰ�װ��
struct FileIdentify : public WrapperT< IFileIdentify > { FileIdentify( ); };
struct FileDocument : public WrapperT< IFileDocument > { FileDocument( ); };
struct FileTransfer : public WrapperT< IFileTransfer > { FileTransfer( ); };
struct FileProvider : public WrapperT< IFileProvider > { FileProvider( ); };
struct FileDatabase : public WrapperT< IFileDatabase > { FileDatabase( ); };

//==================================================================================================
inline FileIdentify::FileIdentify( ) { this->m_pWrapper = CreateFileIdentify( ); }
inline FileDocument::FileDocument( ) { this->m_pWrapper = CreateFileDocument( ); }
inline FileTransfer::FileTransfer( ) { this->m_pWrapper = CreateFileTransfer( ); }
inline FileProvider::FileProvider( ) { this->m_pWrapper = CreateFileProvider( ); }
inline FileDatabase::FileDatabase( ) { this->m_pWrapper = CreateFileDatabase( ); }

//==================================================================================================
#endif
