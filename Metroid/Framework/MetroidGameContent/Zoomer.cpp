#include "Zoomer.h"
#include "MetroidContent.h"


Zoomer::Zoomer()
{
	this->name = "Zoomer";
	
	sprite = AddComponent<SpriteRenderer>();
	sprite->SetDrawOrder(0);
	sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("CharacterSprite"));

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 2.0f));
	physics->SetVelocity(Vec2(1.0f, 0));
	physics->SetStatic(false);
	physics->DisableCollision(false);
	physics->SetMass(0);
}


Zoomer::~Zoomer()
{
}

void Zoomer::Update()
{
	GameObject::Update();
	Translate(physics->GetVelocity() * (float)Time::GetDeltaTime());
}

void Zoomer::OnCollisionEnter(GameObject * other)
{
	if (other->GetName() == "Samus") std::cout << "aaaaaaaaaaaaaaa";
}
