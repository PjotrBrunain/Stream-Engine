#pragma once
#include <memory>
#include "GameObject.h"
#include "Structs.h"

class QbertObject;
class GameTileObject;

class GameBoardObject final : public StreamEngine::GameObject
{
public:
	GameBoardObject(int rows, int columns, float posX, float posY, float height, float width);

	GameBoardObject(const GameBoardObject&) = delete;
	GameBoardObject(GameBoardObject&&) noexcept = delete;
	GameBoardObject& operator=(const GameBoardObject&) = delete;
	GameBoardObject& operator=(GameBoardObject&&) noexcept = delete;
	
	~GameBoardObject() override = default;

	void AddChild(const std::shared_ptr<GameObject>& pChild, int row, int column);

	const glm::vec3& GetTilePosition(int row, int column) const;
	float GetHexSize() const;
	float GetTileHeight(int row, int column) const;
	float GetTileWidth(int row, int column) const;

	int GetNrOfRows() const;
	int GetNrOfColumns() const;

	bool IsOnPlayboard(int row, int column);

	const std::shared_ptr<StreamEngine::GameObject>& GetGameTile(int row, int column);
	bool CheckWin();

	static float GetDistance(const OffsetTileCoords& coords1, const OffsetTileCoords& coords2);

	void Update(float deltaTime) override;

	bool GetHasWon() const;

	void SetNextScene(const std::string& name);

private:
	int m_Rows;
	int m_Columns;
	float m_HexSize;
	static CubeTileCoords GetCubeCoords(const OffsetTileCoords& coords);
	static float CubeDistance(const CubeTileCoords& a, const CubeTileCoords& b);
	bool m_HasWon;
	float m_FlashTime;
	bool m_SwitchFlag;
	int m_NumberOfFlashesToGo;
	std::string m_NextScene;
};
