#include "MiniginPCH.h"
#include "DemoScene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextObject.h"


DemoScene::DemoScene() :
	Scene("Demo")
{
	auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.jpg");
	Add(go);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPSComponent* FPS = new FPSComponent(font);
	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	go->AddComponent(FPS);
	Add(go);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	Add(to);
}

void DemoScene::Update()
{
	
}

void DemoScene::Render() const
{
	
}

