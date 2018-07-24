#pragma once

#include "enum.h"

struct XY
{
	float x{};
	float y{};

	XY operator+(float value) const;
	void operator+=(float value);
	XY operator+(XY value) const;
	void operator+=(XY value);

	XY operator-(float value) const;
	void operator-=(float value);
	XY operator-(XY value) const;
	void operator-=(XY value);

	XY operator*(float value) const;
	void operator*=(float value);
	XY operator*(XY value) const;
	void operator*=(XY value);

	XY operator/(float value) const;
	void operator/=(float value);
	XY operator/(XY value) const;
	void operator/=(XY value);
};

struct RECT_INFO
{
	float l{};
	float t{};
	float r{};
	float b{};

	void SetInfo(float _l, float _t, float _r, float _b);
	void Move(float x, float y);

	float GetWidth() const;
	float GetHeight() const;
};

struct CIRCLE_INFO
{
	XY center{};
	float radius{};

	void SetInfo(float x, float y, float r);
	void Move(float x, float y);
};

struct PIXEL8
{
	unsigned char r;
};

struct PIXEL24
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct PIXEL32
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};