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
#include "MainCharComponent.h"


dae::TestScene::TestScene(const std::string& name) :Scene(name)
, m_GridSizeWidth(14)
, m_GridSizeHeight(19)
{

}

void dae::TestScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	auto to = std::make_shared<TextObject>("DigDugSceneDemo", font);
	to->SetPosition(120, 0);
	Add(to);
	m_GridTest = MapGenerator::GetInstance().CreateMap("../Data/Map.txt", m_GridSizeWidth, m_GridSizeHeight);
	for (auto grid : m_GridTest)
	{
		Add(grid);
	}
	
	m_Test = std::make_shared<GameObject>();
	m_Test->SetTexture("dot.png");
	m_Test->SetSize(25, 25);
	m_Test->SetPosition(192.f, 228.f);
	m_Test->AddComponent(std::make_shared<MainCharComponent>(m_GridTest,InputManager::Controllers::PLAYER01));
	Add(m_Test);

}

void dae::TestScene::Update()
{
	Scene::Update();
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

