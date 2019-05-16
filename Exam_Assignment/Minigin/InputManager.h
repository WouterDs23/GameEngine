#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Commands.h"
#include <map>

namespace dae
{
	enum class Controllers
	{
		PLAYER01 = 0,
		PLAYER02 = 1,
		PLAYER03 = 2,
		PLAYER04 = 3
	};
	enum InputTriggerState
	{
		Pressed,
		Released,
		Down
	};
	struct Input
	{
		Input() :
			Id(-1),
			Actor(),
			sortCommand(),
			TriggerState(Pressed),
			KeyBoardCode(-1),
			ControllerButton(0),
			Player()
		{}

		Input(int id, std::shared_ptr<GameObject> actor, std::unique_ptr<Commands> command, InputTriggerState state = Pressed, int keyboardCode = -1, int gamepadButtonCode = 0, Controllers player = Controllers::PLAYER01)
			:Id(id),
			Actor(actor),
			sortCommand(std::move(command)),
			TriggerState(state),
			KeyBoardCode(keyboardCode),
			ControllerButton(gamepadButtonCode),
			Player(player)
		{

		}
		int Id{ 0 };
		std::shared_ptr<GameObject> Actor;
		std::unique_ptr<Commands> sortCommand;
		InputTriggerState TriggerState;
		int KeyBoardCode;
		int ControllerButton;
		Controllers Player;
	};
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void ConfigButtons(std::shared_ptr<dae::Input> input);
	private:
		bool IsPressed(const  std::weak_ptr<dae::Input>) const;
		static const int MAX_CONTROLLERS{ 4 };
		XINPUT_STATE m_State{};
		bool m_EndIt{ false };
		std::map<int, std::shared_ptr<dae::Input>> m_Controllers;
	};

}
