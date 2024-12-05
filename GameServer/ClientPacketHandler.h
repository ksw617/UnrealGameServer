#pragma once
#include <PacketHandler.h>
#include "Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 1000,
	S_LOGIN = 1001,
	C_ENTER_GAME = 1004,
	S_ENTER_GAME = 1005,
	S_SPAWN = 1006,
	S_DESPAWN = 1007,
	C_LOGOUT = 1008,
	C_MOVE = 1009,
	S_MOVE = 1010,
};

//Recv
bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_LOGIN& packet);
bool Handle_C_ENTER_GAME(shared_ptr<PacketSession>& session, Protocol::C_ENTER_GAME& packet);
bool Handle_C_LOGOUT(shared_ptr<PacketSession>& session, Protocol::C_LOGOUT& packet);
bool Handle_C_MOVE(shared_ptr<PacketSession>& session, Protocol::C_MOVE& packet);


class ClientPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//클라이언트에 보낼 패킷
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_LOGIN& packet) { return PacketHandler::MakeSendBuffer(packet, S_LOGIN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_ENTER_GAME& packet) { return PacketHandler::MakeSendBuffer(packet, S_ENTER_GAME); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_SPAWN& packet) { return PacketHandler::MakeSendBuffer(packet, S_SPAWN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_DESPAWN& packet) { return PacketHandler::MakeSendBuffer(packet, S_DESPAWN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_MOVE& packet) { return PacketHandler::MakeSendBuffer(packet, S_MOVE); }

};

