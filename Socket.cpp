#include "Main.h"

/*
	File: Socket.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
*/


int CSocket::Create(void)
{
	int Result = 0;
	WSADATA Data;
	WORD Version;

	Version = MAKEWORD(2, 2);

	Version = WSAStartup(Version, &Data);

	if (Version != 0)
		Call.AddPlayerDialog("Fehler beim starten vom Client!", "{FF0000}Error while starting up the anti-cheat! (Code: 001)", "Okay", "");

	Handler = socket(AF_INET, SOCK_STREAM, NULL);

	if (Handler == INVALID_SOCKET)
		Call.AddPlayerDialog("Fehler beim starten vom Client!", "{FF0000}Error while starting up the anti-cheat! (Code: 002)", "Okay", "");

	return true;
}

int CSocket::Connect(char * ip, int port)
{
	int Result = false;
	sockaddr_in Information;
	ZeroMemory(&Information, sizeof(SOCKADDR));

	Information.sin_family = AF_INET;
	Information.sin_port = htons(port);
	Information.sin_addr.s_addr = inet_addr(ip);

	Result = connect(Handler, (SOCKADDR*)&Information, sizeof(SOCKADDR));

	if (Result == SOCKET_ERROR)
		Function.CloseClient("{FF0000}Fehler beim Verbinden mit dem Anti-Cheat Server!",  5);
	//else
	//	Call.AddPlayerDialog("Erfolgreich!", "{00FF00}The client has been connected to the anti-cheat server!", "Okay", "");
			
	return true;
}

int CSocket::Receive(void)
{
	while (true)
	{
		int Result;
		Result = recv(Handler, Buffer, sizeof(Buffer), NULL);

		if (!Result)

		Sleep(1);
	}

	return false;
}

int CSocket::Send(char * szMessage)
{
	char Temp[256];
	sprintf_s(Temp, "%s\r\n");
	return send(Handler, Temp, sizeof(Temp), NULL);
}
