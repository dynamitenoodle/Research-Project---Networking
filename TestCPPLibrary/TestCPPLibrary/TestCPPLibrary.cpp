// TestCPPLibrary.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "TestCPPLibrary.h"
#include "stdafx.h"

using namespace std;
extern "C" 
{
	bool __declspec(dllexport) Connect(int ip0, int ip1, int ip2, int ip3, int port)
	{
		bool connectionSuccess = false;
		ofstream myfile;
		myfile.open("DLL_Debug.txt");
		myfile << "Started DLL Debug! " << endl;

		// Startup Winsock aaa
		myfile << "Setting up IP!./n";

		// sets up the IP with input
		//string myIp = "129.21.178.67";
		int ipNum;
		string ip = "";
		
		ip += to_string(ip0) + ".";
		ip += to_string(ip1) + ".";
		ip += to_string(ip2) + ".";
		ip += to_string(ip3);

		// Create a hint structure for the server
		sockaddr_in serverHint;
		serverHint.sin_family = AF_INET;
		serverHint.sin_port = htons(port);
		myfile << "Hint structure set up!" << endl;

		//myfile << "IP: " << ip << "      PORT: " << port << "/n"; aaa
		myfile << "Setup IP" << endl;
		myfile << "IP: " << ip << endl;
		myfile << "PORT: " << port << endl;

		// converts from string to binary for address
		inet_pton(AF_INET, ip.c_str(), &serverHint.sin_addr); // address is of the server
		int serverLength = sizeof(serverHint);

		// Socket creation
		SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

		// Getting the serverIp
		char serverIp[256];
		ZeroMemory(serverIp, 256);

		inet_ntop(AF_INET, &serverHint.sin_addr, serverIp, 256);

		// Preparing the status for the server
		status serverStatus;
		ZeroMemory((char*)&serverStatus, 128);

		// preparing the connect command
		command connect;
		ZeroMemory((char*)&connect, 128);
		connect.cmd = 'c';

		// Test the connection to the server
		myfile << "Preparing the test connection." << endl;
		myfile << "Testing connection to server, if the next message does not appear please restart the program." << endl;
		int testSend = sendto(serverSocket, (char*)&connect, 128, 0, (sockaddr*)&serverHint, serverLength);
		if (testSend == SOCKET_ERROR)
		{
			//cout << "Sending the test message didn't work : " << WSAGetLastError() << endl;
			myfile << "Failed the test connection." << endl;
			myfile.close();
			return connectionSuccess;
		}
		else
		{
			myfile << "Succeded the test connection." << endl;
		}

		// Wait for a response from the server
		myfile << "Preparing to receive from server connection." << endl;
		int bytesInTest = recvfrom(serverSocket, (char*)&serverStatus, 128, 0, (sockaddr*)&serverHint, &serverLength);
		if (bytesInTest == SOCKET_ERROR)
		{
			//cout << "Error receiving from client " << WSAGetLastError() << endl;
			myfile << "Did not receive from the server." << endl;
			myfile.close();
			return connectionSuccess;
		}
		else
		{
			myfile << "We got word from the server!" << endl;
			connectionSuccess = true;
		}

		myfile << "Closed the file!" << endl;
		myfile.close();
		return connectionSuccess;
	}

}