#include "pch.h"
#include "ServerPacketHandler.h"



void ServerPacketHandler::Init()
{
	PacketHandler::Init();

	packetHandlers[S_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{ return HandlePacket<Protocol::S_Login>(Handle_S_LOGIN, session, buffer, len);	 };
	packetHandlers[S_ENTER_GAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{ return HandlePacket<Protocol::S_EnterGame>(Handle_S_ENTER_GAME, session, buffer, len);	 };
	packetHandlers[S_CHAT] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{ return HandlePacket<Protocol::S_Chat>(Handle_S_CHAT, session, buffer, len);	 };
	packetHandlers[S_JOIN_GAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{ return HandlePacket<Protocol::S_JoinGame>(Handle_S_JOIN_GAME, session, buffer, len);	 };
}


bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Invalid handle\n");
	return false;
}

bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet)
{

	if (!packet.success())
	{
		session->Disconnect(L"Refused");
		return false;
	}

	printf("Connected\n");
	Protocol::C_EnterGame sendPacket;

	Protocol::Player* player = new Protocol::Player;
	player->set_id(packet.playerid());
	player->set_name("TEST");

	sendPacket.set_allocated_player(player);
										   	

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);


	return true;
}

bool Handle_S_ENTER_GAME(shared_ptr<PacketSession>& session, Protocol::S_EnterGame& packet)
{
	
	if (packet.success())
	{
		for (int i = 0; i < packet.players_size(); i++)
		{
			const Protocol::Player& player = packet.players(i);
			printf("Player ID : %d, Player Name : %s\n", player.id(), player.name().c_str());

		}
	}
	else
	{
		session->Disconnect(L"Can not enter the game");
	}


	return false;
}

bool Handle_S_CHAT(shared_ptr<PacketSession>& session, Protocol::S_Chat& packet)
{
	return false;
}

bool Handle_S_JOIN_GAME(shared_ptr<PacketSession>& session, Protocol::S_JoinGame& packet)
{
	auto& p = packet.player();
	printf("%s_%d�� �����߽��ϴ�.\n", p.name().c_str(), p.id());

	//Todo
	return true;
}
