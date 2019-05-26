#include "MiniginPCH.h"
#include "FygarBehaviourh.h"
#include "EnemyBehaviour.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "GhostComponent.h"

bool Fygar::ShootingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::ExitGame" || newState == "class dae::ResetGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
	}
	m_FirstTime = false;
	return false;
	return false;
}

void Fygar::ShootingState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		auto ghost = obj.lock()->GetComponent<Enemies::GhostComponent>();
		auto wand = obj.lock()->GetComponent<dae::WanderComponent>().lock();
		if (wand)
		{
			wand->StopWander();
		}
		if (ghost.lock())
		{
			ghost.lock()->EnableGhostMode(false);
		}
		auto seek = obj.lock()->GetComponent<dae::SeekComponent>().lock();
		auto col = obj.lock()->GetComponent<dae::CollisionComponent>().lock();
		auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
		if (seek && AI)
		{
			seek->SetTarget(std::make_shared<dae::GameObject>());
		}

		m_Timer += GameLifeSpan::deltaTime;
		if (m_Timer >= 0.5f)
		{
			if (seek)
			{
				obj.lock()->SetState(std::make_shared<Enemies::WanderState>());
			}
			else
			{
				obj.lock()->SetState(std::make_shared<Fygar::IdleState>());
			}
			
		}
	}
}

bool Fygar::IdleState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::MoveDown" || newState == "class dae::MoveUp" || newState == "class dae::MoveRight" || newState == "class dae::MoveLeft" || newState == "class Enemies::Ghost")
		{
			obj.lock()->SetState(std::make_shared<WalkingState>());
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class dae::ExitGame" || newState == "class dae::ResetGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class Enemies::Shoot")
		{
			obj.lock()->SetState(std::make_shared<ShootingState>());
			return input.lock()->sortCommand->execute(obj);
		}
	}
	return false;
}

void Fygar::IdleState::Update(std::weak_ptr<dae::GameObject>)
{

}

bool Fygar::WalkingState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::MoveDown" || newState == "class dae::MoveUp" || newState == "class dae::MoveRight" || newState == "class dae::MoveLeft" || newState == "class Enemies::Ghost")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class dae::ExitGame" || newState == "class dae::ResetGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
		if (newState == "class Enemies::Shoot")
		{
			obj.lock()->SetState(std::make_shared<ShootingState>());
			return input.lock()->sortCommand->execute(obj);
		}
	}
	return false;
}

void Fygar::WalkingState::Update(std::weak_ptr<dae::GameObject> obj)
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

bool Fygar::HitState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	if (input.lock() && obj.lock())
	{
		std::string newState = typeid(input.lock()->sortCommand.operator*()).name();
		std::string currentState = typeid(obj.lock()->GetState().lock().operator*()).name();
		if (newState == "class dae::ExitGame" || newState == "class dae::ResetGame")
		{
			return input.lock()->sortCommand->execute(obj);
		}
	}
	return false;
}

void Fygar::HitState::Update(std::weak_ptr<dae::GameObject> obj)
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

bool Fygar::DeadState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	return false;
}

void Fygar::DeadState::Update(std::weak_ptr<dae::GameObject>)
{
}
