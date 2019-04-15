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

/*
void CallbackFunc(SOCKET cSocket, sockaddr_in c, char cIp[256], command cmd) {
	// Create the players
	
	if (ClientManager().playerCount == -1) {
		ClientManager().playerArray = new Player[12];
		ClientManager().playerCount = 0;
	}
	
	// Connect Command
	if (cmd.cmd == statusList.connect.sts) {
		ClientManager().playerArray[ClientManager().playerCount] = Player(cIp, ClientManager().playerCount,(string)("EVERYONE IS BOB"),Vector2(0.0f,0.0f),c);
		ClientManager().playerCount++;
		SendMessageToClient(cSocket, c, statusList.connect, "Someone has connected from " + string(cIp), "Client connection error! ");
	}

	if (cmd.cmd == 's')
	{
		for (int i = 0; i < typeAmt; i++)
		{
			gamePacket g = gamePacket();

			if (packetList[i].id == ((gamePacket*)(&clientCommand.payload))->id)//update the packet
			{
				packetList[i] = *((gamePacket*)(&clientCommand.payload));
				if (packetList[i].autoUpdate)
				{
					for (int i = 0; i < ClientManager().playerCount; i++)
					{
						int sendOk;

						sendOk = sendto(clientSocket, (char*)&packetList[i], 128, 0, (sockaddr*)&ClientManager().playerArray[i].sockaddr_in, sizeof(ClientManager().playerArray[i].sockaddr_in));
						cout << "success" << endl;

						if (sendOk == SOCKET_ERROR)
						{
							cout << "error" << WSAGetLastError() << endl;
						}

					}
				}
			}
		}
	}
	else if (clientCommand.cmd == 'r')
	{
		for (int i = 0; i < typeAmt; i++)
		{
			gamePacket g = gamePacket();

			if (packetList[i].id == ((gamePacket*)(&clientCommand.payload))->id)//update the packet
			{
				for (int i = 0; i < ClientManager().playerCount; i++)
				{
					int sendOk;

					sendOk = sendto(clientSocket, (char*)&packetList[i], 128, 0, (sockaddr*)&ClientManager().playerArray[i].sockaddr_in, sizeof(ClientManager().playerArray[i].sockaddr_in));
					cout << "success" << endl;

					if (sendOk == SOCKET_ERROR)
					{
						cout << "error" << WSAGetLastError() << endl;
					}

				}
			}
		}
	}
}
*/

void main()
{
	//callback serverCallback = CallbackFunc;
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
				for (size_t i = 0; i < clientManager.playerCount; i++)
				{
					Player p = clientManager.playerArray[i];
					SendMessageToClient(p.sockaddr_in, statusList.connect, "Someone has connected from " + packet.clientIp, "Client connection error! ");
				}
			}
		}
	}
}