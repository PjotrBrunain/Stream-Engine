#include "MiniginPCH.h"
#include "Stream-Engine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "FPSComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TestCommand.h"

using namespace std;
using namespace std::chrono;

void StreamEngine::Streamgin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		760,
		640,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void StreamEngine::Streamgin::LoadGame(const std::function<void()>& loadFunction) const
{
	loadFunction();
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//shared_ptr<GameObject> background{ std::make_shared<GameObject>() };

	//background->AddComponent(std::make_shared<TextureComponent>("background.jpg", background));

	//scene.Add(background);

	//shared_ptr<GameObject> logo{ std::make_shared<GameObject>() };

	//logo->AddComponent(std::make_shared<TextureComponent>("logo.png", logo));
	//logo->GetTransform().SetPosition(216, 180, 0);

	//scene.Add(logo);

	//shared_ptr<GameObject> text{ std::make_shared<GameObject>() };

	//text->AddComponent(std::make_shared<TextComponent>("Lingua.otf", text));

	//text->GetTransform().SetPosition(80, 20, 0);

	//text->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	//text->GetComponent<TextComponent>()->SetSize(36);

	//scene.Add(text);


	//shared_ptr<GameObject> fpsCounter{ std::make_shared<GameObject>() };

	//std::shared_ptr<TextComponent> pTxtComponent{ std::make_shared<TextComponent>("Lingua.otf",fpsCounter) };
	//pTxtComponent->SetSize(26);
	//pTxtComponent->SetColor({ 0,255,0,255 });
	//const std::shared_ptr<FPSComponent> pFPSComponent{ std::make_shared<FPSComponent>(fpsCounter) };
	//pTxtComponent->LinkText(pFPSComponent->GetTextLink());
	//pTxtComponent->SetDoUpdate(true);

	//fpsCounter->AddComponent(pTxtComponent);
	//fpsCounter->AddComponent(pFPSComponent);

	//fpsCounter->GetTransform().SetPosition(0, 0, 0);

	//scene.Add(fpsCounter);

	//InputManager::GetInstance().SetCommand(FlexibleCommand{ std::make_shared<TestCommand>(), true, ControllerButton::ButtonA });
	
	//auto go = std::make_shared<StreamEngine::GameObject>();
	//go->SetTexture("background.jpg");
	//scene.Add(go);

	//go = std::make_shared<StreamEngine::GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

void StreamEngine::Streamgin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void StreamEngine::Streamgin::Run(const std::function<void()>& loadFunction)
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame(loadFunction);

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = duration<float, std::milli>(currentTime - lastTime).count();
			lastTime = currentTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			lag += deltaTime;
			while (lag >= m_MsPerUpdate)
			{
				sceneManager.FixedUpdate(m_MsPerUpdate);
				lag -= m_MsPerUpdate;
			}
			sceneManager.LateUpdate(deltaTime);
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
