#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"

class GameState
{
public:

	Game* game;

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleInput() = 0;
	virtual void checkCollisions() = 0;
};

#endif /* GAME_STATE_HPP */