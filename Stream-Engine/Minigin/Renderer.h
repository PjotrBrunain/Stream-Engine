#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace StreamEngine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& spriteTexture, float dstX, float dstY, float srcX, float srcY, float srcWidth, float srcHeight) const;
		void RenderTexture(const Texture2D& spriteTexture, float dstX, float dstY, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

