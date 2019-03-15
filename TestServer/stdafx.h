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
