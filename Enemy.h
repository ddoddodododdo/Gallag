#pragma once
#include "GameObj.h"

class Enemy : public GameObj
{
	public:
		Enemy();
		int targetX = 0;
		int targetY = 0;

		double GetRandomX();
		bool Move();
		void DrawObject(CDC& dc, CImage* gameImage, GameObj::DrawType type);
};

