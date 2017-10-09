#include "Ball.hpp"


void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

 void Ball::update()
 {
	 
 }

void Ball::move(sf::Vector2f direction, sf::View viewToRender)
{
	sf::Vector2f pos = circle.shape.getPosition();
	pos += movementSpeed*direction;
	circle.shape.setPosition(pos);
	circle.bounds = circle.shape.getGlobalBounds();
}

