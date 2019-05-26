#include "MiniginPCH.h"
#include "FygarComponent.h"
#include "GameObject.h"
#include "WanderComponent.h"
#include "AIComponent.h"
#include "SeekComponent.h"
#include "GhostComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "EnemyBehaviour.h"
#include "MoveComponent.h"
#include "FireComponent.h"
#include "FygarBehaviourh.h"

Enemies::FygarComponent::FygarComponent(std::vector<std::weak_ptr<dae::GameObject>> obstacles, std::shared_ptr<dae::GameObject> fireGun, dae::Controllers controller):
m_Obstacles(obstacles),
m_FireGun(fireGun),
m_Controller(controller)
{

}

void Enemies::FygarComponent::Initialize()
{
	auto gameObj = GetGameObject().lock();
	if (gameObj)
	{
		gameObj->AddComponent(std::make_shared<dae::AIComponent>());
		auto& input = dae::InputManager::GetInstance();
		if (m_Controller == dae::Controllers::None)
		{
			gameObj->AddComponent(std::make_shared<dae::WanderComponent>(true));
			gameObj->AddComponent(std::make_shared<dae::SeekComponent>());
			gameObj->SetState(std::make_shared<Enemies::WanderState>());
		}
		else
		{
			input.ConfigButtons(std::make_shared<dae::Input>(12, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, 'Q', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(13, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, VK_UP, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(14, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, VK_DOWN, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(15, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, VK_LEFT, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(16, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, VK_RIGHT, 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(17, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, 'M', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(18, GetGameObject().lock(), std::move(std::make_unique<Ghost>()), dae::Released, 'N', 0, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(19, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, 'R', 0, m_Controller));

			input.ConfigButtons(std::make_shared<dae::Input>(20, GetGameObject().lock(), std::move(std::make_unique<dae::ExitGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_Y, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(21, GetGameObject().lock(), std::move(std::make_unique<dae::MoveUp>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_UP, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(22, GetGameObject().lock(), std::move(std::make_unique<dae::MoveDown>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_DOWN, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(23, GetGameObject().lock(), std::move(std::make_unique<dae::MoveLeft>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_LEFT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(24, GetGameObject().lock(), std::move(std::make_unique<dae::MoveRight>()), dae::Pressed, -1, XINPUT_GAMEPAD_DPAD_RIGHT, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(25, GetGameObject().lock(), std::move(std::make_unique<Shoot>()), dae::Released, -1, XINPUT_GAMEPAD_A, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(26, GetGameObject().lock(), std::move(std::make_unique<Ghost>()), dae::Released, -1, XINPUT_GAMEPAD_X, m_Controller));
			input.ConfigButtons(std::make_shared<dae::Input>(27, GetGameObject().lock(), std::move(std::make_unique<dae::ResetGame>()), dae::Pressed, -1, XINPUT_GAMEPAD_B, m_Controller));
			gameObj->SetState(std::make_shared<Fygar::IdleState>());
		}
		gameObj->AddComponent(std::make_shared<Enemies::GhostComponent>("Fygar.png"));
		gameObj->AddComponent(std::make_shared<Enemies::FireComponent>(gameObj->GetTransform().GetSize().x*2.5f, gameObj->GetTransform().GetSize().y * 2.5f,m_FireGun, gameObj));
		gameObj->AddComponent(std::make_shared<HealthComponent>(4));
		gameObj->GetComponent<dae::AIComponent>().lock()->SetObstacles(m_Obstacles);
		gameObj->GetComponent<HealthComponent>().lock()->SetState(std::make_shared<Enemies::EnemyHitState>());
		gameObj->SetTexture("Fygar.png");
	}
	if (m_FireGun)
	{
		m_FireGun->AddComponent(std::make_shared<dae::MoveComponent>(2.f));
		m_FireGun->AddComponent(std::make_shared<dae::CollisionComponent>());
		m_FireGun->SetTexture("Fire.png");
	}
	
}

void Enemies::FygarComponent::Update()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		const auto health = gameObject.lock()->GetComponent<HealthComponent>().lock();
		if (health)
		{
			int lives = health->GetLives();
			if (lives == 0)
			{
				gameObject.lock()->SetDelete(true);
				m_FireGun->SetDelete(true);
				Notify(gameObject);
			}
		}
	}
}

void Enemies::FygarComponent::Render()
{

}

void Enemies::FygarComponent::NextStage()
{
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		switch (m_Stage)
		{
		case 1:
			gameObject.lock()->SetTexture("FygarFirstHit.png");
			break;
		case 2:
			gameObject.lock()->SetTexture("FygarSecondHit.png");
			break;
		case 3:
			gameObject.lock()->SetTexture("FygarThirdHit.png");
			break;
		default:
			break;
		}
		m_Stage++;
	}
}

void Enemies::FygarComponent::ResetStage()
{
	m_Stage = 0;
	auto gameObject = GetGameObject();
	if (gameObject.lock())
	{
		gameObject.lock()->SetTexture("Fygar.png");
	}
}

bool Enemies::Shoot::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto gun = actor.lock()->GetComponent<FireComponent>().lock();
		if (gun)
		{
			gun->Shoot();
		}
	}
	return false;
}

bool Enemies::Ghost::execute(std::weak_ptr<dae::GameObject> actor)
{
	if (actor.lock())
	{
		auto ghost = actor.lock()->GetComponent<Enemies::GhostComponent>();
		if (ghost.lock())
		{
			ghost.lock()->EnableGhostMode(!ghost.lock()->GetInGhostForm());
		}
	}
	return false;
}
