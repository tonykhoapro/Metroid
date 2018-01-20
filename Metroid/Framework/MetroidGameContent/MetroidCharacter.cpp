#include "MetroidCharacter.h"
#include "MetroidContent.h"
#include "Zoomer.h"

MetroidCharacter::MetroidCharacter()
{
	this->name = "Samus";
	this->isControllable = true;

	this->CharacterSprite = AddComponent<SpriteRenderer>();
	CharacterSprite->SetDrawOrder(0);
	CharacterSprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("CharacterSprite"));

	CharacterCamera = AddComponent<CameraComponent>();
	CharacterCamera->SetName("CharacterCamera");

	CharacterPhysics = AddComponent<SimulatePhysics>();
	CharacterPhysics->SetBodySize(Vec2(1.0f, 2.0f));
	CharacterPhysics->SetVelocity(Vec2(0.0f, 0.0f));
	CharacterPhysics->SetMass(2.0f);
	CharacterPhysics->SetStatic(0);
}

MetroidCharacter::~MetroidCharacter()
{
}

void MetroidCharacter::OnSpawn()
{
	GameObject::OnSpawn();
	speed = 8.0f;
}

void MetroidCharacter::Update()
{
	if (Input::IsKeyDown(VK_A))
	{
		CharacterPhysics->SetVelocity(Vec2(-speed, CharacterPhysics->GetVelocity().y));
	}
	else if (Input::IsKeyDown(VK_D))
	{
		CharacterPhysics->SetVelocity(Vec2(speed, CharacterPhysics->GetVelocity().y));
	}
	else if (Input::IsKeyDown(VK_W))
	{
		CharacterPhysics->SetVelocity(Vec2(0, speed));
	}
	else if (Input::IsKeyDown(VK_S))
	{
		CharacterPhysics->SetVelocity(Vec2(0, -speed));
	}
	else CharacterPhysics->SetVelocity(Vec2(0, CharacterPhysics->GetVelocity().y));

	GameObject::Update();
	std::cout << CharacterPhysics->GetVelocity().y << std::endl;

	
}

void MetroidCharacter::OnCollisionEnter(GameObject * other)
{
	if (other->GetName() == "Zoomer")
	{
		//GetScene()->DestroyGameObject(other);
	}
}

//void MetroidCharacter::LateUpdate()
//{
//	
//	GameObject::LateUpdate();
//}
