#pragma once
#pragma once
#include "Singleton.h"
class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager() = default;
	~GameManager() = default;
};