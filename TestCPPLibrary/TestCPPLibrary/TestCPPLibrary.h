// TestCPPLibrary.h
#pragma once
#include "stdafx.h"
extern "C" {
	Queue<posPacket*> packetQueue(10,100);

	__declspec(dllexport) bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
	__declspec(dllexport) bool SendPosition(int* data);
	__declspec(dllexport) bool ReceiveInformation();
	__declspec(dllexport) bool PacketCheck();
	__declspec(dllexport) posPacket* PacketGet();
	void Receive();
}
