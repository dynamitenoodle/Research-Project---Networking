#include "Commands.h"

Commands::Commands()
{
	// Connect Command
	connect.cmd = 'c';
	ZeroMemory(connect.payload, 127);

	// Display Command
	display.cmd = 'd';
	ZeroMemory(display.payload, 127);

	// Leave Command
	leave.cmd = 'l';
	ZeroMemory(leave.payload, 127);
	
	// Test Connection Command
	testConnect.cmd = 't';
	ZeroMemory(testConnect.payload, 127);
	strcpy_s(testConnect.payload, "Are we connected?");
}


Commands::~Commands()
{
}
