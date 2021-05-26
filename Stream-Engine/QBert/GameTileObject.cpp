#include "GameTileObject.h"

#include <algorithm>

void GameTileObject::Update(float deltaTime)
{
	deltaTime++;
}

void GameTileObject::Render()
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<StreamEngine::BaseComponent> pComponent) {if (pComponent->IsVisual()) pComponent->Render(); });
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [this](std::shared_ptr<StreamEngine::BaseComponent> pComponent) {if (pComponent->IsVisual()) pComponent->Render(int(m_SrcRect.bottom), int(m_SrcRect.left), int(m_SrcRect.height), int(m_SrcRect.width)); });
}

void GameTileObject::SetSrcRect(const Rect& srcRect)
{
	m_SrcRect = srcRect;
}
