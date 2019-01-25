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
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y) :
		x(x), y(y)
	{}
	Vector2 zero()
	{
		return Vector2(0, 0);
	}
};

#endif