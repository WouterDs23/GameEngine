#include "MiniginPCH.h"
#include "CharacterBehaviour.h"
#include <string>

bool WalkingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	std::string name = typeid(input.lock()->sortCommand.operator*()).name();
	if (name == "class MoveDown")
	{
		return input.lock()->sortCommand->execute(obj);
	}
	return input.lock()->sortCommand->execute(obj);
}

void WalkingState::Update(std::weak_ptr<dae::GameObject>)
{

}
