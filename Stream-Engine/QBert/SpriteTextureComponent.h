#pragma once
#include <BaseComponent.h>
#include <map>
#include <memory>
#include <string>
#include <vector>



#include "Structs.h"
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
	void Render() const override;

	void SetSrcRectIdx(int srcRectIdx);
	unsigned int GetCurrentSrcRectIdx() const;
	void AddSrcRect(const Rect& srcRect);

	unsigned int GetSrcRectVecLength() const;

	void operator++();
	void operator--();

private:
	static std::map<std::string, std::shared_ptr<StreamEngine::Texture2D>> m_pTextures;
	std::string m_Path;

	std::vector<Rect> m_SrcRects;
	unsigned int m_CurrentSrcRectIdx;
};