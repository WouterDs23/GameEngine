#pragma once
#include "Scene.h"
class DemoScene final : public dae::Scene
{
public:
	DemoScene();
	virtual ~DemoScene() = default;
	DemoScene(const DemoScene& other) = delete;
	DemoScene(DemoScene&& other):
	Scene("Demo")
	{
		this->temp = other.temp;
	};
	DemoScene& operator=(const DemoScene& other) = delete;
	DemoScene& operator=(DemoScene&& other) noexcept = delete;

protected:
	void Update() override;
	void Render() const override;

private:
	std::string temp;
};

