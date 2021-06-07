#pragma once
#include <GameObject.h>

#include "Structs.h"

class GameBoardObject;
class QbertObject;

class TeleportObject final : public StreamEngine::GameObject
{
public:
	void Activate(std::weak_ptr<QbertObject> pQbertObject, std::weak_ptr<GameBoardObject> pGameBoardObject);
	void Update(float deltaTime) override;

	bool GetIsActivated() const;
private:
	glm::vec3 m_DestPos;
	bool m_IsActivated{};
	float m_Delta{5.f};
	const float m_Speed{ 0.5f };
	float m_RemainingFrameTime{60};
	std::weak_ptr<QbertObject> m_pQbertObject;
	std::weak_ptr<GameBoardObject> m_pGameBoardObject;
};

