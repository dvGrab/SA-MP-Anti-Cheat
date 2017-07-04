#include "Main.h"

/*
	File: Socket.cpp
	Author: Grab
	This program is developed for german-crimetime.de!
*/

CSSL OpenSSL;

SSL_CTX * SSL_Context;
SSL * SSL_Handle;

int CSocket::Create(void)
{
	int Result = 0;
	WSADATA Data;
	WORD Version;

	Version = MAKEWORD(2, 2);
	Version = WSAStartup(Version, &Data);

	if (Version != 0)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0001)", 0xFF0000);

	Handler = socket(AF_INET, SOCK_STREAM, NULL);

	if (Handler == INVALID_SOCKET)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0002)", 0xFF0000);

	OpenSSL.Initialize();
	
	SSL_Context = SSL_CTX_new(SSLv23_client_method());
	
	if(SSL_Context == NULL)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0003)", 0xFF0000);
	
	SSL_Handle = SSL_new(SSL_Context);

	if(SSL_Handle == NULL)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0004)", 0xFF0000);

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
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0005)", 0xFF0000);

	Result = SSL_set_fd(SSL_Handle, Handler);
	
	if(Result == NULL)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0006)", 0xFF0000);

	Result = SSL_connect(SSL_Handle);

	if (Result == NULL)
		Call.AddChatMessage("Fehler beim Laden des Anti Cheats aufgetreten! (Code: 0006)", 0xFF0000);
	else
		Send("CLIENTAUTH");

	Receive();

	return true;
}

int CSocket::Receive(void)
{
	while (true)
	{
		int Result;
		Result = SSL_read(SSL_Handle, Buffer, sizeof(Buffer));
		
		if (!Result)
		{
			Call.AddChatMessage("Verbindung zum Anti Cheat Server wurde unterbrochen!", 0xFF0000);
			break;
		}
		else
			Reading.Listen(Buffer);

		sprintf_s(Buffer, "");
		Sleep(5);
	}

	return false;
}

int CSocket::Send(char * szMessage)
{
	char Temp[256];
	sprintf_s(Temp, "%s", szMessage);
	//printf_s("Text: %s\n", szMessage);
	return SSL_write(SSL_Handle, Temp, sizeof(Temp));
}
