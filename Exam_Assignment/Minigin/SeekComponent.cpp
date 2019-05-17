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
		target = path.back();
		auto move = actor->GetComponent<MoveComponent>().lock();
		auto linearVel = target->GetTransform().GetPosition() - actor->GetTransform().GetPosition();
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
	//std::vector<std::shared_ptr<dae::GameObject>> openList;
	//std::vector<std::shared_ptr<dae::GameObject>> closedList;
	std::vector<std::shared_ptr<dae::GameObject>> actionList;
	//std::weak_ptr<dae::GameObject> pCurrentNode{};
	//std::weak_ptr<dae::GameObject> pObjective{};
	//std::weak_ptr<dae::GameObject> pStartObjective{};
	//auto actor = GetGameObject().lock();
	//const auto target = m_Target.lock();
	//if (actor && target)
	//{
	//	auto obstacles = actor->GetComponent<dae::CharacterComponent>().lock()->GetObstacles();
	//	glm::vec3 distance{};
	//	glm::vec3 distanceStart{};
	//	for (auto obs : obstacles)
	//	{
	//		auto collisionComp = obs->GetComponent<CollisionComponent>().lock();
	//		auto conn = obs->GetComponent<ConnectionComponent>().lock();
	//		if (conn)
	//		{
	//			conn->SetHeadConnection(std::shared_ptr<dae::GameObject>());
	//			conn->ResetCosts();
	//		}
	//		if (collisionComp)
	//		{
	//			if (!collisionComp->GetIsObstacle())
	//			{
	//				if (!pObjective.lock())
	//				{
	//					pObjective = obs;
	//					distance = DistanceBetween2Objects(pObjective.lock()->GetTransform().GetMiddlePosition(), target->GetTransform().GetMiddlePosition());
	//					continue;
	//				}
	//				if (!pStartObjective.lock())
	//				{
	//					pStartObjective = obs;
	//					distanceStart = DistanceBetween2Objects(pStartObjective.lock()->GetTransform().GetMiddlePosition(), actor->GetTransform().GetMiddlePosition());
	//					continue;
	//				}

	//				const auto tempDistance = DistanceBetween2Objects(obs->GetTransform().GetMiddlePosition(), target->GetTransform().GetMiddlePosition());
	//				const auto tempDistanceStart = DistanceBetween2Objects(obs->GetTransform().GetMiddlePosition(), actor->GetTransform().GetMiddlePosition());
	//				if (tempDistance.x <= distance.x && tempDistance.y <= distance.y)
	//				{
	//					pObjective = obs;
	//					distance = tempDistance;
	//				}
	//				if (tempDistanceStart.x <= distanceStart.x && tempDistanceStart.y <= distanceStart.y)
	//				{
	//					pStartObjective = obs;
	//					distanceStart = tempDistanceStart;
	//				}
	//				continue;
	//			}
	//		}
	//	}
	//	distance = DistanceBetween2Objects(pObjective.lock()->GetTransform().GetMiddlePosition(), pStartObjective.lock()->GetTransform().GetMiddlePosition());
	//	for (std::shared_ptr<dae::GameObject> g : ConnectingObjects(obstacles, pStartObjective.lock()))
	//	{
	//		auto cost = g->GetComponent<ConnectionComponent>().lock();
	//		if (cost)
	//		{
	//			cost->CalculateCost(pStartObjective.lock(), pObjective.lock());
	//			auto collisionComp = g->GetComponent<CollisionComponent>().lock();
	//			if (collisionComp)
	//			{
	//				if (!collisionComp->GetIsObstacle())
	//				{
	//					openList.push_back(g);
	//				}
	//			}
	//		}
	//	}
	//	while (!openList.empty())
	//	{
	//		float smallest = std::numeric_limits<float>::infinity();
	//		for (auto open : openList)
	//		{
	//			auto cost = open->GetComponent<ConnectionComponent>().lock();
	//			if (cost->GetFCost() < smallest)
	//			{
	//				smallest = cost->GetFCost();
	//				pCurrentNode = open;
	//			}
	//		}

	//		openList.erase(remove(openList.begin(), openList.end(), pCurrentNode.lock()));
	//		closedList.push_back(pCurrentNode.lock());

	//		std::vector<std::shared_ptr<dae::GameObject>> vpConnections = ConnectingObjects(obstacles, pCurrentNode.lock());

	//		std::vector<std::shared_ptr<dae::GameObject>>::iterator result = std::find_if(vpConnections.begin(), vpConnections.end(), [&pObjective](std::shared_ptr<dae::GameObject> a) {
	//			return a == pObjective.lock(); });
	//		if (result != vpConnections.end())
	//		{
	//			auto conn = pObjective.lock()->GetComponent<ConnectionComponent>().lock();
	//			conn->SetHeadConnection(pCurrentNode);
	//			pCurrentNode = pObjective;
	//			openList.clear();
	//			break;
	//		}
	//		for (auto pG : vpConnections)
	//		{
	//			auto resultClosed = std::find(closedList.begin(), closedList.end(), pG);
	//			if (resultClosed != closedList.end())
	//			{
	//				continue;
	//			}
	//			resultClosed = std::find(openList.begin(), openList.end(), pG);
	//			if (resultClosed != openList.end())
	//			{
	//				continue;
	//			}
	//			auto conn = pG->GetComponent<ConnectionComponent>().lock();
	//			conn->SetHeadConnection(pCurrentNode);
	//			conn->CalculateCost(pStartObjective.lock(), pObjective.lock());
	//			auto collisionComp = pG->GetComponent<CollisionComponent>().lock();
	//			if (collisionComp)
	//			{
	//				if (!collisionComp->GetIsObstacle())
	//				{
	//					openList.push_back(pG);
	//				}
	//			}
	//		}
	//	}
	//	actionList.push_back(pObjective.lock());
	//	auto conn = pCurrentNode.lock()->GetComponent<ConnectionComponent>().lock();
	//	while (conn->GetHeadConnection().lock())
	//	{
	//		conn = pCurrentNode.lock()->GetComponent<ConnectionComponent>().lock();
	//		pCurrentNode = conn->GetHeadConnection();
	//		if (pCurrentNode.lock())
	//		{
	//			actionList.push_back(pCurrentNode.lock());
	//		}
	//	}
	//	//actionList.push_back(pStartObjective.lock());
	//}
	return actionList;
}
