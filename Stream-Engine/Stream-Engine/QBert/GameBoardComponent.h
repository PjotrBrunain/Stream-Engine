#pragma once
#include <memory>
#include "GameObject.h"

class GameBoardObject final : public StreamEngine::GameObject
{
public:

	GameBoardObject(int rows, int columns);

	GameBoardObject(const GameBoardObject&) = delete;
	GameBoardObject(GameBoardObject&&) noexcept = delete;
	GameBoardObject& operator=(const GameBoardObject&) = delete;
	GameBoardObject& operator=(GameBoardObject&&) noexcept = delete;
	
	~GameBoardObject() override = default;

	void AddChild(const std::shared_ptr<GameObject>& pChild, int row, int column);

	int GetNrOfRows() const;
	int GetNrOfColumns() const;

private:
	int m_Rows;
	int m_Columns;
};