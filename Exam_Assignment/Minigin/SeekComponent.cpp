#include "MiniginPCH.h"
#include "SeekComponent.h"
#include "GameObject.h"
#include "../DigDug/GhostComponent.h"
#include "MoveComponent.h"
#include "../DigDug/CharacterComponent.h"
#include "CollisionComponent.h"
#include <algorithm>
#include <map>
#include <limits>
#include "ConnectionComponent.h"
#include "AIComponent.h"

dae::SeekComponent::SeekComponent()
{
}


dae::SeekComponent::~SeekComponent()
{
}

void dae::SeekComponent::Initialize()
{
}

void dae::SeekComponent::Update()
{
	auto actor = GetGameObject().lock();
	auto target = m_Target.lock();
	if (actor && target)
	{
		const auto ghostComp = actor->GetComponent<GhostComponent>().lock();
		if (ghostComp)
		{
			if (ghostComp->GetInGhostForm())
			{
				auto move = actor->GetComponent<MoveComponent>().lock();
				auto linearVel = target->GetTransform().GetPosition() - actor->GetTransform().GetPosition();
				Normalize(linearVel);
				move->MoveObject(linearVel.x, linearVel.y);
				return;
			}

		}

		auto path = FindPath();
		if (path.size() > 2)
		{
			target = path.back();
		}		
		auto move = actor->GetComponent<MoveComponent>().lock();
		auto linearVel = target->GetTransform().GetPosition() - actor->GetTransform().GetPosition();
		auto dist = DistanceBetween2Objects(target->GetTransform().GetPosition(), actor->GetTransform().GetPosition());
		if (dist.x <= 0.5 && dist.y <= 0.5)
		{
			return;
		}
		Normalize(linearVel);
		move->MoveObject(linearVel.x, linearVel.y);
		return;
	}
}

void dae::SeekComponent::Render()
{
}

