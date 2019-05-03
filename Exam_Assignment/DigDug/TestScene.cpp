#include "MiniginPCH.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "CharacterComponent.h"
#include "InputManager.h"
#include "WanderComponent.h"
#include "MapGenerator.h"
#include "GhostComponent.h"
#include "SeekComponent.h"


dae::TestScene::TestScene(const std::string& name) :Scene(name)
, m_GridSizeWidth(14)
, m_GridSizeHeight(19)
{

}

void dae::TestScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	auto to = std::make_shared<TextObject>("TestSceneDemo", font);
	to->SetPosition(120, 0);
	Add(to);
	m_GridTest = MapGenerator::GetInstance().CreateMap("../Data/Map.txt", m_GridSizeWidth, m_GridSizeHeight);
	for (auto grid : m_GridTest)
	{
		Add(grid);
	}
	
	m_Test = std::make_shared<GameObject>();
	m_Test->SetTexture("dot.png");
	m_Test->SetSize(30, 30);
	m_Test->SetPosition(192.f, 228.f);
	//InputManager::GetInstance().SetActor(m_Test);
	m_Test->AddComponent(std::make_shared<FPSComponent>(font));
	m_Test->AddComponent(std::make_shared<GhostComponent>());
	m_Test->AddComponent(std::make_shared<SeekComponent>());
	m_Test->AddComponent(std::make_shared<CharacterComponent>());
	m_Test->AddComponent(std::make_shared<WanderComponent>(false));
	m_Test->GetComponent<CharacterComponent>().lock()->SetObstacles(m_GridTest);
	Add(m_Test);

	m_Test2 = std::make_shared<GameObject>();
	m_Test2->SetTexture("dot.png");
	m_Test2->SetSize(30, 30);
	m_Test2->SetPosition(50.f, 10);
	//InputManager::GetInstance().SetActor(m_Test);
	m_Test2->AddComponent(std::make_shared<FPSComponent>(font));
	m_Test2->AddComponent(std::make_shared<GhostComponent>());
	//m_Test2->AddComponent(std::make_shared<SeekComponent>());
	m_Test2->AddComponent(std::make_shared<CharacterComponent>());
	m_Test2->AddComponent(std::make_shared<WanderComponent>(false));
	m_Test2->GetComponent<CharacterComponent>().lock()->SetObstacles(m_GridTest);
	Add(m_Test2);
}

void dae::TestScene::Update()
{
	auto comp = m_Test->GetComponent<CollisionComponent>().lock();
	auto Ghostcomp = m_Test->GetComponent<GhostComponent>().lock();
	auto Seekcomp = m_Test->GetComponent<SeekComponent>().lock();
	//Ghostcomp->EnableGhostMode();
	Seekcomp->SetTarget(m_Test2);
	
	Scene::Update();
	/*for (int i = 0; i < m_GridSizeHeight; i++)
	{
		for (int k = 0; k < m_GridSizeWidth; k++)
		{
			int num = i * m_GridSizeWidth + k;			
			if (comp->CheckCollisionTopBottem(m_GridTest[num]))
			{
				auto move = m_Test->GetComponent<MoveComponent>().lock();
				move->SetSpeed(move->GetSpeed().x, -move->GetSpeed().y);
			}
			if (comp->CheckCollisionLeftRight(m_GridTest[num]))
			{
				auto move = m_Test->GetComponent<MoveComponent>().lock();
				move->SetSpeed(-move->GetSpeed().x, move->GetSpeed().y);
			}
		}

	}
	if (comp->CheckIfInObject(m_GridTest[130]))
	{
		auto move = m_Test->GetComponent<MoveComponent>().lock();
		move->SetSpeed(0.f, 0.f);
	}*/
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

