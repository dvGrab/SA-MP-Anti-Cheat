#include "Informations.h"

char * CInformations::GetPlayerName(void)
{
	char * Temp = 0;
	DWORD dwNamePtr = Function.ModuleAddr[0] + 0x219A6F;

	if (dwNamePtr != NULL)
		Temp = (char*)dwNamePtr;

	if (Temp != NULL)
		return Temp;
	else
		return NULL;
}

char * CInformations::GetServerIP(void)
{
	char * Temp = 0;

	DWORD dwPointer = Function.ModuleAddr[0] + 0x21A0F8;
	DWORD dwFinal = *(DWORD*)dwPointer + 0x20;

	if (dwPointer != NULL && dwFinal != NULL)
		Temp = (char*)dwFinal;

	return Temp;
}

void CInformations::SendPong(char * szPing)
{
	for (int i = 0; i < (int)strlen(szPing); i++)
	{
		if (szPing[i] == 'I')
			szPing[i] = 'O';
	}

	Socket.Send(szPing);
}

void CInformations::Kicked(char * szMsg)
{
	char Temp[512], Reason[64];
	int Size = 0;

	for (int i = 7; i < strlen(szMsg); i++)
	{
		Reason[i - 7] = szMsg[i];
		Size++;
	}

	Reason[Size] = '\0';

	sprintf_s(Temp, "Du wurdest soeben durch das Anti Cheat vom Server entfernt.\n");
	sprintf_s(Temp, "%sSolltest Du fragen dazu haben, melde Dich im Forum.\n\n", Temp);
	sprintf_s(Temp, "%sGrund des Kicks: ", Temp);
	sprintf_s(Temp, "%s%s", Temp, Reason);

	Function.CloseClient("Achtung!", Temp, 5);
}

void CInformations::Popup(char * szText)
{
	HANDLE Handle = GetCurrentProcess();
	HMODULE szModules[124];
	DWORD Modules;
	MD5 md5;
	char szModulePathName[MAX_PATH];
	char szModuleFileName[MAX_PATH];
	char szModuleList[4000];

	if (EnumProcessModules(Handle, szModules, sizeof(szModules), &Modules))
	{
		for (int i = 0; i < Modules / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Handle, szModules[i], szModulePathName, sizeof(szModulePathName)))
				if (GetModuleBaseName(GetCurrentProcess(), szModules[i], szModuleFileName, sizeof(szModuleFileName)))
					sprintf_s(szModuleList, "%s%s\n", szModuleList, szModuleFileName);
		}
	}

}

void DetectionLoop()
{
	while (true)
	{
		Detection.Routine();
		Sleep(5000);
	}
}

int CInformations::Authorize(void)
{
	char Temp[256];

	sprintf_s(Temp, "CLIENTNAME %s", GetPlayerName());
	Socket.Send(Temp);

	Function.ClientChecksum("Client.asi");

	sprintf_s(Temp, "CLIENTCOMPUTERNAME %s", ComputerName());
	Socket.Send(Temp);

	sprintf_s(Temp, "CLIENTPRODUCTID %s", ReadRegistry("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductId"));
	Socket.Send(Temp);

	sprintf_s(Temp, "CLIENTPRODUCTNAME %s", ReadRegistry("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName"));
	Socket.Send(Temp);

	sprintf_s(Temp, "CLIENTHWID %s", GetHWID());
	Socket.Send(Temp);

	sprintf_s(Temp, "CLIENTDIRECTORY %s", GetDirectory());
	Socket.Send(Temp);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DetectionLoop, 0, 0, 0);

	return false;
}

char * CInformations::ComputerName(void)
{
	char szTemp[MAX_COMPUTERNAME_LENGTH];
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;

	if (!GetUserName(szTemp, &dwSize))
		Call.AddChatMessage("{FF0000}Fehler beim Funktionsaufruf. Bitte einem Admin melden! (Code: 0007)", 0xFFFFFF);

	return szTemp;
}

char * CInformations::ReadRegistry(char * szPath, char * szValue)
{
	char szTemp[256];
	HKEY Registry;
	DWORD Size = sizeof(szTemp);
	int Result;

	Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szPath, NULL, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &Registry);

	if (Result != NULL)
		Call.AddChatMessage("{FF0000}Fehler beim Funktionsaufruf. Bitte einem Admin melden! (Code: 0008)", 0xFFFFFF);

	Result = RegGetValue(Registry, "", szValue, RRF_RT_ANY, NULL, (PVOID)szTemp, &Size);

	if (Result != NULL)
		Call.AddChatMessage("{FF0000}Fehler beim Funktionsaufruf. Bitte einen Admin melden! (Code: 0009)", 0xFFFFFF);

	return szTemp;
}

char * CInformations::GetHWID(void)
{
	char szTemp[256];
	DWORD HWID;

	if (!GetVolumeInformation("C:\\", 0, 0, &HWID, 0, 0, 0, 0))
		Call.AddChatMessage("{FF0000}Fehler beim Funktionsaufruf. Bitte einem Admin melden! (Code: 0010)", 0xFFFFFF);

	sprintf_s(szTemp, "%X", HWID);

	return szTemp;
}

char * CInformations::GetDirectory(void)
{
	char szTemp[MAX_PATH];
	DWORD dwSize = MAX_PATH + 1;

	if (!GetCurrentDirectory(dwSize, szTemp))
		Call.AddChatMessage("{FF0000}Fehler beim Funktionsaufruf. Bitte einem Admin melden! (Code: 0011)", 0xFFFFFF);

	return szTemp;
}

void CInformations::SendModules(void)
{
	modules_struct Module;
	MD5 MD5_Struct;

	Module.Handle = GetCurrentProcess();

	std::ofstream File;
	File.open("checksum.txt");

	if (EnumProcessModules(Module.Handle, Module.Files, sizeof(Module.Files), &Module.Size))
	{
		for (int i = 0; i < Module.Size / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Module.Handle, Module.Files[i], Module.PathName, sizeof(Module.PathName)))
			{
				if (GetModuleBaseName(Module.Handle, Module.Files[i], Module.Name, sizeof(Module.Name)))
				{
					char Temp[256];
					sprintf_s(Temp, "NEWMODULE %s (%i)", MD5_Struct.digestFile(Module.PathName), i);
					Socket.Send(Temp);

					File << "Client Module Checksum" << MD5_Struct.digestFile(Module.PathName);
				}
			}
		}
	}

	File.close();

}

void CInformations::GiveMD5File(char * szText)
{
	modules_struct Module;
	MD5 MD5_Struct;
	Module.Handle = GetCurrentProcess();

	int Size = 0;
	char szMD5[64];

	for (int i = 13; i < strlen(szText); i++)
	{
		szMD5[i - 13] = szText[i];
		Size++;
	}

	szMD5[Size] = '\0';

	if (EnumProcessModules(Module.Handle, Module.Files, sizeof(Module.Files), &Module.Size))
	{
		for (int i = 0; i < Module.Size / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Module.Handle, Module.Files[i], Module.PathName, sizeof(Module.PathName)))
			{
				if (GetModuleBaseName(Module.Handle, Module.Files[i], Module.Name, sizeof(Module.Name)))
				{
					if (!strstr(Module.Name, ".asi"))
						continue;

					if (strcmp(MD5_Struct.digestFile(Module.PathName), szMD5))
					{
						
					}
				}
			}
		}
	}
}