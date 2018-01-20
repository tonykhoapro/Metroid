#pragma once
#include "GameFramework\Object.h"
#include <list>
#include <vector>

class Game;
class SimulatePhysics;
class GameObject;

class Scene : public Object
{
public:
	Scene(const std::string& name = "None");
	virtual ~Scene();
public:
	inline void LoadCollisionBoxes();
	std::vector<SimulatePhysics*>& GetCollisionBoxes();
protected:
	void BeginScene();
	void Update();
	void ExitScene();
	
	inline void HandlePendingGameObjects();
	template <class Type> Type* AddNewGameObject(const Transform& transform = Transform(Vec2(0, 0), 0, Vec2(1.0f, 1.0f)));// chi dung trong scene constructor
public:
	template <class Type> Type* SpawnNewGameObject(const Transform& transform);
	void DestroyGameObject(GameObject*& gameObject);
	GameObject* FindGameObjectByName(const std::string& name);
public:
	float SweptAABB(SimulatePhysics* movingGameObject, SimulatePhysics* other, Vec2 & normal);
	void CollisionReponses(SimulatePhysics* movingGameObject, SimulatePhysics* other, const Vec2 & normal, float collisionTime);
private:
	inline RectF GetSweptBroadphaseBox(SimulatePhysics* movingGameObject);
	inline bool IsColliding(const RectF& bodyRect, const RectF& otherRect);
protected:
	std::list<GameObject*> GameObjectsList;// tat ca game object ton tai trong scene
	std::list<GameObject*> PendingGameObjects;// nhung game object can destroy khi ket thuc framne hien tai
	std::list<GameObject*> ActiveGameObjects;// nhung game object se duoc update, clear moi frame
	std::vector<GameObject*> ControllableGameObjects;// main character va nhung thu thuoc ve character

	std::vector<SimulatePhysics*> boxes;
	friend class Game;
};

template<class Type>
inline Type * Scene::AddNewGameObject(const Transform & transform)
{
	Type* newGameObject = new Type();
	GameObjectsList.push_back(newGameObject);
	if(newGameObject->isControllable == true) ControllableGameObjects.push_back(newGameObject);
	newGameObject->scene = this;
	newGameObject->transform = transform;
	return newGameObject;
}

template<class Type>
inline Type* Scene::SpawnNewGameObject(const Transform & transform)
{
	Type* newGameObject = new Type();
	GameObjectsList.push_back(newGameObject);
	if(newGameObject->isControllable == true) ControllableGameObjects.push_back(newGameObject);
	newGameObject->scene = this;
	newGameObject->transform = transform;
	newGameObject->OnSpawn();
	return newGameObject;
}