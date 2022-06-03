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
	//bool xFlag = target.posX <= posX

	return false;
}

void GameObj::DrawObject(CDC& dc, CImage *gameImage, DrawType type)
{
	int drawStartX = posX - sizeX;
	int drawStartY = posY - sizeY;

	gameImage->TransparentBlt(dc, drawStartX, drawStartY, sizeX * 2, sizeY * 2
						, 16 + 24 * 7, 55 + 24 * type, 16, 16, RGB(0, 0, 0));
}
