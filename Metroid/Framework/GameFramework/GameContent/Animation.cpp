#include "Animation.h"
#include "GameFramework\Time.h"


Animation::Animation()
{
}


Animation::Animation(std::vector<Sprite*> sprites, double timePerFrame, bool looped, const std::string& name):
	Object(name),
	sprites(sprites),
	timePerFrame(timePerFrame),
	looped(looped),
	currentIndex(0),
	currentTotalTime(0),
	totalFrame((int)sprites.size())
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (totalFrame <= 1)
	{
		currentActiveSprite = sprites.at(0);
	}
	else
	{
		if (currentTotalTime >= timePerFrame)
		{
			currentTotalTime = 0;
			currentIndex++;
			if (currentIndex >= totalFrame)
			{
				if (looped)
				{
					currentIndex = 0;
				}
				else currentIndex = totalFrame - 1;
			}
		}
		else
		{
			currentTotalTime += Time::GetDeltaTime();
		}
		currentActiveSprite = sprites.at(currentIndex);
	}
}

void Animation::Reset()
{
	currentIndex = 0;
	currentTotalTime = 0;
}

Sprite * Animation::GetActiveSprite()
{
	return this->currentActiveSprite;
}
