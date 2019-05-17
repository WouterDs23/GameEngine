#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "InputManager.h"

dae::CharacterComponent::CharacterComponent()
{
	
}

dae::CharacterComponent::~CharacterComponent()
{

}

void dae::CharacterComponent::Initialize()
{
	GetGameObject().lock()->AddComponent(std::make_shared<dae::MoveComponent>());
	GetGameObject().lock()->AddComponent(std::make_shared<dae::CollisionComponent>());
}

void dae::CharacterComponent::Update()
{

}

void dae::CharacterComponent::Render()
{

}

void dae::CharacterComponent::MoveLeft()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionLeftRight(obs))
				{
					if (!m_JustCollidedLeft && !m_JustCollidedRight)
					{
						for (auto obstacle : m_Obstacles)
						{
							if (col->CheckIfInObject(obstacle))
							{
								obs->SetTexture("dirtway.png");
								col->SetIsObstacle(false);
								goto move;
							}
						}
						return;
					}
					else
					{
						obs->SetTexture("dirtway.png");
						col->SetIsObstacle(false);
					}
				}				
			}
			move:
			m_JustCollidedRight = false;
			m_JustCollidedDown = false;
			m_JustCollidedUp = false;
			m_JustCollidedLeft = true;
			move->MoveObject(-1, 0);
		}
	}
}

void dae::CharacterComponent::MoveRight()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionLeftRight(obs))
				{
					if (!m_JustCollidedLeft && !m_JustCollidedRight)
					{
						for (auto obstacle : m_Obstacles)
						{
							if (col->CheckIfInObject(obstacle))
							{
								obs->SetTexture("dirtway.png");
								col->SetIsObstacle(false);
								goto move;
							}
						}
						return;
					}
					else
					{
						obs->SetTexture("dirtway.png");
						col->SetIsObstacle(false);
					}
				}
			}
		}
		move:
		m_JustCollidedLeft = false;
		m_JustCollidedDown = false;
		m_JustCollidedUp = false;
		m_JustCollidedRight = true;
		move->MoveObject(1, 0);
	}
}

void dae::CharacterComponent::MoveUp()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionTopBottem(obs))
				{
					if (!m_JustCollidedUp && !m_JustCollidedDown)
					{
						for (auto obstacle : m_Obstacles)
						{
							if (col->CheckIfInObject(obstacle))
							{
								obs->SetTexture("dirtway.png");
								col->SetIsObstacle(false);
								goto move;
							}
						}
						return;
					}
					else
					{
						obs->SetTexture("dirtway.png");
						col->SetIsObstacle(false);
					}
				}
			}
			move:
			m_JustCollidedUp = true;
			m_JustCollidedDown = false;
			m_JustCollidedLeft = false;
			m_JustCollidedRight = false;
			move->MoveObject(0, -1);
		}
	}
}

void dae::CharacterComponent::MoveDown()
{
	auto obj = GetGameObject().lock();
	if (obj)
	{
		auto move = obj->GetComponent<dae::MoveComponent>().lock();
		auto col = obj->GetComponent<dae::CollisionComponent>().lock();
		if (move && col)
		{
			for (auto obs : m_Obstacles)
			{
				if (col->CheckCollisionTopBottem(obs))
				{
					if (!m_JustCollidedUp && !m_JustCollidedDown)
					{
						for (auto obstacle : m_Obstacles)
						{
							if (col->CheckIfInObject(obstacle))
							{
								obs->SetTexture("dirtway.png");
								col->SetIsObstacle(false);
								goto move;
							}
						}
						return;
					}
					else
					{
						obs->SetTexture("dirtway.png");
						col->SetIsObstacle(false);
					}
				}
			}
		}
		move:
		m_JustCollidedUp = false;
		m_JustCollidedLeft = false;
		m_JustCollidedRight = false;
		m_JustCollidedDown = true;
		move->MoveObject(0, 1);
	}	
}
