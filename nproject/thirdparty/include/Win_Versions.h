//==============================================================================
//  Summary:
//      Windows Platform Version Definition Header
//  -------------------------------------------------------------------------
//  Author: WonKerr             Version: 1.00.000           Date: 2013-11-07
//==============================================================================

#ifndef __WINDOWS_PLATFORM_VERSION_DEFINITION_HEADER__
#define __WINDOWS_PLATFORM_VERSION_DEFINITION_HEADER__

//==============================================================================

#if defined( WIN32 ) || defined( _WIN32 ) || defined( _MSC_VER )
//==============================================================================
#if ! defined( _ATL_CSTRING_EXPLICIT_CONSTRUCTORS )
#   define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS // 某些 CString 构造函数将是显式的
#endif /* _ATL_CSTRING_EXPLICIT_CONSTRUCTORS */

//==============================================================================
#if ! defined( _AFX_ALL_WARNINGS )
#   define _AFX_ALL_WARNINGS // 关闭对某些常见但经常可放心忽略的警告消息的隐藏
#endif /* _AFX_ALL_WARNINGS */

//==============================================================================
#if ! defined( _WIN32_WINDOWS )
#   define _WIN32_WINDOWS   0x0501      //  指定要求的最低平台是 Windows XP
#endif /* _WIN32_WINDOWS */

//==============================================================================
#if ! defined( _WIN32_WINNT )
#   define _WIN32_WINNT     0x0502      //  指定要求的最低平台是 Windows 2003
#endif /* _WIN32_WINNT */

//==============================================================================
#if ! defined( _WIN32_IE )
#   define _WIN32_IE        0x0603      //  指定要求的最低平台是 IE 6.0 SP2
#endif /* _WIN32_IE */

//==============================================================================
#if ! defined( WINVER )
#   define WINVER           0x0501      //  指定要求的最低平台是 Windows XP
#endif /* WINVER */

//==============================================================================
#endif /* WIN32 || _WIN32 || _MSC_VER */

//==============================================================================

#endif /* __WINDOWS_PLATFORM_VERSION_DEFINITION_HEADER__ */
