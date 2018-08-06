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

enum class ANIMATION_CLIP_TYPE
{
	ATLAS, // 이 프레임워크에서는 sprite altas만 지원할 예정
	FRAME,
	END
};

enum class ANIMATION_OPTION
{
	 LOOP,
	 RETURN,
	 DESTROY,
	 END
};

enum class OBJECT_TYPE
{
	PLAYER,
	MONSTER,
	BULLET,
	STAGE,
	EFFECT,
	UI,
	NUMBER,
	BAR
};

enum class BUTTON_STATE
{
	NORMAL,
	MOUSEON,
	CLICK
};

enum class BAR_CUTTING_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class TILE_TYPE
{
	NORMAL,
	ISOMETRIC
};

enum class TILE_OPTION
{
	NONE,
	BLOCKED
};