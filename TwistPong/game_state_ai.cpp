#include "game_state_ai.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

///This game mode handles one player and one AI, this game is meant to be retro stylized
//TODO::create global bounds
// create ui 
//make ball bounce


void GameStateAI::startGame()
{
	if(!started)
	{
		int random = rand() % 1000;
		int dirX = random % 2 ? -1 : 1;
		double dirY = random < 500 ? random / 1000.0f : -((1000.0f - random) / 1000.0f); 
		ball->direction = sf::Vector2f(-1, 0.1);
	}
}

void GameStateAI::restartGame()
{
	sf::Vector2i pos1 = sf::Vector2i(0, this->gameView.getCenter().y - paddle1->rectangle.height / 2);
	sf::Vector2i pos2 = sf::Vector2i(this->gameView.getSize().x - paddle1->rectangle.width, this->gameView.getCenter().y - paddle2->rectangle.height / 2);
	paddle1->rectangle.shape.setPosition(this->game->window.mapPixelToCoords(pos1));
	paddle2->rectangle.shape.setPosition(this->game->window.mapPixelToCoords(pos2));
	paddle1->normal = sf::Vector2f(1, 0);
	paddle2->normal = sf::Vector2f(-1, 0);

	sf::Vector2i posBall = sf::Vector2i(this->gameView.getCenter().x, this->gameView.getCenter().y);
	ball->circle.shape.setPosition(this->game->window.mapPixelToCoords(posBall));
	setBallRandomDirection();
}

void GameStateAI::setBallRandomDirection()
{
	int random = rand() % 1000;
	int dirX = random % 2 ? -1 : 1;
	double dirY = random < 500 ? random / 1000.0f : -((1000.0f - random) / 1000.0f);
	ball->direction = sf::Vector2f(-1, dirY);
}

bool GameStateAI::checkBallCollision(sf::RectangleShape other) const 
{
	// Find the closest point to the circle within the rectangle
	float ballX = ball->circle.shape.getPosition().x;
	float ballY = ball->circle.shape.getPosition().y;

	float otherX = other.getPosition().x;
	float otherY = other.getPosition().y;

	float closestX = std::clamp(ballX, otherX, otherX + other.getSize().x);
	float closestY = std::clamp(ballY, otherY, otherY + other.getSize().y);

	// Calculate the distance between the circle's center and this closest point
	float distanceX = ballX - closestX;
	float distanceY = ballY - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (ball->circle.shape.getRadius() * ball->circle.shape.getRadius());
}

void GameStateAI::checkCollisions()
{
	if (colVec.empty()) { return; }
	sf::RectangleShape shape;
	for(auto& it : colVec)
	{
		switch(it.first)
		{
		case EntityType::COLLIDERDOWN:
			shape = colDown->rect;
			if (checkBallCollision(shape))
				it.second = true;
			break;
		case EntityType::COLLIDERUP:
			shape = colUp->rect;
			if (checkBallCollision(shape))
				it.second = true;
			break;
		case EntityType::PADDLE1:
			shape = paddle1->rectangle.shape;
			if (checkBallCollision(shape))
			{
				it.second = true;
			}
			break;
		case EntityType::PADDLE2:
			shape = paddle2->rectangle.shape;
			if (checkBallCollision(shape))
			{
				it.second = true;
			}
			break;
		case EntityType::COLLIDERLEFT:
			shape = colLeft->rect;
			if (checkBallCollision(shape))
				it.second = true;
			break;
		case EntityType::COLLIDERRIGHT:
			shape = colRight->rect;
			if (checkBallCollision(shape))
				it.second = true;
			break;
		default:
			break;
		}
	}
}

sf::Vector2f GameStateAI::Reflection(sf::Vector2f vector, sf::Vector2f normal)
{
	return vector - 2 * Dot(vector, normal)*normal;
}

float GameStateAI::Dot(sf::Vector2f vector, sf::Vector2f other)
{
	return vector.x * other.x + vector.y *other.y;
}

void GameStateAI::draw()
{
	this->game->window.clear(sf::Color::Black);
	this->game->window.setView(gameView);
	sf::RenderStates states;
	this->game->window.draw(paddle1->rectangle.shape, states);
	this->game->window.draw(paddle2->rectangle.shape, states);
	this->game->window.draw(ball->circle.shape, states);
}

