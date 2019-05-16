#pragma once
#include "InputManager.h"

namespace dae
{
	class GameObject;
	class Command;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;

		virtual bool HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<Input>) { return false; }
		virtual void Update(std::weak_ptr<dae::GameObject>) {}
	};
}

