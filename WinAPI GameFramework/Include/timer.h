#pragma once

#include "stdafx.h"

class Timer
{
	friend class Core;
public:
	void Initialize();
	void Update();

	float delta_time() const;
	int frame_per_second() const;

private:
	Timer() = default;

	std::chrono::time_point<std::chrono::high_resolution_clock> last_time_point_{};
	float delta_time_{};
	int frame_per_second_{};
};