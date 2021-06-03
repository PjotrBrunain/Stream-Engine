#pragma once
#include <GameObject.h>

#include "Structs.h"

class TeleportObject final : public StreamEngine::GameObject
{
public:
	void Render() override;

private:
	std::vector<Rect> m_SrcRect;
	int m_CurrentSrcRectIdx{};
};

