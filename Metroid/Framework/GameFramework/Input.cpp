#include "Input.h"
#include "Main\GameSystem.h"


Input::Input()
{
}


Input::~Input()
{
}

bool Input::IsKeyDown(unsigned int key)
{
	return GameSystem::IsKeyDown(key);
}

bool Input::IsKeyPressed(unsigned int key)
{
	return GameSystem::IsKeyPressed(key);
}
