#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_State);
	m_EndIt = HandleInput().execute(m_Actor);
	return !m_EndIt;
}

void dae::InputManager::ConfigButtons(ControllerButton button, std::unique_ptr<Commands> sortCommand)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		m_ButtonA.swap(sortCommand);
		break;
	case ControllerButton::ButtonB:
		m_ButtonB.swap(sortCommand);
		break;
	case ControllerButton::ButtonX:
		m_ButtonX.swap(sortCommand);
		break;
	case ControllerButton::ButtonY:
		m_ButtonY.swap(sortCommand);
	case ControllerButton::DPad_Up:
		m_ButtonDU.swap(sortCommand);
		break;
	case ControllerButton::DPad_Down:
		m_ButtonDD.swap(sortCommand);
		break;
	case ControllerButton::DPad_Left:
		m_ButtonDL.swap(sortCommand);
		break;
	case ControllerButton::DPad_Right:
		m_ButtonDR.swap(sortCommand);
		break;
	}
}

dae::Commands& dae::InputManager::HandleInput() const
{
	if (IsPressed(dae::ControllerButton::ButtonA))
	{
		return *m_ButtonA;
	}
	if (IsPressed(dae::ControllerButton::ButtonB))
	{
		return *m_ButtonB;
	}
	if (IsPressed(dae::ControllerButton::ButtonX))
	{
		return *m_ButtonX;
	}
	if (IsPressed(dae::ControllerButton::ButtonY))
	{
		return *m_ButtonY;
	}
	if (IsPressed(dae::ControllerButton::DPad_Up))
	{
		return *m_ButtonDU;
	}
	if (IsPressed(dae::ControllerButton::DPad_Down))
	{
		return *m_ButtonDD;
	}
	if (IsPressed(dae::ControllerButton::DPad_Left))
	{
		return *m_ButtonDL;
	}
	if (IsPressed(dae::ControllerButton::DPad_Right))
	{
		return *m_ButtonDR;
	}
	return *m_Default;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	//http://gameprogrammingpatterns.com/command.html
		
	return (m_State.Gamepad.wButtons & int(button)) != 0;
}

void dae::InputManager::SetActor(std::shared_ptr<GameObject> actor)
{
	m_Actor = actor;
}

