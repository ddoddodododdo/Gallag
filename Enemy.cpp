#include "pch.h"
#include "Enemy.h"

Enemy::Enemy() {
	posY = rand() % (int)(BOARD_SIZE_X * 0.5) - 50;
	posX = GetRandomX();
	sizeX = 20;
	sizeY = 20;
	hp = 2;
	bulletMaker.max = 30;

}

double Enemy::GetRandomX()
{
	double num = rand() % (BOARD_SIZE_X - 50) + 50;
	if (posY > 0)
		num = num > BOARD_SIZE_X * 0.5 ? BOARD_SIZE_X + 50 : -50;

	return num;
}