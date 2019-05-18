#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::MoveComponent::MoveComponent(float xSpeed, float ySpeed, float zSpeed)
{
	m_Speed.x = xSpeed;
	m_Speed.y = ySpeed;
	m_Speed.z = zSpeed;
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

void dae::MoveComponent::SetSpeed(float xSpeed, float ySpeed, float zSpeed)
{
	m_Speed.x = xSpeed;
	m_Speed.y = ySpeed;
	m_Speed.z = zSpeed;
}

void dae::MoveComponent::MoveObject(float xSpeed, float ySpeed, float)
{
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
