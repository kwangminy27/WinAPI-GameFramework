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

void LTRB::SetLTRB(float l, float t, float r, float b)
{
	LTRB::l = l;
	LTRB::t = t;
	LTRB::r = r;
	LTRB::b = b;
}

void LTRB::Move(float x, float y)
{
	l += x;
	t += y;
	r += x;
	b += y;
}

float LTRB::GetWidth() const
{
	return r - l;
}

float LTRB::GetHeight() const
{
	return t - b;
}