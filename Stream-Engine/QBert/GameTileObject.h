#pragma once
#include <GameObject.h>

#include "Structs.h"

class GameTileObject final : public StreamEngine::GameObject
{
public:
	//void Update(float deltaTime) override;

	void UpgradeTile();
	void DegradeTile();

	bool IsMaxLevel();

private:
};

