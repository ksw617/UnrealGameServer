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
	//패킷 구조체
	Protocol::C_Login sendPacket;
	//패킷을 보낼수있게 바이트 단위로 변환
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

	//해당 버퍼 보내기
	session->Send(sendBuffer);
	return true;
}