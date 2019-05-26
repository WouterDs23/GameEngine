#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
namespace dae
{
	class Font;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(std::shared_ptr<dae::Font> font);
		~FPSComponent() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;
	private:
		std::shared_ptr <TextComponent>  m_TextComponent;
		float m_FpsTimer;
		int m_FPS;
		int m_FpsCount;
		unsigned int m_Size{};
	};
}
