#include "pch.h"
#include "GameRoom.h"

#include "Player.h"
#include "ClientSession.h"

void GameRoom::AddPlayer(shared_ptr<Player> player)
{
	unique_lock<shared_mutex> lock(rwLock);
	players.insert(player);
}

void GameRoom::RemovePlayer(shared_ptr<Player> player)
{
	unique_lock<shared_mutex> lock(rwLock);
	players.erase(player);
}

void GameRoom::BroadCast(shared_ptr<class SendBuffer> sendBuffer)
{
	shared_lock<shared_mutex> lock(rwLock);
	for (auto& player : players)
	{
		shared_ptr<Session> session = player->session.lock();
		if (session != nullptr)
		{
			session->Send(sendBuffer);
		}

	}
}
