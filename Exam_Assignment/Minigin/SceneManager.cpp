#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../DigDug/FirstLevel.h"
#include "../DigDug/MainMenuLevel.h"
#include "../DigDug/FirstLevelTwoP.h"
#include "../DigDug/FirstLevelVS.h"
#include "../DigDug/SecondLevel.h"
#include "../DigDug/SecondLevelVS.h"
#include "../DigDug/SecondLevelTwoP.h"


void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

void dae::SceneManager::CreateScene(const std::string& name, TypeOfScene type)
{
	switch (type)
	{
	case MainMenu:
		m_Scenes.push_back(std::make_shared<dae::MainMenuLevel>(name));
		m_Scenes.back()->Initialize();
		break;
	case FirstLevel:
		m_Scenes.push_back(std::make_shared<dae::FirstLevel>(name));
		m_Scenes.back()->Initialize();
		break;
	case FirstLevel2p:
		m_Scenes.push_back(std::make_shared<dae::FirstLevelTwoP>(name));
		m_Scenes.back()->Initialize();
		break;
	case FirstLevel2v2:
		m_Scenes.push_back(std::make_shared<dae::FirstLevelVS>(name));
		m_Scenes.back()->Initialize();
		break;
	case SecondLevel:
		m_Scenes.push_back(std::make_shared<dae::SecondLevel>(name));
		m_Scenes.back()->Initialize();
		break;
	case SecondLevel2p:
		m_Scenes.push_back(std::make_shared<dae::SecondLevelTwoP>(name));
		m_Scenes.back()->Initialize();
		break;
	case SecondLevel2v2:
		m_Scenes.push_back(std::make_shared<dae::SecondLevelVS>(name));
		m_Scenes.back()->Initialize();
		break;
	default:
		m_Scenes.push_back(std::make_shared<Scene>(name));
		m_Scenes.back()->Initialize();
		break;
	}
	m_ActiveScene = m_Scenes.back();
	m_LastUsedType = type;
}

void dae::SceneManager::SetActiveScene(const std::string& name, TypeOfScene type)
{
	for (const auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			m_LastUsedType = type;
			return;
		}		
	}
}

void dae::SceneManager::ResetScene()
{		
	m_ActiveScene->Reset();		
}

void dae::SceneManager::DeleteActiveScene()
{
	m_ActiveScene.reset();
}
