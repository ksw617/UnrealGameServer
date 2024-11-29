#include "pch.h"
#include "GameRoom.h"

#include "Player.h"
#include "ClientSession.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"


#include <locale>
#include <codecvt>
#include <string>


void GameRoom::AddPlayer(shared_ptr<Player> player)
{
	unique_lock<shared_mutex> lock(rwLock);

	Protocol::S_EnterRoom sendPacket;

	for (auto& other : players)
	{
		wstring_convert<codecvt_utf8<wchar_t>> converter;
		string utf8Name = converter.to_bytes(other->name);

		Protocol::Player* p = sendPacket.add_players();
		p->set_name(utf8Name);
		p->set_type((int)other->playerType);
	}
	
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	
	shared_ptr<Session> session = player->session.lock();
	if (session != nullptr)
	{
		session->Send(sendBuffer);
	}

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
