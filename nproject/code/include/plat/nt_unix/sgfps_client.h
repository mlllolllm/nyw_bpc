//**************************************************************************************************
//	File Publisher Service Client Support				版本: 1.00.0000   日期: 2008-03-31 09:05
//	--------------------------------------------------------------------------------------------
//	文件发布服务客户端支持接口
//		<1>	文件发布服务传输接口及包装类 ( IFileTransfer & FileTransferT & FileTransfer )
//		<2>	文件发布服务管理接口及包装类 ( IFileProvider & FileProviderT & FileProvider )
//		<3> 文件发布数据信息接口及包装类 ( IFileDatabase & FileDatabaseT & FileDatabase )
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
//	头文件的接口定义
struct IFileIdentify;
struct IFileDocument;
struct IFileTransfer;
struct IFileProvider;
struct IFileDatabase;

//================================================================================================== 
//	定义文件标识的结构，和标准的形式稍有不同
struct FPS_SEQID { SG_UINT Data1; SG_USHORT Data2; SG_USHORT Data3; SG_UCHAR Data4[8]; };
typedef struct FPS_CHECK { SG_UINT Data[4]; } FPS_HASH , & SG_HASH , * const SG_PHASH ;

#ifndef SG_SEQID
#	define SG_SEQID FPS_SEQID &
#	define FPS_UUID FPS_SEQID
#endif
//================================================================================================== 
//	全局的公共接口,创建一个文件序列号，形式为 {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} 共 38 个字符
FPS_Export SG_UINT CreateFileSequence(SG_PSTR szSequence, SG_UINT nLength, SG_UINT nVersion);

//================================================================================================== 
//	全局的公共接口,创建一个文件序列号，二进制形式，共 16 个字节
FPS_Export SG_UINT CreateSequenceCode(SG_SEQID szSequenceID, SG_UINT nVersion);

//================================================================================================== 
//	全局的公共接口,将文件序列号的二进制和字符串之间做转换
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
//	该枚举定义请参考数据库中对应表 GIS_SYS_FILE_PUBLISH_CATE_INFO 中的定义
enum FileClassDefineInternational
{
	FCDI_Background_Maps	= 0x0000,	//	背景图
	FCDI_Work_Plan_Maps		= 0x0001,	//	用户接入方案图
	FCDI_Offline_Maps		= 0x0002,	//	离线图
	FCID_Design_Docs		= 0x0003,	//	设计文档
	FCDI_GIS_BUSINESS		= 0X0004,	//	规划业务文件

	FCID_WebService_File	= 0x270D,	//	WEB 服务
	FCID_Except_Reporter	= 0x270E,	//	错误输出
	FCID_Online_Upgrader	= 0x270F,	//	在线升级
	FCID_Common_Archives	= 0x2710,	//	通用文档
	FCID_User_Class			= 0x2711,	//	用户定义开始
};

enum FileOperationOption
{
	//==============================================================================================
	FOO_CLASS_TRANSFER		= 0x1000,	//	文件传输相关的

	FCT_ASYNC_TRANSFER		= 0x0001,	//	使用异步方式下载文件
	FCT_CALC_FILE_HASH		= 0x0002,	//	计算文件的哈希，
	FCT_SEARCH_PARENT		= 0x0004,	//	仅在本地搜索，如果文件找不到不要到顶层服务器上寻找
	FCT_SERVER_CACHE		= 0x0008,	//	如果文件是从顶层服务器上下载到的，是否本地缓存
	FCT_LOCAL_CACHE			= 0x0010,	//	文件下载后是否缓存到本地计算机上，
	FCT_SYNC_UPPER			= 0x0020,	//	发布一个文件到服务器后，是否要同步到上级服务器
	FCT_SEND_SIZE			= 0x0040,	//	发布文件时，每次发送的最大数据量，单位：字节
	FCT_COMPRESS			= 0x0080,	//	数据压缩比，0 为不进行压缩处理，1 - 9 为压缩
	FCT_TIMEOUT				= 0x0100,	//	发布文件时，每兆数据的超时时间，单位：秒

	//==============================================================================================
	FOO_CLASS_PROVIDER		= 0x2000,	//	文件服务相关的

	FCP_STREAM_KEEK_ALIVE	= 0x0001,	//	保持网络连接不断开，默认为长连接
	FCP_THREAD_POOL_COUNT	= 0x0002,	//	后台服务线程池数量，必须在异步任务启动前设置

