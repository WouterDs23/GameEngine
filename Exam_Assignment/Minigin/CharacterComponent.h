#pragma once
#include "BaseComponent.h"
#include <memory>
#include "InputManager.h"

class CharacterComponent : public BaseComponent
{
public:
	CharacterComponent();
	~CharacterComponent() override;
	CharacterComponent(const CharacterComponent& other) = delete;
	CharacterComponent(CharacterComponent&& other) noexcept = delete;
	CharacterComponent& operator=(const CharacterComponent& other) = delete;
	CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;

	void Execute();
private:
};

