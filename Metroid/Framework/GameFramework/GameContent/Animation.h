#pragma once
#include "GameFramework\Object.h"
#include <vector>

class Sprite;

class Animation final : public Object
{
public:
	Animation();
	Animation(std::vector<Sprite*> sprites, double timePerFrame, bool looped, const std::string& name);
	~Animation();
public:
	void Update();
	void Reset();
	Sprite* GetActiveSprite();
private:
	std::vector<Sprite*> sprites;

	Sprite* currentActiveSprite;
	double timePerFrame;
	double currentTotalTime;
	int currentIndex;
	int totalFrame;
	bool looped;
};

