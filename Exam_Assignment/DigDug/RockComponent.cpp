#include "MiniginPCH.h"
#include "RockComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"
#include "EnemyBehaviour.h"
#include "SeekComponent.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"

Environment::RockComponent::RockComponent()
{

}

void Environment::RockComponent::Initialize()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		gameObj->AddComponent(std::make_shared<dae::CollisionComponent>());
		gameObj->AddComponent(std::make_shared<dae::MoveComponent>());
	}
}

void Environment::RockComponent::Update()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		auto col = gameObj->GetComponent<dae::CollisionComponent>().lock();
		auto move = gameObj->GetComponent<dae::MoveComponent>().lock();
		if (col && move)
		{
			if (m_AvoidingCollision)
			{
				m_Time += GameLifeSpan::deltaTime;
				if (m_Time < 0.3f)
				{
					return;
				}
				move->MoveObject(0, 1);
				move->SetSpeed(2.f);
				for (auto enemy : m_Enemies)
				{
					if (col->CheckCollisionTopBottem(enemy, 0, 0, true))
					{
						auto health = enemy.lock()->GetComponent<HealthComponent>();
						if (health.lock())
						{
							health.lock()->InstaKillDamage();
						}
						Notify(gameObj);
						gameObj->SetDelete(true);
					}
				}
				for (auto obs : m_Obstacles)
				{
					if (col->CheckCollisionTopBottem(obs))
					{
						gameObj->SetDelete(true);
					}
				}
			}
			else 
			{
				unsigned int size{};
				for (auto obs : m_Obstacles)
				{
					if (!col->CheckCollisionTopBottem(obs, 0,10))
					{
						size++;
					}
				}
				if (size == m_Obstacles.size() && size != 0)
				{
					m_AvoidingCollision = true;
				}
			}
			
		}
	}
}

void Environment::RockComponent::Render()
{

}
