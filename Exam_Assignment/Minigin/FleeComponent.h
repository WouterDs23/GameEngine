#pragma once
#include "BaseComponent.h"
namespace dae
{
	class FleeComponent : public BaseComponent
	{
	public:
		FleeComponent();
		~FleeComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		FleeComponent(const FleeComponent& other) = delete;
		FleeComponent(FleeComponent&& other) noexcept = delete;
		FleeComponent& operator=(const FleeComponent& other) = delete;
		FleeComponent& operator=(FleeComponent&& other) noexcept = delete;
	};
}
