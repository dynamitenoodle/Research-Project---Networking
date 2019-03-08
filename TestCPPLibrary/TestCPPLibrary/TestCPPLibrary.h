// TestCPPLibrary.h
#pragma once

extern "C" {
	__declspec(dllexport) float TestMultiply(float a, float b);
	__declspec(dllexport) float TestDivide(float a, float b);

	__declspec(dllexport) bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
}