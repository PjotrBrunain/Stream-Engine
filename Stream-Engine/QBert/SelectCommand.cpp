#include "SelectCommand.h"
#include <Windows.h>

#include <SDL_keycode.h>
#include <utility>



#include "CoilyObject.h"
#include "GameBoardObject.h"
#include "GameObject.h"
#include "LivesObject.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveUp.h"
#include "QbertObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SelectComponent.h"

SelectCommand::SelectCommand(std::shared_ptr<StreamEngine::GameObject> selectObject)
	:m_SelectObject(std::move(selectObject))
{
}

void SelectCommand::Execute()
{
	std::shared_ptr<SelectComponent> selectComp{ m_SelectObject->GetComponent<SelectComponent>() };
	if (selectComp != nullptr)
	{
		StreamEngine::Scene& scene1{ StreamEngine::SceneManager::GetInstance().GetScene("Level1") };
		StreamEngine::Scene& scene2{ StreamEngine::SceneManager::GetInstance().GetScene("Level2") };
		StreamEngine::Scene& scene3{ StreamEngine::SceneManager::GetInstance().GetScene("Level3") };
		std::shared_ptr<GameBoardObject> pGameBoard1{ std::reinterpret_pointer_cast<GameBoardObject>(scene1.GetObjectByName("GameBoard")) };
		std::shared_ptr<GameBoardObject> pGameBoard2{ std::reinterpret_pointer_cast<GameBoardObject>(scene2.GetObjectByName("GameBoard")) };
		std::shared_ptr<GameBoardObject> pGameBoard3{ std::reinterpret_pointer_cast<GameBoardObject>(scene3.GetObjectByName("GameBoard")) };
		switch (selectComp->GetSelected())
		{
		case 0:
		{
			std::shared_ptr<QbertObject> pQbertObject{ std::make_shared<QbertObject>() };
			pQbertObject->SetName("Qbert1");
			pQbertObject->Init(0, 3, pGameBoard1);

			scene1.Add(pQbertObject);
			scene2.Add(pQbertObject);
			scene3.Add(pQbertObject);

			std::shared_ptr<LivesObject> livesObject{ std::make_shared<LivesObject>(pQbertObject) };
			livesObject->Init();
			livesObject->GetTransform().SetHeight(16);
			livesObject->GetTransform().SetWidth(16);
			livesObject->GetTransform().SetPosition(20, 20, 1);
			scene1.Add(livesObject);
			scene2.Add(livesObject);
			scene3.Add(livesObject);

			std::shared_ptr<CoilyObject> pCoily{ std::make_shared<CoilyObject>(false, pGameBoard1->GetNrOfRows() - 1, pQbertObject) };
			pCoily->Init(0, 3, pGameBoard1);
			pCoily->SetName("Coily");
			scene1.Add(pCoily);
			scene2.Add(pCoily);
			scene3.Add(pCoily);

			pQbertObject->SetCoily(pCoily);
				
			StreamEngine::InputManager::GetInstance().SetAmountOfPlayers(1);
			std::shared_ptr<MoveDown> pMoveDownCommand{ std::make_shared<MoveDown>(pQbertObject,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });

			std::shared_ptr<MoveUp> pMoveUpCommand{ std::make_shared<MoveUp>(pQbertObject,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });

			std::shared_ptr<MoveLeft> pMoveLeftCommand{ std::make_shared<MoveLeft>(pQbertObject, pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });

			std::shared_ptr<MoveRight> pMoveRightCommand{ std::make_shared<MoveRight>(pQbertObject,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });

			StreamEngine::SceneManager::GetInstance().SetActiveScene("Level1");

		}
		break;
		case 1:
		{
			std::shared_ptr<QbertObject> pQbertObject1{ std::make_shared<QbertObject>() };
			pQbertObject1->SetName("Qbert1");
			pQbertObject1->Init(6, 0, pGameBoard1);

			scene1.Add(pQbertObject1);
			scene2.Add(pQbertObject1);
			scene3.Add(pQbertObject1);

			std::shared_ptr<QbertObject> pQbertObject2{ std::make_shared<QbertObject>() };
			pQbertObject2->SetName("Qbert2");
			pQbertObject2->Init(6, 6, pGameBoard1);

			scene1.Add(pQbertObject2);
			scene2.Add(pQbertObject2);
			scene3.Add(pQbertObject2);

			std::shared_ptr<CoilyObject> pCoily{ std::make_shared<CoilyObject>(false, pGameBoard1->GetNrOfRows() - 1, pQbertObject1, pQbertObject2) };
			pCoily->Init(0, 3, pGameBoard1);
			pCoily->SetName("Coily");
			scene1.Add(pCoily);
			scene2.Add(pCoily);
			scene3.Add(pCoily);

			pQbertObject1->SetCoily(pCoily);
			pQbertObject2->SetCoily(pCoily);

			StreamEngine::InputManager::GetInstance().SetAmountOfPlayers(2);
			std::shared_ptr<MoveDown> pMoveDownCommand{ std::make_shared<MoveDown>(pQbertObject1,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject1, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject1, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s });

			std::shared_ptr<MoveUp> pMoveUpCommand{ std::make_shared<MoveUp>(pQbertObject1,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject1, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject1, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w });

			std::shared_ptr<MoveLeft> pMoveLeftCommand{ std::make_shared<MoveLeft>(pQbertObject1, pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject1, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject1, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a });

			std::shared_ptr<MoveRight> pMoveRightCommand{ std::make_shared<MoveRight>(pQbertObject1,pGameBoard1) };
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject1, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject1, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 0,SDLK_d });

			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject2, pGameBoard1);
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 1, SDLK_DOWN });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject2, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 1, SDLK_DOWN });
			pMoveDownCommand = std::make_shared<MoveDown>(pQbertObject2, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveDownCommand, true, XINPUT_GAMEPAD_DPAD_DOWN, 1, SDLK_DOWN });

			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject2, pGameBoard1);
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 1, SDLK_UP });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject2, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 1, SDLK_UP });
			pMoveUpCommand = std::make_shared<MoveUp>(pQbertObject2, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveUpCommand, true, XINPUT_GAMEPAD_DPAD_UP, 1, SDLK_UP });

			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject2, pGameBoard1);
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 1, SDLK_LEFT });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject2, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 1, SDLK_LEFT });
			pMoveLeftCommand = std::make_shared<MoveLeft>(pQbertObject2, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveLeftCommand, true, XINPUT_GAMEPAD_DPAD_LEFT, 1, SDLK_LEFT });

			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject2, pGameBoard1);
			scene1.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 1, SDLK_RIGHT });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject2, pGameBoard2);
			scene2.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 1, SDLK_RIGHT });
			pMoveRightCommand = std::make_shared<MoveRight>(pQbertObject2, pGameBoard3);
			scene3.AddCommand(StreamEngine::FlexibleCommand{ pMoveRightCommand, true, XINPUT_GAMEPAD_DPAD_RIGHT, 1, SDLK_RIGHT });
			StreamEngine::SceneManager::GetInstance().SetActiveScene("Level1");
		}
		break;
		case 2:
			break;
		default:;
		}
	}
}
