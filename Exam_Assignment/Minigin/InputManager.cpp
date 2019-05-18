#include "MiniginPCH.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		ZeroMemory(&m_State, sizeof(XINPUT_STATE));
		XInputGetState(i, &m_State);
		for (std::map<int, std::shared_ptr<dae::Input>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
		{
			if (IsPressed(it->second))
			{
				if (Controllers(i) == it->second->Player)
				{
					if (it->second->TriggerState != InputTriggerState::Released)
					{
						m_EndIt = it->second->Actor->HandleInput(it->second);
						it->second->DoExecute = false;
					}
					else
					{
						it->second->DoExecute = true;
					}
				}
			}
			else
			{
				if (it->second->DoExecute)
				{
					m_EndIt = it->second->Actor->HandleInput(it->second);
					it->second->DoExecute = false;
				}
				
			}
		}
	}
	return !m_EndIt;
}

void dae::InputManager::ConfigButtons(std::shared_ptr<dae::Input>  input)
{
	for (std::map<int, std::shared_ptr<dae::Input>>::iterator it = m_Controllers.begin(); it != m_Controllers.end(); it++)
	{
		if (it->first == input->Id && it->second->Player == input->Player)
		{
			it->second = input;
			return;
		}
	}
	m_Controllers[input->Id] = input;
}

bool dae::InputManager::IsPressed(const std::weak_ptr<dae::Input> input) const
{
	//http://gameprogrammingpatterns.com/command.html
	if (input.lock()->KeyBoardCode != -1)
	{
		return GetAsyncKeyState(input.lock()->KeyBoardCode) & 0x8000;
	}

	return (m_State.Gamepad.wButtons & int(input.lock()->ControllerButton)) != 0;
}

