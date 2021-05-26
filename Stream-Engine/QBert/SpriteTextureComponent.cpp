#include "SpriteTextureComponent.h"



#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

std::map<std::string, std::shared_ptr<StreamEngine::Texture2D>> SpriteTextureComponent::m_pTextures{};

SpriteTextureComponent::SpriteTextureComponent(const std::string& texturePath,
                                               const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject)
		:BaseComponent(true, pOwningGameObject),
		m_Path(texturePath)
{
	if (m_pTextures.find(texturePath) == m_pTextures.end())
	{
		std::shared_ptr<StreamEngine::Texture2D> pTexture{ StreamEngine::ResourceManager::GetInstance().LoadTexture(texturePath) };
		m_pTextures.insert(std::make_pair(texturePath, pTexture));
	}
}

void SpriteTextureComponent::Render(int bottom, int left, int height, int width) const
{
	StreamEngine::Renderer::GetInstance().RenderTexture(*m_pTextures[m_Path], m_pOwningGameObject.lock()->GetTransform().GetPosition().x, m_pOwningGameObject.lock()->GetTransform().GetPosition().y, m_pOwningGameObject.lock()->GetTransform().GetWidth(), m_pOwningGameObject.lock()->GetTransform().GetHeight(), float(left), float(bottom), float(width), float(height));
}
