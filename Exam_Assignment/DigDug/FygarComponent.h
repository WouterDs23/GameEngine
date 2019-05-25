#pragma once
#include "BaseComponent.h"

namespace Enemies
{
	class FygarComponent final : public dae::BaseComponent
	{
	public:
		FygarComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles);
		~FygarComponent() override = default;

		FygarComponent(const FygarComponent& other) = delete;
		FygarComponent(FygarComponent&& other) noexcept = delete;
		FygarComponent& operator=(const FygarComponent& other) = delete;
		FygarComponent& operator=(FygarComponent&& other) noexcept = delete;


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

