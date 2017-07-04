#include "Main.h"

/*
	File: Main.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
*/

CFunctions Function;
CSocket Socket;
CHooks Hooks;
CCalls Call;
SSettings Settings;
CReading Reading;
CHandle Handle;
CDetection Detection;

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, 0, 0, 0);

	return TRUE;
}

void Initialize()
{
	Function.OpenConsole();
	Function.LoadModules();
	Hooks.Initialize();
}

void Startup()
{
	Socket.Create();
	CConfig Config("Settings");
	sprintf(Settings.Address, "%s", Config.ReadString("Settings", "Address", "122.0.0.1"));
	Settings.Port = Config.ReadInteger("Settings", "Port", 7777);

	if (!strcmp(Settings.Address, Informations.GetServerIP()))
	{
		Function.DebugMessage("Socket.Connect", "Socket has been initialized and started to connect...");
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartListen, 0, 0, 0);
	}
	else
	{
		Function.DebugMessage("Settings.Address", "Connect to another server. IP is not valid with the gameserver.");
	}		
}

void StartListen(void)
{
	Socket.Connect(Settings.Address, Settings.Port);
}

