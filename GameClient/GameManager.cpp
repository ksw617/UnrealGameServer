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

        wcout << L"�̸��� �Է��ϼ���: ";
        wstring text;
        wcin >> text;  // wstring �Է� �ޱ�

        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8Msg = converter.to_bytes(text);

        sendPacket.set_name(utf8Msg);

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
        //��� �����Ҳ��� ���� ���� �غ��ô�.
        //Send(sendBuffer);
	}
}
