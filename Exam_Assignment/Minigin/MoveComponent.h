#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		MoveComponent(float xSpeed = 0, float ySpeed = 0, float zSpeed = 0);
		~MoveComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void SetSpeed(float xSpeed, float ySpeed, float zSpeed = 0);
		glm::vec3 GetSpeed() const { return m_Speed; }
		void MoveObject(const float xSpeed, const float ySpeed, const float zSpeed = 0) const;

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) noexcept = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) noexcept = delete;
	private:
		glm::vec3 m_Speed{};
	};
}

