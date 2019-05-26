#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

bool dae::GameObject::HandleInput(std::weak_ptr<dae::Input> command)
{
	if (m_State)
	{
		return m_State->HandleInput(shared_from_this(), command);
	}
	else { return command.lock()->sortCommand->execute(shared_from_this()); }
	return false;
}

void dae::GameObject::Destroy()
{
	m_pComponents.clear();
	m_Texture.reset();
	m_State.reset();
}

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
	if (m_State)
	{
		m_State->Update(shared_from_this());
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
