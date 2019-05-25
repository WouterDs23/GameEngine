#include "MiniginPCH.h"
#include "GhostComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Texture2D.h"

Enemies::GhostComponent::GhostComponent(std::string nonGhostTexture) :
	m_InGhostForm(false),
	m_NonGhostTexture(nonGhostTexture)
{
}


Enemies::GhostComponent::~GhostComponent()
{
}

void Enemies::GhostComponent::Initialize()
{
}

void Enemies::GhostComponent::Update()
{
}

void Enemies::GhostComponent::Render()
{
}

void Enemies::GhostComponent::EnableGhostMode(bool enable)
{
	auto actor = GetGameObject().lock();
	if (actor)
	{
		auto collision = actor->GetComponent<dae::CollisionComponent>().lock();
		if (collision)
		{
			collision->EnableGhost(enable);
			m_InGhostForm = enable;
			if (m_InGhostForm)
			{
				actor->SetTexture("Ghost.png");
				return;
			}
			else
			{
				actor->SetTexture(m_NonGhostTexture);
				return;
			}
		}
	}
}