	FCP_ASYNCH_TASK_COUNT	= 0x0004,	//	后台异步任务的数量，只读选项：只能获取而不能设置
};

struct FPS_CLASS_INFO
{
	SG_UINT nStrategy;		//	策略，参考策略定义
	SG_UINT nMaxLength;		//	缓存文件的最大尺寸
	SG_UINT nMinLength;		//	缓存文件的最小尺寸
	SG_UINT nSpaceTotal;	//	缓存空间的总大小
	SG_UINT nCacheTotal;	//	缓存文件的总个数
	SG_UINT nNameSize;		//	名称缓冲区的大小
	SG_UINT nPathSize;		//	路径缓冲区的大小
	SG_UINT nDescSize;		//	描述缓冲区的大小
	SG_PSTR lpStrName;		//	分类名称
	SG_PSTR lpStrPath;		//	分类存储路径，空为默认路径
	SG_PSTR lpStrDesc;		//	分类描述
	SG_PSTR lpReserved;		//	保留，必须设置为 0
};

//================================================================================================== 
//	如果要实现 COM 组件，可以将该类替换为 IUnknown
struct IInterfaceRoot
{
	FPS_METHOD( GetReference )() = 0;
	FPS_METHOD( DropInstance )() = 0;
};

//================================================================================================== 
//	回调提供者的接口
struct ICallbackOffer : public IInterfaceRoot
{
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		回调的通知接口
	//
	//	参数：
	//		nEvent		- [IN]	通知的事件，该处是网络命令
	//		iError		- [IN]	错误编码
	//		szError		- [IN]	错误描述
	//		pCaller		- [IN]	用户输入的数据
	//		pDocument	- [IN]	异步下载数据时给出的文档对象，如果不为 NULL ，用户需要复制释放对象
	//
	//	返回：
	//		错误编码，系统不关心用户返回的错误编码
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Notify )( SG_UINT nEvent, SG_INT iError, SG_PCSTR szError, SG_PTR pCaller, IFileDocument* pDocument = NULL) = 0;
};

//================================================================================================== 
//	异常信息提供基接口
struct IExceptionInfo : public IInterfaceRoot
{
	FPS_METHOD( GetException )( SG_PINT pError , SG_PSTR pszError , SG_INT uLength ) = 0;
};

//==================================================================================================
//	文件编号的转换接口
struct IFileIdentify : public IExceptionInfo
{
	FPS_METHOD( Create )( SG_PSTR szSequence , SG_UINT nLength = 39, SG_UINT nVersion = 0 ) = 0;
	FPS_METHOD( Create )( SG_SEQID rSequence , SG_UINT nVersion = 0 ) = 0;

	FPS_METHOD( ID2Str )( SG_PSTR szSequence , SG_UINT nLength, SG_SEQID rSequence ) = 0;
	FPS_METHOD( Str2ID )( SG_SEQID rSequence , SG_PCSTR szSequence , SG_UINT nLength = 39 ) = 0;
};

//================================================================================================== 
//	文件数据的缓冲管理器
struct IFileDocument : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取文件的数据内容
	//
	//	参数：
	//		rMessageBlock	- [OUT]	选项的分类
	//		pBuffer			- [OUT]	选项的编号
	//		nLength			- [OUT]	选项的值
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetBuffer )( SG_PSTR & pBuffer , SG_UINT & nLength ) = 0;
	FPS_METHOD( GetBuffer )( ACE_Message_Block & rMessageBlock ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取文件的编辑日期
	//
	//	参数：
	//		tvModify	- [OUT]	文件的编辑日期
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetModify )( ACE_Time_Value & tvModify ) = 0;
	FPS_METHOD( GetModify )( timeval & tvModify ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取文件的 MD5 哈希校验码
	//
	//	参数：
	//		szHash		- [OUT]	选项的分类
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetHash )( SG_PSTR szHash ) = 0; 
	FPS_METHOD( GetHash )( SG_HASH szHash ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		从文件加载数据或将数据保存到文件
	//
	//	参数：
	//		szFilePath	- [IN]	文件的路径
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Load )( SG_PCSTR szFilePath ) = 0;
	FPS_METHOD( Save )( SG_PCSTR szFilePath ) = 0;
};

