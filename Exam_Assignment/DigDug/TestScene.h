#pragma once
#include "Scene.h"
namespace dae
{
	class GameObject;
	class TestScene final :public dae::Scene
	{
	public:
		explicit TestScene(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;


		TestScene(const TestScene& other) = delete;
		TestScene(TestScene&& other) = delete;
		TestScene& operator=(const TestScene& other) = delete;
		TestScene& operator=(TestScene&& other) = delete;
	private:
		std::shared_ptr<dae::GameObject> m_Test;
		std::shared_ptr<dae::GameObject> m_Pooka;
		std::vector< std::shared_ptr<dae::GameObject>> m_GridTest;
		int m_GridSizeWidth{};
		int m_GridSizeHeight{};
		float m_GridWidth{};
		float m_GridHeight{};
	};
}
