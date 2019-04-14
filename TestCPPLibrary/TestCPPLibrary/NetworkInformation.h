#pragma once

namespace NetworkInfo
{
	class NetworkInformation
	{
	public:
		// Information that we need saved
		ofstream myfile;
		string ip;
		sockaddr_in serverHint;
		int serverLength;
		SOCKET serverSocket;
		char* serverIP;
		status serverStatus;

	private:

	};

	static NetworkInformation myInfo;
}
