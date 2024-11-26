#include "pch.h"
#include "Login.h"
#include "Protocol.pb.h"

#include <locale>
#include <codecvt>
#include <string>

#include "ServerPacketHandler.h"
#include "GameManager.h"
#include "ServerSession.h"
#include "SceneManager.h"

void Login::Init()
{
}

void Login::Tick()
{
    Protocol::C_Login sendPacket;

    wcin.imbue(locale("Korean_Korea.949"));
    wcout.imbue(locale("Korean_Korea.949"));

    wcout << L"ID : ";
    wstring id;
    wcin >> id;  // wstring 입력 받기

    wcout << L"PW : ";
    wstring pw;
    wcin >> pw;  // wstring 입력 받기

    wstring_convert<codecvt_utf8<wchar_t>> converter;

    string utf8Id = converter.to_bytes(id);
    sendPacket.set_id(utf8Id);

    string utf8Pw = converter.to_bytes(pw);
    sendPacket.set_pw(utf8Pw);

    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

    auto serverSession = GameManager::Get().GetSession();
    if (serverSession != nullptr)
    {
        serverSession->Send(sendBuffer);
    }

    SceneManager::Get().LoadScene(SCENE_ID::LOADING);
}
