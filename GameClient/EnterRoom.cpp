#include "pch.h"
#include "EnterRoom.h"
#include "Protocol.pb.h"

#include <locale>
#include <codecvt>
#include <string>

#include "ServerPacketHandler.h"
#include "GameManager.h"
#include "ServerSession.h"
#include "SceneManager.h"


void EnterRoom::Init()
{
}

void EnterRoom::Tick()
{
    Protocol::C_Chat sendPacket;

    wcin.imbue(locale("Korean_Korea.949"));
    wcout.imbue(locale("Korean_Korea.949"));

    wcout << L"Send : ";
    wstring msg;
    wcin >> msg;  
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    string utf8Id = converter.to_bytes(msg);
    sendPacket.set_msg(utf8Id);

    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

    auto serverSession = GameManager::Get().GetSession();
    if (serverSession != nullptr)
    {
        serverSession->Send(sendBuffer);
    }

}
