#pragma once
#include "Utilities\Utilities.h"
#include <string>

struct GameSystem
{
	static void Draw(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, int sortingOrder);
	static bool IsKeyDown(unsigned int key);
	static bool IsKeyPressed(unsigned int key);
	static void SetViewPosition(const Vec2& position);
	static void SetViewSize(const Vec2& position);
	static double GetGameSystemTime();
	static double GetDeltaTime();
	static bool CreateTexture(const std::string& fileName, const ARGB& colorKey, int textureID);
	static void RemoveTexture(int textureID);
	static void GetImageInfo(const std::string& fileName, int& width, int& height);
};

