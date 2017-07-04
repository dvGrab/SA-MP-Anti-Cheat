#ifndef READING_H
#define READING_H

#include "Main.h"

class CReading
{
public:
	int Listen(char * Buffer);
	void Name(void);
};
extern CReading Reading;

#endif