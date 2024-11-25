#pragma once

//uint8 == unsigned char	//512°³ Å©±â 1byte
enum class PLAYER_TYPE : uint8
{
	NONE,
	ARCHER,
	KNIGHT,
	WIZARD,
	PRIEST,
};


class Session;
class Player
{
private:
	int playerID = 0;
public:
	int GetPlayerID() const { return playerID; }
	void SetPlayerID(int id) { playerID = id; }
public:
	weak_ptr<Session> session;
public:
	wstring name;
	PLAYER_TYPE playerType;
public:
	Player(shared_ptr<Session> _session, wstring _name, PLAYER_TYPE type) : session(_session), name(_name), playerType(type) {}
};

