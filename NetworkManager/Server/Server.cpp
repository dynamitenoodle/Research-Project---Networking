// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "pch.h"
#include <iostream>
#include "Player.h"
#include "Status.h"
#include "ClientManager.h"

/*
	IGME 589.02 - Networking Project
*/

typedef void(*callback)(SOCKET cSocket, sockaddr_in c, char cIp[256], command cmd);

__declspec(dllimport) void RunServer(); //callback serverCallback
__declspec(dllimport) void SendMessageToClient(sockaddr_in c, status s, string success, string error);
__declspec(dllimport) clientPacketData DequeuePacket();

Status statusList;

void main()
{
	ClientManager clientManager;
	RunServer();
	while (true) {
		clientPacketData packet = DequeuePacket();
		if (packet.cmd.cmd == (char)' ') {
			continue;
		}

		// Connect Command
		if (packet.cmd.cmd == statusList.connect.sts) {
			if (clientManager.playerCount < 12) {
				clientManager.playerArray[clientManager.playerCount] = Player(packet.clientIp, ClientManager().playerCount, (string)("EVERYONE IS BOB"), Vector2(0.0f, 0.0f), packet.client);
				clientManager.playerCount++;
				status cStatus;
				cStatus.sts = 'c';
				ZeroMemory(cStatus.payload, 127);
				//memcpy(cStatus.payload, (char*)&clientManager.playerCount, 127);
				strcpy_s(cStatus.payload, (char*)&clientManager.playerCount);
				for (size_t i = 0; i < clientManager.playerCount; i++)
				{
					Player p = clientManager.playerArray[i];
					SendMessageToClient(p.sockaddr_in, cStatus, "Someone has connected from " + packet.clientIp, "Client connection error! ");
				}
			}
		}

		else if (packet.cmd.cmd == 'p') {
			status pStatus;
			pStatus.sts = 'p';
			ZeroMemory(pStatus.payload, 127);
			memcpy(pStatus.payload, packet.cmd.payload, 127);
			//strcpy_s(pStatus.payload, (char*)&packet.cmd.payload);
			for (size_t i = 0; i < clientManager.playerCount; i++)
			{
				Player p = clientManager.playerArray[i];
				SendMessageToClient(p.sockaddr_in, pStatus, "Sending pos", "Pos relay error");
			}
		}
	}
}