#include "Player.h"

Player::Player()
{
	strcpy_s(this->clientIp, "0");
	this->playerNum = 0;
	this->name = "";

}

Player::Player(char clientIp[256], int playerNum, string name)
{
	strcpy_s(this->clientIp, clientIp);
	this->playerNum = playerNum;
	this->name = name;
	
	// add vector stuff here

}

Player::~Player()
{
}

string Player::GetName()
{
	return this->name;
}

string Player::GetIp()
{
	string clientIp(this->clientIp);
	return clientIp;
}

int Player::GetNum()
{
	return this->playerNum;
}
