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
		if (newState == "class MoveDown" || newState == "class MoveUp" || newState == "class MoveRight" || newState == "class MoveLeft")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class dae::ExitGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class Shoot")
		{
			obj.lock()->SetState(std::make_shared<ShootingState>());
			return input.lock()->sortCommand->execute(obj);
		}
	}
	return false;
}

void WalkingState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		
	}	
}

bool ShootingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::ExitGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
	}
	return false;
}

void ShootingState::Update(std::weak_ptr<dae::GameObject>)
{

}

bool HitState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	return false;
}

void HitState::Update(std::weak_ptr<dae::GameObject>)
{

}

bool DeadState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	return false;
}

void DeadState::Update(std::weak_ptr<dae::GameObject>)
{
}
