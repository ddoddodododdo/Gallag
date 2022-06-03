#include "pch.h"
#include "GameObj.h"

bool GameObj::Move() {
	posX += velocityX;
	posY += velocityY;

	return !IsInGameBoard();
}

bool GameObj::IsInGameBoard() {
	
	bool flag1 = posX > -100 && posY > -100;
	bool flag2 = (posX < BOARD_SIZE_X + 100) && (posY < BOARD_SIZE_Y);

	return flag1 && flag2;
}

bool GameObj::CheckCollision(GameObj target)
{
	bool xFlag = (posX - sizeX) <= target.posX && target.posX <= (posX + sizeX);
	bool yFlag = (posY - sizeY) <= target.posY && target.posY <= (posY + sizeY);
	
	if (xFlag && yFlag) 
		hp--;

	return xFlag && yFlag;
}

bool GameObj::CheckCollision(GameObj target, double sizePer)
{
	bool xFlag = (posX - sizeX * sizePer) <= target.posX && target.posX <= (posX + sizeX * sizePer);
	bool yFlag = (posY - sizeY * sizePer) <= target.posY && target.posY <= (posY + sizeY * sizePer);

	if (xFlag && yFlag)
		hp--;

	return xFlag && yFlag;
}


void GameObj::DrawObject(CDC& dc, CImage *gameImage, GameObj::DrawType type)
{
	int drawStartX = posX - sizeX;
	int drawStartY = posY - sizeY;

	gameImage->TransparentBlt(dc, drawStartX, drawStartY, sizeX * 2, sizeY * 2
						, 16 + 24 * 7, 55 + 24 * type, 16, 16, RGB(0, 0, 0));
}

void GameObj::SetVelocityFromTarget(int targetX, int targetY) {
	velocityX = targetX - posX;
	velocityY = targetY - posY;

	double sum = (abs(velocityX) + abs(velocityY)) / speed;

	velocityX /= sum;
	velocityY /= sum;
}

