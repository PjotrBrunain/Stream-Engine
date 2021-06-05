#include "CoilyObject.h"

#include <utility>


#include "GameBoardObject.h"
#include "QbertObject.h"
#include "SpriteTextureComponent.h"
#include "Structs.h"

CoilyObject::CoilyObject(bool isPlayerControlled, int bottomRow, std::shared_ptr<GameBoardObject> pGameBoard, std::shared_ptr<QbertObject> pQbert)
	:GameObject(),
	m_CurrentMoveDirection(Move::Right),
	m_IsJumping(true),
	m_Speed(.3f),
	m_Delta(5.f),
	m_Column(),
	m_Row(),
	m_DeadTimeRemaining(2.f),
	m_IsBall(true),
	m_BottomRow(bottomRow),
	m_pGameBoard(std::move(pGameBoard)),
	m_pQbert1(std::move(pQbert)),
	m_pQbert2(nullptr),
	m_IsPlayerControlled(isPlayerControlled)
{
}

CoilyObject::CoilyObject(bool isPlayerControlled, int bottomRow, std::shared_ptr<GameBoardObject> pGameBoard, std::shared_ptr<QbertObject> pQbert1, std::shared_ptr<QbertObject> pQbert2)
	:GameObject(),
	m_CurrentMoveDirection(Move::Right),
	m_IsJumping(true),
	m_Speed(.5f),
	m_Delta(2.f),
	m_Column(),
	m_Row(),
	m_DeadTimeRemaining(2.f),
	m_IsBall(true),
	m_BottomRow(bottomRow),
	m_pGameBoard(std::move(pGameBoard)),
	m_pQbert1(std::move(pQbert1)),
	m_pQbert2(std::move(pQbert2)),
	m_IsPlayerControlled(isPlayerControlled)
{
}

void CoilyObject::Init(int row, int column)
{
	std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", weak_from_this()) };
	for (int i = 0; i < 8; ++i)
	{
		pSpriteComponent->AddSrcRect(Rect{ 32.f, i * 16.f, 16.f, 32.f });
	}
	pSpriteComponent->AddSrcRect(Rect{ 16.f, 64.f, 16.f,16.f });
	pSpriteComponent->AddSrcRect(Rect{ 16.f, 80.f, 16.f,16.f });
	pSpriteComponent->SetSrcRectIdx(9);
	AddComponent(pSpriteComponent);

	m_Column = column;
	m_Row = row;
	m_Transform.SetPosition(m_pGameBoard->GetTilePosition(row, column).x + m_pGameBoard->GetTileWidth(row, column) / 8 * 3, m_pGameBoard->GetTilePosition(row, column).y - m_pGameBoard->GetHexSize() * 2 + m_pGameBoard->GetTileHeight(row, column) / 4, 1);
	m_Transform.SetHeight(m_pGameBoard->GetTileHeight(row, column) / 2);
	m_Transform.SetWidth(m_pGameBoard->GetTileWidth(row, column) / 4);
	m_DestPos = { m_pGameBoard->GetTilePosition(row, column).x + m_pGameBoard->GetTileWidth(row, column) / 8 * 3, m_pGameBoard->GetTilePosition(row, column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(row, column) / 4, 1 };
}

int CoilyObject::GetRow() const
{
	return m_Row;
}

int CoilyObject::GetColumn() const
{
	return m_Column;
}

void CoilyObject::SetRow(int row)
{
	m_Row = row;
}

void CoilyObject::SetColumn(int column)
{
	m_Column = column;
}

void CoilyObject::SetMoveDirection(const Move& move)
{
	m_CurrentMoveDirection = move;
	GetComponent<SpriteTextureComponent>()->SetSrcRectIdx(int(m_CurrentMoveDirection));
}

void CoilyObject::Update(float deltaTime)
{
	if (m_DeadTimeRemaining <= 0)
	{
		if (m_IsBall)
		{
			if (!m_IsJumping && m_CoolDown <=0)
			{
				if (int(deltaTime) % 2 == 0)
				{
					JumpDown();
				}
				else
				{
					JumpRight();
				}
				if (m_Row == m_BottomRow)
				{
					m_IsBall = false;
				}
			}
			else
			{
				m_CoolDown -= deltaTime;
			}
		}
		else
		{
			if (!m_IsPlayerControlled && !m_IsJumping && m_CoolDown <= 0)
			{
				float qbertDist1{ std::numeric_limits<float>::max() };
				float qbertDist2{ std::numeric_limits<float>::max() };
				if (m_pQbert1 != nullptr)
				{
					qbertDist1 = m_pGameBoard->GetDistance(OffsetTileCoords{ m_Column, m_Row }, OffsetTileCoords{ m_pQbert1->GetColumn(), m_pQbert1->GetRow() });
				}
				if (m_pQbert2 != nullptr)
				{
					qbertDist2 = m_pGameBoard->GetDistance(OffsetTileCoords{ m_Column, m_Row }, OffsetTileCoords{ m_pQbert2->GetColumn(), m_pQbert2->GetRow() });
				}
				OffsetTileCoords chaseCoords{};
				if (qbertDist2 < qbertDist1)
				{
					chaseCoords.row = m_pQbert2->GetRow();
					chaseCoords.col = m_pQbert2->GetColumn();
				}
				else
				{
					chaseCoords.row = m_pQbert1->GetRow();
					chaseCoords.col = m_pQbert1->GetColumn();
				}
				if (chaseCoords.row >= m_Row && chaseCoords.col >= m_Column)
				{
					JumpRight();
				}
				else if (chaseCoords.row >= m_Row && chaseCoords.col < m_Column)
				{
					JumpDown();
				}
				else if (chaseCoords.row < m_Row && chaseCoords.col >= m_Column)
				{
					JumpUp();
				}
				else if (chaseCoords.row < m_Row && chaseCoords.col < m_Column)
				{
					JumpLeft();
				}
			}
			else
			{
				m_CoolDown -= deltaTime;
			}
		}
		if (m_IsJumping)
		{
			if ((m_DestPos.x - m_Delta < m_Transform.GetPosition().x && m_Transform.GetPosition().x < m_DestPos.x + m_Delta) && (m_DestPos.y - m_Delta < m_Transform.GetPosition().y && m_Transform.GetPosition().y < m_DestPos.y + m_Delta))
			{
				SetIsJumping(false);
			}
			else
			{
				glm::vec3 direction{ m_DestPos - m_Transform.GetPosition() };
				direction = direction / sqrtf(powf(direction.x, 2.f) + powf(direction.y, 2.f) + powf(direction.z, 2.f));
				m_Transform.SetPosition(m_Transform.GetPosition() + direction * deltaTime * m_Speed);
			}
		}
	}
	else
	{
		m_DeadTimeRemaining -= deltaTime;
	}
}

void CoilyObject::SetIsJumping(bool isJumping)
{
	if (isJumping != m_IsJumping)
	{
		std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ GetComponent<SpriteTextureComponent>() };
		if (m_IsJumping)
		{
			--(*pSpriteComponent);
		}
		else
		{
			++(*pSpriteComponent);
		}
		m_IsJumping = isJumping;
		m_CoolDown = 1000;
	}
}

