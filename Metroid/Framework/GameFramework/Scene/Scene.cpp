#include "Scene.h"
#include <algorithm>
#include "GameFramework\GameObject\GameObject.h"
#include "GameFramework\GameComponent\SimulatePhysics.h"
#include "GameFramework\GameContent\GameContent.h"
#include "GameFramework\GameObject\StaticBox.h"

Scene::Scene(const std::string& name) :
	Object(name)
{
	LoadCollisionBoxes();
}

Scene::~Scene()
{
	for (GameObject* gameObject : GameObjectsList)
	{
		if (gameObject)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}
	GameObjectsList.clear();
}

void Scene::LoadCollisionBoxes()
{
	for (CollisionBox collisionBox : GameContent::CollisionBoxes)
	{
		StaticBox* box = AddNewGameObject<StaticBox>(Transform(Vec2(collisionBox.x, collisionBox.y)));
		ActiveGameObjects.push_back(box);
		box->GetComponent<SimulatePhysics>()->SetBodySize(Vec2((float)collisionBox.width, (float)collisionBox.height));
	}
}

void Scene::Update()
{
	for (GameObject* box : ActiveGameObjects)
	{
		SimulatePhysics* staticBox = box->GetComponent<SimulatePhysics>();
		if (!staticBox) continue;
		boxes.push_back(staticBox);
	}
	/*for (GameObject* movingGameObject : ControllableGameObjects)
	{
		SimulatePhysics* movingBox = movingGameObject->GetComponent<SimulatePhysics>();
		if (!movingBox) continue;
		movingBox->HandleCollision(boxes);
	}*/
	
	//-----------------------------------------------------------------
	for (GameObject* gameObject : ActiveGameObjects)
	{
		gameObject->Update();
	}
	for (GameObject* gameObject : ControllableGameObjects)
	{
		gameObject->Update();
	}
	// Check collision
	//-------------------------------------------------------------------------------------------------//
	
	//---------------------------------------------------------------------------------------------------//
	// Invoke all OnCollisionEnter2D method in GameLogic 


	// Reponse collision


	// Update all game components using LateUpdate method
	for (GameObject* gameObject : ControllableGameObjects)
	{
		gameObject->LateUpdate();
	}
	for (GameObject* gameObject : ActiveGameObjects)
	{
		gameObject->LateUpdate();
	}
	boxes.clear();
	//ActiveGameObjects.clear();
	HandlePendingGameObjects();
}

void Scene::HandlePendingGameObjects()
{
	for (std::list<GameObject*>::iterator it = PendingGameObjects.begin(); it != PendingGameObjects.end(); it++)
	{
		if ((*it)->pendingTask == DESTROY)
		{
			GameObjectsList.remove((*it));
			ActiveGameObjects.remove((*it));
			if ((*it))
			{
				delete (*it);
				(*it) = nullptr;
			}
			continue;
		}
	}
	PendingGameObjects.clear();
}

void Scene::BeginScene()
{
	for (GameObject* gameObject : GameObjectsList)
	{
		gameObject->OnSpawn();
	}
}

void Scene::ExitScene()
{
}

std::vector<SimulatePhysics*>& Scene::GetCollisionBoxes()
{
	return this->boxes;
}

void Scene::DestroyGameObject(GameObject * & gameObject)
{
	if (!gameObject || gameObject->scene != this) return;
	gameObject->pendingTask = DESTROY;
	PendingGameObjects.push_back(gameObject);
	gameObject = nullptr;
}

GameObject * Scene::FindGameObjectByName(const std::string & name)
{
	for (GameObject* gameObject : GameObjectsList)
	{
		if (gameObject->GetName() == name) return gameObject;
	}
	return nullptr;
}

