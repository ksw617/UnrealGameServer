#pragma once
#include "Singleton.h"
class GameRoomManager : public Singleton<GameRoomManager>
{
	friend class Singleton<GameRoomManager>;
private:
	GameRoomManager() = default;
	~GameRoomManager() = default;
};