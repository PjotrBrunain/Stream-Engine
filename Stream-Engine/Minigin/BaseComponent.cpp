#include "MiniginPCH.h"
#include "BaseComponent.h"

StreamEngine::BaseComponent::BaseComponent(const bool isVisual, std::weak_ptr<GameObject> pOwningGameObject)
	:m_IsVisual(isVisual),
	m_pOwningGameObject(pOwningGameObject)
{
#if _DEBUG
	//std::cout << "BaseComp constructed\n";
#endif
}

StreamEngine::BaseComponent::~BaseComponent()
{
#if _DEBUG
	//std::cout << "BaseComp destructed\n";
#endif
}

bool StreamEngine::BaseComponent::IsVisual() const
{
	return m_IsVisual;
}
