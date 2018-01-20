#include "StaticBox.h"



StaticBox::StaticBox()
{
	this->physic = AddComponent<SimulatePhysics>();
	this->physic->SetVelocity(Vec2(0, 0));
}


StaticBox::~StaticBox()
{
}

void StaticBox::SetBodySize(const Vec2 & bodySize)
{
	physic->SetBodySize(bodySize);
}
