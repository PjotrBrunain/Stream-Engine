#pragma once
#include <memory>

namespace StreamEngine
{
	class GameObject;
	
	class BaseComponent
	{
	public:
		BaseComponent(bool isVisual, std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~BaseComponent();

#pragma warning (push)
#pragma warning (disable:4100)
		virtual void Update(float deltaTime) {};
		virtual void FixedUpdate(float deltaTime) {};
		virtual void LateUpdate(float deltaTime) {};
#pragma warning (pop)
		virtual void Render() const {};

		bool IsVisual() const;
		
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) noexcept = delete;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&) noexcept = delete;
	private:
		bool m_IsVisual;
	protected:
		//GameObject* m_pOwningGameObject;
		std::weak_ptr<GameObject> m_pOwningGameObject;
	};
}
