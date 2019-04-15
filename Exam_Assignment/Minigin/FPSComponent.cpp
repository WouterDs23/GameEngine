#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FPSComponent.h"
#include "Time.h"
#include "Renderer.h"
#include "TextObject.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::Font> font) :
	m_FpsCount(0),
	m_FpsTimer(0),
	m_FPS(1)
	
{
	m_TextComponent = std::make_shared<TextComponent>(font);
}


FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update()
{
	m_FPS = int(1 / Time::deltaTime);
	m_TextComponent->SetText(std::to_string(m_FPS));
	m_TextComponent->Update();
}
void FPSComponent::Render()
{
	m_TextComponent->Render();
}
