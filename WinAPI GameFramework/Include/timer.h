#pragma once

#include "stdafx.h"

class Timer
{
public:
	Timer() = default;

	void Initialize();
	void Update();
	float GetDeltaTime() const;
	int GetFPS() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> last_time_point_{};
	float delta_time_{};
	float accumulation_time_{};
	int fps_{};
};