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

		void Render() const override;
		void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void LinkText(const std::shared_ptr<std::string> pText);
		void SetSize(const int& size);
		void SetColor(const SDL_Color& color);
		void SetDoUpdate(bool updateText);

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) noexcept = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) noexcept = delete;

	private:
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Color m_Color;
		std::shared_ptr<std::string> m_pText;
		int m_Size;
		std::string m_FontPath;

		bool m_UpdateText;
		
		void CreateTextTexture();
	};
}