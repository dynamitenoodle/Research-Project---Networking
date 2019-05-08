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

extern "C" 
{
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
			connectionSuccess = true;
		}

		myInfo.myfile << "Closed the file!" << endl;
		myInfo.myfile.close();
		
		return connectionSuccess;
	}

	bool __declspec(dllexport) ReceiveInformation()
	{
		static thread mainServerThread(Receive);
		
		return true;
	}

	bool PacketCheck()
	{
		return !packetQueue.IsEmpty();
	}

	posPacket * PacketGet()
	{
		return packetQueue.Pop();
	}

	void Receive()
	{
		//SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
		myInfo.myfile.open("Receive_Debug.txt");
		sockaddr_in clientRecv;//setup client reciever

		myInfo.myfile << "Preparing to receive" << endl;
		ZeroMemory((char*)&myInfo.serverStatus, 128);
		while (true)
		{
			int bytesIn = recvfrom(myInfo.serverSocket, (char*)&myInfo.serverStatus, 128, 0, (sockaddr*)&myInfo.serverHint, 
				&myInfo.serverLength);
			if (bytesIn == SOCKET_ERROR)
			{
				myInfo.myfile << "Error recieving from the server " /*<< WSAGetLastError()*/ << endl;
				continue;
			}

			// If we receive a position Packet
			if (myInfo.serverStatus.sts == 'p')
			{
				// convert the payload back to a posPacket
				posPacket* received = (posPacket*)&myInfo.serverStatus.payload;

				packetQueue.Push(received);

				myInfo.myfile << "Received ID : " << received->id << " with Position X: " << received->xPos 
					<< " Y: " << received->yPos << endl;
				myInfo.myfile << "CannonAngle : " << received->cannonAngle << " Firing: " << received->firing << endl;
			}

			// If we receive a Connection Packet
			else if (myInfo.serverStatus.sts == 'c')
			{
				string myPayload(myInfo.serverStatus.payload);
				myInfo.playerID = (int)myInfo.serverStatus.payload;
				myInfo.myfile << "Connect status received" << endl;
				myInfo.myfile << "My ID is : " << myInfo.playerID << endl;
			}

			// If we receive an unknown Packet
			else
			{
				myInfo.myfile << "Received Status '" << myInfo.serverStatus.sts << "' with Payload : " 
					<< myInfo.serverStatus.payload << endl;
			}

			myInfo.myfile << endl;
		}

		myInfo.myfile << "Closing Receive function" << endl;
		myInfo.myfile.close();
	}
	
	bool __declspec(dllexport) SendPosition(int* data)
	{
		// creates the player position packet
		posPacket* playerPacket = (posPacket*)data;
		playerPacket->id = myInfo.playerID; 
		
		myInfo.myfile << "My ID: " << playerPacket->id << endl;
		myInfo.myfile << "Preparing to send Position with X: " << playerPacket->xPos << " Y: " << playerPacket->yPos << endl;
		myInfo.myfile << "CannonAngle: " << playerPacket->cannonAngle << " Firing: " << playerPacket->firing << endl;

		// create the position sending command
		command pos;
		ZeroMemory((char*)&pos, 128);
		pos.cmd = 'p';

		memcpy(pos.payload, (char*)&playerPacket, 127);

		// sends the players position to the server
		int testSend = sendto(myInfo.serverSocket, (char*)&pos, 128, 0, (sockaddr*)&myInfo.serverHint, myInfo.serverLength);
		if (testSend == SOCKET_ERROR)
		{
			return false;
		}
		myInfo.myfile << "Sent Position"<< endl;
		return true;
	}
}