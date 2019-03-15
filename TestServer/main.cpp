#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Status.h"

/* 
	IGME 589.02 - Networking Project
*/ 

void main()
{
	// seeds the random
	srand(time(NULL));

	// creates the status list
	Status statusList;

	// Startup Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk;
	}

	// Bind socket to ip address and port
	SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;

	// sets up the IP with input
	//string myIp = "129.21.178.67";
	cout << "Please enter the IP of this machine" << endl;
	int ipNum;
	string ip = "";
	for (int i = 0; i < 4;)
	{
		cout << "Insert a value for the " << i << " digit in the ip (0 - 255)" << endl;
		string input;
		getline(cin, input);
		cout << endl;

		ipNum = stoi(input);

		if (ipNum >= 0 || ipNum <= 255)
		{
			if (i < 3)
			{
				ip += input + ".";
				i++;
			}
			else
			{
				ip += input;
				i++;
			}
		}
	}

	// gets input for the port
	int port = -1;
	while (port < 1024 || port > 65535)
	{
		cout << "Insert a port value (1024-65535)" << endl;
		string input;
		getline(cin, input);
		cout << endl;

		port = stoi(input);
	}

	// converts from string to binary for address
	inet_pton(AF_INET, ip.c_str(), &serverHint.sin_addr); // address is for THIS computer, use ipconfig in command prompt
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(port); // Convert from little to big endian

	// binds the socket for the client to use
	if (bind(clientSocket, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}

	// creates the client
	sockaddr_in client;
	int clientLength = sizeof(client);

	// Create the players
	int playerCount = 0;
	Player* playerArray = new Player[10];

	// Enter a loop
	while (true)
	{
		cout << endl;
		// Wait for a client command
		command clientCommand;
		ZeroMemory((char*)&clientCommand, 128);
		ZeroMemory(&client, clientLength);

		int bytesIn = recvfrom(clientSocket, (char*)&clientCommand, 128, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}

		// Display the client info and payload
		char clientIp[256];
		ZeroMemory(clientIp, 256);

		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

		int sendOk;

		// Connect Command
		if (clientCommand.cmd == statusList.connect.sts)
		{
			sendOk = sendto(clientSocket, (char*)&statusList.connect, 128, 0, (sockaddr*)&client, clientLength);
			cout << "Someone has connected from " << clientIp << endl;
		}

		if (sendOk == SOCKET_ERROR)
		{
			cout << "that didn't work! " << WSAGetLastError() << endl;
		}
	}

	// close socket
	closesocket(clientSocket);

	// shutdown winsock
	WSACleanup();
}
