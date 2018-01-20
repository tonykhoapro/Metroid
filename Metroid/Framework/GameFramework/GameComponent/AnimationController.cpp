#include "AnimationController.h"
#include "GameFramework\GameContent\Animation.h"
#include "GameFramework\GameObject\GameObject.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"

AnimationController::AnimationController(std::vector<Animation*> animatedSprites, int sortingOrder, const std::string& name) :
	Component(name),
	AnimationSet(animatedSprites),
	sortingOrder(sortingOrder),
	currentAnimation(nullptr)
{
}


AnimationController::~AnimationController()
{
}

void AnimationController::SetAnimation(const std::string & name)
{
	this->currentAnimation->Reset();
	for (Animation * animation : AnimationSet)
	{
		if (animation->GetName() == name)
		this->currentAnimation = animation;
	}
}

void AnimationController::AddAnimation(Animation* animation)
{
	this->AnimationSet.push_back(animation);
}

void AnimationController::OnSpawn()
{
	if ((int)AnimationSet.size() > 0) currentAnimation = AnimationSet.at(0);
}

void AnimationController::Update()
{
	currentAnimation->Update();
}

void AnimationController::LateUpdate()
{
	GameSystem::Draw(
		gameObject->GetTransform(),
		currentAnimation->GetActiveSprite()->GetTexture()->GetObjectID(),
		currentAnimation->GetActiveSprite()->GetRect(),
		currentAnimation->GetActiveSprite()->GetPixelsPerUnit(),
		this->sortingOrder);
}



