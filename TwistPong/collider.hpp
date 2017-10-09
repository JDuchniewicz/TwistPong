#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "SFML/Graphics.hpp"
#include "Entity.hpp"

class Collider : public Entity{


public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();

	bool isTrigger = false;
	bool isCollider = true;

	EntityType type;
	sf::Vector2f normal;
	sf::RectangleShape rect;

	Collider(int height, int width, EntityType type)
	{
		this->rect.setSize(sf::Vector2f(width, height));
		this->type = type;
	}
};


#endif /*COLLIDER_HPP*/
