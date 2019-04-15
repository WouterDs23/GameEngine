#pragma once
#include "BaseComponent.h"
#include <memory>

class CharacterComponent : public BaseComponent
{
public:
	CharacterComponent();
	~CharacterComponent() override;
	CharacterComponent(const CharacterComponent& other) = delete;
	CharacterComponent(CharacterComponent&& other) noexcept = delete;
	CharacterComponent& operator=(const CharacterComponent& other) = delete;
	CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;

	void Update() override;
	void Render() override;
private:
};

