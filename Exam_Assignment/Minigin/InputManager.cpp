#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_State);
	for (std::map<ControllerButton , std::unique_ptr<Commands>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
	{
		if (IsPressed(ControllerButton(it->first)))
		{
			m_EndIt = it->second->execute(m_Actor);
		}
	}
	return !m_EndIt;
}

void dae::InputManager::ConfigButtons(ControllerButton button, std::unique_ptr<Commands> sortCommand)
{
	for (std::map<ControllerButton, std::unique_ptr<Commands>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
	{
		if (it->first == button)
		{
			it->second.swap(sortCommand);
			return;
		}
	}
	m_Controllers[button].swap(sortCommand);
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

