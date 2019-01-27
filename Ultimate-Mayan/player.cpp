#include "player.h"
#include "graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.15f;
	const float GRAVITY = 0.0015f;
	const float GRAVITY_CAP = 0.4f;
	const float JUMPING_FORCE = -.41f;
}

Player::Player()
{
}

Player::Player(Graphics &graphics, Vector2 spawnpoint) :
	AnimatedSprite(graphics, "Imagenes/Sprites/Rich01.png", 0, 0, 44, 45, spawnpoint.x, spawnpoint.y, 145),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false),
	_maxHealth(3),
	_currentHealth(3)
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
	if (this->_grounded)
	{
		this->playAnimation("RunLeft");
	}
	else
	{
		this->playAnimation("JumpLeft");
	}
	this->_dx = -player_constants::WALK_SPEED;
	this->_facing = LEFT;

}

void Player::moveRight()
{
	if (this->_grounded)
	{
		this->playAnimation("RunRight");
	}
	
	this->_dx = player_constants::WALK_SPEED;
	this->_facing = RIGHT;
}

void Player::jump()
{
	//for now
	if (this->_grounded)
	{
		this->playAnimation(this->_facing == RIGHT ? "JumpRight" : "JumpLeft");

		this->_dy = player_constants::JUMPING_FORCE;
		this->_grounded = false;
	}
}

void Player::stopMoving()
{
	this->_dx = 0;
	if (this->_grounded)
	{
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
	}
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
					this->_dy = 0;
					this->_y = others.at(i).getBottom() + 1;
					if (this->_grounded)
					{
						this->_dx = 0;
						this->_x -= this->_facing == RIGHT ? player_constants::WALK_SPEED : -player_constants::WALK_SPEED;
					}
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

//void handleSlopeCollisions
//handle collisions with all  slopes the player is colliding with
void Player::handleSlopeCollisions(std::vector<Slope> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		//calcuclate where on the slope the	player's bottom center is touching
		//and use y = mx + b to figure out the y position to place him at
		//First calculate "b" (slope intercept) using one of the points (b = y - mx)
		int b = (others.at(i).getP1().y	- (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

		//now get a player center x
		int centerX = this->_boundingBox.getCenterX();

		//now pass the x into the equation y = mx + b (using our newly found b and x) to get the new y position
		int newY = (others.at(i).getSlope() * centerX) + b - (this->_boundingBox.getWidth() / 2); //8 is a temporary magic number to fix a problem maybe use width

		//re-position the player to the new correct "y"
		if (this->_grounded)
		{
			this->_y = newY - this->_boundingBox.getHeight();
			this->_grounded = true;

		}
	}
}

void Player::handleEnemyCollisions(std::vector<Enemy*> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		others.at(i)->touchPlayer(this);
	}
}

void Player::gainHealth(int amount)
{
	this->_currentHealth += amount;
	if (this->_currentHealth > this->_maxHealth)
	{
		this->_currentHealth = this->_maxHealth;
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