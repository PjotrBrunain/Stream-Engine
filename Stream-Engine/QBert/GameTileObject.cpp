#include "GameTileObject.h"

#include <algorithm>

#include "SpriteTextureComponent.h"

void GameTileObject::UpgradeTile()
{
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
	if (pSpriteComponent != nullptr)
	{
		++(*pSpriteComponent);
	}	
}

void GameTileObject::DegradeTile()
{
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
	if (pSpriteComponent != nullptr)
	{
		--(*pSpriteComponent);
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
