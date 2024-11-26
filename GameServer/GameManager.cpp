#include "pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"
#include "GameRoom.h"

void GameManager::Init()
{

    gameRooms.resize(3);   //[0][1][2]

    for (int i = 0; i < gameRooms.size(); i++)
    {
        gameRooms[i] = make_shared<GameRoom>();
    }
}

bool GameManager::CheckUser(string id)
{
    shared_lock<shared_mutex> lock(rwLock);
    return users.find(id) != users.end();
}

void GameManager::AddUser(string id, string pw, string name)
{
    unique_lock<shared_mutex> lock(rwLock);
    auto userInfo = make_shared<UserInfo>(id, pw, name);
    users.emplace(id, userInfo);
}

void GameManager::RemoveUser(string id)
{
    unique_lock<shared_mutex> lock(rwLock);
    users.erase(id);
}

void GameManager::AddPlayer(shared_ptr<class Player>& player)
{
    unique_lock<shared_mutex> lock(rwLock);
    InGameplayers.emplace(player);
    player->SetPlayerID(++playerIndex);

    printf("Player ID : %d\n", player->GetPlayerID());

    Protocol::S_EnterGame sendPacket;


    sendPacket.set_success(true);
    sendPacket.set_playerindex(player->GetPlayerID());

    for (int i = 0; i < gameRooms.size(); i++)
    {
        sendPacket.add_roomids(i);
    }

    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPacket);
    
    shared_ptr<Session> session = player->session.lock();
    if (session != nullptr)
    {
        session->Send(sendBuffer);
    }


}

void GameManager::EnterGame(int index, shared_ptr<Player>& player)
{
    gameRooms[index]->players.insert(player);
}


string GameManager::GetPW(string id)
{
    shared_lock<shared_mutex> lock(rwLock);
    return users[id]->pw;
}
