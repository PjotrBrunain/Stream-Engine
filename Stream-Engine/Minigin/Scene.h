#pragma once
#include "Command.h"
#include "InputManager.h"
#include "SceneManager.h"

namespace StreamEngine
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);

		void Add(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		std::shared_ptr<GameObject> GetObjectByName(std::string name) const;
		const std::vector<FlexibleCommand>& GetCommands() const;

		void AddCommand(const FlexibleCommand& command);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector<FlexibleCommand> m_SceneCommands{};

		static unsigned int m_IdCounter; 
	};

}
