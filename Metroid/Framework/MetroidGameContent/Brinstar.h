#pragma once
#include "GameFramework\GameObject\GameObject.h"
class Brinstar :
	public GameObject
{
public:
	Brinstar();
	virtual ~Brinstar();

	SpriteRenderer* BrinstarSprite;
};