std::vector<std::shared_ptr<dae::GameObject>> dae::SeekComponent::FindPath()
{
	std::vector<std::shared_ptr<dae::GameObject>> openList;
	std::vector<std::shared_ptr<dae::GameObject>> closedList;
	std::vector<std::shared_ptr<dae::GameObject>> actionList;
	std::weak_ptr<dae::GameObject> pCurrentNode{};
	std::weak_ptr<dae::GameObject> pObjective{};
	std::weak_ptr<dae::GameObject> pStartObjective{};
	auto actor = GetGameObject().lock();
	const auto target = m_Target.lock();
	if (actor && target)
	{
		std::vector<std::shared_ptr<dae::GameObject>> obstacles{};
		if (actor->GetComponent<dae::CharacterComponent>().lock())
		{
			obstacles = actor->GetComponent<dae::CharacterComponent>().lock()->GetObstacles();
		}
		if (actor->GetComponent<dae::AIComponent>().lock())
		{
			obstacles = actor->GetComponent<dae::AIComponent>().lock()->GetObstacles();
		}
		glm::vec3 distance{};
		glm::vec3 distanceStart{};
		for (auto obs : obstacles)
		{
			auto collisionComp = obs->GetComponent<CollisionComponent>().lock();
			auto conn = obs->GetComponent<ConnectionComponent>().lock();
			if (conn)
			{
				conn->SetHeadConnection(std::shared_ptr<dae::GameObject>());
				conn->ResetCosts();
			}
			if (collisionComp)
			{
				if (!collisionComp->GetIsObstacle())
				{
					if (!pObjective.lock())
					{
						pObjective = obs;
						distance = DistanceBetween2Objects(pObjective.lock()->GetTransform().GetMiddlePosition(), target->GetTransform().GetMiddlePosition());
						continue;
					}
					if (!pStartObjective.lock())
					{
						pStartObjective = obs;
						distanceStart = DistanceBetween2Objects(pStartObjective.lock()->GetTransform().GetMiddlePosition(), actor->GetTransform().GetMiddlePosition());
						continue;
					}

					const auto tempDistance = DistanceBetween2Objects(obs->GetTransform().GetMiddlePosition(), target->GetTransform().GetMiddlePosition());
					const auto tempDistanceStart = DistanceBetween2Objects(obs->GetTransform().GetMiddlePosition(), actor->GetTransform().GetMiddlePosition());
					if (tempDistance.x <= distance.x && tempDistance.y <= distance.y)
					{
						pObjective = obs;
						distance = tempDistance;
					}
					if (tempDistanceStart.x <= distanceStart.x && tempDistanceStart.y <= distanceStart.y)
					{
						pStartObjective = obs;
						distanceStart = tempDistanceStart;
					}
					continue;
				}
			}
		}
		if (pStartObjective.lock()->GetComponent<NodeComponent>().lock())
		{
			auto connections = pStartObjective.lock()->GetComponent<NodeComponent>().lock()->GetConnections();
			for (auto conn : connections)
			{
				auto connection = conn.lock()->GetComponent<ConnectionComponent>();
				if (connection.lock())
				{
					connection.lock()->CalculateCost(pStartObjective.lock(), pObjective.lock());
					openList.push_back(conn.lock());
				}
			}
		}

		while (!openList.empty())
		{
			float smallest = std::numeric_limits<float>::infinity();
			for (auto open : openList)
			{
				auto cost = open->GetComponent<ConnectionComponent>().lock();
				if (cost->GetFCost() < smallest)
				{
					smallest = cost->GetFCost();
					pCurrentNode = open;
				}
			}

			openList.erase(remove(openList.begin(), openList.end(), pCurrentNode.lock()));
			closedList.push_back(pCurrentNode.lock());
			auto CurrentNode = pCurrentNode.lock()->GetComponent<NodeComponent>();
			auto newNode = pCurrentNode.lock()->GetComponent<NodeComponent>();
			auto CurrentConnection = pCurrentNode.lock()->GetComponent<ConnectionComponent>();
			auto newObj = CurrentConnection.lock()->GetEndNode().lock();
			if (newObj)
			{
				newNode = newObj->GetComponent<NodeComponent>();
			}

			std::vector<std::weak_ptr<dae::GameObject>> vpConnections = newNode.lock()->GetConnections();

			std::vector<std::weak_ptr<dae::GameObject>>::iterator result = std::find_if(vpConnections.begin(), vpConnections.end(), [&pObjective](std::weak_ptr<dae::GameObject> a) {
				return a.lock() == pObjective.lock(); });

			if (result != vpConnections.end())
			{
				auto conn = pObjective.lock()->GetComponent<ConnectionComponent>().lock();
				conn->SetHeadConnection(pCurrentNode);
				pCurrentNode = pObjective;
				openList.clear();
				break;
			}

			for (auto pG : vpConnections)
			{
				auto resultClosed = std::find(closedList.begin(), closedList.end(), pG.lock());
				if (resultClosed != closedList.end())
				{
					continue;
				}
				resultClosed = std::find(openList.begin(), openList.end(), pG.lock());
				if (resultClosed != openList.end())
				{
					continue;
				}
				auto conn = pG.lock()->GetComponent<ConnectionComponent>().lock();
				conn->SetHeadConnection(pCurrentNode);
				conn->CalculateCost(pStartObjective.lock(), pObjective.lock());
				auto collisionComp = pG.lock()->GetComponent<CollisionComponent>().lock();
				if (collisionComp)
				{
					if (!collisionComp->GetIsObstacle())
					{
						openList.push_back(pG.lock());
					}
				}
			}
		}
		actionList.push_back(pObjective.lock());
		if (pCurrentNode.lock())
		{
			auto conn = pCurrentNode.lock()->GetComponent<ConnectionComponent>().lock();
			while (conn->GetHeadConnection().lock())
			{
				conn = pCurrentNode.lock()->GetComponent<ConnectionComponent>().lock();
				pCurrentNode = conn->GetHeadConnection();
				if (pCurrentNode.lock())
				{
					actionList.push_back(pCurrentNode.lock());
				}
			}
		}
		//actionList.push_back(pStartObjective.lock());
	}
	return actionList;
}
