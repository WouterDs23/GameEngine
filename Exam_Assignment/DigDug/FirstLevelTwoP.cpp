﻿#include "MiniginPCH.h"
#include "FirstLevelTwoP.h"
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
#include "ScoreObserver.h"
#include <future>
#include "HealthComponent.h"
#include "FPSComponent.h"


dae::FirstLevelTwoP::FirstLevelTwoP(const std::string& name) :Scene(name)
, m_GridSizeWidth(14)
, m_GridSizeHeight(19)
{

}

void dae::FirstLevelTwoP::Initialize()
{
	auto scoreObserver = std::make_shared<ScoreObserver>();

	ScoreKeeper::GetInstance().ResetScore();

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
	m_PlayerOne = std::make_shared<GameObject>();
	m_PlayerOne->SetTexture("dot.png");
	m_PlayerOne->SetSize(30, 30);
	m_PlayerOne->SetPosition(192.f, 228.f);
	m_PlayerOne->AddComponent(std::make_shared<DigDug::MainCharComponent>(grids,Controllers::PLAYER01));
	auto gun = std::make_shared<dae::GameObject>();
	gun->SetTexture("Gun.png");
	gun->SetPosition(192.f, 228.f);
	gun->AddComponent(std::make_shared<dae::MoveComponent>());
	gun->AddComponent(std::make_shared<dae::CollisionComponent>());
	gun->SetSize(25, 25);
	m_PlayerOne->AddComponent(std::make_shared<DigDug::GunComponent>(gun, m_PlayerOne));
	auto obs = m_PlayerOne->GetComponent<CharacterComponent>().lock();
	Add(m_PlayerOne);
	Add(gun);

	m_PlayerTwo = std::make_shared<GameObject>();
	m_PlayerTwo->SetTexture("dot.png");
	m_PlayerTwo->SetSize(30, 30);
	m_PlayerTwo->SetPosition(192.f, 192.f);
	m_PlayerTwo->AddComponent(std::make_shared<DigDug::MainCharComponent>(grids, Controllers::PLAYER02));
	gun = std::make_shared<dae::GameObject>();
	gun->SetTexture("Gun.png");
	gun->SetPosition(192.f, 228.f);
	gun->AddComponent(std::make_shared<dae::MoveComponent>());
	gun->AddComponent(std::make_shared<dae::CollisionComponent>());
	gun->SetSize(25, 25);
	m_PlayerTwo->AddComponent(std::make_shared<DigDug::GunComponent>(gun, m_PlayerTwo));
	obs = m_PlayerTwo->GetComponent<CharacterComponent>().lock();
	Add(m_PlayerTwo);
	Add(gun);

	m_Pooka = std::make_shared<GameObject>();
	m_Pooka->SetSize(25, 25);
	m_Pooka->SetPosition(70.f, 160.f);
	m_Pooka->AddComponent(std::make_shared<Enemies::PookaComponent>(grids));
	scoreObserver->Attach(m_Pooka->GetComponent<Enemies::PookaComponent>());
	Add(m_Pooka);

	gun = std::make_shared<dae::GameObject>();
	gun->SetPosition(192.f, 228.f);
	gun->SetSize(25, 25);
	Add(gun);

	m_Fygar = std::make_shared<GameObject>();
	m_Fygar->SetSize(25, 25);
	m_Fygar->SetPosition(64.f, 480.f);
	m_Fygar->AddComponent(std::make_shared<Enemies::FygarComponent>(grids, gun));
	scoreObserver->Attach(m_Fygar->GetComponent<Enemies::FygarComponent>());
	Add(m_Fygar);

	m_Pooka->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerOne);
	m_Fygar->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerOne);
	m_PlayerOne->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
	m_PlayerOne->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Fygar);

	m_PlayerTwo->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
	m_PlayerTwo->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Fygar);

	for (auto rocks : m_Rocks)
	{
		auto comp = rocks.lock()->GetComponent<Environment::RockComponent>();
		if (comp.lock())
		{
			comp.lock()->AddEnemy(m_Pooka);
			comp.lock()->AddEnemy(m_PlayerOne);
			comp.lock()->AddEnemy(m_PlayerTwo);
			comp.lock()->AddEnemy(m_Fygar);
			comp.lock()->SetObstacles(grids);
			scoreObserver->Attach(rocks.lock()->GetComponent<Environment::RockComponent>());
		}
	}

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto to = std::make_shared<TextObject>("DigDugFirstLevel2PDemo", font);
	to->SetPosition(120, 0);
	Add(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	m_Score = std::make_shared<TextObject>("0", font);
	m_Score->SetPosition(384.f, 0);
	Add(m_Score);

	m_PlayerOne->AddComponent(std::make_shared<FPSComponent>(font));
}

