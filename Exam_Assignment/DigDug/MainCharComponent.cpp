#include "MiniginPCH.h"
#include "MainCharComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "InputManager.h"
#include "CharacterBehaviour.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GunComponent.h"
#include "MoveComponent.h"

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
		gameObject.lock()->AddComponent(std::make_shared<dae::CharacterComponent>());
		gameObject.lock()->AddComponent(std::make_shared<HealthComponent>(3));;
		auto& input = dae::InputManager::GetInstance();
		input.ConfigButtons(std::make_shared<dae::Input>(0, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_A, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(1, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_UP, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(2, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_DOWN, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(3, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_LEFT, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(4, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_RIGHT, m_Controller));

		input.ConfigButtons(std::make_shared<dae::Input>(5, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(6, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, 'W', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(7, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, 'S', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(8, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, 'A', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(9, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, 'D', 0, m_Controller));
		input.ConfigButtons(std::make_shared<dae::Input>(10, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, 'E', 0, m_Controller));
		gameObject.lock()->GetComponent<dae::CharacterComponent>().lock()->SetObstacles(m_Obstacles);

		gameObject.lock()->SetState(std::make_shared<IdleState>());
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
		gameObject.lock()->AddComponent(std::make_shared<dae::TextComponent>(font));
		gameObject.lock()->GetComponent<dae::TextComponent>().lock()->SetPosition(0, 0);
		int lives = gameObject.lock()->GetComponent<HealthComponent>().lock()->GetLives();
		gameObject.lock()->GetComponent<dae::TextComponent>().lock()->SetText(std::to_string(lives));
	}
}

void MainCharComponent::Update()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{	
		const auto health = gameObject.lock()->GetComponent<HealthComponent>().lock();
		auto text = gameObject.lock()->GetComponent<dae::TextComponent>().lock();
		if (health && text)
		{
			int lives = health->GetLives();
			text->SetText(std::to_string(lives));
			if (lives == 0)
			{
				gameObject.lock()->SetState(std::make_shared<DeadState>());
			}
		}
	}
}

void MainCharComponent::Render()
{
	//m_State->Render();
}

bool Shoot::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto comp = actor.lock()->GetComponent<dae::CharacterComponent>().lock();
		auto gun = actor.lock()->GetComponent<GunComponent>().lock();
		if (comp && gun)
		{
			gun->Shoot(comp->GetLastVelocityX(), comp->GetLastVelocityY());
		}
	}
	return false;
}
