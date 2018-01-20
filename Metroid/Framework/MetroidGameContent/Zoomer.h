#pragma once
#include "GameFramework\GameObject\GameObject.h"
class Zoomer :
	public GameObject
{
public:
	Zoomer();
	virtual ~Zoomer();
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other) override;
	SpriteRenderer* sprite;
	SimulatePhysics* physics;
};

