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

struct XY
{
	float x{};
	float y{};

	XY operator+(float value) const;
	void operator+=(float value);

	XY operator-(float value) const;
	void operator-=(float value);

	XY operator*(float value) const;
	void operator*=(float value);

	XY operator/(float value) const;
	void operator/=(float value);
};

struct LTRB
{
	float l{};
	float t{};
	float r{};
	float b{};

	void SetLTRB(float _l, float _t, float _r, float _b);
	void Move(float x, float y);

	void RenderRectangle(HDC device_context) const;
	void RenderEllipse(HDC device_context) const;

	float GetWidth() const;
	float GetHeight() const;
};

#include "type.inl"