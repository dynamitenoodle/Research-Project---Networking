#pragma once
#include "stdafx.h"

class Player
{
public:
	Player();
	Player(char clientIp[256], int playerNum, string name);
	~Player();

	// Gets the player's name
	string GetName();

	// Gets the player's IP Address
	string GetIp();

	// Gets the player's Num
	int GetNum();

	Vector2 position(0,0);

private:
	char clientIp[256];
	int playerNum;
	string name;

};
