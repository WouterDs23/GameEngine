#pragma once
#include "BaseComponent.h"
namespace dae
{
	class SolidComponent : public BaseComponent
	{
	public:
		SolidComponent();
		~SolidComponent() override;
		
		void Initialize() override;
		void Update() override;
		void Render() override;

		SolidComponent(const SolidComponent& other) = delete;
		SolidComponent(SolidComponent&& other) noexcept = delete;
		SolidComponent& operator=(const SolidComponent& other) = delete;
		SolidComponent& operator=(SolidComponent&& other) noexcept = delete;
	};
}
