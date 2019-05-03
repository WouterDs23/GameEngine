#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class ConnectionComponent final : public BaseComponent
	{
	public:
		ConnectionComponent();
		~ConnectionComponent() override = default;

		void Initialize() override;
		void Update() override;
		void Render() override;

		void SetGCost(float g) { m_GCost = g; }
		float GetGCost() const { return m_GCost; }
		void SetHCost(float h) { m_HCost = h; }
		float GetHCost() const { return m_HCost; }
		float GetFCost() const { return m_GCost + m_HCost; }
		void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }

		void CalculateCost(const std::shared_ptr<GameObject> start, const std::shared_ptr<GameObject> end);

		std::weak_ptr<GameObject> GetHeadConnection() const { return m_pHeadConnection; }
		void SetHeadConnection(std::weak_ptr<GameObject> pC) { m_pHeadConnection = pC; }

		ConnectionComponent(const ConnectionComponent& other) = delete;
		ConnectionComponent(ConnectionComponent&& other) noexcept = delete;
		ConnectionComponent& operator=(const ConnectionComponent& other) = delete;
		ConnectionComponent& operator=(ConnectionComponent&& other) noexcept = delete;

	private:
		float m_GCost = 0.f;
		float m_HCost = 0.f;
		float m_FCost = 0.f;

		std::weak_ptr<GameObject> m_pHeadConnection;
	};
}
