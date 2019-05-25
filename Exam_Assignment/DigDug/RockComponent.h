#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace Environment
{
	class RockComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		RockComponent();
		~RockComponent() override = default;

		RockComponent(const RockComponent& other) = delete;
		RockComponent(RockComponent&& other) noexcept = delete;
		RockComponent& operator=(const RockComponent& other) = delete;
		RockComponent& operator=(RockComponent&& other) noexcept = delete;

		void AddEnemy(std::weak_ptr<dae::GameObject> enemy) { m_Enemies.push_back(enemy); }
		std::vector<std::weak_ptr<dae::GameObject>> GetEnemies() const { return m_Enemies; }

		void SetObstacles(std::vector<std::weak_ptr<dae::GameObject>> obstacles) { m_Obstacles = obstacles; }
		std::vector<std::weak_ptr<dae::GameObject>> GetObstacles() const { return m_Obstacles; }

		void Initialize() override;
		void Update() override;
		void Render() override;
	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_Enemies;
		std::vector<std::weak_ptr<dae::GameObject>> m_Obstacles;
		bool m_AvoidingCollision = false;
	};
}
