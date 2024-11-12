#include "pch.h"
#include "ClientPacketHandler.h"

void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Login>(Handle_C_LOGIN, session, buffer, len);
		};
	packetHandlers[C_ENTER_GAME] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_EnterGame>(Handle_C_ENTER_GAME, session, buffer, len);
		};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet)
{
	printf("Handle_C_LOGIN\n");
	Protocol::S_Login sendPacket;
	sendPacket.set_success(true);
	sendPacket.set_playerid(1);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_ENTER_GAME(shared_ptr<PacketSession>& session, Protocol::C_EnterGame& packet)
{
	auto& p = packet.player();
	printf(p.name().c_str());
	return false;
}
