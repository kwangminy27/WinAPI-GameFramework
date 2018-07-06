#pragma once

inline Point Point::operator+(float value) const
{
	return Point{ x + value, y + value };
}

inline void Point::operator+=(float value)
{
	x += value;
	y += value;
}

inline Point Point::operator-(float value) const
{
	return Point{ x - value, y - value };
}

inline void Point::operator-=(float value)
{
	x -= value;
	y -= value;
}

inline Point Point::operator*(float value) const
{
	return Point{ x * value, y * value };
}

inline void Point::operator*=(float value)
{
	x *= value;
	y *= value;
}

inline Point Point::operator/(float value) const
{
	return Point{ x / value, y / value };
}

inline void Point::operator/=(float value)
{
	x /= value;
	y /= value;
}

inline void Rect::SetRect(float l, float t, float r, float b)
{
	Rect::l = l;
	Rect::t = t;
	Rect::r = r;
	Rect::b = b;
}

inline void Rect::Move(float x, float y)
{
	l += x;
	t += y;
	r += x;
	b += y;
}

inline void Rect::Render(HDC device_context) const
{
	Rectangle(device_context, static_cast<int>(l), static_cast<int>(t), static_cast<int>(r), static_cast<int>(b));
}

inline void Rect::RenderEllipse(HDC device_context) const
{
	Ellipse(device_context, static_cast<int>(l), static_cast<int>(t), static_cast<int>(r), static_cast<int>(b));
}

inline float Rect::GetWidth() const
{
	return r - l;
}

inline float Rect::GetHeight() const
{
	return t - b;
}