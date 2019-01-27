#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"
#include "level.h"
#include "enemy.h"

class Player  : public AnimatedSprite
{
	public:
		Player();
		Player(Graphics &graphics, Vector2 spawnpoint);
		void draw(Graphics &graphics);
		void update(float elapsedTime);

		/*	moveLeft
		Moves the player left by -dx
		*/
		void moveLeft();

		/*	moveRight
		Moves the player right by dx
		*/
		void moveRight();

		/* jump
			fucking moon jump up in this bitch
		*/
		void jump();

		/*	stopMoving
			stops moving the player
		*/
		void stopMoving();

		/*	void lookUp
			the player looks up
		*/
		void lookUp();
		/*	void stopLookingUp
			the player stops looking up
		*/
		void stopLookingUp();
		/*	void lookDown
			the player looks Downw or interacts
		*/
		void lookDown();
		/*	void stopLookingDown
			the player stops looking down or interacting
		*/
		void stopLookingDown();

		virtual void animationDone(std::string currentAnimation);
		virtual void setupAnimations();
		
		void handleTileCollisions(std::vector<RectangleCollision> &others);
		void handleSlopeCollisions(std::vector<Slope> &others);
		void handleEnemyCollisions(std::vector<Enemy*> &others);

		const float getX() const;
		const float getY() const;

		const inline int getMaxHealth() const { return this->_maxHealth; };
		const inline int getCurrentHealth() const { return this->_currentHealth; };

		void gainHealth(int amount);
private:
		float _dx, _dy;

		Direction _facing;
		bool _grounded;

		int _maxHealth;
		int _currentHealth;
};

#endif
