#include "pch.h"
#include "ServerPacketHandler.h"


void ServerPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[S_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len) 
		{
			return HandlePacket<Protocol::S_Login>(Handle_S_LOGIN, session, buffer, len);
		};
}


bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet)
{
	if (!packet.success())
	{
		session->Disconnect(L"Refused");
		return false;
	}

	printf("Handle_S_LOGIN\n");
	Protocol::C_EnterGame sendPacket;

	Protocol::Player* player = new Protocol::Player;
	player->set_id(packet.playerid());
	player->set_name("TEST");

	sendPacket.set_allocated_player(player);

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);


	return true;
}