float Scene::SweptAABB(SimulatePhysics * movingGameObject, SimulatePhysics * other, Vec2 & normal)
{
	//https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	float xEntry, yEntry;
	float xExit, yExit;

	RectF broadphaseRect = GetSweptBroadphaseBox(movingGameObject);
	if (!IsColliding(broadphaseRect, other->GetBodyRect()))
	{
		normal = Vec2(0, 0);
		return 1.0f;
	}

	Vec2 velocity(movingGameObject->GetVelocity());
	float vx = velocity.x * (float)Time::GetDeltaTime();
	float vy = velocity.y * (float)Time::GetDeltaTime();
	RectF movingGameObjectBody = movingGameObject->GetBodyRect();
	RectF otherBody = other->GetBodyRect();

	if (vx > 0.0f)
	{
		xInvEntry = otherBody.left - movingGameObjectBody.right;
		xInvExit = otherBody.right - movingGameObjectBody.left;
	}
	else
	{
		xInvEntry = otherBody.right - movingGameObjectBody.left;
		xInvExit = otherBody.left - movingGameObjectBody.right;
	}

	if (vy > 0.0f)
	{
		yInvEntry = otherBody.bottom - movingGameObjectBody.top;
		yInvExit = otherBody.top - movingGameObjectBody.bottom;
	}
	else
	{
		yInvEntry = otherBody.top - movingGameObjectBody.bottom;
		yInvExit = otherBody.bottom - movingGameObjectBody.top;
	}

	if (vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / vx;
		xExit = xInvExit / vx;
	}

	if (vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / vy;
		yExit = yInvExit / vy;
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		normal = Vec2(0, 0);
		return 1.0f;
	}

	if (xEntry > yEntry)
	{
		if (xInvExit < 0.0f)
		{
			normal = Vec2(-1.0f, 0);
		}
		else
		{
			normal = Vec2(1.0f, 0);
		}
	}
	else
	{
		if (yInvExit < 0.0f)
		{
			normal = Vec2(0, -1.0f);
		}
		else
		{
			normal = Vec2(0, 1.0f);
		}
	}
	std::cout << "x: " << normal.x << ", y = " << normal.y << std::endl;
	return entryTime;
}

void Scene::CollisionReponses(SimulatePhysics * movingGameObject, SimulatePhysics * other, const Vec2 & normal, float collisionTime)
{
	if (collisionTime < 1.0f && collisionTime == 0 && normal == Vec2(0, -1.0f))
	{
		movingGameObject->GetOwner()->Translate(movingGameObject->GetVelocity() * collisionTime * (float)Time::GetDeltaTime());
		if (movingGameObject->GetVelocity().x != 0)
		{
			movingGameObject->GetOwner()->Translate(Vec2(movingGameObject->GetVelocity().x * (float)Time::GetDeltaTime(), 0));
		}
		movingGameObject->SetVelocity(Vec2(movingGameObject->GetVelocity().x, 0));
	}
	else if (collisionTime < 1.0f && collisionTime == 0 && normal == Vec2(0, 1.0f))
	{
		movingGameObject->GetOwner()->Translate(movingGameObject->GetVelocity() * collisionTime * (float)Time::GetDeltaTime());
		movingGameObject->SetVelocity(Vec2(movingGameObject->GetVelocity().x, 0));
	}
	else
	{
		movingGameObject->GetOwner()->Translate(movingGameObject->GetVelocity() * collisionTime * (float)Time::GetDeltaTime());
	}
}

RectF Scene::GetSweptBroadphaseBox(SimulatePhysics * movingGameObject)
{
	RectF rect;
	Vec2 velocity = movingGameObject->GetVelocity();
	RectF movingGameObjectBody = movingGameObject->GetBodyRect();
	float vx = velocity.x * (float)Time::GetDeltaTime();
	float vy = velocity.y * (float)Time::GetDeltaTime();

	rect.top = vy > 0 ? movingGameObjectBody.top + vy : movingGameObjectBody.top;
	rect.bottom = vy > 0 ? movingGameObjectBody.bottom : movingGameObjectBody.bottom + vy;
	rect.left = vx > 0 ? movingGameObjectBody.left : movingGameObjectBody.left + vx;
	rect.right = vx > 0 ? movingGameObjectBody.right + vx : movingGameObjectBody.right;
	return rect;
}

bool Scene::IsColliding(const RectF & bodyRect, const RectF & otherRect)
{
	float left = otherRect.left - bodyRect.right;
	float top = otherRect.top - bodyRect.bottom;
	float right = otherRect.right - bodyRect.left;
	float bottom = otherRect.bottom - bodyRect.top;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}