void dae::FirstLevelTwoP::Update()
{
	Scene::Update();
	if (m_PlayerOne)
	{		
		auto mainChar = m_PlayerOne->GetComponent<DigDug::MainCharComponent>().lock();
		auto mainChar2 = m_PlayerOne->GetComponent<DigDug::MainCharComponent>().lock();
		if (m_PlayerTwo)
		{
			mainChar2 = m_PlayerTwo->GetComponent<DigDug::MainCharComponent>().lock();
		}		

		if (mainChar && mainChar2 && (mainChar->GetResetLevel() || mainChar2->GetResetLevel()))
		{
			mainChar->ResetLevel(false);
			m_PlayerOne->SetPosition(192.f, 228.f);
			m_PlayerOne->SetState(std::make_shared<DigDug::IdleState>());
			if (m_PlayerTwo)
			{
				mainChar2->ResetLevel(false);
				m_PlayerTwo->SetPosition(192.f, 192.f);
				m_PlayerTwo->SetState(std::make_shared<DigDug::IdleState>());
			}

			if (m_Pooka)
			{
				m_Pooka->SetPosition(64.f, 160.f);
				m_Pooka->SetState(std::make_shared<Enemies::WanderState>());
			}

			if (m_Fygar)
			{
				m_Fygar->SetPosition(70.f, 480.f);
				m_Fygar->SetState(std::make_shared<Enemies::WanderState>());
			}
		}
	}
	else if (m_PlayerTwo)
	{
		auto mainChar = m_PlayerTwo->GetComponent<DigDug::MainCharComponent>().lock();
		if (mainChar && mainChar->GetResetLevel())
		{
			mainChar->ResetLevel(false);
			m_PlayerTwo->SetPosition(192.f, 192.f);
			m_PlayerTwo->SetState(std::make_shared<DigDug::IdleState>());

			if (m_Pooka)
			{
				m_Pooka->SetPosition(64.f, 160.f);
				m_Pooka->SetState(std::make_shared<Enemies::WanderState>());
				auto pooka = m_Pooka->GetComponent<Enemies::PookaComponent>();
				if (pooka.lock())
				{
					pooka.lock()->ResetStage();
				}
			}

			if (m_Fygar)
			{
				m_Fygar->SetPosition(70.f, 480.f);
				m_Fygar->SetState(std::make_shared<Enemies::WanderState>());
				auto fygar = m_Fygar->GetComponent<Enemies::FygarComponent>();
				if (fygar.lock())
				{
					fygar.lock()->ResetStage();
				}
			}
		}
	}
	if (m_Score)
	{
		m_Score->SetText(std::to_string(ScoreKeeper::GetInstance().GetScore()));
	}

	if (m_Pooka)
	{
		auto health = m_Pooka->GetComponent<HealthComponent>();
		if (health.lock()->GetLives() == 0)
		{
			m_Pooka.reset();
		}
	}

	if (m_Fygar)
	{
		auto health = m_Fygar->GetComponent<HealthComponent>();
		if (health.lock()->GetLives() == 0)
		{
			m_Fygar.reset();
		}
	}

	if (m_PlayerOne && m_PlayerTwo)
	{
		auto health = m_PlayerOne->GetComponent<HealthComponent>();
		auto health2 = m_PlayerTwo->GetComponent<HealthComponent>();
		if (health.lock()->GetLives() == 0 && health2.lock()->GetLives() != 0)
		{
			m_Pooka->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerTwo);
			m_Fygar->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerTwo);
		}
		if (health.lock()->GetLives() == 0 && health2.lock()->GetLives() == 0)
		{
			SceneManager::GetInstance().DeleteActiveScene();
			SceneManager::GetInstance().CreateScene("EndScreen", SceneManager::EndScreen);
		}
	}

	if (!m_Fygar && !m_Pooka)
	{
		auto obs = m_PlayerOne->GetComponent<HealthComponent>().lock();
		ScoreKeeper::GetInstance().SetLives(obs->GetLives());

		SceneManager::GetInstance().DeleteActiveScene();
		SceneManager::GetInstance().CreateScene("SecondLevel", SceneManager::SecondLevel2p);
	}
}

void dae::FirstLevelTwoP::Render() const
{
	Scene::Render();
}

