#include "Reading.h"

CInformations Informations;

int CReading::Listen(char * Buffer)
{	
	if (!strcmp(Buffer, "WELCOMECLIENT"))
		Informations.Authorize();

	if (strstr(Buffer, "PING"))
		Informations.SendPong(Buffer);

	if (strstr(Buffer, "KICKED"))
		Informations.Kicked(Buffer);
/*
	if (strstr(Buffer, "GIVEFILEINFO"))
		Informations.GiveMD5File(Buffer);
		*/
	return false;
}