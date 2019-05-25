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
		m_Lives--;

		if (player && m_DamagedState)
		{
			player->SetState(m_DamagedState);
		}
		auto pooka = player->GetComponent<Enemies::PookaComponent>().lock();
		if (pooka)
		{
			pooka->NextStage();
			return;
		}
		auto charact = player->GetComponent<DigDug::MainCharComponent>().lock();
		if (charact)
		{			
			charact->ResetLevel();
			return;
		}
	}
	
}
