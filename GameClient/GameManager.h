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
public:
	int GetID() const { return id; }
	void SetID(int _id) { id = _id; }
public:
	shared_ptr<ServerSession> GetSession() { return session.lock(); }
public:
	void BeginPlay();
	void Tick();
public:
	void IsConnectedServer(shared_ptr<ServerSession> serverSession);
};


