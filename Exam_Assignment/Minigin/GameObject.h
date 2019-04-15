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

		template <class T>
		std::weak_ptr<T> AddComponent(std::shared_ptr<T> comp)
		{
			for (auto comps : m_pComponents)
			{
				if (comps == comp)
				{
					std::cout << "Component is already in this object";
					return comp;
				}
			}
			m_pComponents.push_back(comp);
			return comp;
		}

		template <class T>
		std::weak_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			std::weak_ptr<T> temp{};
			for (auto component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return std::dynamic_pointer_cast<T>(component);
				}					
			}
			return temp;
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
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	};
}
