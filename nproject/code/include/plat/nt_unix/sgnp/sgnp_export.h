// -*- C++ -*-
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl -s SGNP
// ------------------------------
#ifndef SGNP_EXPORT_H
#define SGNP_EXPORT_H
 


#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SGNP_HAS_DLL)
#  define SGNP_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SGNP_HAS_DLL */

#if !defined (SGNP_HAS_DLL)
#  define SGNP_HAS_DLL 1
#endif /* ! SGNP_HAS_DLL */

#if defined (SGNP_HAS_DLL) && (SGNP_HAS_DLL == 1)
#  if defined (SGNP_BUILD_DLL)
#    define SGNP_Export ACE_Proper_Export_Flag
#    define SGNP_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SGNP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SGNP_BUILD_DLL */
#    define SGNP_Export ACE_Proper_Import_Flag
#    define SGNP_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SGNP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SGNP_BUILD_DLL */
#else /* SGNP_HAS_DLL == 1 */
#  define SGNP_Export
#  define SGNP_SINGLETON_DECLARATION(T)
#  define SGNP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SGNP_HAS_DLL == 1 */
#if defined (SGNP_MAKESRV_DLL)
#    define SGNP_MakeSrv_Export ACE_Proper_Export_Flag
#else
#    define SGNP_MakeSrv_Export ACE_Proper_Import_Flag
#endif

// Set SGNP_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (SGNP_NTRACE)
#  if (ACE_NTRACE == 1)
#    define SGNP_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define SGNP_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !SGNP_NTRACE */

#if (SGNP_NTRACE == 1)
#  define SGNP_TRACE(X)
#else /* (SGNP_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define SGNP_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (SGNP_NTRACE == 1) */

#if defined (WIN32)
#     if defined( SGNP_BUILD_DLL )
#        define SGNP_TEMPLATE
#     else
#        define SGNP_TEMPLATE extern
#     endif	
#else
#  define SGNP_TEMPLATE
#endif

#define NPC_API SGNP_Export

#endif /* SGNP_EXPORT_H */

// End of auto generated file.