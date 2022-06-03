#pragma once
#include "ObjMaker.h"

class GameObj
{
	public:
		const static int BOARD_SIZE_X = 600;
		const static int BOARD_SIZE_Y = 800;
		double posX;
		double posY;
		double sizeX;
		double sizeY;
		double velocityX = 0;
		double velocityY = 0;
		double speed = 1;
		int hp;
		ObjMaker bulletMaker;

		//true�� ������ ��->����d
		bool Move();
		
		//false�� ������ ��
		bool IsInGameBoard();
		bool CheckCollision(GameObj target);

		enum DrawType {
			PLAYER1, 
			PLAYER2,
			ENEMY1,
			ENEMY2,
			ENEMY3,
			ENEMY4
		};

		void DrawObject(CDC& dc, CImage* gameImage, DrawType type);
};

