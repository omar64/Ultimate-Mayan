#include "bullet.h"

//base Bullet

Bullet::Bullet()
{
}

Bullet::Bullet(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate) :
	AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate)
{
}

Bullet::~Bullet()
{
}

void Bullet::update(int elapsedTime, Player &player)
{
	AnimatedSprite::update(elapsedTime);
}

void Bullet::draw(Graphics &graphics, Camera &camera)
{
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}


//FirstBullet

FirstBullet::FirstBullet()
{}

FirstBullet::FirstBullet(Graphics &graphics, Vector2 spawnPoint, Direction direction) :
	Bullet(graphics, "Imagenes/Sprites/Bala.png", 0, 0, 4, 4, spawnPoint, 200)
{
	this->_direction = direction;
	this->setupAnimations();
	this->playAnimation("meh");
}

void FirstBullet::update(int elapsedTime, Player &player)
{
	this->_x += this->_direction == RIGHT ? this->_velocity : -this->_velocity;
	printf("Bullet: x:%d   y:%d", this->_x, this->_y);
	Bullet::update(elapsedTime, player);
}

void FirstBullet::draw(Graphics &graphics, Camera &camera)
{
	Bullet::draw(graphics, camera);
}

void FirstBullet::animationDone(std::string currentAnimation)
{

}

void FirstBullet::setupAnimations()
{
	this->addAnimation(3, 0, 0, "meh", 4, 4, Vector2(0, 0));
}

void FirstBullet::touchEnemy(Player* player)
{
	player->gainHealth(-1);
	printf("PUNCH IN DAH ROYAL COOOOOOOOOOOOOOOOCK!\n");
}
