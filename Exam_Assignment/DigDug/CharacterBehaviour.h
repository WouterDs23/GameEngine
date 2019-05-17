#pragma once
#include "BaseState.h"

class WalkingState final : public dae::BaseState
{
public:
	WalkingState() = default;
	~WalkingState() override = default;

	bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
	void Update(std::weak_ptr<dae::GameObject>) override;
};

class ShootingState final : public dae::BaseState
{
public:
	ShootingState() = default;
	~ShootingState() override = default;

	bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
	void Update(std::weak_ptr<dae::GameObject>) override;
};

class HitState final : public dae::BaseState
{
public:
	HitState() = default;
	~HitState() override = default;

	bool HandleInput(std::weak_ptr<dae::GameObject> obj, std::weak_ptr<dae::Input> input) override;
	void Update(std::weak_ptr<dae::GameObject>) override;
};
