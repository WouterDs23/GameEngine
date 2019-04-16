#pragma once
#include "BaseComponent.h"
namespace dae
{
	class WanderComponent : public BaseComponent
	{
	public:
		WanderComponent(bool StartWander);
		~WanderComponent() override;

		void Initialize() override;
		void Update() override;
		void Render() override;
		void DoWander();
		void StopWander();


		WanderComponent(const WanderComponent& other) = delete;
		WanderComponent(WanderComponent&& other) noexcept = delete;
		WanderComponent& operator=(const WanderComponent& other) = delete;
		WanderComponent& operator=(WanderComponent&& other) noexcept = delete;
	private:
		bool m_DoWander;
	};
}
