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
		gameObject.lock()->AddComponent(std::make_shared<CharacterComponent>());
		auto& input = dae::InputManager::GetInstance();
		input.SetActor(gameObject.lock(), m_Controller);
		input.ConfigButtons(dae::ControllerButton::ButtonA, std::move(std::make_unique<dae::ExitGame>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Up, std::move(std::make_unique<MoveUp>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Down, std::move(std::make_unique<MoveDown>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Left, std::move(std::make_unique<MoveLeft>()), m_Controller);
		input.ConfigButtons(dae::ControllerButton::DPad_Right, std::move(std::make_unique<MoveRight>()), m_Controller);
		gameObject.lock()->GetComponent<CharacterComponent>().lock()->SetObstacles(m_Obstacles);
	}
}

void MainCharComponent::Update()
{
	//m_State = m_State->Update();
}

void MainCharComponent::Render()
{
	//m_State->Render();
}


bool MoveLeft::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveLeft();
		}
	}
	return false;
}

bool MoveRight::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveRight();
		}
	}
	return false;
}

bool MoveUp::execute(std::weak_ptr<dae::GameObject> actor)
{
	{
		if (actor.lock())
		{
			auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
			if (comp)
			{
				comp->MoveUp();
			}
		}
		return false;
	}
}

bool MoveDown::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveDown();
		}
	}
	return false;
}