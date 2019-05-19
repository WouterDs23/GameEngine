#include "MiniginPCH.h"
#include "GunComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "CharacterBehaviour.h"
#include "CharacterComponent.h"
#include "PookaBehaviour.h"

GunComponent::GunComponent(std::shared_ptr<dae::GameObject> gun, std::weak_ptr<dae::GameObject> parent):
m_Gun(gun),
m_Parent(parent)
{
	
}

void GunComponent::Initialize()
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

void GunComponent::Update()
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

					move->SetSpeed(0, 0);
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
						if (col->CheckCollisionTopBottem(enemy,0,true) || col->CheckCollisionLeftRight(enemy, 0, true))
						{
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

				move->SetSpeed(0, 0);
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

void GunComponent::Render()
{
}

void GunComponent::Shoot(float x, float y)
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

void GunComponent::DoPump()
{
	if (m_Hit == true)
	{
		m_HitTimer = 0.f;
		auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
		auto character = m_Parent.lock()->GetComponent<dae::CharacterComponent>().lock();

		if (character && col)
		{
			auto enemies = character->GetEnemies();
			for (auto enemy : enemies)
			{
				if (col->CheckCollisionTopBottem(enemy, 0, true) || col->CheckCollisionLeftRight(enemy, 0, true))
				{
					
					/*if (enemy.lock())
					{
						auto state = enemy.lock()->GetState().lock();
						if (state)
						{
							std::string currentState = typeid(state.operator*()).name();
							if (currentState == "class PookaHitState")
							{
								std::weak_ptr<PookaHitState> pooka =state;
							}
						}
					}*/
				}

			}
		}
	}
}
