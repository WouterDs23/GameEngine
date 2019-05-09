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
	m_Test->AddComponent(std::make_shared<CharacterComponent>());
	m_Test->AddComponent(std::make_shared<WanderComponent>(true));
	m_Test->GetComponent<CharacterComponent>().lock()->SetObstacles(m_GridTest);
	Add(m_Test);
}

void dae::TestScene::Update()
{
	auto comp = m_Test->GetComponent<CollisionComponent>().lock();
	Scene::Update();
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

