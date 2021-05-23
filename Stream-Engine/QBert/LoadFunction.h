#pragma once
#include "MiniginPCH.h"

#include "FPSComponent.h"
#include "GameBoardObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TestCommand.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"

void testLoadFunction()
{
	auto& scene = StreamEngine::SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<StreamEngine::GameObject> background{ std::make_shared<StreamEngine::GameObject>() };

	background->AddComponent(std::make_shared<StreamEngine::TextureComponent>("background.jpg", background));

	scene.Add(background);

	std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>() };

	logo->AddComponent(std::make_shared<StreamEngine::TextureComponent>("logo.png", logo));
	logo->GetTransform().SetPosition(216, 180, 0);

	scene.Add(logo);

	std::shared_ptr<StreamEngine::GameObject> text{ std::make_shared<StreamEngine::GameObject>() };

	text->AddComponent(std::make_shared<StreamEngine::TextComponent>("Lingua.otf", text));

	text->GetTransform().SetPosition(80, 20, 0);

	text->GetComponent<StreamEngine::TextComponent>()->SetText("Programming 4 Assignment");

	text->GetComponent<StreamEngine::TextComponent>()->SetSize(36);

	scene.Add(text);


	std::shared_ptr<StreamEngine::GameObject> fpsCounter{ std::make_shared<StreamEngine::GameObject>() };

	std::shared_ptr<StreamEngine::TextComponent> pTxtComponent{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",fpsCounter) };
	pTxtComponent->SetSize(26);
	pTxtComponent->SetColor({ 0,255,0,255 });
	const std::shared_ptr<StreamEngine::FPSComponent> pFPSComponent{ std::make_shared<StreamEngine::FPSComponent>(fpsCounter) };
	pTxtComponent->LinkText(pFPSComponent->GetTextLink());
	pTxtComponent->SetDoUpdate(true);

	fpsCounter->AddComponent(pTxtComponent);
	fpsCounter->AddComponent(pFPSComponent);

	fpsCounter->GetTransform().SetPosition(0, 0, 0);

	scene.Add(fpsCounter);


	StreamEngine::SceneManager::GetInstance().SetActiveScene("Demo");
}

void LoadQbert()
{
	auto& sceneLevel1 = StreamEngine::SceneManager::GetInstance().CreateScene("Level1");
	{
		std::shared_ptr<GameBoardObject> pGameBoard{ std::make_shared<GameBoardObject>(7,7) };
		sceneLevel1.Add(pGameBoard);
		
	}
}