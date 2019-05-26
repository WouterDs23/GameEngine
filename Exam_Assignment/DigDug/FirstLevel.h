#pragma once
#include "Scene.h"
#include <future>

namespace dae
{
	class GameObject;
	class TextObject;
	class FirstLevel final :public dae::Scene
	{
	public:
		explicit FirstLevel(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void Reset() override;

		FirstLevel(const FirstLevel& other) = delete;
		FirstLevel(FirstLevel&& other) = delete;
		FirstLevel& operator=(const FirstLevel& other) = delete;
		FirstLevel& operator=(FirstLevel&& other) = delete;
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
