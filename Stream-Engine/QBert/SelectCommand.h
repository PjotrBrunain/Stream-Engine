#pragma once
#include <Command.h>
#include <memory>

namespace StreamEngine {
	class GameObject;
}

class SelectCommand : public StreamEngine::Command
{
public:
	SelectCommand(std::shared_ptr<StreamEngine::GameObject> selectObject);
	~SelectCommand() override = default;
	
	void Execute() override;
private:
	std::shared_ptr<StreamEngine::GameObject> m_SelectObject;
};

