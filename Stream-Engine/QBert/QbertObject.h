#pragma once
#include <GameObject.h>

#include "SpriteTextureComponent.h"

class GameBoardObject;

class QbertObject final : public StreamEngine::GameObject
{
public:
	QbertObject();
	void Init(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard);

	int GetRow() const;
	int GetColumn() const;

	void SetRow(int row);
	void SetColumn(int column);

	void SetMoveDirection(const Move& move);
	void Update(float deltaTime) override;

	void SetIsJumping(bool isJumping);
	bool GetIsJumping() const;
	void SetDestPos(const glm::vec3& destPos);
	void Die(int row, int column, const std::shared_ptr<GameBoardObject>& pGameBoard);
private:
	int m_Column;
	int m_Row;
	Move m_CurrentMoveDirection;
	bool m_IsJumping;
	glm::vec3 m_DestPos;
	float m_Speed;
	float m_Delta;
	int m_Lives;
};
