#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_State);
	m_EndIt = HandleInput().execute();
	return !m_EndIt;
}

void dae::InputManager::ConfigButtons(ControllerButton button, std::unique_ptr<Command> sortCommand)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		/*if (m_ButtonA)
		{
			delete m_ButtonA;
			m_ButtonA = nullptr;
		}*/
		m_ButtonA.swap(sortCommand);
		break;
	case ControllerButton::ButtonB:
		/*if (m_ButtonB)
		{
			delete m_ButtonB;
			m_ButtonB = nullptr;
		}*/
		m_ButtonB.swap(sortCommand);
		break;
	case ControllerButton::ButtonX:
		/*if (m_ButtonX)
		{
			delete m_ButtonX;
			m_ButtonX = nullptr;
		}*/
		m_ButtonX.swap(sortCommand);
		break;
	case ControllerButton::ButtonY:
		/*if (m_ButtonY)
		{
			delete m_ButtonY;
			m_ButtonY = nullptr;
		}*/
		m_ButtonY.swap(sortCommand);
		break;
	}
}

Command& dae::InputManager::HandleInput() const
{
	if (IsPressed(dae::ControllerButton::ButtonA))
	{
		return *m_ButtonA;
	}
	else if (IsPressed(dae::ControllerButton::ButtonB))
	{
		return *m_ButtonB;
	}
	else if (IsPressed(dae::ControllerButton::ButtonX))
	{
		return *m_ButtonX;
	}
	else if (IsPressed(dae::ControllerButton::ButtonY))
	{
		return *m_ButtonY;
	}
	return *m_Default;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	if ((m_State.Gamepad.wButtons & int(button)) != 0)
	{	//http://gameprogrammingpatterns.com/command.html
		switch (button)
		{
		case ControllerButton::ButtonA:
			return true;
			break;
		case ControllerButton::ButtonB:
			return true;
			break;
		case ControllerButton::ButtonX:
			return true;
			break;
		case ControllerButton::ButtonY:
			return true;
			break;
		}
	}
	return false;
}

