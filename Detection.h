#ifndef DETECTION_H
#define DETECTION_H

#include "Main.h"

#define MAX_ASI_FILES 64
#define MAX_ASI_SIZE 256

class CDetection
{
public: 
	char ASI_FILES[MAX_ASI_FILES][MAX_ASI_SIZE];
	int CheatKey;

	void Routine(void);
	bool MemoryEditor(void);
	bool ASICheck(void);
};
extern CDetection Detection;

#endif 