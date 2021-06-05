#pragma once

struct Rect
{
	float bottom;
	float left;
	float width;
	float height;
};

enum class Move
{
	Up = 0,
	Down = 6,
	Left = 2,
	Right = 4
};

struct OffsetTileCoords
{
	int col;
	int row;
};

struct CubeTileCoords
{
	int x;
	int y;
	int z;
};
