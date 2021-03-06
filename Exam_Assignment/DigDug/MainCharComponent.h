#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

namespace DigDug
{
	class Shoot final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};

	class MainCharComponent final : public dae::BaseComponent
	{
	public:
		MainCharComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles, dae::Controllers controller);
		~MainCharComponent() override;

		MainCharComponent(const MainCharComponent& other) = delete;
		MainCharComponent(MainCharComponent&& other) noexcept = delete;
		MainCharComponent& operator=(const MainCharComponent& other) = delete;
		MainCharComponent& operator=(MainCharComponent&& other) noexcept = delete;


		void Initialize() override;
		void Update() override;
		void Render() override;

		void ResetLevel(bool reset = true) { m_ResetLevel = reset; }
		bool GetResetLevel() const { return m_ResetLevel; }
	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_Obstacles;
		dae::Controllers m_Controller{};
		bool m_ResetLevel{ false };
	};
}
