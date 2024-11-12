#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"


void ServerSession::OnConnected()
{
    printf("OnConneted\n");

}

int ServerSession::OnRecvPacket(BYTE* buffer, int len)
{
    return len;
}

void ServerSession::OnSend(int len)
{
}

void ServerSession::OnDisconnected()
{
}
