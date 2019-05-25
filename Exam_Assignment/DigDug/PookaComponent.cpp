#include "MiniginPCH.h"
#include "PookaComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"
#include "EnemyBehaviour.h"
#include "SeekComponent.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"

Enemies::PookaComponent::PookaComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles):
m_Obstacles(obstacles)
{

}

void Enemies::PookaComponent::Initialize()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		gameObj->AddComponent(std::make_shared<dae::AIComponent>());
		gameObj->AddComponent(std::make_shared<dae::WanderComponent>(true));
		gameObj->AddComponent(std::make_shared<dae::SeekComponent>());
		gameObj->AddComponent(std::make_shared<Enemies::GhostComponent>("Pooka.png"));
		gameObj->AddComponent(std::make_shared<HealthComponent>(4));
		gameObj->GetComponent<dae::AIComponent>().lock()->SetObstacles(m_Obstacles);
		gameObj->GetComponent<dae::MoveComponent>().lock()->SetSpeed(2);
		gameObj->GetComponent<HealthComponent>().lock()->SetState(std::make_shared<Enemies::EnemyHitState>());
		gameObj->SetState(std::make_shared<Enemies::WanderState>());
		gameObj->SetTexture("Pooka.png");
	}
}

void Enemies::PookaComponent::Update()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		const auto health = gameObject.lock()->GetComponent<HealthComponent>().lock();
		if (health)
		{
			int lives = health->GetLives();
			if (lives == 0)
			{
				gameObject.lock()->SetDelete(true);
			}
		}
	}
}

void Enemies::PookaComponent::Render()
{

}

void Enemies::PookaComponent::NextStage()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		switch (m_Stage)
		{
		case 1:
			gameObject.lock()->SetTexture("PookaFirstHit.png");
			break;
		case 2:
			gameObject.lock()->SetTexture("PookaSecondHit.png");
			break;
		case 3:
			gameObject.lock()->SetTexture("PookaThirdHit.png");
			break;
		default:
			break;
		}
		m_Stage++;
	}
}

void Enemies::PookaComponent::ResetStage()
{
	m_Stage = 0;
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		gameObject.lock()->SetTexture("Pooka.png");
	}
}
