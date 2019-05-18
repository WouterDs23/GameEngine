#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
class GunComponent :
	public dae::BaseComponent
{
public:
	GunComponent(std::shared_ptr<dae::GameObject> gun, std::weak_ptr<dae::GameObject> parent);
	~GunComponent() override = default;

	GunComponent(const GunComponent& other) = delete;
	GunComponent(GunComponent&& other) noexcept = delete;
	GunComponent& operator=(const GunComponent& other) = delete;
	GunComponent& operator=(GunComponent&& other) noexcept = delete;

	void Initialize() override;
	void Update() override;
	void Render() override;

	void Shoot(float x, float y);
private:
	std::shared_ptr<dae::GameObject> m_Gun{};
	std::weak_ptr<dae::GameObject> m_Parent{};
	bool m_Shot{ false };
	float m_Timer{};
	float m_xSpeed{};
	float m_ySpeed{};
};

