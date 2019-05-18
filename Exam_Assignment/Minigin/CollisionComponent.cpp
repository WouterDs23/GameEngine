#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "../DigDug/GhostComponent.h"

dae::CollisionComponent::CollisionComponent()
	: m_IsObstacle(false),
	m_InGhostForm(false),
	m_Init(false)
{
}

dae::CollisionComponent::CollisionComponent(Transform size)
	:m_IsObstacle(false),
	m_InGhostForm(false),
	m_Transform(size),
	m_Init(true)
{

}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Initialize()
{
	if (!m_Init)
	{
		if (GetGameObject().lock())
		{
			m_Transform = GetGameObject().lock()->GetTransform();
		}		
	}
	else
	{
		m_Transform.SetPosition(GetGameObject().lock()->GetTransform().GetPosition().x, GetGameObject().lock()->GetTransform().GetPosition().y, GetGameObject().lock()->GetTransform().GetPosition().z);
	}
}

void dae::CollisionComponent::Update()
{
	if (GetGameObject().lock())
	{
		m_Transform.SetPosition(GetGameObject().lock()->GetTransform().GetPosition().x, GetGameObject().lock()->GetTransform().GetPosition().y, GetGameObject().lock()->GetTransform().GetPosition().z);
	}
}

void dae::CollisionComponent::Render()
{

}

const bool dae::CollisionComponent::CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other, float offset)
{
	if (other.lock() && !m_InGhostForm)
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && compTest->GetIsObstacle())
		{
			auto transO = compTest->GetTransform().GetPosition();
			auto sizeO = compTest->GetTransform().GetSize();

			auto tranS = m_Transform.GetPosition();
			auto sizeS = m_Transform.GetSize();
			auto middleS = m_Transform.GetMiddlePosition();

			if (transO.y + sizeO.y < tranS.y + offset ||(tranS.y + sizeS.y)+ offset < transO.y)
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

const bool dae::CollisionComponent::CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other, float offset)
{
	if (other.lock() && !m_InGhostForm)
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && compTest->GetIsObstacle())
		{
			auto transO = compTest->GetTransform().GetPosition();
			auto sizeO = compTest->GetTransform().GetSize();

			auto tranS = m_Transform.GetPosition();
			auto sizeS = m_Transform.GetSize();
			auto middleS = m_Transform.GetMiddlePosition();

			if (offset+(tranS.x + sizeS.x) < transO.x || transO.x + sizeO.x < tranS.x + offset)
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

const bool dae::CollisionComponent::CheckIfInObject(std::weak_ptr<dae::GameObject> other)
{

	if (other.lock())
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest)
		{
			auto transO = compTest->GetTransform().GetPosition();
			auto sizeO = compTest->GetTransform().GetSize();

			auto tranS = m_Transform.GetPosition();
			auto sizeS = m_Transform.GetSize();
			auto middleS = m_Transform.GetMiddlePosition();
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

void dae::CollisionComponent::EnableGhost(bool enable)
{
	auto actor = GetGameObject().lock();
	if (actor)
	{
		auto ghost = actor->GetComponent<GhostComponent>().lock();
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
