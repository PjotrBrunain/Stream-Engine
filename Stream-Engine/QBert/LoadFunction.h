#pragma once
#include <algorithm>

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
#include "Scene.h"
#include "SelectCommand.h"
#include "SelectComponent.h"
#include "SelectDownCommand.h"
#include "SelectUpCommand.h"
#include "SpriteTextureComponent.h"
#include "TeleportObject.h"

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
								if (line.find("roundrobbing") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									if (line.find("true") != std::string::npos)
									{
										pGameTile->SetRoundRobbing(true);
									}
									else if (line.find("false") != std::string::npos)
									{
										pGameTile->SetRoundRobbing(false);
									}
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
	std::shared_ptr<StreamEngine::GameObject> fpsCounter{ std::make_shared<StreamEngine::GameObject>() };
	{
		std::shared_ptr<StreamEngine::TextComponent> pTxtComponent{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",fpsCounter) };
		pTxtComponent->SetSize(26);
		pTxtComponent->SetColor({ 0,255,0,255 });
		const std::shared_ptr<StreamEngine::FPSComponent> pFPSComponent{ std::make_shared<StreamEngine::FPSComponent>(fpsCounter) };
		pTxtComponent->LinkText(pFPSComponent->GetTextLink());
		pTxtComponent->SetDoUpdate(true);

		fpsCounter->AddComponent(pTxtComponent);
		fpsCounter->AddComponent(pFPSComponent);

		fpsCounter->GetTransform().SetPosition(0, 0, 0);
	}
	
	//StartScreen
	{
		auto& sceneStartScreen = StreamEngine::SceneManager::GetInstance().CreateScene("StartScreen");

		std::shared_ptr<StreamEngine::GameObject> backGround{ std::make_shared<StreamEngine::GameObject>("backGround") };
		backGround->AddComponent(std::make_shared<StreamEngine::TextureComponent>("Background.png", backGround));
		backGround->GetTransform().SetHeight(640);
		backGround->GetTransform().SetWidth(760);
		sceneStartScreen.Add(backGround);

		std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>("logo") };
		std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", logo) };
		spriteComponent->AddSrcRect(Rect{ 32, 128, 92, 16 });
		spriteComponent->SetSrcRectIdx(0);
		logo->AddComponent(spriteComponent);

		logo->GetTransform().SetPosition(20, 20, 1);
		logo->GetTransform().SetHeight(32);
		logo->GetTransform().SetWidth(184);

		sceneStartScreen.Add(logo);

		std::shared_ptr<StreamEngine::GameObject> soloText{ std::make_shared<StreamEngine::GameObject>() };
		std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("q-bert-original.ttf", soloText) };
		textComp->SetColor(SDL_Color{ 0,185,0,255 });
		textComp->SetSize(32);
		textComp->SetText("SinglePlayer");
		soloText->AddComponent(textComp);

		soloText->GetTransform().SetPosition(64, 100, 1);
		sceneStartScreen.Add(soloText);

		std::shared_ptr<StreamEngine::GameObject> coopText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("q-bert-original.ttf", coopText);
		textComp->SetColor(SDL_Color{ 0,185,0,255 });
		textComp->SetSize(32);
		textComp->SetText("Co op");
		coopText->AddComponent(textComp);

		coopText->GetTransform().SetPosition(64, 180, 1);
		sceneStartScreen.Add(coopText);

		std::shared_ptr<StreamEngine::GameObject> versusText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("q-bert-original.ttf", versusText);
		textComp->SetColor(SDL_Color{ 0,185,0,255 });
		textComp->SetSize(32);
		textComp->SetText("Versus");
		versusText->AddComponent(textComp);

		versusText->GetTransform().SetPosition(64, 260, 1);
		sceneStartScreen.Add(versusText);

		std::shared_ptr<StreamEngine::GameObject> selectQbert{ std::make_shared<StreamEngine::GameObject>() };
		spriteComponent = std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", selectQbert);
		spriteComponent->AddSrcRect(Rect{ 0, 64, 16,16 });
		spriteComponent->SetSrcRectIdx(0);
		selectQbert->AddComponent(spriteComponent);
		selectQbert->GetTransform().SetHeight(32);
		selectQbert->GetTransform().SetWidth(32);
		selectQbert->GetTransform().SetPosition(16, 100, 1);
		sceneStartScreen.Add(selectQbert);

		std::shared_ptr<SelectComponent> selComp{ std::make_shared<SelectComponent>(selectQbert) };
		selComp->AddSelectedPos({ 16,100,1 });
		selComp->AddSelectedPos({ 16, 180,1 });
		selComp->AddSelectedPos({ 16,260,1 });
		selComp->SetSelected(0);
		selectQbert->AddComponent(selComp);

		sceneStartScreen.AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectDownCommand>(selectQbert), true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s,0 });
		sceneStartScreen.AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectUpCommand>(selectQbert), true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w, 0 });
		sceneStartScreen.AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectCommand>(selectQbert), true, XINPUT_GAMEPAD_A, 0, SDLK_RETURN, 0 });
		sceneStartScreen.Add(fpsCounter);
	}
	
	//Level1
	{
		auto& sceneLevel1 = StreamEngine::SceneManager::GetInstance().CreateScene("Level1");

		ReadLevelFromFile("../Data/Level1.json", sceneLevel1);

		sceneLevel1.Add(fpsCounter);

		std::shared_ptr<GameBoardObject> pGameBoard{ std::dynamic_pointer_cast<GameBoardObject>(sceneLevel1.GetObjectByName("GameBoard")) };
		
		pGameBoard->SetNextScene("Level2");

		std::shared_ptr<TeleportObject> teleport1{ std::make_shared<TeleportObject>() };
		std::shared_ptr<SpriteTextureComponent> spriteComp{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", teleport1) };
		spriteComp->AddSrcRect(Rect{ 352, 0, 16,16 });
		spriteComp->AddSrcRect(Rect{ 80, 224, 32,32 });
		spriteComp->AddSrcRect(Rect{ 80, 256, 32,32 });
		spriteComp->AddSrcRect(Rect{ 80, 288, 32,32 });
		spriteComp->AddSrcRect(Rect{ 80, 320, 32,32 });
		spriteComp->AddSrcRect(Rect{ 80, 352, 32,32 });
		spriteComp->AddSrcRect(Rect{ 80, 384, 32,32 });
		spriteComp->SetSrcRectIdx(0);
		teleport1->AddComponent(spriteComp);
		pGameBoard->AddChild(teleport1, 3, 0);
		teleport1->GetTransform().SetHeight(teleport1->GetTransform().GetHeight() / 2);
		teleport1->GetTransform().SetWidth(teleport1->GetTransform().GetWidth() / 2);
		sceneLevel1.Add(teleport1);
	}

	//Level2
	{
		auto& sceneLevel2 = StreamEngine::SceneManager::GetInstance().CreateScene("Level2");

		ReadLevelFromFile("../Data/Level2.json", sceneLevel2);

		sceneLevel2.Add(fpsCounter);

		std::dynamic_pointer_cast<GameBoardObject>(sceneLevel2.GetObjectByName("GameBoard"))->SetNextScene("Level3");
	}

	//Level3
	{
		auto& sceneLevel3 = StreamEngine::SceneManager::GetInstance().CreateScene("Level3");

		ReadLevelFromFile("../Data/Level3.json", sceneLevel3);

		sceneLevel3.Add(fpsCounter);

		std::dynamic_pointer_cast<GameBoardObject>(sceneLevel3.GetObjectByName("GameBoard"))->SetNextScene("WinScreen");
	}

	//DeathScreen
	{
		auto& sceneDeathScreen = StreamEngine::SceneManager::GetInstance().CreateScene("DeathScreen");
		std::shared_ptr<StreamEngine::GameObject> backGround{ std::make_shared<StreamEngine::GameObject>("backGround") };
		backGround->AddComponent(std::make_shared<StreamEngine::TextureComponent>("Background.png", backGround));
		backGround->GetTransform().SetHeight(640);
		backGround->GetTransform().SetWidth(760);
		sceneDeathScreen.Add(backGround);

		std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>("logo") };
		std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", logo) };
		spriteComponent->AddSrcRect(Rect{ 32, 128, 92, 16 });
		spriteComponent->SetSrcRectIdx(0);
		logo->AddComponent(spriteComponent);
		logo->GetTransform().SetPosition(20, 20, 1);
		logo->GetTransform().SetHeight(32);
		logo->GetTransform().SetWidth(184);

		sceneDeathScreen.Add(logo);

		std::shared_ptr<StreamEngine::GameObject> deathText{ std::make_shared<StreamEngine::GameObject>() };
		std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("q-bert-original.ttf",deathText) };
		textComp->SetSize(64);
		textComp->SetColor({ 0,185,0,255 });
		textComp->SetText("DEFEAT");
		deathText->AddComponent(textComp);
		deathText->GetTransform().SetPosition(20, 80, 1);

		sceneDeathScreen.Add(deathText);
	}

	//WinScreen
	{
		auto& sceneWinScreen{ StreamEngine::SceneManager::GetInstance().CreateScene("WinScreen") };
		std::shared_ptr<StreamEngine::GameObject> backGround{ std::make_shared<StreamEngine::GameObject>("backGround") };
		backGround->AddComponent(std::make_shared<StreamEngine::TextureComponent>("Background.png", backGround));
		backGround->GetTransform().SetHeight(640);
		backGround->GetTransform().SetWidth(760);
		sceneWinScreen.Add(backGround);

		std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>("logo") };
		std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - QBert - General Sprites.png", logo) };
		spriteComponent->AddSrcRect(Rect{ 32, 128, 92, 16 });
		spriteComponent->SetSrcRectIdx(0);
		logo->AddComponent(spriteComponent);
		logo->GetTransform().SetPosition(20, 20, 1);
		logo->GetTransform().SetHeight(32);
		logo->GetTransform().SetWidth(184);

		sceneWinScreen.Add(logo);

		std::shared_ptr<StreamEngine::GameObject> winText{ std::make_shared<StreamEngine::GameObject>() };
		std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("q-bert-original.ttf", winText) };
		textComp->SetSize(64);
		textComp->SetColor({ 0,185,0,255 });
		textComp->SetText("You won!");
		winText->AddComponent(textComp);
		winText->GetTransform().SetPosition(20, 80, 1);

		sceneWinScreen.Add(winText);
	}
	StreamEngine::SceneManager::GetInstance().SetActiveScene("StartScreen");
}
