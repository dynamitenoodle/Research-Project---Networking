#pragma once
#include "pch.h"

class Player
{
public:
	Player();
	Player(char clientIp[256], int playerNum, string name, Vector2 posOrg, sockaddr_in sock);
	~Player();

	// Gets the player's name
	string GetName();

	sockaddr_in sockaddr_in;
	// Gets the player's IP Address
	string GetIp();

	// Gets the player's Num
	int GetNum();

	Vector2 position;

private:
	char clientIp[256];
	int playerNum;
	string name;

};
