#include "MiniginPCH.h"
#include "PookaComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"

PookaComponent::PookaComponent(std::vector<std::shared_ptr<dae::GameObject>> obstacles):
m_Obstacles(obstacles)
{

}

void PookaComponent::Initialize()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		gameObj->AddComponent(std::make_shared<dae::AIComponent>());
		gameObj->AddComponent(std::make_shared<dae::WanderComponent>(true));
		gameObj->GetComponent<dae::AIComponent>().lock()->SetObstacles(m_Obstacles);
	}
}

void PookaComponent::Update()
{

}

void PookaComponent::Render()
{

}
