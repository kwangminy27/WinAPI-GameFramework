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

	//XY operator=(XY const& )

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

struct LTRB
{
	float l{};
	float t{};
	float r{};
	float b{};

	void SetLTRB(float _l, float _t, float _r, float _b);
	void Move(float x, float y);

	float GetWidth() const;
	float GetHeight() const;
};