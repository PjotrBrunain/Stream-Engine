#include "SpriteTextureComponent.h"



#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

std::map<std::string, std::shared_ptr<StreamEngine::Texture2D>> SpriteTextureComponent::m_pTextures{};

SpriteTextureComponent::SpriteTextureComponent(const std::string& texturePath,
                                               const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject)
		:BaseComponent(true, pOwningGameObject),
		m_Path(texturePath),
		m_CurrentSrcRectIdx()
{
	if (m_pTextures.find(texturePath) == m_pTextures.end())
	{
		std::shared_ptr<StreamEngine::Texture2D> pTexture{ StreamEngine::ResourceManager::GetInstance().LoadTexture(texturePath) };
		m_pTextures.insert(std::make_pair(texturePath, pTexture));
	}
}

void SpriteTextureComponent::Render() const
{
	StreamEngine::Renderer::GetInstance().RenderTexture(*m_pTextures[m_Path], m_pOwningGameObject.lock()->GetTransform().GetPosition().x, m_pOwningGameObject.lock()->GetTransform().GetPosition().y, m_pOwningGameObject.lock()->GetTransform().GetWidth(), m_pOwningGameObject.lock()->GetTransform().GetHeight(), m_SrcRects[m_CurrentSrcRectIdx].left, m_SrcRects[m_CurrentSrcRectIdx].bottom, m_SrcRects[m_CurrentSrcRectIdx].width, m_SrcRects[m_CurrentSrcRectIdx].height);
}

void SpriteTextureComponent::SetSrcRect(int srcRectIdx)
{
	m_CurrentSrcRectIdx = srcRectIdx;
}

void SpriteTextureComponent::AddSrcRect(const Rect& srcRect)
{
	m_SrcRects.push_back(srcRect);
}
