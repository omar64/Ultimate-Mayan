#ifndef RECTANGLECOLLISION_H
#define RECTANGLECOLLISION_H

#include "globals.h"

class RectangleCollision
{
public:
	RectangleCollision()
	{}

	RectangleCollision(int x, int y, int width, int height) :
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{

	}

	const int getCenterX() const
	{
		return this->_x + this->_width / 2;
	}

	const int getCenterY() const
	{
		return this->_y + this->_height / 2;
	}

	const int getLeft() const
	{
		return this->_x;
	}

	const int getRight() const
	{
		return this->_x + this->_width;
	}

	const int getTop() const
	{
		return this->_y;
	}

	const int getBottom() const
	{
		return this->_y + this->_height;
	}

	const int getWidth()
	{
		return this->_width;
	}

	const int getHeight()
	{
		return this->_height;
	}

	const int getSide(const sides::Side side) const
	{
		return
			side == sides::LEFT ? this->getRight() :
			side == sides::RIGHT ? this->getLeft() :
			side == sides::TOP ? this->getBottom() :
			side == sides::BOTTOM ? this->getTop() :
			sides::NONE;
	}

	//bool collidesWith
	//Takes in another RectangleCollision and checks if the two are colliding
	const bool collidesWith(const RectangleCollision &other)
	{
		return
			this->getRight() >= other.getLeft() &&
			this->getLeft() <= other.getRight() &&
			this->getTop() <= other.getBottom() &&
			this->getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const
	{
		return this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0;
	}

private:
	int _x, _y, _width, _height;
};


#endif // !RECTANGLECOLLISION_H