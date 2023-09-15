//==================================================================================================
//  Summary:
//      Include ZIP Library Headers and Automic import library
//  
//  Comment:
//      <1> This header will be used for ZLib
//  ---------------------------------------------------------------------------------------------
//  Author : Arctos                     Version : 1.2.8                         Date: 2013-11-14
//==================================================================================================

#ifndef __THIRDPARTY_ZIP_LIBRARY_HEADERS__
#define __THIRDPARTY_ZIP_LIBRARY_HEADERS__

//==================================================================================================
//  ZLib Library Headers
#include <ZIP/unzip.h>
#include <ZIP/zip.h>

//==================================================================================================
//  Auto Import Zlib library ( Only Ansi - Mbcs Charset Support )
#if defined( _MSC_VER ) && ! defined( NOT_IMPORT_ZIP )

#  include "Auto_Libraries.h"

#  if defined( ZIP_AS_STATIC_LIBS )
#    define ZIP_LIBRARY LIBRARY_STATIC_CRM( "ZIP" )
#    define ZIP_LINKAGE LIB_STATIC_LINKAGE
#  else
#    define ZIP_LIBRARY LIBRARY_SHARED_CRM( "ZIP" )
#    define ZIP_LINKAGE LIB_SHARED_LINKAGE
#  endif

#  pragma message( LIB_IMPORT_MESSAGE ZIP_LIBRARY ZIP_LINKAGE )
#  pragma comment( lib , ZIP_LIBRARY LIB_IMPORT_LINKAGE )

#endif /* _MSC_VER && ! NOT_IMPORT_ZIP */

//==================================================================================================
#endif /* __THIRDPARTY_ZIP_LIBRARY_HEADERS__ */
