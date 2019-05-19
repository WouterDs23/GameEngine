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
#include "SeekComponent.h"
#include "GunComponent.h"
#include "MoveComponent.h"
#include "PookaComponent.h"
#include "AIComponent.h"
#include "PookaBehaviour.h"
#include "CharacterBehaviour.h"


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
	auto m_GridTest = MapGenerator::GetInstance().CreateMap("../Data/Map.txt", m_GridSizeWidth, m_GridSizeHeight);
	std::vector<std::weak_ptr<GameObject>> grids{};
	for (auto grid : m_GridTest)
	{
		Add(grid);
		grids.push_back(grid);
	}
	m_GridTest.clear();
	m_Test = std::make_shared<GameObject>();
	m_Test->SetTexture("dot.png");
	m_Test->SetSize(25, 25);
	m_Test->SetPosition(192.f, 228.f);
	m_Test->AddComponent(std::make_shared<MainCharComponent>(grids,Controllers::PLAYER01));
	auto gun = std::make_shared<dae::GameObject>();
	gun->SetTexture("Gun.png");
	gun->SetPosition(192.f, 228.f);
	gun->AddComponent(std::make_shared<dae::MoveComponent>());
	gun->AddComponent(std::make_shared<dae::CollisionComponent>());
	gun->SetSize(25, 25);
	m_Test->AddComponent(std::make_shared<GunComponent>(gun, m_Test));
	Add(m_Test);
	Add(gun);

	m_Pooka = std::make_shared<GameObject>();
	m_Pooka->SetTexture("Pooka.png");
	m_Pooka->SetSize(25, 25);
	m_Pooka->SetPosition(64.f, 160.f);
	m_Pooka->AddComponent(std::make_shared<PookaComponent>(grids));
	Add(m_Pooka);
	m_Pooka->GetComponent<AIComponent>().lock()->SetEnemy(m_Test);
	m_Test->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
}

void dae::TestScene::Update()
{
	Scene::Update();
	if (m_Test)
	{
		auto mainChar = m_Test->GetComponent<MainCharComponent>().lock();
		if (mainChar && mainChar->GetResetLevel())
		{
			mainChar->ResetLevel(false);
			m_Pooka->SetPosition(64.f, 160.f);
			m_Test->SetPosition(192.f, 228.f);
			m_Pooka->SetState(std::make_shared<WanderState>());
			m_Test->SetState(std::make_shared<IdleState>());
		}
	}
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

