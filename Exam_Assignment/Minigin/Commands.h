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
	class MoveLeft : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveRight : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveUp : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveDown : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class ExitGame : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject>) override { return true; }
	};
}