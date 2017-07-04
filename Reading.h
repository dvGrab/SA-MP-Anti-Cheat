#ifndef READING_H
#define READING_H

#include "Main.h"

class CReading
{
public:
	int Listen(char * Buffer);

	char Temp[256];
};
extern CReading Reading;

#endif