#include "pch.h"
#include "ClientPacketHandler.h"
#include "GameManager.h"

void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Login>(Handle_C_LOGIN, session, buffer, len);
		};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet)
{
	printf("Name : %s, ID : %s, PW : %s", packet.name().c_str(), packet.id().c_str(), packet.pw().c_str());
	
	GameManager::Get().playerName.insert(packet.name().c_str());
	//Todo
	return true;
}

