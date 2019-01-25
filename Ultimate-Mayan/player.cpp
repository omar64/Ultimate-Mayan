#include "player.h"
#include "graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player()
{
}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "Imagenes/Sprites/Rich01.png", 0, 0, 44, 45, x, y, 145),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false)
{
	graphics.loadImage("Imagenes/Sprites/Rich01.png");
	this->setupAnimations();
	this->playAnimation("IdleRight");
}

void Player::setupAnimations()
{
	this->addAnimation(6, 0, 0, "RunRight", 44, 45, Vector2(0, 0));
	this->addAnimation(6, 0, 45, "RunLeft", 44, 45, Vector2(0, 0));
	this->addAnimation(5, 0, 90, "JumpRight", 44, 45, Vector2(0, 0));
	this->addAnimation(5, 0, 135, "JumpLeft", 44, 45, Vector2(0, 0));
	this->addAnimation(4, 0, 180, "IdleRight", 44, 45, Vector2(0, 0));
	this->addAnimation(4, 0, 224, "IdleLeft", 44, 45, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation)
{
	
}

const float Player::getX() const
{
	return this->_x;
}

const float Player::getY() const
{
	return this->_y;
}

void Player::moveLeft()
{
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;

}

void Player::moveRight()
{
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::jump()
{
	//for now
	if (this->_grounded)
	{
		this->_dy = -.5;
		this->_grounded = false;
	}
}

void Player::stopMoving()
{
	this->_dx = 0;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

//void handleTileCollisions
//Handles the collisions with all the tiles the player is colliding with
void Player::handleTileCollisions(std::vector<RectangleCollision> &others)
{
	//Figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < others.size(); i++)
	{
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE)
		{
			switch (collisionSide)
			{
				case sides::TOP:
					this->_y = others.at(i).getBottom() + 1;
					this->_dy = 0;
					break;
				case sides::BOTTOM:
					this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
					this->_dy = 0;
					this->_grounded = true;
					break;
				case sides::LEFT:
					this->_x = others.at(i).getRight() + 1;
					break;
				case sides::RIGHT:
					this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
					break;
			}
		}
	}
}

void Player::update(float elapsedTime)
{
	//Apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP)
	{
		this->_dy += player_constants::GRAVITY * elapsedTime;
	}

	//Move by dx
	this->_x += this->_dx * elapsedTime;
	AnimatedSprite::update(elapsedTime);	
	this->_y += this->_dy * elapsedTime;
}

void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}