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
	S_ENTERROOM = 1007,
};


//Recv
bool Handle_C_LOGIN(shared_ptr<PacketSession>& session, Protocol::C_Login& packet);
bool Handle_C_REGISTER(shared_ptr<PacketSession>& session, Protocol::C_Register& packet);
bool Handle_C_ENTERGAME(shared_ptr<PacketSession>& session, Protocol::C_EnterGame& packet); 
bool Handle_C_ENTERROOM(shared_ptr<PacketSession>& session, Protocol::C_EnterRoom& packet);

class ClientPacketHandler : public PacketHandler
{
public:
	static void Init();
public:
	//Send
	//Ŭ���̾�Ʈ�� ���� ��Ŷ
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_Login& packet) { return PacketHandler::MakeSendBuffer(packet, S_LOGIN); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_Register& packet) { return PacketHandler::MakeSendBuffer(packet, S_REGISTER); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_EnterGame& packet) { return PacketHandler::MakeSendBuffer(packet, S_ENTERGAME); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_EnterRoom& packet) { return PacketHandler::MakeSendBuffer(packet, S_ENTERROOM); }

};

