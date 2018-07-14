#pragma once

#include "stdafx.h"

class Math
{
public:
	static float PI();
	static float GetDistance(XY const& src, XY const& dest);
	static float GetAngle(XY const& src, XY const& dest);
	static float DegreeToRadian(float degree);
	static float RadianToDegree(float radian);
};