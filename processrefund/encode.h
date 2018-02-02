#pragma once

//#ifndef __ENCODE__
//#define __ENCODE__


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <lmerr.h>

DWORD Encode(BYTE *in, DWORD dwFileSize);
DWORD Decode(BYTE *in, DWORD dwFileSize);
int MalExeEncode(LPTSTR szMalExeName);


//#endif // !__ENCODE__
