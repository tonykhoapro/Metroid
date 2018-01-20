#include "MetroidScene.h"
#include "MetroidContent.h"
#include "MetroidCharacter.h"
#include "MetroidGameContent\Brinstar.h"
#include "Zoomer.h"
#include "GameFramework\GameObject\StaticBox.h"

MetroidScene::MetroidScene(const std::string & name):
	Scene(name)
{
	ActiveGameObjects.push_back(AddNewGameObject<Brinstar>(Transform(Vec2(240.0f, 142.5f))));
	AddNewGameObject<MetroidCharacter>(Transform(Vec2(40.0f, 86.1f)));
	ActiveGameObjects.push_back(AddNewGameObject<Zoomer>(Transform(Vec2(40.0f, 80.0f))));
	//ActiveGameObjects.push_back(AddNewGameObject<StaticBox>(Transform(Vec2(40.17f, 77.19f))));
}

MetroidScene::~MetroidScene()
{
}
