#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"

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
	std::string mText;
	dae::Transform mTransform;
	std::shared_ptr<dae::Font> mFont;
	std::shared_ptr<dae::Texture2D> mTexture;
};

