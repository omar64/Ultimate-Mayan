#include "hud.h"

#include "graphics.h"

HUD::HUD()
{
}


HUD::HUD(Graphics &graphics, Player &player)
{
	this->_player = player;
	this->_healthBarSprite = Sprite(graphics, "Imagenes/Sprites/Enemy01.png", 0, 0, 32, 32, 64, 64); //cambiar la imagen obvis dobis porque como que que asquito no?
	this->_healthNumber1 = Sprite(graphics, "Imagenes/Sprites/Enemy01.png", 64, 64, 32, 32, 128, 128);
}

void HUD::update(int elapsedTime, Player &player)
{
	this->_player = player;
}

void HUD::draw(Graphics &graphics)
{
	this->_healthBarSprite.draw(graphics, this->_healthBarSprite.getX(), this->_healthBarSprite.getY());
	this->_healthNumber1.draw(graphics, this->_healthNumber1.getX(), this->_healthNumber1.getY());
}