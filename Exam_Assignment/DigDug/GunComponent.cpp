#include "MiniginPCH.h"
#include "GunComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "CharacterBehaviour.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"

DigDug::GunComponent::GunComponent(std::shared_ptr<dae::GameObject> gun, std::weak_ptr<dae::GameObject> parent):
m_Gun(gun),
m_Parent(parent)
{
	
}

void DigDug::GunComponent::Initialize()
{
	if (m_Gun)
	{
		m_Gun->SetDoRenderAndUpdate(false);
		if (m_Parent.lock())
		{
			m_Gun->SetPosition(m_Parent.lock()->GetTransform().GetPosition().x, m_Parent.lock()->GetTransform().GetPosition().y);
		}
	}
}

void DigDug::GunComponent::Update()
{
	if (m_Shot)
	{
		if (!m_Hit)
		{
			m_Timer += GameLifeSpan::deltaTime;
			if (m_Timer >= 0.5f)
			{
				m_Timer = 0.f;
				m_Shot = false;
				auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
				auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
				if (move && col)
				{

					if (m_Gun && m_Parent.lock())
					{
						m_Gun->SetDoRenderAndUpdate(false);
						m_Parent.lock()->SetState(std::make_shared<IdleState>());
						m_HitTimer = 0;
						m_Timer = 0;
						m_Hit = false;
					}
				}
			}
			else
			{

				auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
				auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
				auto character = m_Parent.lock()->GetComponent<dae::CharacterComponent>().lock();
				if (move && col)
				{
					move->MoveObject(m_xSpeed, m_ySpeed);
				}
				if (character && col)
				{
					auto enemies = character->GetEnemies();
					for (auto enemy : enemies)
					{
						if (col->CheckCollisionTopBottem(enemy, 0, 0, true) || col->CheckCollisionLeftRight(enemy, 0, 0, true))
						{
							auto health = enemy.lock()->GetComponent<HealthComponent>();
							if (health.lock())
							{
								health.lock()->TakeDamage();
							}
							m_Hit = true;
							m_HitTimer = 0.f;
							m_Timer = 0.f;
						}
						
					}
				}
			}
			return;
		}
		m_HitTimer += GameLifeSpan::deltaTime;
		if (m_HitTimer >= 0.5f)
		{
			auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
			auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
			if (move && col)
			{
				if (m_Gun)
				{
					m_Gun->SetDoRenderAndUpdate(false);
					m_Parent.lock()->SetState(std::make_shared<IdleState>());
					m_HitTimer = 0;
					m_Timer = 0;
					m_Hit = false;
				}
			}
		}
	}
}

void DigDug::GunComponent::Render()
{
}

void DigDug::GunComponent::Shoot(float x, float y)
{
	if (m_Gun)
	{
		if (m_Parent.lock())
		{
			m_Gun->SetPosition(m_Parent.lock()->GetTransform().GetPosition().x, m_Parent.lock()->GetTransform().GetPosition().y);
		}
		auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
		auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			m_xSpeed = x *2;
			m_ySpeed = y *2;
			move->MoveObject(m_xSpeed, m_ySpeed);
			m_Shot = true;
			m_Gun->SetDoRenderAndUpdate(true);
		}
	}
}

void DigDug::GunComponent::DoPump()
{
	if (m_Hit == true)
	{
		auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
		auto character = m_Parent.lock()->GetComponent<dae::CharacterComponent>().lock();

		if (character && col)
		{
			auto enemies = character->GetEnemies();
			for (auto enemy : enemies)
			{
				if (col->CheckCollisionTopBottem(enemy, 0, 0, true) || col->CheckCollisionLeftRight(enemy, 0, 0, true))
				{
					auto health = enemy.lock()->GetComponent<HealthComponent>();
					if (health.lock())
					{
						if (m_HitTimer >=0.1f)
						{
							m_HitTimer = 0.f;
							health.lock()->TakeDamage();
						}						
					}
				}

			}
		}
	}
}
