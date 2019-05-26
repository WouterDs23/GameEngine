#pragma once
#include "BaseState.h"

namespace Enemies
{
	class WanderState final : public dae::BaseState
	{
	public:
		WanderState() = default;
		~WanderState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		float m_Timer{};
		float m_EndTimer{ -1.f };
	};

	class SeekState final : public dae::BaseState
	{
	public:
		SeekState() = default;
		~SeekState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	};

	/*class RunAwayState final : public dae::BaseState
	{
	public:
		RunAwayState() = default;
		~RunAwayState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	};*/

	class GhostState final : public dae::BaseState
	{
	public:
		GhostState() = default;
		~GhostState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		float m_Timer{};
	};
	class EnemyHitState final : public dae::BaseState
	{
	public:
		EnemyHitState() = default;
		~EnemyHitState() override = default;

		bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
		void Update(std::weak_ptr<dae::GameObject>) override;
	private:
		float m_Timer{};
	};
}