#pragma once
#include "GameFramework\GameObject\GameObject.h"
#include "MetroidCharacter.h"

class Kraid : public GameObject
{
public:
	Kraid();
	virtual ~Kraid();
	virtual void OnSpawn() override;
	virtual void Update() override;
	/*virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;*/
	SpriteRenderer* sprite;
	SimulatePhysics* physics;

	AnimationController* animation;
	MetroidCharacter* Samus;
	double OnGetDamageDelayTime;
	Vec2 kraid;
	int flag;
	double countTime, damagedTimer;
	float vx, vy;
	int rotate;
	float direction;
	int waiting;

	double hp;
	int damaged;
	int Damage;

	void(*KraidUpdate)(Kraid* gameObject);
	void moveState();
	int checkDamaged(int isDamaged);
	void resetNoDamage();
	int checkSamusGun(int samusGun);
	void setDirection(Vec2 samusPosition);

	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;

	double fireTimer;
};