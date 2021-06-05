#pragma once
//#pragma warning (push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
//#pragma warning (pop)

#include "BaseComponent.h"

namespace StreamEngine
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~Transform();

		Transform(const Transform&) = delete;
		Transform(Transform&&) noexcept = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(Transform&&) = delete;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& newPos);

		void SetHeight(const float height);
		void SetWidth(const float width);
		float GetHeight() const { return m_Height; }
		float GetWidth() const { return m_Width; }
	private:
		glm::vec3 m_Position;
		float m_Height;
		float m_Width;
	};
}
