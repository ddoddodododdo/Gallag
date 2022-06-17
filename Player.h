#pragma once
#include "GameObj.h"
#include "InputKey.h"

class Player :
    public GameObj
{
    public:
        int itemTime;
        void Reset();
        //void Move(double moveX, double moveY);
        void Move(InputKey input);
        bool CheckGetItem(GameObj item);
        
    

};

