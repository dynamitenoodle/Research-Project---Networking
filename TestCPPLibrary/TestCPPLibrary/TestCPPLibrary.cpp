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
	std::vector<posPacket> PlayersLastKnownPositions = vector<posPacket>();
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

		// All receiving is now done in the receive thread
		/*
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
		*/
		myInfo.myfile << "Closed the file!" << endl;
		myInfo.myfile.close();
		
		return connectionSuccess;
	}

	bool __declspec(dllexport) ReceiveInformation()
	{
		static thread mainServerThread(Receive);
		
		return true;
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
			int bytesIn = recvfrom(myInfo.serverSocket, (char*)&myInfo.serverStatus, 128, 0, (sockaddr*)&myInfo.serverHint, &myInfo.serverLength);
			if (bytesIn == SOCKET_ERROR)
			{
				myInfo.myfile << "Error recieving from the server " << WSAGetLastError() << endl;
				continue;
			}

			//Display message and client info
			if (myInfo.serverStatus.sts == 'p')
			{
				// convert the payload back to a posPacket
				posPacket received = *((posPacket*)&myInfo.serverStatus.payload);

				myInfo.myfile << "Received ID : " << received.id << " with Position : " << received.pos << endl;
				//myInfo.myfile << "PlayerID : " << myInfo.serverStatus.payload is : " << myInfo.playerID << endl;
			}
			else if (myInfo.serverStatus.sts == 'c')
			{
				string myPayload(myInfo.serverStatus.payload);
				myInfo.playerID = (int)myInfo.serverStatus.payload;
				myInfo.myfile << "My ID is : " << myInfo.serverStatus.payload << endl;
			}
			else
			{
				myInfo.myfile << "Received Status '" << myInfo.serverStatus.sts << "' with Payload : " << myInfo.serverStatus.payload << endl;
			}
			/*
			if (myInfo.serverStatus.sts == 'c')
			{
			myInfo.myfile << "Received Status '" << myInfo.server << myInfo.serverStatus.payload << endl;
			}
			else
			{
			myInfo.myfile << myInfo.serverStatus.payload << endl;
			}
			*/
			/*
			bool contained = false;
			posPacket temp = *((posPacket*)((&myInfo.serverStatus) + 1));
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
			*/
		}

		myInfo.myfile << "Closing Receive function" << endl;
		myInfo.myfile.close();
	}
	
	bool __declspec(dllexport) SendPosition(float x, float y)
	{
		// create the position sending command
		command pos;
		ZeroMemory((char*)&pos, 128);
		pos.cmd = 'p';

		// creates the player position packet
		posPacket playerPacket;
		playerPacket.id = myInfo.playerID;

		playerPacket.pos = new float[2];
		playerPacket.pos[0] = x;
		playerPacket.pos[1] = y;

		strcpy_s(pos.payload, (char*)&playerPacket);

		// sends the players position to the server
		int testSend = sendto(myInfo.serverSocket, (char*)&pos, 128, 0, (sockaddr*)&myInfo.serverHint, myInfo.serverLength);
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