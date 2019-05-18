#pragma once
#include "Singleton.h"
#include "SceneManager.h"

struct GameLifeSpan final
{
	inline static float deltaTime{};
	inline static float elapsedTime{};
};