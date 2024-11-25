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
	set<shared_ptr<Player>> InGameplayers;
	vector<shared_ptr<GameRoom>> gameRooms;
	atomic<int> playerIndex = 0;
public:
	void Init();
	bool CheckUser(string id);
	void AddUser(string id, string pw, string name);
	void RemoveUser(string id);
public:
	void AddPlayer(shared_ptr<Player>& player);
	void EnterGame(int index, shared_ptr<Player>& player);
public:
	string GetPW(string id);

};