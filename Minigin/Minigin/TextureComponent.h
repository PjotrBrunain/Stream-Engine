#pragma once
#include "BaseComponent.h"
#include "string"

namespace StreamEngine
{
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& texturePath);
		virtual ~TextureComponent();

		void run() override;

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) noexcept = delete;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent& operator=(TextureComponent&&) noexcept = delete;
	};
}
