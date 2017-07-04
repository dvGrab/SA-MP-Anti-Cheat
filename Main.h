#ifndef MAIN_H
#define MAIN_H

#pragma warning(disable:4018)
#pragma warning(disable:4172)


#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <Winsock.h>
#include <detours.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <fstream>
#include <io.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "Functions.h"
#include "Socket.h"
#include "Hooks.h"
#include "Calls.h"
#include "Config.h"
#include "Reading.h"
#include "Handle.h"
#include "MD5.h"
#include "Informations.h"
#include "SSL.h"
#include "Detection.h"

#pragma once
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")


void Initialize();
void Startup();
void StartListen(void);

struct SSettings
{
	int Port;
	char Address[32];
	int Timeout;
};
extern SSettings Settings;

#endif

