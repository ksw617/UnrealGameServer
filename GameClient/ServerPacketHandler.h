#pragma once
#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 0,
	S_LOGIN = 1,
};

//Recv
//서버에서 S_LOGIN을 보냈을때 여기서 호출되는
bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet);

class ServerPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//클라이언트가 보낼 패킷들 정리
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Login& packet) { return PacketHandler::MakeSendBuffer(packet, C_LOGIN); }

};

