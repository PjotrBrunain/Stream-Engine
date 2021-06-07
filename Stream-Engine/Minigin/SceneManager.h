#pragma once
#include <unordered_map>

#include "Singleton.h"

namespace StreamEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(const float deltaTime);
		void FixedUpdate(const float deltaTime);
		void LateUpdate(const float deltaTime);
		void Render();

		Scene& GetScene(const std::string& name);

		void SetActiveScene(std::string name);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;

		std::string m_CurrentScene;
	};
}
