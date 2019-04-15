#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"


void dae::SceneManager::Update()
{
	for(auto scene : mScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::CreateScene(const std::string& name, TypeOfScene type)
{
	switch (type)
	{
	case TestScene:
		mScenes.push_back(std::make_shared<dae::TestScene>(name));
		mScenes.back()->Initialize();
		break;
	default:
		mScenes.push_back(std::make_shared<Scene>(name));
		mScenes.back()->Initialize();
		break;
	}	
}
