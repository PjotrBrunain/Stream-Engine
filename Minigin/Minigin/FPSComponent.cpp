#include "MiniginPCH.h"
#include "FPSComponent.h"

StreamEngine::FPSComponent::FPSComponent(std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(false, pOwningGameObject),
	m_pText(std::make_shared<std::string>("0"))
{
}

void StreamEngine::FPSComponent::Update(float deltaTime)
{
	*m_pText = std::to_string(int(1 / deltaTime * 1000));
}

std::shared_ptr<std::string> StreamEngine::FPSComponent::GetTextLink() const
{
	return m_pText;
}
