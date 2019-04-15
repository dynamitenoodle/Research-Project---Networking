// TestCPPLibrary.h
#pragma once
#include "stdafx.h"
extern "C" {
	__declspec(dllexport) bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
	__declspec(dllexport) bool SendPosition(float x, float y);
	__declspec(dllexport) float GetPosition(int id, bool isX);
	__declspec(dllexport) int PosAmt();
}
