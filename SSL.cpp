#include "SSL.h"

void CSSL::Initialize(void)
{
	OpenSSL_add_all_algorithms();
	SSL_library_init();
	SSL_load_error_strings();
}

void CSSL::Destroy(void)
{
	EVP_cleanup();
}

void CSSL::Shutdown(SSL *Object)
{
	SSL_shutdown(Object);
	SSL_free(Object);
}