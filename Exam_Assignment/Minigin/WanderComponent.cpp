#include "MiniginPCH.h"
#include "WanderComponent.h"
#include "GameObject.h"
#include "MoveComponent.h"

dae::WanderComponent::WanderComponent(bool doWander)
:m_DoWander(doWander)
{
}

dae::WanderComponent::~WanderComponent()
{
}

void dae::WanderComponent::Initialize()
{

}

void dae::WanderComponent::Update()
{
	if (m_DoWander && m_pGameObject.lock())
	{
		auto trans = m_pGameObject.lock()->GetTransform();
		auto speed = m_pGameObject.lock()->GetComponent<MoveComponent>();
		if (speed.lock())
		{
			auto const xPos = trans.GetPosition().x + speed.lock()->GetSpeed().x;
			auto const yPos = trans.GetPosition().y + speed.lock()->GetSpeed().y;
			m_pGameObject.lock()->SetPosition(xPos, yPos);
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
