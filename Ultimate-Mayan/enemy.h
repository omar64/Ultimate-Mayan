#ifndef ENEMY_H
#define ENEMY_H

#include "animatedsprite.h"
#include "globals.h"
#include "player.h"

#include <string>

class Graphics;

class Enemy : public AnimatedSprite
{
public:
	Enemy();
	Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnpoint, int timeToUpdate);

	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics, Camera &camera);
	virtual void touchPlayer(Player* player) = 0;

	const inline int getMaxHealth() { return this->_maxHealth; }
	const inline int getCurrentHealth() { return this->_currentHealth; }

protected:
	Direction _direction;
	int _maxHealth;
	int _currentHealth;
};

class AlienBlue : public Enemy
{
public:
	AlienBlue();
	AlienBlue(Graphics &graphics, Vector2 spawnPoint);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics, Camera &camera);
	void touchPlayer(Player* player);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
protected:
};
#endif