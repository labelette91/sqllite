// TestSqlLite.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <string.h>

using namespace std;
bool  Execute(char *  DbName , char SqlReq[]);
/*
int _tmain(int argc, char* argv[])
{
char *errmsg  ;
char *p = argv[2];
std::string SqlReq = argv[2];
printf(" %s",p);
	if (argc<2)
	{
		return 1;
	}
	 Execute( (char*)argv[1], (char*)argv[2]);

	


	return 0;
}

*/
int main( int argc, char *argv[], char *envp[] ) {
    int iNumberLines = 0;    // Default is no line numbers.

    // If /n is passed to the .exe, display numbered listing
    // of environment variables.

    if ( (argc == 2) && _stricmp( argv[1], "/n" ) == 0 )
         iNumberLines = 1;

    // Walk through list of strings until a NULL is encountered.
    for( int i = 0; envp[i] != NULL; ++i ) {
        if( iNumberLines )
            cout << i << ": " << envp[i] << "\n";
    }

char *errmsg  ;
char *p = argv[2];
std::string SqlReq = argv[2];
printf(" %s",p);
	if (argc<2)
	{
		return 1;
	}
	 Execute( (char*)argv[1], (char*)argv[2]);

/*
CSQLInit();
OpenDatabase();
CSQLClose();
*/
}