#include "SelectUpCommand.h"

#include <utility>

#include "GameObject.h"
#include "SelectComponent.h"

SelectUpCommand::SelectUpCommand(std::shared_ptr<StreamEngine::GameObject> object)
	:m_SelectBoardObject(std::move(object))
{
}

void SelectUpCommand::Execute()
{
	std::shared_ptr<SelectComponent> selectComp{ m_SelectBoardObject->GetComponent<SelectComponent>() };
	if (selectComp != nullptr)
	{
		selectComp->SetSelected(selectComp->GetSelected() - 1);
	}
}
