#pragma once
#include "Scene.h"
#include <future>
#include "BaseState.h"

namespace dae
{
	class GameObject;
	class TextObject;
	class EndScreen final :public dae::Scene
	{
	public:
		explicit EndScreen(const std::string& name);

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void Reset() override;

		EndScreen(const EndScreen& other) = delete;
		EndScreen(EndScreen&& other) = delete;
		EndScreen& operator=(const EndScreen& other) = delete;
		EndScreen& operator=(EndScreen&& other) = delete;
	private:
		std::shared_ptr<GameObject> m_pBackGround;
		std::shared_ptr<dae::TextObject> m_Score;
		std::shared_ptr<dae::TextObject> m_EndGame;
	};
}
