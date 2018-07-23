#pragma once

enum class RESOLUTION
{
	WIDTH = 1280,
	HEIGHT = 720
};

enum class FLAG
{
	RUN,
	END
};

enum class COLLIDER
{
	POINT,
	RECT,
	CIRCLE,
	PIXEL
};

enum class COLLISION_CALLBACK
{
	ENTER,
	STAY,
	LEAVE,
	END
};