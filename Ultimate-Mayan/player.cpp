#include "player.h"
#include "graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.98f;
}

Player::Player()
{
}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "Imagenes/Sprites/Rich01.png", 0, 0, 44, 45, x, y, 145)
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

void Player::stopMoving()
{
	this->_dx = 0;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float elapsedTime)
{
	//Move by dx
	this->_x += this->_dx * elapsedTime;
	AnimatedSprite::update(elapsedTime);	
}

void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}