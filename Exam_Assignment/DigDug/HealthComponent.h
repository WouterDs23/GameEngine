#pragma once
#include "BaseComponent.h"

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

	int GetLives() const { return m_Lives; }
private:
	int m_Lives{};
};

