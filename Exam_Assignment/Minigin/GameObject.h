#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddComponent(BaseComponent* comp)
		{
			for (BaseComponent* comps : m_Components)
			{
				if (comps == comp)
				{
					std::cout << "Component is already in this object";
					return;
				}
			}
			m_Components.push_back(comp);
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	protected:
		void RootUpdate();

	private:
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;
		std::vector<BaseComponent*> m_Components;
	};
}
