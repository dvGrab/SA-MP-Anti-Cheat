#ifndef CALLS_H
#define CALLS_H

#include "Main.h"

class CCalls
{
public:
	void AddChatMessage(char * szText, DWORD dwColor);
	void AddPlayerDialog(char * szTitle, char * szText, char * szButton, char * szSecButton);
};
extern CCalls Call;

#endif