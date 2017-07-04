#include "Hooks.h"

/*
	File: Hooks.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
	*/


typedef int(_cdecl * readchatmsg_t)(DWORD, char *, ...);
readchatmsg_t ReadChatMessage_o;

int ReadChatMessage(DWORD addr, char * Text, ...)
{
	_asm pushad;

	Hooks.Count++;

	if (Hooks.Count > 3 && Hooks.Unlocked != 1)
	{
		Handle.GetModules();
		Hooks.Unlocked = true;
		Startup();
	}
	
	_asm popad;
	return ReadChatMessage_o(addr, Text);
	
}

void CHooks::Initialize(void)
{
	DWORD dwChatMessage = Function.ModuleAddr[0] + 0x64520;
	ReadChatMessage_o = (readchatmsg_t)DetourFunction((PBYTE)dwChatMessage, (PBYTE)ReadChatMessage);
}

