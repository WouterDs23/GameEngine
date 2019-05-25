#include "MiniginPCH.h"
#include "FygarBehaviourh.h"
#include "EnemyBehaviour.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "GhostComponent.h"

bool Fygar::ShootingState::HandleInput(std::weak_ptr<dae::GameObject>, std::weak_ptr<dae::Input>)
{
	return false;
}

void Fygar::ShootingState::Update(std::weak_ptr<dae::GameObject> obj)
{
	if (obj.lock())
	{
		auto ghost = obj.lock()->GetComponent<Enemies::GhostComponent>();
		obj.lock()->GetComponent<dae::WanderComponent>().lock()->StopWander();
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
			obj.lock()->SetState(std::make_shared<Enemies::WanderState>());
		}
	}
}
