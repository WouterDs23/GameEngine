#pragma once
#include <memory>
#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "iostream"
#include "BaseState.h"

namespace dae
{
	class GameObject final : public SceneObject , public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetSize(float x, float y);

		Transform GetTransform() const { return m_Transform; }

		void AddComponent(std::shared_ptr<dae::BaseComponent> comp)
		{
			for (auto comps : m_pComponents)
			{
				if (comps == comp)
				{
					std::cout << "Component is already in this object";
					return;
				}
			}
			m_pComponents.push_back(comp);
			comp->SetGameObject(shared_from_this());
			comp->Initialize();
		}

		template <class T>
		std::weak_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			std::weak_ptr<T> temp{};
			for (auto const component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return std::dynamic_pointer_cast<T>(component);
				}					
			}
			return temp;
		}

		std::weak_ptr<dae::BaseState> GetState() const { return m_State; }

		void SetState(std::shared_ptr<dae::BaseState> state) { m_State = state; }

		bool HandleInput(std::weak_ptr<dae::Input> command);

		void Destroy();

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
		std::vector<std::shared_ptr<dae::BaseComponent>> m_pComponents;
		std::shared_ptr<dae::BaseState> m_State{};
	};
}
