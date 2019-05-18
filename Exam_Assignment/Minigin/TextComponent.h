#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
namespace dae
{
	class Texture2D;
	class Font;
	class Transform;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(std::shared_ptr<dae::Font> font);
		~TextComponent() override;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;
		void SetText(std::string text);
		void SetPosition(float x, float y);
	private:
		std::string m_Text;
		dae::Transform m_Transform;
		std::shared_ptr<dae::Font> m_Font;
		std::shared_ptr<dae::Texture2D> m_Texture;
	};
}