#pragma once
#include "Transform.h"

namespace StreamEngine
{
	class Texture2D;
	class BaseComponent;
	class GameObject final
	{
	public:
		void Update();

		void SetTexture(const std::string& filename);
		void AddComponent(BaseComponent* pComponent);
		template <typename T>
		T* GetComponent()
		{
			for (BaseComponent* bc: m_pComponents)
			{
				if (typeid(*bc) == typeid(T))
				{
					return dynamic_cast<T>(bc);
				}
			}
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<BaseComponent*> m_pComponents{};
	};
}
