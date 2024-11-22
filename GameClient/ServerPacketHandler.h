#pragma once
#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 1000,
	S_LOGIN = 1001,
	C_REGISTER = 1002,
	S_REGISTER = 1003,
	C_ENTERGAME = 1004,
	S_ENTERGAME = 1005,

};

//Recv
bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet);
bool Handle_S_REGISTER(shared_ptr<PacketSession>& session, Protocol::S_Register& packet);
bool Handle_S_ENTERGAME(shared_ptr<PacketSession>& session, Protocol::S_EnterGame& packet);

class ServerPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//클라이언트가 보낼 패킷들 정리
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Login& packet) { return PacketHandler::MakeSendBuffer(packet, C_LOGIN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Register& packet) { return PacketHandler::MakeSendBuffer(packet, C_REGISTER); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_EnterGame& packet) { return PacketHandler::MakeSendBuffer(packet, C_ENTERGAME); }

};

