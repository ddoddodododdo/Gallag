#include "pch.h"
#include "ObjMaker.h"

bool ObjMaker::CanMake()
{
	if (++count > max) {
		count = 0;
		return true;
	}

	return false;
}
