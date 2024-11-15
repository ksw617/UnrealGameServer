#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

#include "GameManager.h"
//Client
void ServerSession::OnConnected()
{
    printf("OnConneted\n");
    GameManager::Get().IsConnectedServer(reinterpret_pointer_cast<ServerSession>(shared_from_this()));

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
