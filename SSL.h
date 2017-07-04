#ifndef CSSL_H
#define CSSL_H

#include "Main.h"

class CSSL
{
public:
	void Initialize(void);
	void Destroy(void);
	void Shutdown(SSL *Object);
};
extern CSSL OpenSSL;

#endif