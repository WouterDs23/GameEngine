#include "MiniginPCH.h"
#include "ConnectionComponent.h"
#include "GameObject.h"

dae::ConnectionComponent::ConnectionComponent()
{
}

void dae::ConnectionComponent::Initialize()
{
}

void dae::ConnectionComponent::Update()
{
}

void dae::ConnectionComponent::Render()
{
}

void dae::ConnectionComponent::CalculateCost(const std::shared_ptr<GameObject> start, const std::shared_ptr<GameObject> end)
{
	float currentGCost = 0;
	if (m_pHeadConnection.lock())
	{
		auto conn = m_pHeadConnection.lock()->GetComponent<ConnectionComponent>();
		if (conn.lock())
		{
			currentGCost = conn.lock()->GetGCost();
		}
		
	}
	auto parentPos = start->GetTransform().GetMiddlePosition();
	if (m_pHeadConnection.lock())
	{
		parentPos = m_pHeadConnection.lock()->GetTransform().GetMiddlePosition();
	}

	const auto object = GetGameObject().lock();
	auto tempV = DistanceBetween2Objects(object->GetTransform().GetMiddlePosition(), parentPos);
	const float gCost = tempV.x + tempV.y;
	m_GCost = currentGCost + gCost;

	tempV = DistanceBetween2Objects(object->GetTransform().GetMiddlePosition(), end->GetTransform().GetMiddlePosition());
	const float hCost = tempV.x + tempV.y;
	m_HCost = hCost;	
}
