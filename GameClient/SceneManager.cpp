#include "pch.h"
#include "SceneManager.h"
#include "Loading.h"
#include "Login.h"
#include "Register.h"
#include "EnterGame.h"
#include "SelectRoom.h"
#include "EnterRoom.h"

void SceneManager::LoadScene(SCENE_ID id)
{

	switch (id)
	{
	case SCENE_ID::LOADING:
		scene = make_shared<Loading>();
		break;
	case SCENE_ID::LOGIN:
		scene = make_shared<Login>();
		break;
	case SCENE_ID::REGISTER:
		scene = make_shared<Register>();
		break;
	case SCENE_ID::ENTERGAME:
		scene = make_shared<EnterGame>();
		break;
	case SCENE_ID::SELECTROOM:
		scene = make_shared<SelectRoom>();
		break;
	case SCENE_ID::ENTERROOM:
		scene = make_shared<EnterRoom>();
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
