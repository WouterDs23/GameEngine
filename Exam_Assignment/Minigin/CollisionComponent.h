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

		bool CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other);
		bool CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other);

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
	};
}
