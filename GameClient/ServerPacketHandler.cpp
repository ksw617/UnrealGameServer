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
	//��Ŷ ����ü
	Protocol::C_Login sendPacket;
	//��Ŷ�� �������ְ� ����Ʈ ������ ��ȯ
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

	//�ش� ���� ������
	session->Send(sendBuffer);
	return true;
}