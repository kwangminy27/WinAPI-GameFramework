#pragma once

#include "type.h"

XY XY::operator+(float value) const
{
	return XY{ x + value, y + value };
}

void XY::operator+=(float value)
{
	x += value;
	y += value;
}

XY XY::operator+(XY value) const
{
	return XY{ x + value.x, y + value.y };
}

void XY::operator+=(XY value)
{
	x += value.x;
	y += value.y;
}

XY XY::operator-(float value) const
{
	return XY{ x - value, y - value };
}

void XY::operator-=(float value)
{
	x -= value;
	y -= value;
}

XY XY::operator-(XY value) const
{
	return XY{ x - value.x, y - value.y };
}

void XY::operator-=(XY value)
{
	x -= value.x;
	y -= value.y;
}

XY XY::operator*(float value) const
{
	return XY{ x * value, y * value };
}

void XY::operator*=(float value)
{
	x *= value;
	y *= value;
}

XY XY::operator*(XY value) const
{
	return XY{ x * value.x, y * value.y };
}

void XY::operator*=(XY value)
{
	x *= value.x;
	y *= value.y;
}

XY XY::operator/(float value) const
{
	return XY{ x / value, y / value };
}

void XY::operator/=(float value)
{
	x /= value;
	y /= value;
}

XY XY::operator/(XY value) const
{
	return XY{ x / value.x, y / value.y };
}

void XY::operator/=(XY value)
{
	x /= value.x;
	y /= value.y;
}

void RECT_INFO::SetInfo(float _l, float _t, float _r, float _b)
{
	l = _l;
	t = _t;
	r = _r;
	b = _b;
}

void RECT_INFO::Move(float x, float y)
{
	l += x;
	t += y;
	r += x;
	b += y;
}

float RECT_INFO::GetWidth() const
{
	return r - l;
}

float RECT_INFO::GetHeight() const
{
	return t - b;
}

void CIRCLE_INFO::SetInfo(float x, float y, float r)
{
	center.x = x;
	center.y = y;
	radius = r;
}

void CIRCLE_INFO::Move(float x, float y)
{
	center.x += x;
	center.y += y;
}
