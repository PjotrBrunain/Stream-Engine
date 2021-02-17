#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::GameObject::~GameObject() = default;

void StreamEngine::GameObject::Update(){}

void StreamEngine::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void StreamEngine::GameObject::AddComponent(BaseComponent* pComponent)
{
	m_pComponents.push_back(pComponent);
}
