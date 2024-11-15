#pragma once
class ServerSession;
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
	GameManager& operator= (const GameManager&) = delete;

private:
	bool IsConnected = false;
	weak_ptr<ServerSession> session;
public:
	shared_ptr<ServerSession> GetSession() { return session.lock(); }
public:
	void BeginPlay();
	void Tick();
public:
	void IsConnectedServer(shared_ptr<ServerSession> serverSession);
};


