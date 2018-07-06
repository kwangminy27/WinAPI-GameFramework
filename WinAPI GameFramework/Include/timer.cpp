#include "timer.h"

using namespace std;
using namespace chrono;

void Timer::Initialize()
{
	last_time_point_ = high_resolution_clock::now();
}

void Timer::Update()
{
	static int fps = 0;

	auto duration = high_resolution_clock::now() - last_time_point_;
	delta_time_ = duration.count() * 0.000'000'001f;
	last_time_point_ = high_resolution_clock::now();

	++fps;
	accumulation_time_ += delta_time_;
	if (accumulation_time_ >= 1.f)
	{
		fps_ = fps;
		fps = 0;
		accumulation_time_ = 0.f;
	}
}

float Timer::GetDeltaTime() const
{
	return delta_time_;
}

int Timer::GetFPS() const
{
	return fps_;
}
