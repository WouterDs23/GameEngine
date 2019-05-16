#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "BaseState.h"

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


	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Obstacles;
	dae::Controllers m_Controller{};
	
};

