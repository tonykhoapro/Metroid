#define _CRT_SECURE_NO_DEPRECATE
#include "CameraComponent.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameObject\GameObject.h"
#include "ResourcesLoader\Rapidjson\document.h"
#include "ResourcesLoader\Rapidjson\filereadstream.h"
#include "GameFramework\GameContent\GameContent.h"
#include "GameFramework\GameContent\Texture.h"
#include "Main\GameSystem.h"

using namespace rapidjson;

CameraComponent::CameraComponent(float aspectRatio, float size, const std::string& name) :
	Component(name),
	aspectRatio(aspectRatio),
	size(size),
	originalSize(size),
	rows(285),
	columns(480)
{
	FILE* fp = fopen("TiledBackground.json", "rb"); // non-Windows use "r"
	char readBuffer[200000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	const Value& array = d["data"];
	int k = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (k < (int)array.Size()) tiles[rows - 1 - i][j] = array[k].GetInt();
			k++;
		}
	}

}


CameraComponent::~CameraComponent()
{
}

void CameraComponent::Zoom(float scale)
{
	if (scale <= 0.25f) scale = 0.25f;
	size = originalSize * scale;
	GameSystem::SetViewSize(Vec2(aspectRatio * size, size));
}

void CameraComponent::SetSize(float size)
{
	this->originalSize = size;
	this->size = size;
	GameSystem::SetViewSize(Vec2(aspectRatio * size, size));
}

void CameraComponent::LateUpdate()
{
	Vec2 position = this->gameObject->GetTransform().position;
	GameSystem::SetViewPosition(position);
	/*float top = position.y + size / 2.0f;
	float bottom = position.y - size / 2.0f; 
	float left = position.x - size * aspectRatio / 2.0f;
	float right = position.x + size * aspectRatio / 2.0f;

	for (int j = bottom; j <= top; j++)
	{
		for (int i = left; i <= right; i++)
		{
			if(tiles[i][j] == 0) continue;

			GameSystem::Draw();
		}
	}*/

}

void CameraComponent::OnSpawn()
{
	GameSystem::SetViewSize(Vec2(size * aspectRatio, size));
	GameSystem::SetViewPosition(this->gameObject->GetTransform().position);
	//this->tex = GameContent::GetObjectByName<Texture>("TileSetTexture");

}
