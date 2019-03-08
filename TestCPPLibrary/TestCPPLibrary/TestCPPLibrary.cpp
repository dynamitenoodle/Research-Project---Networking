// TestCPPLibrary.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "TestCPPLibrary.h"
#include "stdafx.h"

using namespace std;
extern "C" 
{
	float __declspec(dllexport) TestMultiply(float a, float b)
	{
		return a * b;
	}

	float __declspec(dllexport) TestDivide(float a, float b)
	{
		if (b == 0) {
			return 0;
			//throw invalid_argument("b cannot be zero!");
		}

		return a / b;
	}

	bool __declspec(dllexport) Connect(int ip0, int ip1, int ip2, int ip3, int port)
	{
		bool connectionSuccess = false;
		ofstream myfile;
		myfile.open("test.txt", ios::out | ios::trunc);
		myfile << "We got in!./n";

		// Startup Winsock
		/*
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		myfile << "Starting up WinSock!./n" << endl;
		int wsOk = WSAStartup(version, &data);
		if (wsOk != 0)
		{
			//cout << "Can't start Winsock! " << wsOk;
			myfile << "Failed right at the start./n" << endl;
			myfile.close();
			return connectionSuccess;
		}
		myfile << "Past WSA startup./n";
		*/

		myfile << "Setting up IP!./n";
		// sets up the IP with input
		//string myIp = "129.21.178.67";
		int ipNum;
		string ip = "";
		ip += ip0 + ".";
		ip += ip1 + ".";
		ip += ip2 + ".";
		ip += ip3;

		// Create a hint structure for the server
		sockaddr_in serverHint;
		serverHint.sin_family = AF_INET;
		serverHint.sin_port = htons(port);

		//myfile << "IP: " << ip << "      PORT: " << port << "/n";
		myfile << "Setup IP./n";
		myfile << "IP: " << ip;
		myfile << "PORT: " << port;
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

		command connect;
		ZeroMemory((char*)&connect, 128);
		connect.cmd = 'c';

		myfile << "Preparing the test connection./n";
		// Test the connection to the server
		//cout << "Testing connection to server, if the next message does not appear please restart the program" << endl;
		int testSend = sendto(serverSocket, (char*)&connect, 128, 0, (sockaddr*)&serverHint, serverLength);
		if (testSend == SOCKET_ERROR)
		{
			//cout << "Sending the test message didn't work : " << WSAGetLastError() << endl;
			myfile << "Failed the test connection./n";
			myfile.close();
			return connectionSuccess;
		}
		else
		{
			myfile << "Succeded the test connection./n";
		}

		// Wait for a response from the server
		myfile << "Preparing to receive from server connection./n";
		int bytesInTest = recvfrom(serverSocket, (char*)&serverStatus, 128, 0, (sockaddr*)&serverHint, &serverLength);
		if (bytesInTest == SOCKET_ERROR)
		{
			//cout << "Error receiving from client " << WSAGetLastError() << endl;
			myfile << "Did not receive from the server./n";
			myfile.close();
			return connectionSuccess;
		}
		else
		{
			myfile << "We got word from the server!/n";
			connectionSuccess = true;
		}

		myfile << "Closed the file!/n";
		myfile.close();
		return connectionSuccess;
	}

}