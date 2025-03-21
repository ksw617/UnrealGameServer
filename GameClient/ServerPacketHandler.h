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
	C_ENTERROOM = 1006,
	S_ENTERROOM	= 1007,
	S_ENTERNEWBIE = 1010,
	C_CHAT = 2023,
	S_CHAT = 2231,
};

//Recv
bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_Login& packet);
bool Handle_S_REGISTER(shared_ptr<PacketSession>& session, Protocol::S_Register& packet);
bool Handle_S_ENTERGAME(shared_ptr<PacketSession>& session, Protocol::S_EnterGame& packet);
bool Handle_S_ENTERROOM(shared_ptr<PacketSession>& session, Protocol::S_EnterRoom& packet);
bool Handle_S_ENTERNEWBIE(shared_ptr<PacketSession>& session, Protocol::S_EnterNewbie& packet);
bool Handle_S_CHAT(shared_ptr<PacketSession>& session, Protocol::S_Chat& packet);


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
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_EnterRoom& packet) { return PacketHandler::MakeSendBuffer(packet, C_ENTERROOM); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_Chat& packet) { return PacketHandler::MakeSendBuffer(packet, C_CHAT); }


};

