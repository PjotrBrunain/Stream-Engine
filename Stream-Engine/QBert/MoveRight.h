#pragma once
#include <Command.h>
#include <memory>
class QbertObject;
class GameBoardObject;

class MoveRight : public StreamEngine::Command
{
public:
	MoveRight(std::shared_ptr<QbertObject> pQbert, std::shared_ptr<GameBoardObject> pGameBoard);
	~MoveRight() override = default;
	
	void Execute() override;
private:
	std::shared_ptr<QbertObject> m_pQbert;
	std::shared_ptr<GameBoardObject> m_pGameBoard;
};

