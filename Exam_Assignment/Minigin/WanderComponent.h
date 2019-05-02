#pragma once
#include "BaseComponent.h"
#include "Commands.h"

namespace dae
{
	class WanderComponent final : public BaseComponent
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
		enum Direction
		{
			Left,
			Right,
			Down,
			Up,
			Default
		};
		void RandomDirCalc(Direction DontGo = Default);

		bool m_DoWander;
		bool m_WanderLeft;
		bool m_WanderRight;
		bool m_WanderTop;
		bool m_WanderBottem;
		std::unique_ptr<Commands> m_GoLeft;
		std::unique_ptr<Commands> m_GoRight;
		std::unique_ptr<Commands> m_GoUp;
		std::unique_ptr<Commands> m_GoDown;
	};
}
