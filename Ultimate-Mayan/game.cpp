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
	const int MAX_FRAME_TIME = 1000 / FPS;	
	float CAMERA_X_POS = 0;
	float CAMERA_Y_POS = 0;
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
	this->_camera = Camera(CAMERA_X_POS, CAMERA_Y_POS, globals::SCREEN_HEIGHT, globals::SCREEN_WIDTH);

	this->_level = Level("Ultimate Mayan02", graphics);
	this->_player = Player(graphics, this->_level.getPlayerSpawnPoint());
	this->_hud = HUD(graphics, this->_player);

	printf("player x:%d  ---  y:%d", this->_player.getX(), this->_player.getY());


	// No Touchie
	std::vector<FirstBullet> _player_bullets;
	// No Touchie

	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while (true)
	{
		input.beginNewFrame();

		float const temporal_player_x = this->_player.getX();
		float const temporal_player_y = this->_player.getY();


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
				// NO Touchie
				FirstBullet bullet(graphics, Vector2(50, 50), RIGHT);
				_player_bullets.push_back(bullet);
				// NO Touchie
				printf("BOTON\n");
			}
		}

		if (input.wasKeyPressed(CONTROL_JUMP) == true)
		{			
				this->_player.jump();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		int aux = std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME);
		this->_graphics = graphics;


		this->update(aux);
		// No Touchie
		for (auto &bullet : _player_bullets) // access by reference to avoid copying
		{
			bullet.update(aux, this->_player);
			bullet.draw(graphics, _camera);
		}
		// No Touchie
		
		this->tryToMoveCamera(temporal_player_x - this->_player.getX(), temporal_player_y - this->_player.getY());

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();
	this->_level.draw(graphics, _camera);
	this->_player.draw(graphics, _camera); //100, 100
	//this->_hud.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime)
{
	this->_player.update(elapsedTime);
	this->_level.update(elapsedTime, this->_player);
	this->_hud.update(elapsedTime, this->_player);

	//check collisions
	std::vector<RectangleCollision> others;
	if ((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0)
	{
		//player collided with at least one tile. handle it
		this->_player.handleTileCollisions(others);
	}
	//check slopes
	//std::vector<Slope> otherSlopes;
	//if ((otherSlopes = this->_level.checkSlopeCollisions(this->_player.getBoundingBox())).size() > 0)
	//{
	//	this->_player.handleSlopeCollisions(otherSlopes);
	//}

	//check enemies
	std::vector<Enemy*> enemies;
	
	if ((enemies = this->_level.checkEnemyCollisions(this->_player.getBoundingBox())).size() > 0)
	{
		this->_player.handleEnemyCollisions(enemies);
	}
}

void Game::tryToMoveCamera(float x_movement, float y_movement)
{
	this->_camera.x = this->_player.getX() - (globals::SCREEN_HEIGHT / 2) - 32;
	this->_camera.y = this->_player.getY() - (globals::SCREEN_WIDTH / 2) + 52;
	/*
	float new_camera_x = this->_camera.x - x_movement;
	float new_camera_y = this->_camera.y - y_movement;
	if (abs(x_movement) > 0)
	{
		//printf("x:%f    cam:%f      vel:%f\n", this->_player.getX(), this->_camera.x, x_movement);
	}
	if (new_camera_x >= 0 && new_camera_x <= this->_level.getSize().x - globals::SCREEN_WIDTH)
	{
		if (x_movement < 0)
		{
			if (this->_player.getX() >= globals::SCREEN_WIDTH / 2)
			{
				//delete this function
				//this->_player.putInTheMiddle();
				this->_camera.x = new_camera_x;
				this->_camera.y = new_camera_y;
			}
		}
	}
	*/
}



