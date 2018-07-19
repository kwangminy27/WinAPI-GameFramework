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
	RECT,
	SPHERE,
	PIXEL
};

enum class COLLISION_CALLBACK
{
	ENTER,
	STAY,
	LEAVE,
	END
};