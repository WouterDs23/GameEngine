#include "MiniginPCH.h"
#include "CharacterBehaviour.h"
#include <string>
#include "GameObject.h"

bool WalkingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class MoveDown")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class MoveUp")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class MoveRight")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class MoveLeft")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		return input.lock()->sortCommand->execute(obj);
	}
	return false;
}

void WalkingState::Update(std::weak_ptr<dae::GameObject>)
{

}
