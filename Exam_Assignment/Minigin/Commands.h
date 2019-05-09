#pragma once
namespace dae
{
	class GameObject;
	class CharacterComponent;
	class Commands
	{
	public:
		Commands();
		virtual ~Commands();
		virtual bool execute(std::weak_ptr<dae::GameObject> actor);
	};

	class ExitGame final : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject>) override { return true; }
	};
}