#include "MiniginPCH.h"
#include "PookaBehaviour.h"
#include "GameObject.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "AIComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"

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
				if (obs)
				{
					auto collision = obs->GetComponent<dae::CollisionComponent>().lock();
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
