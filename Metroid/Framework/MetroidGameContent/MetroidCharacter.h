#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter :
	public GameObject
{
public:
	MetroidCharacter();
	virtual ~MetroidCharacter();

	SpriteRenderer* CharacterSprite;
	CameraComponent* CharacterCamera;
	SimulatePhysics* CharacterPhysics;

	float speed;
	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject* other) override;
	//virtual void LateUpdate() override;
};



