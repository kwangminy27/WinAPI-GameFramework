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

// frame_x, frame_y�� ������ �̾Ƴ��� �ִϸ��̼� ������ �����ǵ��� �� �� ���� ��?
struct ANIMATION_FRAME_INFO
{
	XY size{}; // �������� ������
	int start_x{}; // sprite atlas���� �ִϸ��̼� Ŭ�� ������ ������ ���� ������ �ε���
	int start_y{};
	int end_x{}; // ������ �������� ���� �ε���
	int count{};
	int count_x{}; // �ִϸ��̼� Ŭ���� ���� �ε����� ����
	int count_y{};
	int count_max_x{}; // sprite atlas�� �ִ� ���� ������ ����
	int count_max_y{};
};