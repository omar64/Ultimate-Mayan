#ifndef SPRITE_H

#define SPRITE_H
#include <SDL.h>
#include <string>

#include "rectanglecollision.h"
#include "globals.h"

class Graphics;

/*	Sprite class
	holds all information for indivual sprites
*/

class Sprite
{
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);

	const RectangleCollision getBoundingBox() const;
	const sides::Side getCollisionSide(RectangleCollision &other) const;

	const inline float getX() const { return this->_x; }
	const inline float getY() const { return this->_y; }

	void setSourceRectX(int value);
	void setSourceRectY(int value);
	void setSourceRectW(int value);
	void setSourceRectH(int value);

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;
	RectangleCollision _boundingBox;

//private:

};

#endif