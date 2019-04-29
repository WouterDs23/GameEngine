#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
dae::GameObject::~GameObject() = default;

void dae::GameObject::RootUpdate()
{

}

void dae::GameObject::Update()
{
	for (auto comp : m_pComponents)
	{
		comp->Update();
	}
}
void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	
	for (auto comp : m_pComponents)
	{
		comp->Render();
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetSize(float x, float y)
{
	m_Transform.SetSize(x, y, 0.f);
}
