#pragma once

#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 0,
	S_LOGIN = 1,

};

//Recv
//클라에서 C_LOGIN을 보냈을때 여기서 호출되는
bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet);

class ClientPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//클라이언트가 보낼 패킷들 정리
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_Login& packet) { return PacketHandler::MakeSendBuffer(packet, S_LOGIN); }

};

