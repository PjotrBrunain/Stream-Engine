#include "SpriteTextureComponent.h"

#include "ResourceManager.h"

SpriteTextureComponent::SpriteTextureComponent(const std::string& texturePath,
                                               const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject)
		:BaseComponent(true, pOwningGameObject)
{
	m_pTexture = StreamEngine::ResourceManager::GetInstance().LoadTexture(texturePath);
}
