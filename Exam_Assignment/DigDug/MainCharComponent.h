#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
class CharacterState
{
public:
	CharacterState() = default;
	virtual ~CharacterState() = default;

	CharacterState(const CharacterState& other) = delete;
	CharacterState(CharacterState&& other) noexcept = delete;
	CharacterState& operator=(const CharacterState& other) = delete;
	CharacterState& operator=(CharacterState&& other) noexcept = delete;

	virtual std::shared_ptr<CharacterState> Update() = 0;
	virtual void Render() = 0;
};

class MoveLeft final : public dae::Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
};

class MoveRight final : public dae::Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
};

class MoveUp final : public dae::Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
};

class MoveDown final : public dae::Commands
{
public:
	virtual bool execute(std::weak_ptr<dae::GameObject> actor) override;
};

class MainCharComponent final : public dae::BaseComponent
{
public:
	MainCharComponent(std::vector<std::shared_ptr<dae::GameObject>> obstacles, dae::Controllers controller);
	~MainCharComponent() override;
	
	MainCharComponent(const MainCharComponent& other) = delete;
	MainCharComponent(MainCharComponent&& other) noexcept = delete;
	MainCharComponent& operator=(const MainCharComponent& other) = delete;
	MainCharComponent& operator=(MainCharComponent&& other) noexcept = delete;

	std::weak_ptr<CharacterState> GetState() const { return m_State; }

	void Initialize() override;
	void Update() override;
	void Render() override;
private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Obstacles;
	dae::Controllers m_Controller{};
	std::shared_ptr<CharacterState> m_State;
};

