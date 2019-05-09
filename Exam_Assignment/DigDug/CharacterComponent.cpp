#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "InputManager.h"

CharacterComponent::CharacterComponent()
{
	
}

CharacterComponent::~CharacterComponent()
{

}

void CharacterComponent::Initialize()
{
	GetGameObject().lock()->AddComponent(std::make_shared<dae::MoveComponent>());
	GetGameObject().lock()->AddComponent(std::make_shared<dae::CollisionComponent>());
}

void CharacterComponent::Update()
{

}

void CharacterComponent::Render()
{

}

void CharacterComponent::MoveLeft()
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
					obs->SetTexture("dirtway.png");
					col->SetIsObstacle(false);
				}				
			}
			m_JustCollidedRight = false;
			m_JustCollidedDown = false;
			m_JustCollidedUp = false;
			move->MoveObject(-1, 0);
		}
	}
}

void CharacterComponent::MoveRight()
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
					obs->SetTexture("dirtway.png");
					col->SetIsObstacle(false);
				}
			}
			m_JustCollidedLeft = false;
			m_JustCollidedDown = false;
			m_JustCollidedUp = false;
			move->MoveObject(1, 0);
		}
	}
}

void CharacterComponent::MoveUp()
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

					obs->SetTexture("dirtway.png");
					col->SetIsObstacle(false);
				}
			}
			m_JustCollidedDown = false;
			m_JustCollidedLeft = false;
			m_JustCollidedRight = false;
			move->MoveObject(0, -1);
		}
	}
}

void CharacterComponent::MoveDown()
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
					obs->SetTexture("dirtway.png");
					col->SetIsObstacle(false);
				}
			}
			m_JustCollidedUp = false;
			m_JustCollidedLeft = false;
			m_JustCollidedRight = false;
			move->MoveObject(0, 1);
		}
	}
}
