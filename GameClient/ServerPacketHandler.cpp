#include "pch.h"
#include "ServerPacketHandler.h"

#include "SceneManager.h"


void ServerPacketHandler::Init()
{
	PacketHandler::Init();

	//Recv
	packetHandlers[S_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len) 
		{
			return HandlePacket<Protocol::S_Login>(Handle_S_LOGIN, session, buffer, len);
		};
	packetHandlers[S_REGISTER] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
		{
			return HandlePacket<Protocol::S_Register>(Handle_S_REGISTER, session, buffer, len);
		};
}


bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
{
	printf("Handle_INVALID\n");
	return false;
}

bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet)
{
	if (packet.success())
	{
		SceneManager::Get().LoardScene(SCENE_ID::ENTERGAME);
	}
	else
	{
		SceneManager::Get().LoardScene(SCENE_ID::REGISTER);
	}

	return true;
}

bool Handle_S_REGISTER(shared_ptr<PacketSession>& session, Protocol::S_Register& packet)
{
	//Todo
	return false;
}
