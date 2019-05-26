#pragma once
#include <SDL_ttf.h>

namespace dae
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		unsigned int GetSize() { return m_Size; }
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		TTF_Font* mFont;
		unsigned int m_Size;
	};

}
