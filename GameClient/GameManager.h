#pragma once
#include "Singleton.h"
class ServerSession;
class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
private:
	GameManager() = default;
	~GameManager() = default;

private:
	atomic<bool> IsConnected = false;
	weak_ptr<ServerSession> session;
private:
	int id = 0;
	vector<int> roomIds;
public:
	int GetID() const { return id; }
	void SetID(int _id) { id = _id; }
	void SetGameRoom(int _id) { roomIds.push_back(_id); }
	int GetRoomSize() { return roomIds.size(); }
	int GetRoomID(int index) { return roomIds[index]; }
public:
	shared_ptr<ServerSession> GetSession() { return session.lock(); }
public:
	void BeginPlay();
	void Tick();
public:
	void IsConnectedServer(shared_ptr<ServerSession> serverSession);
};