bool CoilyObject::GetIsJumping() const
{
	return m_IsJumping;
}

void CoilyObject::SetDestPos(const glm::vec3& destPos)
{
	m_DestPos = destPos;
}

void CoilyObject::Die(int row, int column)
{
	GetComponent<SpriteTextureComponent>()->SetSrcRectIdx(8);

	m_Column = column;
	m_Row = row;
	m_Transform.SetPosition(m_pGameBoard->GetTilePosition(row, column).x + m_pGameBoard->GetTileWidth(row, column) / 4, m_pGameBoard->GetTilePosition(row, column).y - m_pGameBoard->GetHexSize() * 2 + m_pGameBoard->GetTileHeight(row, column) / 4, 1);
	m_DeadTimeRemaining = 5000.f;
}

void CoilyObject::JumpDown()
{
	if (!m_IsJumping)
	{
		if (m_Row % 2 == 0)
		{
			m_Column--;
		}
		m_Row++;
		if (m_pGameBoard->IsOnPlayboard(m_Row, m_Column))
		{
			m_DestPos = glm::vec3{ m_pGameBoard->GetTilePosition(m_Row, m_Column).x + m_pGameBoard->GetTileWidth(m_Row, m_Column) / 8 * 3, m_pGameBoard->GetTilePosition(m_Row, m_Column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(m_Row, m_Column) / 4, 1 };
			if (!m_IsBall)
			{
				SetMoveDirection(Move::Down);
			}
			SetIsJumping(true);
		}
		else if (m_IsBall)
		{
			JumpRight();
		}
	}
}

void CoilyObject::JumpUp()
{
	if (!m_IsJumping)
	{
		if (m_Row % 2 == 1)
		{
			m_Column++;
		}
		m_Row--;
		if (m_pGameBoard->IsOnPlayboard(m_Row, m_Column))
		{
			m_DestPos = glm::vec3{ m_pGameBoard->GetTilePosition(m_Row, m_Column).x + m_pGameBoard->GetTileWidth(m_Row, m_Column) / 8 * 3, m_pGameBoard->GetTilePosition(m_Row, m_Column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(m_Row, m_Column) / 4, 1 };
			if (!m_IsBall)
			{
				SetMoveDirection(Move::Up);
			}
			SetIsJumping(true);
		}
	}
}

void CoilyObject::JumpRight()
{
	if (!m_IsJumping)
	{
		if (m_Row % 2 == 1)
		{
			m_Column++;
		}
		m_Row++;
		if (m_pGameBoard->IsOnPlayboard(m_Row, m_Column))
		{
			m_DestPos = glm::vec3{ m_pGameBoard->GetTilePosition(m_Row, m_Column).x + m_pGameBoard->GetTileWidth(m_Row, m_Column) / 8 * 3, m_pGameBoard->GetTilePosition(m_Row, m_Column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(m_Row, m_Column) / 4, 1 };
			if (!m_IsBall)
			{
				SetMoveDirection(Move::Right);
			}
			SetIsJumping(true);
		}
		else if (m_IsBall)
		{
			JumpDown();
		}
	}
}

void CoilyObject::JumpLeft()
{
	if (!m_IsJumping)
	{
		if (m_Row % 2 == 0)
		{
			m_Column--;
		}
		m_Row--;
		if (m_pGameBoard->IsOnPlayboard(m_Row, m_Column))
		{
			m_DestPos = glm::vec3{ m_pGameBoard->GetTilePosition(m_Row, m_Column).x + m_pGameBoard->GetTileWidth(m_Row, m_Column) / 8 * 3, m_pGameBoard->GetTilePosition(m_Row, m_Column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(m_Row, m_Column) / 4, 1 };
			if (!m_IsBall)
			{
				SetMoveDirection(Move::Left);
			}
			SetIsJumping(true);
		}
	}
}
