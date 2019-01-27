#include "enemy.h"

//Base enemy class

Enemy::Enemy()
{
}

Enemy::Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate) :
	AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate),
	_direction(LEFT),
	_maxHealth(0),
	_currentHealth(0)
{	
}

void Enemy::update(int elapsedTime, Player &player)
{
	AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}



//AlienBlue

AlienBlue::AlienBlue()
{}

AlienBlue::AlienBlue(Graphics &graphics, Vector2 spawnPoint) :
	Enemy(graphics, "Imagenes/Sprites/Enemy02.png", 0, 0, 32, 51, spawnPoint, 140)
{
	this->setupAnimations();
	this->playAnimation("meh");
}

void AlienBlue::update(int elapsedTime, Player &player)
{
	Enemy::update(elapsedTime, player);
	if (this->_x < 0 && this->_direction == LEFT)
	{
		this->_direction = RIGHT;
	}
	if(this->_x > globals::SCREEN_WIDTH - this->_boundingBox.getWidth() && this->_direction == RIGHT)
	{
		this->_direction = LEFT;
	}
	this->_x += this->_direction == RIGHT ? 0.05 : -0.05;
}

void AlienBlue::draw(Graphics &graphics)
{
	Enemy::draw(graphics);
}

void AlienBlue::animationDone(std::string currentAnimation)
{

}

void AlienBlue::setupAnimations()
{
	this->addAnimation(6, 0, 0, "meh", 32, 51, Vector2(0,0));
}

void AlienBlue::touchPlayer(Player* player)
{
	player->gainHealth(-1);
	printf("PUNCH IN DAH ROYAL COOOOOOOOOOOOOOOOCK!\n");
}