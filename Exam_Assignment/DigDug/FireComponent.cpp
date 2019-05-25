#include "MiniginPCH.h"
#include "FireComponent.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "FygarBehaviourh.h"
#include "HealthComponent.h"

Enemies::FireComponent::FireComponent(float collisionSizeX, float collisionSizeY,std::shared_ptr<dae::GameObject> firegun, std::weak_ptr<dae::GameObject> parent) :
	m_FireGun(firegun),
	m_Parent(parent),
	m_CollisionSize(collisionSizeX,collisionSizeY,0)
{
}

void Enemies::FireComponent::Initialize()
{
	if (m_FireGun.lock())
	{
		m_FireGun.lock()->SetDoRenderAndUpdate(false);
		if (m_Parent.lock())
		{
			m_FireGun.lock()->SetPosition(m_Parent.lock()->GetTransform().GetPosition().x, m_Parent.lock()->GetTransform().GetPosition().y);
		}
	}
}

void Enemies::FireComponent::Update()
{
	if (m_CanFire)
	{
		if (m_FireGun.lock() && m_FireGun.lock()->GetDoRenderAndUpdate())
		{
			m_Timer += GameLifeSpan::deltaTime;
			if (m_Timer >= 0.5f)
			{
				m_Timer = 0.f;
				auto move = m_FireGun.lock()->GetComponent<dae::MoveComponent>().lock();
				auto col = m_FireGun.lock()->GetComponent<dae::CollisionComponent>().lock();
				if (move && col)
				{
					if (m_FireGun.lock() && m_Parent.lock())
					{
						m_FireGun.lock()->SetDoRenderAndUpdate(false);
						m_Timer = 0;
					}
				}
			}
			else
			{
				auto move = m_FireGun.lock()->GetComponent<dae::MoveComponent>().lock();
				auto col = m_FireGun.lock()->GetComponent<dae::CollisionComponent>().lock();
				auto AI = m_Parent.lock()->GetComponent<dae::AIComponent>().lock();
				auto moveParent = m_Parent.lock()->GetComponent<dae::MoveComponent>().lock();
				if (move && col && moveParent)
				{
					move->MoveObject(moveParent->GetPrevSpeed().x, moveParent->GetPrevSpeed().y);
				}
				if (AI && col)
				{
					auto enemy = AI->GetEnemy();
					if (col->CheckCollisionTopBottem(enemy, 0, 0, true) || col->CheckCollisionLeftRight(enemy, 0, 0, true))
					{
						auto health = enemy.lock()->GetComponent<HealthComponent>();
						if (health.lock())
						{
							health.lock()->TakeDamage();
						}
						if (move && col)
						{
							if (m_FireGun.lock() && m_Parent.lock())
							{
								m_FireGun.lock()->SetDoRenderAndUpdate(false);
								m_Timer = 0;
							}
						}
					}
				}
			}

		}
		else if (m_Parent.lock())
		{
			auto AI = m_Parent.lock()->GetComponent<dae::AIComponent>();
			auto col = m_Parent.lock()->GetComponent<dae::CollisionComponent>();
			if (AI.lock() && col.lock())
			{
				if (col.lock()->CheckIfObjectInMe(m_CollisionSize, AI.lock()->GetEnemy()))
				{
					if (m_FireGun.lock() && !m_FireGun.lock()->GetDoRenderAndUpdate())
					{
						m_FireGun.lock()->SetDoRenderAndUpdate(true);
						if (m_Parent.lock())
						{
							m_Parent.lock()->SetState(std::make_shared<Fygar::ShootingState>());
							m_FireGun.lock()->SetPosition(m_Parent.lock()->GetTransform().GetPosition().x, m_Parent.lock()->GetTransform().GetPosition().y);
						}
					}
				}

			}
		}
	}
}

void Enemies::FireComponent::Render()
{

}
