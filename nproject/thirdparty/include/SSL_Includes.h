//==================================================================================================
//  Summary:
//      Include OpenSSL Headers and Automic import library
//  
//  Comment:
//      <1> This header will be used for SSL & TLS
//  ---------------------------------------------------------------------------------------------
//  Author : Arctos                     Version : 0.9.8R                        Date : 2012-08-23
//==================================================================================================

#ifndef __SECURE_SOCKETS_LAYER_AND_TRANSPORT_LAYER_SECURITY_HEADERS__
#define __SECURE_SOCKETS_LAYER_AND_TRANSPORT_LAYER_SECURITY_HEADERS__

//==================================================================================================
//  OpenSSL Base Headers
#include <openssl/opensslconf.h>
#include <openssl/conf_api.h>

//==================================================================================================
//  OpenSSL Hash Headers
//#include <openssl/mdc2.h>				// ! Linux
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

//==================================================================================================
//  OpenSSL Crypto Headers
#include <openssl/rc2.h>
#include <openssl/rc4.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/cast.h>
//#include <openssl/idea.h>				// ! Linux
#include <openssl/blowfish.h>

//==================================================================================================
//  OpenSSL Padding Headers
#include <openssl/pkcs7.h>
#include <openssl/pkcs12.h>

//==================================================================================================
//  OpenSSL SSL & TLS Headers
#include <openssl/ssl.h>

//==================================================================================================
//  OpenSSL Online Certificate Status Protocol Headers
#include <openssl/ocsp.h>

//==================================================================================================
//  OpenSSL Codec Protocol Headers
#include <openssl/asn1t.h>
#include <openssl/asn1_mac.h>
#include <openssl/krb5_asn.h>

//==================================================================================================
//  OpenSSL Other Headers
#include <openssl/engine.h>
#include <openssl/txt_db.h>
//#include <openssl/tmdiff.h>			// ! Linux SunOS(default) 
//#include <openssl/fips_rand.h>		// ! Linux SunOS(default) 
#include <openssl/ui_compat.h>
#include <openssl/x509_vfy.h>

//==================================================================================================
//  Auto Import "Secure Sockets Layer" library ( Only Ansi - Mbcs Charset Support )
#if defined( _MSC_VER ) && ! defined( NOT_IMPORT_SSL )

#   include "Auto_Libraries.h"

#   if defined( SSL_AS_STATIC_LIBS )
#       define SSL_LIBRARY  LIBRARY_STATIC_CRM( "SSL" )
#       define SSL_LINKAGE  LIB_STATIC_LINKAGE
#   else
#       define SSL_LIBRARY  LIBRARY_SHARED_CRM( "SSL" )
#       define SSL_LINKAGE  LIB_SHARED_LINKAGE
#   endif

#   pragma message( LIB_IMPORT_MESSAGE SSL_LIBRARY SSL_LINKAGE )
#   pragma comment( lib , SSL_LIBRARY LIB_IMPORT_LINKAGE )

#endif /* _MSC_VER && ! NOT_IMPORT_SSL */

//==================================================================================================
#endif /* __SECURE_SOCKETS_LAYER_AND_TRANSPORT_LAYER_SECURITY_HEADERS__ */
