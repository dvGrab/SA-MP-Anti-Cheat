#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <Winsock.h>
#include <detours.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <FastCRC.h>

#include "Functions.h"
#include "Socket.h"
#include "Hooks.h"
#include "Calls.h"
#include "Config.h"
#include "Reading.h"
#include "Handle.h"
#include "MD5.h"

#pragma once
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "FastCRC.lib")

void Initialize();
void Startup();
void StartListen(void);

struct SSettings
{
	int Port;
	char Address[32];
};
extern SSettings Settings;

#endif