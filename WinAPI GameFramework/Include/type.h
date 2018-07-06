#pragma once

enum class RESOLUTION
{
	WIDTH = 800,
	HEIGHT = 600
};

enum class FLAG
{
	RUN,
	END
};

struct Point
{
	float x{};
	float y{};

	Point operator+(float value) const;
	void operator+=(float value);

	Point operator-(float value) const;
	void operator-=(float value);

	Point operator*(float value) const;
	void operator*=(float value);

	Point operator/(float value) const;
	void operator/=(float value);
};

struct Rect
{
	float l{};
	float t{};
	float r{};
	float b{};

	void SetRect(float _l, float _t, float _r, float _b);
	void Move(float x, float y);
	void Render(HDC device_context) const;
	void RenderEllipse(HDC device_context) const;

	float GetWidth() const;
	float GetHeight() const;
};

#include "type.inl"