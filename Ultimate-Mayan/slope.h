#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"

#include <cmath>

class Slope
{
public:
	Slope() 
	{}
	Slope(Vector2 p1, Vector2 p2) :
		_p1(p1),
		_p2(p2)
	{
		if (this->_p2.x - this->_p1.x != 0)
		{
			this->_slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
		}
	}

	void inline move(float x_movement, float y_movement) {
		this->_p1.x += x_movement; this->_p1.y += y_movement;
		this->_p2.x += x_movement; this->_p2.y += y_movement;
	}

	const inline float getSlope()
	{
		return this->_slope;
	}

	const bool collidesWith(const RectangleCollision &other) const
	{
		return
			(other.getRight() >= this->_p2.x &&
				other.getLeft() <= this->_p1.x &&
				other.getTop() <= this->_p2.y &&
				other.getBottom() >= this->_p1.y) ||
			(other.getRight() >= this->_p1.x &&
				other.getLeft() <= this->_p2.x &&
				other.getTop() <= this->_p1.y &&
				other.getBottom() >= this->_p2.y) ||
			(other.getLeft() >= this->_p1.x &&
				other.getRight() <= this->_p2.x &&
				other.getTop() <= this->_p1.y &&
				other.getBottom() >= this->_p2.y) ||
			(other.getLeft() >= this->_p2.x &&
				other.getRight() <= this->_p1.x &&
				other.getTop() <= this->_p2.y &&
				other.getBottom() >= this->_p1.y);
	}

	const inline Vector2 getP1() const { return this->_p1; };
	const inline Vector2 getP2() const { return this->_p2; };

	~Slope()
	{}
private:
	Vector2 _p1, _p2;
	float _slope;
};


#endif