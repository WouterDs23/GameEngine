#pragma once
#include "Scene.h"
#include <future>

namespace dae
{
	class GameObject;
	class TextObject;
	class SecondLevelTwoP final :public dae::Scene
	{
	public:
		explicit SecondLevelTwoP(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void Reset() override;

		SecondLevelTwoP(const SecondLevelTwoP& other) = delete;
		SecondLevelTwoP(SecondLevelTwoP&& other) = delete;
		SecondLevelTwoP& operator=(const SecondLevelTwoP& other) = delete;
		SecondLevelTwoP& operator=(SecondLevelTwoP&& other) = delete;
	private:
		std::shared_ptr<dae::GameObject> m_PlayerOne;
		std::shared_ptr<dae::GameObject> m_PlayerTwo;
		std::shared_ptr<dae::GameObject> m_Pooka;
		std::shared_ptr<dae::GameObject> m_Fygar;
		std::shared_ptr<dae::GameObject> m_Pooka2;
		std::shared_ptr<dae::GameObject> m_Fygar2;
		std::vector< std::weak_ptr<dae::GameObject>> m_Rocks;
		std::shared_ptr<dae::TextObject> m_Score;
		int m_GridSizeWidth{};
		int m_GridSizeHeight{};
		float m_GridWidth{};
		float m_GridHeight{};
	};
}
