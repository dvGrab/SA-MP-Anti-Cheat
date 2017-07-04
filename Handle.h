#ifndef HANDLE_H
#define HANDLE_H

#include "Main.h"

class CHandle
{
public:
	int GetModules(void);
	char * GetModuleChecksum(char * ModuleName);
};
extern CHandle Handle;

#endif