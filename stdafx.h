// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

	#pragma warning(disable : 4996)

#if defined WIN32
	#include "targetver.h"
#endif


// TODO: reference additional headers your program requires here

typedef unsigned char       BYTE;
typedef unsigned char boolean;
typedef unsigned char byte;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef          short  int16_t;
typedef unsigned int   uint32_t;
typedef  int   int32_t;

typedef unsigned int size_t   ;
typedef unsigned short word;


#if !defined WIN32
#include <stdio.h>
//#include <stdlib.h>
#include <string>
	#include <sys/socket.h> // Needed for the socket functions
	#include <netdb.h>
	#include <arpa/inet.h>
	typedef int SOCKET;
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR   -1
	#define closesocket(s) close(s);
#else

#if _MSC_VER > 1500
	#pragma warning(disable : 4996)
#endif
	#include <winsock2.h>

	#if defined _M_IX86
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_IA64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_X64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif

#if _MSC_VER <= 1500
	// For Visual Studio 2008 and below, no stdint.h comes with the header files. Use boost's implementation.
//	#include <boost/cstdint.hpp>
//	using boost::uint32_t;
//	using boost::uint8_t;
#endif

#endif

#define WEBSERVER_DONT_USE_ZIP


#include <tchar.h>
