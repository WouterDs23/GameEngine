#include "MiniginPCH.h"
#include "PookaBehaviour.h"
#include "GameObject.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "AIComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "HealthComponent.h"
#include "PookaComponent.h"

bool WanderState::HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<dae::Input>)
{
	return false;
}

void WanderState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (m_EndTimer < 0.f)
	{
		m_EndTimer = float(rand() % 3) + 2;
	}
	m_Timer += GameLifeSpan::deltaTime;
	
	if (obj.lock())
	{
		auto seek = obj.lock()->GetComponent<dae::SeekComponent>().lock();
		auto col = obj.lock()->GetComponent<dae::CollisionComponent>().lock();
		auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
		if (seek && AI)
		{
			seek->SetTarget(std::make_shared<dae::GameObject>());
		}
	}
	if (m_Timer >= m_EndTimer)
	{
		
		if (obj.lock())
		{
			obj.lock()->SetState(std::make_shared<GhostState>());
			auto ghost = obj.lock()->GetComponent<dae::GhostComponent>();
			auto seek = obj.lock()->GetComponent<dae::SeekComponent>().lock();
			auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
			obj.lock()->GetComponent<dae::WanderComponent>().lock()->StopWander();
			if (ghost.lock())
			{
				ghost.lock()->EnableGhostMode();
			}
			if (seek && AI)
			{
				seek->SetTarget(AI->GetEnemy());
			}
		}
	}
}

bool SeekState::HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<dae::Input>)
{
	return false;
}

void SeekState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		auto seek = obj.lock()->GetComponent<dae::SeekComponent>().lock();
		auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
		if (seek && AI)
		{
			seek->SetTarget(AI->GetEnemy());
		}
	}
}

bool GhostState::HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<dae::Input>)
{
	return false;
}

void GhostState::Update(std::weak_ptr<dae::GameObject> obj)
{
	m_Timer += GameLifeSpan::deltaTime;
	if (!(m_Timer >= 1.f))
	{
		return;
	}
	if (obj.lock())
	{
		auto col = obj.lock()->GetComponent<dae::CollisionComponent>().lock();
		auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
		if (col && AI)
		{
			auto obstacles = AI->GetObstacles();
			for (auto obs : obstacles)
			{
				if (obs.lock())
				{
					auto collision = obs.lock()->GetComponent<dae::CollisionComponent>().lock();
					if (collision)
					{
						if (!collision->GetIsObstacle())
						{
							if (col->CheckIfInObject(obs))
							{
								obj.lock()->SetState(std::make_shared<SeekState>());
								auto ghost = obj.lock()->GetComponent<dae::GhostComponent>();
								if (ghost.lock())
								{
									ghost.lock()->EnableGhostMode(false);
								}
							}
							
						}
					}
				}
			}
		}
	}
}

bool PookaHitState::HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input)
{
	return false;
}

void PookaHitState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		auto seek = obj.lock()->GetComponent<dae::SeekComponent>().lock();
		auto col = obj.lock()->GetComponent<dae::CollisionComponent>().lock();
		auto AI = obj.lock()->GetComponent<dae::AIComponent>().lock();
		if (seek && AI)
		{
			seek->SetTarget(std::make_shared<dae::GameObject>());
		}
		if (col)
		{
			col->DoCollision(false);
		}
	}
	m_Timer += GameLifeSpan::deltaTime;
	if ((m_Timer >= 1.5f))
	{
		const auto health = obj.lock()->GetComponent<HealthComponent>().lock();
		if (health)
		{
			health->SetLives(4);
		}

		auto pooka = obj.lock()->GetComponent<PookaComponent>().lock();
		if (pooka)
		{
			pooka->ResetStage();
		}
		obj.lock()->SetState(std::make_shared<SeekState>());
		auto col = obj.lock()->GetComponent<dae::CollisionComponent>().lock();
		if (col)
		{
			col->DoCollision(true);
		}
	}
}
