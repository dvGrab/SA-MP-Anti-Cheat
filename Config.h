#ifndef CONFIG_H
#define CONFIG_H

#include "Main.h"

class CConfig
{
private:

public:
	char Name[MAX_PATH];
	CConfig(char * FileName);
	int ReadInteger(char * AppName, char * KeyName, int Default);
	char * ReadString(char * AppName, char * KeyName, char * Default);
	float CConfig::ReadFloat(char * AppName, char * KeyName, char * Default);
	bool ReadBool(char * AppName, char * KeyName, char * Default);
};
extern CConfig Config;

#endif