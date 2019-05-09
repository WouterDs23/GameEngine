#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		ZeroMemory(&m_State, sizeof(XINPUT_STATE));
		XInputGetState(i, &m_State);
		for (std::map<std::pair<ControllerButton, Controllers>, std::unique_ptr<Commands>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
		{
			if (IsPressed(ControllerButton(it->first.first)))
			{
				if (Controllers(i) == it->first.second)
				{
					m_EndIt = it->second->execute(m_Actors[Controllers(i)]);
				}
			}
		}
	}
	return !m_EndIt;
}

void dae::InputManager::ConfigButtons(ControllerButton button, std::unique_ptr<Commands> sortCommand, Controllers controller)
{
	for (std::map<std::pair<ControllerButton, Controllers>, std::unique_ptr<Commands>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
	{
		if (it->first.first == button && it->first.second == controller)
		{
			it->second.swap(sortCommand);
			return;
		}
	}
	m_Controllers[std::make_pair(button, controller)].swap(sortCommand);
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	//http://gameprogrammingpatterns.com/command.html
		
	return (m_State.Gamepad.wButtons & int(button)) != 0;
}

void dae::InputManager::SetActor(std::shared_ptr<GameObject> actor , Controllers controller)
{
	m_Actors[controller] = actor;
}

