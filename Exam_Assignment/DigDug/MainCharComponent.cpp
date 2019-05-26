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

DigDug::MainCharComponent::MainCharComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles, dae::Controllers controller) :
	m_Obstacles{ obstacles },
	m_Controller{ controller }
{
}


DigDug::MainCharComponent::~MainCharComponent()
{
}

void DigDug::MainCharComponent::Initialize()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		gameObject.lock()->AddComponent(std::make_shared<dae::CharacterComponent>());
		gameObject.lock()->AddComponent(std::make_shared<HealthComponent>(3));;
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
		gameObject.lock()->AddComponent(std::make_shared<dae::TextComponent>(font));
		auto& input = dae::InputManager::GetInstance();

		if (m_Controller == dae::Controllers::PLAYER02)
		{
			input.ConfigButtons(std::make_shared<dae::Input>(12, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(13, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, VK_UP, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(14, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, VK_DOWN, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(15, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, VK_LEFT, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(16, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, VK_RIGHT, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(17, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, 'M', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(18, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, 'R', 0, m_Controller));

			input.ConfigButtons(std::make_shared<dae::Input>(30, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_Y, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(31, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_UP, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(32, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_DOWN, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(33, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_LEFT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(34, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_RIGHT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(35, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, -1, XINPUT_GAMEPAD_A, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(36, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_B, m_Controller));
			gameObject.lock()->GetComponent<dae::TextComponent>().lock()->SetPosition(30, 0);
		}
		else
		{
			input.ConfigButtons(std::make_shared<dae::Input>(5, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(6, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, 'W', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(7, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, 'S', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(8, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, 'A', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(9, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, 'D', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(10, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, 'E', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(11, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, 'R', 0, m_Controller));

			input.ConfigButtons(std::make_shared<dae::Input>(0, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_Y, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(1, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_UP, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(2, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_DOWN, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(3, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_LEFT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(4, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_RIGHT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(28, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, -1, XINPUT_GAMEPAD_A, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(29, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_B, m_Controller));
			gameObject.lock()->GetComponent<dae::TextComponent>().lock()->SetPosition(0, 0);
		}

		
		gameObject.lock()->GetComponent<dae::CharacterComponent>().lock()->SetObstacles(m_Obstacles);

		gameObject.lock()->SetState(std::make_shared<IdleState>());
		auto health = gameObject.lock()->GetComponent<HealthComponent>().lock();
		health->SetState(std::make_shared<HitState>());
		gameObject.lock()->GetComponent<dae::TextComponent>().lock()->SetText(std::to_string(health->GetLives()));
	}
}

void DigDug::MainCharComponent::Update()
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

void DigDug::MainCharComponent::Render()
{
	//m_State->Render();
}

bool DigDug::Shoot::execute(std::weak_ptr<dae::GameObject> actor)
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

