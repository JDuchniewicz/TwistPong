#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "game_state.hpp"


class GameStateStart : public GameState
{
private: 
	sf::View view;
	sf::Music music;

	void loadGame(std::string name);

public:
	virtual void draw();
	virtual void update();
	virtual void handleInput();

	virtual void checkCollisions();

	GameStateStart(Game* game);
};



#endif /*GAME_STATE_START_HPP*/