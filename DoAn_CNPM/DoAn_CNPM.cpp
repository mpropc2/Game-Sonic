// DoAn_CNPM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Enemy_Normal.h"
#include "IButton.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveUp.h"
#include "MoveDown.h"
using namespace sf;

const int SoDong = 25;
const int SoCot = 40;

int grid[SoDong][SoCot] = { 0 };
int ts = 18; //tile size

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(SoCot*ts, SoDong*ts), "AirXonix 2D!");
	window.setFramerateLimit(60);

	Texture tiles, gameOverImage, enemyImage;
	tiles.loadFromFile("images/tiles.png");
	gameOverImage.loadFromFile("images/gameover.png");
	enemyImage.loadFromFile("images/enemy.png");

	Sprite oVuong(tiles), imgGameOver(gameOverImage), enemyObject(enemyImage);
	imgGameOver.setPosition(100, 100);
	enemyObject.setOrigin(20, 20);

	int numOfEnemy = 5;
	Enemy_Normal enemies[10];

	bool isGameOver = true;
	int x = 0, y = 0, dx = 0, dy = 0;
	float timer = 0, delay = 0.07;
	Clock clock;

	for (int i = 0; i<SoDong; i++)
		for (int j = 0; j<SoCot; j++)
			if (i == 0 || j == 0 || i == SoDong - 1 || j == SoCot - 1)  grid[i][j] = 1;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape)
				{
					for (int i = 1; i<SoDong - 1; i++)
						for (int j = 1; j<SoCot - 1; j++)
							grid[i][j] = 0;

					x = 10; y = 0;
					isGameOver = true;
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) { IButton* moveLeft = new MoveLeft(); moveLeft->execute(dx, dy); };
		if (Keyboard::isKeyPressed(Keyboard::Right)) { IButton* moveRight = new MoveRight(); moveRight->execute(dx, dy); };
		if (Keyboard::isKeyPressed(Keyboard::Up)) { IButton* moveUp = new MoveUp(); moveUp->execute(dx, dy); };
		if (Keyboard::isKeyPressed(Keyboard::Down)) { IButton* moveDown = new MoveDown(); moveDown->execute(dx, dy); };

		if (!isGameOver) continue;

		if (timer > delay)
		{
			x += dx;
			y += dy;

			if (x<0) x = 0; if (x>SoCot - 1) x = SoCot - 1;
			if (y<0) y = 0; if (y>SoDong - 1) y = SoDong - 1;

			if (grid[y][x] == 2) isGameOver = false;
			if (grid[y][x] == 0) grid[y][x] = 2;
			timer = 0;
		}

		for (int i = 0; i<numOfEnemy; i++) enemies[i].Move(grid);

		if (grid[y][x] == 1)
		{
			dx = dy = 0;

			for (int i = 0; i < numOfEnemy; i++)
			{
				int _y = enemies[i].y / ts;
				int _x = enemies[i].x / ts;
				enemies[i].floodFill(grid, _y, _x);
			}

			for (int i = 0; i<SoDong; i++)
				for (int j = 0; j<SoCot; j++)
					if (grid[i][j] == -1) grid[i][j] = 0;
					else grid[i][j] = 1;
		}

		for (int i = 0; i<numOfEnemy; i++)
			if (grid[enemies[i].y / ts][enemies[i].x / ts] == 2) isGameOver = false;

		/////////vẽ giao diện//////////
		window.clear();

		for (int i = 0; i<SoDong; i++)
			for (int j = 0; j<SoCot; j++)
			{
				if (grid[i][j] == 0) continue;
				if (grid[i][j] == 1) oVuong.setTextureRect(IntRect(0, 0, ts, ts));
				if (grid[i][j] == 2) oVuong.setTextureRect(IntRect(54, 0, ts, ts));
				oVuong.setPosition(j*ts, i*ts);
				window.draw(oVuong);
			}

		oVuong.setTextureRect(IntRect(36, 0, ts, ts));
		oVuong.setPosition(x*ts, y*ts);
		window.draw(oVuong);

		enemyObject.rotate(10);
		for (int i = 0; i<numOfEnemy; i++)
		{
			enemyObject.setPosition(enemies[i].x, enemies[i].y);
			window.draw(enemyObject);
		}

		if (!isGameOver) window.draw(imgGameOver);

		window.display();
	}

	return 0;
}

