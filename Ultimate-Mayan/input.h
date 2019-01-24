#ifndef INPUT_H

#define INPUT_H
#include <SDL.h>
#include <map>

class Input
{
public:
	void beginNewFrame();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);

	bool wasKeyPressed(int key);
	bool wasKeyReleased(int key);
	bool isKeyHeld(int key);
private:
	std::map<int, bool> _heldKeys;
	std::map<int, bool> _pressedKeys;
	std::map<int, bool> _releasedKeys;
};

#endif