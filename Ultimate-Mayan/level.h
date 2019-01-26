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
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);

	std::vector<RectangleCollision> checkTileCollisions(const RectangleCollision &other);
	std::vector<Slope> checkSlopeCollisions(const RectangleCollision &other);

	const Vector2 getPlayerSpawnPoint() const;

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