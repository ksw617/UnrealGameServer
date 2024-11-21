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

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager() = default;
	~GameManager() = default;
private:
	shared_mutex rwLock;
	map<string, UserInfo> users;
public:
	bool CheckUser(string id);
	void AddUser(string id, string pw, string name);
	void RemoveUser(string id);
public:
	string GetPW(string id);

};