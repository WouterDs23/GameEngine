#include "MiniginPCH.h"
#include "MainCharComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "InputManager.h"

MainCharComponent::MainCharComponent(std::vector<std::shared_ptr<dae::GameObject>> obstacles, dae::InputManager::Controllers controller) :
	m_Obstacles{ obstacles },
	m_Controller{ controller }
{
}


MainCharComponent::~MainCharComponent()
{
}

void MainCharComponent::Initialize()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		gameObject.lock()->AddComponent(std::make_shared<dae::CharacterComponent>());
		auto& input = dae::InputManager::GetInstance();
		input.SetActor(gameObject.lock(), m_Controller);
		input.ConfigButtons(dae::ControllerButton::ButtonA, std::move(std::make_unique<dae::ExitGame>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Up, std::move(std::make_unique<dae::MoveUp>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Down, std::move(std::make_unique<dae::MoveDown>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Left, std::move(std::make_unique<dae::MoveLeft>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Right, std::move(std::make_unique<dae::MoveRight>()), m_Controller);
		gameObject.lock()->GetComponent<dae::CharacterComponent>().lock()->SetObstacles(m_Obstacles);
	}
}

void MainCharComponent::Update()
{

}

void MainCharComponent::Render()
{

}
