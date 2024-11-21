#include "pch.h"
#include "Register.h"

#include <locale>
#include <codecvt>
#include <string>

#include "ServerPacketHandler.h"
#include "GameManager.h"
#include "ServerSession.h"
#include "SceneManager.h"

void Register::Init()
{
	printf("REGISTER\n");
}

void Register::Tick()
{
    Protocol::C_Register sendPacket;

    wcin.imbue(locale("Korean_Korea.949"));
    wcout.imbue(locale("Korean_Korea.949"));

    wcout << L"ID : ";
    wstring id;
    wcin >> id;  // wstring 입력 받기

    wcout << L"PW : ";
    wstring pw;
    wcin >> pw;  // wstring 입력 받기

    wcout << L"NAME : ";
    wstring name;
    wcin >> name;  // wstring 입력 받기

    wstring_convert<codecvt_utf8<wchar_t>> converter;

    string utf8Id = converter.to_bytes(id);
    sendPacket.set_id(utf8Id);

    string utf8Pw = converter.to_bytes(pw);
    sendPacket.set_pw(utf8Pw);

    string utf8Name = converter.to_bytes(name);
    sendPacket.set_name(utf8Name);

    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

    auto serverSession = GameManager::Get().GetSession();
    if (serverSession != nullptr)
    {
        serverSession->Send(sendBuffer);
    }

    SceneManager::Get().LoardScene(SCENE_ID::LOADING);
}
