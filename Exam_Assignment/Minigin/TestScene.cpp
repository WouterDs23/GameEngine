#include "MiniginPCH.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "WanderComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"


dae::TestScene::TestScene(const std::string& name) :Scene(name)
, m_GridSizeWidth(14)
, m_GridSizeHeight(19)
{

}

void dae::TestScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	Add(go);

	m_GridWidth = Renderer::GetInstance().GetWidth() / m_GridSizeWidth;
	m_GridHeight = Renderer::GetInstance().GetHeight() / m_GridSizeHeight;

	m_Test = std::make_shared<GameObject>();
	m_Test->SetTexture("dot.png");
	m_Test->SetSize(m_GridWidth, m_GridHeight);
	m_Test->SetPosition(320.0000076f, 227.3684292f);
	m_Test->AddComponent(std::make_shared<FPSComponent>(font));
	m_Test->AddComponent(std::make_shared<WanderComponent>(true));
	m_Test->AddComponent(std::make_shared<MoveComponent>(0.f, 3.f));
	m_Test->AddComponent(std::make_shared<CollisionComponent>());
	Add(m_Test);
	
	float currwidth{};
	float currheight{};
	m_GridTest.resize(m_GridSizeHeight * m_GridSizeWidth);
	for (int i = 0; i < m_GridSizeHeight; i++)
	{
		for (int k = 0; k < m_GridSizeWidth; k++)
		{
			int num = i * m_GridSizeWidth + k;
			m_GridTest[num] = std::make_shared<GameObject>();
			m_GridTest[num]->SetPosition(currwidth, currheight);
			m_GridTest[num]->SetSize(m_GridWidth, m_GridHeight);
			if (k != 7 && i != 9)
			{
				m_GridTest[num]->SetTexture("logo2.png");
				m_GridTest[num]->SetObstacle();
				m_GridTest[num]->AddComponent(std::make_shared<CollisionComponent>());
			}
			if (i == 9 && (k == 0 || k == 13))
			{
				m_GridTest[num]->SetTexture("logo2.png");
				m_GridTest[num]->SetObstacle();
				m_GridTest[num]->AddComponent(std::make_shared<CollisionComponent>());
			}
			if (k == 7 && (i == 0 || i == 18))
			{
				m_GridTest[num]->SetTexture("logo2.png");
				m_GridTest[num]->SetObstacle();
				m_GridTest[num]->AddComponent(std::make_shared<CollisionComponent>());
			}
			Add(m_GridTest[num]);
			currwidth += m_GridWidth;
		}
		currheight += m_GridHeight;
		currwidth = 0;
	}
	
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	Add(to);
}

void dae::TestScene::Update()
{
	auto comp = m_Test->GetComponent<CollisionComponent>().lock();
	Scene::Update();
	for (int i = 0; i < m_GridSizeHeight; i++)
	{
		for (int k = 0; k < m_GridSizeWidth; k++)
		{
			int num = i * m_GridSizeWidth + k;			
			if (comp->CheckCollisionTopBottem(m_GridTest[num]))
			{
				auto move = m_Test->GetComponent<MoveComponent>().lock();
				move->SetSpeed(move->GetSpeed().x, -move->GetSpeed().y, move->GetSpeed().z);
			}
			if (comp->CheckCollisionLeftRight(m_GridTest[num]))
			{
				auto move = m_Test->GetComponent<MoveComponent>().lock();
				move->SetSpeed(-move->GetSpeed().x, move->GetSpeed().y, move->GetSpeed().z);
			}
		}

	}
}

void dae::TestScene::Render() const
{
	Scene::Render();
}

