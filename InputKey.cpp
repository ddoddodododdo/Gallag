#include "pch.h"
#include "InputKey.h"

void InputKey::SetInputInfo(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
			case VK_LEFT:
				isLeft = true;
				break;
			case VK_RIGHT:
				isRight = true;
				break;
			case VK_UP:
				isUp = true;
				break;
			case VK_DOWN:
				isDown = true;
				break;
			default:
				break;
		}
	}

	if (pMsg->message == WM_KEYUP) {
		switch (pMsg->wParam)
		{
			case VK_LEFT:
				isLeft = false;
				break;
			case VK_RIGHT:
				isRight = false;
				break;
			case VK_UP:
				isUp = false;
				break;
			case VK_DOWN:
				isDown = false;
				break;
			default:
				break;
		}
	}
}
