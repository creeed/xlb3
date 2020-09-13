#ifndef __XLBE_PREREQS_H__
#define __XLBE_PREREQS_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

/////////////////////////////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <math.h>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <iomanip>

#include "XlbeConfig.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
#define Xlbe_Export

#if defined( _MSC_VER )
#	define XLBE_MSVC_COMPILER
#endif

#if defined(__WIN32__) || defined(_WIN32)
# define XLBE_WIN32_PLATFORM
#		if defined( XLBE_DYNAMIC_LIB )
#			undef Xlbe_Export
#			if defined( XLBE_NONCLIENT_BUILD )
#				define Xlbe_Export __declspec( dllexport )
#			else
#				define Xlbe_Export __declspec( dllimport )
#			endif
#		endif
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////

#if defined( XLBE_WIN32_PLATFORM )
    #define WIN32_LEAN_AND_MEAN
    //#define _WIN32_WINNT 0x0400 
    #include <windows.h>
    #include <io.h>
    #include <time.h>

    #pragma warning(disable:4251)
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbeTypes.h"
#include "XlbeErrno.h"
#include "XlbeUtility.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x) != 0 ) { delete (x); (x) = 0; }
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////

#endif 