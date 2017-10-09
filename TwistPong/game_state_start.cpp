#include  "game_state_start.hpp"
#include  <iostream>
#include "game_state_ai.hpp"


void GameStateStart::draw()
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);


}

void GameStateStart::update()
{
	
}

void GameStateStart::handleInput()
{
	sf::Event event;

	while(game->window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;

		case sf::Event::Resized:
			this->view.setSize(event.size.width, event.size.height);
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space)
			{
				std::cout << "space pressed" << std::endl;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				std::cout << "a pressed" << std::endl;
				loadGame("AI");
			}
			else if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break; 
			//TODO:: add gui system for the menu and add loading from there not with key 
		}

	}
}

void GameStateStart::checkCollisions()
{
}

GameStateStart::GameStateStart(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	if(!music.openFromFile("media/track1.ogg"))
	{
		std::cout << "cannot open music file" << std::endl;
	}
	//music.play();

}

void GameStateStart::loadGame(std::string name)
{
	if (name == "AI")
	{
		this->game->pushState(new GameStateAI(this->game));
	}
	return;

}