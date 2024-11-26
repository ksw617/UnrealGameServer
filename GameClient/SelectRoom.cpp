#include "pch.h"
#include "SelectRoom.h"
#include "GameManager.h"
#include "Protocol.pb.h"
#include "SceneManager.h"
#include "ServerPacketHandler.h"
#include "ServerSession.h"

void SelectRoom::Init()
{
}

void SelectRoom::Tick()
{
	for (int i = 0; i < GameManager::Get().GetRoomSize(); i++)
	{
		cout << "[" << i  << "] Room ID : " << GameManager::Get().GetRoomID(i) << endl;
	}

	cout << "Select Room Index" << endl;

	int index;
	cin >> index;

	if (index < 0 || index >= GameManager::Get().GetRoomSize())
		return;

	Protocol::C_EnterRoom sendPacket;

	sendPacket.set_playerindex(GameManager::Get().GetID());
	sendPacket.set_roomid(GameManager::Get().GetRoomID(index));

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(sendPacket);

	auto serverSession = GameManager::Get().GetSession();
	if (serverSession != nullptr)
	{
		serverSession->Send(sendBuffer);
	}

	SceneManager::Get().LoadScene(SCENE_ID::LOADING);
}
