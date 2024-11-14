#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>

//Client
void ServerSession::OnConnected()
{
   
    printf("OnConneted\n");

    Protocol::C_Login sendPacket;

    wstring text = L"한글";
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string utf8Msg = converter.to_bytes(text);

    sendPacket.set_name(utf8Msg);  // UTF-8로 설정

    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
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
