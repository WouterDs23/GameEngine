#include "MiniginPCH.h"
#include "ConnectionComponent.h"
#include "GameObject.h"

void dae::NodeComponent::AddConnection(std::weak_ptr<GameObject> obj)
{
	{
		for (auto comps : m_Connections)
		{
			if (comps.lock() == obj.lock())
			{
				return;
			}
		}
		auto connection = GetGameObject().lock()->GetComponent<ConnectionComponent>();
		if (connection.lock())
		{
			m_Connections.push_back(obj);
			connection.lock()->SetStartNode(GetGameObject().lock());
			connection.lock()->SetEndNode(obj);
		}
			
	}
}

void dae::NodeComponent::ResetCosts()
{
	{
		for (auto conn : m_Connections)
		{
			if (conn.lock())
			{
				auto connection = conn.lock()->GetComponent<ConnectionComponent>();
				if (connection.lock())
				{
					connection.lock()->ResetCosts();
				}
			}
			
		}
	}
}

void dae::ConnectionComponent::CalculateCost(std::weak_ptr<GameObject> start, std::weak_ptr<GameObject> end)
{
	float currentGCost = 0;
	auto head = GetHeadConnection().lock();
	auto headConn = head->GetComponent<ConnectionComponent>();
	if (head && headConn.lock())
		currentGCost = headConn.lock()->GetGCost();

	auto parentPos = start.lock()->GetTransform().GetPosition();
	if (head && headConn.lock())
		parentPos = headConn.lock()->GetStartNode().lock()->GetTransform().GetPosition();
	
	auto tempV = DistanceBetween2Objects(GetEndNode().lock()->GetTransform().GetPosition(), parentPos);
	float gCost = tempV.x + tempV.y;
	SetGCost(currentGCost + gCost);
	
	tempV = DistanceBetween2Objects(GetEndNode().lock()->GetTransform().GetPosition(), end.lock()->GetTransform().GetPosition());
	float hCost = tempV.x + tempV.y;
	SetHCost(hCost);
}
