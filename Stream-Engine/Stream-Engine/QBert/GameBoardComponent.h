#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

class GameBoardObject final : public StreamEngine::GameObject
{
public:

	GameBoardObject(int rows, int columns);

	GameBoardObject(const GameBoardObject&) = delete;
	GameBoardObject(GameBoardObject&&) noexcept = delete;
	GameBoardObject& operator=(const GameBoardObject&) = delete;
	GameBoardObject& operator=(GameBoardObject&&) noexcept = delete;
	
	virtual ~GameBoardObject() = default;
	
	void Update(float deltaTime) override;
	void Render() override;

private:
	int m_Rows;
	int m_Columns;
};

