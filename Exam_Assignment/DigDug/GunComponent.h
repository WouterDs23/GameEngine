#pragma once
#include <BaseComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "GameObject.h"
#pragma warning(pop)
class GunComponent :
	public dae::BaseComponent
{
public:
	GunComponent(std::shared_ptr<dae::GameObject> gun);
	~GunComponent() override = default;

	GunComponent(const GunComponent& other) = delete;
	GunComponent(GunComponent&& other) noexcept = delete;
	GunComponent& operator=(const GunComponent& other) = delete;
	GunComponent& operator=(GunComponent&& other) noexcept = delete;

	void Initialize() override;
	void Update() override;
	void Render() override;

	void Shoot(glm::vec3 vel);
private:
	std::shared_ptr<dae::GameObject> m_Gun{};
	bool m_Shot{ false };
	float m_Timer{};
};

