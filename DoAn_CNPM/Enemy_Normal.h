#pragma once
class Enemy_Normal
{
public:
	int x, y, dx, dy, ts;
	Enemy_Normal();
	void Move(int (&grid)[25][40]);
	void floodFill(int (&grid)[25][40], int x, int y);
	~Enemy_Normal();
};

