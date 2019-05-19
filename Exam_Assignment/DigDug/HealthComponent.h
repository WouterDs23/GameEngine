#pragma once
#include "BaseComponent.h"
#include "BaseState.h"

class HealthComponent :
	public dae::BaseComponent
{
public:
	HealthComponent(int lives):m_Lives(lives){};
	~HealthComponent() override = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Initialize() override;
	void Update() override;
	void Render() override;

	void TakeDamage();

	void SetState(std::shared_ptr<dae::BaseState> state) { m_DamagedState = state; }

	int GetLives() const { return m_Lives; }
	void SetLives(int lives) { m_Lives = lives; }
private:
	int m_Lives{};
	std::shared_ptr<dae::BaseState> m_DamagedState{};
};

