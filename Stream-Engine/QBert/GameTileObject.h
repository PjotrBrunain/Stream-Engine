#pragma once
#include <GameObject.h>

struct Rect
{
	float bottom;
	float left;
	float width;
	float height;
};

class GameTileObject final : public StreamEngine::GameObject
{
public:
	void Update(float deltaTime) override;
	void Render() override;

	void SetSrcRect(const Rect& srcRect);

private:
	Rect m_SrcRect{};
};

