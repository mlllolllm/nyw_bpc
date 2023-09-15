//==================================================================================================
//  Summary:
//      Include STL ( Standard Template Library ) Namspace Headers
//  
//  ---------------------------------------------------------------------------------------------
//  Author: Arctos                      Version : 1.0.0                         Date: 2013-10-10
//==================================================================================================

#ifndef __CPLUSPLUS_STANDARD_TEMPLATE_LIBRARY_HEADERS__
#define __CPLUSPLUS_STANDARD_TEMPLATE_LIBRARY_HEADERS__

//==================================================================================================
//	Disable Secure Warnings On Microsoft Compiler
#if	defined( _MSC_VER ) && ( _MSC_VER > 1300 )
# define _CRT_NON_CONFORMING_SWPRINTFS
# define _CRT_NONSTDC_NO_DEPRECATE
# define _CRT_NONSTDC_NO_WARNINGS
# define _CRT_SECURE_NO_DEPRECATE
# define _CRT_SECURE_NO_WARNINGS
#endif

//==================================================================================================
//	Standard C Plus Plus Headers
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <float.h>
#include <time.h>
#include <math.h>

//==================================================================================================
#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#include <malloc.h>

//==================================================================================================
#include <sys/types.h>
#include <sys/stat.h>

//==================================================================================================
#if defined( _WIN32 ) || defined( WIN32 )
#	include <sys/utime.h>
#	include <direct.h>
#	include <tchar.h>
#endif

//==================================================================================================
#if defined( __unix ) || defined( __unix__ )
#	include <sys/procfs.h>
#	include <sys/shm.h>
#	include <unistd.h>
#	include <dirent.h>
#	include <utime.h>
#endif

//==================================================================================================
//	Stdandard Template Library
#include <exception>
#include <algorithm>
#include <numeric>		// functional iterator
#include <limits>

//==================================================================================================
#include <iostream>		// istream
#include <fstream>		// ostream istream ios
#include <sstream>
#include <string>

//==================================================================================================
#include <vector>
#include <queue>
#include <stack>	//	deque
#include <list>
#include <map>
#include <set>

//==================================================================================================



//==================================================================================================

#endif /* __CPLUSPLUS_STANDARD_TEMPLATE_LIBRARY_HEADERS__ */
