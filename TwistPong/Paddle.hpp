#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "SFML/Graphics.hpp"
#include "Entity.hpp"

enum class Direction{UP, DOWN, LEFT, RIGHT};

class Paddle : public Entity
{
private:
	sf::Color color;
	//texture


public:
	struct Rectangle
	{
		sf::RectangleShape shape;
		int height;
		int width;
	} rectangle;



	sf::Vector2f normal; //for now we have only one normal (later an array?)
	EntityType type;

	float movementSpeed = 15.0f; // maybe set in ctor


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	 void update();
	 void move( Direction dir, sf::View viewToRender);

	Paddle(int height, int width, sf::Color color, EntityType type)
	{
		this->rectangle.height = height;
		this->rectangle.width = width;
		this->color = color;
		this->rectangle.shape.setFillColor(color);
		this->rectangle.shape.setSize(sf::Vector2f(width, height));
		this->entity = type;
	}
	Paddle() {}
};


#endif /*PADDLE_HPP*/
