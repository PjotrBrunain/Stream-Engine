#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::TextureComponent::TextureComponent(const std::string& texturePath, std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(true, pOwningGameObject),
	m_pTexture(nullptr)
{
#if _DEBUG
	//std::cout << "TextureComp constructed\n";
#endif
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

StreamEngine::TextureComponent::~TextureComponent()
{
#if _DEBUG
	//std::cout << "TextureComp destructed\n";
#endif
}

void StreamEngine::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture.get(), m_pOwningGameObject.lock()->GetTransform().GetPosition().x, m_pOwningGameObject.lock()->GetTransform().GetPosition().y);
}
