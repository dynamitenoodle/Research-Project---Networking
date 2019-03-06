// TestCPPLibrary.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "TestCPPLibrary.h"
#include "stdafx.h"

using namespace std;
extern "C" {
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

	string __declspec(dllexport) TestString()
	{
		string returnStr = "Hello World";
		return returnStr;
	}

}