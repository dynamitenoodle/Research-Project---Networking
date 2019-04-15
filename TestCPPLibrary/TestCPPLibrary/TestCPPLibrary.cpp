// TestCPPLibrary.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "stdafx.h"
#include "TestCPPLibrary.h"
#include "NetworkInformation.h"
#include <thread>
#include <Vector>

using namespace std;
using namespace NetworkInfo;
struct packet 
{
	char id;
	float* pos;
};
extern "C" 
{
	std::vector<packet> PlayersLastKnownPositions = vector<packet>();
	bool __declspec(dllexport) Connect(int ip0, int ip1, int ip2, int ip3, int port)
	{
		
		bool connectionSuccess = false;
		myInfo.myfile.open("DLL_Debug.txt");
		myInfo.myfile << "Started DLL Debug! " << endl;

		// Startup Winsock aaa
		myInfo.myfile << "Setting up IP!." << endl;
		
		myInfo.ip = "";
		
		myInfo.ip += to_string(ip0) + ".";
		myInfo.ip += to_string(ip1) + ".";
		myInfo.ip += to_string(ip2) + ".";
		myInfo.ip += to_string(ip3);

		// Create a hint structure for the server
		myInfo.serverHint.sin_family = AF_INET;
		myInfo.serverHint.sin_port = htons(port);
		myInfo.myfile << "Hint structure set up!" << endl;

		//myfile << "IP: " << ip << "      PORT: " << port << "/n"; aaa
		myInfo.myfile << "Setup IP" << endl;
		myInfo.myfile << "IP: " << myInfo.ip << endl;
		myInfo.myfile << "PORT: " << port << endl;

		// converts from string to binary for address
		inet_pton(AF_INET, myInfo.ip.c_str(), &myInfo.serverHint.sin_addr); // address is of the server
		myInfo.serverLength = sizeof(myInfo.serverHint);

		myInfo.myfile << "Creating the socket" << endl;
		// Socket creation
		SOCKET serverSocket;
		serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
		myInfo.myfile << "Setting the myInfo serverSocket variable" << endl;
		myInfo.serverSocket = serverSocket;

		// Getting the serverIp
		myInfo.myfile << "Clearing memory for IP" << endl;
		ZeroMemory((char*)&myInfo.serverIP, 256);

		myInfo.myfile << "Creating the Server IP" << endl;
		inet_ntop(AF_INET, &(myInfo.serverHint.sin_addr), myInfo.serverIP, 256);
		myInfo.myfile << "Server IP (sin_addr): " << &myInfo.serverIP << endl;

		// Preparing the status for the server
		ZeroMemory((char*)&myInfo.serverStatus, 128);

		// preparing the connect command
		command connect;
		ZeroMemory((char*)&connect, 128);
		connect.cmd = 'c';

		// Test the connection to the server
		myInfo.myfile << "Preparing the test connection." << endl;
		myInfo.myfile << "Testing connection to server, if the next message does not appear please restart the program." << endl;
		int testSend = sendto(myInfo.serverSocket, (char*)&connect, 128, 0, (sockaddr*)&myInfo.serverHint, myInfo.serverLength);
		myInfo.myfile << "testSend value: " << testSend << endl;
		if (testSend == SOCKET_ERROR)
		{
			//cout << "Sending the test message didn't work : " << WSAGetLastError() << endl;
			myInfo.myfile << "Failed the test connection." << endl;
			myInfo.myfile.close();
			return connectionSuccess;
		}
		else
		{
			myInfo.myfile << "Succeded the test connection." << endl;
		}

		// Wait for a response from the server
		myInfo.myfile << "Preparing to receive from server connection." << endl;
		int bytesInTest = recvfrom(myInfo.serverSocket, (char*)&myInfo.serverStatus, 128, 0, (sockaddr*)&myInfo.serverHint, &myInfo.serverLength);
		if (bytesInTest == SOCKET_ERROR)
		{
			//cout << "Error receiving from client " << WSAGetLastError() << endl;
			myInfo.myfile << "Did not receive from the server." << endl;
			myInfo.myfile.close();
			return connectionSuccess;
		}
		else
		{
			myInfo.myfile << "We got word from the server!" << endl;
			connectionSuccess = true;
		}

		myInfo.myfile << "Closed the file!" << endl;
		myInfo.myfile.close();
		std::thread Recieve = std::thread([serverSocket]
		{

			//SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
			sockaddr_in clientRecv;//setup client reciever

			char buf[1024];
			ZeroMemory(buf, 1024);
			int* serverLength = new int((sizeof(clientRecv)));
			while (true)
			{

				int bytesIn = recvfrom(serverSocket, buf, 128, 0, (sockaddr*)&clientRecv, serverLength);
				if (bytesIn == SOCKET_ERROR)
				{
					std::cout << "Error recieving from the server " << WSAGetLastError() << std::endl;
					continue;
				}
				//Display message and client info
				char clientIp[256];
				ZeroMemory(clientIp, 256);

				inet_ntop(AF_INET, &clientRecv.sin_addr, clientIp, 256);
				bool contained = false;
				packet temp = *((packet*)((&buf) + 1));
				for (size_t i = 0; i < PlayersLastKnownPositions.size(); i++)
				{
					if (PlayersLastKnownPositions[i].id == temp.id) 
					{
						PlayersLastKnownPositions[i] = temp;
						contained = true;
					}
				}
				if (!contained)
				{
					PlayersLastKnownPositions.push_back(temp);
				}

			}
		});
		return connectionSuccess;

	}
	
	bool __declspec(dllexport) SendPosition(float x, float y)
	{
		command Pos;
		ZeroMemory((char*)&Pos, 128);
		Pos.cmd = 'p';
		float* t = new float[2];
		t[0] = x;
		t[1] = y;
		int testSend = sendto(myInfo.serverSocket, (char*)&t, 128, 0, (sockaddr*)&myInfo.serverHint, myInfo.serverLength);
		
		if (testSend == SOCKET_ERROR)
		{
			return false;
		}
		return true;
	}

	float __declspec(dllexport) GetPosition(int id, bool isX)
	{
		if (isX) 
		{
			return PlayersLastKnownPositions[id].pos[0];
		}
		return PlayersLastKnownPositions[id].pos[1];
	}
	int __declspec(dllexport) PosAmt()
	{
		return (int)PlayersLastKnownPositions.size();
	}


	
}