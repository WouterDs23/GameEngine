#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		float GetWidth() const { return float(m_Width); }
		float GetHeight() const { return float(m_Height); }

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		int m_Width{};
		int m_Height{};
	};
}

