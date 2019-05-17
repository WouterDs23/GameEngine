#pragma once
#include "BaseComponent.h"
namespace dae
{
	class NodeComponent final : public BaseComponent
	{
	public:
		NodeComponent() = default;
		~NodeComponent() override = default;

		void Initialize() override {}
		void Update() override{}
		void Render() override{}

		NodeComponent(const NodeComponent& other) = delete;
		NodeComponent(NodeComponent&& other) noexcept = delete;
		NodeComponent& operator=(const NodeComponent& other) = delete;
		NodeComponent& operator=(NodeComponent&& other) noexcept = delete;

		void AddConnection(std::weak_ptr<GameObject> obj);
		
		std::vector<std::weak_ptr<GameObject>> GetConnections() const
		{
			return m_Connections;
		}

		void ResetCosts();
		

	private:
		std::vector<std::weak_ptr<GameObject>> m_Connections;
	};


	class ConnectionComponent final : public BaseComponent
	{
	public:
		ConnectionComponent() = default;
		~ConnectionComponent() override = default;

		void Initialize() override {}
		void Update() override {}
		void Render() override {}

		ConnectionComponent(const ConnectionComponent& other) = delete;
		ConnectionComponent(ConnectionComponent&& other) noexcept = delete;
		ConnectionComponent& operator=(const ConnectionComponent& other) = delete;
		ConnectionComponent& operator=(ConnectionComponent&& other) noexcept = delete;

		void SetGCost(float g) { m_GCost = g; }
		float GetGCost() const { return m_GCost; }
		void SetHCost(float h) { m_HCost = h; }
		float GetHCost() const { return m_HCost; }
		float GetFCost() const { return m_GCost + m_HCost; }
		void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }



		std::weak_ptr<GameObject> GetStartNode() const { return m_pStartNode; }
		void SetStartNode(std::weak_ptr<GameObject> pStartNode) { m_pStartNode = pStartNode; }
		std::weak_ptr<GameObject> GetEndNode() const { return m_pEndNode; }
		void SetEndNode(std::weak_ptr<GameObject> pEndNode) { m_pEndNode = pEndNode; }
		std::weak_ptr<GameObject> GetHeadConnection() const { return m_pHeadConnection; }
		void SetHeadConnection(std::weak_ptr<GameObject> pC) { m_pHeadConnection = pC; }

		void CalculateCost(std::weak_ptr<GameObject> start, std::weak_ptr<GameObject> end);

	private:
		float m_GCost = 0.f;
		float m_HCost = 0.f;
		float m_FCost = 0.f;

		std::weak_ptr<GameObject> m_pHeadConnection;
		std::weak_ptr<GameObject> m_pStartNode;
		std::weak_ptr<GameObject> m_pEndNode;
	};
}
