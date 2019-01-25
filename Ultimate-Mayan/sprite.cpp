#include "sprite.h"
#include "graphics.h"
#include "globals.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>

Sprite::Sprite()
{

}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : _x(posX), _y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL)
	{
		printf("\nError: Unable to load image\n");
		char full[_MAX_PATH];
		if (_fullpath(full, ".\\", _MAX_PATH) != NULL)
			printf("Full path is: %s\n", full);
		else
			printf("Invalid path\n");
	}
	this->_boundingBox = RectangleCollision(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);

}

Sprite::~Sprite()
{

}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update()
{
	this->_boundingBox = RectangleCollision(this->_x, this->_y, 
		this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE);
}

const RectangleCollision Sprite::getBoundingBox() const
{
	return this->_boundingBox;
}

//Side getCollisionSide
//Determine which side the collision happened on
const sides::Side Sprite::getCollisionSide(RectangleCollision &other) const
{
	int amtRight, amtLeft, amtTop, amtBottom;

	amtRight = this->getBoundingBox().getRight() - other.getLeft();
	amtLeft = this->getBoundingBox().getLeft() - other.getRight();
	amtTop = this->getBoundingBox().getTop() - other.getBottom();
	amtBottom = this->getBoundingBox().getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++)
	{
		if (vals[i] < lowest)
		{
			lowest = vals[i];
		}
	}

	return
		lowest == abs(amtRight) ? sides::RIGHT :
		lowest == abs(amtLeft) ? sides::LEFT :
		lowest == abs(amtTop) ? sides::TOP :
		lowest == abs(amtBottom) ? sides::BOTTOM :
		sides::NONE;
}