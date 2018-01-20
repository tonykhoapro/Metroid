#include "SpriteRenderer.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameObject\GameObject.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"


SpriteRenderer::SpriteRenderer(Sprite * sprite, int sortingOrder, const std::string & name) :
	Component(name),
	sprite(sprite),
	sortingOrder(sortingOrder)
{
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::SetDrawOrder(int drawOrder)
{
	this->sortingOrder = drawOrder;
}

void SpriteRenderer::LateUpdate()
{
	GameSystem::Draw(
		gameObject->GetTransform(),
		sprite->GetTexture()->GetObjectID(),
		sprite->GetRect(),
		sprite->GetPixelsPerUnit(),
		this->sortingOrder);
}
