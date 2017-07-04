#include "Functions.h"

/*
	File: Functions.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
*/

int CFunctions::OpenConsole(void)
{
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		return true;
	}

	return false;
}

int CFunctions::LoadModules(void)
{
	sprintf_s(Modules[MAX_MODULES], "samp.dll");

	for (int i = 0; i < MAX_MODULES + 1; i++)
	{
		if (Modules[i] != 0)
		{
			ModuleAddr[i] = (DWORD)GetModuleHandle(Modules[i]);

			if (ModuleAddr[i] != 0)
			{
				printf("CFunctions::LoadModule -> Module %s is loaded on addr 0x%X!\n", Modules[i], ModuleAddr[i]);
			}
			else
			{
				char Temp[256];
				sprintf_s(Temp, "CFunctions::LoadModule->Cannot load module %s!\n", Modules[i]);
				MessageBox(0, Temp, "Error!", MB_OK | MB_ICONERROR);
				exit(0);
			}
		}
	}
	return false;
}

int CFunctions::UnloadModule(char * name)
{
	HMODULE Address = GetModuleHandle(name);

	if (Address != 0)
	{
		FreeLibraryAndExitThread(Address, 0);
		return true;
	}

	return false;
}

int CFunctions::CloseClient(char * Title, char * Text, int Seconds)
{
	char Temp[512];

	while (Seconds)
	{
		sprintf(Temp, "%s (Sekunden bis zum schlieﬂen: %i)",Title, Seconds);
		Call.AddPlayerDialog(Temp, Text, "Okay", "");
		Seconds--;
		Sleep(1000);
	}

	exit(0);
	return true;
}

void CFunctions::DebugMessage(char * szClass, char * szMessage)
{
	if (szClass != 0 && szMessage != 0)
	{
		char Temp[256];
		sprintf_s(Temp, "{FF0000}<{FFFF00}DEBUG{FF0000}>{FF0000}%s: {FFFFFF}%s", szClass, szMessage);
		Call.AddChatMessage(Temp, -1);
	}
}

char * CFunctions::ClientChecksum(char * szClientName)
{
	modules_struct Module;
	MD5 MD5_Struct;

	Module.Handle = GetCurrentProcess();

	if (EnumProcessModules(Module.Handle, Module.Files, sizeof(Module.Files), &Module.Size))
	{
		for (int i = 0; i < Module.Size / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Module.Handle, Module.Files[i], Module.PathName, sizeof(Module.PathName)))
			{
				if (GetModuleBaseName(Module.Handle, Module.Files[i], Module.Name, sizeof(Module.Name)))
				{			
					if (_strcmpi(Module.Name, szClientName) == false)
					{
						char Temp[256];
						sprintf_s(Temp, "CLIENTCHECKSUM %s", MD5_Struct.digestFile(Module.PathName));
						Socket.Send(Temp);

						std::ofstream File;
						File.open("checksum.txt");
						File << "Checksum " << MD5_Struct.digestFile(Module.PathName);
						File.close();
						break;
					} 
				}
			}
		}
	}

	return szClientName;
}


DWORD CFunctions::FindPattern(DWORD base, DWORD size, char pattern[], char mask[])
{
	for (DWORD retAddress = base; retAddress < (base + size); retAddress++)
	{
		if (*(BYTE*)retAddress == (pattern[0] & 0xff) || mask[0] == '?')
		{
			DWORD startSearch = retAddress;
			for (int i = 0; mask[i] != '\0'; i++, startSearch++)
			{
				if ((pattern[i] & 0xff) != *(BYTE*)startSearch && mask[i] != '?')
					break;

				if (((pattern[i] & 0xff) == *(BYTE*)startSearch || mask[i] == '?') && mask[i + 1] == '\0')
					return retAddress;
			}
		}
	}
	return false;
}

DWORD CFunctions::GetModuleSize(char * Name)
{
	MODULEENTRY32 Modules;
	HANDLE Snapshot;

	Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

	if (Snapshot)
	{
		if (Module32First(Snapshot, &Modules))
		{
			while (Module32Next(Snapshot, &Modules))
			{
				if (!strcmp(Modules.szModule, Name))
				{
					return Modules.dwSize;
					break;
				}
			}
		}
	}
}