#pragma once
#include "Scene.h"
class Register : public Scene
{
public:
	virtual void Init() override;
	virtual void Tick() override;
};
