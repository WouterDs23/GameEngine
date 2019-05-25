#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::MoveComponent::MoveComponent(float MoveSpeed):
	m_MoveSpeed(MoveSpeed)
{
	
}


dae::MoveComponent::~MoveComponent()
{

}

void dae::MoveComponent::Initialize()
{
}

void dae::MoveComponent::Update()
{
	
}

void dae::MoveComponent::Render()
{

}

void dae::MoveComponent::SetSpeed(float MoveSpeed)
{
	m_MoveSpeed = MoveSpeed;
}

void dae::MoveComponent::MoveObject(float xSpeed, float ySpeed, float)
{
	xSpeed *= m_MoveSpeed;
	ySpeed *= m_MoveSpeed;
	m_PrevSpeed = { xSpeed,ySpeed,0 };
	auto gam = GetGameObject().lock();
	if (gam)
	{
		auto trans = gam->GetTransform();
		if (trans.GetPosition().x <= 0.f || trans.GetPosition().x + trans.GetSize().x >= Renderer::GetInstance().GetWidth() || trans.GetPosition().y <= 0 || trans.GetPosition().y + trans.GetSize().y >= Renderer::GetInstance().GetHeight())
		{
			gam->SetPosition(trans.GetPosition().x - (xSpeed*2), trans.GetPosition().y - (ySpeed*2));
			return;
		}
		gam->SetPosition(trans.GetPosition().x + xSpeed, trans.GetPosition().y + ySpeed);
	}
}
