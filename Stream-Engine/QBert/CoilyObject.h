#pragma once
#include <GameObject.h>
class QbertObject;
enum class Move;
class GameBoardObject;

class CoilyObject : public StreamEngine::GameObject
{
public:
	CoilyObject(bool isPlayerControlled, int bottomRow, std::shared_ptr<QbertObject> pQbert);
	CoilyObject(bool isPlayerControlled, int bottomRow, std::shared_ptr<QbertObject> pQbert1, std::shared_ptr<QbertObject> pQbert2);
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
	void Die(int row, int column);
private:
	int m_Column;
	int m_Row;
	Move m_CurrentMoveDirection;
	bool m_IsJumping;
	glm::vec3 m_DestPos;
	float m_Speed;
	float m_Delta;
	//int m_Lives;
	float m_DeadTimeRemaining;
	bool m_IsBall;
	int m_BottomRow;
	std::shared_ptr<GameBoardObject> m_pGameBoard;
	std::shared_ptr<QbertObject> m_pQbert1;
	std::shared_ptr<QbertObject> m_pQbert2;

	bool m_IsPlayerControlled;

	float m_CoolDown;
	
	void JumpDown();
	void JumpUp();
	void JumpRight();
	void JumpLeft();
};

