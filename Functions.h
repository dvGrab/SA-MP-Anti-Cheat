#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Main.h"

#define MAX_MODULES 0

class CFunctions
{
private:
	char Modules[1][32];
	
public:
	DWORD ModuleAddr[1];

	int OpenConsole(void);
	int LoadModules(void);
	int UnloadModule(char * name);
	int CloseClient(char * Title, char * Text, int Seconds);
	void DebugMessage(char * szClass, char * szMessage);
	char * ClientChecksum(char * szClientName);
	DWORD FindPattern(DWORD base, DWORD size, char pattern[], char mask[]);
	DWORD GetModuleSize(char * Name);
};
extern CFunctions Function;

struct modules_struct
{
	HANDLE Handle;
	HMODULE Files[248];
	DWORD Size;
	char PathName[256];
	char Name[256];

};

#endif