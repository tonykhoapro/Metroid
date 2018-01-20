#include "Brinstar.h"
#include "MetroidGameContent\MetroidContent.h"


Brinstar::Brinstar()
{
	this->name = "Brinstar";
	BrinstarSprite = AddComponent<SpriteRenderer>();
	BrinstarSprite->SetDrawOrder(1);
	BrinstarSprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("BrinstarSprite"));
}


Brinstar::~Brinstar()
{
}