//================================================================================================== 
//	文件发布服务传输接口
struct IFileTransfer : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		设置或获取文件传输的选项
	//
	//	参数：
	//		nClass		- [IN]	选项的分类
	//		nOption		- [IN]	选项的编号
	//		nValue		- [IN]	选项的值
	//		pValue		- [OUT] 选项的值
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetOption )( SG_UINT nClass, SG_UINT nOption, SG_INT& nValue) = 0;
	FPS_METHOD( SetOption )( SG_UINT nClass, SG_UINT nOption, SG_INT& nValue) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		发布文件
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码，支持二进制和字符串两种格式
	//		szHash		- [IN]	文件的哈希编码，可选
	//		uSize		- [IN]	文件的大小
	//		pData		- [IN]	文件数据内容
	//		szFile		- [IN]	磁盘文件路径
	//		ptvEdit		- [IN]	文件的编辑日期，可选
	//		pDocument	- [OUT]	文件的数据管理器指针，该接口必须设置了好了数据
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_UINT uSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_UINT uSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_PCSTR szFile) = 0;
	FPS_METHOD( Publish )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_PCSTR szFile) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		下载文件
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码
	//		szFile		- [IN]	磁盘文件路径
	//		szHash		- [I,O]	文件的哈希编码，可选
	//		uSize		- [OUT]	文件的大小
	//		pData		- [OUT]	文件数据内容
	//		ptvEdit		- [OUT]	文件的编辑日期，可选
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_UINT nSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_UINT nSize, SG_PTR pData, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, SG_PCSTR szFile) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, SG_PCSTR szFile) = 0;
	
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		异步下载文件
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码
	//		szFile		- [IN]	磁盘文件路径
	//		szHash		- [IN]	文件的哈希编码，可选
	//		pDocument	- [OUT]	文件的数据管理器指针，同步方式通过该接口返回数据给用户，不能为 NULL
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//
	//	备注：
	//		<1>	该函数会修改同异步标志，后续的普通函数会被影响，参考 SetOption 函数
	//		<2>	该函数会修改回调接口和用户参数，后续的异步调用会被影响，参考 Callback 函数
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, ICallbackOffer* pCallback, SG_PTR pUserData) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, ICallbackOffer* pCallback, SG_PTR pUserData) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		同步下载文件
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码
	//		szFile		- [IN]	磁盘文件路径
	//		szHash		- [IN]	文件的哈希编码，可选
	//		pDocument	- [OUT]	文件的数据管理器指针，同步方式通过该接口返回数据给用户，不能为 NULL
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//
	//	备注：
	//		<1>	该函数会修改同异步标志，后续的普通函数会被影响，参考 SetOption 函数
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Download )( SG_UINT nClass, SG_PCSTR szID, SG_PCSTR szHash, IFileDocument* pDocument) = 0;
	FPS_METHOD( Download )( SG_UINT nClass, SG_SEQID szID, SG_PHASH szHash, IFileDocument* pDocument) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		删除文件
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Delete )( SG_UINT nClass, SG_PCSTR szID, SG_BOOL bDeleteParent) = 0;
	FPS_METHOD( Delete )( SG_UINT nClass, SG_SEQID szID, SG_BOOL bDeleteParent) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		设置回调接口
	//
	//	参数：
	//		lpCallback	- [IN]	回调接口
	//		pUserData	- [IN]	用户给出的回调数据
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//
	//	备注：
	//		<1>	回调接口只对异步方式有效，一次设置永久使用，使用 NULL 接口取消回调接口。
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Callback )( ICallbackOffer* lpCallback, SG_PTR pUserData = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		查询文件信息
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码
	//		szHash		- [OUT]	文件的哈希编码
	//		uSize		- [OUT]	文件的大小
	//		ptvEdit		- [OUT]	文件的编辑日期，可选
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( QueryInfo )( SG_UINT nClass, SG_PCSTR szID, SG_PSTR szHash, SG_UINT* pSize, timeval* ptvEdit = NULL) = 0;
	FPS_METHOD( QueryInfo )( SG_UINT nClass, SG_SEQID szID, SG_HASH szHash, SG_UINT* pSize, timeval* ptvEdit = NULL) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		查询分类信息
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		rClassInfo	- [OUT]	文件分类信息
	//		uFlags		- [IN]	保留参数
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( QueryClass )( SG_UINT nClass, FPS_CLASS_INFO & rClassInfo, SG_UINT uFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		创建文件分类
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		rClassInfo	- [IN]	文件分类信息
	//		uFlags		- [IN]	保留参数
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( CreateClass	)( SG_UINT nClass, FPS_CLASS_INFO & rClassInfo, SG_UINT uFlags = 0 ) = 0;
};

//================================================================================================== 
//	文件发布服务管理接口
struct IFileProvider : public IFileTransfer
{
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		使用指定的参数初始化内置参数
	//
	//	参数：
	//		pszAddress	- [IN]	服务器的地址
	//		nThreads	- [IN]	线程池的数量
	//		nFlags		- [IN]	初始化标志，该值设置为 1 可以自动初始化网络代理
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Initialize )( SG_PCSTR pszAddress = NULL, SG_UINT nThreads = 1, SG_UINT nFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		终止异步执行器
	//
	//	参数：
	//		pszReserved	- [IN]	保留参数，必须设置为 NULL 
	//		nFlags		- [IN]	初始化标志，该值设置为 1 可以自动初始化网络代理
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Terminate )( SG_PCSTR pszReserved = NULL, SG_UINT nFlags = 0 ) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		查询服务器的信息		
	//
	//	参数：
	//		nClass		- [IN]	信息分类
	//		szValue		- [OUT]	信息内容
	//		nSize		- [IN]	信息内容缓冲区大小
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( Information )( SG_UINT nClass, SG_PSTR szValue, SG_UINT nSize) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取或者设置服务器参数
	//
	//	参数：
	//		nClass	- [IN]	参数分类
	//		nOption	- [IN]	参数选项
	//		szValue	- [OUT]	选项内容
	//		nSize	- [IN]	选项内容缓冲区大小
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( SetConfigure )( SG_UINT nClass, SG_UINT nOption, SG_PSTR szValue, SG_UINT nSize) = 0;
	FPS_METHOD( GetConfigure )( SG_UINT nClass, SG_UINT nOption, SG_PSTR szValue, SG_UINT nSize) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		查询同步文件列表
	//
	//	参数：
	//		nClass		- [IN]	文件的分类
	//		szID		- [IN]	文件的编码，可选
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	// FPS_METHOD( WaitSyncFile )( SG_UINT nClass, SG_PCSTR szID) = 0;
};

