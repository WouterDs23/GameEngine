#include "MiniginPCH.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextObject.h"
#include "CollisionComponent.h"
#include "CharacterComponent.h"
#include "InputManager.h"
#include "MapGenerator.h"
#include "MainCharComponent.h"
#include "GunComponent.h"
#include "MoveComponent.h"
#include "PookaComponent.h"
#include "AIComponent.h"
#include "CharacterBehaviour.h"
#include "EnemyBehaviour.h"
#include "FygarComponent.h"
#include "RockComponent.h"


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
		auto comp = grid->GetComponent<Environment::RockComponent>();
		if (comp.lock())
		{
			m_Rocks.push_back(grid);
		}
		else { grids.push_back(grid); }
		
	}
	m_Test = std::make_shared<GameObject>();
	m_Test->SetTexture("dot.png");
	m_Test->SetSize(30, 30);
	m_Test->SetPosition(192.f, 228.f);
	m_Test->AddComponent(std::make_shared<DigDug::MainCharComponent>(grids,Controllers::PLAYER01));
	auto gun = std::make_shared<dae::GameObject>();
	gun->SetTexture("Gun.png");
	gun->SetPosition(192.f, 228.f);
	gun->AddComponent(std::make_shared<dae::MoveComponent>());
	gun->AddComponent(std::make_shared<dae::CollisionComponent>());
	gun->SetSize(25, 25);
	m_Test->AddComponent(std::make_shared<DigDug::GunComponent>(gun, m_Test));
	auto obs = m_Test->GetComponent<CharacterComponent>().lock();
	Add(m_Test);
	Add(gun);

	m_Pooka = std::make_shared<GameObject>();
	m_Pooka->SetSize(25, 25);
	m_Pooka->SetPosition(64.f, 160.f);
	m_Pooka->AddComponent(std::make_shared<Enemies::PookaComponent>(obs->GetObstacles()));
	Add(m_Pooka);

	gun = std::make_shared<dae::GameObject>();
	gun->SetPosition(192.f, 228.f);
	gun->SetSize(25, 25);
	Add(gun);

	m_Fygar = std::make_shared<GameObject>();
	m_Fygar->SetSize(25, 25);
	m_Fygar->SetPosition(64.f, 480.f);
	m_Fygar->AddComponent(std::make_shared<Enemies::FygarComponent>(obs->GetObstacles(), gun));
	Add(m_Fygar);

	m_Pooka->GetComponent<AIComponent>().lock()->SetEnemy(m_Test);
	m_Fygar->GetComponent<AIComponent>().lock()->SetEnemy(m_Test);
	m_Test->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
	m_Test->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Fygar);

	for (auto rocks : m_Rocks)
	{
		auto comp = rocks.lock()->GetComponent<Environment::RockComponent>();
		if (comp.lock())
		{
			comp.lock()->AddEnemy(m_Pooka);
			comp.lock()->AddEnemy(m_Test);
			comp.lock()->AddEnemy(m_Fygar);
		}
	}
	if (obs)
	{
		for (auto rocks : m_Rocks)
		{
			if (rocks.lock())
			{
				auto comp = rocks.lock()->GetComponent<Environment::RockComponent>();
				if (comp.lock())
				{
					comp.lock()->SetObstacles(grids);
				}
			}
		}
	}
}

void dae::TestScene::Update()
{
	Scene::Update();
	if (m_Test)
	{		
		auto mainChar = m_Test->GetComponent<DigDug::MainCharComponent>().lock();
		if (mainChar && mainChar->GetResetLevel())
		{
			mainChar->ResetLevel(false);
			m_Test->SetPosition(192.f, 228.f);
			m_Test->SetState(std::make_shared<DigDug::IdleState>());

			if (m_Pooka)
			{
				m_Pooka->SetPosition(64.f, 160.f);
				m_Pooka->SetState(std::make_shared<Enemies::WanderState>());
			}

			if (m_Fygar)
			{
				m_Fygar->SetPosition(64.f, 480.f);
				m_Fygar->SetState(std::make_shared<Enemies::WanderState>());
			}
		}
	}
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

