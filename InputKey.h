#pragma once
class InputKey
{
	public:
		bool isUp = false;
		bool isDown = false;
		bool isLeft = false;
		bool isRight = false;

		void SetInputInfo(MSG* pMsg);

};

