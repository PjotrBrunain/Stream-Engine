#include "QbertObject.h"

#include "GameBoardObject.h"

QbertObject::QbertObject()
	:GameObject()
{
}

void QbertObject::Init(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard)
{
	std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", weak_from_this()) };
	for (int i = 0; i < 8; ++i)
	{
		pSpriteComponent->AddSrcRect(Rect{ 0.f,i * 16.f,16.f,16.f });
	}
	pSpriteComponent->SetSrcRect(4);
	AddComponent(pSpriteComponent);

	m_Column = column;
	m_Row = row;
	m_Transform.SetPosition(pGameBoard->GetTilePosition(row, column).x, pGameBoard->GetTilePosition(row, column).y - pGameBoard->GetHexSize(), 1);
	m_Transform.SetHeight(pGameBoard->GetTileHeight(row, column));
	m_Transform.SetWidth(pGameBoard->GetTileWidth(row, column));
}

int QbertObject::GetRow() const
{
	return m_Row;
}

int QbertObject::GetColumn() const
{
	return m_Column;
}

void QbertObject::SetRow(int row)
{
	m_Row = row;
}

void QbertObject::SetColumn(int column)
{
	m_Column = column;
}
