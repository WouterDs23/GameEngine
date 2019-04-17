#pragma once
#include "BaseComponent.h"
namespace dae
{
	class CharacterComponent : public BaseComponent
	{
	public:
		CharacterComponent();
		~CharacterComponent() override;

		void Execute();
		void Initialize() override;
		void Update() override;
		void Render() override;

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		void SetObstacles(std::vector<std::shared_ptr<dae::GameObject>> obstacles) { m_Obstacles = obstacles; }

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
