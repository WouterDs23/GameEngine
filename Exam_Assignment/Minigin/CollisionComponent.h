#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae {
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent();
		~CollisionComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		const bool CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other, float offset = 0, bool doDamage = false) const;
		const bool CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other, float offset = 0, bool doDamage = false) const;
		const bool CheckIfInObject(std::weak_ptr<dae::GameObject> other) const;
		void SetIsObstacle(bool isObstacle = true)
		{
			m_IsObstacle = isObstacle;
		}
		bool GetIsObstacle() const { return  m_IsObstacle; }

		void EnableGhost(bool enable);

		void DoCollision(bool enable) { m_doCollision = enable; }

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
	private:
		bool m_IsObstacle;
		bool m_InGhostForm;
		bool m_doCollision{true};
	};
}
