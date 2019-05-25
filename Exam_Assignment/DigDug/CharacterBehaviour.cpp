#include "MiniginPCH.h"
#include "CharacterBehaviour.h"
#include <string>
#include "GameObject.h"
#include "GunComponent.h"

bool DigDug::IdleState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::MoveDown" || newState == "class dae::MoveUp" || newState == "class dae::MoveRight" || newState == "class dae::MoveLeft")
		{
			obj.lock()->SetState(std::make_shared<WalkingState>());
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

void DigDug::IdleState::Update(std::weak_ptr<dae::GameObject>)
{

}

bool DigDug::WalkingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::MoveDown" || newState == "class dae::MoveUp" || newState == "class dae::MoveRight" || newState == "class dae::MoveLeft")
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

void DigDug::WalkingState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		m_Timer += GameLifeSpan::deltaTime;
		if (m_Timer >= 5.f)
		{
			obj.lock()->SetState(std::make_shared<IdleState>());
		}
	}	
}

bool DigDug::ShootingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::ExitGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (currentState == "class ShootingState" && newState == "class Shoot")
		{
			auto gun = obj.lock()->GetComponent<GunComponent>().lock();
			if (gun)
			{
				gun->DoPump();
			}
		}		
	}
	m_FirstTime = false;
	return false;
}

void DigDug::ShootingState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		m_Timer += GameLifeSpan::deltaTime;
		if (m_Timer >= 5.f)
		{
			obj.lock()->SetState(std::make_shared<IdleState>());
		}
	}
}

bool DigDug::HitState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
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

void DigDug::HitState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		m_Timer += GameLifeSpan::deltaTime;
		if (m_Timer >= 1.f)
		{
			obj.lock()->SetState(std::make_shared<IdleState>());
		}
	}
}

bool DigDug::DeadState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	return false;
}

void DigDug::DeadState::Update(std::weak_ptr<dae::GameObject>)
{
}
