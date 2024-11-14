#include "pch.h"
#include "GameManager.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

#include <locale>
#include <codecvt>
#include <string>

bool GameManager::IsConnected = false;

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
        //어떻게 구현할껀지 내일 같이 해봅시다.
        //Send(sendBuffer);
	}
}
