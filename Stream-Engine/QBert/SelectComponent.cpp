#include "SelectComponent.h"

#include <utility>

#include "GameObject.h"

SelectComponent::SelectComponent(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_SelectedOption()
{
}

void SelectComponent::SetSelected(size_t select)
{
	if (select >= m_SelectPositions.size())
	{
		m_SelectedOption = m_SelectPositions.size() - 1;
	}
	else
	{
		m_SelectedOption = select;
	}
	if (m_pOwningGameObject.lock() != nullptr)
	{
		m_pOwningGameObject.lock()->GetTransform().SetPosition(m_SelectPositions[m_SelectedOption]);
	}
}

size_t SelectComponent::GetSelected() const
{
	return m_SelectedOption;
}

const glm::vec3& SelectComponent::GetSelectedPos() const
{
	return m_SelectPositions[m_SelectedOption];
}

void SelectComponent::AddSelectedPos(const glm::vec3& pos)
{
	m_SelectPositions.push_back(pos);
}
