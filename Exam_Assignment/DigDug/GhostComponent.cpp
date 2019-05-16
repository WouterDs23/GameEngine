#include "MiniginPCH.h"
#include "GhostComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Texture2D.h"

dae::GhostComponent::GhostComponent():
	m_InGhostForm(false)
{
}


dae::GhostComponent::~GhostComponent()
{
}

void dae::GhostComponent::Initialize()
{
}

void dae::GhostComponent::Update()
{
}

void dae::GhostComponent::Render()
{
}

void dae::GhostComponent::EnableGhostMode(bool enable)
{
	auto actor = GetGameObject().lock();
	if (actor)
	{
		auto collision = actor->GetComponent<CollisionComponent>().lock();
		if (collision)
		{
			collision->EnableGhost(enable);
			m_InGhostForm = enable;
			if (m_InGhostForm)
			{
				actor->SetTexture("dotGhost.png");
				return;
			}
			else
			{
				actor->SetTexture("dot.png");
				return;
			}
		}
	}
}
