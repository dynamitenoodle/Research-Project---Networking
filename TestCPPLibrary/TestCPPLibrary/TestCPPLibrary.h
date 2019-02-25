// TestCPPLibrary.h
#pragma once

extern "C" {
	__declspec(dllexport) float TestMultiply(float a, float b);
	__declspec(dllexport) float TestDivide(float a, float b);
	__declspec(dllexport) string TestString();
}