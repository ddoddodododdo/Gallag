#include "pch.h"
#include "Player.h"


void Player::Reset()
{
	posX = BOARD_SIZE_X * 0.5;
	posY = BOARD_SIZE_Y * 0.8;
	sizeX = 20;
	sizeY = 20;
	speed = 10;
	hp = 3;
	bulletMaker.max = 3;
	itemTime = 0;
}

void Player::Move(InputKey input)
{
	double moveX = input.isRight - input.isLeft;
	double moveY = input.isDown - input.isUp;

	if (abs(moveX) + abs(moveY) >= 2) {
		moveX *= 0.707;
		moveY *= 0.707;
	}

	posX += moveX * speed;
	posY += moveY * speed;

	if (posX < 0) posX = 0;
	else if (posX > BOARD_SIZE_X) posX = BOARD_SIZE_X;
	if (posY < 0) posY = 0;
	else if (posY > BOARD_SIZE_Y - 50) posY = BOARD_SIZE_Y - 50;

	itemTime--;
	
	//itemTime = itemTime > 0 ? itemTime-- : 0;
}

bool Player::CheckGetItem(GameObj item)
{
	bool flag = CheckCollision(item, 1);
	if (flag) {
		itemTime = 100;
		hp++;
	}
	
	return flag;
}


