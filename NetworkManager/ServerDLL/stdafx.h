// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>



// reference additional headers your program requires here
#include <vector>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <cstdlib>
#include <time.h> 
#include <stdio.h>
#include "queue.h"
#include <thread>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

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

struct clientPacketData {
	clientPacketData() {
		cmd.cmd = (char)' ';
	}
	clientPacketData(sockaddr_in cli, char cIp[256], command c) {
		client = cli;
		clientIp = string(cIp);
		cmd = c;
	}
	sockaddr_in client;
	string clientIp;
	command cmd;
};