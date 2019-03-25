// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "pch.h"
#include <iostream>
#include "Player.h"
#include "Status.h"

/*
	IGME 589.02 - Networking Project
*/


typedef void(*callback)(SOCKET cSocket, sockaddr_in c, char cIp[256], command cmd);

__declspec(dllimport) void RunServer(callback serverCallback);
__declspec(dllimport) void SendMessageToClient(SOCKET cSocket, sockaddr_in c, status s, string success, string error);

Status statusList;

void CallbackFunc(SOCKET cSocket, sockaddr_in c, char cIp[256], command cmd) {
	// Create the players
	static int playerCount = 0;
	static Player* playerArray = new Player[10];

	// Connect Command
	if (cmd.cmd == statusList.connect.sts) {
		SendMessageToClient(cSocket, c, statusList.connect, "Someone has connected from " + string(cIp), "Client connection error! ");
	}
}

void main()
{
	callback serverCallback = CallbackFunc;
	RunServer(serverCallback);
}
