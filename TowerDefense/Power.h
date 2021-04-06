#pragma once
#include "Object.h"

//TODO: different powers
class Power : public Object
{
public:
	Power(const TEXTURES &id, const sf::Vector2i _coordinates)
		: Object(id, _coordinates)
	{
		set_sprite_position(_coordinates, power_size, power_size);
		this->is_drawable = true;


	}
	Power(const TEXTURES &id, bool is_drawable = false)
		:is_drawable(is_drawable)
	{
		get_id() = id;
	}
	
	sf::Time cooldown;
	int cooldown_seconds = 10;
	int duration_time = 4;
	sf::Vector2f fcoordinates;
	sf::CircleShape boom_range;
	bool is_drawable = true;
	bool on_cooldown = false;
	const float power_size = 54.;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (is_drawable == true)
			target.draw(this->get_sprite());

	}
};