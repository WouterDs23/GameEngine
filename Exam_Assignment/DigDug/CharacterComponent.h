#pragma once
#include "BaseComponent.h"
namespace dae
{
	class CharacterComponent final : public dae::BaseComponent
	{
	public:
		CharacterComponent();
		~CharacterComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		void SetObstacles(std::vector<std::shared_ptr<dae::GameObject>> obstacles) { m_Obstacles = obstacles; }
		std::vector<std::shared_ptr<dae::GameObject>> GetObstacles() const { return m_Obstacles; }
		bool GetCollidedLeft() const { return m_JustCollidedLeft; }
		bool GetCollidedRight() const { return m_JustCollidedRight; }
		bool GetCollidedTop() const { return m_JustCollidedUp; }
		bool GetCollidedBottom() const { return m_JustCollidedDown; };

		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) noexcept = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;

	private:
		std::vector<std::shared_ptr<dae::GameObject>> m_Obstacles;
		bool m_JustCollidedLeft{};
		bool m_JustCollidedUp{};
		bool m_JustCollidedDown{};
		bool m_JustCollidedRight{};
	};
}
