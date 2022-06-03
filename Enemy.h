#pragma once
#include "GameObj.h"

class Enemy : public GameObj
{
	public:
		Enemy();
		double GetRandomX();
		int targetX = 0;
		int targetY = 0;

};

