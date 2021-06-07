#pragma once
#include <Command.h>
#include <memory>

namespace StreamEngine {
	class GameObject;
}

class SelectUpCommand : public StreamEngine::Command
{
public:
	SelectUpCommand(std::shared_ptr<StreamEngine::GameObject> object);
	~SelectUpCommand() override = default;
	
	void Execute() override;
private:
	std::shared_ptr<StreamEngine::GameObject> m_SelectBoardObject;
};

