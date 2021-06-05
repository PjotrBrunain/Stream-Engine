#include "QbertObject.h"

#include "GameBoardObject.h"

QbertObject::QbertObject()
	:GameObject(),
	m_CurrentMoveDirection(Move::Right),
	m_IsJumping(),
	m_Speed(.5f),
	m_Delta(5.f),
	m_Lives(3),
	m_Column(),
	m_Row()
{
}

void QbertObject::Init(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard)
{
	std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", weak_from_this()) };
	for (int i = 0; i < 8; ++i)
	{
		pSpriteComponent->AddSrcRect(Rect{ 0.f,i * 16.f,16.f,16.f });
	}
	pSpriteComponent->SetSrcRectIdx(int(m_CurrentMoveDirection));
	AddComponent(pSpriteComponent);

	m_Column = column;
	m_Row = row;
	m_Transform.SetPosition(pGameBoard->GetTilePosition(row, column).x + pGameBoard->GetTileWidth(row, column) / 4, pGameBoard->GetTilePosition(row, column).y - pGameBoard->GetHexSize() + pGameBoard->GetTileHeight(row, column) / 4, 1);
	m_Transform.SetHeight((pGameBoard->GetTileHeight(row, column) / 4) * 2);
	m_Transform.SetWidth((pGameBoard->GetTileWidth(row, column) / 4) * 2);
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

void QbertObject::SetMoveDirection(const Move& move)
{
	m_CurrentMoveDirection = move;
	GetComponent<SpriteTextureComponent>()->SetSrcRectIdx(int(m_CurrentMoveDirection));
}

void QbertObject::Update(float deltaTime)
{
	if (m_IsJumping)
	{
		if ((m_DestPos.x - m_Delta < m_Transform.GetPosition().x && m_Transform.GetPosition().x < m_DestPos.x + m_Delta)&&(m_DestPos.y - m_Delta < m_Transform.GetPosition().y && m_Transform.GetPosition().y < m_DestPos.y + m_Delta))
		{
			SetIsJumping(false);
		}
		else
		{
			glm::vec3 direction{ m_DestPos - m_Transform.GetPosition() };
			direction = direction / sqrtf(powf(direction.x,2.f) + powf(direction.y,2.f) + powf(direction.z,2.f));
			m_Transform.SetPosition(m_Transform.GetPosition() + direction * deltaTime * m_Speed);
		}
	}
}

void QbertObject::SetIsJumping(bool isJumping)
{
	if (isJumping != m_IsJumping)
	{
		std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
		if (m_IsJumping)
		{
			//pSpriteComponent->SetSrcRect(pSpriteComponent->GetSrcRect() - 1);
			--(*pSpriteComponent);
		}
		else
		{
			//pSpriteComponent->SetSrcRect(pSpriteComponent->GetSrcRect() + 1);
			++(*pSpriteComponent);
		}
		m_IsJumping = isJumping;
	}
}

bool QbertObject::GetIsJumping() const
{
	return m_IsJumping;
}

void QbertObject::SetDestPos(const glm::vec3& destPos)
{
	m_DestPos = destPos;
}

void QbertObject::Die(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard)
{
	if (m_Lives != 0)
	{
		m_CurrentMoveDirection = Move::Right;
		m_Lives--;
		m_Column = column;
		m_Row = row;
		m_Transform.SetPosition(pGameBoard->GetTilePosition(row, column).x + pGameBoard->GetTileWidth(row, column) / 4, pGameBoard->GetTilePosition(row, column).y - pGameBoard->GetHexSize() + pGameBoard->GetTileHeight(row, column) / 4, 1);
	}
}
