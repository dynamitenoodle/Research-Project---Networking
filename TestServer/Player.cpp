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
}

Player::~Player()
{
}

string Player::GetName()
{
	string name(this->name);
	return name;
}

string Player::GetIp()
{
	string clientIp(this->clientIp);
	return clientIp;
}

