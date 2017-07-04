#include "Handle.h"

MD5 md5;

/*
	looking for std::vector (stl container)
*/

int CHandle::GetModules(void)
{
	HANDLE Handle = GetCurrentProcess();
	HMODULE szModules[124];
	DWORD Modules;
	char szModulePathName[MAX_PATH];
	char szModuleFileName[MAX_PATH];

	if (EnumProcessModules(Handle, szModules, sizeof(szModules), &Modules))
	{
		for (int i = 0; i < Modules / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Handle, szModules[i], szModulePathName, sizeof(szModulePathName)))
			{
				if (GetModuleBaseName(GetCurrentProcess(), szModules[i], szModuleFileName, sizeof(szModuleFileName)))
				{
					printf("Module: %s MD5: %s\n", szModuleFileName, md5.digestFile(szModulePathName));
				}
			}
		}
	}

	return false;
}

char * CHandle::GetModuleChecksum(char * ModuleName)
{
	HANDLE Handle = GetCurrentProcess();
	HMODULE hModule[124];
	DWORD dwSize;
	char szModuleName[MAX_PATH];

	if (EnumProcessModules(Handle, hModule, sizeof(hModule), &dwSize))
	{
		for (int i = 0; i < dwSize / sizeof(HMODULE); i++)
		{
			if (GetModuleBaseName(Handle, hModule[i], szModuleName, sizeof(szModuleName)))
			{
			}
		}
	}


	return ModuleName;
}