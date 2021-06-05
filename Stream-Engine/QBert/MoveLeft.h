#pragma once
#include <Command.h>
#include <memory>
class QbertObject;
class GameBoardObject;

class MoveLeft : public StreamEngine::Command
{
public:
	MoveLeft(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard);
	~MoveLeft() override = default;
	
	void Execute() override;
private:
	std::shared_ptr<QbertObject> m_pQbert;
	std::shared_ptr<GameBoardObject> m_pGameBoard;
};

