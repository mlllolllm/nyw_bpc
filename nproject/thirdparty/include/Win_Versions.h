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
#   define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS // ĳЩ CString ���캯��������ʽ��
#endif /* _ATL_CSTRING_EXPLICIT_CONSTRUCTORS */

//==============================================================================
#if ! defined( _AFX_ALL_WARNINGS )
#   define _AFX_ALL_WARNINGS // �رն�ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#endif /* _AFX_ALL_WARNINGS */

//==============================================================================
#if ! defined( _WIN32_WINDOWS )
#   define _WIN32_WINDOWS   0x0501      //  ָ��Ҫ������ƽ̨�� Windows XP
#endif /* _WIN32_WINDOWS */

//==============================================================================
#if ! defined( _WIN32_WINNT )
#   define _WIN32_WINNT     0x0502      //  ָ��Ҫ������ƽ̨�� Windows 2003
#endif /* _WIN32_WINNT */

//==============================================================================
#if ! defined( _WIN32_IE )
#   define _WIN32_IE        0x0603      //  ָ��Ҫ������ƽ̨�� IE 6.0 SP2
#endif /* _WIN32_IE */

//==============================================================================
#if ! defined( WINVER )
#   define WINVER           0x0501      //  ָ��Ҫ������ƽ̨�� Windows XP
#endif /* WINVER */

//==============================================================================
#endif /* WIN32 || _WIN32 || _MSC_VER */

//==============================================================================

#endif /* __WINDOWS_PLATFORM_VERSION_DEFINITION_HEADER__ */
