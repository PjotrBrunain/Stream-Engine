#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void StreamEngine::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void StreamEngine::SceneManager::FixedUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void StreamEngine::SceneManager::LateUpdate(const float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate(deltaTime);
	}
}

void StreamEngine::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

StreamEngine::Scene& StreamEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(std::make_shared<Scene>(name));
	m_Scenes.push_back(scene);
	return *scene.get();
}
