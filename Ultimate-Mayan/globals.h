#ifndef GLOBAL_H

#define GLOBAL_H

namespace globals 
{
	const int SCREEN_WIDTH = 384;//384;
	const int SCREEN_HEIGHT = 288;//288;

	const float SPRITE_SCALE = 1.0f;	
}

namespace sides
{
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};
	
	inline Side getOppositeSide(Side side)
	{
		return
			side == TOP ? BOTTOM :
			side == BOTTOM ? TOP :
			side == LEFT ? RIGHT :
			side == RIGHT ? LEFT :
			NONE;

	}
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 
{
	float x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(float x, float y) :
		x(x), y(y)
	{}
	Vector2 zero()
	{
		return Vector2(0, 0);
	}
};

struct Camera
{
	float x, y, w, h;
	Camera() :
		x(0), y(0), w(0), h(0)
	{}
	Camera(float x, float y, float w, float h) :
		x(x), y(y), w(w), h(h)
	{}
};
#endif