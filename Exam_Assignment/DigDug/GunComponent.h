#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
namespace DigDug
{
	class GunComponent :
		public dae::BaseComponent
	{
	public:
		GunComponent(std::shared_ptr<dae::GameObject> gun, std::weak_ptr<dae::GameObject> parent);
		~GunComponent() override = default;

		GunComponent(const GunComponent& other) = delete;
		GunComponent(GunComponent&& other) noexcept = delete;
		GunComponent& operator=(const GunComponent& other) = delete;
		GunComponent& operator=(GunComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

		std::shared_ptr<dae::GameObject> GetGun() const { return m_Gun; }

		void Shoot(float x, float y);
		void DoPump();
	private:
		std::shared_ptr<dae::GameObject> m_Gun{};
		std::weak_ptr<dae::GameObject> m_Parent{};
		bool m_Shot{ false };
		bool m_DoPump{ false };
		bool m_Hit{ false };
		float m_Timer{};
		float m_HitTimer{};
		float m_xSpeed{};
		float m_ySpeed{};

	};
}
