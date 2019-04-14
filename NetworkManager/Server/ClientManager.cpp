#include "pch.h"
#include "Player.h"
#include "ClientManager.h"

Player* ClientManager::playerArray;
int ClientManager::playerCount;

ClientManager::ClientManager()
{
	playerCount = -1;
}

ClientManager::~ClientManager()
{

}
