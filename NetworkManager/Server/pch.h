// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <cstdlib>
#include <time.h> 
#include <stdio.h>
#include "Vector2.h"

// use std chrono for timing if needed

#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "..\\x64\\Debug\\ServerDLL.lib")

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

struct gamePacket
{
	unsigned int id;
	char data[127];
	bool autoUpdate;
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


//gamePacket packetList[1024];
#endif //PCH_H
