#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

//Client
void ServerSession::OnConnected()
{
    printf("OnConneted\n");

    Protocol::C_Login sendPack;
    sendPack.set_name("Kwak");
    sendPack.set_id("QWER");
    sendPack.set_pw("qwer123");

    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPack);
    Send(sendBuffer);

}

int ServerSession::OnRecvPacket(BYTE* buffer, int len)
{
    shared_ptr<PacketSession> session = GetPacketSession();
    ServerPacketHandler::HandlePacket(session, buffer, len);
    return len;
}

void ServerSession::OnSend(int len)
{
}

void ServerSession::OnDisconnected()
{
}
