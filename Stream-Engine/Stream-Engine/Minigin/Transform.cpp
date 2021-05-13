#include "MiniginPCH.h"
#include "Transform.h"

StreamEngine::Transform::Transform(std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(false, pOwningGameObject)
{
}

StreamEngine::Transform::~Transform()
{
}

void StreamEngine::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
