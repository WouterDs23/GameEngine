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
}