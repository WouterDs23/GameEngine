#include "MiniginPCH.h"
#include "TestScene.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "ResourceManager.h"
#include "GameObject.h"

namespace dae
{
	TestScene::TestScene(const std::string& name) :Scene(name)
	{

	}

	void TestScene::Initialize()
	{
		auto go = std::make_shared<GameObject>();
		go->SetTexture("background.jpg");
		Add(go);
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

		go = std::make_shared<GameObject>();
		go->SetTexture("logo.png");
		go->SetPosition(216, 180);
		go->AddComponent(std::make_shared<FPSComponent>(font));
		Add(go);

		auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
		to->SetPosition(80, 20);
		Add(to);
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::Render() const
	{
		Scene::Render();
	}
}
