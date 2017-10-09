#include "Paddle.hpp"
#include <iostream>


void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}

void Paddle::update()
{

}

void Paddle::move(Direction dir, sf::View viewToRender) 
{
	sf::Vector2f pos = rectangle.shape.getPosition();
	switch(dir)
	{
	case Direction::UP:
		if ((rectangle.shape.getPosition().y + 1 * movementSpeed) > 50)
		rectangle.shape.setPosition(pos += sf::Vector2f(0, -1)*movementSpeed);
		break;
	case Direction::DOWN:
		if ((rectangle.shape.getPosition().y + -1 * movementSpeed) < viewToRender.getSize().y - (rectangle.height+50)) 
			rectangle.shape.setPosition(pos += sf::Vector2f(0, 1)*movementSpeed);
		break;
	case Direction::LEFT:
		if ((rectangle.shape.getPosition().x + -1 * movementSpeed) > 50) //TODO::check later for validness
		rectangle.shape.setPosition(pos += sf::Vector2f(-1, 0)*movementSpeed);
		break;
	case Direction::RIGHT:
		if ((rectangle.shape.getPosition().x + 1 * movementSpeed) < viewToRender.getSize().x - (rectangle.width + 50))
		rectangle.shape.setPosition(pos += sf::Vector2f(1, 0)*movementSpeed);
		break;
	default:
		break;
	}
}
