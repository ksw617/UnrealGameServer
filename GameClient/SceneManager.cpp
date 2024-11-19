#include "pch.h"
#include "SceneManager.h"
#include "Login.h"

void SceneManager::LoardScene(SCENE_ID id)
{

	switch (id)
	{
	case SCENE_ID::LOGIN:
		scene = make_shared<Login>();
		break;
	default:
		break;
	}

	scene->Init();

}

void SceneManager::Tick()
{
	scene->Tick();
}
