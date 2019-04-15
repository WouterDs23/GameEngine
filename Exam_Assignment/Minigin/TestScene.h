#pragma once
#include "Scene.h"

namespace dae
{
	class TestScene :public dae::Scene
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
	};
}
