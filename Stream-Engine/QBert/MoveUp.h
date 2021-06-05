#pragma once
#include <Command.h>

#include "GameBoardObject.h"
#include "QbertObject.h"

class MoveUp : public StreamEngine::Command
{
public:
	void Execute() override;

	MoveUp(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard);
	~MoveUp() override = default;
private:
	std::shared_ptr<QbertObject> m_pQbert;
	std::shared_ptr<GameBoardObject> m_pGameBoard;
};