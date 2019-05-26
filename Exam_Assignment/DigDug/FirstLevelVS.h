#pragma once
#include "Scene.h"
#include <future>

namespace dae
{
	class GameObject;
	class TextObject;
	class FirstLevelVS final :public dae::Scene
	{
	public:
		explicit FirstLevelVS(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void Reset() override;

		FirstLevelVS(const FirstLevelVS& other) = delete;
		FirstLevelVS(FirstLevelVS&& other) = delete;
		FirstLevelVS& operator=(const FirstLevelVS& other) = delete;
		FirstLevelVS& operator=(FirstLevelVS&& other) = delete;
	private:
		std::shared_ptr<dae::GameObject> m_PlayerOne;
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
