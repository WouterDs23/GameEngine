#pragma once
#include "BaseComponent.h"
#include <memory>
#include "InputManager.h"
namespace dae
{
	class CharacterComponent : public BaseComponent
	{
	public:
		CharacterComponent();
		~CharacterComponent() override;

		void Execute();
		void Initialize() override;
		void Update() override;
		void Render() override;

		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) noexcept = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;
	private:
	};
}
