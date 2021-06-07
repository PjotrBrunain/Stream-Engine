#pragma once
#include <BaseComponent.h>
#include <vector>
#include <glm/detail/type_vec.hpp>

class SelectComponent final : public StreamEngine::BaseComponent
{
public:
	SelectComponent(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject);
	~SelectComponent() override = default;

	void SetSelected(size_t select);
	size_t GetSelected() const;
	const glm::vec3& GetSelectedPos() const;
	void AddSelectedPos(const glm::vec3& pos);

private:
	size_t m_SelectedOption;
	std::vector<glm::vec3> m_SelectPositions;
};

