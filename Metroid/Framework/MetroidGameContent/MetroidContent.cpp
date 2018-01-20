#include "MetroidContent.h"
#include "MetroidScene.h"
#include "GameFramework\GameContent\Texture.h"

void MetroidContent::Initialize()
{
	LoadCollisionBoxes("CollisionBoxes.xml");

	Texture* tileset = AddTexture("TileSet.png", ARGB(255, 0, 0, 0), "TileSetTexture");
	Texture* tex = AddTexture("Brinstar.png", ARGB(255, 0, 0, 0), "MetroidTexture");
	AddSprite(tex, Rect(0, 4560, 0, 7680), 16.0f, "BrinstarSprite");
	AddSprite(tex, Rect(620, 652, 1, 17), 16.0f, "CharacterSprite");
	
	Scene* scene = new MetroidScene("MetroidScene");
	GameContent::AddStartScene(scene);
	//GameContent::StartScene = GetObjectByName<MetroidScene>("MetroidScene");
}


MetroidContent::~MetroidContent()
{
	if (MainScene)
	{
		delete MainScene;
		MainScene = nullptr;
	}
}
