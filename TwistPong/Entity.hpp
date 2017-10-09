#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SFML/Graphics.hpp"

enum class EntityType { PADDLE1, PADDLE2, COLLIDERLEFT, COLLIDERRIGHT, COLLIDERUP, COLLIDERDOWN, BALL, OBSTACLE, PADDLE3, PADDLE4};

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update() = 0;

	EntityType entity;
};


#endif /*ENTITY_HPP*/
