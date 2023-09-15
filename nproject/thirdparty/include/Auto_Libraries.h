//==================================================================================================
//  Summary:
//      Automic import library on "Microsoft Windows Platform"
//  
//  Comment:
//      <1> This header will be used for automic import library 
//  ---------------------------------------------------------------------------------------------
//  Author: Arctos                      Version : 1.0.00                        Date: 2009-11-11
//==================================================================================================

#ifndef __AUTO_IMPORT_LIBRARY_ON_WINDOWS_PLATFORM_H__
#define __AUTO_IMPORT_LIBRARY_ON_WINDOWS_PLATFORM_H__

//==================================================================================================
//  Library Suffix of charset
#if defined( BUILD_WCHAR ) || defined( _UNICODE ) || defined( UNICODE )
#   define LIB_CHARSET  "U"
#else
#   define LIB_CHARSET  "M"
#endif

//==================================================================================================
//  Library Suffix of debug or release
#if defined( BUILD_DEBUG ) || defined( _DEBUG ) || defined( DEBUG )
#   define LIB_RELEASE  "D"
#else
#   define LIB_RELEASE  "R"
#endif

//==================================================================================================
//  Library Suffix of Machine
#if defined( BUILD_64BIT ) || defined( _WIN64 ) || defined( WIN64 )
#   define LIB_MACHINE  "64"
#else
#   define LIB_MACHINE  "32"
#endif

//==================================================================================================
//  Ansi Or Wide Suffix String
#define LIB_CHARSET_SUFFIX  ACE_TEXT( LIB_CHARSET )
#define LIB_RELEASE_SUFFIX  ACE_TEXT( LIB_RELEASE )
#define LIB_MACHINE_SUFFIX  ACE_TEXT( LIB_MACHINE )

//==================================================================================================
//  Ansi Or Wide Suffix of CRM / URM / XRM
#define LIBRARY_CRM_SUFFIX  LIB_CHARSET_SUFFIX LIB_RELEASE_SUFFIX LIB_MACHINE_SUFFIX
#define LIBRARY_URM_SUFFIX  ACE_TEXT( "U" ) LIB_RELEASE_SUFFIX LIB_MACHINE_SUFFIX
#define LIBRARY_XRM_SUFFIX  ACE_TEXT( "X" ) LIB_RELEASE_SUFFIX LIB_MACHINE_SUFFIX

//==================================================================================================
//  Library Name With Special Characteristic Suffix
#define LIBRARY_NAME_CRM( NAME , TYPE ) NAME LIB_CHARSET LIB_RELEASE LIB_MACHINE TYPE
#define LIBRARY_NAME_URM( NAME , TYPE ) NAME "U" LIB_RELEASE LIB_MACHINE TYPE
#define LIBRARY_NAME_XRM( NAME , TYPE ) NAME LIB_RELEASE LIB_MACHINE TYPE

//==================================================================================================
//  Standard Static / Shared Library Full Name
#define LIBRARY_STATIC_CRM( NAME ) LIBRARY_NAME_CRM( NAME , "_S" )
#define LIBRARY_STATIC_URM( NAME ) LIBRARY_NAME_URM( NAME , "_S" )
#define LIBRARY_STATIC_XRM( NAME ) LIBRARY_NAME_XRM( NAME , "_S" )
#define LIBRARY_SHARED_CRM( NAME ) LIBRARY_NAME_CRM( NAME , "" )
#define LIBRARY_SHARED_URM( NAME ) LIBRARY_NAME_URM( NAME , "" )
#define LIBRARY_SHARED_XRM( NAME ) LIBRARY_NAME_XRM( NAME , "" )

//==================================================================================================
//  Extend Name of Shared Library / Static Library / Import Library
#define LIB_IMPORT_MESSAGE "Automatically linking with "
#define LIB_IMPORT_LINKAGE ".lib"
#define LIB_SHARED_LINKAGE ".dll"
#define LIB_STATIC_LINKAGE ".lib"

//==================================================================================================
#endif /* #define __AUTO_IMPORT_LIBRARY_ON_WINDOWS_PLATFORM_H__ */
