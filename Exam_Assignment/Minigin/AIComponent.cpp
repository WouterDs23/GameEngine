#include "MiniginPCH.h"
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "InputManager.h"

dae::AIComponent::AIComponent()
{
	
}

dae::AIComponent::~AIComponent()
{

}

void dae::AIComponent::Initialize()
{
	GetGameObject().lock()->AddComponent(std::make_shared<dae::MoveComponent>());
	GetGameObject().lock()->AddComponent(std::make_shared<dae::CollisionComponent>());
}

void dae::AIComponent::Update()
{

}

void dae::AIComponent::Render()
{

}

void dae::AIComponent::MoveLeft()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col && !m_JustCollidedLeft)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionLeftRight(obs) && !m_JustCollidedRight)
				{
					m_JustCollidedLeft = true;
					if (!col->CheckCollisionLeftRight(obs, 1.f))
					{
						move->MoveObject(1, 0);
					}
					return;
				}				
			}
			m_JustCollidedRight = false;
			m_JustCollidedDown = false;
			m_JustCollidedUp = false;
			move->MoveObject(-1, 0);
		}
	}
}

void dae::AIComponent::MoveRight()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col && !m_JustCollidedRight)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionLeftRight(obs) && !m_JustCollidedLeft)
				{
					m_JustCollidedRight = true;
					if (!col->CheckCollisionLeftRight(obs, -1.f))
					{
						move->MoveObject(-1, 0);
					}
					return;
				}
			}
			m_JustCollidedLeft = false;
			m_JustCollidedDown = false;
			m_JustCollidedUp = false;
			move->MoveObject(1, 0);
		}
	}
}

void dae::AIComponent::MoveUp()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col && !m_JustCollidedUp)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionTopBottem(obs) && !m_JustCollidedDown)
				{
					m_JustCollidedUp = true;
					if (!col->CheckCollisionTopBottem(obs, 1.f))
					{
						move->MoveObject(0, 1);
					}
					return;
				}
			}
			m_JustCollidedDown = false;
			m_JustCollidedLeft = false;
			m_JustCollidedRight = false;
			move->MoveObject(0, -1);
		}
	}
}

void dae::AIComponent::MoveDown()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col && !m_JustCollidedDown)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionTopBottem(obs) && !m_JustCollidedUp)
				{
					m_JustCollidedDown = true;
					if (!col->CheckCollisionTopBottem(obs, -1.f))
					{
						move->MoveObject(0, -1);
					}
					return;
				}
			}
			m_JustCollidedUp = false;
			m_JustCollidedLeft = false;
			m_JustCollidedRight = false;
			move->MoveObject(0, 1);
		}
	}
}
