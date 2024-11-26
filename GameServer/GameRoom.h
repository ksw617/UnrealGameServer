#pragma once
class Player;
class GameRoom
{
public:
	int roomID;
private:
	shared_mutex rwLock;
	set<shared_ptr<Player>> players;
public:
	void AddPlayer(shared_ptr<Player> player);
	void RemovePlayer(shared_ptr<Player> player);
	void BroadCast(shared_ptr<class SendBuffer> sendBuffer);

};

