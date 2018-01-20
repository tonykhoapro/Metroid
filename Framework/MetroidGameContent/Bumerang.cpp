#include "Bumerang.h"
#include "MetroidContent.h"
#include "BumerangAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "MetroidCharacter.h"
#include "SamusAnimation.h"

Bumerang::Bumerang() :
	lifeTime(4.0),
	speedX(1.45f), speedY(8.0f)
{
	this->name = "RidleyBullet";
	//this->isControllable = 1;

	/*sprite = AddComponent<SpriteRenderer>();
	sprite->SetDrawOrder(0);
	sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("tilekraid_8"));*/

	physics = AddComponent<SimulatePhysics>();

	physics->SetBodySize(Vec2(0.3f, 0.3f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<BumerangAnimation>(); //*
	Health = 30;
	x = 0;
	y = 0;
	A = 30;
	shoot = 0;
	shootingTimer = 0;
	timeout = 0.0f;
}


Bumerang::~Bumerang()
{
}

void Bumerang::Fire(const Vec2 & firePosition, int direction)
{
	this->SetTransform(firePosition);
	this->firePosition = firePosition;
	this->direction = direction;

	//Nap bumerang
	//this->SetTransform(Transform(Vec2(kraidPos.x, kraidPos.y), 0, Vec2(direction, 1.0f)));
	//this->SetTransform(Transform(Vec2(kraidPos.x, kraidPos.y)));
	if (direction == 1)
	{
		this->GetTransform().scale = Vec2(1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x += speedX;
		y = A * sin(2 * x);
		physics->SetVelocity(Vec2(x + 3.0f, y));
	}
	else
	{
		this->GetTransform().scale = Vec2(1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x -= speedX;
		y = -A * sin(2 * x);
		physics->SetVelocity(Vec2(x - 3.f, y));
	}

}

void Bumerang::OnSpawn() //*
{
	Enemy::OnSpawn();

	kraid = GetScene()->FindGameObjectByName("Kraid");
	kraidPos = kraid->GetTransform().position;
	yMax = kraidPos.y + 3.5f;
}

void Bumerang::Update()
{
	Enemy::Update();
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime < 0)
	{
		scene->DestroyGameObject(this);
	}
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	if (this->GetTransform().position.y > yMax && direction == 1) {
		x = 0;
		x += speedX;
		y = -A * sin(2 * x);
		this->physics->SetVelocity(Vec2(x + 3.5f, y));//x+3.5f, y
	}

	if (this->GetTransform().position.y > yMax && direction == -1)//(&&)
	{
		x = 0;
		x -= speedX;
		y = A * sin(2 * x);
		this->physics->SetVelocity(Vec2(x - 3.5f, y));//x+3.5f, y
	}

	//if (direction == 1)
	//{
	xpos = this->GetTransform().position.x + physics->GetVelocity().x * Time::GetDeltaTime();
	ypos = this->GetTransform().position.y + physics->GetVelocity().y * Time::GetDeltaTime();
	//SetTransform(Transform(Vec2(firePosition.x + std::abs(xpos - firePosition.x), ypos)));
	SetTransform(Transform(Vec2(xpos, ypos)));
	/*}
	else
	{
	xpos = this->GetTransform().position.x + box->GetVelocity().x * Time::GetDeltaTime();
	ypos = this->GetTransform().position.y + box->GetVelocity().y * Time::GetDeltaTime();
	SetTransform(Transform(Vec2(xpos, ypos)));
	}*/

	if (CameraComponent::tiles[(int)(this->GetTransform().position.y)][(int)this->GetTransform().position.x] != -1)
	{
		GetScene()->DestroyGameObject(this);
	}

	//SetTransform(Transform(Vec2(this->GetTransform().position.x, this->GetTransform().position.y), 0)); //*

}

void Bumerang::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	if (other->GetName() != "Bomb")
	{
		animation->Pause(1);
		OnGetDamageDelayTime = 0.5;
	}

	if (other->GetTag() == "Player" && isFrozen == 0)
	{
		if (Samus->OnDamageTime <= 0)
		{
			Samus->energy -= this->Damage;
			Samus->OnDamage = 1;
			Samus->jumpTime = 0;
			Samus->OnDamageTime = 0.2;
			Samus->animation->color = ARGB(100, 255, 255, 255);

			if (normal.x == 1.0f)
			{
				Samus->CharacterPhysics->SetVelocityX(3.0f);
			}
			else
			{
				Samus->CharacterPhysics->SetVelocityX(-3.0f);
			}
		}
	}
}