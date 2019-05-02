#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Commands.h"
#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		DPad_Up = XINPUT_GAMEPAD_DPAD_UP,
		DPad_Down = XINPUT_GAMEPAD_DPAD_DOWN,
		DPad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
		DPad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void ConfigButtons(ControllerButton button, std::unique_ptr<Commands> sortCommand);
		bool IsPressed(ControllerButton button) const;
		void SetActor(std::shared_ptr<GameObject> actor);
	private:
		XINPUT_STATE m_State{};
		bool m_EndIt{false};
		std::map<ControllerButton, std::unique_ptr<Commands>> m_Controllers;
		std::weak_ptr<GameObject> m_Actor;
	};

}
