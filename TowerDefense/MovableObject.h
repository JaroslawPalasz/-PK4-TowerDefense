#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	MovableObject()
	{

	}
	MovableObject(const TEXTURES &id, const sf::Vector2i _coordinates)
		: Object(id, _coordinates)
	{
		is_alive = true;
	}
	bool is_alive;
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->get_sprite());
	}

};
