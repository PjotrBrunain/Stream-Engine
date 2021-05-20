#include "GameBoardComponent.h"

GameBoardObject::GameBoardObject(int rows, int columns)
		:GameObject(),
		m_Rows(rows),
		m_Columns(columns)
{
	m_pChildObjects.resize(rows * columns);
}
