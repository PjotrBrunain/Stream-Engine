#pragma once
#include "Command.h"
#include "GameBoardObject.h"
#include "QbertObject.h"

class MoveDown : public StreamEngine::Command
{
public:
	void Execute() override;

	MoveDown(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard);
	~MoveDown() override = default;
private:
	std::shared_ptr<QbertObject> m_pQbert;
	std::shared_ptr<GameBoardObject> m_pGameBoard;
};