//================================================================================================== 
//	文件发布数据信息接口
struct IFileDatabase : public IExceptionInfo
{
	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取或设置文件分类信息
	//
	//	参数：
	//		nClass	- [IN]	文件分类
	//		dsInfo	- [I/O]	分类信息
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetClassInfo )( SG_UINT nClass, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetClassInfo )( SG_UINT nClass, CSgDataSet& dsInfo) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		获取或设置文件信息
	//
	//	参数：
	//		nClass	- [IN]	文件分类
	//		szID	- [IN]	文件编号
	//		dsInfo	- [I/O]	文件信息
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( GetFileInfo )( SG_UINT nClass, SG_PCSTR szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( GetFileInfo )( SG_UINT nClass, SG_SEQID szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetFileInfo )( SG_UINT nClass, SG_PCSTR szID, CSgDataSet& dsInfo) = 0;
	FPS_METHOD( SetFileInfo )( SG_UINT nClass, SG_SEQID szID, CSgDataSet& dsInfo) = 0;

	//----------------------------------------------------------------------------------------------
	//	概述：
	//		设置分类基本信息
	//
	//	参数：
	//		nClass		- [IN]	文件分类
	//		szName		- [IN]	分类名称
	//		szPath		- [IN]	分类存储路径
	//		szComment	- [IN]	分类描述信息
	//
	//	返回：
	//		错误码，< 0 表明发生错误，错误原因使用 GetException 获取
	//----------------------------------------------------------------------------------------------
	FPS_METHOD( SetClassInfo )( SG_UINT nClass, SG_PCSTR szName, SG_PCSTR szPath, SG_PCSTR szComment) = 0;
};

//==================================================================================================
//	创建文件发布服务的相关接口
FPS_Export IFileIdentify * CreateFileIdentify( );
FPS_Export IFileDocument * CreateFileDocument( );
FPS_Export IFileTransfer * CreateFileTransfer( );
FPS_Export IFileProvider * CreateFileProvider( );
FPS_Export IFileDatabase * CreateFileDatabase( );

//==================================================================================================
//	对接口进行包装的类
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
// 包装类的类型定义
typedef WrapperT< IFileIdentify > FileIdentifyT;
typedef WrapperT< IFileDocument > FileDocumentT;
typedef WrapperT< IFileTransfer > FileTransferT;
typedef WrapperT< IFileProvider > FileProviderT;
typedef WrapperT< IFileDatabase > FileDatabaseT;

//==================================================================================================
// 声明对象后自动创建接口包装类
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
