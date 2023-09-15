//==================================================================================================
//  Summary:
//      Include XML Library Headers and Automic import library
//  
//  Comment:
//      <1> This header will be used for TinyXML / PugiXML / RapidXML
//  ---------------------------------------------------------------------------------------------
//  Author : Arctos                     Version : 1.0.0                         Date: 2012-08-23
//==================================================================================================

#ifndef __THIRDPARTY_XML_LIBRARY_HEADERS__
#define __THIRDPARTY_XML_LIBRARY_HEADERS__

//==================================================================================================
//  RapidXML Headers    ( Version : 1.13 )
//#include <XML/rapidxml.hpp>
//#include <XML/rapidxml_iterators.hpp>
//#include <XML/rapidxml_print.hpp>
//#include <XML/rapidxml_utils.hpp>

//==================================================================================================
//  PugiXML Headers     ( Version : 1.2 )
//#include <XML/pugixml.hpp>

//==================================================================================================
//  TinyXML Headers     ( Version : 2.6.2 )
#include <XML/tinyxml.h>

//==================================================================================================
//  Auto Import XML library
#if defined( _MSC_VER ) && ! defined( NOT_IMPORT_XML )

#  include "Auto_Libraries.h"

#  if defined( XML_AS_STATIC_LIBS )
#    define XML_LIBRARY LIBRARY_STATIC_CRM( "XML" )
#    define XML_LINKAGE LIB_STATIC_LINKAGE
#  else
#    define XML_LIBRARY LIBRARY_SHARED_CRM( "XML" )
#    define XML_LINKAGE LIB_SHARED_LINKAGE
#  endif

#  pragma message( LIB_IMPORT_MESSAGE XML_LIBRARY XML_LINKAGE )
#  pragma comment( lib , XML_LIBRARY LIB_IMPORT_LINKAGE )

#endif /* _MSC_VER && ! NOT_IMPORT_XML */

//==================================================================================================
#endif /* __THIRDPARTY_XML_LIBRARY_HEADERS__ */
