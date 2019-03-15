#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "globals.h"
#include "tile.h"
#include "rectanglecollision.h"
#include "slope.h"
#include "animatedtile.h"

class Graphics;
class Enemy;
class Player;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Graphics &graphics);
	~Level();
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics, Camera &camera);

	std::vector<RectangleCollision> checkTileCollisions(const RectangleCollision &other);
	std::vector<Slope> checkSlopeCollisions(const RectangleCollision &other);
	std::vector<Enemy*> checkEnemyCollisions(const RectangleCollision &other);

	const Vector2 getPlayerSpawnPoint() const;
	const inline Vector2 getSize() const { return Vector2(this->_size.x * this->_tileSize.x, this->_size.y * this->_tileSize.y); }

private:
	std::string _mapName;
	Vector2 _spawnPoint;

	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<RectangleCollision> _collisionRects;
	std::vector<Slope> _slopes;

	std::vector<AnimatedTile> _animatedTileList;
	std::vector<AnimatedTileInfo> _animatedTileInfos;


	std::vector<Enemy*> _enemies;

	/* void loadMap
	* Loads a map
	*/
	void loadMap(std::string mapName, Graphics &graphics);

	Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);

};

//Tileset structure
struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;
	Tileset() {
		this->FirstGid = -1;
	}
	Tileset(SDL_Texture* texture, int firstGid) {
		this->Texture = texture;
		this->FirstGid = firstGid;
	}
};




#endif