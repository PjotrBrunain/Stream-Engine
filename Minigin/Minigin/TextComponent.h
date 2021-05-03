#pragma once
#include <SDL.h>
#include "BaseComponent.h"

namespace StreamEngine
{
	class Texture2D;
	class Font;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(std::weak_ptr<GameObject> pOwningGameObject);
		TextComponent(const std::string& fontPath, std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~TextComponent();

		void Render() override;

		void SetText(const std::string& text);
		void SetSize(const int& size);

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) noexcept = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) noexcept = delete;

	private:
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Color m_Color;
		std::string m_Text;
		int m_Size;
		std::string m_FontPath;

		void CreateTextTexture();
	};
}