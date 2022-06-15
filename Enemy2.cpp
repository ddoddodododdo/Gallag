#include "pch.h"
#include "Enemy2.h"

Enemy2::Enemy2()
{
	//Enemy::Enemy();
	sinParam = (rand() % 100) * 0.0314;
	bulletMaker.max = 60;
}

bool Enemy2::Move()
{
	sinParam += 0.1;
	double sinVal = sin(sinParam);

	posX += (velocityX + -velocityY * sinVal);
	posY += (velocityY + velocityX * sinVal);


	return !IsInGameBoard();
}
