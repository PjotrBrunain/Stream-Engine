#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "algorithm"

StreamEngine::Transform& StreamEngine::GameObject::GetTransform()
{
	return m_Transform;
}

void StreamEngine::GameObject::Render()
{
	if (m_IsVisual)
	{
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<BaseComponent> pComponent) {if (pComponent->IsVisual()) pComponent->Render(); });
	}
}

bool StreamEngine::GameObject::IsVisual() const
{
	return m_IsVisual;
}

void StreamEngine::GameObject::AddChild(const std::shared_ptr<GameObject>& pChild)
{
	m_pChildObjects.push_back(pChild);
}

std::string StreamEngine::GameObject::GetName() const
{
	return m_Name;
}

void StreamEngine::GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

void StreamEngine::GameObject::SetOwner(const std::weak_ptr<GameObject> owner)
{
	m_pOwner = owner;
}

void StreamEngine::GameObject::SetIsVisual(bool isVisual)
{
	m_IsVisual = isVisual;
}

StreamEngine::GameObject::GameObject(std::string name)
	:m_Name(name)
{
}

StreamEngine::GameObject::~GameObject() = default;

void StreamEngine::GameObject::Update(float deltaTime)
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) {pComponent->Update(deltaTime); });
}

void StreamEngine::GameObject::FixedUpdate(float deltaTime)
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) {pComponent->FixedUpdate(deltaTime); });
}

void StreamEngine::GameObject::LateUpdate(float deltaTime)
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) {pComponent->LateUpdate(deltaTime); });
}

void StreamEngine::GameObject::AddComponent(const std::shared_ptr<BaseComponent> pComponent)
{
	m_pComponents.push_back(pComponent);
	m_IsVisual = m_IsVisual || pComponent->IsVisual();
}
