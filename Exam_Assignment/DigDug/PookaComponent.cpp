#include "MiniginPCH.h"
#include "PookaComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"
#include "PookaBehaviour.h"
#include "SeekComponent.h"
#include "GhostComponent.h"

PookaComponent::PookaComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles):
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
		gameObj->AddComponent(std::make_shared<dae::SeekComponent>());
		gameObj->AddComponent(std::make_shared<dae::GhostComponent>());
		gameObj->GetComponent<dae::AIComponent>().lock()->SetObstacles(m_Obstacles);
		gameObj->SetState(std::make_shared<WanderState>());
	}
}

void PookaComponent::Update()
{

}

void PookaComponent::Render()
{

}
