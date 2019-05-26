#pragma once
#include "Scene.h"
#include <future>
#include "BaseState.h"

namespace dae
{
	class NormalGame final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
	class TwoPlayerGame final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
	class VersusGame final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
	class GameObject;
	class TextObject;
	class MainMenuLevel final :public dae::Scene
	{
	public:
		explicit MainMenuLevel(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void Reset() override;

		MainMenuLevel(const MainMenuLevel& other) = delete;
		MainMenuLevel(MainMenuLevel&& other) = delete;
		MainMenuLevel& operator=(const MainMenuLevel& other) = delete;
		MainMenuLevel& operator=(MainMenuLevel&& other) = delete;
	private:
		std::shared_ptr<GameObject> m_pBackGround;
		std::shared_ptr<dae::TextObject> m_OnePlayer;
		std::shared_ptr<dae::TextObject> m_TwoPlayers;
		std::shared_ptr<dae::TextObject> m_Versus;
		std::shared_ptr<dae::TextObject> m_Quit;
	};
}
