#include "MiniginPCH.h"
#include "WanderComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "CharacterComponent.h"

dae::WanderComponent::WanderComponent(bool doWander)
:m_DoWander(doWander),
m_WanderLeft(false),
m_WanderRight(false),
m_WanderTop(false),
m_WanderBottem(false)
{
	m_GoLeft = std::make_unique<MoveLeft>();
	m_GoRight = std::make_unique<MoveRight>();
	m_GoUp = std::make_unique<MoveUp>();
	m_GoDown = std::make_unique<MoveDown>();
}

dae::WanderComponent::~WanderComponent()
{
}

void dae::WanderComponent::Initialize()
{
	RandomDirCalc();
}

void dae::WanderComponent::Update()
{
	auto actor = GetGameObject().lock();
	if (m_DoWander && m_pGameObject.lock())
	{
		if (m_WanderLeft)
		{
			m_GoLeft->execute(GetGameObject());
			if (actor)
			{
				auto comp = actor->GetComponent<CharacterComponent>().lock();
				if (comp)
				{
					if (comp->GetCollidedLeft())
					{
						m_WanderLeft = false;
						RandomDirCalc(Left);
					}
					
				}
			}
			return;
		}
		if (m_WanderRight)
		{
			m_GoRight->execute(GetGameObject());
			if (actor)
			{
				auto comp = actor->GetComponent<CharacterComponent>().lock();
				if (comp)
				{
					if (comp->GetCollidedRight())
					{
						m_WanderRight = false;
						RandomDirCalc(Right);
					}

				}
			}
			return;
		}
		if (m_WanderTop)
		{
			m_GoUp->execute(GetGameObject());
			if (actor)
			{
				auto comp = actor->GetComponent<CharacterComponent>().lock();
				if (comp)
				{
					if (comp->GetCollidedTop())
					{
						m_WanderTop = false;
						RandomDirCalc(Up);
					}

				}
			}
			return;
		}
		if (m_WanderBottem)
		{
			m_GoDown->execute(GetGameObject());
			if (actor)
			{
				auto comp = actor->GetComponent<CharacterComponent>().lock();
				if (comp)
				{
					if (comp->GetCollidedBottom())
					{
						m_WanderBottem = false;
						RandomDirCalc(Down);
					}

				}
			}
			return;
		}
	}
	
}

void dae::WanderComponent::Render()
{
}

void dae::WanderComponent::DoWander()
{
	m_DoWander = true;
}

void dae::WanderComponent::StopWander()
{
	m_DoWander = false;
}

void dae::WanderComponent::RandomDirCalc(Direction DontGo)
{
	auto actor = GetGameObject().lock();
	auto comp = actor->GetComponent<CharacterComponent>().lock();
	if (comp)
	{
		bool canGo = false;
		do
		{
			int randStartLoc = rand() % 4;
			switch (randStartLoc)
			{
			case 0:
				if (DontGo != Left)
				{
					m_WanderLeft = canGo = true;
				}
				break;
			case 1:
				if (DontGo != Right)
				{
					m_WanderRight = canGo = true;
				}				
				break;
			case 2:
				if (DontGo != Up)
				{
					m_WanderTop = canGo = true;
				}
				break;
			case 3:
				if (DontGo != Down)
				{
					m_WanderBottem = canGo = true;
				}
				break;
			default:
				break;

			}
		} while (!canGo);
	}
	
}
