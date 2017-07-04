#ifndef SOCKET_H
#define SOCKET_H

#include "Main.h"

class CSocket
{
private:
	SOCKET Handler;

public:
	char Buffer[512];

	int Create(void);
	int Connect(char * ip, int port);
	int Receive(void);
	int Send(char * szMessage);
};
extern CSocket Socket;

#endif