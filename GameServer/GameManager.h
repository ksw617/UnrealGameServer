#pragma once
#pragma once
#include "Singleton.h"

struct UserInfo
{
	string id;
	string pw;
	string name;

	UserInfo(string _id, string _pw, string _name) : id(_id), pw(_pw), name(_name) {}
};

class Player;
class GameRoom;
class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager() = default;
	~GameManager() = default;
private:
	shared_mutex rwLock;
	map<string, shared_ptr<UserInfo>> users;
	map<int, shared_ptr<Player>> inGameplayers;
	vector<shared_ptr<GameRoom>> gameRooms;
	atomic<int> playerIndex = 0;
public:
	void Init();
	bool CheckUser(string id);
	void AddUser(string id, string pw, string name);
	void RemoveUser(string id);
public:
	shared_ptr<Player> GetPlayer(int id) {
		if (inGameplayers.find(id) != inGameplayers.end())
		{
			return inGameplayers[id];
		} 

		return nullptr;
	}
	void AddPlayer(shared_ptr<Player>& player);
	void EnterGameRoom(int index, shared_ptr<Player>& player);
	shared_ptr<GameRoom> GetGameRoom(int index) { return gameRooms[index]; }
public:
	string GetPW(string id);

};