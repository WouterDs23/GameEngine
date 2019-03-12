#pragma once
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

	GameObject* GetGameObject() const { return m_pGameObject; }
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	GameObject* m_pGameObject;
};

