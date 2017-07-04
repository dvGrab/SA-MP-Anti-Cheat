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
	sprintf_s(Modules[0], "samp.dll");

	for (int i = 0; i < 1; i++)
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
		printf("CFunctions::UnloadModule -> Module %s has been unloaded!\n", name);
		FreeLibraryAndExitThread(Address, 0);
		return true;
	}

	return false;
}

int CFunctions::CloseClient(char * Text, int Seconds)
{
	char Temp_0[512];

	while (Seconds)
	{
		sprintf(Temp_0, "Error! (Seconds to close: %i)", Seconds);
		Call.AddPlayerDialog(Temp_0, Text, "Okay", "");
		Seconds--;
		Sleep(1000);
	}

	exit(0);
	return true;
}
