// TestCPPLibrary.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "TestCPPLibrary.h"
#include "stdafx.h"
#include "NetworkInformation.h"

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

		// sets up the IP with input
		//string myIp = "129.21.178.67";
		//int ipNum;
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
		return connectionSuccess;
	}

}