#include "pch.h"
#include "ClientPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>


void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
	packetHandlers[C_ENTER_GAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::C_ENTER_GAME>(Handle_C_ENTER_GAME, session, buffer, len); 	};

	packetHandlers[C_LOGOUT] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{  return HandlePacket<Protocol::C_LOGOUT>(Handle_C_LOGOUT, session, buffer, len); };

	packetHandlers[C_MOVE] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{	return HandlePacket<Protocol::C_MOVE>(Handle_C_MOVE, session, buffer, len); 	};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}
	 
bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_LOGIN& packet)
{
	printf("Client Login");
	Protocol::S_LOGIN sendPacket;

	Protocol::Player* player = new Protocol::Player();
	player->set_id(0);
	player->set_x(0);
	player->set_y(0);
	player->set_z(0);
	player->set_yaw(0);

	sendPacket.set_success(true);
	sendPacket.set_allocated_player(player);

	shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
	
	return true;
}

bool Handle_C_ENTER_GAME(shared_ptr<PacketSession>& session, Protocol::C_ENTER_GAME& packet)
{
	printf("Enter Game");
	return false;
}

bool Handle_C_LOGOUT(shared_ptr<PacketSession>& session, Protocol::C_LOGOUT& packet)
{
	return false;
}

bool Handle_C_MOVE(shared_ptr<PacketSession>& session, Protocol::C_MOVE& packet)
{
	return false;
}
