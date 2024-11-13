#include "pch.h"
#include "ClientSession.h"

#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

//Server
void ClientSession::OnConnected()
{
    printf("OnConneted\n");

    //패킷 구조체
    Protocol::S_Login sendPacket;
    //패킷을 보낼수있게 바이트 단위로 변환
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);

    //해당 버퍼 보내기
    Send(sendBuffer);
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