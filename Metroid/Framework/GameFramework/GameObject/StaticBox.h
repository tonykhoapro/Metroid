#pragma once
#include "GameFramework\GameObject\GameObject.h"

class StaticBox : public GameObject
{
public:
	StaticBox();
	virtual ~StaticBox();
public:
	void SetBodySize(const Vec2& bodySize);
private:
	SimulatePhysics* physic;
};

