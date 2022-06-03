#include "pch.h"
#include "Enemy.h"

Enemy::Enemy() {
	posY = rand() % (int)(BOARD_SIZE_X * 0.5) - 50;
	posX = GetRandomX();
	sizeX = 20;
	sizeY = 20;
	speed = 5;
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

void Enemy::DrawObject(CDC& dc, CImage* gameImage, GameObj::DrawType type)
{
	int drawStartX = posX - sizeX;
	int drawStartY = posY - sizeY;

	int selectImg = 7;
	if (bulletMaker.count < 2) 
		selectImg = 6;

	gameImage->TransparentBlt(dc, drawStartX, drawStartY, sizeX * 2, sizeY * 2
		, 16 + 24 * selectImg, 55 + 24 * type, 16, 16, RGB(0, 0, 0));
}
