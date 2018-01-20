#include "GameObject.h"
#include "GameFramework\Scene\Scene.h"

GameObject::GameObject(const Transform& transform, const std::string& tag, const std::string& name) :
	Object(name),
	transform(transform),
	tag(tag),
	scene(nullptr),
	pendingTask(NONE),
	isControllable(false)
{
}

GameObject::~GameObject()
{
	for (Component* component : components)
	{
		if (component)
		{
			delete component;
			component = nullptr;
		}
	}
	components.clear();
}

const Transform& GameObject::GetTransform()
{
	return this->transform;
}

void GameObject::SetTransform(const Transform & transform)
{
	this->transform = transform;
}

void GameObject::Translate(const Vec2 & translation)
{
	this->transform.position.x += translation.x;
	this->transform.position.y += translation.y;
}

Scene * GameObject::GetScene()
{
	return this->scene;
}

void GameObject::OnSpawn()
{
	for (Component* component : components)
	{
		component->OnSpawn();
	}
}

void GameObject::Update()
{
	for (Component* component : components)
	{
		component->Update();
	}
}

void GameObject::LateUpdate()
{
	for (Component* component : components)
	{
		component->LateUpdate();
	}
}

std::list<Component*>& GameObject::GetAllComponents()
{
	return this->components;
}

bool GameObject::IsControllable()
{
	return this->isControllable;
}

const std::string& GameObject::GetTag()
{
	return this->tag;
}

