#pragma once
#include "Transform.h"

namespace StreamEngine
{
	class Texture2D;
	class BaseComponent;
	class GameObject : std::enable_shared_from_this<GameObject>
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		void AddComponent(std::shared_ptr<BaseComponent> pComponent);
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			for (std::shared_ptr<BaseComponent> bc: m_pComponents)
			{
				BaseComponent* rawBc = bc.get();
				if (typeid(*rawBc) == typeid(T))
				{
					//return dynamic_cast<T>(bc);
					return std::dynamic_pointer_cast<T>(bc);
				}
			}
			return nullptr;
		}

		Transform& GetTransform();

		virtual void Render();

		bool IsVisual() const;

		GameObject() = default;
		GameObject(std::string name);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChildObjects{};
		bool m_IsVisual{};
		Transform m_Transform{ weak_from_this() };

		std::string m_Name{};
		std::weak_ptr<GameObject> m_pOwner{};
	};
}
