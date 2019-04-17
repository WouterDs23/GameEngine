#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"

dae::CollisionComponent::CollisionComponent():m_IsObstacle(false)
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

const bool dae::CollisionComponent::CheckCollisionTopBottem(std::weak_ptr<dae::GameObject> other)
{
	if (other.lock())
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && compTest->GetIsObstacle())
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto tranS = GetGameObject().lock()->GetTransform().GetPosition();
			auto sizeS = GetGameObject().lock()->GetTransform().GetSize();
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();

			if (transO.y + sizeO.y < tranS.y || tranS.y + sizeS.y < transO.y)
			{
				return false;
			}

			if (transO.x + sizeO.x > middleS.x && middleS.x > transO.x)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

const bool dae::CollisionComponent::CheckCollisionLeftRight(std::weak_ptr<dae::GameObject> other)
{
	if (other.lock())
	{
		auto compTest = other.lock()->GetComponent<CollisionComponent>().lock();
		if (compTest && compTest->GetIsObstacle())
		{
			auto transO = other.lock()->GetTransform().GetPosition();
			auto sizeO = other.lock()->GetTransform().GetSize();

			auto tranS = GetGameObject().lock()->GetTransform().GetPosition();
			auto sizeS = GetGameObject().lock()->GetTransform().GetSize();
			auto middleS = GetGameObject().lock()->GetTransform().GetMiddlePosition();

			if (tranS.x + sizeS.x < transO.x || transO.x + sizeO.x < tranS.x)
			{
				return false;
			}

			if (transO.y + sizeO.y > middleS.y && middleS.y > transO.y)
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
