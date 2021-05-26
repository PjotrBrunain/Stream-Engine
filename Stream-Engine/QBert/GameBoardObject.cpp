#include "GameBoardObject.h"

GameBoardObject::GameBoardObject(int rows, int columns, float posX, float posY, float height, float width)
	:GameObject(),
	m_Rows(rows),
	m_Columns(columns)
{
	m_pChildObjects.resize(rows * columns);
	m_Transform.SetPosition(posX, posY, 1);
	m_Transform.SetHeight(height);
	m_Transform.SetWidth(width);
	//m_HexSize = width / float(columns * 2 + 1) * 2 / float(sqrt(3));
	m_HexSize = 4 * height / float(3 * rows + 1)/2.f;
}

void GameBoardObject::AddChild(const std::shared_ptr<GameObject>& pChild, int row, int column)
{
	m_pChildObjects[row * m_Columns + column] = pChild;
	float x{m_Transform.GetPosition().x};
	float y{m_Transform.GetPosition().y};
	float w = float(sqrt(3)) * m_HexSize;
	if (row % 2 == 1)
	{
		x += w / 2 + w * float(column);
	}
	else
	{
		x += w * float(column);
	}

	y += float(row) * (0.75f*(m_HexSize * 2));

	pChild->GetTransform().SetPosition(x, y, 1);
	pChild->GetTransform().SetHeight(2 * m_HexSize);
	pChild->GetTransform().SetWidth(w);
}

int GameBoardObject::GetNrOfRows() const
{
	return m_Rows;
}

int GameBoardObject::GetNrOfColumns() const
{
	return m_Columns;
}
