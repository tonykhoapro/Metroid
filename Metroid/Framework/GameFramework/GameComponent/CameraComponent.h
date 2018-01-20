#pragma once
#include "GameFramework\GameComponent\Component.h"

class Texture;

class CameraComponent final : public Component
{
public:
	CameraComponent(float aspectRatio = 1.333f, float size = 14.0f, const std::string& name = "None");
	~CameraComponent();
	void Zoom(float scale);
	void SetSize(float size);
protected:
	void LateUpdate() override;
	void OnSpawn() override;
	float aspectRatio;
	float size;
	float originalSize;
	int rows;
	int columns;
	int tiles[285][480];
	Texture* tex;
};

