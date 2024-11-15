#include "pch.h"
#include "GameManager.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

#include "ServerSession.h"

#include <locale>
#include <codecvt>
#include <string>


void GameManager::BeginPlay()
{
}

void GameManager::Tick()
{
	if (IsConnected)
	{

        Protocol::C_Login sendPacket;

        wcin.imbue(locale("Korean_Korea.949"));
        wcout.imbue(locale("Korean_Korea.949"));

        wcout << L"이름을 입력하세요: ";
        wstring text;
        wcin >> text;  // wstring 입력 받기

        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8Msg = converter.to_bytes(text);

        sendPacket.set_name(utf8Msg);

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
 
        auto serverSession = GetSession();
        if (serverSession != nullptr)
        {
            GetSession()->Send(sendBuffer);
        }

	}
}

void GameManager::IsConnectedServer(shared_ptr<ServerSession> serverSession)
{
    IsConnected = true;
    session = serverSession;
}
