#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae {
	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent();
		~CollisionComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		bool CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other, float offsetX = 0, float offsetY = 0, bool overrideGhost = false) const;
		bool CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other, float offsetX = 0, float offsetY = 0, bool overrideGhost = false) const;
		bool CheckIfInObject(std::weak_ptr<dae::GameObject> other) const;
		bool CheckIfObjectInMe(glm::vec3 size,std::weak_ptr<dae::GameObject> other) const;
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
