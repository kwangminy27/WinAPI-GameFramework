#include "type.h"
#pragma once

inline XY XY::operator+(float value) const
{
	return XY{ x + value, y + value };
}

inline void XY::operator+=(float value)
{
	x += value;
	y += value;
}

inline XY XY::operator+(XY value) const
{
	return XY{ x + value.x, y + value.y };
}

inline void XY::operator+=(XY value)
{
	x += value.x;
	y += value.y;
}

inline XY XY::operator-(float value) const
{
	return XY{ x - value, y - value };
}

inline void XY::operator-=(float value)
{
	x -= value;
	y -= value;
}

inline XY XY::operator-(XY value) const
{
	return XY{ x - value.x, y - value.y };
}

inline void XY::operator-=(XY value)
{
	x -= value.x;
	y -= value.y;
}

inline XY XY::operator*(float value) const
{
	return XY{ x * value, y * value };
}

inline void XY::operator*=(float value)
{
	x *= value;
	y *= value;
}

inline XY XY::operator*(XY value) const
{
	return XY{ x * value.x, y * value.y };
}

inline void XY::operator*=(XY value)
{
	x *= value.x;
	y *= value.y;
}

inline XY XY::operator/(float value) const
{
	return XY{ x / value, y / value };
}

inline void XY::operator/=(float value)
{
	x /= value;
	y /= value;
}

inline XY XY::operator/(XY value) const
{
	return XY{ x / value.x, y / value.y };
}

inline void XY::operator/=(XY value)
{
	x /= value.x;
	y /= value.y;
}

inline void LTRB::SetLTRB(float l, float t, float r, float b)
{
	LTRB::l = l;
	LTRB::t = t;
	LTRB::r = r;
	LTRB::b = b;
}

inline void LTRB::Move(float x, float y)
{
	l += x;
	t += y;
	r += x;
	b += y;
}

inline void LTRB::RenderRectangle(HDC device_context) const
{
	Rectangle(device_context, static_cast<int>(l), static_cast<int>(t), static_cast<int>(r), static_cast<int>(b));
}

inline void LTRB::RenderEllipse(HDC device_context) const
{
	Ellipse(device_context, static_cast<int>(l), static_cast<int>(t), static_cast<int>(r), static_cast<int>(b));
}

inline float LTRB::GetWidth() const
{
	return r - l;
}

inline float LTRB::GetHeight() const
{
	return t - b;
}