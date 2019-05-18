#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"


dae::TextComponent::TextComponent(std::shared_ptr<dae::Font> font) :
	m_Font{ font }
{
}


dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Initialize()
{
}

void dae::TextComponent::Update()
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_Texture = std::make_shared<dae::Texture2D>(texture);
}

void dae::TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(std::string text)
{
	m_Text = text;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
