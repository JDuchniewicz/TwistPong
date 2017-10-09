#include <stack>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp" 

void Game::loadTextures()
{

}

void Game::loadFonts()
{
	sf::Font font;
	font.loadFromFile("media/font.ttf");
	this->fonts["main_font"] = font;

	return;
}

void Game::pushState(GameState* state)
{
	this->states.push(state);
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();
}

void Game::changeState(GameState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);
}

GameState* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::gameLoop()
{
	float frameTime = 1.0f / 60.0f;
	RestartClock();
	while (this->window.isOpen())
	{
		if (elapsed.asSeconds() >= frameTime)
		{
			if (peekState() == nullptr) continue;
			peekState()->handleInput();
			peekState()->checkCollisions();
			peekState()->update();
			this->window.clear(sf::Color::Black);
			peekState()->draw();
			this->window.display();
			this->RestartClock();
			elapsed -= sf::seconds(frameTime); //TODO: check if works, refactor it so it works smoothly 60 fps, moreover add instant control not weird event handling
		}
	}
}

void Game::RestartClock()
{
	elapsed += clock.restart();
}

Game::Game()
{
	this->loadTextures();
	this->loadFonts();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	this->window.create(sf::VideoMode(1600, 900), "Twist Pong", sf::Style::Default, settings);
	this->window.setFramerateLimit(60);

	srand(int(time(nullptr)));

	//this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty()) popState();
}


