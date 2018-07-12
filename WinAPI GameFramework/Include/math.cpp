#pragma once

#include "math.h"

float Math::GetDistance(XY const& src, XY const& dest)
{
	float width = dest.x - src.x;
	float height = dest.y - src.y;
	return sqrt((width * width) + (height * height));
}