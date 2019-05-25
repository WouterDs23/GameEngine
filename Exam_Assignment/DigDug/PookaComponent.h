#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace Enemies
{
	class PookaComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		PookaComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles);
		~PookaComponent() override = default;

		PookaComponent(const PookaComponent& other) = delete;
		PookaComponent(PookaComponent&& other) noexcept = delete;
		PookaComponent& operator=(const PookaComponent& other) = delete;
		PookaComponent& operator=(PookaComponent&& other) noexcept = delete;


		void Initialize() override;
		void Update() override;
		void Render() override;

		void NextStage();
		void ResetStage();
	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_Obstacles;
		int m_Stage{};
	};
}
