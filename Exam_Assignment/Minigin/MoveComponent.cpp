#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "GameObject.h"

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
		gam->SetPosition(trans.GetPosition().x + xSpeed, trans.GetPosition().y + ySpeed);
	}
}
