#pragma once
#include "Singleton.h"
#include "SceneManager.h"

class Time final : public dae::Singleton<Time>
{
public:
	float GetDeltaTime()
	{
		return deltaTime;
	}
	void SetDeltaTime(float delta) { deltaTime = delta; }
private:
	float deltaTime;
};

