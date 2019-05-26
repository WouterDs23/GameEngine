#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace Enemies
{
	class FireComponent final : public dae::BaseComponent
	{
	public:
		FireComponent(float collisionSizeX, float collisionSizeY, std::shared_ptr<dae::GameObject> firegun, std::weak_ptr<dae::GameObject> parent);
		~FireComponent() override = default;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void CanFire(bool canI) { m_CanFire = canI; }

		void SetGun(std::weak_ptr<dae::GameObject> gun) { m_FireGun = gun; }

		void Shoot();

		FireComponent(const FireComponent& other) = delete;
		FireComponent(FireComponent&& other) noexcept = delete;
		FireComponent& operator=(const FireComponent& other) = delete;
		FireComponent& operator=(FireComponent&& other) noexcept = delete;
	private:
		std::weak_ptr<dae::GameObject> m_FireGun{};
		std::weak_ptr<dae::GameObject> m_Parent{};
		glm::vec3 m_CollisionSize{};
		float m_Timer{};
		bool m_CanFire{ true };
	};
}

