#include "MiniginPCH.h"
#include "EndScreen.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "ScoreObserver.h"
#include "TextObject.h"


dae::EndScreen::EndScreen(const std::string& name) :Scene(name)
{

}

void dae::EndScreen::Initialize()
{
	ScoreKeeper::GetInstance().ResetScore();

	m_pBackGround = std::make_shared<GameObject>();
	m_pBackGround->SetTexture("background.jpg");
	Add(m_pBackGround);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	m_EndGame = std::make_shared<TextObject>("0", font);
	m_EndGame->SetPosition(50, 174);
	m_EndGame->SetText("EndGame");
	Add(m_EndGame);

	m_Score = std::make_shared<TextObject>("0", font);
	m_Score->SetPosition(50, 234);
	m_Score->SetText(std::to_string(ScoreKeeper::GetInstance().GetScore()));
	Add(m_Score);
}

void dae::EndScreen::Update()
{
	Scene::Update();
}

void dae::EndScreen::Render() const
{
	Scene::Render();
}

void dae::EndScreen::Reset()
{
	Scene::Reset();

}

