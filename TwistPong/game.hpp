#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class GameState;

class Game
{
private:

	void loadTextures();
	void loadFonts();
	
	sf::Time elapsed;

public:

	std::stack<GameState*> states;

	sf::RenderWindow window;
	sf::Sprite background;
	sf::Clock clock;

	std::map<std::string, sf::Font> fonts;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();
	void RestartClock();

	Game();
	~Game();
};

#endif /* GAME_HPP */