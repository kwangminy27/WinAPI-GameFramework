#include "physics.h"

float Physics::GravitionalAcceleration()
{
	static float kGravitionalAcceleration = 9.8f;
	return kGravitionalAcceleration;
}