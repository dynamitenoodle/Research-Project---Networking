#include "Status.h"

Status::Status()
{
	// Welcome Status
	ZeroMemory((char*)&connect, 128);
	connect.sts = 'c';
	strcpy_s(connect.payload, "Connection Successful");

}

Status::~Status()
{
}
