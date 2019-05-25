#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "../DigDug/GhostComponent.h"
#include "../DigDug/HealthComponent.h"

dae::CollisionComponent::CollisionComponent()
	: m_IsObstacle(false),
	m_InGhostForm(false)
{
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Initialize()
{
	
}

void dae::CollisionComponent::Update()
{

}

void dae::CollisionComponent::Render()
{

}

bool dae::CollisionComponent::CheckCollisionTopBottem (std::weak_ptr<dae::GameObject> other, float offsetX, float offsetY, bool overrideGhost)const
{
	if (other.lock() && (!m_InGhostForm || overrideGhost) && m_doCollision)
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && (compTest->GetIsObstacle() || overrideGhost))
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto tranS = GetGameObject().lock()->GetTransform().GetPosition();
			auto sizeS = GetGameObject().lock()->GetTransform().GetSize();
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();
			middleS.x += offsetX;
			middleS.y += offsetY;

			if (transO.y + sizeO.y < tranS.y + offsetY ||(tranS.y + sizeS.y)+ offsetY < transO.y)
			{
				return false;
			}

			if (transO.x + sizeO.x > middleS.x && middleS.x > transO.x)
			{
				return true;
			}
			if (transO.x + sizeO.x > middleS.x + ((sizeS.x/2.f)- (sizeS.x / 10)) && middleS.x + ((sizeS.x / 2.f) - (sizeS.x / 10)) > transO.x)
			{
				return true;
			}
			if (transO.x + sizeO.x > middleS.x - ((sizeS.x / 2.f) - (sizeS.x/10)) && middleS.x -((sizeS.x / 2.f) - (sizeS.x / 10)) > transO.x)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool dae::CollisionComponent::CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other, float offsetX, float offsetY ,bool overrideGhost)const
{
	if (other.lock() && (!m_InGhostForm || overrideGhost) && m_doCollision)
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && (compTest->GetIsObstacle()))
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto tranS = GetGameObject().lock()->GetTransform().GetPosition();
			auto sizeS = GetGameObject().lock()->GetTransform().GetSize();
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();

			middleS.x += offsetX;
			middleS.y += offsetY;

			if (offsetX +(tranS.x + sizeS.x) < transO.x || transO.x + sizeO.x < tranS.x + offsetX)
			{
				return false;
			}

			if (transO.y + sizeO.y > middleS.y && middleS.y > transO.y)
			{
				return true;
			}
			if (transO.y + sizeO.y > middleS.y + ((sizeS.y / 2.f) - (sizeS.y / 10)) && middleS.y + ((sizeS.y / 2.f) - (sizeS.y / 10)) > transO.y)
			{
				return true;
			}
			if (transO.y + sizeO.y > middleS.y - ((sizeS.y / 2.f) - (sizeS.y / 10)) && middleS.y - ((sizeS.y / 2.f) - (sizeS.y / 10)) > transO.y)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool dae::CollisionComponent::CheckIfInObject(std::weak_ptr<dae::GameObject> other)const
{

	if (other.lock())
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest)
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto tranS = GetGameObject().lock()->GetTransform().GetPosition();
			auto sizeS = GetGameObject().lock()->GetTransform().GetSize();
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();
			if (transO.x - 2.f < tranS.x)
			{
				if (transO.x + sizeO.x + 2.f > tranS.x + sizeS.x)
				{
					if (transO.y - 2.f < tranS.y)
					{
						if (transO.y + sizeO.y + 2.f > tranS.y + sizeS.y)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool dae::CollisionComponent::CheckIfObjectInMe(glm::vec3 size, std::weak_ptr<dae::GameObject> other) const
{
	if (other.lock())
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest)
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto sizeS = size;
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();
			if (transO.x - 2.f > middleS.x - sizeS.x)
			{
				if (transO.x + sizeO.x + 2.f < middleS.x + sizeS.x)
				{
					if (transO.y - 2.f > middleS.y - sizeS.y)
					{
						if (transO.y + sizeO.y + 2.f < middleS.y + sizeS.y)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void dae::CollisionComponent::EnableGhost(bool enable)
{
	auto actor = GetGameObject().lock();
	if (actor)
	{
		auto ghost = actor->GetComponent<Enemies::GhostComponent>().lock();
		if (ghost)
		{
			if (enable)
			{
				m_InGhostForm = true;
			}
			else
			{
				m_InGhostForm = false;
			}
			
		}
	}
}
