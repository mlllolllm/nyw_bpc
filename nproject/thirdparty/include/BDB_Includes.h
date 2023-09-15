//==================================================================================================
//	Summary:
//		Include Embed Berkeley Database Headers and Automic import library
//	
//	Comment:
//		<1>	This header will be used for Embed Berkeley DB
//	---------------------------------------------------------------------------------------------
//	Author: Arctos                     Date: 2010-03-30                        Version: 5.0.21
//==================================================================================================

#ifndef __THIRDPARTY_EMBED_BERKELEY_DATABASE_HEADERS__
#define __THIRDPARTY_EMBED_BERKELEY_DATABASE_HEADERS__

//==================================================================================================
//	Berkeley Embed Database Headers
#include <BerkeleyDB/db_cxx.h>

//==================================================================================================
//	automic import "Embed Berkeley DB" library ( Only UTF8 Charset Support )
#if defined( _MSC_VER ) && ! defined( _NOT_AUTO_IMPORT_BDB_LIBRARY_ )

#	include "Auto_Libraries.h"

#	if defined( BDB_AS_STATIC_LIBS )
#		define BDB_LIBRARY	LIBRARY_STATIC_URM( "BDB" )
#		define BDB_LINKAGE	LIB_STATIC_LINKAGE
#	else
#		define BDB_LIBRARY	LIBRARY_SHARED_URM( "BDB" )
#		define BDB_LINKAGE	LIB_SHARED_LINKAGE
#	endif

#	pragma message( LIB_IMPORT_MESSAGE BDB_LIBRARY BDB_LINKAGE )
#	pragma comment( lib , BDB_LIBRARY LIB_IMPORT_LINKAGE )

#endif /* _MSC_VER && ! _NOT_AUTO_IMPORT_BDB_LIBRARY_ */

//==================================================================================================
#endif /* __THIRDPARTY_EMBED_BERKELEY_DATABASE_HEADERS__ */
