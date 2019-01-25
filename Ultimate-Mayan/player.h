#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"

class Player  : public AnimatedSprite
{
	public:
		Player();
		Player(Graphics &graphics, float x, float y);
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

		virtual void animationDone(std::string currentAnimation);
		virtual void setupAnimations();

		void handleTileCollisions(std::vector<RectangleCollision> &others);

		const float getX() const;
		const float getY() const;
	private:
		float _dx, _dy;

		Direction _facing;
		bool _grounded;
};

#endif
