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

// frame_x, frame_y만 별개로 뽑아내면 애니메이션 정보가 공유되도록 할 수 있을 듯?
struct ANIMATION_FRAME_INFO
{
	XY size{}; // 프레임의 사이즈
	int start_x{}; // sprite atlas에서 애니메이션 클립 정보를 구성할 시작 프레임 인덱스
	int start_y{};
	int end_x{}; // 마지막 프레임의 가로 인덱스
	int count{};
	int count_x{}; // 애니메이션 클립의 가로 인덱스의 개수
	int count_y{};
	int count_max_x{}; // sprite atlas의 최대 가로 프레임 개수
	int count_max_y{};
};