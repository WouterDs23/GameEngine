#pragma once
#include "BaseComponent.h"
#include "Font.h"

class TextComponent;


class FPSComponent : public BaseComponent
{
public:
	FPSComponent(std::shared_ptr<dae::Font> font);
	~FPSComponent() override;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) noexcept = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

	void Update() override;
	void Render() override;
private:
	int m_FPS;
	float m_FpsTimer;
	int m_FpsCount;
	std::shared_ptr <TextComponent>  m_TextComponent;
};
