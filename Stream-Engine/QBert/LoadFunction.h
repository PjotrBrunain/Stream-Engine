#pragma once
#include "MiniginPCH.h"

#include <fstream>

#include "FPSComponent.h"
#include "GameBoardObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TestCommand.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "GameTileObject.h"
#include "QbertObject.h"
#include "Scene.h"
#include "SpriteTextureComponent.h"

inline void testLoadFunction()
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

inline void ReadLevelFromFile(const std::string& filePath, StreamEngine::Scene& scene)
{
	std::ifstream fileStream{ filePath };
	std::string line{};
	if (fileStream)
	{
		do
		{
			std::getline(fileStream, line);
			if (line == "{")
			{
				std::shared_ptr<GameBoardObject> pGameBoard{ std::make_shared<GameBoardObject>(7,7,45.f,20.f,600.f,600.f) };
				pGameBoard->SetName("GameBoard");
				scene.Add(pGameBoard);
				std::getline(fileStream, line);
				if (line.find("tiles") != std::string::npos)
				{
					do
					{
						std::getline(fileStream, line);
						if (line.find("{") != std::string::npos)
						{
							std::shared_ptr<GameTileObject> pGameTile{ std::make_shared<GameTileObject>() };
							const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", pGameTile) };
							int row{};
							int column{};
							std::getline(fileStream, line);
							std::stringstream ss{ line };
							do
							{
								if (line.find("row") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									row = std::stoi(line);
								}
								if (line.find("column") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									column = std::stoi(line);
								}
								if (line.find("srcRect") != std::string::npos)
								{
									std::getline(fileStream, line);
									do
									{
										if (line.find("{") != std::string::npos)
										{
											Rect srcRect{};
											do
											{
												std::getline(fileStream, line);
												std::stringstream ss2{ line };
												if (line.find("bottom") != std::string::npos)
												{
													std::getline(ss2, line, ':');
													std::getline(ss2, line);
													srcRect.bottom = std::stof(line);
												}
												if (line.find("left") != std::string::npos)
												{
													std::getline(ss2, line, ':');
													std::getline(ss2, line);
													srcRect.left = std::stof(line);
												}
												if (line.find("width") != std::string::npos)
												{
													std::getline(ss2, line, ':');
													std::getline(ss2, line);
													srcRect.width = std::stof(line);
												}
												if (line.find("height") != std::string::npos)
												{
													std::getline(ss2, line, ':');
													std::getline(ss2, line);
													srcRect.height = std::stof(line);
												}
											} while (line.find("}") == std::string::npos);
											pSpriteComponent->AddSrcRect(srcRect);
										}
										std::getline(fileStream, line);
									} while (line.find("]") == std::string::npos);
								}
								std::getline(fileStream, line);
								ss = std::stringstream{ line };
							} while (line.find("}") == std::string::npos);

							pGameTile->AddComponent(pSpriteComponent);
							pGameBoard->AddChild(pGameTile, row, column);
							scene.Add(pGameTile);
						}
					} while (line.find("]") == std::string::npos);
				}

			}
		} while (!fileStream.eof());

	}
}

inline void LoadQbert()
{
	auto& sceneLevel1 = StreamEngine::SceneManager::GetInstance().CreateScene("Level1");
	/*std::shared_ptr<GameBoardObject> pGameBoard{ std::make_shared<GameBoardObject>(7,7,0.f,0.f,640.f,640.f) };
	sceneLevel1.Add(pGameBoard);

	std::shared_ptr<GameTileObject> pGameTile{ std::make_shared<GameTileObject>() };
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", pGameTile) };
	pGameTile->AddComponent(pSpriteComponent);
	pGameTile->SetSrcRect(Rect{ 320,0,32,32 });
	pGameBoard->AddChild(pGameTile, 5, 6);
	sceneLevel1.Add(pGameTile);

	std::shared_ptr<GameTileObject> pGameTile2{ std::make_shared<GameTileObject>() };
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent2{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", pGameTile2) };
	pGameTile->AddComponent(pSpriteComponent2);
	pGameTile->SetSrcRect(Rect{ 320,0,32,32 });
	pGameBoard->AddChild(pGameTile2, 5, 4);
	sceneLevel1.Add(pGameTile2);

	std::shared_ptr<GameTileObject> pGameTile3{ std::make_shared<GameTileObject>() };
	const std::shared_ptr<SpriteTextureComponent> pSpriteComponent3{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", pGameTile3) };
	pGameTile->AddComponent(pSpriteComponent3);
	pGameTile->SetSrcRect(Rect{ 320,0,32,32 });
	pGameBoard->AddChild(pGameTile3, 5, 5);
	sceneLevel1.Add(pGameTile3);*/

	ReadLevelFromFile("../Data/Level1.json", sceneLevel1);

	{
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

		sceneLevel1.Add(fpsCounter);
	}

	{
		std::shared_ptr<QbertObject> pQbertObject{ std::make_shared<QbertObject>() };
		pQbertObject->Init(0,3,std::reinterpret_pointer_cast<GameBoardObject>(sceneLevel1.GetObjectByName("GameBoard")));
		//pQbertObject->GetTransform().SetPosition(0, 0, 0);
		//pQbertObject->GetTransform().SetHeight(64);
		//pQbertObject->GetTransform().SetWidth(64);
		sceneLevel1.Add(pQbertObject);

		StreamEngine::InputManager::GetInstance().SetAmountOfPlayers(1);
		
	}
	
	StreamEngine::SceneManager::GetInstance().SetActiveScene("Level1");
}

