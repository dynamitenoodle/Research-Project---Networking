#include "pch.h"
#include "Player.h"

Player::Player()
{
	this->clientIp = "";
	this->playerNum = 0;
	this->name = "";

}

Player::Player(string clientIp, int playerNum, string name, Vector2 posOrg, ::sockaddr_in sock)
{
	this->clientIp = clientIp;
	this->playerNum = playerNum;
	this->name = name;
	this->sockaddr_in = sock;
	// add vector stuff here
	this->position = posOrg;
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
