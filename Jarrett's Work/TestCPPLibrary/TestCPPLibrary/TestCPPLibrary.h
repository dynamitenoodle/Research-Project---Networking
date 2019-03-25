// TestCPPLibrary.h
#pragma once

extern "C" {
	__declspec(dllexport) bool Connect(int ip0, int ip1, int ip2, int ip3, int port);

}
