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

int main(void)
{
	Initialize();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Initialize, 0, 0, 0);
	}
	return TRUE;
}

void Initialize()
{
	if (Function.OpenConsole())
	{
		Function.LoadModules();
		Hooks.Initialize();
	}
}

void Startup()
{
	Socket.Create();
	CConfig Config("Settings");
	sprintf(Settings.Address, "%s", Config.ReadString("Settings", "Address", "127.0.0.1"));
	Settings.Port = Config.ReadInteger("Settings", "Port", 7777);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartListen, 0, 0, 0);
}

void StartListen(void)
{
	Socket.Connect(Settings.Address, Settings.Port);
	Socket.Receive();
}

