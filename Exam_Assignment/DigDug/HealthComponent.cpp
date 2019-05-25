#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "PookaComponent.h"
#include "MainCharComponent.h"
#include "FygarComponent.h"

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
		auto fygar = player->GetComponent<Enemies::FygarComponent>().lock();
		if (pooka)
		{
			pooka->NextStage();
			return;
		}
		if (fygar)
		{
			fygar->NextStage();
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

void HealthComponent::InstaKillDamage()
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
		auto fygar = player->GetComponent<Enemies::FygarComponent>().lock();
		if (pooka || fygar)
		{
			player->SetDelete(true);
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
