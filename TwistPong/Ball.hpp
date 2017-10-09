#ifndef BALL_HPP
#define BALL_HPP

#include "SFML/Graphics.hpp"
#include "Entity.hpp"

class Ball : public Entity
{
private:
	sf::Color color;
	//texture

public:
	struct Circle
	{
		sf::CircleShape shape;
		sf::FloatRect bounds; //later change for perfect collisions
		float radius;
	} circle;


	sf::Vector2f direction;
	float movementSpeed = 8.0f; // maybe set in ctor
	float rotation = 0.0f;

	EntityType type = EntityType::BALL;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
	void move(sf::Vector2f direction, sf::View viewToRender);

	Ball(float radius, sf::Color color)
	{
		this->color = color;
		this->circle.radius = radius;
		this->circle.shape.setFillColor(color);
		this->circle.shape.setRadius(radius);
		this->circle.shape.setOrigin(circle.shape.getRadius(), circle.shape.getRadius()); //we set origin of shape to its center
	}
	Ball() {}
};


#endif /*BALL_HPP*/
