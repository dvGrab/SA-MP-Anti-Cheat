#ifndef HOOKS_H
#define HOOKS_H

#include "Main.h"

class CHooks
{
public:
	bool Unlocked;
	int Count;
	void Initialize(void);
};	
extern CHooks Hooks;

#endif //HOOKS_H