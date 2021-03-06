#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class MoveComponent final : public BaseComponent
	{
	public:
		MoveComponent(float MoveSpeed = 1.f);
		~MoveComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void SetSpeed(float MoveSpeed);
		void MoveObject(float xSpeed, float ySpeed, float zSpeed = 0);
		glm::vec3 GetPrevSpeed() const { return m_PrevSpeed; }

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) noexcept = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) noexcept = delete;
	private:
		float m_MoveSpeed;
		glm::vec3 m_PrevSpeed{1.f,0.f,0.f};
	};
}

