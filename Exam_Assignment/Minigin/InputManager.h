#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void ConfigButtons(ControllerButton button, std::unique_ptr<Command> sortCommand);
		Command& HandleInput() const;
		bool IsPressed(ControllerButton button) const;
	private:
		XINPUT_STATE m_State;
		bool m_EndIt{false};

		std::unique_ptr<Command> m_ButtonX{};
		std::unique_ptr<Command> m_ButtonY{};
		std::unique_ptr<Command> m_ButtonA{};
		std::unique_ptr<Command> m_ButtonB{};
		std::unique_ptr<Command> m_Default = std::make_unique<Command>();
	};

}
