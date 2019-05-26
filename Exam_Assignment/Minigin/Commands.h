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

	class ResetGame final : public Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject>) override
		{
			SceneManager::GetInstance().ResetScene();
			return false;
		}
	};

	class MoveLeft final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveRight final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveUp final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MoveDown final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
}