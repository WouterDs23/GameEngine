#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Font.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<dae::Font> font) :
	m_FpsCount(0),
	m_FpsTimer(0),
	m_FPS(1)
	
{
	m_TextComponent = std::make_shared<TextComponent>(font);
}


dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Initialize()
{
	m_pGameObject.lock()->AddComponent(m_TextComponent);
}

void dae::FPSComponent::Update()
{
	m_FPS = int(1 / GameLifeSpan::deltaTime);
	m_TextComponent->SetText(std::to_string(m_FPS));
}
void dae::FPSComponent::Render()
{
}
