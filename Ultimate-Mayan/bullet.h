#ifndef BULLET_H
#define BULLET_H

#include "animatedsprite.h"
#include "globals.h"
#include "player.h"

class Graphics;

class Bullet : public AnimatedSprite
{
public:
	Bullet();
	Bullet(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnpoint, int timeToUpdate);
	~Bullet();

	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics, Camera &camera);
	virtual void touchEnemy(Player* player) = 0;

protected:
	Direction _direction;

};


class FirstBullet : public Bullet
{
public:
	FirstBullet();
	FirstBullet(Graphics &graphics, Vector2 spawnPoint, Direction _direction);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics, Camera &camera);
	void touchEnemy(Player* player);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
private:
	const float _velocity = 0.01f;
};

#endif