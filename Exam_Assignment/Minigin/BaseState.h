#pragma once
namespace dae
{
	class GameObject;
	class Command;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;

		virtual void HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<Command>) {};
		virtual void Update(std::weak_ptr<dae::GameObject>) {};
	};
}

