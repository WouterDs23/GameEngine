#pragma once
#include "Scene.h"
#include <future>

namespace dae
{
	class GameObject;
	class TextObject;
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
		std::shared_ptr<dae::GameObject> m_Fygar;
		std::vector< std::weak_ptr<dae::GameObject>> m_Rocks;
		std::shared_ptr<dae::TextObject> m_Score;
		int m_GridSizeWidth{};
		int m_GridSizeHeight{};
		float m_GridWidth{};
		float m_GridHeight{};
	};
}
