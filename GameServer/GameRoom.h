#pragma once
class Player;
class GameRoom
{
public:
	int roomID;
public:
	set<shared_ptr<Player>> players;
};

