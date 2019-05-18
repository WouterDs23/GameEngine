#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae {
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent();
		CollisionComponent(Transform size);
		~CollisionComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		const bool CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other, float offset = 0);
		const bool CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other, float offset = 0);
		const bool CheckIfInObject(std::weak_ptr<dae::GameObject> other);
		void SetIsObstacle(bool isObstacle = true)
		{
			m_IsObstacle = isObstacle;
		}
		bool GetIsObstacle() const { return  m_IsObstacle; }

		void EnableGhost(bool enable);

		Transform GetTransform() const { return m_Transform; }

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
	private:
		bool m_IsObstacle;
		bool m_InGhostForm;
		bool m_Init{false};
		Transform m_Transform; 
	};
}
