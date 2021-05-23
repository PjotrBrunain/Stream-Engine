#include "GameBoardObject.h"

GameBoardObject::GameBoardObject(int rows, int columns)
		:GameObject(),
		m_Rows(rows),
		m_Columns(columns)
{
	m_pChildObjects.resize(rows * columns);
}

void GameBoardObject::AddChild(const std::shared_ptr<GameObject>& pChild, int row, int column)
{
	m_pChildObjects[row * m_Columns + column] = pChild;
}

int GameBoardObject::GetNrOfRows() const
{
	return m_Rows;
}

int GameBoardObject::GetNrOfColumns() const
{
	return m_Columns;
}
