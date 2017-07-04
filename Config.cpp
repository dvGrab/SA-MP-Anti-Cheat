#include "Config.h"

CConfig::CConfig(char * FileName)
{
	sprintf_s(Name, ".\\%s.ini", FileName);
	printf("CConfig::Config -> New config is loading! ('%s')\n", Name);
}

int CConfig::ReadInteger(char * AppName, char * KeyName, int Default)
{
	int Temp = FALSE;
	Temp = GetPrivateProfileInt(AppName, KeyName, NULL, Name);
	return Temp;
}

char * CConfig::ReadString(char * AppName, char * KeyName, char * Default)
{
	char Temp[256];
	GetPrivateProfileString(AppName, KeyName, Default, Temp, sizeof(Temp), Name);
	return Temp;
}

double CConfig::ReadFloat(char * AppName, char * KeyName, char * Default)
{
	char Temp[256];
	GetPrivateProfileString(AppName, KeyName, Default, Temp, sizeof(Temp), Name);
	return atof(Temp);
}

bool CConfig::ReadBool(char * AppName, char * KeyName, char * Default)
{
	char Temp[256];
	bool Value = FALSE;
	GetPrivateProfileString(AppName, KeyName, Default, Temp, sizeof(Temp), Name);

	if (strstr(Temp, "true"))
		Value = true;

	return Value;
}