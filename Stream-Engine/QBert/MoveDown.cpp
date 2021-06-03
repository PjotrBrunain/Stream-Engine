#include "MoveDown.h"

#include <utility>

void MoveDown::Execute()
{
	int column = m_pQbert->GetColumn();
	int row = m_pQbert->GetRow();
	if (row % 2 == 1)
	{
		column--;
	}
	row++;
	m_pQbert->SetRow(row);
	m_pQbert->SetColumn(column);
	float hexSize = m_pGameBoard->GetHexSize();
	m_pQbert->GetTransform().SetPosition(m_pGameBoard->GetTilePosition(row, column).x, m_pGameBoard->GetTilePosition(row, column).y + hexSize, 1);
}

MoveDown::MoveDown(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard)
	:Command(),
	m_pQbert(std::move(pQbert)),
	m_pGameBoard(std::move(pGameBoard))
{
}
