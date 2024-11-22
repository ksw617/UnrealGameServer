#include "pch.h"
#include "GameManager.h"
#include "Player.h"

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
    cout << "Name : ";
    wcout.imbue(locale("Korean_Korea.949"));
    wcout << player->name << endl;

    switch (player->playerType)     
    {
    case PLAYER_TYPE::ARCHER:
        cout << "ARCHER" << endl;
        break;
    case PLAYER_TYPE::KNIGHT:
        cout << "KNIGHT" << endl;
        break;
    case PLAYER_TYPE::WIZARD:
        cout << "WIZARD" << endl;
        break;
    case PLAYER_TYPE::PRIEST:
        cout << "PRIEST" << endl;
        break;
    default:
        break;
    }


    players.emplace(player);
}

string GameManager::GetPW(string id)
{
    shared_lock<shared_mutex> lock(rwLock);
    return users[id]->pw;
}
