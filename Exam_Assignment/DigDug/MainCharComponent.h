#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
class CharacterState
{
	CharacterState() = default;
	virtual ~CharacterState() = default;

	CharacterState(const CharacterState& other) = delete;
	CharacterState(CharacterState&& other) noexcept = delete;
	CharacterState& operator=(const CharacterState& other) = delete;
	CharacterState& operator=(CharacterState&& other) noexcept = delete;
};

class MainCharComponent final : public dae::BaseComponent
{
public:
	MainCharComponent(std::vector<std::shared_ptr<dae::GameObject>> obstacles, dae::InputManager::Controllers controller);
	~MainCharComponent() override;
	
	MainCharComponent(const MainCharComponent& other) = delete;
	MainCharComponent(MainCharComponent&& other) noexcept = delete;
	MainCharComponent& operator=(const MainCharComponent& other) = delete;
	MainCharComponent& operator=(MainCharComponent&& other) noexcept = delete;

	void Initialize() override;
	void Update() override;
	void Render() override;
private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Obstacles;
	dae::InputManager::Controllers m_Controller{};
	std::shared_ptr<CharacterState> m_State;
};

