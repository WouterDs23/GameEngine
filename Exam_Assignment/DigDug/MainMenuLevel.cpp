#include "MiniginPCH.h"
#include "MainMenuLevel.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "ScoreObserver.h"
#include "TextObject.h"


bool dae::NormalGame::execute(std::weak_ptr<dae::GameObject> actor)
{
	SceneManager::GetInstance().DeleteActiveScene();
	SceneManager::GetInstance().CreateScene("FirstLevel", SceneManager::FirstLevel);
	return false;
}

bool dae::TwoPlayerGame::execute(std::weak_ptr<dae::GameObject> actor)
{
	SceneManager::GetInstance().DeleteActiveScene();
	SceneManager::GetInstance().CreateScene("FirstLevel", SceneManager::FirstLevel2p);
	return false;
}

bool dae::VersusGame::execute(std::weak_ptr<dae::GameObject> actor)
{
	SceneManager::GetInstance().DeleteActiveScene();
	SceneManager::GetInstance().CreateScene("FirstLevel", SceneManager::FirstLevel2v2);
	return false;
}

dae::MainMenuLevel::MainMenuLevel(const std::string& name) :Scene(name)
{

}

void dae::MainMenuLevel::Initialize()
{
	ScoreKeeper::GetInstance().ResetScore();

	m_pBackGround = std::make_shared<GameObject>();
	m_pBackGround->SetTexture("background.jpg");
	Add(m_pBackGround);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_OnePlayer = std::make_shared<TextObject>("0", font);
	m_OnePlayer->SetPosition(50, 174);
	m_OnePlayer->SetText("Normal Game: Press W or Gamepad A");
	Add(m_OnePlayer);

	m_TwoPlayers = std::make_shared<TextObject>("0", font);
	m_TwoPlayers->SetPosition(50, 234);
	m_TwoPlayers->SetText("Two Player Game: Press E or Gamepad X");
	Add(m_TwoPlayers);

	m_Versus = std::make_shared<TextObject>("0", font);
	m_Versus->SetPosition(50, 294);
	m_Versus->SetText("Versus Game: Press R or Gamepad B");
	Add(m_Versus);

	m_Quit = std::make_shared<TextObject>("0", font);
	m_Quit->SetPosition(50, 354);
	m_Quit->SetText("Quit: Press Q or Gamepad Y");
	Add(m_Quit);

	auto& input = dae::InputManager::GetInstance();
	input.ConfigButtons(std::make_shared<dae::Input>(0, m_pBackGround, std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_Y, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(1, m_pBackGround, std::move(std::make_unique<dae::NormalGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_A, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(2, m_pBackGround, std::move(std::make_unique<dae::TwoPlayerGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_X, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(3, m_pBackGround, std::move(std::make_unique<dae::VersusGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_B, Controllers::PLAYER01));

	input.ConfigButtons(std::make_shared<dae::Input>(4, m_pBackGround, std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(5, m_pBackGround, std::move(std::make_unique<dae::NormalGame>()), dae::Pressed, 'W', 0, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(6, m_pBackGround, std::move(std::make_unique<dae::TwoPlayerGame>()), dae::Pressed, 'E', 0, Controllers::PLAYER01));
	input.ConfigButtons(std::make_shared<dae::Input>(7, m_pBackGround, std::move(std::make_unique<dae::VersusGame>()), dae::Pressed, 'R', 0, Controllers::PLAYER01));
}

void dae::MainMenuLevel::Update()
{
	Scene::Update();
}

void dae::MainMenuLevel::Render() const
{
	Scene::Render();
}

void dae::MainMenuLevel::Reset()
{
	Scene::Reset();

}

