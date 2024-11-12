#pragma once

#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 0,
	S_LOGIN = 1,

};

//Recv
//Ŭ�󿡼� C_LOGIN�� �������� ���⼭ ȣ��Ǵ�
bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet);

class ClientPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//Ŭ���̾�Ʈ�� ���� ��Ŷ�� ����
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_Login& packet) { return PacketHandler::MakeSendBuffer(packet, S_LOGIN); }

};

