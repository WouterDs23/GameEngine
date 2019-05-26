#pragma once
#include "BaseState.h"
namespace Fygar
{
	class ShootingState final : public dae::BaseState
	{
	public:
		ShootingState() = default;
		~ShootingState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		bool m_FirstTime{ true };
		float m_Timer{};
	};

	class IdleState final : public dae::BaseState
	{
	public:
		IdleState() = default;
		~IdleState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	};

	class WalkingState final : public dae::BaseState
	{
	public:
		WalkingState() = default;
		~WalkingState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		float m_Timer{};
	};

	class HitState final : public dae::BaseState
	{
	public:
		HitState() = default;
		~HitState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		float m_Timer{};
	};
	class DeadState final : public dae::BaseState
	{
	public:
		DeadState() = default;
		~DeadState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	};
}
