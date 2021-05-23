#pragma once
#include <BaseComponent.h>
#include <memory>
#include <string>

#include "Texture2D.h"

class SpriteTextureComponent final : public StreamEngine::BaseComponent
{
public:
	SpriteTextureComponent(const std::string& texturePath, const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject);

	SpriteTextureComponent(const SpriteTextureComponent&) = delete;
	SpriteTextureComponent(SpriteTextureComponent&&) noexcept = delete;
	SpriteTextureComponent& operator=(const SpriteTextureComponent&) = delete;
	SpriteTextureComponent& operator=(SpriteTextureComponent&&) noexcept = delete;
	
	~SpriteTextureComponent() override = default;
	void Render(int bottom, int left, int height, int width);

private:
	std::shared_ptr<StreamEngine::Texture2D> m_pTexture;
};

