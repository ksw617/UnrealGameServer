#pragma once
#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 0,
	S_LOGIN = 1,
	C_ENTER_GAME = 2,
};

//Recv
//�������� S_LOGIN�� �������� ���⼭ ȣ��Ǵ�
bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet);

class ServerPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//Ŭ���̾�Ʈ�� ���� ��Ŷ�� ����
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Login& packet) { return PacketHandler::MakeSendBuffer(packet, C_LOGIN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_EnterGame& packet) { return PacketHandler::MakeSendBuffer(packet, C_ENTER_GAME); }
};

