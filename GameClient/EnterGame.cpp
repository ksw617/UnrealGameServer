#include "pch.h"
#include "EnterGame.h"

#include <locale>
#include <codecvt>
#include <string>

#include "ServerPacketHandler.h"
#include "GameManager.h"
#include "ServerSession.h"
#include "SceneManager.h"

void EnterGame::Init()
{
	printf("EnterGame\n");
}

void EnterGame::Tick()
{
    Protocol::C_EnterGame sendPacket;

    wcin.imbue(locale("Korean_Korea.949"));
    wcout.imbue(locale("Korean_Korea.949"));

    wcout << L"Character Name : ";
    wstring name;
    wcin >> name;  // wstring 입력 받기

    wcout << L"1. 궁수, 2. 검사, 3. 마법사, 4.성직자" << endl;

    int playerType;
    cin >> playerType;

   

    wstring_convert<codecvt_utf8<wchar_t>> converter;

    string utf8Name = converter.to_bytes(name);

    Protocol::Player* player = new Protocol::Player;
    player->set_name(utf8Name);
    player->set_type(playerType);

    sendPacket.set_allocated_player(player);
   
   auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);
   
   auto serverSession = GameManager::Get().GetSession();
   if (serverSession != nullptr)
   {
       serverSession->Send(sendBuffer);
   }
   
   SceneManager::Get().LoadScene(SCENE_ID::LOADING);
}
