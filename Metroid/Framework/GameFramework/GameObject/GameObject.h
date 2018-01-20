#pragma once
#include "GameFramework\Object.h"
#include <string>
#include <list>
#include "GameFramework\GameComponent\AnimationController.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "GameFramework\GameComponent\SpriteRenderer.h"
#include "GameFramework\GameComponent\SimulatePhysics.h"
#include "GameFramework\Input.h"
#include "GameFramework\Time.h"
#include "GameFramework\Scene\Scene.h"

class Scene;
class Component;

enum PENDING_TASK
{
	NONE, DESTROY
};

class GameObject : public Object
{
public:
	GameObject(const Transform& transform = Transform(Vec2(0, 0), 0, Vec2(1.0f, 1.0f)), const std::string& tag = "None", const std::string& name = "None");
	virtual ~GameObject();
public:
	template <class Type> Type* AddComponent();
	template <class Type> Type* GetComponent();
	std::list<Component*>& GetAllComponents();
public:
	bool IsControllable();
	const std::string& GetTag();
	const Transform& GetTransform();
	void SetTransform(const Transform& transform);
	void Translate(const Vec2& translation);
	Scene* GetScene();
protected:
	bool isControllable;
private:
	Transform transform;
	Scene* scene;
	std::string tag;
	PENDING_TASK pendingTask;
	std::list<Component*> components;
protected:
	virtual void OnSpawn(); // Khi game object vua duoc scene tao ra
	virtual void Update(); // Update game logic
	virtual void OnCollisionEnter(GameObject* other) {};// tu kich hoat khi va cham voi game object khac
	virtual void LateUpdate(); // Chu yeu dung de render
	friend class Scene;
	friend class SimulatePhysics;
};


template<class Type>
inline Type * GameObject::AddComponent()
{
	Type* newComponent = new Type();
	this->components.push_back(newComponent);
	newComponent->gameObject = this;
	return newComponent;
}

// Tra ve component thuoc class Type duoc tim thay dau tien, nullptr neu khong co component phu hop.
template<class Type>
inline Type * GameObject::GetComponent()
{
	for (Component* component : components)
	{
		Type * com = dynamic_cast<Type*>(component);
		if (com)
		{
			return com;
		}
	}
	return nullptr;
}


