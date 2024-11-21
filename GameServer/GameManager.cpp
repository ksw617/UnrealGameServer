#include "pch.h"
#include "GameManager.h"

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

string GameManager::GetPW(string id)
{
    shared_lock<shared_mutex> lock(rwLock);
    return users[id].pw;
}
