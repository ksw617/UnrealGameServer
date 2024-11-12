#include "pch.h"
#include "ClientSession.h"

void ClientSession::OnConnected()
{

    printf("OnConneted\n");
}

int ClientSession::OnRecvPacket(BYTE* buffer, int len)
{

    return len;
}

void ClientSession::OnSend(int len)
{
}

void ClientSession::OnDisconnected()
{
}