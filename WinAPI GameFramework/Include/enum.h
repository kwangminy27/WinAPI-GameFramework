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

enum class ANIMATION_CLIP_TYPE
{
	ATLAS, // 이 프레임워크에서는 sprite altas만 사용할 예정
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
	UI
};