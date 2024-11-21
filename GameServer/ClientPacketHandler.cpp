#include "pch.h"
#include "ClientPacketHandler.h"

#include "GameManager.h"
#include "ClientPacketHandler.h"

void ClientPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[C_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Login>(Handle_C_LOGIN, session, buffer, len);
		};
	packetHandlers[C_REGISTER] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::C_Register>(Handle_C_REGISTER, session, buffer, len);
		};
}

bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet)
{
	string id = packet.id();
	string pw = packet.pw(); 

	Protocol::S_Login sendPacket;

	bool success = GameManager::Get().CheckUser(id);
	
	if (success)
	{
		success = (pw == GameManager::Get().GetPW(id));
	}

	sendPacket.set_success(success);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
	session->Send(sendBuffer);
	

	return true;
}

bool Handle_C_REGISTER(shared_ptr<PacketSession>& session, Protocol::C_Register& packet)
{
	string id = packet.id();
	string pw = packet.pw();
	string name = packet.name();
	bool success = GameManager::Get().CheckUser(id);
	//Todo
	return false;
}
			 
