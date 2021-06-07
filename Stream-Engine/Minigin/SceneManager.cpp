#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void StreamEngine::SceneManager::Update(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->Update(deltaTime);
}

void StreamEngine::SceneManager::FixedUpdate(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->FixedUpdate(deltaTime);
}

void StreamEngine::SceneManager::LateUpdate(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->LateUpdate(deltaTime);
}

void StreamEngine::SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
}

StreamEngine::Scene& StreamEngine::SceneManager::GetScene(const std::string& name)
{
	return *m_Scenes[name].get();
}

void StreamEngine::SceneManager::SetActiveScene(std::string name)
{
	if (m_Scenes.find(name) != m_Scenes.end())
	{
		m_CurrentScene = name;
		InputManager::GetInstance().SetCommands(m_Scenes[name]->GetCommands());
	}
}

StreamEngine::Scene& StreamEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(std::make_shared<Scene>(name));
	m_Scenes.insert(std::make_pair(name, scene));
	return *scene.get();
}
