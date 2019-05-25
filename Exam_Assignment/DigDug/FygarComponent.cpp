#include "MiniginPCH.h"
#include "FygarComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"
#include "SeekComponent.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "EnemyBehaviour.h"
#include "MoveComponent.h"
#include "FireComponent.h"

Enemies::FygarComponent::FygarComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles, std::shared_ptr<dae::GameObject> fireGun):
m_Obstacles(obstacles),
m_FireGun(fireGun)
{

}

void Enemies::FygarComponent::Initialize()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		gameObj->AddComponent(std::make_shared<dae::AIComponent>());
		gameObj->AddComponent(std::make_shared<dae::WanderComponent>(true));
		gameObj->AddComponent(std::make_shared<dae::SeekComponent>());
		gameObj->AddComponent(std::make_shared<Enemies::GhostComponent>("Fygar.png"));
		gameObj->AddComponent(std::make_shared<Enemies::FireComponent>(gameObj->GetTransform().GetSize().x*2.5f, gameObj->GetTransform().GetSize().y * 2.5f,m_FireGun, gameObj));
		gameObj->AddComponent(std::make_shared<HealthComponent>(4));
		gameObj->GetComponent<dae::AIComponent>().lock()->SetObstacles(m_Obstacles);
		gameObj->GetComponent<HealthComponent>().lock()->SetState(std::make_shared<Enemies::EnemyHitState>());
		gameObj->SetState(std::make_shared<Enemies::WanderState>());
		gameObj->SetTexture("Fygar.png");
	}
	if (m_FireGun)
	{
		m_FireGun->AddComponent(std::make_shared<dae::MoveComponent>(2.f));
		m_FireGun->AddComponent(std::make_shared<dae::CollisionComponent>());
		m_FireGun->SetTexture("Fire.png");
	}
	
}

void Enemies::FygarComponent::Update()
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

void Enemies::FygarComponent::Render()
{

}

void Enemies::FygarComponent::NextStage()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		switch (m_Stage)
		{
		case 1:
			gameObject.lock()->SetTexture("FygarFirstHit.png");
			break;
		case 2:
			gameObject.lock()->SetTexture("FygarSecondHit.png");
			break;
		case 3:
			gameObject.lock()->SetTexture("FygarThirdHit.png");
			break;
		default:
			break;
		}
		m_Stage++;
	}
}

void Enemies::FygarComponent::ResetStage()
{
	m_Stage = 0;
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		gameObject.lock()->SetTexture("Fygar.png");
	}
}
