#pragma once
#include <GameObject.h>

#include "SpriteTextureComponent.h"

class GameBoardObject;

class QbertObject : public StreamEngine::GameObject
{
public:
	QbertObject();
	void Init(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard);

	int GetRow() const;
	int GetColumn() const;

	void SetRow(int row);
	void SetColumn(int column);
private:
	int m_Column;
	int m_Row;
};
