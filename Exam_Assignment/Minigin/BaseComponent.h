#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		friend class GameObject;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = 0;

		std::weak_ptr<GameObject> GetGameObject() const { return m_pGameObject; }
		void SetGameObject(std::shared_ptr<GameObject> actor) { m_pGameObject = actor; };
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		std::weak_ptr<GameObject> m_pGameObject;
	};
}

