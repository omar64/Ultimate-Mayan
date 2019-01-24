#include <SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

// !?!?!?
#include <algorithm>
// ?!?!?!

/*  Game Class
	This class holds all information for our main game loop.
*/
namespace
{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;	

}

enum Controls {
	CONTROL_LEFT = SDL_SCANCODE_LEFT,
	CONTROL_RIGHT = SDL_SCANCODE_RIGHT,
	CONTROL_UP = SDL_SCANCODE_UP,
	CONTROL_DOWN = SDL_SCANCODE_DOWN,
	CONTROL_ATTACK = SDL_SCANCODE_Z,
	CONTROL_JUMP = SDL_SCANCODE_X,
	CONTROL_MAGIC = SDL_SCANCODE_C
};

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	this->_player = Player(graphics, 100, 100);
	this->_level = Level("Ultimate Mayan", Vector2(100,100), graphics);


	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while (true)
	{
		input.beginNewFrame();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
				{
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				input.keyUpEvent(event);
			}

			if (event.type == SDL_QUIT)
			{
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			return;
		}
		
		else if (input.isKeyHeld(CONTROL_RIGHT) == true)
		{
			if(input.wasKeyPressed(CONTROL_ATTACK) == true && input.wasKeyPressed(CONTROL_JUMP) == true)
			{
				printf("Rodar(Derecha)\n");			
			}
			else
			{
				this->_player.moveRight();
			}
		}
		else if (input.isKeyHeld(CONTROL_LEFT) == true)
		{
			if (input.wasKeyPressed(CONTROL_ATTACK) == true && input.wasKeyPressed(CONTROL_JUMP) == true)
			{
				printf("Rodar(Izquierda)\n");
			}
			else
			{
				this->_player.moveLeft();
			}
		}
		if (input.isKeyHeld(CONTROL_UP) == true)
		{
			if (input.wasKeyPressed(CONTROL_ATTACK) == true)
			{
				printf("SPECIAL ITEM\n");
			}
			else if (input.wasKeyPressed(CONTROL_MAGIC) == true)
			{
				printf("CARGA\n");
			}
		}

		else if (input.isKeyHeld(CONTROL_DOWN) == true)
		{
			if (input.wasKeyPressed(CONTROL_ATTACK) == true)
			{
				printf("ATAQUE BAJO\n");
			}
			else if (input.wasKeyPressed(CONTROL_JUMP) == true)
			{
				printf("BAJAR 1 Plataforma\n");
			}
			else if (input.wasKeyPressed(CONTROL_MAGIC) == true)
			{
				printf("Escudo\n");
			}
		}

		if (!input.isKeyHeld(CONTROL_LEFT) && !input.isKeyHeld(CONTROL_RIGHT))
		{
			this->_player.stopMoving();
		}

		if (input.wasKeyPressed(CONTROL_MAGIC) == true)
		{
			if (input.wasKeyPressed(CONTROL_ATTACK) == true)
			{
				printf("COMBO MAGIA/MELEE\n");
			}
			else
			{
				printf("BOTON\n");
			}
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		int aux = std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME);

		this->update(aux);
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();
	this->_level.draw(graphics);
	this->_player.draw(graphics); //100, 100

	graphics.flip();
}

void Game::update(float elapsedTime)
{
	this->_player.update(elapsedTime);
	this->_level.update(elapsedTime);
}

