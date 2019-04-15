#pragma once
#include "targetver.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <fstream>
// use std chrono for timing if needed

#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

struct command
{
	unsigned char cmd; // 256 commands for now
	char payload[127]; // Some payload based on the command
};

struct status
{
	unsigned char sts; // 256 status tpyes for now
	char payload[127]; // Some payload based
};

struct posPacket
{
	int id;
	float pos[2];
};
