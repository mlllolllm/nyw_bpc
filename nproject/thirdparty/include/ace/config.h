//==============================================================================
//  Summary:
//      ACE ADAPTIVE Communication Environment Config Header
//  ------------------------------------------------------------------------
//  http://www.cnblogs.com/WonKerr/archive/2013/06/13/predefined_macros.html
//==============================================================================
#ifndef __ACE_ADAPTIVE_COMMUNICATION_ENVIRONMENT_CONFIG_HEADER__
#define __ACE_ADAPTIVE_COMMUNICATION_ENVIRONMENT_CONFIG_HEADER__

//==============================================================================
#define ACE_DEFINES_DEFAULT_WIN32_SECURITY_ATTRIBUTES
#define ACE_HAS_STANDARD_CPP_LIBRARY 1
#define ACE_NO_WIN32_LEAN_AND_MEAN
#define ACE_MAXLOGMSGLEN 1024

//==============================================================================
//  CDR ( Common Data Representation ) Macros Definition
//  CDR Size From 64K Grow By Expr 2 Until 1M Linear Grow By 1M
#define ACE_DEFAULT_CDR_LINEAR_GROWTH_CHUNK 0x00100000
#define ACE_DEFAULT_CDR_EXP_GROWTH_MAX  0x00100000
#define ACE_DEFAULT_CDR_BUFSIZE 0x00010000
#define ACE_LACKS_CDR_ALIGNMENT

//==============================================================================
//  Compiler : GNU C/C++ , MSVC , Intel ICC/ICPC , Solaris Studio
//  Processor: Athlon,Atom,Core,Core 2,Core i3/i5/i7,Opteron,Pentium,Phenom,etc
#if defined( _M_X64 ) || defined( __x86_64__ ) || defined( __amd64__ )
#   define ARCH_64BIT
#   define CPU_X64
#elif defined( _M_IX86 ) || defined( __i386 )
#   define CPU_X86
#endif

//==============================================================================
//  Compiler : GNU C/C++ , MSVC , Intel ICC/ICPC , HP C/aC++
//  Processor: Itanium,Itanium 2,Itanium 2 9000/9100/9300,etc
#if defined( _M_IA64 ) || defined( __itanium__ ) || defined( __ia64 )
#   define ARCH_64BIT
#   define CPU_ITANIUM
#endif

//==============================================================================
//  Compiler : GNU C/C++ , IBM XL C/C++
//  Processor: PowerPC, POWER 1/2/3/4/5/67/,G1,G2,G3,G4,G5,etc
#if defined( __powerpc__ ) || defined( __ppc__ ) || defined( __PPC__ )
#   define CPU_POWERPC
#   if defined( __64BIT__ ) || defined( __PPC64__ )
#       define ARCH_64BIT
#   endif
#endif

//==============================================================================
//  Compiler : GNU C/C++ , Solaris Studio
//  Processor: UltraSPARC I/II/III/IV/T1/T2, SPARC T3/T4, etc
#if defined( __sparc )
#   define CPU_SPARC
#   if defined( __64BIT__ ) || defined( __sparcv9 )
#       define ARCH_64BIT
#   endif
#endif

//==============================================================================
#if ! defined( BUILD_64BIT ) && defined( ARCH_64BIT )
#   define BUILD_64BIT
#endif

#if defined( BUILD_64BIT )
#   define ACE_LD_MACHINE ACE_TEXT("64")
#else
#   define ACE_LD_MACHINE ACE_TEXT("32")
#endif

//==============================================================================
#if defined( _UNICODE ) || defined( UNICODE )
#   define ACE_USES_WCHAR
#   define ACE_HAS_WCHAR
#   define BUILD_WCHAR
#endif

#if defined( BUILD_WCHAR )
#   define ACE_LD_CHARSET ACE_TEXT("U")
#else
#   define ACE_LD_CHARSET ACE_TEXT("M")
#endif

//==============================================================================
#if defined( _DEBUG ) || defined( DEBUG )
#   define BUILD_DEBUG
#endif

#if defined( BUILD_DEBUG )
#   define ACE_LD_RELEASE ACE_TEXT("D")
#else
#   define ACE_LD_RELEASE ACE_TEXT("R")
#endif

//==============================================================================
#define ACE_LD_DECORATOR_STR ACE_LD_CHARSET ACE_LD_RELEASE ACE_LD_MACHINE

//==============================================================================
#if defined( _WIN32 )                       // MSVC | GCC | ICC | CLang
#   include "ace/config-win32.h"
#   define OS_WINNT
#elif defined( __linux__ )                  // GNU GCC/G++ | Intel ICC
#   include "ace/config-linux.h"
#   define OS_LINUX
#elif defined( __sun ) && defined( __SVR4 ) // GNU GCC/G++ | Sun Studio
#   include "ace/config-sunos5.9.h"
#   define OS_SUNOS
#elif defined( __hpux )                     // GNU GCC/G++ | HP C/aC++
#   include "ace/config-hpux-11.00.h"
#   define OS_HPUX
#elif defined( _AIX )                       // GNU GCC/G++ | IBM XL C/C++
#   include "ace/config-aix-5.x.h"
#   define OS_AIX
#endif

//==============================================================================
#endif /* __ACE_ADAPTIVE_COMMUNICATION_ENVIRONMENT_CONFIG_HEADER__ */