void dae::FirstLevelTwoP::Reset()
{
	Scene::Reset();
	m_Rocks.clear();

	ScoreKeeper::GetInstance().ResetScore();

	auto m_GridTest = MapGenerator::GetInstance().GetMap("../Data/Map.txt", m_GridSizeWidth, m_GridSizeHeight);
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
	if (m_PlayerOne)
	{
		m_PlayerOne->SetPosition(192.f, 228.f);
		auto obs = m_PlayerOne->GetComponent<HealthComponent>().lock();
		obs->SetLives(3);
		m_PlayerOne->GetComponent<CharacterComponent>().lock()->SetObstacles(grids);
		Add(m_PlayerOne->GetComponent<DigDug::GunComponent>().lock()->GetGun());
		Add(m_PlayerOne);
	}
	else
	{
		m_PlayerOne = std::make_shared<GameObject>();
		m_PlayerOne->SetTexture("dot.png");
		m_PlayerOne->SetSize(30, 30);
		m_PlayerOne->SetPosition(192.f, 228.f);
		m_PlayerOne->AddComponent(std::make_shared<DigDug::MainCharComponent>(grids, Controllers::PLAYER01));
		auto gun = std::make_shared<dae::GameObject>();
		gun->SetTexture("Gun.png");
		gun->SetPosition(192.f, 228.f);
		gun->AddComponent(std::make_shared<dae::MoveComponent>());
		gun->AddComponent(std::make_shared<dae::CollisionComponent>());
		gun->SetSize(25, 25);
		m_PlayerOne->AddComponent(std::make_shared<DigDug::GunComponent>(gun, m_PlayerOne));
		auto obs = m_PlayerOne->GetComponent<CharacterComponent>().lock();
		Add(m_PlayerOne);
		Add(gun);		
	}

	if (m_PlayerTwo)
	{
		m_PlayerTwo->SetPosition(192.f, 192.f);
		auto obs = m_PlayerTwo->GetComponent<HealthComponent>().lock();
		obs->SetLives(3);
		m_PlayerTwo->GetComponent<CharacterComponent>().lock()->SetObstacles(grids);
		Add(m_PlayerTwo->GetComponent<DigDug::GunComponent>().lock()->GetGun());
		Add(m_PlayerTwo);
	}
	else
	{
		m_PlayerTwo = std::make_shared<GameObject>();
		m_PlayerTwo->SetTexture("dot.png");
		m_PlayerTwo->SetSize(30, 30);
		m_PlayerTwo->SetPosition(192.f, 192.f);
		m_PlayerTwo->AddComponent(std::make_shared<DigDug::MainCharComponent>(grids, Controllers::PLAYER02));
		auto gun = std::make_shared<dae::GameObject>();
		gun->SetTexture("Gun.png");
		gun->SetPosition(192.f, 228.f);
		gun->AddComponent(std::make_shared<dae::MoveComponent>());
		gun->AddComponent(std::make_shared<dae::CollisionComponent>());
		gun->SetSize(25, 25);
		m_PlayerTwo->AddComponent(std::make_shared<DigDug::GunComponent>(gun, m_PlayerTwo));
		auto obs = m_PlayerTwo->GetComponent<CharacterComponent>().lock();
		Add(m_PlayerTwo);
		Add(gun);
	}

	if (m_Pooka)
	{
		m_Pooka->SetPosition(64.f, 160.f);
		m_Pooka->SetState(std::make_shared<Enemies::WanderState>());
		m_Pooka->GetComponent<AIComponent>().lock()->SetObstacles(grids);
		Add(m_Pooka);
	}
	else
	{
		m_Pooka = std::make_shared<GameObject>();
		m_Pooka->SetSize(25, 25);
		m_Pooka->SetPosition(64.f, 160.f);
		m_Pooka->AddComponent(std::make_shared<Enemies::PookaComponent>(grids));
		Add(m_Pooka);
	}

	if (m_Fygar)
	{
		m_Fygar->SetPosition(64.f, 480.f);
		m_Fygar->SetState(std::make_shared<Enemies::WanderState>());
		m_Fygar->GetComponent<AIComponent>().lock()->SetObstacles(grids);
		Add(m_Fygar->GetComponent<Enemies::FygarComponent>().lock()->GetGun());
		Add(m_Fygar);
	}
	else
	{
		auto gun = std::make_shared<dae::GameObject>();
		gun->SetPosition(192.f, 228.f);
		gun->SetSize(25, 25);
		Add(gun);

		m_Fygar = std::make_shared<GameObject>();
		m_Fygar->SetSize(25, 25);
		m_Fygar->SetPosition(64.f, 480.f);
		m_Fygar->AddComponent(std::make_shared<Enemies::FygarComponent>(grids, gun));
		Add(m_Fygar);
	}	

	m_Pooka->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerOne);
	m_Fygar->GetComponent<AIComponent>().lock()->SetEnemy(m_PlayerOne);
	m_PlayerOne->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
	m_PlayerOne->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Fygar);

	m_PlayerTwo->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Pooka);
	m_PlayerTwo->GetComponent<CharacterComponent>().lock()->AddEnemy(m_Fygar);

	for (auto rocks : m_Rocks)
	{
		auto comp = rocks.lock()->GetComponent<Environment::RockComponent>();
		if (comp.lock())
		{
			comp.lock()->AddEnemy(m_Pooka);
			comp.lock()->AddEnemy(m_PlayerOne);
			comp.lock()->AddEnemy(m_PlayerTwo);
			comp.lock()->AddEnemy(m_Fygar);
			comp.lock()->SetObstacles(grids);
		}
	}
	

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto to = std::make_shared<TextObject>("DigDugFirstLevel2PDemo", font);
	to->SetPosition(120, 0);
	Add(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	m_Score = std::make_shared<TextObject>("0", font);
	m_Score->SetPosition(384.f, 0);
	Add(m_Score);
}

