#ifndef GAME_STATE_AI_HPP
#define  GAME_STATE_AI_HPP

#include "SFML/Graphics.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "collider.hpp"
#include "game_state.hpp"
#include <memory>


class GameStateAI : public GameState
{
private:
	sf::View gameView;

	Paddle* paddle1;
	Paddle* paddle2;
	Ball* ball;

	Collider* colUp;
	Collider* colDown;
	Collider* colLeft;
	Collider* colRight;

	std::vector<std::unique_ptr<Entity>> entities;


	bool started = false;

	std::vector<std::pair<EntityType, bool>> colVec;

	void startGame();
	void restartGame();
	void setBallRandomDirection();

	bool checkBallCollision(sf::RectangleShape other) const;

public:
	virtual void draw();
	virtual void update();
	virtual void handleInput();

	virtual void checkCollisions();

	static sf::Vector2f Reflection(sf::Vector2f vector, sf::Vector2f normal);
	static float Dot(sf::Vector2f vector, sf::Vector2f other);

	GameStateAI(Game* game);
	~GameStateAI();
};



#endif /*GAME_STATE_AI_HPP*/