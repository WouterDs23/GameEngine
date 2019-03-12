#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FPSComponent.h"
#include "Time.h"
#include "Renderer.h"
#include "TextObject.h"
#include "Font.h"
#include "Texture2D.h"


FPSComponent::FPSComponent(std::shared_ptr<dae::Font> font):
mFont(font)
{
}


FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update()
{
	m_FpsTimer += Time::GetInstance().GetDeltaTime();
	m_FpsCount++;
	if (m_FpsTimer > 1.f)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1.f;
	}
	mText = std::to_string(m_FPS) + " FPS";

	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
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
	mTexture = std::make_shared<dae::Texture2D>(texture);
}
void FPSComponent::Render()
{
	if (mTexture != nullptr)
	{
		const auto pos = mTransform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}
