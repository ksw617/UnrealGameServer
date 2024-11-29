#pragma once
#include "Scene.h"
class EnterRoom : public Scene
{
public:
	virtual void Init() override;
	virtual void Tick() override;
};
