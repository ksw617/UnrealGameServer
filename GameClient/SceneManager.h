#pragma once
#include "Singleton.h"

//uint8 == unsigned char	//512°³ Å©±â 1byte
enum class SCENE_ID : uint8
{
	LOADING,
	LOGIN,
	REGISTER,
	ENTERGAME,
	SELECTROOM,
};


class SceneManager : public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;
private:
	SceneManager() = default;
	~SceneManager() = default;
private:
	shared_ptr<class Scene> scene = nullptr;
public:
	void LoadScene(SCENE_ID id);
	void Tick();
};

