#pragma once
#include "Scene.h"
class EnterGame : public Scene
{
public:
	virtual void Init() override;
	virtual void Tick() override;
};
