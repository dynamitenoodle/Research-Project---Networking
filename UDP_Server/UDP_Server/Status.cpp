#include "Status.h"

Status::Status()
{
	// Welcome Status
	ZeroMemory((char*)&connect, 128);
	connect.sts = 'c';
	strcpy_s(connect.payload, "Welcome to the dungeon ...");

	ZeroMemory((char*)&display, 128);
	display.sts = 'd';
	strcpy_s(display.payload, "Displaying Dungeon...");

	ZeroMemory((char*)&testConnect, 128);
	testConnect.sts = 't';
	strcpy_s(connect.payload, "Test Accomplished");

	ZeroMemory((char*)&leave, 128);
	leave.sts = 'l';
	strcpy_s(connect.payload, "Leaving...");
}


Status::~Status()
{
}
