#pragma once
class GameManager
{
private:
	GameManager() = default;
	~GameManager() = default;
public:
	static GameManager& Get()
	{
		static GameManager instance;
		return instance;
	}
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
public:
	set<string> playerName;
};
