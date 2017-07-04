#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include "Main.h"

class CInformations
{
public:
	char * GetPlayerName(void);
	char * GetServerIP(void);
	void SendPong(char * szPing);
	void Popup(char * szText);
	int Authorize(void);
	char * ComputerName(void);
	char * GetProductID(void);
	char * ReadRegistry(char * szPath, char * szValue);
	char * GetHWID(void);
	char * GetDirectory(void);
	void SendModules(void);
	void Kicked(char * szMsg);
	void GiveMD5File(char * szText);
};
extern CInformations Informations;

#endif