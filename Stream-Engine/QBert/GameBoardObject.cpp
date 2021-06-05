#include "GameBoardObject.h"
#include "GameTileObject.h"

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

const glm::vec3& GameBoardObject::GetTilePosition(int row, int column) const
{
	return m_pChildObjects[row * m_Columns + column]->GetTransform().GetPosition();
}

float GameBoardObject::GetHexSize() const
{
	return m_HexSize;
}

float GameBoardObject::GetTileHeight(int row, int column) const
{
	return m_pChildObjects[row * m_Columns + column]->GetTransform().GetHeight();
}

float GameBoardObject::GetTileWidth(int row, int column) const
{
	return m_pChildObjects[row * m_Columns + column]->GetTransform().GetWidth();
}

int GameBoardObject::GetNrOfRows() const
{
	return m_Rows;
}

int GameBoardObject::GetNrOfColumns() const
{
	return m_Columns;
}

bool GameBoardObject::IsOnPlayboard(int row, int column)
{
	int idx{ row * m_Columns + column };
	if (idx >= int(m_pChildObjects.size()) || idx < 0) return false;

	if (m_pChildObjects[idx] == nullptr) return false;

	return true;
}

const std::shared_ptr<StreamEngine::GameObject>& GameBoardObject::GetGameTile(int row, int column)
{
	return m_pChildObjects[row * m_Columns + column];
}

bool GameBoardObject::CheckWin() const
{
	bool hasWon{true};
	for (std::shared_ptr<GameObject> PChildObject : m_pChildObjects)
	{
		std::shared_ptr<GameTileObject> pGameTile{ std::dynamic_pointer_cast<GameTileObject>(PChildObject) };
		if (pGameTile != nullptr)
		{
			hasWon = hasWon && pGameTile->IsMaxLevel();
		}
	}
	return hasWon;
}

float GameBoardObject::GetDistance(const OffsetTileCoords& coords1, const OffsetTileCoords& coords2)
{
	return CubeDistance(GetCubeCoords(coords1), GetCubeCoords(coords2));
}

CubeTileCoords GameBoardObject::GetCubeCoords(const OffsetTileCoords& coords)
{
	int x = coords.col - (coords.row - (coords.row & 1)) / 2;
	int z = coords.row;
	int y = -x - z;
	return CubeTileCoords{ x,y,z };
}

float GameBoardObject::CubeDistance(const CubeTileCoords& a, const CubeTileCoords& b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2.f;
}
