#pragma once
#include "BaseComponent.h"

namespace dae {
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent();
		~CollisionComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		const bool CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other);
		const bool CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other);
		const bool CheckIfInObject(std::weak_ptr<dae::GameObject> other);
		void SetIsObstacle(bool isObstacle = true)
		{
			m_IsObstacle = isObstacle;
		}
		const bool GetIsObstacle() const { return  m_IsObstacle; }

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
	private:
		bool m_IsObstacle;
	};
}
