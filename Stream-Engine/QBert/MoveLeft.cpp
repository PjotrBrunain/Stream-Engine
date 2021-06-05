#include "MoveLeft.h"

#include "GameBoardObject.h"
#include "GameTileObject.h"
#include "QbertObject.h"

MoveLeft::MoveLeft(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard)
	:Command(),
	m_pQbert(std::move(pQbert)),
	m_pGameBoard(std::move(pGameBoard))
{
}

void MoveLeft::Execute()
{
	if (!m_pQbert->GetIsJumping())
	{
		int column = m_pQbert->GetColumn();
		int row = m_pQbert->GetRow();
		if (row % 2 == 0)
		{
			column--;
		}
		row--;
		if (m_pGameBoard->IsOnPlayboard(row, column))
		{
			m_pQbert->SetRow(row);
			m_pQbert->SetColumn(column);
			m_pQbert->SetDestPos(glm::vec3{ m_pGameBoard->GetTilePosition(row, column).x + m_pGameBoard->GetTileWidth(row, column) / 4, m_pGameBoard->GetTilePosition(row, column).y - m_pGameBoard->GetHexSize() + m_pGameBoard->GetTileHeight(row, column) / 4, 1 });
			m_pQbert->SetMoveDirection(Move::Left);
			m_pQbert->SetIsJumping(true);
			std::shared_ptr<GameTileObject> pGameTileObject{ std::reinterpret_pointer_cast<GameTileObject>(m_pGameBoard->GetGameTile(row, column)) };
			if (pGameTileObject != nullptr)
			{
				pGameTileObject->UpgradeTile();
			}
		}
		else
		{
			m_pQbert->Die(0, 3, m_pGameBoard);
		}
	}
}
