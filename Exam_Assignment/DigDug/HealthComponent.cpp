#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "PookaComponent.h"
#include "MainCharComponent.h"

void HealthComponent::Initialize()
{
}

void HealthComponent::Update()
{

}

void HealthComponent::Render()
{

}

void HealthComponent::TakeDamage()
{
	auto player = GetGameObject().lock();
	if (player)
	{
		auto pooka = player->GetComponent<PookaComponent>().lock();
		if (pooka)
		{
			m_Lives--;
			pooka->NextStage();

			if (player && m_DamagedState)
			{
				player->SetState(m_DamagedState);
			}
			return;
		}
		auto charact = player->GetComponent<MainCharComponent>().lock();
		if (charact)
		{
			if (player->GetState().lock() != m_DamagedState)
			{
				m_Lives--;

				if (player && m_DamagedState)
				{
					player->SetState(m_DamagedState);
				}
				charact->ResetLevel();
			}
		}
	}
	
}
