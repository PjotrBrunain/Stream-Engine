#include "GameTileObject.h"

#include <algorithm>

#include "SpriteTextureComponent.h"

void GameTileObject::UpgradeTile()
{
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
	if (pSpriteComponent != nullptr)
	{
		if (!m_IsRoundRobbing)
		{
			++(*pSpriteComponent);
		}
		else
		{
			unsigned int srcIdx{ pSpriteComponent->GetCurrentSrcRectIdx() };
			srcIdx++;
			srcIdx = srcIdx % pSpriteComponent->GetSrcRectVecLength();
			pSpriteComponent->SetSrcRectIdx(srcIdx);
		}
	}	
}

void GameTileObject::DegradeTile()
{
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
	if (pSpriteComponent != nullptr)
	{
		if (!m_IsRoundRobbing)
		{
			--(*pSpriteComponent);
		}
		else
		{
			unsigned int srcIdx{ pSpriteComponent->GetCurrentSrcRectIdx() };
			srcIdx--;
			srcIdx = srcIdx % pSpriteComponent->GetSrcRectVecLength();
			pSpriteComponent->SetSrcRectIdx(srcIdx);
		}
	}
}

bool GameTileObject::IsMaxLevel()
{
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
	if (pSpriteComponent != nullptr)
	{
		return pSpriteComponent->GetCurrentSrcRectIdx() == (pSpriteComponent->GetSrcRectVecLength() - 1);
	}
	return false;
}

void GameTileObject::SetRoundRobbing(bool isRoundRobbing)
{
	m_IsRoundRobbing = isRoundRobbing;
}
