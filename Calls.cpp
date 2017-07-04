#include "Calls.h"

/*
	File: Calls.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
*/

void CCalls::AddChatMessage(char * szText, DWORD dwColor)
{
	DWORD dwAddress = Function.ModuleAddr[0] + 0x64010; 
	DWORD dwChatPtr = Function.ModuleAddr[0] + 0x21A0E4;

	if (dwAddress != NULL && dwChatPtr != NULL)
	{
		_asm
		{
			mov eax, dword ptr[dwChatPtr];
			mov ecx, dword ptr[eax];
			push 0;
			push dwColor;
			push 0;
			push szText;
			push 8;
			call dwAddress;
		}
	}
}

void CCalls::AddPlayerDialog(char * szTitle, char * szText, char * szButton, char * szSecButton)
{
	DWORD dwAddress = Function.ModuleAddr[0] + 0x6B9C0;
	DWORD dwDialogPtr = Function.ModuleAddr[0] + 0x21A0B8;

	if (dwAddress != NULL && dwDialogPtr != NULL)
	{
		_asm
		{
			mov eax, dword ptr[dwDialogPtr]
			mov ecx, dword ptr[eax];
			push 0;
			push szSecButton;
			push szButton;
			push szText;
			push szTitle;
			push 0;
			push 1;
			call dwAddress;
		}
	}
}