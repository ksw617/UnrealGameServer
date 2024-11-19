#include "pch.h"
#include "GameManager.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

#include "ServerSession.h"

#include <locale>
#include <codecvt>
#include <string>
#include "SceneManager.h"


void GameManager::BeginPlay()
{
    SceneManager& sceneManager = SceneManager::Get();
	SceneManager::Get().LoardScene(SCENE_ID::LOGIN);
}

void GameManager::Tick()
{
	if (IsConnected.load())
	{
		SceneManager::Get().Tick();
	}
}

void GameManager::IsConnectedServer(shared_ptr<ServerSession> serverSession)
{
    IsConnected.store(true);
    session = serverSession;
}