void GameStateAI::update() //not opening media :///
{
	if(started)
	{
		for(auto& it: colVec)
		{
			//update ball state
			if (it.first == EntityType::COLLIDERLEFT && it.second)
			{
				it.second = false;
				//check the trigger
				//adjust scoring
			}
			//update ball state
			if (it.first == EntityType::COLLIDERRIGHT && it.second)
			{
				it.second = false;
				//check the trigger
				//adjust scoring
			}
			if (it.first == EntityType::COLLIDERUP && it.second)
				{
					it.second = false;
					ball->direction = Reflection(ball->direction, colUp->normal);
				}
			if (it.first == EntityType::COLLIDERDOWN && it.second)
			{
				it.second = false;
				ball->direction = Reflection(ball->direction, colDown->normal);
				std::cout << "ball dir after collision with coldown, x: " << ball->direction.x << " y: " << ball->direction.y << std::endl;
			}
			if (it.first == EntityType::PADDLE1 && it.second)
			{
				it.second = false;
				if (ball->direction == -paddle1->normal)
					ball->direction = -ball->direction;
				else
					ball->direction = Reflection(ball->direction, paddle1->normal);
			}
			if (it.first == EntityType::PADDLE2 && it.second)
			{
				it.second = false;
				if (ball->direction == -paddle2->normal)
					ball->direction = -ball->direction;
				else
					ball->direction = Reflection(ball->direction, paddle2->normal);
			}
		}
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				paddle1->move(Direction::UP, this->gameView);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				paddle1->move(Direction::DOWN, this->gameView);
			}

			ball->move(ball->direction, this->gameView);

			paddle1->update();
			paddle2->update();

		}
}

void GameStateAI::handleInput() //for other games we need to poll keyboard for key pressed
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;

		case sf::Event::Resized:
			this->gameView.setSize(event.size.width, event.size.height);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space && !started)
			{
				std::cout << "game start" << std::endl;
				startGame();
				started = true;
			} 
			else if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			else if (event.key.code == sf::Keyboard::Tab) restartGame();
			break;
		default:
			break;
		}

	}
}

GameStateAI::GameStateAI(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
	std::cout << "LOADED";

	paddle1 = new Paddle(200, 50, sf::Color(255, 0, 0, 255), EntityType::PADDLE1);
	paddle2 = new Paddle(200, 50, sf::Color(0, 255, 0, 255), EntityType::PADDLE2);
	ball = new Ball(50, sf::Color(0, 0, 255, 255));
	colLeft = new Collider(this->game->window.getSize().y, 50, EntityType::COLLIDERLEFT);
	colRight = new Collider(this->game->window.getSize().y, 50,EntityType::COLLIDERRIGHT);
	colUp = new Collider(50, this->game->window.getSize().x, EntityType::COLLIDERUP);
	colDown = new Collider(50, this->game->window.getSize().x, EntityType::COLLIDERDOWN);

	sf::Vector2i pos1 = sf::Vector2i(0, this->gameView.getCenter().y - paddle1->rectangle.height / 2);
	sf::Vector2i pos2 = sf::Vector2i(this->gameView.getSize().x - paddle1->rectangle.width, this->gameView.getCenter().y - paddle2->rectangle.height / 2);
	paddle1->rectangle.shape.setPosition(this->game->window.mapPixelToCoords(pos1));
	paddle2->rectangle.shape.setPosition(this->game->window.mapPixelToCoords(pos2));

	colLeft->rect.setPosition(-50,  0);
	colRight->rect.setPosition(this->game->window.getSize().x, 0);
	colUp->rect.setPosition(0, -50);
	colDown->rect.setPosition(0, this->game->window.getSize().y);


	paddle1->normal = sf::Vector2f(1, 0);
	paddle2->normal = sf::Vector2f(-1, 0);
	colLeft->normal = sf::Vector2f(1, 0);
	colRight->normal = sf::Vector2f(-1, 0);
	colUp->normal = sf::Vector2f(0, 1);
	colDown->normal = sf::Vector2f(0, -1); //TODO:: down collider not fkin working dont kno why :((((((((((((


	sf::Vector2i posBall = sf::Vector2i(this->gameView.getCenter().x, this->gameView.getCenter().y);
	ball->circle.shape.setPosition(this->game->window.mapPixelToCoords(posBall));




	entities.push_back(static_cast<std::unique_ptr<Entity>>(paddle1));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(paddle2));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(ball));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(colDown));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(colUp));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(colRight));
	entities.push_back(static_cast<std::unique_ptr<Entity>>(colLeft));


	colVec.push_back(std::make_pair(EntityType::PADDLE1, false));
	colVec.push_back(std::make_pair(EntityType::PADDLE2, false));
	colVec.push_back(std::make_pair(EntityType::COLLIDERDOWN, false));
	colVec.push_back(std::make_pair(EntityType::COLLIDERLEFT, false));
	colVec.push_back(std::make_pair(EntityType::COLLIDERRIGHT, false));
	colVec.push_back(std::make_pair(EntityType::COLLIDERUP, false));
	colVec.push_back(std::make_pair(EntityType::COLLIDERDOWN, false));

}

GameStateAI::~GameStateAI()
{
	//del and clear
}

