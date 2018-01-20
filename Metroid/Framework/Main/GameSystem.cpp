#include "GameSystem.h"
#include "Core\SystemManager\SystemManager.h"
#include "Main\Game.h"


void GameSystem::Draw(const Transform & transform, int textureID, const Rect & rect, float pixelsPerUnit, int sortingOrder)
{
	DRAW(transform, textureID, rect, pixelsPerUnit, sortingOrder);
}

bool GameSystem::IsKeyDown(unsigned int key)
{
	return SYSTEM_KEY_DOWN(key);
}

bool GameSystem::IsKeyPressed(unsigned int key)
{
	return SYSTEM_KEY_PRESSED(key);
}

void GameSystem::SetViewPosition(const Vec2 & position)
{
	VIEW_POSITION(position);
}

void GameSystem::SetViewSize(const Vec2 & position)
{
	SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->SetViewSize(position);
}

double GameSystem::GetGameSystemTime()
{
	return SystemManager::GetInstance()->GetSystem<WindowsTime>()->GetLifeTime();
}

double GameSystem::GetDeltaTime()
{
	return Game::deltaTime;
}

bool GameSystem::CreateTexture(const std::string & fileName, const ARGB & colorKey, int textureID)
{
	return SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->CreateTextureFromFile(fileName, colorKey, textureID);
}

void GameSystem::RemoveTexture(int textureID)
{
	SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->RemoveTexture(textureID);
}

void GameSystem::GetImageInfo(const std::string & fileName, int & width, int & height)
{
	SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->GetImageInfoFromFile(fileName, width, height);
}

