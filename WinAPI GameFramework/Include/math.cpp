#include "math.h"

float Math::PI()
{
	float const kPi = 3.141592f;
	return kPi;
}

float Math::GetDistance(XY const& src, XY const& dest)
{
	float width = dest.x - src.x;
	float height = dest.y - src.y;
	return sqrt((width * width) + (height * height));
}

float Math::GetAngle(XY const& src, XY const& dest)
{
	float width = dest.x - src.x;
	float diagonal = Math::GetDistance(src, dest);
	float cos_theta = width / diagonal;
	float theta = RadianToDegree(acos(cos_theta));

	if (dest.y - src.y < 0.f)
		theta = 360.f - theta;

	return theta;
}

float Math::DegreeToRadian(float degree)
{
	return degree * Math::PI() / 180.f;
}

float Math::RadianToDegree(float radian)
{
	return radian * 180.f / Math::PI();
}