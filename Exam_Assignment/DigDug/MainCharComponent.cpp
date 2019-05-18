#include "MiniginPCH.h"
#include "MainCharComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "InputManager.h"
#include "CharacterBehaviour.h"
#include "CollisionComponent.h"

MainCharComponent::MainCharComponent(std::vector<std::shared_ptr<dae::GameObject>> obstacles, dae::Controllers controller) :
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
		gameObject.lock()->AddComponent(std::make_shared<dae::CollisionComponent>());
		gameObject.lock()->AddComponent(std::make_shared<dae::CharacterComponent>());
		auto& input = dae::InputManager::GetInstance();
		input.ConfigButtons(std::make_shared<dae::Input>(0, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_A, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(1, GetGameObject().lock(), std::move(std::make_unique<MoveUp>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_UP, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(2, GetGameObject().lock(), std::move(std::make_unique<MoveDown>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_DOWN, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(3, GetGameObject().lock(), std::move(std::make_unique<MoveLeft>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_LEFT, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(4, GetGameObject().lock(), std::move(std::make_unique<MoveRight>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_RIGHT, m_Controller));

		input.ConfigButtons(std::make_shared<dae::Input>(5, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(6, GetGameObject().lock(), std::move(std::make_unique<MoveUp>()), dae::Pressed, 'W', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(7, GetGameObject().lock(), std::move(std::make_unique<MoveDown>()), dae::Pressed, 'S', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(8, GetGameObject().lock(), std::move(std::make_unique<MoveLeft>()), dae::Pressed, 'A', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(9, GetGameObject().lock(), std::move(std::make_unique<MoveRight>()), dae::Pressed, 'D', 0, m_Controller));
		gameObject.lock()->GetComponent<dae::CharacterComponent>().lock()->SetObstacles(m_Obstacles);

		gameObject.lock()->SetState(std::make_shared<WalkingState>());
	}
}

void MainCharComponent::Update()
{

}

void MainCharComponent::Render()
{
	//m_State->Render();
}



bool MoveLeft::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
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
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
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
			auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
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
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
		if (comp)
		{
			comp->MoveDown();
		}
	}
	return false;
}

bool Shoot::execute(std::weak_ptr<dae::GameObject> actor)
{
	return false;
}
