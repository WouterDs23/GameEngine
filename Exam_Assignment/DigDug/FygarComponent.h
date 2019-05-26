#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "InputManager.h"

namespace Enemies
{
	class Shoot final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
	class Ghost final : public dae::Commands
	{
	public:
		virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
	};
	class FygarComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		FygarComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles, std::shared_ptr<dae::GameObject> fireGun, dae::Controllers controller = dae::Controllers::None);
		~FygarComponent() override = default;

		FygarComponent(const FygarComponent& other) = delete;
		FygarComponent(FygarComponent&& other) noexcept = delete;
		FygarComponent& operator=(const FygarComponent& other) = delete;
		FygarComponent& operator=(FygarComponent&& other) noexcept = delete;

		std::shared_ptr<dae::GameObject> GetGun() const { return m_FireGun; }


		void Initialize() override;
		void Update() override;
		void Render() override;

		void NextStage();
		void ResetStage();
	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_Obstacles;
		std::shared_ptr<dae::GameObject> m_FireGun;
		dae::Controllers m_Controller{};
		int m_Stage{};
	};
}

