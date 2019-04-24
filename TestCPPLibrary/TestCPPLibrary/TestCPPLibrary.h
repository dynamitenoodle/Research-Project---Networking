// TestCPPLibrary.h
#pragma once
#include "stdafx.h"
extern "C" {
	__declspec(dllexport) bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
	__declspec(dllexport) bool SendPosition(float* data);
	__declspec(dllexport) bool ReceiveInformation();
	void Receive();
}
