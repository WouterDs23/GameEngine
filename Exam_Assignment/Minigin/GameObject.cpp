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
	for (BaseComponent* comp : m_Components)
	{
		comp->Update();
	}
}
void dae::GameObject::Render() const
{
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	for (BaseComponent* comp : m_Components)
	{
		comp->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}
