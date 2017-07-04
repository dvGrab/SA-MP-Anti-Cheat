#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Main.h"

class CFunctions
{
private:
	char Modules[1][32];
	
public:
	DWORD ModuleAddr[1];

	int OpenConsole(void);
	int LoadModules(void);
	int UnloadModule(char * name);
	int CloseClient(char * Text, int Seconds);
};
extern CFunctions Function;

#endif