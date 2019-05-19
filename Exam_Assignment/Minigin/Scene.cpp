#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name)
{
}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Initialize()
{
}

void dae::Scene::Update()
{
	for(auto gameObject : m_Objects)
	{
		if (gameObject->GetDelete())
		{
			m_Objects.erase(remove(m_Objects.begin(), m_Objects.end(), gameObject));
			gameObject.reset();
			continue;
		}
		if (gameObject && gameObject->GetDoRenderAndUpdate())
		{
			gameObject->Update();			
		}
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		if (gameObject && gameObject->GetDoRenderAndUpdate())
		{
			gameObject->Render();
		}
	}
}

