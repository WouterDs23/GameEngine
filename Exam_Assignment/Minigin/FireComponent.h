#pragma once
#include "BaseComponent.h"
namespace dae
{
	class FireComponent final : public dae::BaseComponent
	{
	public:
		FireComponent();
		~FireComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		FireComponent(const FireComponent& other) = delete;
		FireComponent(FireComponent&& other) noexcept = delete;
		FireComponent& operator=(const FireComponent& other) = delete;
		FireComponent& operator=(FireComponent&& other) noexcept = delete;
	};
}

