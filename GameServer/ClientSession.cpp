#include "pch.h"
#include "ClientSession.h"

#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

//Server
void ClientSession::OnConnected()
{
    printf("OnConneted\n");

}

int ClientSession::OnRecvPacket(BYTE* buffer, int len)
{
    shared_ptr<PacketSession> session = GetPacketSession();
    ClientPacketHandler::HandlePacket(session, buffer, len);
    
    return len;
}

void ClientSession::OnSend(int len)
{
}

void ClientSession::OnDisconnected()
{
}