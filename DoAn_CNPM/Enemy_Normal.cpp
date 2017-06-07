#include "stdafx.h"
#include "Enemy_Normal.h"
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;


Enemy_Normal::Enemy_Normal()
{
	ts = 18;
	x = y = 300;
	dx = 4 - rand() % 8;
	dy = 4 - rand() % 8;
}

void Enemy_Normal::Move(int(&grid)[25][40])
{
	x += dx; if (grid[y / ts][x / ts] == 1) 
	{ 
		dx = -dx; x += dx; grid[y / ts][x / ts] = 0; 
	}
	y += dy; if (grid[y / ts][x / ts] == 1) { dy = -dy; y += dy; grid[y / ts][x / ts] = 0; }
}

void Enemy_Normal::floodFill(int(&grid)[25][40], int y, int x)
{
	if (grid[y][x] == 0) grid[y][x] = -1;
	if (grid[y - 1][x] == 0) floodFill(grid, y - 1, x);
	if (grid[y + 1][x] == 0) floodFill(grid, y + 1, x);
	if (grid[y][x - 1] == 0) floodFill(grid, y, x - 1);
	if (grid[y][x + 1] == 0) floodFill(grid, y, x + 1);
}

Enemy_Normal::~Enemy_Normal()
{
}
