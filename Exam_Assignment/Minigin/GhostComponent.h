#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GhostComponent : public BaseComponent
	{
	public:
		GhostComponent();
		~GhostComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;
	};
}
