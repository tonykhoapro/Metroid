#include "SamusWaveBeam.h"
#include "Enemy.h"
#include "MetroidContent.h"
#include "MetroidCharacter.h"

SamusWaveBeam::SamusWaveBeam(const Vec2& direction, const Vec2& position)
{
	tag = "SamusDamage";
	name = "SamusWaveBeam";
	damage = 12;
	this->isControllable = 1;
	transform.position = position;

	lifeTime = 2.0;
	speedX = 0.4f;
	speedY = 4.0f;

	x = 0;
	y = 0;
	yMax = 82.5;
	A = 30;
	Move = &SamusWaveBeam::MoveUp;
	sprite = AddComponent<SpriteRenderer>();
	sprite->SetDrawOrder(0);
	sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_91"));

	physic = AddComponent<SimulatePhysics>();
	physic->SetBodySize(Vec2(0.3f, 0.3f));
	physic->SetStatic(false);
	physic->DisableCollision(false);
	physic->SetMass(0);

	if (direction.x > 0)
	{
		this->GetTransform().scale = Vec2(1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x += speedX;
		y = A * sin(2 * x);
		physic->SetVelocity(Vec2(x, y));
	}

}


SamusWaveBeam::~SamusWaveBeam()
{
}

void SamusWaveBeam::Update()
{
	GameObject::Update();
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime < 0)
	{
		GetScene()->DestroyGameObject(this);
	}
	(*this.*Move)();
}

void SamusWaveBeam::OnSpawn()
{
	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
	if (Input::IsKeyDown(VK_UP))
	{
		transform.position.y += 1.0f;
		Move = &SamusWaveBeam::MoveUp;
	}
	else if (Samus->GetTransform().scale.x > 0)
	{
		transform.position.x += 0.5f;
		Move = &SamusWaveBeam::MoveRight;
	}
	else
	{
		transform.position.x -= 0.5f;
		transform.position.y -= 1.0f;
		Move = &SamusWaveBeam::MoveLeft;
	}
}

void SamusWaveBeam::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "Enemy")
	{
		Enemy* enemy = static_cast<Enemy*>(other);
		if (enemy->Health > 0)
		{
			enemy->Health -= damage;
		}
	}
	else if (other->GetTag() == "PortalEntrance" || other->GetTag() == "Portal")
	{
		scene->DestroyGameObject(this);
	}	
	else if (other->GetTag() == "EnergyBall")
	{
		scene->DestroyGameObject(other);
	}
}

void SamusWaveBeam::MoveUp()
{
	y += speedX;
	x = A * sin(y + 21);
	physic->SetVelocity(Vec2(x, y));
}

void SamusWaveBeam::MoveRight()
{
	x += speedX;
	y = A * sin(x + 21);
	physic->SetVelocity(Vec2(x, y));
}

void SamusWaveBeam::MoveLeft()
{
	x -= speedX;
	y = A * sin(x - 21);
	physic->SetVelocity(Vec2(x, y));
}
