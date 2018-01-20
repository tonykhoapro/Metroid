#pragma once
#include "GameFramework\GameComponent\Component.h"
#include <vector>

class Animation;

class AnimationController final : public Component
{
public:
	AnimationController(std::vector<Animation*> animatedSprites = std::vector<Animation*>(), int sortingOrder = 0, const std::string& name = "None");
	~AnimationController();
public:
	void SetAnimation(const std::string& name);
	void AddAnimation(Animation* animation);
protected:
	std::vector<Animation*> AnimationSet;
	Animation* currentAnimation;
	int sortingOrder;
protected:
	void OnSpawn() override;
	void Update() override;
	void LateUpdate() override;
};

