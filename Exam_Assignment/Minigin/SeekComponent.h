#pragma once
#include "BaseComponent.h"
namespace dae
{
	class SeekComponent final : public BaseComponent
	{
	public:
		SeekComponent();
		~SeekComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;

		SeekComponent(const SeekComponent& other) = delete;
		SeekComponent(SeekComponent&& other) noexcept = delete;
		SeekComponent& operator=(const SeekComponent& other) = delete;
		SeekComponent& operator=(SeekComponent&& other) noexcept = delete;
	};
}
