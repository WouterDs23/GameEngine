#include "MiniginPCH.h"
#include "GunComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"

GunComponent::GunComponent(std::shared_ptr<dae::GameObject> gun):
m_Gun(gun)
{
	
}

void GunComponent::Initialize()
{
	if (m_Gun)
	{
		m_Gun->SetDoRenderAndUpdate(false);
	}
}

void GunComponent::Update()
{
	if (m_Shot)
	{
		m_Timer += GameLifeSpan::deltaTime;
		if (m_Timer >= 2.f)
		{
			m_Timer = 0.f;
			m_Shot = false;
			auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
			auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
			if (move && col)
			{
				
				move->SetSpeed(0, 0);
				if (m_Gun)
				{
					m_Gun->SetDoRenderAndUpdate(false);
				}
			}
		}
		else
		{
			
		}
	}
}

void GunComponent::Render()
{
}

void GunComponent::Shoot(glm::vec3 vel)
{
	if (m_Gun)
	{
		auto move = m_Gun->GetComponent<dae::MoveComponent>().lock();
		auto col = m_Gun->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			move->SetSpeed(vel.x, vel.y);
			m_Shot = true;
			m_Gun->SetDoRenderAndUpdate(true);
		}
	}
}
